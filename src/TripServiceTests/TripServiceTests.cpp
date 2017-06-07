// TripServiceTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TripService/User.h"
#include "../TripService/TripService.h"
#include "../TripService/UserNotLoggedInException.h"
#include "UserSessionAccessor.h"
#include "FakeUserSession.h"
#include "FakeTripDAO.h"
#include <memory>

using namespace testing;

class TripServiceTests : public Test
{
protected:
	 FakeUserSession* fakeUserSession;

	~TripServiceTests()
	{
		//UserSessionAccessor::Set(nullptr);
	}
	void SetUp() override
	{
		fakeUserSession = new FakeUserSession();
		UserSessionAccessor::Set(fakeUserSession);
	}

	void TearDown() override
	{
		UserSessionAccessor::Set(nullptr);
	}
};

TEST_F(TripServiceTests, ShouldThrowExceptionWhenUserNotLoggedIn)
{
	EXPECT_CALL(*fakeUserSession, GetLoggedUser()).WillRepeatedly(Return(nullptr));

	TripService<TripDAO> tripService;

	User dummy(1);

	ASSERT_THROW(tripService.GetTripsByUser(dummy), UserNotLoggedInException);
}

TEST_F(TripServiceTests, shouldNotReturnTripsWhenLoggedUserIsNotAFriend)
{
	User user(1);

	EXPECT_CALL(*fakeUserSession, GetLoggedUser()).WillRepeatedly(Return(&user));

	TripService<TripDAO> tripService;

	User notFriend(2);
	auto trips = tripService.GetTripsByUser(notFriend);

	ASSERT_EQ(0, trips.size());
}

TEST_F(TripServiceTests, shouldReturnTripsWhenLoggedUserIsAFriend)
{
	User user(1);

	EXPECT_CALL(*fakeUserSession, GetLoggedUser()).WillRepeatedly(Return(&user));

	TripService<FakeTripsDAO> tripService;

	User myFriend(2);
	myFriend.AddFriend(user);
	myFriend.AddTrip(Trip(1));
	myFriend.AddTrip(Trip(2));

	auto trips = tripService.GetTripsByUser(myFriend);

	ASSERT_THAT(trips, ContainerEq(myFriend.Trips()));
}

int main(int argc, char** argv)
{
	InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
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

using namespace testing;

TEST(TripServiceTests, ShouldThrowExceptionWhenUserNotLoggedIn)
{
	User* NotLoggedUser = nullptr;

	auto fakeUserSession = new FakeUserSession();
	EXPECT_CALL(*fakeUserSession, GetLoggedUser()).WillRepeatedly(Return(NotLoggedUser));
	UserSessionAccessor::Set(fakeUserSession);

	TripService tripService;

	User dummy(1);

	ASSERT_THROW(tripService.GetTripsByUser(dummy), UserNotLoggedInException);
}

TEST(TripServiceTests, shouldNotReturnTripsWhenLoggedUserIsNotAFriend)
{
	User user(1);

	auto fakeUserSession = new FakeUserSession();
	EXPECT_CALL(*fakeUserSession, GetLoggedUser()).WillRepeatedly(Return(&user));
	UserSessionAccessor::Set(fakeUserSession);

	TripService tripService;

	User notFriend(2);
	auto trips = tripService.GetTripsByUser(notFriend);

	ASSERT_EQ(0, trips.size());
}

TEST(TripServiceTests, shouldReturnTripsWhenLoggedUserIsAFriend)
{
	User user(1);

	auto fakeUserSession = new FakeUserSession();
	EXPECT_CALL(*fakeUserSession, GetLoggedUser()).WillRepeatedly(Return(&user));
	UserSessionAccessor::Set(fakeUserSession);

	TripService tripService;

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
#include "catch.hpp"
#include "FakeUserSession.h"
#include "UserSessionAccessor.h"
#include "../TripService/TripService.h"
#include "../TripService/User.h"
#include "gmock/gmock.h"

TEST_CASE("Should throw exception if not logged in", "")
{
	User* NotLoggedUser = nullptr;

	auto fakeUserSession = new FakeUserSession();
	EXPECT_CALL(*fakeUserSession, GetLoggedUser()).WillRepeatedly(testing::Return(NotLoggedUser));
	UserSessionAccessor::Set(fakeUserSession);

	TripService tripService;

	User dummy(1);

	REQUIRE_THROWS_AS(tripService.GetTripsByUser(dummy), UserNotLoggedInException);
}


/*
 
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

*/
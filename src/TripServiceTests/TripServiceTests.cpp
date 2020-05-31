#include "gmock/gmock.h"
#include "catch.hpp"
#include "FakeTripsDAO.h"
#include "FakeUserSession.h"
#include "UserSessionAccessor.h"
#include "../TripService/TripService.h"
#include "../TripService/User.h"


using namespace
testing;

TEST_CASE("Should throw exception if not logged in", "")
{
	User* NotLoggedUser = nullptr;

	auto fakeUserSession = new FakeUserSession();
	EXPECT_CALL(*fakeUserSession, GetLoggedUser()).WillRepeatedly(testing::Return(NotLoggedUser));
	UserSessionAccessor::Set(fakeUserSession);

	TripService tripService;

	User dummy(1);

	REQUIRE_THROWS_AS(
		tripService.GetTripsByUser(dummy), UserNotLoggedInException);
}

TEST_CASE("Should not return trips when logged user is not a friend")
{
	User user(1);

	auto fakeUserSession = new FakeUserSession();
	EXPECT_CALL(*fakeUserSession, GetLoggedUser())
		.WillRepeatedly(Return(&user));

	UserSessionAccessor::Set(fakeUserSession);

	TripService tripService;

	User notFriend(2);
	auto trips = tripService.GetTripsByUser(notFriend);

	REQUIRE(trips.size() == 0);
}

TEST_CASE("Should return trips when logged user is a friend")
{
	User user(1);

	auto fakeUserSession = new FakeUserSession();
	EXPECT_CALL(*fakeUserSession, GetLoggedUser()).WillRepeatedly(Return(&user));
	UserSessionAccessor::Set(fakeUserSession);

	TripServiceBase<FakeTripsDAO> tripService;

	User myFriend(2);
	myFriend.AddFriend(user);
	myFriend.AddTrip(Trip(1));
	myFriend.AddTrip(Trip(2));

	auto trips = tripService.GetTripsByUser(myFriend);

	REQUIRE_THAT(trips, Catch::Equals(myFriend.Trips()));
}
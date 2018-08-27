// TripServiceTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "gmock/gmock.h"
#include "../TripService/User.h"
#include "../TripService/TripService.h"
#include "../TripService/UserNotLoggedInException.h"
#include "UserSessionAccessor.h"
#include "FakeUserSession.h"
#include "FakeTripDAO.h"

using namespace testing;

TEST_CASE("When TripService.GetTripsByUser is Called it ")
{
	FakeUserSession fakeUserSession;
	UserSessionAccessor::Set(&fakeUserSession);
	TripService<FakeTripsDAO> tripService;

	SECTION("Should Throw Exception When User Not Logged In")
	{
		EXPECT_CALL(fakeUserSession, GetLoggedUser()).WillRepeatedly(Return(nullptr));

		User dummy(1);

		REQUIRE_THROWS_AS(tripService.GetTripsByUser(dummy), UserNotLoggedInException);
	}

	SECTION("Should Not Return Trips When Logged User Is Not a Friend")
	{
		User user(1);
		EXPECT_CALL(fakeUserSession, GetLoggedUser()).WillRepeatedly(Return(&user));

		User notFriend(2);
		auto trips = tripService.GetTripsByUser(notFriend);

		REQUIRE(trips.size() == 0);
	}

	SECTION("Should Return Trips When Logged User Is a Friend")
	{
		User user(1);
		EXPECT_CALL(fakeUserSession, GetLoggedUser()).WillRepeatedly(Return(&user));

		User myFriend(2);
		myFriend.AddFriend(user);
		myFriend.AddTrip(Trip(1));
		myFriend.AddTrip(Trip(2));

		auto trips = tripService.GetTripsByUser(myFriend);

		REQUIRE(trips == myFriend.Trips());
	}
}

int main(int argc, char** argv)
{
	::testing::GTEST_FLAG(throw_on_failure) = true;
	InitGoogleMock(&argc, argv);

	return Catch::Session().run(argc, argv);
}
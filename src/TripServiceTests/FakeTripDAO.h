#pragma once
#include "../TripService/Trip.h"
#include <list>
#include "../TripService/User.h"


class FakeTripsDAO
{
public:
	static std::list<Trip> FindTripsByUser(User user)
	{
		return user.Trips();
	}
};

#pragma once
#include "../TripService/User.h"

class FakeTripsDAO
{
public:
	static std::vector<Trip> FindTripsByUser(User user)
	{
		return user.Trips();
	}
};

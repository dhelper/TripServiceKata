#pragma once
#include "User.h"

class TripDAO
{
public:
	inline static std::vector<Trip> FindTripsByUser(User user)
	{
		throw "TripDAO should not be invoked on an unit test.";
	}
};

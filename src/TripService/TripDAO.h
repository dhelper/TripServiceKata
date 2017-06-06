#pragma once
#include "User.h"

class TripDAO
{
public:
	inline static std::list<Trip> FindTripsByUser(User user)
	{
		throw "TripDAO should not be invoked on an unit test.";
	}
};

#pragma once
#include "../TripService/UserSession.h"

class UserSessionAccessor
{
public:
	static void Set(UserSession* other)
	{
		UserSession::instance = other;
	}
};

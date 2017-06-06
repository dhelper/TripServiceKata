#pragma once
#include "../TripService/UserSession.h"

class UserSessionAccessor
{
public:
	static void Set(UserSession* other)
	{
		// Execute singleton at least once
		UserSession::GetInstance();

		delete UserSession::instance;

		UserSession::instance = other;
	}
};

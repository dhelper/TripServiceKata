#pragma once

#include "../TripService/UserSession.h"

class UserSessionAccessor
{
public:
	static void Set(FakeUserSession* fakeUserSession)
	{
		UserSession::GetInstance();

		delete UserSession::instance;

		UserSession::instance = fakeUserSession;
	}
};
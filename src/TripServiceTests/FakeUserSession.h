#pragma once
#include "../TripService/UserSession.h"
#include "gmock/gmock.h"

class FakeUserSession : public UserSession
{
public:
	MOCK_METHOD(bool, IsUserLoggedIn, (User));
	MOCK_METHOD(User*, GetLoggedUser, ());

	void Replace()
	{
		
	}
};

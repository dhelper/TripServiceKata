#pragma once

#include "../TripService/UserSession.h"
#include "gmock/gmock.h"

class FakeUserSession : public UserSession
{
public:
	FakeUserSession(){}

	MOCK_METHOD1(IsUserLoggedIn, bool(User));
	MOCK_METHOD0(GetLoggedUser, User*());
};

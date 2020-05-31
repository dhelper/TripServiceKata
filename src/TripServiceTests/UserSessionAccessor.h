#pragma once

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
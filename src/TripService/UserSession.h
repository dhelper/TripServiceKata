#pragma once
#include "User.h"

class FakeUserSession;
class UserSessionAccessor;

class UserSession
{
	static UserSession *instance;
public:
	static UserSession* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new UserSession();
		}

		return instance;
	}

	virtual bool IsUserLoggedIn(User user)
	{
		throw "UserSession.IsUserLoggedIn() should not be called in an unit test";
	}

	virtual User* GetLoggedUser()
	{
		throw "UserSession.GetLoggedUser() should not be called in an unit test";
	}

private:
	UserSession() {};
	~UserSession() = default;
	UserSession(const UserSession& src) = delete;
	UserSession& operator=(const UserSession& rhs) = delete;

	friend class FakeUserSession;
	friend class UserSessionAccessor;
};

#pragma once
#include "Trip.h"
#include <list>
#include "UserNotLoggedInException.h"
#include "UserSession.h"
#include "TripDAO.h"

class User;

class TripService
{
public:
	static std::vector<Trip> GetTripsByUser(User user);

};

std::vector<Trip> TripService::GetTripsByUser(User user)
{
	std::vector<Trip> triplist;
	User* loggedUser = UserSession::GetInstance()->GetLoggedUser();
	bool isFriend = false;
	if (loggedUser)
	{
		for (auto i = user.GetFriends().begin(); i != user.GetFriends().end(); ++i)
		{
			if (*i == *loggedUser)
			{
				isFriend = true;
				break;
			}
		}
		if (isFriend)
		{
			triplist = TripDAO::FindTripsByUser(user);
		}
		return triplist;
	}
	else
	{
		throw UserNotLoggedInException();
	}
}
#pragma once
#include "Trip.h"
#include <list>
#include "UserNotLoggedInException.h"
#include "UserSession.h"
#include "TripDAO.h"

class User;

template<class T>
class TripService
{
public:
	static std::list<Trip> GetTripsByUser(User user);

};

template<class T>
std::list<Trip> TripService<T>::GetTripsByUser(User user)
{
	std::list<Trip> triplist;
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
			triplist = T::FindTripsByUser(user);
		}
		return triplist;
	}
	else
	{
		throw UserNotLoggedInException();
	}
}
#pragma once
#include "Trip.h"
#include <list>
#include "UserNotLoggedInException.h"
#include "UserSession.h"
#include "TripDAO.h"

class User;

template<class T>
class TripServiceBase
{
public:
	static std::vector<Trip> GetTripsByUser(User user);

};

class TripService : public TripServiceBase< TripDAO>
{

};

template <class T>
std::vector<Trip> TripServiceBase<T>::GetTripsByUser(User user)
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
			triplist = T::FindTripsByUser(user);
		}
		return triplist;
	}
	else
	{
		throw UserNotLoggedInException();
	}
}
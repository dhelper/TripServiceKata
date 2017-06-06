
#include "stdafx.h"
/*#include <list>
#include "TripDAO.h"
#include "TripService.h"
#include "UserSession.h"
#include "UserNotLoggedInException.h"

std::list<Trip> TripService::GetTripsByUser(User user)
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
			triplist = TripDAO::FindTripsByUser(user);
		}
		return triplist;
	}
	else
	{
		throw UserNotLoggedInException();
	}
}
*/

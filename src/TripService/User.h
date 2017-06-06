#pragma once
#include <list>
#include "Trip.h"

class User
{
public:
	inline User(int _id) :id(_id) {};

	inline std::list<User>& GetFriends() { return friends; }
	inline void AddFriend(User user) { friends.push_back(user); }
	inline std::list<Trip>& Trips() { return trips; }
	inline void AddTrip(Trip trip) { trips.push_back(trip); }

	inline bool operator==(User& other) { return (other.id == id); }
private:
	int id;
	std::list<Trip> trips;
	std::list<User> friends;
};

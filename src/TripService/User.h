#pragma once
#include <vector>
#include "Trip.h"

class User
{
public:
	inline User(int _id) :id(_id) {};

	inline std::vector<User>& GetFriends() { return friends; }
	inline void AddFriend(User user) { friends.push_back(user); }
	inline std::vector<Trip>& Trips() { return trips; }
	inline void AddTrip(Trip trip) { trips.push_back(trip); }

	inline bool operator==(User& other) { return (other.id == id); }
private:
	int id;
	std::vector<Trip> trips;
	std::vector<User> friends;
};

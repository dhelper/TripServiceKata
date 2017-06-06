#pragma once

class Trip
{
	int id;


public:
	Trip(int id)
		: id(id)
	{
	}


	friend bool operator==(const Trip& lhs, const Trip& rhs)
	{
		return lhs.id == rhs.id;
	}

	friend bool operator!=(const Trip& lhs, const Trip& rhs)
	{
		return !(lhs == rhs);
	}
};
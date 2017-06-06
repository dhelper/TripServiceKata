// TripServiceTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;

int main(int argc, char** argv)
{
	InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
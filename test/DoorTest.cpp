#include "gtest/gtest.h"
#include "../code/Door.h"

class DoorTest : public ::testing::Test 
{
	 protected:
		DoorTest() 
		{
		  testPtr = new Door ("Right");
		}
		Door* testPtr;
};
	 
TEST_F(DoorTest)
{
    EXPECT_EQ(false,testPtr->GetDoorStatus());
	EXPECT_EQ("Right",testPtr->GetDoorSide());
}

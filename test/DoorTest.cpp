#include "gtest/gtest.h"
#include "../code/Door.h"

class DoorTest : public ::testing::Test 
{
	 protected:
		DoorTest() 
		{
		  testPtr = new Door (NULL,"Right");
		}
		Door* testPtr;
};
	 
TEST_F(DoorTest, doorParamsTest)
{
    EXPECT_EQ(false,testPtr->GetDoorStatus());
	EXPECT_EQ("Right",testPtr->GetDoorSide());
	testPtr->SetDoorStatus(true);
	EXPECT_EQ(true,testPtr->GetDoorStatus());
}

TEST_F(DoorTest, hasValvesTest)
{
	std::vector<Valve*> v = testPtr->GetValves();
	EXPECT_EQ(3, v.size());
}

TEST_F(DoorTest, createMessageTest)
{
	std::string compareStr1 = "GetDoorRight;";
	std::string compareStr2 = "SetDoorRight:open;";
	std::string compareStr3 = "SetDoorRight:close;";
	EXPECT_EQ(compareStr1, testPtr->CreateDoorMessage("", true);
	EXPECT_EQ(compareStr2, testPtr->CreateDoorMessage("open", false);
	EXPECT_EQ(compareStr3, testPtr->CreateDoorMessage("close", false);
}

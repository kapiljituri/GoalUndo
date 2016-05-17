/**
 * Unit Tests for GoalUndo class
**/

#include <gtest/gtest.h>
#include "GoalUndo.h"

class GoalUndoTest : public ::testing::Test
{
	protected:
		GoalUndoTest(){}
		virtual ~GoalUndoTest(){}
		virtual void SetUp(){}
		virtual void TearDown(){}
};

TEST(GoalUndoTest, EmptyCheck)
{
  GoalUndo task;
	ASSERT_EQ("", task.getGoal());
}

TEST(GoalUndoTest, NotEmptyCheck)
{
  GoalUndo task;
  task.addOperation("gFirst", "oFirst");
	ASSERT_EQ("gFirst", task.getGoal());
}

TEST(GoalUndoTest, MultipleOperationsInSingleGoal)
{
  int i;
  GoalUndo task;
  // Adding first operation in first goal
  task.addOperation("gFirst", "myOperation");

  // Adding 20 more operations in single goal (total = 21)
  for(i=0; i<20; i++){
    task.addOperation("myOperation");
  }

  // Removing 19 operations (remaining = 2)
  for(i=0; i<19; i++){
    task.undoOperation();
  }

  // Asserting if 2 operations present
  ASSERT_EQ("myOperation myOperation", task.getOperations());

}

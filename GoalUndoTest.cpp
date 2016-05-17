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

  // Asserting if 2 operations are present
  ASSERT_EQ("myOperation myOperation", task.getOperations());
}

TEST(GoalUndoTest, RemovingOperationsInRandomOrder)
{
  GoalUndo task;
  task.addOperation("gFirst", "oFirst");
  task.addOperation("oSecond");
  task.addOperation("oThird");
  task.addOperation("oFourth");
  task.addOperation("oFirst"); // Duplicate operation
  task.addOperation("oFifth");

	ASSERT_EQ("oFirst oSecond oThird oFourth oFirst oFifth", task.getOperations());

  task.undoOperation("oThird");
  ASSERT_EQ("oFirst oSecond oFourth oFirst oFifth", task.getOperations());

  // Removing duplicate 'oFirst' operation
  task.undoOperation("oFirst");
  ASSERT_EQ("oFirst oSecond oFourth oFifth", task.getOperations());

  // Removing non existing operation
  task.undoOperation("oSixth");
  ASSERT_EQ("oFirst oSecond oFourth oFifth", task.getOperations());

  task.undoOperation("oFourth");
  task.undoOperation("oFirst");
  task.undoOperation("oFifth");
  ASSERT_EQ("oSecond", task.getOperations());

  task.undoOperation("oSecond");
  ASSERT_EQ("", task.getOperations());
}

TEST(GoalUndoTest, DefaultUndoOperationBehavior)
{
  int i;
  GoalUndo task;
  task.addOperation("myGoal", "myOperation");
  // Adding 9 more operations in single goal (total = 10)
  for(i=0; i<9; i++){
    task.addOperation("myOperation");
  }

  // Removing 19 operations (remaining = 2)
  for(i=0; i<10; i++){
    task.undoOperation();
  }

	ASSERT_EQ("", task.getGoal());
}

TEST(GoalUndoTest, OverloadedUndoOperationBehavior)
{
  GoalUndo task;
  task.addOperation("gFirst", "oFirst");
  task.addOperation("oSecond");

  task.undoOperation("oFirst");
  task.undoOperation("oSecond");

	ASSERT_EQ("", task.getGoal());
}

TEST(GoalUndoTest, NoGoalIsAddedIfNameProvidedIsEmpty)
{
  GoalUndo task;
  task.addOperation("", "");
  task.addOperation("");

	ASSERT_EQ("", task.getGoal());
}

TEST(GoalUndoTest, NoOperationIsAddedIfNameProvidedIsEmpty)
{
  GoalUndo task;
  task.addOperation("", "");
  task.addOperation("");

	ASSERT_EQ("", task.getOperations());
}

TEST(GoalUndoTest, GoalIsNotAddedIfOperationNameIsEmpty)
{
  GoalUndo task;
  task.addOperation("Hello", "");

	ASSERT_EQ("", task.getGoal());
}

TEST(GoalUndoTest, RemovingGoalRemovesAllOperationsRelatedToIt)
{
  GoalUndo task;
  task.addOperation("Dogs", "Husky");
  task.addOperation("German Shepherd");
  task.addOperation("Bulldog");
  task.addOperation("Labrador");

  task.addOperation("Fruits", "Apple");
  task.addOperation("Mango");
  task.addOperation("Grapes");
  task.addOperation("Strawberry");

  task.addOperation("Cats", "Lynx");
  task.addOperation("Leopard");
  task.addOperation("Tiger");
  task.addOperation("Lion");
  task.addOperation("Cheetah");

  ASSERT_EQ("Cats", task.getGoal());
	ASSERT_EQ("Lynx Leopard Tiger Lion Cheetah", task.getOperations());

  task.undoGoal();
  ASSERT_EQ("Fruits", task.getGoal());
	ASSERT_EQ("Apple Mango Grapes Strawberry", task.getOperations());

  task.undoGoal();
  ASSERT_EQ("Dogs", task.getGoal());
	ASSERT_EQ("Husky German Shepherd Bulldog Labrador", task.getOperations());

  task.undoGoal();
  ASSERT_EQ("", task.getGoal());
	ASSERT_EQ("", task.getOperations());

  task.undoGoal();  // Doing multiple undo on empty list
  task.undoGoal();
  task.undoGoal();
  task.undoGoal();
  ASSERT_EQ("", task.getGoal());
	ASSERT_EQ("", task.getOperations());

}

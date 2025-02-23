#include "super_stack.h"
#include <gtest.h>

TEST(super_stack, can_create_copy_stack)
{
  super_stack<int> first;
  first.push(37);
  super_stack<int> second(first);
  EXPECT_EQ(first, second);
  //ASSERT_NO_THROW();
  //EXPECT_EQ();
  //EXPECT_NE();
  //ASSERT_ANY_THROW();

}

TEST(super_stack, check_empty)
{
  super_stack<int> first;
  EXPECT_EQ(first.empty(), 1);
}


TEST(super_stack, can_get_size)
{
  super_stack<int> first;
  for(size_t i = 0; i < 10; i++)
  {
    first.push(i);
  }
  EXPECT_EQ(first.size(), 10);
}

TEST(super_stack, can_push)
{
  super_stack<int> first;
  first.push(37);
  EXPECT_EQ(first.Top(), 37);
}

TEST(super_stack, throw_stack_pop_empty)
{
  super_stack<int> first;
  ASSERT_ANY_THROW(first.pop());
}
TEST(super_stack, can_stack_pop)
{
  super_stack<int> first;
  first.push(84);
  first.push(37);
  first.pop();
  EXPECT_EQ(first.Top(), 84);
}

TEST(super_stack, can_Top)
{
  super_stack<int> first;
  first.push(174);
  EXPECT_EQ(first.Top(), 174);
}

TEST(super_stack, throw_Top_empty)
{
  super_stack<int> first;
  ASSERT_ANY_THROW(first.Top());
}

TEST(super_stack, can_clear)
{
  super_stack<int> first;
  super_stack<int> second;
  first.push(1);
  first.push(2);
  first.push(3);
  first.push(4);
  first.clear();
  EXPECT_EQ(first, second);
}

TEST(super_stack, can_assign)
{
  super_stack<int> first;
  first.push(1);
  first.push(2);
  first.pop();
  super_stack<int> second = first;
  EXPECT_EQ(first, second);
}

TEST(super_stack, compare_diff_size)
{
  super_stack<int> first;
  super_stack<int> second;
  first.push(3);
  EXPECT_NE(first, second);
}

TEST(super_stack, compare_eq_size)
{
  super_stack<int> first;
  super_stack<int> second;
  first.push(3);
  second.push(3);
  EXPECT_EQ(first, second);
}

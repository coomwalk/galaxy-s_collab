// тесты для вычисления арифметических выражений
#include <gtest.h>
#include "arithmetic.h"


TEST(arithmetic, cant_create_object_arithmetic_with_string)
{
  string zibrail2 = "(34+17))/44";
  arithmetic zxc(zibrail2);
  EXPECT_EQ(zxc.input_string_out(), "(34+17))/44");
}







TEST(arithmetic, can_parsing)
{
  string zibrail2 = "(34+17)/44";

  arithmetic zxc(zibrail2);
  for_check zxc1;
  vector <lexema> k{
    lexema(4, "("), lexema(2, "34"), lexema(3,"+"), lexema(2,"17"), lexema(4,")"), lexema(3,"/"), lexema(2,"44")
  };
  EXPECT_EQ(zxc1.check_parser(zxc, k), 1);
}







TEST(arithmetic, cant_str_start_with_operation)
{
  string zibrail2 = "*(34+17)/44";
  arithmetic zxc(zibrail2);

  for_check zxc1;
  ASSERT_ANY_THROW(zxc1.check_check(zxc));
}

TEST(arithmetic, cant_skobki_close_more_open)
{
  string zibrail2 = "(34+17))/44";
  arithmetic zxc(zibrail2);
  for_check zxc1;
  ASSERT_ANY_THROW(zxc1.check_check(zxc));
}

TEST(arithmetic, cant_skobki_open_more_close)
{
  string zibrail2 = "((34+17)/44";
  arithmetic zxc(zibrail2);
  for_check zxc1;
  ASSERT_ANY_THROW(zxc1.check_check(zxc));
}

TEST(arithmetic, cant_operands_close1)
{
  string zibrail2 = "(34+17a)/44";
  arithmetic zxc(zibrail2);
  for_check zxc1;
  ASSERT_ANY_THROW(zxc1.check_check(zxc));
}

TEST(arithmetic, cant_operands_close2)
{
  string zibrail2 = "(a34+17)/44";
  arithmetic zxc(zibrail2);
  for_check zxc1;
  ASSERT_ANY_THROW(zxc1.check_check(zxc));
}

TEST(arithmetic, cant_operation_close)
{
  string zibrail2 = "(34+*17)/44";
  arithmetic zxc(zibrail2);
  for_check zxc1;
  ASSERT_ANY_THROW(zxc1.check_check(zxc));
}
 
TEST(arithmetic, cant_skobki_error)
{
  string zibrail2 = "((34+17)/44))";
  arithmetic zxc(zibrail2);
  for_check zxc1;
  ASSERT_ANY_THROW(zxc1.check_check(zxc));
}








TEST(arithmetic, correct_postfix1 )
{
  string zibrail2 = "(34+17)/44";
  arithmetic zxc(zibrail2);
  for_check zxc1;
  EXPECT_EQ(1, zxc1.check_postfix(zxc, "34 17 + 44 /"));
}

TEST(arithmetic, correct_postfix2)
{
  string zibrail2 = "(a + b) * (c + d)";
  arithmetic zxc(zibrail2);
  for_check zxc1;
  EXPECT_EQ(1, zxc1.check_postfix(zxc, "a b + c d + *"));
}

TEST(arithmetic, correct_postfix3)
{
  string zibrail2 = "52*3-140/17*(13-25/13)+2";
  arithmetic zxc(zibrail2);
  for_check zxc1;
  EXPECT_EQ(1, zxc1.check_postfix(zxc, "52 3 * 140 17 / 13 25 13 / - * - 2 +"));
}

TEST(arithmetic, correct_calculate1 )
{
  string zibrail2 = "(34+16)/5+3";
  arithmetic zxc(zibrail2);
  for_check zxc1;
  EXPECT_EQ(1, zxc1.check_calculate(zxc,13.0));
}

TEST(arithmetic, correct_calculate2 )
{
  string zibrail2 = "(40+38)/2";
  arithmetic zxc(zibrail2);
  for_check zxc1;
  EXPECT_EQ(1, zxc1.check_calculate(zxc,39.0));
}

TEST(arithmetic, correct_calculate3 )
{
  string zibrail2 = "(43+17)*5-23+(1-1)";
  arithmetic zxc(zibrail2);
  for_check zxc1;
  EXPECT_EQ(1, zxc1.check_calculate(zxc,277.0));
}




///////////////////////

#include "matrix.h"
#include "gtest/gtest.h"

TEST( matrix_test, Does_Init) {
  Matrix* test = new Matrix(3);

  test->fastPushValue(5);
  test->fastPushValue(6);
  test->fastPushValue(7);
  test->fastPushValue(2);
  test->fastPushValue(3);
  test->fastPushValue(1);

  ASSERT_TRUE(test->matrixIsValid());

  EXPECT_EQ(1, test->getValue(2, 1));

}

TEST( matrix_test, properGetterSetter) {
  Matrix* test = new Matrix(3);

  test->fastPushValue(5);
  test->fastPushValue(6);
  test->fastPushValue(7);
  test->fastPushValue(2);
  test->fastPushValue(3);
  test->fastPushValue(1);

  EXPECT_EQ(5, test->getValue(0,0));
  EXPECT_EQ(6, test->getValue(1,0));
  EXPECT_EQ(7, test->getValue(2,0));


  EXPECT_EQ(2, test->getValue(0,1));
  EXPECT_EQ(3, test->getValue(1,1));
  EXPECT_EQ(1, test->getValue(2,1));
}

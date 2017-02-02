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

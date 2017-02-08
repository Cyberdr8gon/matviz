
#include "renderMethods.h"
#include "matrix.h"
#include "gtest/gtest.h"

TEST ( render_test, Returns_correct_bmp ) {
  Matrix* test = new Matrix(3);

  test->fastPushValue(0);
  test->fastPushValue(1);
  test->fastPushValue(0);
  test->fastPushValue(1);
  test->fastPushValue(0);
  test->fastPushValue(1);


  auto testBitmap = greyscaleSpyPlot(test, 6, 4);

  std::vector<rgbColorValue> resultsCorrect;

  resultsCorrect.push_back(rgbColorValue(0xFF,0xFF,0xFF));
  resultsCorrect.push_back(rgbColorValue(0,0,0));
  resultsCorrect.push_back(rgbColorValue(0xFF,0xFF,0xFF));
  resultsCorrect.push_back(rgbColorValue(0,0,0));
  resultsCorrect.push_back(rgbColorValue(0xFF,0xFF,0xFF));
  resultsCorrect.push_back(rgbColorValue(0,0,0));

  resultsCorrect.push_back(rgbColorValue(0xFF,0xFF,0xFF));
  resultsCorrect.push_back(rgbColorValue(0,0,0));
  resultsCorrect.push_back(rgbColorValue(0xFF,0xFF,0xFF));
  resultsCorrect.push_back(rgbColorValue(0,0,0));
  resultsCorrect.push_back(rgbColorValue(0xFF,0xFF,0xFF));
  resultsCorrect.push_back(rgbColorValue(0,0,0));

  for (int i = 0; i < testBitmap->size(); i++) {
    EXPECT_EQ(resultsCorrect[i].red, (*testBitmap)[i].red);
    EXPECT_EQ(resultsCorrect[i].green, (*testBitmap)[i].green);
    EXPECT_EQ(resultsCorrect[i].blue, (*testBitmap)[i].blue);
  }

}

#include <vector>
#include <memory>
#include <cmath>
#include <limits>

#include "matrix.h"
#include "bmp.h"


inline bool logicallyEqual(double a, double b, double errorFactor=0.1) {
  return a==b || 
    (std::abs(a-b)<std::abs(std::min(a,b)) * std::numeric_limits<double>::epsilon() * errorFactor);
}



// assumes matrix has already been validated
std::shared_ptr<std::vector<rgbColorValue>> 
greyscaleSpyPlot(
    const Matrix* matrixToParse, 
    long imageWidth, 
    long imageHeight )
{
  long matrixColumns = matrixToParse->getNumberOfColumns();
  long matrixRows = matrixToParse->getNumberOfRows();

  double xAxisRatio = double(matrixColumns) / double(imageWidth);
  double yAxisRatio = double(matrixRows) /  double(imageHeight);

  auto bitmapContainer = std::make_shared<std::vector<rgbColorValue>>();

  for(long i = 0; i < imageHeight; i++) {
    for (long j = 0; j < imageWidth; j++) {
      if (logicallyEqual(matrixToParse->getValue(double(j) * xAxisRatio, 
                                                 double(i) * yAxisRatio), 0)) {
        bitmapContainer->push_back(rgbColorValue(0,0,0));
      } else {
        bitmapContainer->push_back(rgbColorValue(0xFF,0xFF,0xFF));
      }
    }
  }

  return bitmapContainer;

}

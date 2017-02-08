#pragma once
#include <vector>
#include <memory>
#include <cmath>
#include <limits>

#include "matrix.h"
#include "bmp.h"



// assumes matrix has already been validated
std::shared_ptr<std::vector<rgbColorValue>> 
greyscaleSpyPlot( const Matrix* matrixToParse, long imageWidth, long imageHeight );

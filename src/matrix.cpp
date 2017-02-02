/*
 * Matrix.cpp
 * Author: Sam Bateman
 *
 * Defines class methods for matrix class
 * Further details can be found in matrix.h
 *
 */
#include "matrix.h"
#include <iostream>

Matrix::Matrix(unsigned int columns) {
  numberOfColumns = columns;
}

double Matrix::getValue(unsigned int column, unsigned int row) {
  return matrixData[numberOfColumns * row + column];
}


bool Matrix::validCoordinates(unsigned int column, unsigned int row) {
  return (numberOfColumns * row + column) <= (matrixData.size()) && (column < numberOfColumns);
}

void Matrix::fastPushValue(double value) {
  matrixData.push_back(value);
}

bool Matrix::setValue(unsigned int column, unsigned int row, double value) {
  if(validCoordinates(column, row)) {
    matrixData[numberOfColumns * row + column] = value;
    return true;
  }
  return false;
}


void Matrix::printMatrix() {
  std::cout << "Debug matrix print:" << std::endl;
  for(int j = 0; j < matrixData.size() / numberOfColumns; j++ ) {
    for(int i = 0; i < numberOfColumns; i++) {
      // loop through and print matrix
      std::cout << getValue(i, j) << ", " ;

    }
    std::cout << std::endl;
  }

  std::cout << "Matrix is Valid: " << matrixIsValid() << std::endl;
}


bool Matrix::matrixIsValid() {
  return !(matrixData.size() % numberOfColumns);
}

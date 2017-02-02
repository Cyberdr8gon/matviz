#pragma once
/*
 *
 * Matrix.h
 * Author: Sam Bateman
 * Version 1.0 - Passing
 * 
 *
 * Defines the matrix class and it's api. 
 * The api always references columns/rows as 0 based
 *
 */


#include <vector>

// this will likely need to be fleshed out in the future
/*
 * This is currently just a container to hold the parsed data
 * TODO: provide more advanced functionality as program grows in complexity
 * NOTE - matrix value sets are 0 based
 *
 * 
 * 
 */

class Matrix {
  public:
    // call this and then init with many fastPushValue
    // TODO overload this to simplify loading from args, pipes and files
    Matrix(unsigned int columns);

    double getValue(unsigned int column, unsigned int row);

    // returns true if successful
    bool setValue(unsigned int column, unsigned int row, double value);

    void fastPushValue(double value);

    void printMatrix(); 

    // checks if the data is rectangular/square
    // and therefor valid for matrix operations
    // if it is, returns true
    bool matrixIsValid();
  private:
    // returns true if coordinates are valid
    bool validCoordinates(unsigned int column, unsigned int row);
    unsigned int numberOfColumns;

    // this is a 1d array being used to represent a matrix
    // TODO replace this with binary tree to increase speed of non-end insertion
    std::vector<double> matrixData;
};

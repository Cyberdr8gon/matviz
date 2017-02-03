#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <memory>


#include "matrix.h"

Matrix* fileLoader(char* filename) {

  std::ifstream fileHandle(filename);
  std::string line;
  
  if( !fileHandle ) {
    std::cout << "Error opening file:" << std::endl;
    std::cout << "Either filename is invalid or you have insufficient permissions" << std::endl;
    fileHandle.close();
    std::exit(1);
  }

  std::getline(fileHandle, line);
  unsigned int width = std::stoi(line);

  Matrix* newMatrix = new Matrix(width);

  while (std::getline(fileHandle, line)) {
    std::stringstream lineStream(line);
    std::string cell;
    while(std::getline(lineStream,cell,',')) {
      newMatrix->fastPushValue(std::stoi(cell));
    }
  }

  return newMatrix;

}


int main( int argc, char* argv[] ) {
  if(argc <= 1) {
    if (argv[0]) {
      std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
    } else {
      std::cout << "Usage: <program name> <filename>" << std::endl;
    }

    std::exit(1);
  }

  Matrix* matrix = fileLoader(argv[1]);
  if(!matrix->matrixIsValid()){
    std::cout << "Error: Invalid matrix file" << std::endl;
    std::cout << "Please ensure the matrix is properly formatted." << std::endl;
    if( argv[0] ) {
      std::cout << "More info: " << argv[0] << " --format" << std::endl;
    } else {
      std::cout << "More info: <program name> --format" << std::endl;
    }
    exit(1);
  }


  return 0;
}

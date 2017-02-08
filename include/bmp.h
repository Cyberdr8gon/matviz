#pragma once
#include <vector>
#include <memory>


struct rgbColorValue{
  unsigned char red = 0;
  unsigned char green = 0;
  unsigned char blue = 0;
  rgbColorValue(unsigned char red, unsigned char green, unsigned char blue);
};

// class assumes bitmap passed in is top to bottom, with index 0 of vector
// representing the top left corner of the image, drawn from left to right
class bmp {
  public:
    bmp(std::shared_ptr<std::vector<rgbColorValue>> imageVector, long width, long height);

    void writeToFile(char* filename);

  private:
    void encodeBitmap();

    void writeHeader();

    std::shared_ptr<std::vector<rgbColorValue>> bitmapToWrite;

    // may have to use char* pointer and malloc
    std::vector<char> dataToWrite;

    unsigned long filesize = 0;

    long outputWidth;
    long outputHeight;

  
};

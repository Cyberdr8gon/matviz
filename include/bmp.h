#include <vector>
#include <memory>


struct rgbColorValue{
  unsigned char red = 0;
  unsigned char green = 0;
  unsigned char blue = 0;
  rgbColorValue(char red, char green, char blue);
}

class bmp {
  public:
    bmp(const std::shared_ptr<std::vector<rgbColorValue>> &imageVector, long width, long height);

    bool writeToFile(char* filename);

  private:
    void encodeBitmap();

    void writeHeader();

    std::shared_ptr<std::vector<rgbColorValue>> bitmapToWrite(nullptr);

    // may have to use char* pointer and malloc
    std::vector<char> dataToWrite;

    unsigned long filesize = 0;

    std::ofstream file_output;

    long outputWidth;
    long outputHeight;

  
}

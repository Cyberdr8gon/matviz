#include <fstream>
#include <iostream>
#include <cstdlib>
#include <memory>
#include "bmp.h"

rgbColorValue::rgbColorValue(unsigned char red, unsigned char green, unsigned char blue)
  : red(red), green(green), blue(blue) 
{ }


bmp::bmp(std::shared_ptr<std::vector<rgbColorValue>>  imageVector, long width, long height) 
  : outputWidth(width), outputHeight(height), bitmapToWrite(imageVector), dataToWrite()
{
  encodeBitmap();
}


// imageHeight is encoded as negitive to allow
// top to bottom writing to file
void bmp::encodeBitmap() {
  writeHeader();

  // if sizeOfRow is not multiple of 4
  // it must be modified to be divisable by 4 with padding bytes
  // NOTE this means sizeOfRow and outputWidth are different and
  // should be used to know when to start writing null bytes
  //

  int padding = ( 4 - ( ( outputWidth * 3  ) % 4  )  ) % 4;

  int scanLineRow = outputWidth + padding;

  filesize = scanLineRow * outputHeight * long(3) + long(54);

  dataToWrite[2] = char(filesize);
  dataToWrite[3] = char(filesize >> 8);
  dataToWrite[4] = char(filesize >> 16);
  dataToWrite[5] = char(filesize >> 24);

  for(long i = 0; i < outputHeight; i++) {
    for(long j = 0; j < scanLineRow; j++) {
      if(j >= outputWidth) {
        dataToWrite.push_back(char(0));
      } else {
        dataToWrite.push_back((*bitmapToWrite)[outputWidth * i + j].blue);
        dataToWrite.push_back((*bitmapToWrite)[outputWidth * i + j].green);
        dataToWrite.push_back((*bitmapToWrite)[outputWidth * i + j].red);
      }
    }
  }


}

void bmp::writeHeader() {
  /*
   * FILE HEADER
   */

  // bitmap filetype "BM" first 2 bytes
  // bfType
  dataToWrite.push_back('B');
  dataToWrite.push_back('M');

  // write filesize little endian - 4 bytes
  // note that we must write this backwards from lowest to highest
  // bits because of how a little endian system will read the file
  // bytes 4
  // bfSize
  
  // do this at end
  
//  dataToWrite.push_back(char(filesize));
//  dataToWrite.push_back(char(filesize)  >> 4);
//  dataToWrite.push_back(char(filesize)  >> 8);
//  dataToWrite.push_back(char(filesize)  >> 12);
    dataToWrite.push_back(char(0));
    dataToWrite.push_back(char(0)); 
    dataToWrite.push_back(char(0));
    dataToWrite.push_back(char(0));


  // reserved 4 bytes, size 0
  // bytes 4
  // brReserved1 and brReserved2
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));

  // offset of pixel data from start of file
  // should be roughly 54 but we should 
  // check another bitmap to make sure
  // bytes 4
  // bfOffBits
  dataToWrite.push_back(0x36);
  dataToWrite.push_back(0);
  dataToWrite.push_back(0);
  dataToWrite.push_back(0);

  /*
   * IMAGE HEADER
   */

  // size in bytes of image header
  // 4 bytes
  // almost always 40 aka 0x28
  // biSize
  

  dataToWrite.push_back(0x28);
  dataToWrite.push_back(0);
  dataToWrite.push_back(0);
  dataToWrite.push_back(0);

  // these bytes here are being miswritten

  // width of image in pixels
  // 4 bytes
  // biWidth
  
  dataToWrite.push_back((unsigned char) outputWidth);
  dataToWrite.push_back((unsigned char)(outputWidth >> 8));
  dataToWrite.push_back((unsigned char)(outputWidth >> 16));
  dataToWrite.push_back((unsigned char)(outputWidth >> 24));

  // height of image in pixels
  // given in negitive to have it read from bottom to top
  // 4 bytes
  // biHeight
   
  dataToWrite.push_back((unsigned char)(-outputHeight));
  dataToWrite.push_back((unsigned char)(-outputHeight >> 8));
  dataToWrite.push_back((unsigned char)(-outputHeight >> 16));
  dataToWrite.push_back((unsigned char)(-outputHeight >> 24));


  // number of image planes in image
  // obviously, its a bitmap and is always 1
  // 2 bytes
  // biPlanes
  
  dataToWrite.push_back(char(1));
  dataToWrite.push_back(char(0));

  // number of bits per pixel
  // for us it will be 24
  // 2 bytes
  // biBitCount
  
  dataToWrite.push_back(char(0x18));
  dataToWrite.push_back(char(0));

  // type of compression
  // no compression = 0
  // 4 bytes
  // biCompression
  
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));
  

  // size of image
  // because uncompressed, there is no point
  // in settings this as it will be calculated
  // with previously shared information
  // 4 bytes
  // biSizeImage
  
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));

  // recommended X bits per meter
  // doesn't really matter for our purposes
  // bytes 4
  // biXPelsPerMeter

  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));
 
  // recommended Y bits per meter
  // doesn't really matter for our purposes
  // bytes 4
  // biXPelsPerMeter

  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));
  
  // number of color map entries actually used 
  // 4 bytes
  // biClrUsed
  
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));

  // number of colors considered important in
  // image
  // 4 bytes
  // biClrImportant
  
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));
  dataToWrite.push_back(char(0));


}

void bmp::writeToFile(char* filename) {
  std::fstream fileStream(filename, std::ios::out | std::ios::binary | std::ios::trunc);
  if(!fileStream) {
    std::cout << "Error:" << std::endl;
    std::cout << "Could not open " << filename << " for writing." << std::endl;
    std::exit(126);
  }

  //std::copy(dataToWrite.begin(), dataToWrite.end(), std::ostreambuf_iterator<char>(fileStream));
  for(long i = 0; i < dataToWrite.size(); i++) {
    fileStream << dataToWrite[i];
  }

  fileStream.close();

}

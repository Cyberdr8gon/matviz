#include "bmp.h"



bmp::bmp(const std::shared_ptr<std::vector<rgbColorValue>> &imageVector, long width, long height) {
  bitmapToWrite(imageVector);
  outputHeight = height;
  ouputWidth = width;
  encodeBitmap();
}


void bmp::encodeBitmap() {
  filesize = outputWidth * outputHeight * long(3) + long(54) + outputHeight;
  dataToWrite(filesize);
  writeHeader();
  // TODO continue
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
  // bfSize
  
  unsigned char temp = char(filesize);
  dataToWrite.push_back(temp);
  temp = char(filesize  >> 4);
  dataToWrite.push_back(temp);
  temp = char(filesize  >> 8);
  dataToWrite.push_back(temp);
  temp = char(filesize  >> 12);
  dataToWrite.push_back(temp);


  // reserved 4 bytes, size 0
  // brReserved1 and brReserved2
  temp = 0;
  dataToWrite.push_back(temp);
  dataToWrite.push_back(temp);
  dataToWrite.push_back(temp);
  dataToWrite.push_back(temp);

  // offset of pixel data from start of file
  // should be roughly 54 but we should 
  // check another bitmap to make sure
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


  // width of image in pixels
  // 4 bytes
  // biWidth
  
  dataToWrite.push_back(char(outputWidth));
  dataToWrite.push_back(char(outputWidth >> 4));
  dataToWrite.push_back(char(outputWidth >> 8));
  dataToWrite.push_back(char(outputWidth >> 12));

  // height of image in pixels
  // 4 bytes
  // biHeight
   
  dataToWrite.push_back(char(outputHeight));
  dataToWrite.push_back(char(outputHeight >> 4));
  dataToWrite.push_back(char(outputHeight >> 8));
  dataToWrite.push_back(char(outputHeight >> 12));


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

  // TODO start here
}


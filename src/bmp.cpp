#include "bmp.h"

rgbColorValue::rgbColorValue(char red, char green, char blue) : red(red), green(green), blue(blue) {
  
}


bmp::bmp(std::vector<rgbColorValue> &imageVector, long width, long height) {
  bitmapToWrite = imageVector;
  outputHeight = height;
  outputWidth = width;
  encodeBitmap();
}


// imageHeight is encoded as negitive to allow
// top to bottom writing to file
void bmp::encodeBitmap() {
  filesize = outputWidth * outputHeight * long(3) + long(54) + outputHeight;
  writeHeader();

  int sizeOfRow = outputWidth;
  // if sizeOfRow is not multiple of 4
  // it must be modified to be divisable by 4 with padding bytes
  // NOTE this means sizeOfRow and outputWidth are different and
  // should be used to know when to start writing null bytes
  while (!(sizeOfRow % 4) ) {
    sizeOfRow++;
  }

  long sizeOfArray = long(bitmapToWrite.size());

  for(long i = 0; i < outputHeight; i++) {
    for(long j = 0; j < sizeOfRow; j++) {
      if(j >= outputWidth) {
        dataToWrite.push_back(char(0));
      } else {
        dataToWrite.push_back(bitmapToWrite[outputWidth * i + j].red);
        dataToWrite.push_back(bitmapToWrite[outputWidth * i + j].green);
        dataToWrite.push_back(bitmapToWrite[outputWidth * i + j].blue);
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
  
  dataToWrite.push_back(char(filesize));
  dataToWrite.push_back(char(filesize)  >> 4);
  dataToWrite.push_back(char(filesize)  >> 8);
  dataToWrite.push_back(char(filesize)  >> 12);


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


  // width of image in pixels
  // 4 bytes
  // biWidth
  
  dataToWrite.push_back(char(outputWidth));
  dataToWrite.push_back(char(outputWidth >> 4));
  dataToWrite.push_back(char(outputWidth >> 8));
  dataToWrite.push_back(char(outputWidth >> 12));

  // height of image in pixels
  // given in negitive to have it read from bottom to top
  // 4 bytes
  // biHeight
   
  dataToWrite.push_back(char(-outputHeight));
  dataToWrite.push_back(char(-outputHeight >> 4));
  dataToWrite.push_back(char(-outputHeight >> 8));
  dataToWrite.push_back(char(-outputHeight >> 12));


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

bool bmp::writeToFile(char* filename) {
  // TODO start here
}

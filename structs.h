#include "macros.h"
typedef struct{
  unsigned short *magic_Number;
  char magicNumber[2];
  char* commentLine;
  unsigned int width,height,maxGray;
  unsigned char* imageData;
  int *imageDataBin;
}Image;

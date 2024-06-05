#include <stdio.h>
#include <stdlib.h>
#include "initImage.h"

void initImage(Image *image){
  image->magic_Number= NULL;
  image->commentLine = NULL;
  image->imageData = NULL;
  image->imageDataBin = NULL;
  image->height = 0;
  image->width=0;
  image->maxGray=255;
}

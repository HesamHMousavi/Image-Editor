#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "structs.h"
#include "initImage.c"
#include "pgmWrite.c"
#include "pgmRead.c"
int roundNumber(float num);
int ReduceImage(Image *image, int factor);
int main(int argc, char **argv)
{
  if(argc == 1){
    //output error message
    printf("Usage: %s inputImage.pgm reduction_factor outputImage.pgm\n", argv[0]);
    //exit the program 
    return EXIT_ZERO_ARG;
  }
  else if(argc < 4 || argc > 4){
    //output error message
    printf("ERROR: Bad Argument Count");
    //exit the program 
    return EXIT_WRONG_ARG_COUNT;
  }
  int factor = atoi(argv[2]);
  if(factor <= 0){ 
    printf("ERROR: Miscellaneous (Bad Sacling Factor)");
    return 100;
  }
  //initlize an image struct to store the image in
  Image img,*image=&img;
  initImage(image); 
  int readRes = 0, writeResult = 0, redRes = 0;
  readRes = readFile(argv[1], image);
  //check if read proccess failes
  if(readRes != 0){
    return readRes;
  }
  //check if reduce proccess failes
  redRes = ReduceImage(image , factor);
  if(redRes != 0){
    return redRes;
  }
  //check if write proccess failes
  writeResult = writeFile(argv[3],image);
  if(writeResult != 0){
    return writeResult;
  }
  printf("REDUCED\n");
  //return correct error code
  return EXIT_NO_ERRORS;
}
int ReduceImage(Image *image, int factor){
  //declare a 2d array to store the gray values read from the input file
  //calculate and store the reduced width and height
  int widthRed = roundNumber(image->width/(double)factor);
  int heightRed = roundNumber(image->height/(double)factor);
  //declare a 2d array to store the reduced values
  int* imgArrRed = (int *) malloc(widthRed * heightRed * sizeof(int));
  if(imgArrRed == NULL){
    //check if the memory allocation failed
    printf("ERROR: Image Malloc Failed");
    free(imgArrRed);
    return 7;
  } 
  int counter = 0, redCounter = 0;
  for (int i=0; i<image->width; i++){
    for (int j=0; j<image->height; j++){
      //check if the width and heigt are diviable by the given factor
      if((i % factor == 0) && (j % factor == 0)){
        //store that value in the imgArrRed array
        imgArrRed[redCounter] = image->imageData[counter];
        redCounter++;
      }
      counter++;
    }
  }
  //assign reduce dimensions
  image->width = widthRed;
  image->height = heightRed;
  //allocate space based on the reduced size
  image->imageData = (unsigned char *)malloc(image->width * image->height * sizeof(unsigned char));
  if(image->imageData == NULL){
    //check if the memory allocation failed
    printf("ERROR: Image Malloc Failed");
    free(image->imageData);
    return 7;
  } 
  int counter2 = 0;
  for (int i=0; i<image->width; i++){
    for (int j=0; j<image->height; j++){
      //assign the reduced values to the image array 
      image->imageData[counter2] = imgArrRed[counter2];
      counter2++;
    }
  }
  return 0;
}
int roundNumber(float value)
{
  return value < 0 ? value - 0.5 : value + 0.5;
}

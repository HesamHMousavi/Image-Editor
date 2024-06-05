#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "structs.h"
#include "initImage.c"
#include "pgmRead.c"

//This function is used to compares two pgm images
int convertb2a(long long n);
void convert (Image *imagePtr);
int main(int argc , char **argv){
  if(argc == 1){
    //output error message
    printf("Usage: ./pgmComp inputImage.pgm inputImage.pgm");
    return EXIT_ZERO_ARG;
  }
  else if(argc < 3 || argc > 3){
    //output error message
    printf("ERROR: Bad Argument Count");
    return EXIT_WRONG_ARG_COUNT;
  }
  
  //create 2 image structs to store 
  Image image1, *imagePtr1 = &image1;
  Image image2, *imagePtr2 = &image2;
  //variables to store the magic
  //initImage to initilize the image properties
  int readResult1 = 0, readResult2 = 0;
  initImage(imagePtr1);
  initImage(imagePtr2);
  //readFile to read the pgm and store 
  readResult1 = readFile(argv[1], imagePtr1);
  if(readResult1 != 0){
    //checkd if the first read process is successful
    return readResult1;
  }
  readResult2 = readFile(argv[2],imagePtr2);
  if(readResult2 != 0){
    //checks if the second read process is successful
    return readResult2;
  }
  //assign the magic number to variale image magic number 
  if(imagePtr1->height != imagePtr2->height || imagePtr1->width != imagePtr2->width || imagePtr1->maxGray != imagePtr2->maxGray){
    printf("DIFFERENT\n");
    return EXIT_NO_ERRORS;
  }
  //compare both images' gray values
  for(int i = 0;i < imagePtr1->width * imagePtr1->height;i++){
    if((int)imagePtr1->imageData[i] != (int)imagePtr2->imageData[i]){
      //return if there is a mismtach
      printf("DIFFERENT\n");
      return EXIT_NO_ERRORS;
    }
  }
  //if all comparisons return true? the print message
  printf("IDENTICAL\n");
  return EXIT_NO_ERRORS;
}

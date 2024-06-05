#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "structs.h"
#include "initImage.c"
#include "pgmRead.c"
#include "pgmWrite.c"

int main(int argc , char **argv){
  //checks if no arguments are given
  if(argc == 1){
    //output error message
    printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
    return EXIT_ZERO_ARG;
  }
  else if(argc < 3 || argc > 3){
    //checks the number of argumnets
    printf("ERROR: Bad Argument Count");
    return EXIT_WRONG_ARG_COUNT;
  }

  //create an image pointer and a struct
  //point the pointer to the image struct
  Image image,*imagePtr = &image;
  //call initImage to initialize the image values
  initImage(imagePtr);
  //read in the pgm file and store it in the image struct
  int resultRead = 0; int resultWrite = 0;
  //check if the read process is successfull
  resultRead = readFile(argv[1],imagePtr);
  if(resultRead != 0){
    return resultRead;
  } 
  //check if the write process is successfull
  resultWrite = writeFile(argv[2],imagePtr);
  if(resultWrite != 0){
   return resultWrite;
  }
  //exit routine
  printf("ECHOED\n");
  return EXIT_NO_ERRORS;
}

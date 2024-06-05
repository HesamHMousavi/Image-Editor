#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "structs.h"
#include "initImage.c"
#include "pgmRead.c"
#include "pgmWrite.c"
//#include <unistd.h>

int main(int argc, char **argv)
{
  if(argc == 1){//check the correct number of args is supplied
    //output error message
    printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
    return EXIT_ZERO_ARG;
  } 
  if(argc < 3 || argc > 3){//check the correct number of args is supplied
    //output error message
    printf("ERROR: Bad Argument Count");
    return EXIT_WRONG_ARG_COUNT;
  }
  if(access(argv[2], F_OK) == 0){
     if(access(argv[2], W_OK) != 0){
     //check if user has write permission
     printf("ERROR: Bad File Name (%s)", argv[2]);
     //return correct error code
     return EXIT_BAD_FILE_NAME;
     }
  }
  //create an image struct to store the image in
  Image image , *imagePtr=&image;
  //initilize the image attributes
  initImage(imagePtr);
  //read the image from the file and store it in the image stuct
  int readResult = 0;
  readResult = readFile(argv[1],imagePtr);
  if(readResult != 0){
    return readResult;
  }
  //check if the file is already in ascii format
  if(imagePtr->magicNumber[1] == '2'){
    //output error message
    printf("ERROR: Bad Magic Number (%s)",argv[1]);
    return EXIT_BAD_MAGIC_NUMBER;
  }
  // convert the magic number
  //set magic number
  imagePtr->magicNumber[1]='2';
  int writeResult = 0;
  //write image to file
  writeResult = writeFile(argv[2],imagePtr);
  if(writeResult != 0){
    //check write procces if successful
    return writeResult;
  }
  printf("CONVERTED");
  return EXIT_NO_ERRORS;
}

#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "structs.h"
#include "initImage.c"
#include "pgmRead.c"
#include "pgmWrite.c"

int main(int argc , char **argv){
  if(argc == 1){//check the correct number of command line args are supplied
  //output error message if not
    printf("Usage: ./pgma2b inputImage.pgm outputImage.pgm");
    //exit with error code
    return EXIT_ZERO_ARG;
  } 
  else if(argc < 3 || argc > 3){//check the correct number of command line args ar supplied
  //output error message if not
    printf("ERROR: Bad Argument Count");
    //exit with error code
    return EXIT_WRONG_ARG_COUNT;
  }

  //declare an image pointer to store the image being read
  Image image , *imagePtr=&image;
  //initilize the image values
  initImage(imagePtr);
  //read the image and store it the in the image pointer
  int readResult = 0;
  //RAED FILE
  readResult = readFile(argv[1],imagePtr);
  //check if and error ocurred
  if(readResult != 0){
    //return the error code 
    return readResult;
  }
  //convert the magic number 
  if(imagePtr->magicNumber[1] == '5'){
    //output error message 
    printf("ERROR: Bad Magic Number (%s)",argv[1]);
    //return correct error code
    return EXIT_BAD_MAGIC_NUMBER;
  }
  imagePtr->magicNumber[1]='5';
  int writeResult = 0; 
  //check if an error code has occured
  writeResult = writeFile(argv[2],imagePtr);
  if(writeResult != 0){ 
   //return correct error code
   return writeResult;
  }
  //exit with no errors
  printf("CONVERTED");
  return EXIT_NO_ERRORS;
}

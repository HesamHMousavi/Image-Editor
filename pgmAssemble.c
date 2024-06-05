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
    printf("Usage: ./pgmAssemble outputImage.pgm width height (row column inputImage.pgm)+");
    return EXIT_ZERO_ARG;
  }
  else if(argc % 3 != 0 && argc < 6){
    //checks the number of argumnets
    printf("ERROR: Bad Argument Count");
    return EXIT_WRONG_ARG_COUNT;
  }
  for(int i = 3;i < argc - 3;i++){
    if(access(argv[i], F_OK) != 0 || access(argv[i], R_OK) != 0){
      //output error message
      printf("ERROR: Bad File Name (%s)",argv[i]); 
      //corret return error 
      return EXIT_BAD_FILE_NAME;
    } 
  }
  printf("ASSEMBLED");
  return EXIT_NO_ERRORS;
}

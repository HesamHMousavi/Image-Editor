#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macros.h"
#include "structs.h"
#include "initImage.c"
#include "pgmRead.c"
#include "pgmWrite.c"

int main(int argc , char **argv){
  //checks if no arguments are given
  if(argc == 1){
    //output error message
    printf("Usage: ./pgmTile inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm");
    return EXIT_ZERO_ARG;
  }
  else if(argc < 4 || argc > 4){
    //checks the number of argumnets
    printf("ERROR: Bad Argument Count");
    return EXIT_WRONG_ARG_COUNT;
  }
  //check output template 
  char str[100] = "_<row>_<column>.pgm";
  char *template = strstr(argv[3], str);
  if(template == NULL){
    //return correct message and error code
    printf("ERROR: Miscellaneous");
    return 100;
  }
  char newFile[100], ch1[2] , ch2[2];
  //convert factor from string to intger
  int fileCounter = 0,factor = atoi(argv[2]);
  //allocate space for files array
  char **files = malloc(factor*factor * sizeof(char*));
  if(files == NULL){//check if the memory allocation failed
    //output error message
    printf("ERROR: Image Malloc Failed");
    //return correct error code
    return 7;
  } 
  for (int i = 0; i < factor*factor; i++){
    files[i] = malloc((100) * sizeof(char));
    if(files[i] == NULL){//check if the memory allocation failed
      //output error message
      printf("ERROR: Image Malloc Failed");
      //return correct error code
      return 7;
    } 
  }
  //Generates files for subimages
  for(int i = 0; i< factor;i++){
    for(int j = 0; j < factor;j++){
      memcpy(newFile, argv[3], strlen(argv[3]) - 19);
      strcat(newFile, "_");
      sprintf(ch1, "%d", i);
      strcat(newFile, ch1);
      strcat(newFile, "_");
      sprintf(ch2, "%d", j);
      strcat(newFile, ch2);
      strcat(newFile, ".pgm");
      strcpy(files[fileCounter], newFile);
      memset(newFile,0,strlen(newFile));
      fileCounter++;
    }
  }
  Image image,*imagePtr = &image;
  //call initImage to initialize the image values
  initImage(imagePtr);
  //read in the pgm file and store it in the image struct
  int resultRead = 0; int resultWrite = 0;
  //check if the read process is successfull
  resultRead = readFile(argv[1],imagePtr);
  if(resultRead != 0){
    //check if the read process failes
    return resultRead;
  }
  //check the image dimensions are divisible by the given factor
  if((imagePtr->width % factor != 0) || (imagePtr->height % factor != 0)){
    //return error message
    printf("ERROR: Miscellaneous");
    //return error code
    return 100;
  }
  int counter = 0;
  //A 2d array to store the gray values of the image
  int *imgArr [imagePtr->height];
  for (int i = 0; i < imagePtr->height; i++){
    //use malloc to allocate space
    imgArr[i] = (int*)malloc(imagePtr->width * sizeof(int));
    //check if the memory allocation failed
    if(imgArr[i] == NULL){
      //output error message
      printf("ERROR: Image Malloc Failed");
      //return correct error code
      return 7;
    } 
  }
  for(int i = 0; i < imagePtr->height;i++){
    for(int j = 0; j < imagePtr->width;j++){
      //write image gray values into the 2d array
      imgArr[i][j] = imagePtr->imageData[counter];
      counter++;
    }
  }
  //store the actual image dimensions
  int oldWidth = imagePtr->width;
  int oldHeight = imagePtr->height;
  //calcualt the new image dimensions of subimages 
  imagePtr->width = imagePtr->width/factor;
  imagePtr->height = imagePtr->height/factor;
  //allocate space based on new image size
  imagePtr->imageData = (unsigned char *)malloc((imagePtr->width) * (imagePtr->height) * sizeof(unsigned char));
  if(imagePtr->imageData == NULL){//check if the memory allocation failed
    //output error message
    printf("ERROR: Image Malloc Failed");
    //return correct error code
    return 7;
  } 
  //variables to minpulate the image data
  int heightCounter = 0, 
  widthCounter = 0, 
  heightDefaultvalue = 0,
  widthDefaultCounter = 0,
  //counts the number of tiles
  tileCounter = 0, 
  //counts the number of data elements
  dataCounter = 0;
  for(int i = 0; i< oldWidth * oldHeight;i++){
    //assign image values to new indices
    imagePtr->imageData[dataCounter] = imgArr[heightCounter][widthCounter];
    widthCounter++;
    //check if three values are written
    if((i+1) % (oldWidth/factor) == 0){
      //increase the height pointer
      heightCounter = heightCounter+1;
      //set the width pointer to default value
      widthCounter = widthDefaultCounter;  
    }
    //check if a tile is read
    if((i+1) % ((oldHeight * oldWidth) / (factor*factor)) == 0){
      //reset the data counter
      dataCounter = -1;
      //increase the default width value
      widthDefaultCounter+= (oldWidth/factor);
      //set the width counter to default value
      widthCounter = widthDefaultCounter;  
      //set the height counter to default value
      heightCounter = heightDefaultvalue;
      //write the subimage to the corresponding file
      resultWrite = writeFile(files[tileCounter],imagePtr);  
      //check if the write process failed
      if(resultWrite != 0){
        return resultWrite;
      }
      //increase the tile counter
      tileCounter++;
      //check if the tile counter if divisible by the counter
      if(tileCounter % factor == 0){
        //if so increase the default height value
        heightDefaultvalue = heightDefaultvalue+(oldWidth/factor);
        //set the height counter to the default value
        heightCounter = heightDefaultvalue;
        //reset the default width value
        widthDefaultCounter = 0;
      }
    }
    //increase the data counter
    dataCounter++;
    //if the width counter is equal to the actual width
    if(widthCounter == oldWidth)
      //reset the width counter
      widthCounter = 0; 
  }
  //print success message
  printf("TILED");
  //return with correc exit code
  return EXIT_NO_ERRORS;
}
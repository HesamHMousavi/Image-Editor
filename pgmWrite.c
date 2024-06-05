#include "pgmWrite.h"
#include <unistd.h>

/*This routine is used to write a pgm image to a pgm file based on the given pgm stuct*/

int writeFile(char fileName[255],Image *image){
   if(access(fileName, F_OK) == 0){
     if(access(fileName, W_OK) != 0){
     //check if user has write permission
     printf("ERROR: Bad File Name (%s)", fileName);
     //return correct error code
     return EXIT_BAD_FILE_NAME;
     }
  }
  //assign a file pointer and open the file
  FILE * outputFile = fopen(fileName, "wb");
  //check if the file failed to be opened
  if(outputFile == NULL){
    //output error message
    printf("ERROR: Bad File Name (%s)", fileName);
    // clean up memory and close file
    freeMemory(outputFile , image);
    //return correct error code
    return EXIT_BAD_OUTPUT_FILE;
  }
  if(image->maxGray > MAX_GRAY_VALUE){
    //output corrcet error message
    printf("ERROR: Bad Max Gary Value (%s)",fileName);
    //clean up memory and close file
    freeMemory(outputFile , image);
    //return correct error code
    return EXIT_BAD_MAX_GRAY_VALUE;
  }
  size_t nBytesWritten;
  if(image->magicNumber[0] != 'P' && (image->magicNumber[1] == '2' || image->magicNumber[1] == '5')){
    //testing the validity of the magic numbers
    printf("ERROR: Bad Magic Number (%s)", fileName);
    //clean up memory and close file
    freeMemory(outputFile , image);
    //return correct error code
    return EXIT_BAD_MAGIC_NUMBER;
  }
  else if(image->magicNumber[1] == '2'){
    long nImageBytes = image->width * image->height * sizeof(unsigned char);
    nBytesWritten = fprintf(outputFile,"P2\n%d %d\n%d\n", image->width ,image->height ,image->maxGray);
    if(nBytesWritten < 0){//check if the content is written to the file
      //output error message
      printf("ERROR: Output Failed (%s)", fileName);
      // clean up memory and close file
      free(image->imageData);
      //return correct error code
      return EXIT_BAD_OUTPUT;
    } 
    int counter=0 ;
    for(unsigned char *nextGrayValue = image->imageData; nextGrayValue < image->imageData + nImageBytes; nextGrayValue++){
      //get the next column
      int nextCol = (nextGrayValue - image->imageData+1) % image->width;
      //if the next column is greater than 0 the print a space else move to the next line
      nBytesWritten = fprintf(outputFile ,"%d%c", image->imageData[counter], (nextCol? ' ':'\n'));
      // printf("value: %x\n",);
      if(nBytesWritten < 0){//check the file is written 
        //output error message   
        printf("ERROR: Output Failed (%s)", fileName);
        //clean up memory and close file
        free(image->imageData);
       //return correct error code
        return EXIT_BAD_OUTPUT;
      }
      counter++;
    }
  }
  else if(image->magicNumber[1] == '5'){
    long nImageBytes = image->width * image->height * sizeof(unsigned char);
    nBytesWritten = fprintf(outputFile,"P5\n%d %d\n%d\n",image->width ,image->height ,image->maxGray);  
    if(nBytesWritten < 0){//check if the content is written to the file
      //output error message
      printf("ERROR: Output Failed (%s)", fileName);
      // clean up memory and close file
      free(image->imageData);
      //return correct error code
      return EXIT_BAD_OUTPUT;
    } 
    for(unsigned char *nextGrayValue = image->imageData; nextGrayValue < (image->imageData) + nImageBytes; nextGrayValue++){
      nBytesWritten = fwrite(nextGrayValue,sizeof(*nextGrayValue), 1 ,outputFile);
      // int i = *nextGrayValue;
      if(nBytesWritten < 0){//check the file is written 
        //output error message   
        printf("ERROR: Output Failed (%s)", fileName);
        //clean up memory and close file 
        freeMemory(outputFile,image);
        //return correct error code
        return EXIT_BAD_OUTPUT;
      }
    }
  }
  fclose(outputFile);
  return EXIT_NO_ERRORS;
}

int freeMemory(FILE * outputFile, Image* image){ 
  fclose(outputFile);
  if(image->commentLine != 0){
    free(image->commentLine);
  }
  if(image->imageData){
    free(image->imageData);
  }
}

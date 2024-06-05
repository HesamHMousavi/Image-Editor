#include "pgmRead.h"
#include <unistd.h>

/*This routine is used to read in the pgm image and store it in a given Image struct*/
int conb2a(long long n);
int readFile(char fileName[255],Image *image){
  if(access(fileName, F_OK) == 0){
   if(access(fileName, R_OK) != 0){
     //output error message
     printf("ERROR: Bad File Name (%s)",fileName); 
     //corret return error 
       return EXIT_BAD_FILE_NAME;
    }
   } 
  //assign char array for magic number
  unsigned char magic_number[2] = {'0', '0'};
  //assign the magic number to the image struc magic number
  image->magic_Number = (unsigned short *) magic_number;
  //open file to read in data
  FILE *inputFile = fopen(fileName, "rb");
  //check if the file failed to open
  if(inputFile == NULL){
    //output error message
    printf("ERROR: Bad File Name (%s)", fileName);
    //return and exit the routine
    return EXIT_BAD_FILE_NAME;
  }
  //read in the magic number
  magic_number[0] = getc(inputFile);
  magic_number[1] = getc(inputFile);
  //store the magic number in the image struct
  image->magicNumber[0]= magic_number[0];
  image->magicNumber[1]=magic_number[1];
  //Check if the magic number of the file is valid
  if(*image->magic_Number != MAGIC_NUMBER_ASCII_PGM && *image->magic_Number != MAGIC_NUMBER_RAW_PGM){
    //output error message
    printf("ERROR: Bad Magic Number (%s)", fileName);
    //clean up memory and close file
    freeMemoryR(inputFile , image);
    //return correct error code
    return EXIT_BAD_MAGIC_NUMBER; 
  }
  //scan for any spaces
  int spaceCount = fscanf(inputFile, " ");
  //get the next charachter
  char nextChar = fgetc(inputFile);
  if(nextChar == '#'){//check for any comment lines
  //allocate memoryf for a comment line if it exists
    image->commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH);
      if(image->commentLine == NULL){//if allocation falied 
      //output error message   
      printf("ERROR: Image Malloc Failed");
      //clean up memory and close file
      freeMemoryR(inputFile,image);
      //return correct error code
      return 7;
    } 
    //read in the comment line and store it in the allocated memory
    char *commentString = fgets(image->commentLine,MAX_COMMENT_LINE_LENGTH, inputFile); 
    //check comment line length
    if((strlen(commentString) + 1) == MAX_COMMENT_LINE_LENGTH){
       printf("ERROR: Bad Comment Line (%s)", fileName);
      //clean up memory and close file
      freeMemoryR(inputFile,image);
      //return correct error code
      return EXIT_BAD_COMMENT;
    } 
  }
  else{
    //place the character back in the stream 
    ungetc(nextChar, inputFile);
  }
  //read the dimentions of the image file
  int scanCount = fscanf(inputFile, "%u %u %u", &(image->width), &(image->height), &(image->maxGray));
  if((scanCount != 3)||//check that the width , height and maximum gray value exist
  (image->width < MIN_IMAGE_DIMENSION)||// check that the width is within the specified limit
  (image->width > MAX_IMAGE_DIMENSION)||
  (image->height < MIN_IMAGE_DIMENSION)||//check that the height is within the specified limit
  (image->height > MAX_IMAGE_DIMENSION)
  ){
    //output error message
    printf("ERROR: Bad Dimensions (%s)", fileName);
    //clean up memory and close file
    freeMemoryR(inputFile, image);
    //return correct error code
    return EXIT_BAD_DIMENTIONS;
  }
  if(image->maxGray > MAX_GRAY_VALUE){
   //output ccorrect error code 
   printf("ERROR: Bad Max Gray Value (%s)",fileName);
   //clean memory and close file
   freeMemoryR(inputFile , image);
   //return correct error code
   return EXIT_BAD_MAX_GRAY_VALUE; 
  }
  //calculate the size of the image
  long nImageBytes = image->width * image->height * sizeof(unsigned char);
  image->imageData = (unsigned char*) malloc(nImageBytes);
  //allocate memory based on the size of the image
  if(image->imageData == NULL){//check if the memory allocation failed
    //output error message
    printf("ERROR: Image Malloc Failed");
    //clean up memory and close file
    freeMemoryR(inputFile , image);
    //return correct error code
    return 7;
  } 
  int grayValue = -1;
  if(image->magicNumber[1] == '2'){
    for(unsigned char *nextGrayValue = image->imageData; nextGrayValue < image->imageData + nImageBytes; nextGrayValue++)
    {
    //scan the gray value of the pixle and store it in the grayValue variable
    int scanCount = fscanf(inputFile, " %u", &grayValue);
    // int i = *nextGrayValue;
    // printf("value: %d\n",grayValue);
    //check if the scanCount is not equal to 1 the gray value is greater than 255 or less than 0
      if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255)){ 
        //output error message
        printf("ERROR: Bad Data (%s)", fileName);	
        //free memory and close file
        freeMemoryR(inputFile,image);
        //return correct error code
	      return EXIT_BAD_DATA;
      }
    //assign the next gray value to the grayValue variable
    *nextGrayValue = (unsigned char) grayValue;
    } 
  }
  else if(image->magicNumber[1] == '5'){
    int counter = -1;
    for(unsigned char *nextGrayValue = image->imageData; nextGrayValue < image->imageData + (image->width * image->height)+1; nextGrayValue++){
      // scan the gray value of the pixle and store it in the grayValue variable
      int scanCount = fread(nextGrayValue, sizeof(unsigned char),1, inputFile);
      if (counter > -1)
        image->imageData[counter] = *nextGrayValue;
      //check if the scanCount is not equal to 1 the gray value is greater than 255 or less than 0
      if ((scanCount != 1)){ 
          //output error message
          printf("ERROR: Bad Data (%s)", fileName);	
          //clean up memory an close file
          freeMemoryR(inputFile, image);
          //return correct error code
          return EXIT_BAD_DATA;
      }
      counter++;
    }
  }
  if(fscanf(inputFile, " %u", &grayValue) != EOF){
    printf("ERROR: Bad Data (%s)", fileName);	
    //free memory and close file
    freeMemoryR(inputFile,image);
    //return correct error code
    return EXIT_BAD_DATA;
  }
  //close file
  fclose(inputFile);
  return EXIT_NO_ERRORS;
}
int freeMemoryR(FILE * inputFile, Image *image){
  //close file
  fclose(inputFile);
  //check if the comment line not null
  if(image->commentLine != NULL){ 
   //free memory
    free(image->commentLine);
  }
  //check if image data is not null
  if(image->imageData != NULL){
    //free image data
    free(image->imageData);
  }
}

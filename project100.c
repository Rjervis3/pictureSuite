
    /***********************************************************************
     * Name: Renn Jervis                                                   *
     * Box: 3762                                                           *
     * Assignment name Project 100: Picture suite                          *
     *                                                                     *
     * Assignment for Friday November 7th                                  *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *   >referenced the Strucs lab, especially program structs-practice.c *
     *   >referenced Lab exercise on 2D Arrays for the corresponding       *
     *     greyscale value of a pixel                                      *
     *   >man page for sqrt funct                                          *
     *                                                                     *
     *                                                                     *
     *                                                                     *
     *   Help obtained                                                     *
     *     [none]                                                          *
     *                                                                     *
     *                                                                     *
     *   My/our signature(s) below confirms that the above list of sources *
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students) about the solution to this problem       *
     *                                                                     *
     *   Signature:                                                        *
     ***********************************************************************/
/* This is a program that contains an array of functions that modify a 
   picture*/

//compile and run with the line gcc -lMyroC -o 1 project100.c && ./1


#include <stdio.h>
#include "MyroC.h"
#include <math.h>  //for use of sqrt function


//Pre-conditions: None
//Post-conditions: This function should increase the red component
// of each pixel in the picture proportionally to the max value
void pictureRedder (Picture * pic);

//Pre-conditions: None
//Post-conditions: This function should increase the intensity of the 
//green color in each pixel of the picture proportionally to the maximum
void pictureGreener (Picture * pic);

//Pre-conditions: None
//Post-conditions: This function should increase the intensity of the 
//blue color in each pixel of the picture proportionally to max value
void pictureBluer (Picture * pic);

//Pre-conditions: color variable is either 'r', 'g', or 'b'
//Post-conditions: Function should set the pixel component of the specified 
//color to 0. 
void pixelStrip (Picture * pic, char color);

//Pre-conditions: xCenter and yCenter are within bounds of picture
//Post-conditions: Function should select each pixel within the given 
//radius of the specified center point and set it to correct greyscale val
void circleSelect (Picture * pic, int xCenter, int yCenter, int radius);

//Pre-conditions: None
//Post-conditions: Function should exchange sections of the picture  
void pictureSwap(Picture * pic);


//Pre-conditions: None (note: for testing)
//Post-conditions: Function saves picture to given filename
void exportPic(Picture * pic, const char * name)
{
  rSavePicture(pic, name);
}


//Pre-conditions: None
//Post-conditions: Program terminates successfully
int main()
{
  //specify original picture
  Picture * loadPic = rLoadPicture
    ("/home/jervisre/csc161/projects/project_100/flowers.jpg");

 //set color for pixelStrip function here
 char color = 'b';

  //create copies for various functions
  Picture * picStrip = rClonePicture(loadPic);
  Picture * picRed = rClonePicture(loadPic);
  Picture * picGreen = rClonePicture(loadPic);
  Picture * picBlue = rClonePicture(loadPic);
  Picture * picCircle = rClonePicture(loadPic);
  Picture * picSwap = rClonePicture(loadPic);

  //display original picture  note: will not continue until pic is closed
 rShowPicture(loadPic);

 pixelStrip(picStrip, color);
 rShowPicture(picStrip);

 pictureRedder(picRed);
 rShowPicture(picRed);

 pictureGreener(picGreen);
 rShowPicture(picGreen);

 pictureBluer(picBlue);
 rShowPicture(picBlue);

 circleSelect(picCircle, 100, 100, 100);
 rShowPicture(picCircle);

 pictureSwap(picSwap);
 rShowPicture(picSwap);

 //for use with testing
 //const char * file = "redder.jpg";
 // exportPic(picRed, file );

  return 0;
}

void pixelStrip (Picture * pic, char color)
{ int height, width, i, j;

  width =rGetPictureHeight(pic);  //see note in testing
  height =rGetPictureWidth(pic);
  
  // height =rGetPictureHeight(pic);
  // width =rGetPictureWidth(pic);

  Pixel rStripped, bStripped, Gstripped;
  //rStripped = rGetPicturePixel(
  //rStripped.G


  for (i=0; i<height; i++){   //i moves through rows
    for (j=0; j<width; j++){   //move across columns of each row
      if (color == 'r')                     //set all R pixels to 0
        {
          Pixel pixel = rGetPicturePixel(pic, i, j);
          pixel.R=0;
          rSetPicturePixel(pic, i, j,  pixel);              
        }
      else if (color == 'g')
        {                                       //set all G pixels to 0
          Pixel pixel = rGetPicturePixel(pic, i, j);
          pixel.G=0;
          rSetPicturePixel(pic, i, j, pixel);          
        }
      else if (color == 'b')
        {                                      //set all B pixels to 0
          Pixel pixel = rGetPicturePixel(pic, i, j);
          pixel.B=0;
          rSetPicturePixel(pic, i, j, pixel);
        }
    }
  }
}

void pictureRedder (Picture * pic)
{
  int x, y, height, width, red;
  double diff;

  width =rGetPictureHeight(pic);   //see note in testing
  height =rGetPictureWidth(pic);

  // height =rGetPictureHeight(pic);
  // width =rGetPictureWidth(pic);

  for(x=0; x<width; x++){ //iterate column by column
    for(y=0; y<height; y++){
      Pixel pixelRedden = rGetPicturePixel(pic, y, x);
      red=pixelRedden.R;
      diff=255-red;
      pixelRedden.R+=(diff*.8);//will not exceed 255 and scales red increase
      rSetPicturePixel(pic, y, x, pixelRedden);
    }
  }
}

void pictureGreener (Picture * pic)
{
  int x, y, height, width, green;
  double  diff;
  width =rGetPictureHeight(pic);
  height =rGetPictureWidth(pic);

  // height =rGetPictureHeight(pic);
  // width =rGetPictureWidth(pic);

  for(x=0; x<width; x++){ //iterate column by column
    for(y=0; y<height; y++){
      Pixel pixelGreen = rGetPicturePixel(pic, y, x);
      green=pixelGreen.G;
      diff=255-green;
      pixelGreen.G+=(diff*.8);//will not exceed 255 and scales green increase
      rSetPicturePixel(pic, y, x, pixelGreen);
    }
  }
}

void pictureBluer (Picture * pic)
{
  int x, y, height, width, blue;
  double diff;

  width =rGetPictureHeight(pic);
  height =rGetPictureWidth(pic);

  // height =rGetPictureHeight(pic);
  // width =rGetPictureWidth(pic);

  for(x=0; x<width; x++){ //iterate column by column
    for(y=0; y<height; y++){
      Pixel pixelBlue = rGetPicturePixel(pic, y, x);
      blue=pixelBlue.B;
      diff=255-blue;
      per = diff / (double) 255;
      pixelBlue.B+=(diff*.8);
      rSetPicturePixel(pic, y, x, pixelBlue);
    }
  }
}

void circleSelect (Picture * pic, int xCenter, int yCenter, int radius)
  {
    int x, y, height, width, xdist, ydist; 
    double distance, greyvalue;
    Pixel pixel;
    width =rGetPictureHeight(pic);
    height =rGetPictureWidth(pic);

    for(x=0; x<width; x++){
      for(y=0; y<height; y++){
        xdist=x-xCenter;
        ydist=y-yCenter;
        distance =sqrt( (xdist*xdist) + (ydist*ydist));
        //distance = 
        //sqrt((((x-xCenter)*(x-xCenter))+((y-yCenter)*(y-yCenter))));
        // printf("dist = %lf\n", distance);
        if (distance <=radius)
          {
            pixel=rGetPicturePixel(pic, y, x);
            greyvalue=.3*pixel.R+.5*pixel.G+.11*pixel.B;
            pixel.R=pixel.G=pixel.B=greyvalue;
            rSetPicturePixel(pic, y, x, pixel);
          }
      }
    }
  }

void pictureSwap(Picture * pic)
{
  int height, width;
  width =rGetPictureHeight(pic);
  height =rGetPictureWidth(pic);
  // height =rGetPictureHeight(pic);
   // width =rGetPictureWidth(pic);
  int x, y;
  Pixel pixeli, pixels, temp;
  //top left quadrent and bottom right switch
  for(x=0; x< width / 2; x++){
    for(y=0; y<height/2; y++){
      pixeli=rGetPicturePixel(pic, y, x);
      pixels=rGetPicturePixel(pic, y + height/2,  x + width/2);
      rSetPicturePixel(pic, y, x, pixels);
      rSetPicturePixel(pic, y+height/2, x + width/2, pixeli);
    }
  }
  //swap bottom left and upper right quadrant
     for(x=0; x< width/2; x++){
      for(y=height/2; y<height; y++){
        pixeli=rGetPicturePixel(pic, y, x);
        pixels=rGetPicturePixel(pic, y - height/2,  x + width/2);
        rSetPicturePixel(pic, y, x, pixels);
        rSetPicturePixel(pic, y-height/2, x + width/2, pixeli);
      }
      }


}

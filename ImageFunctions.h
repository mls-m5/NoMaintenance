/*
 * ImageFunctions.h
 *
 *  Created on: 29 jan 2013
 *      Author: mattias
 */

#ifndef IMAGEFUNCTIONS_H_
#define IMAGEFUNCTIONS_H_
#include <SDL/SDL.h>
#include <string>
#include <GL/gl.h>
#include "aux.h"

class Image{
public:
	GLuint num;
	int w;
	int h;
	int actualSize;
	Image():num(0), w(0), h(0){};

	Image(int texNum, int width, int height, int as){
		num = texNum;
		w = width;
		h = height;
		actualSize = as;
	}
};



class ImageFunctions {

//	static void setStandardDimensions(int num, SDL_Surface* bi2) ;


	static Image ConvertToImage(SDL_Surface *bi2);

public:
	static SDL_Surface *createSurface(SDL_Surface *surf, int w, int h, bool transparent);
	ImageFunctions();
	virtual ~ImageFunctions();
	static Image ForePicture[];
	static int subWidth[];
	static int subHeight[];
	static int imagesPerRow[];
	static GLuint levelPicFBO;
	static Image loadImage(std::string res, bool CustomPath = false);

	inline static unsigned int getBufferPixel(SDL_Surface*s, int x, int y) {
		return ((unsigned int*) ((s->pixels)))[y*(s->pitch/sizeof(unsigned int)) + x];}


	static SDL_Surface* loadRawSurface(bool CustomPath, std::string res);

	static unsigned int RGBToColor(int r, int g, int b, int a = 255);

	static void LoadBufferedImageToArray(int num, std::string res) ;

	static void DrawLineToDisplay(double x1, double y1, double x2, double y2, double w, Color c);


	static void DrawPicture(int picNum, double x, double y,
			int rotateNum) ;

	static void SetLevelPic(SDL_Surface* level, SDL_Surface* rlevel);
	static void SetLevelFBO(GLuint texture);

	static void InitImageFunctions(SDL_Surface* surface) ;
	static void UnloadImageFunctions();


	static void drawAirCircleToMap(int x, int y, int r) ;

	static void UpdateScreen();
	static void SetViewport(int x1, int y1, int w, int h);

	static void DrawCircleToMap(double X, double Y, double r, Color color) ;
	static void DrawCircle(double X, double Y, double r, Color c, double Alpha = 1.);

};

#endif /* IMAGEFUNCTIONS_H_ */

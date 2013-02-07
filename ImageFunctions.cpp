/*
 * ImageFunctions.cpp
 *
 *  Created on: 29 jan 2013
 *      Author: mattias
 */

#define GL_GLEXT_PROTOTYPES
//#define GL_GLEXT_PROTOTYPES

#include <GL/glew.h>
#include "ImageFunctions.h"
#include "aux.h"
#include <iostream>
#include <fstream>
using namespace std;
#include <string>
#include <iosfwd>
#include <GL/gl.h>
#include <math.h>


/* SDL interprets each pixel as a 32-bit number, so our masks must depend
   on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define rmask 0xff000000;
#define rmask 0x00ff0000;
#define rmask 0x0000ff00;
#define rmask 0x000000ff;
#else
#define rmask (0x000000ff)
#define gmask (0x0000ff00)
#define bmask (0x00ff0000)
#define amask (0xff000000)
#endif



Image ImageFunctions::ForePicture[ddLast];
int ImageFunctions::subWidth[ddLast];
int ImageFunctions::subHeight[ddLast];
int ImageFunctions::imagesPerRow[ddLast];
GLuint ImageFunctions::levelPicFBO;

SDL_Surface * BackSurface;
ImageFunctions::ImageFunctions() {
	// TODO Auto-generated constructor stub

}

ImageFunctions::~ImageFunctions() {
	// TODO Auto-generated destructor stub
}


void ImageFunctions::LoadBufferedImageToArray(int num, string res){
	auto bi2 = loadImage(res.c_str());
	ForePicture[num] = bi2;

	cout << res << endl;

	string url = ("data/gfx/" + res);
	ifstream file(url);
	if (file.is_open()){

		file >> subWidth[num];
		file >> subHeight[num];
		file >> imagesPerRow[num];
	}


}


//void ImageFunctions::setStandardDimensions(int num, SDL_Surface *bi2) {
//	subWidth[num] = bi2->w;
//	subHeight[num] = bi2->h;
//	imagesPerRow[num] = 1;
//}

SDL_Surface *ImageFunctions::createSurface(SDL_Surface*surf, int w, int h, bool transparent){

	auto surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
	                               rmask, gmask, bmask, amask);

	SDL_Rect source;
	source.x = source.y = 0;
	source.w = surf->w;
	source.h = surf->h;

//	SDL_Rect dest; //Detta stämmer ej.. src = dest...
//	dest.x = dest.y = 0;
//	dest.w = w;
//	dest.h = h;

	auto dest = source;
	if (surf)
		SDL_BlitSurface(surf, &source, surface, &dest);


//	source.x = source.y = 0;
//	source.w = surf->w;
//	source.w = surf->h;
//	SDL_FillRect(surface, &source, 0x00FFFF00);

	return surface;
}

inline int
pow2roundup (int x)
{
    if (x < 0)
        return 0;
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x+1;
}

	Image ImageFunctions::ConvertToImage(SDL_Surface* bi) {


	//Öker storleken så att gl blir glad
	int nw = (bi->w > bi->h)? bi->w: bi->h;
	nw = pow2roundup(nw);

	auto surface = createSurface(bi, nw,nw, false);

	//////////////////////////////////////7
	GLuint texture;
	// This is a handle to our texture object
//	SDL_Surface* surface = surface; // This surface will tell us the details of the image
	GLenum texture_format;
	GLint nOfColors;
	if ((surface)) {

		// Check that the image's width is a power of 2
		if ((surface->w & (surface->w - 1)) != 0) {
			printf("warning: image.bmp's width is not a power of 2\n");
		}

		// Also check if the height is a power of 2
		if ((surface->h & (surface->h - 1)) != 0) {
			printf("warning: image.bmp's height is not a power of 2\n");
		}

		// get the number of channels in the SDL surface
		nOfColors = surface->format->BytesPerPixel;
		if (nOfColors == 4) // contains an alpha channel
				{
			if (surface->format->Rmask == 0x000000ff)
				texture_format = GL_RGBA;
			else
				texture_format = GL_BGRA;
		} else if (nOfColors == 3) // no alpha channel
				{
			if (surface->format->Rmask == 0x000000ff)
				texture_format = GL_RGB;
			else
				texture_format = GL_BGR;
		} else {
			printf(
					"warning: the image is not truecolor..  this will probably break\n");
			// this error should not go unhandled
		}

		// Have OpenGL generate a texture object handle for us
		glGenTextures(1, &texture);

		// Bind the texture object
		glBindTexture(GL_TEXTURE_2D, texture);

		// Set the texture's stretching properties
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Edit the texture object's image data using the information SDL_Surface gives us
		glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
				texture_format, GL_UNSIGNED_BYTE, surface->pixels);
	} else {
		printf("SDL could not load image.bmp: %s\n", SDL_GetError());
		SDL_FreeSurface(surface);
		SDL_Quit();
		Image empty(0, 0,0, 0);
		return empty;
	}

	auto im = Image(texture, bi->w, bi->h,nw);
	// Free the SDL_Surface only if it was successfully created
	if (surface) {
		SDL_FreeSurface(surface);
	}
	return im;
}

SDL_Surface* ImageFunctions::loadRawSurface(bool CustomPath, string res) {
	SDL_Surface* bi;
	if (CustomPath) {
		bi = SDL_LoadBMP(res.c_str());
	} else {
		bi = SDL_LoadBMP(string("data/gfx/" + res + ".bmp").c_str());
	}
	if (!bi) {
		cout << "Kunde inte läsa in grafik: " << res << endl;
		//return NULL;
	}
	return bi;
}

Image ImageFunctions::loadImage(string res, bool CustomPath) {
	SDL_Surface *bi = loadRawSurface(CustomPath, res);

	//Gör om svart till alphalager
	SDL_SetColorKey( bi, SDL_SRCCOLORKEY, SDL_MapRGB(bi->format, 0, 0, 0) );



	//////////////////////////////////////7

	auto image = ConvertToImage(bi);
	SDL_FreeSurface(bi);

	return image;
}


void ImageFunctions::DrawPicture(int picNum, double x, double y,
		int rotateNum) {

	glColor4d(1,1,1,1);
	glBindTexture(GL_TEXTURE_2D, ForePicture[picNum].num);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glTexParameteri( GL_TEXTURE_2D,
//	                 GL_TEXTURE_WRAP_T,
//	                 GL_REPEAT );
	if (imagesPerRow[picNum] != 0){
		double w = (double)subWidth[picNum] / ForePicture[picNum].actualSize;
		double h = (double)subHeight[picNum] / ForePicture[picNum].actualSize;
		double sourceX = w * (double)(rotateNum % imagesPerRow[picNum]);
//		double sourceX = (double)stempx / (double)ForePicture[picNum].actualSize;

		double sourceY = h * (double)(rotateNum / imagesPerRow[picNum]);
//		double sourceY = (double) stempy / (double)ForePicture[picNum].actualSize;

//		SDL_Rect dest = {(unsigned short)x, (unsigned short)y,(unsigned short) (x+w), (unsigned short)(y+h)};
//		SDL_Rect source = {(unsigned short)sourceX, (unsigned short)sourceY, (unsigned short)(w), (unsigned short)(h)};
//		SDL_BlitSurface(ForePicture[picNum], &source, BackSurface, &dest);


		double x1 = x;
		double x2 = x + subWidth[picNum];
		double y1 = y;
		double y2 = y + subHeight[picNum];
		glBegin(GL_TRIANGLE_FAN);
		glColor3d(1,1,1);
		glTexCoord2d(sourceX, sourceY + 0);
		glVertex2d (x1, y1);
		glTexCoord2d(sourceX + w, sourceY + 0);
		glVertex2d (x2, y1);
		glTexCoord2d(sourceX + w, sourceY + h);
		glVertex2d(x2, y2);
		glTexCoord2d(sourceX + 0, sourceY + h);
		glVertex2d(x1, y2);
		glEnd();
	}
	else{
		double w = (double)ForePicture[picNum].w / ForePicture[picNum].actualSize;
		double h = (double)ForePicture[picNum].h / ForePicture[picNum].actualSize;
		double x1 = x;
		double x2 = x + ForePicture[picNum].w;
		double y1 = y;
		double y2 = y + ForePicture[picNum].h;
		glBegin(GL_TRIANGLE_FAN);
		glColor3d(1,1,1);
		glTexCoord2d(0, 0 + 0);
		glVertex2d (x1, y1);
		glTexCoord2d(0 + w, 0 + 0);
		glVertex2d (x2, y1);
		glTexCoord2d(0 + w, 0 + h);
		glVertex2d(x2, y2);
		glTexCoord2d(0 + 0, 0 + h);
		glVertex2d(x1, y2);
		glEnd();
//		int w = subWidth[picNum];
//		int h = subHeight[picNum];
//		SDL_Rect dest = {(unsigned short)x, (unsigned short)y,(unsigned short) (x+w), (unsigned short)(y+h)};
//		SDL_Rect source = {(unsigned short)0, (unsigned short)0, (unsigned short)(0 + w), (unsigned short)(0 + h)};
//	    SDL_BlitSurface(ForePicture[picNum], &source, BackSurface, &dest);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ImageFunctions::SetLevelPic(SDL_Surface* level, SDL_Surface* rlevel){
//	ForePicture[ddLevel] = level;

	ForePicture[ddLevel] = ConvertToImage(level);
	ForePicture[ddRLevel] = ConvertToImage(rlevel);
	SetLevelFBO(ForePicture[ddLevel].num);

//	ForePicture[ddLevel] = ConvertToImage(rlevel);

}

void ImageFunctions::InitImageFunctions(SDL_Surface *surface){

	glewInit();

	BackSurface = surface;

	LoadBufferedImageToArray(ddSmoke, "Smoke");
	LoadBufferedImageToArray(ddAirokurtz, "Airokurtz");
	LoadBufferedImageToArray(ddbExp, "bExp");
	LoadBufferedImageToArray(ddBomb, "Bomb");
	LoadBufferedImageToArray(ddChassi, "chassi");
	LoadBufferedImageToArray(ddCrossHair, "CrossHair");
	LoadBufferedImageToArray(ddDisk, "Disk");
	LoadBufferedImageToArray(ddEagle, "Eagle");
	LoadBufferedImageToArray(ddFlag, "Flag");
	LoadBufferedImageToArray(ddFlashbang, "Flashbang");
	LoadBufferedImageToArray(ddGuy, "Guy");
	LoadBufferedImageToArray(ddhExp, "hExp");
	LoadBufferedImageToArray(ddItem, "Item");
	LoadBufferedImageToArray(ddJetWheel, "Jetwheel");
	LoadBufferedImageToArray(ddMech, "Mech");
	LoadBufferedImageToArray(ddMissile, "Missile");
	LoadBufferedImageToArray(ddNinjaRope, "Ninjarope");
	LoadBufferedImageToArray(ddNuke, "nuke");
	LoadBufferedImageToArray(ddShell, "Shell");
	LoadBufferedImageToArray(ddSpark, "Spark");
	LoadBufferedImageToArray(ddTurret, "Turret");
	LoadBufferedImageToArray(ddWheel, "wheel");

	LoadBufferedImageToArray(ddWheel2, "wheel");  //Dessa fungerar ej av någon anlednin. Det verkar vara något med numren
	LoadBufferedImageToArray(ddCrossHair2, "CrossHair");
	LoadBufferedImageToArray(ddbExp2, "bExp");
//	LoadBufferedImageToArray(ddCrossHair, "chassi");
}


void ImageFunctions::drawAirCircleToMap(int x, int y, int r) {
//	Graphics2D g = ForePicture[ddLevel].createGraphics();
//	g.setColor(new Color(ForePicture[ddLevel].getRGB(0, 0), true));
//	g.fillOval(x - r, y - r, r * 2, r * 2);
//	g.dispose();
}

unsigned int ImageFunctions::RGBToColor(int r, int g, int b, int a) {
	return SDL_MapRGBA(BackSurface->format,r,g,b,a);
}

void ImageFunctions::DrawLineToDisplay(double x1, double y1, double x2,
		double y2, double w, Color c) {

	double dx, dy;
	dx = x2-x1;
	dy = y2-y1;

	double d = sqrt(dx * dx + dy* dy);
	dx /= d;
	dy /= d;
	dx *= w / 2;
	dy *= w / 2;

	glColor3d(c.r, c.g, c.b);

//	glDisable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_QUADS);
	glVertex2d(x1 - dy, y1 + dx);
	glVertex2d(x1 + dy, y1 - dx);
	glVertex2d(x2 + dy, y2 - dx);
	glVertex2d(x2 - dy, y2 + dx);
	glEnd();
//	glEnable(GL_TEXTURE_2D);


}




void ImageFunctions::SetLevelFBO(GLuint texture) {
	// create a renderbuffer object to store depth info

	//TODO: Se till att skriva om den här funktionen
//	GLuint textureId;
//	glGenTextures(1, &textureId);
//	glBindTexture(GL_TEXTURE_2D, textureId);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, ForePicture[ddLast].w, ForePicture[ddLast].h, 0,
//	             GL_RGBA, GL_UNSIGNED_BYTE, 0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	GLuint rboId;
//	glGenRenderbuffers(1, &rboId);
//	glBindRenderbuffer(GL_RENDERBUFFER, rboId);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,
//	                      ForePicture[ddLevel].w, ForePicture[ddLevel].h);
//	glBindRenderbuffer(GL_RENDERBUFFER, 0);
//
//	// create a framebuffer object
//	GLuint fboId;
//	glGenFramebuffers(1, &fboId);
//	glBindFramebuffer(GL_FRAMEBUFFER, fboId);
//
//	// attach the texture to FBO color attachment point
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
//	                       GL_TEXTURE_2D, textureId, 0);
//
//	// attach the renderbuffer to depth attachment point
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
//	                          GL_RENDERBUFFER, rboId);
//
//	GLboolean fboUsed = false;
//	// check FBO status
//	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//	if(status != GL_FRAMEBUFFER_COMPLETE)
//	    fboUsed = false;
//
//	// switch back to window-system-provided framebuffer
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//		if (!fboUsed){
//			cout << "Kunde inte ladda frame buffer-objekt. Kan inte ta bort data från kartans textur, felkod: " << status << endl;
//		}
//
//	return ;
	//Det verkar som att man bara behöver en render buffer om man vill använda djup...
//	GLuint RB;
//	glGenRenderbuffers(1, &RB);
//	glBindRenderbuffer(GL_RENDERBUFFER, RB);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,
//	                      ForePicture[ddLevel].w, ForePicture[ddLevel].h);
//	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// create a framebuffer object
	GLboolean fboUsed = false;

	glGenFramebuffers(1, &levelPicFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, levelPicFBO);

	// attach the texture to FBO color attachment point
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
	                       GL_TEXTURE_2D, ForePicture[ddLevel].num, 0);


	glBindTexture(GL_TEXTURE_2D, ForePicture[ddLevel].num);

	//De två första raderna är viktiga för att få det hela att fungera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap
	glBindTexture(GL_TEXTURE_2D, 0);

	// attach the renderbuffer to depth attachment point
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
//	                          GL_RENDERBUFFER, RB);
//	 check FBO status
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(status != GL_FRAMEBUFFER_COMPLETE)
	    fboUsed = false;

	if (!fboUsed){
		cout << "Kunde inte ladda frame buffer-objekt. Kan inte ta bort data från kartans textur, felkod: " << status << endl;
	}


	// switch back to window-system-provided framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


}

void ImageFunctions::UpdateScreen() {
//	SDL_Flip(BackSurface);
	SDL_GL_SwapBuffers();
	glClearColor(0,0.1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void ImageFunctions::UnloadImageFunctions() {
	for (int i=0; i < ddLast; ++i){
		glDeleteTextures(1, &ForePicture[i].num);
	}
}

void ImageFunctions::SetViewport(int x1, int y1, int w, int h) {
	glViewport(x1,y1,w,h);
}

void ImageFunctions::DrawCircleToMap(double X, double Y, double r, Color color) {
	auto textureSize = ForePicture[ddLevel].actualSize;
	glBindFramebuffer(GL_FRAMEBUFFER, levelPicFBO);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glViewport(0,0,textureSize, textureSize);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslated(-1,-1,0);
	glScaled(1. / (double)textureSize * 2., 1. / (double)textureSize * 2., 1.);

//	glBegin(GL_LINES);
//
//	glColor3d(1,1,1);
//	glVertex2d(0,0);
//	glVertex2d(X,Y);
//	glEnd();


	glDisable(GL_BLEND);
	glColor4d(0,color.r, color.g, color.b);
	glBegin(GL_TRIANGLE_FAN);
	for (int i= 0; i < 360; ++i){
		glVertex2f(X + r * sin((double)i / 180. * PI),Y + r * cos((double)i / 180. * PI));
	}
	glEnd();

	DrawCircle(X,Y,r, color, 0);


	glPopMatrix();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glEnable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, ForePicture[ddLevel].num);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

Color::Color(double nr, double ng, double nb) {
//	control for overflow
	auto max1 = [] (double x) {return (x > 1.)? 1. : x;};
	r = max1(nr);
	g = max1(ng);
	b = max1(nb);

	color = SDL_MapRGB(BackSurface->format, (unsigned char) r * 255, (unsigned char) g * 255, (unsigned char) b * 255);
}

Color::Color(unsigned int c) {
	Uint8 tr, tg, tb;
	SDL_GetRGB(c, BackSurface->format, &tr,&tg,&tb);
	r = (double) tr / 255.;
	g = (double) tg / 255.;
	b = (double) tb / 255.;
}

void ImageFunctions::DrawCircle(double X, double Y, double r, Color c, double Alpha) {
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor4d(Alpha,c.r, c.g, c.b);
	glBegin(GL_TRIANGLE_FAN);
	for (int i= 0; i < 360; ++i){
		glVertex2f(X + r * sin((double)i / 180. * PI),Y + r * cos((double)i / 180. * PI));
	}
	glEnd();
}





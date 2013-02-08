/*
 * Screen.h
 *
 *  Created on: 23 jan 2013
 *      Author: mattias
 */

#ifndef SCREEN_H_
#define SCREEN_H_
#include <list>
#include "Solid.h"
#include "Player.h"
#include "common.h"
#include "ControlClass.h"
#include <string>
#include <vector>
#include <SDL/SDL.h>
using std::string;
using std::vector;
class Screen {

	struct Position{
		double X, Y;
	};

private:
	int PLAYERNUMBER;
	std::vector<std::vector<unsigned char>>Map;
	int MapWidth, MapHeight;
	Color ignoreColor;
	std::list<Solid*> Objekt;
	std::list<Solid*> removeList;
	Position PlScreen[2];
	Position CScreen[2];
	Player * player[2];
	double Status[2][9];
	long QuakeScreen;
	long DropBoxLeft;

	int SCREENPLHEIGHT;
	int SCREENPLWIDTH;

	int MapIgnore;
	double TimeDelay;
	int Initialized;

	int PlayerScreenNum;
	Solid* CurrentObject;

	SDL_Surface *screen;

	int CurrentlyRendering;

	void setControlStateFromKey(int e, int i);
	void Render();

	struct ControlMap{
		unsigned int Jump;
		unsigned int Up;
		unsigned int Down;
		unsigned int Left;
		unsigned int Right;
		unsigned int Fire;
		unsigned int Change;
		unsigned int Reload;
	} cmap[2];

public:

	//BufferedImage backBuffer;
	struct ControlStruct {
		unsigned char Jump;
		unsigned char Up;
		unsigned char Down;
		unsigned char Left;
		unsigned char Right;
		unsigned char Fire;
		unsigned char Change;
		unsigned char Reload;
		int MoveDirection;
		int AimDirection;
	} control[2];
	Screen();
	virtual ~Screen();

	Screen(int Width, int Height, int PlayerNum);

	void Start();

	void LoadControls();

	void SetScreenSize(int w, int h);

	void InitFrmScreen() ;

	void LoadLevel(string filename) ;

	bool PollEvents();

	void getHardwareToControlNumber(SDL_KeyboardEvent *key, unsigned char state);

	int GetMapLine(double x,double y,double xs,double ys) ;

	void SetScreenPos(int num, double x, double y);

	void PlaySound(int s) ;

	void RemoveObject(Solid *o) ;
	void MakeSmoke(double x, double y, double xs, double ys,
			int SmokeType = 0) ;
	void MakeQuake(long QuakeScale) ;

	void DropBox() ;



	void HugeExplosion(double xpos, double ypos,  double Damage, double Power) ;
	void CustomExplosion(double x, double y, long Damage,
			int Size, long Power) ;
	void Explosion(double x, double y, int Size, int Damage, int Power) ;



	void DrawCircleToMap(double X, double Y, int r, int color);

	int isPlayer(double X, double Y, int Height = 0, int Width = 0) ;
	void AddTextToBuffer(long l, std::string string) ;
	Player *getPlayer(int l) ;
	void HitPlayer(int i, int Damage) ;
	void AddObject(Solid *o) ;

	int GetMap(double X, double Y) ;

	void DrawPlPic(int PicNum, double x, double y, long RotateNum = 0) ;

	void DrawOnePlPic(int playerNum,
			int picNum, double x, double y, int RotateNum = 0) ;


	int GetMapWidth() {return MapWidth;}

	int GetMapHeight() {return MapHeight;}

	void DrawPlLine(double xPos, double yPos,
			double x2, double y2, double width, Color c, bool rounded = false);

	void DrawPlCircle(double x, double y,
			double size, Color c);

	void DrawText(double x, double y, std::string text);
	void DrawOneText(double x, double y, std::string text, int num = -1);

	ControlStruct GetControll(int num) ;

	void SetStatus(long myNumber, long index, double value) ;
	void SetStatus(long number, long index, long Value, long ValueMax){
		if (ValueMax)
			SetStatus(number, index, (double)Value / (double)ValueMax);
		else
			SetStatus(number, index, 0.);
	}

	void MakePlayers(int myNumber) ;

	void KilledPlayer(int myNumber) ;

	bool isThisPlayer(int target, double ninjaPosX,
			double ninjaPosY) ;

	void SetPlayer(int Index, Player * p) ;

	void SetWeaponBar(int Index, double Value);
};

#endif /* SCREEN_H_ */

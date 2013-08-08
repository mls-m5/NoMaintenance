/*
 * Screen.cpp
 *
 *  Created on: 23 jan 2013
 *      Author: mattias
 */

#include "Screen.h"
#include <math.h>
#include <SDL/SDL.h>
#include "common.h"
#include "ImageFunctions.h"
#include "Smoke.h"
#include "Exp.h"
#include <ostream>
#include <iostream>
#include "SoundFunctions.h"
#include "Spark.h"
#include "Bomb.h"
#include "Blast.h"
#include "Musquash.h"
#include "HExp.h"
#include "Zookaba.h"
#include "Eagle.h"
#include "Guy.h"
#include "CExp.h"
#include "Reference.h"
#include "Airokurtz.h"
#include "Hao.h"
#include "Box.h"
#include "Phykoser.h"

Screen frmScreen;

Screen::Screen() {
	Initialized = false;

}

Screen::~Screen() {
	// TODO Auto-generated destructor stub
}



Screen::Screen(int Width, int Height, int PlayerNum)  {
	SetScreenSize(Width, Height);
	PlayerScreenNum = PlayerNum;
	if (!Initialized){
		InitFrmScreen();
		Initialized = true;
	}
}

void Screen::Start(){

	bool gameRunning = true;

	while (gameRunning)
	{
		DropBoxLeft = DropBoxLeft - 1;
		if (DropBoxLeft < 1) {
			DropBox();
			DropBoxLeft = 300;
		}

		if (PollEvents())
		{
			gameRunning = false;
		}

		for (auto it: Objekt){
			it->TimeTab();
		}

		removeList.sort();
		removeList.unique();
		for (auto r: removeList){
			Objekt.remove(r);
			delete r;
		}
		removeList.clear();
		Render();
		SDL_Delay((30));
	}


	SDL_Quit();
}

void Screen::getHardwareToControlNumber(SDL_KeyboardEvent *key, unsigned char state){
	auto s = key->keysym.sym;
	for (int i = 0; i < 2; ++i){
		if(s == cmap[i].Left)
			control[i].Left = state;
		else if(s == cmap[i].Right)
			control[i].Right = state;

		else if(s == cmap[i].Up)
			control[i].Up = state;

		else if(s == cmap[i].Down)
			control[i].Down = state;

		else if(s == cmap[i].Jump)
			control[i].Jump = state;

		else if(s == cmap[i].Fire)
			control[i].Fire = state;

		else if(s == cmap[i].Reload)
			control[i].Reload = state;

		else if(s == cmap[i].Change)
			control[i].Change = state;

		control[i].MoveDirection = 0;
		if (control[i].Left) control[i].MoveDirection --;
		if (control[i].Right) control[i].MoveDirection ++;


		control[i].AimDirection = 0;
		if (control[i].Up) control[i].AimDirection --;
		if (control[i].Down) control[i].AimDirection ++;
	}


}

bool Screen::PollEvents() {
	SDL_Event event;

	while(SDL_PollEvent(&event)) {

		if (event.type == SDL_QUIT){
			return true;
		}
		else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE){
				return true;
			}
			else if(event.key.keysym.sym == SDLK_F5){
				SDL_WM_ToggleFullScreen(screen);
			}
			else
			{

				getHardwareToControlNumber(&event.key, 1);
			}


		}
		else if (event.type == SDL_KEYUP){
			getHardwareToControlNumber(&event.key, 0);
		}
	}
	return false;

}


void Screen::LoadControls() {
	for (int i = 0; i < 2; ++i){
		control[i].MoveDirection = 0;
		control[i].AimDirection = 0;
		control[i].Left = 0;
		control[i].Right = 0;
		control[i].Up = 0;
		control[i].Down = 0;
		control[i].Change =0;
		control[i].Fire = 0;
	}
#if 0
	cmap[0].Left = SDLK_e;
	cmap[0].Right = SDLK_i;
	cmap[0].Up = SDLK_p;
	cmap[0].Down = SDLK_u;
	cmap[0].Jump = SDLK_SPACE;
	cmap[0].Fire = SDLK_h;
	cmap[0].Reload = SDLK_t;
	cmap[0].Change = SDLK_n;
#else
	cmap[0].Left = SDLK_a;
	cmap[0].Right = SDLK_d;
	cmap[0].Up = SDLK_w;
	cmap[0].Down = SDLK_s;
	cmap[0].Jump = SDLK_k;
	cmap[0].Fire = SDLK_j;
	cmap[0].Reload = SDLK_SPACE;
	cmap[0].Change = SDLK_l;
#endif


	cmap[1].Left = SDLK_LEFT;
	cmap[1].Right = SDLK_RIGHT;
	cmap[1].Up = SDLK_UP;
	cmap[1].Down = SDLK_DOWN;
	cmap[1].Jump = SDLK_KP5;
	cmap[1].Fire = SDLK_KP4;
	cmap[1].Reload = SDLK_KP0;
	cmap[1].Change = SDLK_KP6;
}

void Screen::SetScreenSize(int w, int h){
	SCREENPLWIDTH = w / 2;
	SCREENPLHEIGHT = h;
}

void Screen::InitFrmScreen() {
	SetScreenSize(1200, 800);
	SDL_Init( SDL_INIT_AUDIO | SDL_OPENGL);
	screen = SDL_SetVideoMode( SCREENPLWIDTH * 2, SCREENPLHEIGHT, 0,
			SDL_GL_DOUBLEBUFFER | SDL_OPENGL);
	SDL_WM_SetCaption( "No Maintenance", 0 );

	TimeDelay = 0.009;
	LoadControls();
	ImageFunctions::InitImageFunctions(screen);
	SoundFunctions::InitSoundFunctions();

//	PlaySound(dsExplosion);

	LoadLevel("data/user/test");
	PLAYERNUMBER = 2;

	GamePlay.Ammo = 100;
	GamePlay.Armor = 100;
	GamePlay.Blood = 100;
	GamePlay.Veihles = 10;
	GamePlay.ShowContent = true;


	for (int i = 0; i < 5; ++i){
		DropBox();
	}
	DropBoxLeft = 0;

	//
	//	auto s = new Smoke();
	//	s->Init(10, 10, 1, 1, 0);
	//	AddObject(s);
	//	MakeSmoke(10,10,0,1,0);
	//	MakeSmoke(40,10,0,1,0);
	//	MakeSmoke(70,10,0,1,0);


	//	for (int i = 0; i < 20; ++i){
	//		auto s2 = new Spark();
	//		s2->Init( 5 + (double)i, - 10 , 2+(double)i, 0);
	//		AddObject(s2);
	//	}

	//	s2 = new Spark();
	//	s2.Init(10, 10, 5, 1);
	//	AddObject(s2);
	//
	//	auto z = new Zookaba();
	//	z->Init(10, 10, 1, 1);
	//	AddObject(z);
	////
	//	auto b = new Bomb();
	//	b->Init(10, 10, 15, 2);
	//	AddObject(b);
	//
	//	auto b3 = new Blast();
	//	b3->Init(30, 10, 3, 0, 30);
	//	AddObject(b3);
	//
	//	auto m = new Musquash();

#if 0
	auto e = new Eagle();
	e->Init(30, 30, 0, 0,  1);
	AddObject(e);
	SetPlayer(1, e);

	auto m = new Airokurtz();
	m->Init(40, 30, 0, 0, 0);
	AddObject(m);
	SetPlayer(0, m);
#else
	srand(SDL_GetTicks());
	MakePlayers(0);
	MakePlayers(1);
#endif
	for (int i = 0; i < 10; ++i){
		MakePlayers(2);
	}

	//	m = new Musquash();
	//	m->Init(40, 30, 0, 0, 2);
	//	AddObject(m);
	//	SetPlayer(0, m);


	CScreen[0] = {200, 400};
	for (int j = 0; j <2; ++j){
		for (int i = 0; j < 8; ++j){
			SetStatus(j, i,1);
		}
	}
}


void Screen::LoadLevel(string filename) {
	unsigned int MapEl[mDirt + 1];

	//	auto bufferedImage = SDL_LoadBMP((filename + ".bmp").c_str());
	//
	auto imageSurf = SDL_LoadBMP((filename + ".bmp").c_str());
	auto bufferedImage = ImageFunctions::createSurface(imageSurf, imageSurf->w, imageSurf->h, 0);

	MapWidth = bufferedImage->w-1;
	MapHeight = bufferedImage->h-1;
	Map.resize(MapWidth);
	for (int i = 0; i < MapWidth; ++i){
		Map[i].resize(MapHeight);
	}

	for (int i = 0; i <= mDirt; ++i){
		MapEl[i] = ImageFunctions::getBufferPixel(bufferedImage, i, 0);
	}
	ignoreColor = Color(MapEl[0], bufferedImage->format);

	unsigned int pixel;
	for (int x=0; x<MapWidth; ++x)
		for (int y=0; y<MapHeight; ++y){
			pixel = ImageFunctions::getBufferPixel(bufferedImage, x, y);
			if (pixel == MapEl[mAir]){
				Map[x][y] = mAir;
			}
			else if (pixel == MapEl[mAir + 1]){
				Map[x][y] = mAir;
			}
			else{
				Map[x][y] = mDirt;
			}
		}

	auto imageSurf2 = ImageFunctions::loadRawSurface(true,(filename + "(r).bmp").c_str());
	auto bufferedImage2 = ImageFunctions::createSurface(imageSurf2, imageSurf2->w, imageSurf2->h, 1);
	if (bufferedImage2) {
		for (int x = 0; x<MapWidth; ++x)
			for(int y=0; y<MapHeight; ++y){

				pixel = ImageFunctions::getBufferPixel(bufferedImage2, x, y);

				if (pixel  != bufferedImage2->format->Amask){
					Map[x][y] = mRock;
				}
			}
	}
	else{
		std::cout << ("Kunde inte läsa filen" + filename + "(r).bmp" +
				"Laddar inte bergdelen") << std::endl;
	}

	SDL_SetColorKey( imageSurf, SDL_SRCCOLORKEY, ((unsigned int*)bufferedImage->pixels)[0] );
	SDL_SetColorKey( imageSurf2, SDL_SRCCOLORKEY, SDL_MapRGB(imageSurf2->format, 0, 0, 0) );
	ImageFunctions::SetLevelPic(imageSurf, imageSurf2);


	SDL_FreeSurface(bufferedImage);
	SDL_FreeSurface(bufferedImage2);
	SDL_FreeSurface(imageSurf);
	SDL_FreeSurface(imageSurf2);
}

void Screen::Render() {


	for (int i = 0; i < 2; ++i){
		CurrentlyRendering = i;

		ImageFunctions::SetViewport(i * SCREENPLWIDTH,0,SCREENPLWIDTH, SCREENPLHEIGHT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glScalef(1./SCREENPLWIDTH *4., -1./SCREENPLHEIGHT *4., 1.);
		glTranslatef(-PlScreen[i].X, - PlScreen[i].Y, 0);

		glMatrixMode(GL_MODELVIEW);
		//
		glLoadIdentity();
		DrawPlPic(ddLevel, 0,0, 0);
		for (auto it: Objekt){
			it->Render();
		}


		DrawPlPic(ddRLevel, 0,0, 0);

		//Ritar display
		glMatrixMode(GL_PROJECTION);

		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();


		for (int j = 0; j < 8; ++j){
			auto tx = -.8 + (double) j / 16. ;
			ImageFunctions::DrawLineToDisplay(tx,1./ 4. -1.,tx,-1.,.03, Color(0,0,0));
			ImageFunctions::DrawLineToDisplay(tx,Status[i][j] / 4. -1.,tx,-1.,.01, Color(1,1,1));
		}

		ImageFunctions::DrawCircle(0,-.90,.11,Color(.1,.1,.1, .5 * Status[i][8]));
		ImageFunctions::DrawPie(0,-.90,.1,Color(1,1,1), 0, 360 * Status[i][8]);
		Status[i][8] /= 1.5;
	}

	ImageFunctions::UpdateScreen();

}

int Screen::GetMapLine(double x,double y,double xs,double ys) {
	long i;
	float Xj; float Yj;
	int NX; int NY;
	long Total;
	unsigned char TempMap;
	double XSpeed = xs * 2;
	double YSpeed = ys * 2;
	if (XSpeed > 0) {
		if (YSpeed > 0) {
			Total = (long) (XSpeed + YSpeed);
		}
		else{
			Total = (long) (XSpeed - YSpeed);
		}
	}
	else{
		if (YSpeed > 0) {
			Total = (long) (-XSpeed + YSpeed);
		}
		else{
			Total = (long) (-XSpeed - YSpeed);
		}
	}
	Xj = 0;
	Yj = 0;
	if (Total != 0) { Xj = (float) (XSpeed / Total);}
	if (Total != 0) { Yj = (float) (YSpeed / Total);}
	for(i = 0; i <= Total; ++i){
		NX = (int) (x - i * Xj);
		NY = (int) (y - i * Yj);
		if (NY < 2) return mAir;
		if (NX < 2 || NX >= MapWidth || NY < 2 || NY >= MapHeight) {
			return mRock;
		}
		TempMap = Map[NX][NY];
		if (TempMap != 0) {
			return TempMap;
		}
	}

	return mAir;
}

void Screen::SetScreenPos(int num, double x, double y){
	PlScreen[num] = {x,y};
}

void Screen::PlaySound(int s) {
	SoundFunctions::PlaySound(s);
}


void Screen::RemoveObject(Solid* o) {
	//	Objekt.remove(o);
	//	delete (o);
	removeList.push_back(o);
}
void Screen::MakeSmoke(double x, double y, double xs, double ys,
		int SmokeType) {
	auto nSmoke = new Smoke();
	nSmoke->Init(x, y, xs, ys, SmokeType);
	AddObject(nSmoke);

}
void Screen::MakeQuake(long QuakeScale) {
	if (QuakeScale > QuakeScreen){
		QuakeScreen = QuakeScale;
	}
}

void Screen::DropBox() {
	long i; long X; long Y;
	int i2;
	i2 = Rnd() * 25;
	auto box = new Box;

	if (i2 <=  1){
		box->Item = "kanonare";
		box->BoxType = 1;
	} else if (i2 <=  2){
		box->Item = "m6ton";
		box->BoxType = 1;
	} else if (i2 <=  3){
		box->Item = "floppydisk";
		box->BoxType = 1;
	} else if (i2 <=  5){
		box->Item = "kraft";
		box->BoxType = 3;
	} else if (i2 <=  10){
		auto in = (int)(1 + Rnd() * 6);
		box->Item = "item nr " + in;
		box->BoxType = 2;
		box->ItemNumber = in;
	} else if (i2 <=  11){
		box->Item = "haubits";
		box->BoxType = 1;
	} else if (i2 <=  12){
		box->Item = "akå10";
		box->BoxType = 1;
	} else if (i2 <=  13){
		box->Item = "uschmalaba";
		box->BoxType = 4;
	} else if (i2 <=  14){
		box->Item = "m7ton";
		box->BoxType = 1;
	} else if (i2 <=  15){
		box->Item = "carlgustaf";
		box->BoxType = 1;
	} else if (i2 <=  16){
		box->Item = "minuteman";
		box->BoxType = 6;
	} else if (i2 <=  17){
		box->Item = "chokladzingo";
		box->BoxType = 4;
	} else if (i2 <=  18){
		box->Item = "gåsgun";
		box->BoxType = 0;
	} else if (i2 <=  19){
		box->Item = "armageddon";
		box->BoxType = 5;
	} else if (i2 <=  20){
		box->Item = "zookaba";
		box->BoxType = 1;
	} else if (i2 <=  21){
		box->Item = "multiblaster";
		box->BoxType = 0;
	} else if (i2 <=  22){
		box->Item = "jolt";
		box->BoxType = 0;
	} else if (i2 <=  23){
		box->Item = "nurb";
		box->BoxType = 4;
	} else if (i2 <=  24){
		box->Item = "gaseel";
		box->BoxType = 1;
	} else if (i2 <=  25){
		box->Item = "meangun";
		box->BoxType = 0;
	} else if (i2 <=  26){
		box->Item = "miligun";
		box->BoxType = 1;
	} else if (i2 <=  27){
		box->Item = "eldfunkar";
		box->BoxType = 4;
	} else if (i2 <=  28){
		box->Item = "SpastOLW";
		box->BoxType = 1;
	}

	AddTextToBuffer(0, "Har släppt " + box->Item);
	AddTextToBuffer(1, "Har släppt " + box->Item);
	for(i = 0; i <= 1000; ++i){
		X = (MapWidth - 20) * Rnd() + 10;
		Y = (MapHeight - 20) * Rnd() + 10;
		if (GetMap(X, Y) == mAir) { break;}
	}
	box->Init(X, Y, 0, 0);
	;
	AddObject(box);
	;
}


void Screen::HugeExplosion(double xpos, double ypos,  double Damage, double Power) {
	DrawCircleToMap (xpos, ypos, 30, mAir);
	auto nExp = new HExp();
	nExp->Init (xpos,ypos);
	AddObject(nExp);
	int i = isPlayer(xpos, ypos,30 , 30);
	double PX, PY;
	double FX = 0, FY = 0;
	if (i!=0){
		i = i-1;
		PX = player[i]->XPos;
		if (PX < 1 && PX > -1) {
			FX = Power / ((int)(Rnd() * 2)-1);
		}
		PY = player[i]->YPos;
		if (PY < 1 && PY > -1) {
			FY = Power / ((int)(Rnd() * 2)-1);
		}
		player[i]->Force(FX, FY);

		HitPlayer(i,  (int) Damage);
	}

}
void Screen::CustomExplosion(double x, double y, long Damage,
		int Size, long Power) {
	DrawCircleToMap(x, y, Size, mAir);
	double playerAngle; double playerDistance; double NPower;
	auto nExp = new CExp();
	nExp->Init (x,y,Size);
	AddObject(nExp);

	double dx, dy;

	for (int i = 0; i < PLAYERNUMBER; ++i){
		dx = player[i]->XPos - x;
		dy = player[i]->YPos - y;
		playerDistance = sqrt(dx * dx + dy * dy + player[i]->Width + player[i]->Height);

		if (playerDistance < Size){
			playerAngle = (double)GetRot(dx, dy, 6280) / 1000;
			NPower = playerDistance / Size + 1;
			player[i]->Force(sin(playerAngle) * Power / NPower,
					cos(playerAngle) * Power / NPower);
			player[i]->Damage((int) (Damage / NPower));
		}
	}

}
void Screen::Explosion(double x, double y, int Size, int Damage, int Power) {
		DrawCircleToMap (x, y, (double)(7 + 8 * Size), mAir);
//	DrawCircleToMap(x,y, 7+Size,mAir);
	auto nExp = new Exp();
	nExp->Init (x,y, Size);
	AddObject(nExp);
	int i = isPlayer(x, y,Size, Size);
	double PX, PY;
	double FX = 0, FY = 0;
	if (i!=0){
		i = i-1;
		PX = player[i]->XPos;
		if (PX < 1 && PX > -1) {
			FX = Power / (((int) Rnd()) * 2-1);
		}
		PY = player[i]->YPos;
		if (PY < 1 && PY > -1) {
			FY = Power / (((int) Rnd()) * 2 -1);
		}
		player[i]->Force(FX, FY);
		HitPlayer(i, Damage);
	}
}



void Screen::DrawCircleToMap(double X, double Y, int r, int color) {
	int cystart;
	int ty;
	//	int tx;
	;
	int rr;
	int cr;
	rr = r * r;
	if (Y - r < 0) { cystart = (int) -Y; }else{ cystart = -r;}
	if (Y + r >= MapHeight) { ty = (int) (MapHeight - Y); }else{ ty = r;}
	;
	for(int cy = cystart; cy <= ty; ++cy){
		cr = (int) sqrt(rr - cy * cy);
		int cxstart;
		cxstart = X - cr;
		if (cxstart < 0) cxstart = 0;
		int cxstop = X + cr;
		if (cxstop >= MapWidth) cxstop = MapWidth -1;
		for (int cx = cxstart; cx <= cxstop; ++cx){
			if (Map[cx][ (int) (cy + Y)] == mDirt) { Map[ cx][(int) (cy + Y)] = color;}
		}
	}

	Color c;
	if (color == mAir){
		c = Color(ignoreColor);
	}
	else{
		c = Color(0,1,0);
	}
	ImageFunctions::DrawCircleToMap(X, Y, r, c);
	//	ImageFunctions.drawAirCircleToMap((int)X,(int)Y,r);

}

int Screen::isPlayer(double X, double Y, int Height, int Width) {
	Height = Height / 2;
	Width = Width / 2;
	for(int i = 0; i <= 1; ++i){

		if (player[i]){
			if ((X - Width) < player[i]->XPos + player[i]->Width && (X + Width) > player[i]->XPos - player[i]->Width &&
					(Y - Height) < player[i]->YPos + player[i]->Height && (Y + Height) > player[i]->YPos - player[i]->Width) {
				return i + 1;
			}
		}

	}
	return 0;
}
void Screen::AddTextToBuffer(long l, string string) {
	// TODO Auto-generated method stub

}
Player *Screen::getPlayer(int i) {
	return player[i];
}

void Screen::HitPlayer(int i, int Damage) {
	player[i]->Damage(Damage);
}

void Screen::AddObject(Solid *o) {
	Objekt.push_front(o);
}

int Screen::GetMap(double X, double Y) {
	int tx = (int) X;
	int ty = (int) Y;
	if (ty < 0) return mAir;
	if (tx >= MapWidth || tx < 0) return mDirt;
	if (ty >= MapHeight || ty < 0) return mDirt;

	return Map[tx][ty];
}

void Screen::DrawPlPic(int PicNum, double x, double y, long RotateNum) {
	ImageFunctions::DrawPicture(PicNum, x , y, RotateNum);
}

void Screen::DrawOnePlPic(int playerNum,
		int PicNum, double x, double y, int RotateNum) {
	if (CurrentlyRendering == playerNum){
		ImageFunctions::DrawPicture(PicNum, x , y, RotateNum);
	}

}

void Screen::setControlStateFromKey(int e, int state) {
	switch (e) {
	case SDLK_SPACE:
		control[0].Jump = (state);
		break;

	case SDLK_LEFT:
		control[0].Left = (state);
		break;

	case SDLK_RIGHT:
		control[0].Right = (state);
		break;
	case SDLK_UP:
		control[0].Up = (state);
		break;

	case SDLK_DOWN:
		control[0].Down = (state);
		break;
	case SDLK_k:
		control[0].Fire = (state);
		break;
	case SDLK_j:
		control[0].Change = (state);
		break;
	case SDLK_PERIOD:
		control[0].Reload = (state);
		break;

	default:
		break;
	}
}

void Screen::DrawPlLine(double X1, double Y1,
		double X2, double Y2, double Width, Color c, bool rounded) {
	if (rounded){
		ImageFunctions::DrawCircle(X1, Y1, Width / 2., c);
		ImageFunctions::DrawCircle(X2, Y2, Width / 2., c);
	}
	ImageFunctions::DrawLineToDisplay(X1, Y1, X2, Y2, Width , c);
}

void Screen::DrawPlCircle(double x, double y,
		double size, Color c) {
	ImageFunctions::DrawCircle(x,y, size, c);
}

Screen::ControlStruct Screen::GetControll(int num) {
	return control[num];
}

void Screen::SetStatus(long player, long Index, double Value) {
	if (player >= 2) return;
	if (player < 0) return;
	Status[player][Index] = Value;

}

void Screen::MakePlayers(int myNumber) {
	int X, Y;
	for (int i = 0; i < 1000; ++i){
		X = (MapWidth - 20) * Rnd() + 10;
		Y = (MapHeight - 20) * Rnd() + 10;
		if (GetMap(X, Y) == mAir) break;
	}

	int vehicleNum = Rnd() * 6;
	Player *p;
	switch (vehicleNum) {
	case 0:
		p = new Musquash();
		break;
	case 1:
		p = new Eagle();
		break;
	case 2:
		p = new Reference();
		break;
	case 3:
		p = new Hao();
		break;
	case 4:
		p = new Airokurtz();
		break;
	case 5:
		p = new Phykoser();
		break;
	default:
		p = new Guy();
		break;
	}

	p->Init(X, Y, 0,0, myNumber);
	AddObject(p);
	if (myNumber == 0 || myNumber == 1){
		SetPlayer(myNumber, p);
	}
}

void Screen::KilledPlayer(int myNumber) {
}

bool Screen::isThisPlayer(int target, double ninjaPosX,
		double ninjaPosY) {
	// TODO Auto-generated method stub
	return false;
}


void Screen::DrawText(double x, double y, std::string text) {
	ImageFunctions::DrawText(x,y,text);
}


void Screen::DrawOneText(double x, double y, std::string text, int num) {
	if (num == CurrentlyRendering){
		ImageFunctions::DrawText(x,y,text);
	}
}

void Screen::SetPlayer(int Index, Player* p) {
	if (Index > PLAYERNUMBER -1) return;
	player[Index] = p;

}

void Screen::SetWeaponBar(int Index, double Value) {
	if (Index == 0 || Index == 1){
		Status[Index][8] = Value;
	}
}



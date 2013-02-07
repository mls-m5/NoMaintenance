/*
 * Tropelet.cpp
 *
 *  Created on: 6 feb 2013
 *      Author: mattias
 */

#include "Tropelet.h"
#include "Screen.h"

struct Position{
	double X, Y;
};

Tropelet::Tropelet() {
	// TODO Auto-generated constructor stub

}

Tropelet::~Tropelet() {
	// TODO Auto-generated destructor stub
}

void Tropelet::Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire){
    if (!isFire) { return;;}
    if (MyPlayer->getItem(1) < 20 || MyPlayer->getItem(2) < 220) { return;;}
    MyPlayer->setItem (1, 0);
    MyPlayer->CalcItem(2, -250);
    long i; Position Speed; Position Pos; long HitPlayer;
    Speed.X = XAim / 10 * Turn;
    Speed.Y = YAim / 10;
    Pos.X = X + XAim / 3 * Turn;
    Pos.Y = Y + YAim / 3;
    for(i = 0; i <= 30; ++i){
        Pos.X = Pos.X + Speed.X;
        Pos.Y = Pos.Y + Speed.Y;
        HitPlayer = FrmScreen.isPlayer((Pos.X), (Pos.Y));
        if (FrmScreen.GetMap((Pos.X), (Pos.Y)) || HitPlayer) { break;}
        FrmScreen.MakeSmoke(Pos.X, Pos.Y, 0, -3, 1);
    }
    PlaySound(dsFire4);
    if (i == 31) { return;;}
    Pos.X = Pos.X - Speed.X;
    Pos.Y = Pos.Y - Speed.Y;
    if (HitPlayer) {
        MakeWarp (HitPlayer - 1);
        FrmScreen.HitPlayer(HitPlayer- 1, 20);
    }else{
        FrmScreen.DrawCircleToMap((Pos.X), (Pos.Y), 30, mAir);
    }
}

void Tropelet::MakeWarp(long Player){
    long i; long X; long Y;
    long MapX; long MapY;
        auto PlayerToWarp = frmScreen.getPlayer(Player);
        MapX = frmScreen.GetMapWidth();
        MapY = frmScreen.GetMapHeight();
        FrmScreen.MakeSmoke(PlayerToWarp->XPos, PlayerToWarp->YPos, -3, 0, 1);
        FrmScreen.MakeSmoke(PlayerToWarp->XPos, PlayerToWarp->YPos, 3, 0, 1);
    for(i = 0; i <= 1000; ++i){
        X = (MapX - 20) * Rnd() + 10;
        Y = (MapY - 20) * Rnd() + 10;
        if (FrmScreen.GetMap(X, Y) == mAir) { break;}
    }
    PlayerToWarp->XPos = X;
    PlayerToWarp->YPos = Y;
    FrmScreen.MakeSmoke(PlayerToWarp->XPos, PlayerToWarp->YPos, -3, 0, 1);
    FrmScreen.MakeSmoke(PlayerToWarp->XPos, PlayerToWarp->YPos, 3, 0, 1);
}

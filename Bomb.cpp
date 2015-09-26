/*
 * Bomb.cpp
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#include "Bomb.h"
#include "common.h"
#include "Spark.h"

Bomb::Bomb() {
}

Bomb::~Bomb() {
}



void Bomb::Init(double X, double Y, double Xs, double Ys){
    XPos = X;
    YPos = Y;
    XSpeed = Xs;
    YSpeed = Ys;
}

void Bomb::TimeTab(){
    YSpeed = YSpeed + 0.3;
    XPos = XPos + XSpeed;
    YPos = YPos + YSpeed;
    if (FrmScreen.GetMapLine((XPos), (YPos), XSpeed, YSpeed)) {
        long i; Spark nSpark;
        FrmScreen.RemoveObject(this);
        FrmScreen.HugeExplosion((XPos), (YPos), 10, 15);
        for(i = 0; i <= 7; ++i){
            auto nSpark = new Spark;
            nSpark->Init((XPos - XSpeed * 2), (YPos - YSpeed * 2), 14 * Rnd()- 7, 15 * Rnd() - 10);
            FrmScreen.AddObject(nSpark);
        }
        PlaySound(dsExplosion);
        FrmScreen.MakeQuake(10);
    }
    if (FrmScreen.isPlayer((XPos), (YPos))) {
        FrmScreen.RemoveObject(this);
        FrmScreen.Explosion((XPos), (YPos), 1, 10, 15);
        PlaySound(dsExplosion);
        FrmScreen.MakeQuake(5);
    }
}

void Bomb::Render() {
    FrmScreen.DrawPlPic(ddShell, XPos - 5, YPos - 5, GetRot(XSpeed, YSpeed, 15));
}


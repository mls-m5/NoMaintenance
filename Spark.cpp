/*
 * Spark.cpp
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#include "Spark.h"
#include "common.h"
#include "ImageFunctions.h"

Spark::Spark() {
	// TODO Auto-generated constructor stub

}

Spark::~Spark() {
	// TODO Auto-generated destructor stub
}

void Spark::Init(double X, double Y, double Xs, double Ys) {
    XPos = X;
    YPos = Y;
    XSpeed = Xs;
    YSpeed = Ys;
}

void Spark::TimeTab() {
    YSpeed = YSpeed + 0.3;
    XPos = XPos + XSpeed;
    YPos = YPos + YSpeed;
    if (FrmScreen.GetMapLine((XPos), (YPos), XSpeed, YSpeed)!= 0) {
        FrmScreen.RemoveObject(this);
        long i;
        for(i = 0; i <= 5; ++i){
            XPos = XPos - XSpeed / 6;
            YPos = YPos - YSpeed / 6;
            if (FrmScreen.GetMap(XPos, YPos) == mAir) {
            	break;
            }
        }
        FrmScreen.Explosion(XPos, YPos, 0, 2, 1);
        return;
    }
    if (FrmScreen.isPlayer((XPos), (YPos))!= 0) {
        FrmScreen.RemoveObject(this);
        FrmScreen.Explosion((XPos), (YPos), 1, 4, 1);
    }
}

void Spark::Render() {
    FrmScreen.DrawPlLine (XPos, YPos, XPos - XSpeed, YPos - YSpeed, 1, ImageFunctions::RGBToColor(255,255,0));
}



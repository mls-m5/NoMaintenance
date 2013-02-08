/*
 * CExp.cpp
 *
 *  Created on: 6 feb 2013
 *      Author: mattias
 */

#include "CExp.h"
#include "common.h"

CExp::CExp() {
	// TODO Auto-generated constructor stub

}

CExp::~CExp() {
	// TODO Auto-generated destructor stub
}


void CExp::Init(double X, double Y, double Size){
	XPos = X;
	YPos = Y;
	mSize = Size;
}

void CExp::TimeTab(){
	mSize = mSize / 1.5 - 2;
	if (mSize < 0) {
		FrmScreen.RemoveObject(this);
	}
}
void CExp::Render(){
	FrmScreen.DrawPlCircle (XPos, YPos, mSize, Color(1,1,0));
}

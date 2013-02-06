/*
 * Exp.cpp
 *
 *  Created on: 29 jan 2013
 *      Author: mattias
 */

#include "Exp.h"
#include "aux.h"

Exp::Exp() {
	// TODO Auto-generated constructor stub

}

Exp::~Exp() {
	// TODO Auto-generated destructor stub
}

void Exp::Init(double X, double Y, long nSize){
	XPos = X;
	YPos = Y;
	i = (int) (3 - 3 * nSize);
	Size = 7;
}

void Exp::TimeTab(){
	if (i >= Size) {
		FrmScreen.RemoveObject(this);
	}
	i = i + 1;
}
void Exp::Render(){
	FrmScreen.DrawPlPic(ddbExp, XPos - 15, YPos - 15, i);
}

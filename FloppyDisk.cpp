/*
 * FloppyDisk.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "FloppyDisk.h"
#include "common.h"
#include "Disk.h"

FloppyDisk::FloppyDisk() {
	// TODO Auto-generated constructor stub

}

FloppyDisk::~FloppyDisk() {
	// TODO Auto-generated destructor stub
}

void FloppyDisk::Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire){
    if (!isFire) { return;;}
    if (MyPlayer->getItem(1) < 100 || MyPlayer->getItem(5) < 2) { return;;}
    MyPlayer->CalcItem(1, -100);
    MyPlayer->CalcItem(5, -2);
    auto nDisk = new Disk;
    nDisk->Init(X + XAim / 3 * Turn, Y + YAim / 3, XAim / 5 * Turn, YAim / 5);
    FrmScreen.AddObject(nDisk);
    PlaySound(dsLaunch);

}

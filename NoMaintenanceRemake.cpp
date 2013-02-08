//============================================================================
// Name        : NoMaintenanceRemake.cpp
// Author      : Mattias Larsson Sköld
// Version     :
// Copyright   : Copyright
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include "Screen.h"

using namespace std;
#ifdef __MINGW32__

int main( int argc, char **argv ) {
#else
int main(void) {
#endif
	frmScreen.InitFrmScreen();
	frmScreen.Start();
	return 0;
}

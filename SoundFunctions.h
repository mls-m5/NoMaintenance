/*
 * SoundFunctions.h
 *
 *  Created on: 29 jan 2013
 *      Author: mattias
 */

#ifndef SOUNDFUNCTIONS_H_
#define SOUNDFUNCTIONS_H_

#define MAXPLAYINGSOUNDS 20

#include <string>
#include <SDL/SDL.h>

#include "aux.h"

class SoundFunctions {

	struct sample {
	    Uint8 *data;
	    Uint32 dpos;
	    Uint32 dlen;
	} ;

	static sample playingSounds[MAXPLAYINGSOUNDS];

	class Sound{
public:
	    Uint8 *data;
	    Uint32 dpos;
	    Uint32 dlen;

	    Sound(std::string filename);
	    ~Sound();

	} ;

	static Sound* sound[dslast];

	static void mixaudio(void *unused, Uint8 *stream, int len);


public:
	SoundFunctions();
	virtual ~SoundFunctions();


	static void InitSoundFunctions();

	static void unloadSoundFunctions();

	static void PlaySound(int soundNum);
};

inline void PlaySound(int num){
	SoundFunctions::PlaySound(num);
}


#endif /* SOUNDFUNCTIONS_H_ */

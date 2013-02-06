/*
 * SoundFunctions.cpp
 *
 *  Created on: 29 jan 2013
 *      Author: mattias
 */

#include "SoundFunctions.h"
#include <SDL/SDL.h>

SoundFunctions::sample SoundFunctions::playingSounds[MAXPLAYINGSOUNDS];

SoundFunctions::Sound* SoundFunctions::sound[dslast];

SoundFunctions::SoundFunctions() {
	// TODO Auto-generated constructor stub

}

SoundFunctions::~SoundFunctions() {
	// TODO Auto-generated destructor stub
}

void SoundFunctions::InitSoundFunctions() {
	sound[dsFire1] = new Sound("fire1.wav"); //Laddar ljudfilerna
	sound[dsFire2] = new Sound("fire2.wav");
	sound[dsFire3] = new Sound("fire3.wav");
	sound[dsFire4] = new Sound("fire4.wav");
	sound[dsFire5] = new Sound("fire5.wav");
	sound[dsFire6] = new Sound("fire6.wav");
	sound[dsFire7] = new Sound("fire7.wav");
	sound[dsFire8] = new Sound("fire8.wav");
	sound[dsFire9] = new Sound("fire9.wav");
	sound[dsShotgun] = new Sound("shotgun.wav") ;
	sound[dsExplosion] = new Sound("exp.wav");
	sound[dsReload] = new Sound("reload.wav");
	sound[dsReload2] = new Sound("reload2.wav");
	sound[dsOpen] = new Sound("open.wav");
	sound[dsLaser] = new Sound("laserfire.wav");
	sound[dsLaunch] = new Sound("launch.wav");
	sound[dsOusch] = new Sound("ousch.wav");
	sound[dsDie] = new Sound("die.wav");


    extern void mixaudio(void *unused, Uint8 *stream, int len);
    SDL_AudioSpec fmt;

    /* Set 16-bit stereo audio at 22Khz */
    fmt.freq = 22050;
    fmt.format = AUDIO_S16;
    fmt.channels = 2;
    fmt.samples = 512;        /* A good value for games */
    fmt.callback = SoundFunctions::mixaudio;
    fmt.userdata = NULL;

    /* Open the audio device and start playing sound! */
    if ( SDL_OpenAudio(&fmt, NULL) < 0 ) {
        fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_PauseAudio(0);

}

void SoundFunctions::unloadSoundFunctions() {

	SDL_CloseAudio();
}

void SoundFunctions::mixaudio(void* unused, Uint8* stream, int len) {

	int i;
	//Uint32 amount;
	int amount;

	for ( i=0; i<MAXPLAYINGSOUNDS; ++i ) {
		amount = (playingSounds[i].dlen-playingSounds[i].dpos);
		if ( amount > len ) {
			amount = len;
		}
		SDL_MixAudio(stream, &playingSounds[i].data[playingSounds[i].dpos], (Uint32)amount, SDL_MIX_MAXVOLUME);
		playingSounds[i].dpos += amount;
	}
}

void SoundFunctions::PlaySound(int soundNum) {
	int index;
	for ( index=0; index<MAXPLAYINGSOUNDS; ++index ) {
		if ( playingSounds[index].dpos == playingSounds[index].dlen ) {
			break;
		}
	}
	if ( index == MAXPLAYINGSOUNDS )
		return;
	SDL_LockAudio();
	playingSounds[index].data = sound[soundNum]->data;
	playingSounds[index].dlen = sound[soundNum]->dlen;
	playingSounds[index].dpos = 0;

	SDL_UnlockAudio();
}

SoundFunctions::Sound::Sound(std::string filename) {
	SDL_AudioSpec wave;
	Uint8 *data;
	Uint32 dlen;
	SDL_AudioCVT cvt;


	/* Load the sound file and convert it to 16-bit stereo at 22kHz */
	if ( SDL_LoadWAV(("data/sfx/" + filename).c_str(), &wave, &data, &dlen) == NULL ) {
		cout << "Couldn't load " << filename << " " << SDL_GetError() << endl;
		return;
	}
	SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq,
			AUDIO_S16,   2,             22050);
	cvt.buf = (Uint8*)malloc(dlen*cvt.len_mult);
	memcpy(cvt.buf, data, dlen);
	cvt.len = dlen;
	SDL_ConvertAudio(&cvt);
	SDL_FreeWAV(data);

	this->data = cvt.buf;
	this->dlen = cvt.len_cvt;
}

SoundFunctions::Sound::~Sound() {
	free(data);
}





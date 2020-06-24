#pragma once

#include <stdio.h>
#include <Windows.h>

#pragma comment(lib,"winmm.lib")		
#include "Mmsystem.h"
#include "Digitalv.h"

MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;
DWORD m_dwDeviceID;
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;

int dwID_bgm;
int dwID_eff;

#define background_bgm "../../resource/sound/start.wav"
#define click_event "../../resource/sound/event.wav"

void PlayMusic(fileName);
void StopMusic();

void PlayEffect(fileName);
void StopEffect();

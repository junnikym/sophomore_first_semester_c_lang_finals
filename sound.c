#include "sound.h"

//"../../resource/sound/"

void PlayMusic(fileName) {

	printf("Reading sound\n");

	mciOpen.lpstrElementName = fileName; // 파일 경로 입력
	mciOpen.lpstrDeviceType = "mpegvideo";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)& mciOpen);

	dwID_bgm = mciOpen.wDeviceID;

	mciSendCommand(dwID_bgm, MCI_PLAY, MCI_DGV_PLAY_REPEAT, // play & repeat
		(DWORD)(LPVOID)& m_mciPlayParms);

	/* mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY,
	(DWORD)(LPVOID)&m_mciPlayParms); */// Pause

	/* mciSendCommandW(dwID, MCI_RESUME, 0, NULL); */// resume

	/* mciSendCommandW(dwID, MCI_CLOSE, 0, NULL); */// stop
}

void StopMusic() {
	mciSendCommand(dwID_bgm, MCI_CLOSE, 0, NULL); // Sound off
}

void PlayEffect(fileName) {

	sndPlaySoundA(fileName, SND_ASYNC | SND_NODEFAULT | 0);

	mciOpen.lpstrElementName = fileName; // 파일 경로 입력
	mciOpen.lpstrDeviceType = "mpegvideo";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)& mciOpen);

	dwID_eff = mciOpen.wDeviceID;

	mciSendCommand(dwID_bgm, MCI_PLAY, MCI_NOTIFY, (DWORD)& m_mciPlayParms); // play & repeat
}

void StopEffect() {
	mciSendCommand(dwID_eff, MCI_CLOSE, 0, NULL);
}

#include <Windows.h>
#include <string>
#include <chrono>
#include <tchar.h>
#include <strsafe.h>

#include "settings.h"
#include "charset.h"

using namespace std;

int nScreenWidth = 80;
int nScreenHeight = 40;
int nAnimationCount = 0;

float fPreferedFPS = 10.0f;//an speed of screen`s refreshing

float fMinElapsedTime = 1.0f;
float fMaxElapsedTime = 0.0f;
float fElapsedTime;
float fFPSSync = 0.0f;
float fFPSCount = 0.0f;

bool bCheckKeyState = false;

auto tp1 = chrono::system_clock::now();
auto tp2 = chrono::system_clock::now();

short nShade = 9600;

wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight + 1];
void screenfill() {
	for (int i = 0; i < nScreenWidth * nScreenHeight + 1; i++) screen[i] = nShade;
}

int main() {
	charset CharSet;

	string sLogo1 = "    ______     ______     __   __   ______     ______     ______     __  __        /1$$==$1   /1$$___1   /1$1 /$/  /1$$___1   /1$$==$1   /1$$___1   /1$1_1$1       1$1$$__<   1$1$$__1   1$1$1`/   1$1$$__1   1$1$$__<   1$1___$$1  1$1____$1       1$1_1$1_1  1$1_____1  1$1_/     1$1_____1  1$1_1$1_1  1/1_____1  1/1_____1       1/_/$/_/   1/_____/   1//       1/_____/   1/_/$/_/   1/_____/   1/_____/   ";
	/* ______     ______     __   __   ______     ______     ______     __  __
	  /\  == \   /\  ___\   /\ \ / /  /\  ___\   /\  == \   /\  ___\   /\ \_\ \
	  \ \  __<   \ \  __\   \ \ \'/   \ \  __\   \ \  __<   \ \___  \  \ \____ \
	   \ \_\ \_\  \ \_____\  \ \_/     \ \_____\  \ \_\ \_\  \/\_____\  \/\_____\
		\/_/ /_/   \/_____/   \//       \/_____/   \/_/ /_/   \/_____/   \/_____/ */

	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	screenfill();
	
	while(1) {
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		fElapsedTime = elapsedTime.count();
		if (fElapsedTime < fMinElapsedTime) fMinElapsedTime = fElapsedTime;
		if (fElapsedTime > fMaxElapsedTime) fMaxElapsedTime = fElapsedTime;
		
		if (GetAsyncKeyState(0x41) & 0x8000 || GetAsyncKeyState(0x44) & 0x8000) {
			if (GetAsyncKeyState(0x41) & 0x8000 && !bCheckKeyState) nShade += 4;
			if (GetAsyncKeyState(0x44) & 0x8000 && !bCheckKeyState) nShade -= 4;
			bCheckKeyState = true;
		}
		else bCheckKeyState = false;
		
		if (fFPSSync > (1.0f / fPreferedFPS)) {
			if (nAnimationCount > 8) nAnimationCount = 0;
			nAnimationCount++;

			for (int y = 0; y < nScreenHeight; y++) {
				for (int x = 0; x < nScreenWidth; x++) {
					//animation
					screen[x + y * nScreenWidth] = CharSet.FsShade((x + y + nAnimationCount) % 9);

					//static
					//screen[x + y * nScreenWidth] = CharSet.FsShade((x + y) % 10);

					//logo
					if ((x + y * nScreenHeight) < (nScreenWidth * 5) && (sLogo1[x + y * nScreenHeight] != ' ')) {
						screen[x + y * nScreenHeight] = CharSet.FcSpecChar(sLogo1[x + y * nScreenHeight]);
					} //else if ((x + y * nScreenHeight) < (nScreenWidth * 6)) screen[x + y * nScreenHeight] = nShade;

				}
			}



			screen[nScreenWidth * nScreenHeight] = '\0';
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
			fFPSCount = fFPSSync;
			fFPSSync = 0.0f;
			//nShade++;
		}
		else {
			fFPSSync += fElapsedTime;
		}

		TCHAR title[MAX_PATH];
		StringCchPrintf(title, MAX_PATH, TEXT("FPS = %3.2f | FPS_Max = %3.2f | FPS_Min = %3.2f | FPS_Sync=%3.2f | ASCII Code = %1.0f"), 1.0f / fElapsedTime, 1.0f / fMinElapsedTime, 1.0f / fFPSCount, 1.0f / fMaxElapsedTime, (float)nShade);
		SetConsoleTitle(title);
	}
	return 0;
}

/*
swprintf(screen, 80, L"FPS=%3.2f FPS_Max=%3.2f FPS_Min=%3.2f Hesh=%1.0f", 1.0f / fElapsedTime, 1.0f / fMinElapsedTime, 1.0f / fMaxElapsedTime, (float)nShade);

------------------------------------------------

for (int y = 0; y < nScreenWidth; y++) {
	for (int x = 0; x < nScreenHeight; x++) {
		screen[x + y * nScreenHeight] = nShade;
	}
}

------------------------------------------------


*/
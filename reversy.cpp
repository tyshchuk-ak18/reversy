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
int nSelectedButton = 0;

float fPreferedFPS = 10.0f;//an speed of screen`s updating

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
	settings Setting;

	string sMenuButton = "Start";
	string sLogo1 = " $______$   $______$   $__   __ $______$   $______$   $______$   $__  __$   ";
	string sLogo2 = "$/1$$==$1$ $/1$$___1$ $/1$1 /$/$/1$$___1$ $/1$$==$1$ $/1$$___1$ $/1$1_1$1$  ";
	string sLogo3 = "$1$1$$__<$$$1$1$$__1$$$1$1$1`/$$1$1$$__1$$$1$1$$__<$$$1$1___$$1$$1$1____$1$ ";
	string sLogo4 = " $1$1_1$1_1$$1$1_____1$$1$1_/$  $1$1_____1$$1$1_1$1_1$$1/1_____1$$1/1_____1$";
	string sLogo5 = "  $1/_/$/_/$ $1/_____/$ $1//$    $1/_____/$ $1/_/$/_/$ $1/_____/$ $1/_____/$";//$ equal to null
	string sLogo6 = "   $$$$ $$$   $$$$$$$$   $$$      $$$$$$$$   $$$$ $$$   $$$$$$$$   $$$$$$$$ ";

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
		
		if (GetAsyncKeyState(0x41) & 0x8000 || GetAsyncKeyState(0x44) & 0x8000 || GetAsyncKeyState(0x45) & 0x8000 || GetAsyncKeyState(0x51) & 0x8000 || GetAsyncKeyState(0x53) & 0x8000 || GetAsyncKeyState(0x57) & 0x8000) {
			if (GetAsyncKeyState(0x53) & 0x8000 && !bCheckKeyState) nShade -= 4;//s
			if (GetAsyncKeyState(0x41) & 0x8000 && !bCheckKeyState) nShade -= 4;//a
			if (GetAsyncKeyState(0x51) & 0x8000 && !bCheckKeyState) nShade -= 4;//q
			if (GetAsyncKeyState(0x57) & 0x8000 && !bCheckKeyState) nShade += 4;//w
			if (GetAsyncKeyState(0x44) & 0x8000 && !bCheckKeyState) nShade += 4;//d
			if (GetAsyncKeyState(0x45) & 0x8000 && !bCheckKeyState) nShade += 4;//e
			bCheckKeyState = true;
		}
		else bCheckKeyState = false;
		
		if (fFPSSync > (1.0f / fPreferedFPS)) {//main screen will update every 1 / fPreferedFPS milliseconds
			if (nAnimationCount > 7) nAnimationCount = 0;
			if (Setting.GbEA()) nAnimationCount++;

			for (int y = 0; y < nScreenHeight; y++) {
				for (int x = 0; x < nScreenWidth; x++) {
					//animation and background
					if (Setting.GbEA()) screen[x + y * nScreenWidth] = CharSet.GsShade((x + y + nAnimationCount) % 8);
					else screen[x + y * nScreenWidth] = CharSet.GsShade(0);

					//logo_new
					if (x >= Setting.GnLPX() && x <= Setting.GnLPX() + 75) if (y >= Setting.GnLPY() && y <= Setting.GnLPY() + 5) {
						if (y == Setting.GnLPY() + 0) if (sLogo1[x - Setting.GnLPX()] != ' ') screen[x + y * nScreenWidth] = CharSet.GcSpecChar(sLogo1[x - Setting.GnLPX()]);
						if (y == Setting.GnLPY() + 1) if (sLogo2[x - Setting.GnLPX()] != ' ') screen[x + y * nScreenWidth] = CharSet.GcSpecChar(sLogo2[x - Setting.GnLPX()]);
						if (y == Setting.GnLPY() + 2) if (sLogo3[x - Setting.GnLPX()] != ' ') screen[x + y * nScreenWidth] = CharSet.GcSpecChar(sLogo3[x - Setting.GnLPX()]);
						if (y == Setting.GnLPY() + 3) if (sLogo4[x - Setting.GnLPX()] != ' ') screen[x + y * nScreenWidth] = CharSet.GcSpecChar(sLogo4[x - Setting.GnLPX()]);
						if (y == Setting.GnLPY() + 4) if (sLogo5[x - Setting.GnLPX()] != ' ') screen[x + y * nScreenWidth] = CharSet.GcSpecChar(sLogo5[x - Setting.GnLPX()]);
						if (y == Setting.GnLPY() + 5) if (sLogo6[x - Setting.GnLPX()] != ' ') screen[x + y * nScreenWidth] = CharSet.GcSpecChar(sLogo6[x - Setting.GnLPX()]);
					}

					//borders

					//1 menu button
					if (x >= Setting.GnFBPX() && x <= Setting.GnFBPX() + 6) if (y >= Setting.GnFBPY() && y <= Setting.GnFBPY() + 2) {
						if (x == Setting.GnFBPX() && y == Setting.GnFBPY()) screen[x + y * nScreenWidth] = CharSet.GsBorder(1);
						if (x == Setting.GnFBPX() + 6 && y == Setting.GnFBPY()) screen[x + y * nScreenWidth] = CharSet.GsBorder(2);
						if (x == Setting.GnFBPX() + 6 && y == Setting.GnFBPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(3);
						if (x == Setting.GnFBPX() && y == Setting.GnFBPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(4);
						if (x > Setting.GnFBPX() && x < Setting.GnFBPX() + 6 && (y == Setting.GnFBPY() || y == Setting.GnFBPY() + 2)) screen[x + y * nScreenWidth] = CharSet.GsBorder(5);
						if ((x == Setting.GnFBPX() || x == Setting.GnFBPX() + 6) && y > Setting.GnFBPY() && y < Setting.GnFBPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(6);
						
					}
				}
			}



			screen[nScreenWidth * nScreenHeight] = '\0';
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
			fFPSCount = fFPSSync;
			fFPSSync = 0.0f;
		}
		else fFPSSync += fElapsedTime;

		TCHAR title[MAX_PATH];
		StringCchPrintf(title, MAX_PATH, TEXT("FPS = %3.2f | FPS_Max = %3.2f | FPS_Min = %3.2f | FPS_Sync=%3.2f | TEST = %1.0f"), 1.0f / fElapsedTime, 1.0f / fMinElapsedTime, 1.0f / fFPSCount, 1.0f / fMaxElapsedTime, (float)nShade);
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
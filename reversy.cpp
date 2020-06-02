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
const int nMenuButtons = 3;

float fPreferedFPS = 30.0f;//an speed of screen`s updating

float fMinElapsedTime = 1.0f;
float fMaxElapsedTime = 0.0f;
float fElapsedTime;
float fFPSSync = 0.0f;
float fFPSCount = 0.0f;

bool bCheckKeyState = false;
bool bCheckedMenuButton[nMenuButtons];
void uncheckmenubuttons() {
	for (int i = 0; i < nMenuButtons; i++){
		bCheckedMenuButton[i] = false;
	}
}

auto tp1 = chrono::system_clock::now();
auto tp2 = chrono::system_clock::now();

short nShade = 9600;

wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight + 1];
void screenfill() {
	for (int i = 0; i < nScreenWidth * nScreenHeight + 1; i++) screen[i] = 0;
}

int main() {
	charset CharSet;
	settings Setting;

	string sStartMenuButton = "Start";
	string sSettingsMenuButton = "Settings";
	string sExitMenuButton = "Exit";
	string sLogo1 = " $______$   $______$   $__$ $__$$______$   $______$   $______$   $__$$__$   ";
	string sLogo2 = "$/1$$==$1$ $/1$$___1$ $/1$1$/$/$/1$$___1$ $/1$$==$1$ $/1$$___1$ $/1$1_1$1$  ";
	string sLogo3 = "$1$1$$__<$$$1$1$$__1$$$1$1$1`/$$1$1$$__1$$$1$1$$__<$$$1$1___$$1$$1$1____$1$ ";
	string sLogo4 = " $1$1_1$1_1$$1$1_____1$$1$1_/$  $1$1_____1$$1$1_1$1_1$$1/1_____1$$1/1_____1$";
	string sLogo5 = "  $1/_/$/_/$ $1/_____/$ $1//$    $1/_____/$ $1/_/$/_/$ $1/_____/$ $1/_____/$";
	string sLogo6 = "   $$$$ $$$   $$$$$$$$   $$$      $$$$$$$$   $$$$ $$$   $$$$$$$$   $$$$$$$$ ";//$ equal to null

	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	screenfill();
	uncheckmenubuttons();
	bCheckedMenuButton[0] = true;
	
	while(1) {
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		fElapsedTime = elapsedTime.count();
		if (fElapsedTime < fMinElapsedTime) fMinElapsedTime = fElapsedTime;
		if (fElapsedTime > fMaxElapsedTime) fMaxElapsedTime = fElapsedTime;
		
		if (GetAsyncKeyState(0x41) & 0x8000 || GetAsyncKeyState(0x44) & 0x8000 || GetAsyncKeyState(0x45) & 0x8000 || GetAsyncKeyState(0x51) & 0x8000 || GetAsyncKeyState(0x53) & 0x8000 || GetAsyncKeyState(0x57) & 0x8000) {
			if (GetAsyncKeyState(0x53) & 0x8000 && !bCheckKeyState) {//s
				for (int i = 0; i < nMenuButtons; i++) {
					if (bCheckedMenuButton[i]) {
						bCheckedMenuButton[i] = false;
						bCheckedMenuButton[(i + 1) % nMenuButtons] = true;
						break;
					}
				}
			}
			if (GetAsyncKeyState(0x41) & 0x8000 && !bCheckKeyState) nShade -= 4;//a
			if (GetAsyncKeyState(0x51) & 0x8000 && !bCheckKeyState) nShade -= 4;//q
			if (GetAsyncKeyState(0x57) & 0x8000 && !bCheckKeyState) {//w
				for (int i = 0; i < nMenuButtons; i++) {
					if (bCheckedMenuButton[i]) {
						bCheckedMenuButton[i] = false;
						bCheckedMenuButton[(i + nMenuButtons - 1) % nMenuButtons] = true;
						break;
					}
				}
			}
			if (GetAsyncKeyState(0x44) & 0x8000 && !bCheckKeyState) nShade += 4;//d
			if (GetAsyncKeyState(0x45) & 0x8000 && !bCheckKeyState) {//e
				if (bCheckedMenuButton[0]) {
					//
				}
				if (bCheckedMenuButton[1]) {
					Setting.SbEAToggle();
				}
				if (bCheckedMenuButton[2]) {
					return 0;
				}
			}
			bCheckKeyState = true;
		}
		else bCheckKeyState = false;
		
		if (fFPSSync > (1.0f / fPreferedFPS)) {//main screen will update every (1 / fPreferedFPS) milliseconds
			if (nAnimationCount > 7) nAnimationCount = 0;
			if (Setting.GbEA()) nAnimationCount++;

			for (int y = 0; y < nScreenHeight; y++) {
				for (int x = 0; x < nScreenWidth; x++) {
					//animation and background
					if (Setting.GbEA()) screen[x + y * nScreenWidth] = CharSet.GsShade((x + y + nAnimationCount) % 8);
					else screen[x + y * nScreenWidth] = CharSet.GsShade(0);

					//logo
					if (x >= Setting.GnLPX() && x <= Setting.GnLPX() + 75) if (y >= Setting.GnLPY() && y <= Setting.GnLPY() + 5) {
						if (y == Setting.GnLPY()) if (sLogo1[x - Setting.GnLPX()] != ' ') screen[x + y * nScreenWidth] = CharSet.GcSpecChar(sLogo1[x - Setting.GnLPX()]);
						if (y == Setting.GnLPY() + 1) if (sLogo2[x - Setting.GnLPX()] != ' ') screen[x + y * nScreenWidth] = CharSet.GcSpecChar(sLogo2[x - Setting.GnLPX()]);
						if (y == Setting.GnLPY() + 2) if (sLogo3[x - Setting.GnLPX()] != ' ') screen[x + y * nScreenWidth] = CharSet.GcSpecChar(sLogo3[x - Setting.GnLPX()]);
						if (y == Setting.GnLPY() + 3) if (sLogo4[x - Setting.GnLPX()] != ' ') screen[x + y * nScreenWidth] = CharSet.GcSpecChar(sLogo4[x - Setting.GnLPX()]);
						if (y == Setting.GnLPY() + 4) if (sLogo5[x - Setting.GnLPX()] != ' ') screen[x + y * nScreenWidth] = CharSet.GcSpecChar(sLogo5[x - Setting.GnLPX()]);
						if (y == Setting.GnLPY() + 5) if (sLogo6[x - Setting.GnLPX()] != ' ') screen[x + y * nScreenWidth] = CharSet.GcSpecChar(sLogo6[x - Setting.GnLPX()]);
					}

					//borders
					if (x == 0 && y == 0) screen[x + y * nScreenWidth] = CharSet.GsBorder(7);//main upper left
					if (x == nScreenWidth - 1 && y == 0) screen[x + y * nScreenWidth] = CharSet.GsBorder(8);//main upper right
					if (x == nScreenWidth - 1 && y == nScreenHeight - 1) screen[x + y * nScreenWidth] = CharSet.GsBorder(9);//main lower right
					if (x == 0 && y == nScreenHeight - 1) screen[x + y * nScreenWidth] = CharSet.GsBorder(10);//main lower left
					if (x == 1 && y == 1) screen[x + y * nScreenWidth] = CharSet.GsBorder(1);//logo upper left
					if (x == nScreenWidth - 2 && y == 1) screen[x + y * nScreenWidth] = CharSet.GsBorder(2);//logo upper right
					if (x == nScreenWidth - 2 && y == 8) screen[x + y * nScreenWidth] = CharSet.GsBorder(3);// logo lower right
					if (x == 1 && y == 8) screen[x + y * nScreenWidth] = CharSet.GsBorder(4);//logo lower left
					if ((y == 0 || y == 9 || y == 39) && x > 0 && x < 79) screen[x + y * nScreenWidth] = CharSet.GsBorder(11);//main horizontal
					if ((x == 0 || x == 79) && y > 0 && y < 39 && y != 9) screen[x + y * nScreenWidth] = CharSet.GsBorder(12);//main vertical
					if ((y == 1 || y == 8) && x > 1 && x < 78) screen[x + y * nScreenWidth] = CharSet.GsBorder(5);//logo horizontal
					if ((x == 1 || x == 78) && y > 1 && y < 8) screen[x + y * nScreenWidth] = CharSet.GsBorder(6);//logo vertical
					if (x == 0 && y == 9) screen[x + y * nScreenWidth] = CharSet.GsBorder(16);//main left separator
					if (x == nScreenWidth - 1 && y == 9) screen[x + y * nScreenWidth] = CharSet.GsBorder(15);//main right separator

					//start menu button
					if (x >= Setting.GnSMBPX() && x <= Setting.GnSMBPX() + Setting.GnSMBL()) if (y >= Setting.GnSMBPY() && y <= Setting.GnSMBPY() + 2) {
						if (bCheckedMenuButton[0]) {//cheked
							if (x == Setting.GnSMBPX() && y == Setting.GnSMBPY()) screen[x + y * nScreenWidth] = CharSet.GsBorder(1);//uncheked
							if (x == Setting.GnSMBPX() + Setting.GnSMBL() && y == Setting.GnSMBPY()) screen[x + y * nScreenWidth] = CharSet.GsBorder(2);
							if (x == Setting.GnSMBPX() + Setting.GnSMBL() && y == Setting.GnSMBPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(3);
							if (x == Setting.GnSMBPX() && y == Setting.GnSMBPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(4);
							if (x > Setting.GnSMBPX() && x < Setting.GnSMBPX() + Setting.GnSMBL() && (y == Setting.GnSMBPY() || y == Setting.GnSMBPY() + 2)) screen[x + y * nScreenWidth] = CharSet.GsBorder(5);
							if ((x == Setting.GnSMBPX() || x == Setting.GnSMBPX() + Setting.GnSMBL()) && y > Setting.GnSMBPY() && y < Setting.GnSMBPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(6);
						} else {//uncheked
							if (x >= Setting.GnSMBPX() && x <= Setting.GnSMBPX() + Setting.GnSMBL() && y == Setting.GnSMBPY()) screen[x + y * nScreenWidth] = CharSet.GsShade(0);
							if ((x == Setting.GnSMBPX() || x == Setting.GnSMBPX() + Setting.GnSMBL()) && y == Setting.GnSMBPY() + 1) screen[x + y * nScreenWidth] = CharSet.GsShade(0);
							if (x >= Setting.GnSMBPX() && x <= Setting.GnSMBPX() + Setting.GnSMBL() && y == Setting.GnSMBPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsShade(0);
						}
						if (x > Setting.GnSMBPX() && x < Setting.GnSMBPX() + Setting.GnSMBL() && y == Setting.GnSMBPY() + 1) screen[x + y * nScreenWidth] = CharSet.GcLatin(sStartMenuButton[x - Setting.GnSMBPX() - 1]);//text
					}

					//settings menu button
					if (x >= Setting.GnSnMBPX() && x <= Setting.GnSnMBPX() + Setting.GnSnMBL()) if (y >= Setting.GnSnMBPY() && y <= Setting.GnSnMBPY() + 2) {
						if (bCheckedMenuButton[1]) {//cheked
							if (x == Setting.GnSnMBPX() && y == Setting.GnSnMBPY()) screen[x + y * nScreenWidth] = CharSet.GsBorder(1);//uncheked
							if (x == Setting.GnSnMBPX() + Setting.GnSnMBL() && y == Setting.GnSnMBPY()) screen[x + y * nScreenWidth] = CharSet.GsBorder(2);
							if (x == Setting.GnSnMBPX() + Setting.GnSnMBL() && y == Setting.GnSnMBPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(3);
							if (x == Setting.GnSnMBPX() && y == Setting.GnSnMBPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(4);
							if (x > Setting.GnSnMBPX() && x < Setting.GnSnMBPX() + Setting.GnSnMBL() && (y == Setting.GnSnMBPY() || y == Setting.GnSnMBPY() + 2)) screen[x + y * nScreenWidth] = CharSet.GsBorder(5);
							if ((x == Setting.GnSnMBPX() || x == Setting.GnSnMBPX() + Setting.GnSnMBL()) && y > Setting.GnSnMBPY() && y < Setting.GnSnMBPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(6);
						} else {//unchecked
							if (x >= Setting.GnSnMBPX() && x <= Setting.GnSnMBPX() + Setting.GnSnMBL() && y == Setting.GnSnMBPY()) screen[x + y * nScreenWidth] = CharSet.GsShade(0);
							if ((x == Setting.GnSnMBPX() || x == Setting.GnSnMBPX() + Setting.GnSnMBL()) && y == Setting.GnSnMBPY() + 1) screen[x + y * nScreenWidth] = CharSet.GsShade(0);
							if (x >= Setting.GnSnMBPX() && x <= Setting.GnSnMBPX() + Setting.GnSnMBL() && y == Setting.GnSnMBPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsShade(0);
						}
						if (x > Setting.GnSnMBPX() && x < Setting.GnSnMBPX() + Setting.GnSnMBL() && y == Setting.GnSnMBPY() + 1) screen[x + y * nScreenWidth] = CharSet.GcLatin(sSettingsMenuButton[x - Setting.GnSnMBPX() - 1]);//text
					}


					//exit menu button
					if (x >= Setting.GnEMBPX() && x <= Setting.GnEMBPX() + Setting.GnEMBL()) if (y >= Setting.GnEMBPY() && y <= Setting.GnEMBPY() + 2) {
						if (bCheckedMenuButton[2]) {//checked
							if (x == Setting.GnEMBPX() && y == Setting.GnEMBPY()) screen[x + y * nScreenWidth] = CharSet.GsBorder(1);
							if (x == Setting.GnEMBPX() + Setting.GnEMBL() && y == Setting.GnEMBPY()) screen[x + y * nScreenWidth] = CharSet.GsBorder(2);
							if (x == Setting.GnEMBPX() + Setting.GnEMBL() && y == Setting.GnEMBPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(3);
							if (x == Setting.GnEMBPX() && y == Setting.GnEMBPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(4);
							if (x > Setting.GnEMBPX() && x < Setting.GnEMBPX() + Setting.GnEMBL() && (y == Setting.GnEMBPY() || y == Setting.GnEMBPY() + 2)) screen[x + y * nScreenWidth] = CharSet.GsBorder(5);
							if ((x == Setting.GnEMBPX() || x == Setting.GnEMBPX() + Setting.GnEMBL()) && y > Setting.GnEMBPY() && y < Setting.GnEMBPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(6);
						} else {//unchecked
							if (x >= Setting.GnEMBPX() && x <= Setting.GnEMBPX() + Setting.GnEMBL() && y == Setting.GnEMBPY()) screen[x + y * nScreenWidth] = CharSet.GsShade(0);
							if ((x == Setting.GnEMBPX() || x == Setting.GnEMBPX() + Setting.GnEMBL()) && y == Setting.GnEMBPY() + 1) screen[x + y * nScreenWidth] = CharSet.GsShade(0);
							if (x >= Setting.GnEMBPX() && x <= Setting.GnEMBPX() + Setting.GnEMBL() && y == Setting.GnEMBPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsShade(0);
						}
						if (x > Setting.GnEMBPX() && x < Setting.GnEMBPX() + Setting.GnEMBL() && y == Setting.GnEMBPY() + 1) screen[x + y * nScreenWidth] = CharSet.GcLatin(sExitMenuButton[x - Setting.GnEMBPX() - 1]);//text
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
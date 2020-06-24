#include <Windows.h>
#include <string>
#include <chrono>
#include <tchar.h>
#include <strsafe.h>

#include "settings.h"
#include "charset.h"
#include "board.h"

using namespace std;

const int nMenuButtons = 3;

int nScreenWidth = 80;
int nScreenHeight = 40;
int nAnimationCount = 0;
int nSelectedButton = 0;
int nSelectedBoardPos[2];
int nAction;//1-start menu; 2-game starts; 3-game ends; 4-settings menu

float fPreferedFPS = 15.0f;//screen updating speed

float fMinElapsedTime = 1.0f;
float fMaxElapsedTime = 0.0f;
float fElapsedTime;
float fFPSSync = 0.0f;
float fFPSCount = 0.0f;

bool bCheckKeyState = false;
bool bCheckedMenuButton[nMenuButtons];


auto tp1 = chrono::system_clock::now();
auto tp2 = chrono::system_clock::now();

short nShade = 1;

wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight + 1];

void screenfill() {
	for (int i = 0; i < nScreenWidth * nScreenHeight + 1; i++) screen[i] = 0;
}

void startaction() {
	for (int i = 0; i < nMenuButtons; i++) bCheckedMenuButton[i] = false;
	nSelectedBoardPos[0] = 0;
	nSelectedBoardPos[1] = 0;
	nAction = 1;
	bCheckedMenuButton[0] = true;
}


int main() {
	charset CharSet;
	settings Setting;
	boardlogic Board;

	string sStartMenuButton = "Start";
	string sSettingsMenuButton = "Settings";
	string sExitMenuButton = "Quit";
	string sFirstLoad = "Press E";
	string sScore = "Black   White  ";
	string sHorizontalNumeration = " A B C D E F G H";
	string sVerticalNumeration = " 1 2 3 4 5 6 7 8";

	string sLogo1 = " $______$   $______$   $__$ $__$$______$   $______$   $______$   $__$$__$   ";
	string sLogo2 = "$/1$$==$1$ $/1$$___1$ $/1$1$/$/$/1$$___1$ $/1$$==$1$ $/1$$___1$ $/1$1_1$1$  ";
	string sLogo3 = "$1$1$$__<$$$1$1$$__1$$$1$1$1`/$$1$1$$__1$$$1$1$$__<$$$1$1___$$1$$1$1____$1$ ";
	string sLogo4 = " $1$1_1$1_1$$1$1_____1$$1$1_/$  $1$1_____1$$1$1_1$1_1$$1/1_____1$$1/1_____1$";
	string sLogo5 = "  $1/_/$/_/$ $1/_____/$ $1//$    $1/_____/$ $1/_/$/_/$ $1/_____/$ $1/_____/$";
	string sLogo6 = "   $$$$ $$$   $$$$$$$$   $$$      $$$$$$$$   $$$$ $$$   $$$$$$$$   $$$$$$$$ ";//$ equal to null

	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	//start parametres
	screenfill();
	startaction();
	
	while(1) {
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		fElapsedTime = elapsedTime.count();
		if (fElapsedTime < fMinElapsedTime) fMinElapsedTime = fElapsedTime;
		if (fElapsedTime > fMaxElapsedTime) fMaxElapsedTime = fElapsedTime;
		
		if (GetAsyncKeyState(0x41) & 0x8000 || GetAsyncKeyState(0x44) & 0x8000 || GetAsyncKeyState(0x45) & 0x8000 || GetAsyncKeyState(0x51) & 0x8000 || GetAsyncKeyState(0x53) & 0x8000 || GetAsyncKeyState(0x57) & 0x8000) {
			if (GetAsyncKeyState(0x57) & 0x8000 && !bCheckKeyState) {//w
				switch (nAction)
				{
				case 1: {
					for (int i = 0; i < nMenuButtons; i++) {
						if (bCheckedMenuButton[i]) {
							bCheckedMenuButton[i] = false;
							bCheckedMenuButton[(i + nMenuButtons - 1) % nMenuButtons] = true;
							break;
						}
					}
				}
				case 2: {
					if (nSelectedBoardPos[1] > 0) nSelectedBoardPos[1]--;
					break;
				}
				default: break;
				}
			}
			if (GetAsyncKeyState(0x53) & 0x8000 && !bCheckKeyState) {//s
				switch (nAction)
				{
				case 1: {
					for (int i = 0; i < nMenuButtons; i++) {
						if (bCheckedMenuButton[i]) {
							bCheckedMenuButton[i] = false;
							bCheckedMenuButton[(i + 1) % nMenuButtons] = true;
							break;
						}
					}
				}
				case 2: {
					if (nSelectedBoardPos[1] < Board.GnBS() - 1) nSelectedBoardPos[1]++;
					break;
				}
				default: break;
				}
			}
			if (GetAsyncKeyState(0x41) & 0x8000 && !bCheckKeyState) {//a
				switch (nAction)
				{
				case 2: {
					if (nSelectedBoardPos[0] > 0) nSelectedBoardPos[0]--;
					break;
				}
				default: break;
				}
			}
			if (GetAsyncKeyState(0x44) & 0x8000 && !bCheckKeyState) {//d
				switch (nAction)
				{
				case 2: {
					if (nSelectedBoardPos[0] < Board.GnBS() - 1) nSelectedBoardPos[0]++;
					break;
				}
				default: break;
				}
			}
			if (GetAsyncKeyState(0x45) & 0x8000 && !bCheckKeyState) {//e
				switch (nAction)
				{
				case 1: {//start menu
					if (bCheckedMenuButton[0]) {
						Board.vBoardReset();
						nSelectedBoardPos[0] = 0;
						nSelectedBoardPos[1] = 0;
						nAction = 2;
					}
					if (bCheckedMenuButton[1]) {
						Setting.SbEAToggle();
					}
					if (bCheckedMenuButton[2]) {
						return 0;
					}
					break;
				}
				case 2: {//game in process
					Board.SnBU(nSelectedBoardPos[0], nSelectedBoardPos[1]);
					if (!Board.GbIP()) {
						nAction = 3;
					}
					break;
				}
				case 3: {//game ended
					
					break;
				}
				case 4: {//settings menu

					break;
				}
				default: break;//first load
				}
			}
			if (GetAsyncKeyState(0x51) & 0x8000 && !bCheckKeyState) {//q
				switch (nAction)
				{
				case 2: {
					nAction = 1;
					Board.vClearMem();
					break;
				}
				case 3: {
					nAction = 1;
					Board.vClearMem();
					break;
				}
				default: break;
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
					{
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
					}

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

					//board
					if (nAction == 2 || nAction == 3) if (x >= Setting.GnBPX() && x <= Setting.GnBPX() + Board.GnBS() * 2) if (y >= Setting.GnBPY() && y <= Setting.GnBPY() + Board.GnBS() * 2) {
						if (x == Setting.GnBPX() && y == Setting.GnBPY()) screen[x + y * nScreenWidth] = CharSet.GsBorder(1);
						if (x == Setting.GnBPX() + Board.GnBS() * 2 && y == Setting.GnBPY()) screen[x + y * nScreenWidth] = CharSet.GsBorder(2);
						if (x == Setting.GnBPX() + Board.GnBS() * 2 && y == Setting.GnBPY() + Board.GnBS() * 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(3);
						if (x == Setting.GnBPX() && y == Setting.GnBPY() + Board.GnBS() * 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(4);
						if (x > Setting.GnBPX() && x < Setting.GnBPX() + Board.GnBS() * 2 && (x - Setting.GnBPX()) % 2 == 0 && y == Setting.GnBPY()) screen[x + y * nScreenWidth] = CharSet.GsBorder(22);
						if (x == Setting.GnBPX() && y > Setting.GnBPY() && y < Setting.GnBPY() + Board.GnBS() * 2 && (y - Setting.GnBPY()) % 2 == 0) screen[x + y * nScreenWidth] = CharSet.GsBorder(24);
						if (x == Setting.GnBPX() + Board.GnBS() * 2 && y > Setting.GnBPY() && y < Setting.GnBPY() + Board.GnBS() * 2 && (y - Setting.GnBPY()) % 2 == 0) screen[x + y * nScreenWidth] = CharSet.GsBorder(23);
						if (x > Setting.GnBPX() && x < Setting.GnBPX() + Board.GnBS() * 2 && (x - Setting.GnBPX()) % 2 == 0 && y == Setting.GnBPY() + Board.GnBS() * 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(21);
						if ((x - Setting.GnBPX()) % 2 == 0 && (y - Setting.GnBPY()) % 2 == 1) screen[x + y * nScreenWidth] = CharSet.GsBorder(6);
						if ((x - Setting.GnBPX()) % 2 == 1 && (y - Setting.GnBPY()) % 2 == 0) screen[x + y * nScreenWidth] = CharSet.GsBorder(5);
						if (x > Setting.GnBPX() && x < Setting.GnBPX() + Board.GnBS() * 2 && (x - Setting.GnBPX()) % 2 == 0 && y > Setting.GnBPY() && y < Setting.GnBPY() + Board.GnBS() * 2 && (y - Setting.GnBPY()) % 2 == 0) screen[x + y * nScreenWidth] = CharSet.GsBorder(25);
						if ((x - Setting.GnBPX()) % 2 == 1 && (y - Setting.GnBPY()) % 2 == 1 && Board.GnBU((x - Setting.GnBPX()) / 2, (y - Setting.GnBPY()) / 2) == 0) screen[x + y * nScreenWidth] = 0;
						if ((x - Setting.GnBPX()) % 2 == 1 && (y - Setting.GnBPY()) % 2 == 1 && Board.GnBU((x - Setting.GnBPX()) / 2, (y - Setting.GnBPY()) / 2) == 1) screen[x + y * nScreenWidth] = 1;
						if ((x - Setting.GnBPX()) % 2 == 1 && (y - Setting.GnBPY()) % 2 == 1 && Board.GnBU((x - Setting.GnBPX()) / 2, (y - Setting.GnBPY()) / 2) == 2) screen[x + y * nScreenWidth] = 2;
						if ((x - Setting.GnBPX()) % 2 == 1 && (y - Setting.GnBPY()) % 2 == 1 && Board.GnBU((x - Setting.GnBPX()) / 2, (y - Setting.GnBPY()) / 2) == 3) screen[x + y * nScreenWidth] = 7;
						if (nAction == 2) if ((x - Setting.GnBPX()) % 2 == 1 && (y - Setting.GnBPY()) % 2 == 1 && nSelectedBoardPos[0] == (x - Setting.GnBPX()) / 2 && nSelectedBoardPos[1] == (y - Setting.GnBPY()) / 2) screen[x + y * nScreenWidth] = CharSet.GsShade(4);
					}

					//score
					if (nAction == 2 || nAction == 3) if (x >= Setting.GnSPX() && x <= Setting.GnSPX() + Setting.GnSL()) if (y >= Setting.GnSPY() && y <= Setting.GnSPY() + 2) {
						if (Board.GbT()) {
							if (x == Setting.GnSPX() && y == Setting.GnSPY()) screen[x + y * nScreenWidth] = CharSet.GsBorder(7);
							if (x == Setting.GnSPX() && y == Setting.GnSPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(10);
							if (x == Setting.GnSPX() + Setting.GnSL() && y == Setting.GnSPY()) screen[x + y * nScreenWidth] = CharSet.GsBorder(2);
							if (x == Setting.GnSPX() + Setting.GnSL() && y == Setting.GnSPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(3);
							if (x > Setting.GnSPX() && x < Setting.GnSPX() + Setting.GnSL() / 2 && (y == Setting.GnSPY() || y == Setting.GnSPY() + 2)) screen[x + y * nScreenWidth] = CharSet.GsBorder(11);
							if (x > Setting.GnSPX() + Setting.GnSL() / 2 && x < Setting.GnSPX() + Setting.GnSL() && (y == Setting.GnSPY() || y == Setting.GnSPY() + 2)) screen[x + y * nScreenWidth] = CharSet.GsBorder(5);
							if (x == Setting.GnSPX() && y == Setting.GnSPY() + 1) screen[x + y * nScreenWidth] = CharSet.GsBorder(12);
							if (x == Setting.GnSPX() + Setting.GnSL() && y == Setting.GnSPY() + 1) screen[x + y * nScreenWidth] = CharSet.GsBorder(6);
						}
						else {
							if (x == Setting.GnSPX() && y == Setting.GnSPY()) screen[x + y * nScreenWidth] = CharSet.GsBorder(1);
							if (x == Setting.GnSPX() && y == Setting.GnSPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(4);
							if (x == Setting.GnSPX() + Setting.GnSL() && y == Setting.GnSPY()) screen[x + y * nScreenWidth] = CharSet.GsBorder(8);
							if (x == Setting.GnSPX() + Setting.GnSL() && y == Setting.GnSPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(9);
							if (x > Setting.GnSPX() && x < Setting.GnSPX() + Setting.GnSL() / 2 && (y == Setting.GnSPY() || y == Setting.GnSPY() + 2)) screen[x + y * nScreenWidth] = CharSet.GsBorder(5);
							if (x > Setting.GnSPX() + Setting.GnSL() / 2 && x < Setting.GnSPX() + Setting.GnSL() && (y == Setting.GnSPY() || y == Setting.GnSPY() + 2)) screen[x + y * nScreenWidth] = CharSet.GsBorder(11);
							if (x == Setting.GnSPX() && y == Setting.GnSPY() + 1) screen[x + y * nScreenWidth] = CharSet.GsBorder(6);
							if (x == Setting.GnSPX() + Setting.GnSL() && y == Setting.GnSPY() + 1) screen[x + y * nScreenWidth] = CharSet.GsBorder(12);
						}
						if (x == Setting.GnSPX() + Setting.GnSL() / 2) {
							if (y == Setting.GnSPY()) screen[x + y * nScreenWidth] = CharSet.GsBorder(27);
							if (y == Setting.GnSPY() + 1) screen[x + y * nScreenWidth] = CharSet.GsBorder(12);
							if (y == Setting.GnSPY() + 2) screen[x + y * nScreenWidth] = CharSet.GsBorder(28);
						}
						if (x > Setting.GnSPX() && x < Setting.GnSPX() + Setting.GnSL() && y == Setting.GnSPY() + 1) if (sScore[x - Setting.GnSPX() - 1] != ' ') screen[x + y * nScreenWidth] = CharSet.GcLatin(sScore[x - Setting.GnSPX() - 1]);
						if (y == Setting.GnSPY() + 1) {
							if (x == Setting.GnSPX() + 6) screen[x + y * nScreenWidth] = (Board.GnBUA() - Board.GnBUA() % 10) / 10 + 48;
							if (x == Setting.GnSPX() + 7) screen[x + y * nScreenWidth] = Board.GnBUA() % 10 + 48;
							if (x == Setting.GnSPX() + 14) screen[x + y * nScreenWidth] = (Board.GnWUA() - Board.GnWUA() % 10) / 10 + 48;
							if (x == Setting.GnSPX() + 15) screen[x + y * nScreenWidth] = Board.GnWUA() % 10 + 48;
						}
					}

					//numeration
					if (nAction == 2 || nAction == 3) {
						if (x >= Setting.GnBPX() && x < Setting.GnBPX() + Board.GnBS() * 2 && y == Setting.GnBPY() - 1) if (sHorizontalNumeration[x - Setting.GnBPX()] != ' ') screen[x + y * nScreenWidth] = CharSet.GcLatin(sHorizontalNumeration[x - Setting.GnBPX()]);
						if (x == Setting.GnBPX() - 1 && y >= Setting.GnBPY() && y < Setting.GnBPY() + Board.GnBS() * 2) if (sVerticalNumeration[y - Setting.GnBPY()] != ' ') screen[x + y * nScreenWidth] = CharSet.GcNumber(sVerticalNumeration[y - Setting.GnBPY()]);
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
		StringCchPrintf(title, MAX_PATH, TEXT("FPS = %3.2f | FPS_Max = %3.2f | FPS_Min = %3.2f | FPS_Sync=%3.2f | TEST = %1.0f"), 1.0f / fElapsedTime, 1.0f / fMinElapsedTime, 1.0f / fFPSCount, 1.0f / fMaxElapsedTime);
		SetConsoleTitle(title);
	}
}

/*

swprintf(screen, 80, L"FPS=%3.2f FPS_Max=%3.2f FPS_Min=%3.2f Hesh=%1.0f", 1.0f / fElapsedTime, 1.0f / fMinElapsedTime, 1.0f / fMaxElapsedTime, (float)nShade);

*/
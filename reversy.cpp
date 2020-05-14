﻿#include <Windows.h>
#include <string>
#include <chrono>
#include "menus.h"

using namespace std;

int nScreenWidth = 80;
int nScreenHeight = 40;

float fMinElapsedTime = 1.0f;
float fMaxElapsedTime = 0.0f;
float fElapsedTime;

bool bCheckKeyState = false;

auto tp1 = chrono::system_clock::now();
auto tp2 = chrono::system_clock::now();
short nShade = 0x2588;

wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight + 1];

int main() {
	menus Menus;
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	while(1) {
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		fElapsedTime = elapsedTime.count();
		if (fElapsedTime < fMinElapsedTime) fMinElapsedTime = fElapsedTime;
		if (fElapsedTime > fMaxElapsedTime) fMaxElapsedTime = fElapsedTime;

		if (GetAsyncKeyState(0x41) & 0x8000 || GetAsyncKeyState(0x44) & 0x8000) {
			if (GetAsyncKeyState(0x41) & 0x8000 && !bCheckKeyState) nShade += 1;
			if (GetAsyncKeyState(0x44) & 0x8000 && !bCheckKeyState) nShade -= 1;
			bCheckKeyState = true;
		}
		else bCheckKeyState = false;

		for (int y = 0; y < nScreenWidth; y++) {
			for (int x = 0; x < nScreenHeight; x++) {
				screen[x + y * nScreenHeight] = nShade;
			}
		}
		swprintf(screen, 80, L"FPS=%3.2f FPS_Max=%3.2f FPS_Min=%3.2f Hesh=%1.0f", 1.0f / fElapsedTime, 1.0f / fMinElapsedTime, 1.0f / fMaxElapsedTime, (float)nShade);
		screen[nScreenWidth * nScreenHeight] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
	}
	return 0;
}
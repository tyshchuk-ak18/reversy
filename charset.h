#include <string>
class charset {
public:
	int GcSpecChar(char buffer) {//for logo
		switch (buffer)
		{
		case '_': {
			return 95;
			break;
		}
		case '/': {
			return 47;
			break;
		}
		case '`': {
			return 39;
			break;
		}
		case '=': {
			return 61;
			break;
		}
		case '>': {
			return 62;
			break;
		}
		case '<': {
			return 60;
			break;
		}
		case '1': {
			return 92;
			break;
		}
		case '$': {
			return 0;
			break;
		}
		default: {
			return 63;//error
			break;
		}
		}
	}

	int GcNumber(wchar_t buffer) {//numbers
		switch (buffer) {
		case '0': {
			return 48;
			break;
		}
		case '1': {
			return 49;
			break;
		}
		case '2': {
			return 50;
			break;
		}
		case '3': {
			return 51;
			break;
		}
		case '4': {
			return 52;
			break;
		}
		case '5': {
			return 53;
			break;
		}
		case '6': {
			return 54;
			break;
		}
		case '7': {
			return 55;
			break;
		}
		case '8': {
			return 56;
			break;
		}
		case '9': {
			return 57;
			break;
		}
		default: {
			return 63;//error
			break;
		}
		}
	}

	int GcLatinUpper(wchar_t buffer) {
		switch (buffer) {
		case 'A': {
			return 65;
			break;
		}
		default: {
			return 63;
			break;
		}
		}
	}

	int GcLatinLower(wchar_t buffer) {
		switch (buffer) {
		case 'a': {
			return 97;
			break;
		}
		default: {
			return 63;//error
			break;
		}
		}
	}

	int GcCyrillic(wchar_t buffer) {
		switch (buffer) {
		default: {
			return 63;//error
			break;
		}
		}
	}

	int GsShade(int i) {
		switch (i) {
		case 0: {
			return 0;//black
			break;
		}
		case 1: {
			return 9617;//dark grey
			break;
		}
		case 2: {
			return 9618;//grey
			break;
		}
		case 3: {
			return 9619;//light grey
			break;
		}
		case 4: {
			return 9608;//white
			break;
		}
		case 5: {
			return 9619;//light grey
			break;
		}
		case 6: {
			return 9618;//grey
			break;
		}
		case 7: {
			return 9617;//dark grey
			break;
		}
		default: {
			return 63;//error
			break;
		}
		}
	}

	int GsBorder(int i) {
		switch (i) {
		case 1: {
			return 9484;// upper left slim
			break;
		}
		case 2: {
			return 9488;// upper right slim
			break;
		}
		case 3: {
			return 9496;// lower right slim
			break;
		}
		case 4: {
			return 9492;// lower left slim
			break;
		}
		case 5: {
			return 9472;//horizontal slim
			break;
		}
		case 6: {
			return 9474;//vertical slim
			break;
		}
		case 7: {
			return 9556;//upper left thick
			break;
		}
		case 8: {
			return 9559;//upper right thick
			break;
		}
		case 9: {
			return 9565;//lower right thick
			break;
		}
		case 10: {
			return 9562;//lower left thick
			break;
		}
		case 11: {
			return 9552;//horizontal thick
			break;
		}
		case 12: {
			return 9553;//vertical thick
			break;
		}
		case 13: {
			return 9577;//horizontal to up thick
			break;
		}
		case 14: {
			return 9574;//horizontal to down thick
			break;
		}
		case 15: {
			return 9571;//vertical to left thick
			break;
		}
		case 16: {
			return 9568;//vertical to right thick
			break;
		}
		default: {
			return 63;//error
			break;
		}
		}
	}
};
/*
	0x1 = black units;
	0x2 = white units;
	0x22, 0x95 = lower dephis _;
	0x33 = exclamation mark !;
	0x34 = double quotes ";
	0x35 = hesh #;
	0x36 = dollar $;
	0x37 = percent %;
	0x38 = and &;
	0x39, 0x96 = quote ';
	0x40 = opened bracket, then closed braket;
	0x44 = coma ,;
	0x45 = minus -;
	0x46 = dot .;
	0x47 = /; *(4)
	0x48 = 0, then: numbers;
	0x58 = double dot :, then comadot;
	0x60 = smaller <;
	0x61 = equal =;
	0x62 = greater >;
	0x64 = dog @;
	0x65 = A, then: uppercase letters;
	0x92 = \; *(1)
	0x97 = a, then: lowercase letters;
	0x124 = vertical line |;
	0x2588 = shade block (darkest);	9608
	0x2593 = shade block (darker);	9619
	0x2592 = shade block (dark);	9618
	0x2591 = shade block (grey);	9617
*/
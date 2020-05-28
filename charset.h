#include <string>
class charset {
public:
	int GcSpecChar(char buffer) {
		int ascii = 0;
		if (buffer == '_') return 95;
		else if (buffer == '/') return 47;
		else if (buffer == '`') return 39;
		else if (buffer == '=') return 61;
		else if (buffer == '>') return 62;
		else if (buffer == '<') return 60;
		else if (buffer == '1') return 92;
		else if (buffer == '$') return 0;
		else return ascii;
	}
	int GcNumber(wchar_t buffer) {
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
		default:
			return 63;
			break;
		}
	}
	int GcLatin(wchar_t buffer) {
		int ascii = 0x0;
		return ascii;
	}
	int GcCyrillic(wchar_t buffer) {
		int ascii = 0x0;
		return ascii;
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
		default:
			return 63;//error
			break;
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
			return 9472;//horizontal line slim
			break;
		}
		case 6: {
			return 9474;//vertical line slim
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
		default: {
			return 0;
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
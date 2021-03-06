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

	int GcLatin(wchar_t buffer) {
		switch (buffer) {
		case '$': {
			break;
		}
		case 'A': {
			return 65;
			break;
		}
		case 'B': {
			return 66;
			break;
		}
		case 'C': {
			return 67;
			break;
		}
		case 'D': {
			return 68;
			break;
		}
		case 'E': {
			return 69;
			break;
		}
		case 'F': {
			return 70;
			break;
		}
		case 'G': {
			return 71;
			break;
		}
		case 'H': {
			return 72;
			break;
		}
		case 'Q': {
			return 81;
			break;
		}
		case 'S': {
			return 83;
			break;
		}
		case 'W': {
			return 87;
			break;
		}
		case 'a': {
			return 97;
			break;
		}
		case 'c': {
			return 99;
			break;
		}
		case 'e': {
			return 101;
			break;
		}
		case 'g': {
			return 103;
			break;
		}
		case 'h': {
			return 104;
			break;
		}
		case 'i': {
			return 105;
			break;
		}
		case 'k': {
			return 107;
			break;
		}
		case 'l': {
			return 108;
			break;
		}
		case 'n': {
			return 110;
			break;
		}
		case 'r': {
			return 114;
			break;
		}
		case 's': {
			return 115;
			break;
		}
		case 't': {
			return 116;
			break;
		}
		case 'u': {
			return 117;
			break;
		}
		case 'x': {
			return 120;
			break;
		}
		default: {
			return 63;
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
		case 17: {
			return 9600;//upper block
			break;
		}
		case 18: {
			return 9604;//lower block
			break;
		}
		case 19: {
			return 9612;//left block
			break;
		}
		case 20: {
			return 9616;//right block
			break;
		}
		case 21: {
			return 9524;//horizontal to up slim
			break;
		}
		case 22: {
			return 9516;//horizontal to down slim
			break;
		}
		case 23: {
			return 9508;//vertical to left slim
			break;
		}
		case 24: {
			return 9500;//vertical to right slim
			break;
		}
		case 25: {
			return 9532;//crosshair slim
			break;
		}
		case 26: {
			return 9580;//crosshair thick
			break;
		}
		case 27: {
			return 9574;//t-like to down thick
			break;
		}
		case 28: {
			return 9577;//t-like to up thick
			break;
		}
		default: {
			return 63;//error
			break;
		}
		}
	}
};
#include <string>
class charset {
public:
	int FcSpecChar(char buffer) {
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
	int FcNumber(wchar_t buffer) {
		int ascii = 0x0;
		return ascii;
	}
	int FcLatin(wchar_t buffer) {
		int ascii = 0x0;
		return ascii;
	}
	int FcCyrillic(wchar_t buffer) {
		int ascii = 0x0;
		return ascii;
	}
	int FsShade(int i) {
		if (i == 1) return 9617;
		else if (i == 2) return 9618;
		else if (i == 3) return 9619;
		else if (i == 4) return 9608;
		else if (i == 5) return 9619;
		else if (i == 6) return 9618;
		else if (i == 7) return 9617;
		else return 0x0;
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
	0x172 = 
	0x2588 = shade block (darkest);	9608
	0x2593 = shade block (darker);	9619
	0x2592 = shade block (dark);	9618
	0x2591 = shade block (grey);	9617

*/
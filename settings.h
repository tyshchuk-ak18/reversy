class settings {
private:
	int nFirstButtonPosX = 5;
	int nFirstButtonPosY = 15;
	int nLogoPosX = 2;
	int nLogoPosY = 2;

	bool bEnableAnimation = true;
public:
	int GnFBPX() {
		return nFirstButtonPosX;
	}
	int GnFBPY() {
		return nFirstButtonPosY;
	}
	int GnLPX() {
		return nLogoPosX;
	}
	int GnLPY() {
		return nLogoPosY;
	}

	bool GbEA() {
		return bEnableAnimation;
	}
};
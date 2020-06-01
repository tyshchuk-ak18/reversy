class settings {
private:
	int nStartMenuButton[3] = { 5, 15, 6 };
	int nExitMenuButton[3] = { 5, 19, 5 };
	int nLogoPosX = 2;
	int nLogoPosY = 2;

	bool bEnableAnimation = false;

public:
	int GnSMBPX() {
		return nStartMenuButton[0];
	}
	int GnSMBPY() {
		return nStartMenuButton[1];
	}
	int GnSMBL() {
		return nStartMenuButton[2];
	}

	int GnEMBPX() {
		return nExitMenuButton[0];
	}
	int GnEMBPY() {
		return nExitMenuButton[1];
	}
	int GnEMBL() {
		return nExitMenuButton[2];
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
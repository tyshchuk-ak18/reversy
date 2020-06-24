class settings {
private:
	int nStartMenuButton[3] = { 2, 12, 6 };
	int nSettingsMenuButton[3] = { 2, 17, 9 };
	int nExitMenuButton[3] = { 2, 22, 5 };
	int nLogoPos[2] = { 2, 2 };
	int nBoardPos[2] = { 60, 12 };
	int nScorePos[3] = { 60, 29, 16 };

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

	int GnSnMBPX() {
		return nSettingsMenuButton[0];
	}
	int GnSnMBPY() {
		return nSettingsMenuButton[1];
	}
	int GnSnMBL() {
		return nSettingsMenuButton[2];
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
		return nLogoPos[0];
	}
	int GnLPY() {
		return nLogoPos[1];
	}

	int GnBPX() {
		return nBoardPos[0];
	}
	int GnBPY() {
		return nBoardPos[1];
	}

	int GnSPX() {
		return nScorePos[0];
	}
	int GnSPY() {
		return nScorePos[1];
	}
	int GnSL() {
		return nScorePos[2];
	}

	bool GbEA() {
		return bEnableAnimation;
	}

	void SbEAToggle() {
		bool i = true;
		if (bEnableAnimation && i) {
			bEnableAnimation = false;
			i = false;
		}
		if (!bEnableAnimation && i) {
			bEnableAnimation = true;
			i = false;
		}
	}
};
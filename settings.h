class settings {
private:
	int nStartMenuButton[3] = { 5, 15, 6 };
	int nSettingsMenuButton[3] = { 5, 19, 9 };
	int nExitMenuButton[3] = { 5, 23, 5 };
	int nLogoPos[2] = { 2, 2 };

	bool bEnableAnimation = true;

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
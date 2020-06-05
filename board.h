class boardlogic {
private:
	const int nBoardSize = 8;

	int** board = new int*[nBoardSize];
	int nUnitsAmount[2];

	bool bTurn;//true-black; false-white

public:
	const int GnBS() {
		return nBoardSize;
	}
	int GnBU(int x, int y) {
		return board[y][x];
	}
	int GnBUA() {
		return nUnitsAmount[0];
	}
	int GnWUA() {
		return nUnitsAmount[1];
	}

	void vBoardReset() {//1-black; 2-white; 3-available to set
		for (int i = 0; i < nBoardSize; i++) board[i] = new int[nBoardSize];
		for (int j = 0; j < nBoardSize; j++) for (int i = 0; i < nBoardSize; i++) board[j][i] = 0;
		board[3][3] = 1;
		board[3][4] = 2;
		board[4][3] = 2;
		board[4][4] = 1;
		bTurn = true;
		vCheckAvailablePlace();
	}
	void vClearMem() {
		for (int i = 0; i < nBoardSize; i++) delete[] board[i];
	}

	void SnBU(int x, int y) {
		bool i = true;
		if (bTurn && i && board[y][x] == 3) {
			bTurn = false;
			board[y][x] = 1;
			i = false;
		}
		if (!bTurn && i && board[y][x] == 3) {
			bTurn = true;
			board[y][x] = 2;
			i = false;
		}
		vCheckAvailablePlace();
	}

	void vFlipUnits() {

	}

	void vCheckAvailablePlace() {
		nUnitsAmount[0] = 0;
		nUnitsAmount[1] = 0;
		for (int j = 0; j < nBoardSize; j++) for (int i = 0; i < nBoardSize; i++) {
			if (board[j][i] == 1) nUnitsAmount[0]++;//score of black
			if (board[j][i] == 2) nUnitsAmount[1]++;//score of white
			if (board[j][i] == 3) board[j][i] = 0;
		}
		if (bTurn) for (int k = 0; k < nUnitsAmount[0]; k++) {
			int n = 0, x, y;
			for (int j = 0; j < nBoardSize; j++) {
				for (int i = 0; i < nBoardSize; i++) {
					if (n == k) { x = i; y = j; }//search for each black unit
					if (board[j][i] == 1) n++;
				}
			}

			for (int i = x + 1; i < nBoardSize - 2 && board[y][i] == 2; i++) {//search for last another to right
				if (board[y][i + 1] == 0) {
					board[y][i + 1] = 3;
					break;
				}
			}
			for (int i = x - 1; i > 2 && board[y][i] == 2; i--) {//search for last another to left
				if (board[y][i - 1] == 0) {
					board[y][i - 1] = 3;
					break;
				}
			}
			for (int j = y + 1; j < nBoardSize - 2 && board[j][x] == 2; j++) {//search for last another to down
				if (board[j + 1][x] == 0) {
					board[j + 1][x] = 3;
					break;
				}
			}
			for (int j = y - 1; j > 2 && board[j][x] == 2; j--) {//search for last another to up
				if (board[j - 1][x] == 0) {
					board[j - 1][x] = 3;
					break;
				}
			}

			for (int i = 0; i + x + 1 < nBoardSize - 2 && i + y + 1 < nBoardSize - 2 && board[i + y + 1][i + x + 1] == 2; i++) {//search for last another to right-down
				if (board[i + y + 2][i + x + 2] == 0) {
					board[i + y + 2][i + x + 2] = 3;
					break;
				}
			}
			for (int i = 0; -i + x - 1 > 2 && i + y + 1 < nBoardSize - 2 && board[i + y + 1][-i + x - 1] == 2; i++) {//search for last another to left-down
				if (board[i + y + 2][-i + x - 2] == 0) {
					board[i + y + 2][-i + x - 2] = 3;
					break;
				}
			}
			for (int i = 0; i + x - 1 > 2 && i + y - 1 > 2 && board[i + y - 1][i + x - 1] == 2; i--) {//search for last another to left-up
				if (board[i + y - 2][i + x - 2] == 0) {
					board[i + y - 2][i + x - 2] = 3;
					break;
				}
			}
			for (int i = 0; i + x + 1 < nBoardSize - 2 && -i + y - 1 > 2 && board[-i + y - 1][i + x + 1] == 2; i++) {//search for last another to left-up
				if (board[-i + y - 2][i + x + 2] == 0) {
					board[-i + y - 2][i + x + 2] = 3;
					break;
				}
			}
		}

		if (!bTurn) for (int k = 0; k < nUnitsAmount[0]; k++) {
			int n = 0, x, y;
			for (int j = 0; j < nBoardSize; j++) {
				for (int i = 0; i < nBoardSize; i++) {
					if (n == k) { x = i; y = j; }//search for each white unit
					if (board[j][i] == 2) n++;
				}
			}

			for (int i = x + 1; i < nBoardSize - 2 && board[y][i] == 1; i++) {//search for last another to right
				if (board[y][i + 1] == 0) {
					board[y][i + 1] = 3;
					break;
				}
			}
			for (int i = x - 1; i > 2 && board[y][i] == 1; i--) {//search for last another to left
				if (board[y][i - 1] == 0) {
					board[y][i - 1] = 3;
					break;
				}
			}
			for (int j = y + 1; j < nBoardSize - 2 && board[j][x] == 1; j++) {//search for last another to down
				if (board[j + 1][x] == 0) {
					board[j + 1][x] = 3;
					break;
				}
			}
			for (int j = y - 1; j > 2 && board[j][x] == 1; j--) {//search for last another to up
				if (board[j - 1][x] == 0) {
					board[j - 1][x] = 3;
					break;
				}
			}

			for (int i = 0; i + x + 1 < nBoardSize - 2 && i + y + 1 < nBoardSize - 2 && board[i + y + 1][i + x + 1] == 1; i++) {//search for last another to right-down
				if (board[i + y + 2][i + x + 2] == 0) {
					board[i + y + 2][i + x + 2] = 3;
					break;
				}
			}
			for (int i = 0; -i + x - 1 > 2 && i + y + 1 < nBoardSize - 2 && board[i + y + 1][-i + x - 1] == 1; i++) {//search for last another to left-down
				if (board[i + y + 2][-i + x - 2] == 0) {
					board[i + y + 2][-i + x - 2] = 3;
					break;
				}
			}
			for (int i = 0; i + x - 1 > 2 && i + y - 1 > 2 && board[i + y - 1][i + x - 1] == 1; i--) {//search for last another to left-up
				if (board[i + y - 2][i + x - 2] == 0) {
					board[i + y - 2][i + x - 2] = 3;
					break;
				}
			}
			for (int i = 0; i + x + 1 < nBoardSize - 2 && -i + y - 1 > 2 && board[-i + y - 1][i + x + 1] == 1; i++) {//search for last another to left-up
				if (board[-i + y - 2][i + x + 2] == 0) {
					board[-i + y - 2][i + x + 2] = 3;
					break;
				}
			}
		}
	}
};
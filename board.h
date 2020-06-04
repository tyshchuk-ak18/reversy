class board {
private:
	const int nBoardSize = 8;
	int** nBoard = new int*[nBoardSize];
	bool bTurn;//true-black; false-white

public:
	int GnBS() {
		return nBoardSize;
	}
	int GnBU(int x, int y) {
		return nBoard[x][y];
	}
	void vBoardReset() {//1-black; 2-white; 3-available to set
		for (int i = 0; i < nBoardSize; i++) nBoard[i] = new int[nBoardSize];
		for (int j = 0; j < nBoardSize; j++) for (int i = 0; i < nBoardSize; i++) nBoard[j][i] = 0;
		nBoard[3][3] = 1;
		nBoard[3][4] = 2;
		nBoard[4][3] = 2;
		nBoard[4][4] = 1;
		nBoard[0][1] = 3;
	}
	void SnBU(int x, int y) {
		bool i = true;
		if (bTurn && i) {
			nBoard[y][x] = 1;
			vCheckAvailable();
			bTurn = false;
			i = false;
		}
		if (!bTurn && i) {
			nBoard[y][x] = 2;
			vCheckAvailable();
			bTurn = true;
			i = false;
		}
	}
	void vCheckAvailable() {

	}
};
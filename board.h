class boardlogic {
private:
	const int nBoardSize = 8;

	int** board = new int*[nBoardSize];
	int nUnitsAmount[2];

	bool bTurn;//true-black; false-white
	bool bIsPlace = true;

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
	bool GbIP() {
		return bIsPlace;
	}
	bool GbT() {
		return bTurn;
	}

	void vBoardReset() {//1-black; 2-white; 3-available to set
		for (int i = 0; i < nBoardSize; i++) board[i] = new int[nBoardSize];
		for (int j = 0; j < nBoardSize; j++) for (int i = 0; i < nBoardSize; i++) board[j][i] = 0;
		board[3][3] = 1;
		board[3][4] = 2;
		board[4][3] = 2;
		board[4][4] = 1;
		bTurn = true;
		vCheckAvailablePlace(false);
	}
	void vClearMem() {
		for (int i = 0; i < nBoardSize; i++) delete[] board[i];
	}

	void SnBU(int x, int y) {
		bool i = true;
		if (bTurn && i && board[y][x] == 3) {//set black
			vFlipUnits(x, y);
			bTurn = false;
			i = false;
		}
		if (!bTurn && i && board[y][x] == 3) {// set white
			vFlipUnits(x, y);
			bTurn = true;
			i = false;
		}
		vCheckAvailablePlace(false);
	}

	void vFlipUnits(int x, int y) {
		if (bTurn) {
			board[y][x] = 1;
			//ray casts to right
			if (x < nBoardSize - 2 && board[y][x + 1] == 2) {//check if next is another then go
				for (int i1 = x + 1; i1 < nBoardSize; i1++) {
					if (board[y][i1 + 1] == 1) {//search for last same
						for (int i2 = i1; i2 > x; i2--) board[y][i2] = 1;//flip all another
						break;//if last another is seeked then stop
					}
					if (board[y][i1 + 1] == 0 || board[y][i1 + 1] == 3) break;//if no neither same nor another then stop
				}
			}
			if (x == nBoardSize - 2 && board[y][x + 1] == 2) {//for border flipping
				if (board[y][x + 2] == 1) board[y][x + 1] = 1;
			}
			//ray casts to down
			if (y < nBoardSize - 2 && board[y + 1][x] == 2) {
				for (int i1 = y + 1; i1 < nBoardSize; i1++) {
					if (board[i1 + 1][x] == 1) {
						for (int i2 = i1; i2 > y; i2--) board[i2][x] = 1;
						break;
					}
					if (board[i1 + 1][x] == 0 || board[i1 + 1][x] == 3) break;
				}
			}
			if (y == nBoardSize - 2 && board[y + 1][x] == 2) {
				if (board[y + 2][x] == 1) board[y + 1][x] = 1;
			}
			//ray casts to left
			if (x > 2 && board[y][x - 1] == 2) {
				for (int i1 = x - 1; i1 > 0; i1--) {
					if (board[y][i1 - 1] == 1) {
						for (int i2 = i1; i2 < x; i2++) board[y][i2] = 1;
						break;
					}
					if (board[y][i1 - 1] == 0 || board[y][i1 - 1] == 3) break;
				}
			}
			if (x == 2 && board[y][x - 1] == 2) {
				if (board[y][x - 2] == 1) board[y][x - 1] = 1;
			}
			//ray casts to up
			if (y > 2 && board[y - 1][x] == 2) {
				for (int i1 = y - 1; i1 > 0; i1--) {
					if (board[i1 - 1][x] == 1) {
						for (int i2 = i1; i2 < y; i2++) board[i2][x] = 1;
						break;
					}
					if (board[i1 - 1][x] == 0 || board[i1 - 1][x] == 3) break;
				}
			}

			//ray casts to right down
			if (y < nBoardSize - 2 && x < nBoardSize - 2 && board[y + 1][x + 1] == 2) {
				for (int i1 = 0; i1 + y + 1 < nBoardSize && i1 + x + 1 < nBoardSize; i1++) {
					if (board[i1 + y + 2][i1 + x + 2] == 1) {
						for (int i2 = i1 + 1; i2 + y + 1 > y && i2 + x + 1 > x; i2--) board[i2 + y][i2 + x] = 1;
						break;
					}
					if (board[i1 + y + 2][i1 + x + 2] == 0 || board[i1 + y + 2][i1 + x + 2] == 3) break;
				}
			}
			//ray casts to left up
			if (y > 2 && x > 2 && board[y - 1][x - 1] == 2) {
				for (int i1 = 0; -i1 + y - 1 > 0 && -i1 + x - 1 > 0; i1++) {
					if (board[-i1 + y - 2][-i1 + x - 2] == 1) {
						for (int i2 = i1 + 1; -i2 + y - 1 < y && -i2 + x - 1 < x; i2--) board[-i2 + y][-i2 + x] = 1;
						break;
					}
					if (board[-i1 + y - 2][-i1 + x - 2] == 0 || board[-i1 + y - 2][-i1 + x - 2] == 3) break;
				}
			}
			//ray casts to left down
			if (y < nBoardSize - 2 && x > 2 && board[y + 1][x - 1] == 2) {
				for (int i1 = 0; i1 + y + 1 < nBoardSize && -i1 + x - 1 > 0; i1++) {
					if (board[i1 + y + 2][-i1 + x - 2] == 1) {
						for (int i2 = i1 + 1; i2 + y + 1 > y && -i2 + x - 1 < x; i2--) board[i2 + y][-i2 + x] = 1;
						break;
					}
					if (board[i1 + y + 2][-i1 + x - 2] == 0 || board[i1 + y + 2][-i1 + x - 2] == 3) break;
				}
			}
			//ray casts to right up
			if (y > 2 && x < nBoardSize - 2 && board[y - 1][x + 1] == 2) {
				for (int i1 = 0; -i1 + y - 1 > 0 && i1 + x + 1 < nBoardSize; i1++) {
					if (board[-i1 + y - 2][i1 + x + 2] == 1) {
						for (int i2 = i1 + 1; -i2 + y - 1 < y && i2 + x + 1 > x; i2--) board[-i2 + y][i2 + x] = 1;
						break;
					}
					if (board[-i1 + y - 2][i1 + x + 2] == 0 || board[-i1 + y - 2][i1 + x + 2] == 3) break;
				}
			}
		}

		if (!bTurn) {
			board[y][x] = 2;
			if (x < nBoardSize - 2 && board[y][x + 1] == 1) {
				for (int i1 = x + 1; i1 < nBoardSize; i1++) {
					if (board[y][i1 + 1] == 2) {
						for (int i2 = i1; i2 > x; i2--) board[y][i2] = 2;
						break;
					}
					if (board[y][i1 + 1] == 0 || board[y][i1 + 1] == 3) break;
				}
			}
			if (x == nBoardSize - 2 && board[y][x + 1] == 1) {
				if (board[y][x + 2] == 2) board[y][x + 1] = 2;
			}
			if (y < nBoardSize - 2 && board[y + 1][x] == 1) {
				for (int i1 = y + 1; i1 < nBoardSize; i1++) {
					if (board[i1 + 1][x] == 2) {
						for (int i2 = i1; i2 > y; i2--) board[i2][x] = 2;
						break;
					}
					if (board[i1 + 1][x] == 0 || board[i1 + 1][x] == 3) break;
				}
			}
			if (y == nBoardSize - 2 && board[y + 1][x] == 1) {
				if (board[y + 2][x] == 2) board[y + 1][x] = 2;
			}
			if (x > 2 && board[y][x - 1] == 1) {
				for (int i1 = x - 1; i1 > 0; i1--) {
					if (board[y][i1 - 1] == 2) {
						for (int i2 = i1; i2 < x; i2++) board[y][i2] = 2;
						break;
					}
					if (board[y][i1 - 1] == 0 || board[y][i1 - 1] == 3) break;
				}
			}
			if (x == 2 && board[y][x - 1] == 1) {
				if (board[y][x - 2] == 2) board[y][x - 1] = 2;
			}
			if (y > 2 && board[y - 1][x] == 1) {
				for (int i1 = y - 1; i1 > 0; i1--) {
					if (board[i1 - 1][x] == 2) {
						for (int i2 = i1; i2 < y; i2++) board[i2][x] = 2;
						break;
					}
					if (board[i1 - 1][x] == 0 || board[i1 - 1][x] == 3) break;
				}
			}
			if (y == 2 && board[y - 1][x] == 1) {
				if (board[y - 2][x] == 2) board[y - 1][x] = 2;
			}

			if (y < nBoardSize - 2 && x < nBoardSize - 2 && board[y + 1][x + 1] == 1) {
				for (int i1 = 0; i1 + y + 1 < nBoardSize && i1 + x + 1 < nBoardSize; i1++) {
					if (board[i1 + y + 2][i1 + x + 2] == 2) {
						for (int i2 = i1 + 1; i2 + y + 1 > y && i2 + x + 1 > x; i2--) board[i2 + y][i2 + x] = 2;
						break;
					}
					if (board[i1 + y + 2][i1 + x + 2] == 0 || board[i1 + y + 2][i1 + x + 2] == 3) break;
				}
			}
			if (y > 2 && x > 2 && board[y - 1][x - 1] == 1) {
				for (int i1 = 0; -i1 + y - 1 > 0 && -i1 + x - 1 > 0; i1++) {
					if (board[-i1 + y - 2][-i1 + x - 2] == 2) {
						for (int i2 = i1 + 1; -i2 + y - 1 < y && -i2 + x - 1 < x; i2--) board[-i2 + y][-i2 + x] = 2;
						break;
					}
					if (board[-i1 + y - 2][-i1 + x - 2] == 0 || board[-i1 + y - 2][-i1 + x - 2] == 3) break;
				}
			}
			if (y < nBoardSize - 2 && x > 2 && board[y + 1][x - 1] == 1) {
				for (int i1 = 0; i1 + y + 1 < nBoardSize && -i1 + x - 1 > 0; i1++) {
					if (board[i1 + y + 2][-i1 + x - 2] == 2) {
						for (int i2 = i1 + 1; i2 + y + 1 > y && -i2 + x - 1 < x; i2--) board[i2 + y][-i2 + x] = 2;
						break;
					}
					if (board[i1 + y + 2][-i1 + x - 2] == 0 || board[i1 + y + 2][-i1 + x - 2] == 3) break;
				}
			}
			if (y > 0 && x < nBoardSize && board[y - 1][x + 1] == 1) {
				for (int i1 = 0; -i1 + y - 1 > 0 && i1 + x + 1 < nBoardSize; i1++) {
					if (board[-i1 + y - 2][i1 + x + 2] == 2) {
						for (int i2 = i1 + 1; -i2 + y - 1 < y && i2 + x + 1 > x; i2--) board[-i2 + y][i2 + x] = 2;
						break;
					}
					if (board[-i1 + y - 2][i1 + x + 2] == 0 || board[-i1 + y - 2][i1 + x + 2] == 3) break;
				}
			}
		}
	}

	void vCheckAvailablePlace(bool secondcheck) {
		nUnitsAmount[0] = 0;
		nUnitsAmount[1] = 0;
		for (int j = 0; j < nBoardSize; j++) for (int i = 0; i < nBoardSize; i++) {
			if (board[j][i] == 1) nUnitsAmount[0]++;//score of black
			if (board[j][i] == 2) nUnitsAmount[1]++;//score of white
			if (board[j][i] == 3) board[j][i] = 0;
		}
		
		for (int y = 0; y < nBoardSize; y++) {
			for (int x = 0; x < nBoardSize; x++) {
				if (bTurn && board[y][x] == 1) {
					for (int i = x + 1; i < nBoardSize && board[y][i] == 2; i++) {//search for last another to right
						if (board[y][i + 1] == 0) {
							board[y][i + 1] = 3;
							break;
						}
					}
					
					for (int i = 1; -i + x > 0 && board[y][-i + x] == 2; i++) {//search for last another to left
						if (board[y][-i + x - 1] == 0) {
							board[y][-i + x - 1] = 3;
							break;
						}
					}
					for (int i = y + 1; i < nBoardSize && board[i][x] == 2; i++) {//search for last another to down
						if (board[i + 1][x] == 0) {
							board[i + 1][x] = 3;
							break;
						}
					}
					for (int i = 1; -i + y > 0 && board[-i + y][x] == 2; i++) {//search for last another to up
						if (board[-i + y - 1][x] == 0) {
							board[-i + y - 1][x] = 3;
							break;
						}
					}

					for (int i = 1; i + y < nBoardSize && i + x < nBoardSize && board[i + y][i + x] == 2; i++) {//search for last another to right-down
						if (board[i + y + 1][i + x + 1] == 0) {
							board[i + y + 1][i + x + 1] = 3;
							break;
						}
					}
					for (int i = 1; -i + y > 0 && -i + x > 0 && board[-i + y][-i + x] == 2; i++) {//search for last another to left-up
						if (board[-i + y - 1][-i + x - 1] == 0) {
							board[-i + y - 1][-i + x - 1] = 3;
							break;
						}
					}
					for (int i = 1; -i + y > 0 && i + x < nBoardSize && board[-i + y][i + x] == 2; i++) {//search for last another to right-up
						if (board[-i + y - 1][i + x + 1] == 0) {
							board[-i + y - 1][i + x + 1] = 3;
							break;
						}
					}
					for (int i = 1; i + y < nBoardSize && -i + x < nBoardSize && board[i + y][-i + x] == 2; i++) {//search for last another to left-down
						if (board[i + y + 1][-i + x - 1] == 0) {
							board[i + y + 1][-i + x - 1] = 3;
							break;
						}
					}
				}

				if (!bTurn && board[y][x] == 2) {
					for (int i = x + 1; i < nBoardSize && board[y][i] == 1; i++) {//search for last another to right
						if (board[y][i + 1] == 0) {
							board[y][i + 1] = 3;
							break;
						}
					}
					for (int i = 1; -i + x > 0 && board[y][-i + x] == 1; i++) {//search for last another to left
						if (board[y][-i + x - 1] == 0) {
							board[y][-i + x - 1] = 3;
							break;
						}
					}
					for (int i = 1; i + y < nBoardSize && board[i + y][x] == 1; i++) {//search for last another to down
						if (board[i + y + 1][x] == 0) {
							board[i + y + 1][x] = 3;
							break;
						}
					}
					for (int i = 1; -i + y > 0 && board[-i + y][x] == 1; i++) {//search for last another to up
						if (board[-i + y - 1][x] == 0) {
							board[-i + y - 1][x] = 3;
							break;
						}
					}

					for (int i = 1; i + y < nBoardSize && i + x < nBoardSize && board[i + y][i + x] == 1; i++) {//search for last another to right-down
						if (board[i + y + 1][i + x + 1] == 0) {
							board[i + y + 1][i + x + 1] = 3;
							break;
						}
					}
					for (int i = 1; -i + y > 0 && -i + x > 0 && board[-i + y][-i + x] == 1; i++) {//search for last another to left-up
						if (board[-i + y - 1][-i + x - 1] == 0) {
							board[-i + y - 1][-i + x - 1] = 3;
							break;
						}
					}
					for (int i = 1; -i + y > 0 && i + x < nBoardSize && board[-i + y][i + x] == 1; i++) {//search for last another to right-up
						if (board[-i + y - 1][i + x + 1] == 0) {
							board[-i + y - 1][i + x + 1] = 3;
							break;
						}
					}
					for (int i = 1; i + y < nBoardSize && -i + x < nBoardSize && board[i + y][-i + x] == 1; i++) {//search for last another to left-down
						if (board[i + y + 1][-i + x - 1] == 0) {
							board[i + y + 1][-i + x - 1] = 3;
							break;
						}
					}
				}
			}
		}

		bIsPlace = false;//check if can set unit
		for (int j = 0; j < nBoardSize; j++) for (int i = 0; i < nBoardSize; i++) if (board[j][i] == 3) bIsPlace = true;
		if (!bIsPlace && bTurn && !secondcheck) bTurn = false;
		if (!bIsPlace && !bTurn && !secondcheck) bTurn = true;
		if (!bIsPlace && !secondcheck) vCheckAvailablePlace(true);
	}
};
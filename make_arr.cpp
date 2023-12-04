#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class Sudoku {
public:
	int grid[9][9]; // 스도쿠 판을 표현할 2차원 배열, 크기는 항상 9x9
	int K; // 빈칸으로 남길 숫자의 개수
	int N;

	// 생성자: K(빈칸 개수)만 입력으로 받음
	Sudoku(int K):N(9) {
		this->K = K;
		// 명시적으로 grid를 0으로 초기화
		for(int i=0; i<9; i++){
			for(int j=0; j<9; j++){
				grid[i][j]=0;
			}
		}
	}

	// 스도쿠 판을 채우는 주 함수
	void fillValues() {
		// 대각선에 있는 작은 정사각형들을 먼저 채움
		fillDiagonal();
		// 남은 부분을 채움
		fillRemaining(0, 3);
		// K개의 빈칸을 만듦
		removeKDigits();
	}

	// 대각선의 작은 정사각형을 채우는 함수
	void fillDiagonal() {
		for (int i = 0; i < 9; i = i + 3)
			fillBox(i, i);
	}

	// 주어진 row, col 위치에서 시작하는 3x3 박스에 num이 사용되지 않았는지 체크
	bool unUsedInBox(int rowStart, int colStart, int num) {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (grid[rowStart + i][colStart + j] == num)
					return false;
		return true;
	}

	// 3x3 박스를 채우는 함수
	void fillBox(int row, int col) {
		int num;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				do {
					num = randomGenerator(N);
				}
				while (!unUsedInBox(row, col, num));
				grid[row + i][col + j] = num;
			}
		}
	}

	// 1부터 num까지의 랜덤한 숫자를 생성하는 함수
	int randomGenerator(int num) {
		return (rand() % num)+1;
	}

	// (i, j) 위치에 num을 놓을 수 있는지 판단하는 함수
	bool CheckIfSafe(int i, int j, int num) {
		return (unUsedInRow(i, num) && unUsedInCol(j, num) &&
			unUsedInBox(i - i % 3, j - j % 3, num));
	}

	// 해당 행에 num이 존재하지 않는지 확인하는 함수
	bool unUsedInRow(int i, int num) {
		for (int j = 0; j < 9; j++)
			if (grid[i][j] == num)
				return false;
		return true;
	}

	// 해당 열에 num이 존재하지 않는지 확인하는 함수
	bool unUsedInCol(int j, int num) {
		for (int i = 0; i < 9; i++)
			if (grid[i][j] == num)
				return false;
		return true;
	}

	// 스도쿠 판을 채우는 재귀 함수
	bool fillRemaining(int i, int j) {
		// i와 j 값이 9 이상이면, 모든 칸을 채운 것이므로 true를 반환
		if (i == 8 && j == 9)
			return true;

		// j가 9 이상이면, 다음 행으로 이동
		if (j == 9) {
			i++;
			j = 0;
		}

		// 이미 값이 채워진 칸이면, 다음 칸으로 이동
		if (grid[i][j] != 0)
			return fillRemaining(i, j + 1);

		// 빈 칸에 들어갈 수 있는 숫자를 찾음
		for (int num = 1; num <= 9; num++) {
			// 현재 위치 (i, j)에 num을 놓을 수 있는지 확인
			if (CheckIfSafe(i, j, num)) {
				// 가능하면, 그 위치에 num을 놓음
				grid[i][j] = num;
				// 다음 칸을 채움 (재귀 호출)
				if (fillRemaining(i, j + 1))
					return true;
			}
			// 현재 위치에 num을 놓을 수 없거나, 다음 칸을 채우는 것이 실패하면 0으로 초기화
			grid[i][j] = 0;
		}
		return false;  // 가능한 숫자를 모두 시도했지만 실패한 경우 false 반환
	}

		// K개의 숫자를 랜덤하게 지우는 함수
	void removeKDigits() {
		int count = K;  // 지울 숫자의 수를 카운트하는 변수
		while (count != 0) {
			int cellId = randomGenerator(9 * 9) - 1;  // 랜덤한 위치의 cell 인덱스 생성
			int i = (cellId / 9);  // 행 인덱스 계산
			int j = cellId % 9;  // 열 인덱스 계산
			// if (j != 0)
			// 	j--;

			if (grid[i][j] != 0) {  // 해당 cell이 0이 아니면 (즉, 지울 수 있으면)
				count--;  // 카운트 감소
				grid[i][j] = 0;  // 해당 cell을 0으로 만든다
			}
		}
	}

	// 스도쿠 판을 출력하는 함수
	void printSudoku() {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				// 각 행과 열의 숫자를 공백으로 구분하여 출력
				cout << to_string(grid[i][j]) + " ";
			}
			// 각 행 출력이 끝나면 줄바꿈
			cout << endl;
		}
		// cout << endl;  // 전체 보드 출력이 끝나면 한 줄 띄운다
	}

};

int main() {
	int K = 50;  // 50개의 빈 칸
    srand(time(0));  // 현재 시간을 시드 값으로 설정
	Sudoku Sudoku(K);  // 스도쿠 객체 생성
	Sudoku.fillValues();  // 스도쿠 판 채우기
	Sudoku.printSudoku();  // 스도쿠 판 출력
	return 0;
}

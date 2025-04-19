#include <iostream>
using namespace std;



bool isSafe(int board[][8], int N, int row, int col) {
	for (int i = 0; i < row; i++) {
		if (board[i][col] == 1) return false;
		if (col - (row - i) >= 0 && board[i][col - (row - i)] == 1) return false;
		if (col + (row - i) < N && board[i][col + (row - i)] == 1) return false;
	}
	return true;
}

void solvesN_Queens(int board[][8], int N, int row, int* solutions) {
	if (row == N) {		// all queens placed successfully
		(*solutions)++;
		return;
	}

	for (int i = 0; i < N; i++) {
		if (isSafe(board, N, row, i)) {
			// mark position of the newly placed queen
			board[row][i] = 1;

			// one row must have only one queen, therefore recur for next row
			solvesN_Queens(board, N, row + 1, solutions);

			// return to previous state of the chessboard to move on to next posible placement (backtrack)
			board[row][i] = 0; 
		}
	}
	return;
}

int main() {
	int N;
	int solutions = 0;

	cout << "Enter N-Queens size: ";
	cin >> N;
	if (N < 1) cout << "Invalid input.";
	else {
		int board[8][8] = { 0 };
		solvesN_Queens(board, N, 0, &solutions);
		cout << solutions;
	}
	
	return 0;
}
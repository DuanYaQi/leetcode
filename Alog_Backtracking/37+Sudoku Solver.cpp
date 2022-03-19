class Solution {
public:
    bool isValid(int row, int col, char val, vector<vector<char>>& board) {
        for (int i = 0; i < board.size(); ++i) {
            if (board[row][i] == val) {
                return false;
            }
        }

        for (int i = 0; i < board.size(); ++i) {
            if (board[i][col] == val) {
                return false;
            }
        }

        int startX = (row / 3) * 3;
        int startY = (col / 3) * 3;

        for (int i = startX; i < startX + 3; ++i) {
            for (int j = startY; j < startY + 3; ++j) {
                if (board[i][j] == val) {
                    return false;
                }
            }
        }

        return true;

    }

    bool backTracking(vector<vector<char>>& board) {

        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board.size(); ++j) {

                if (board[i][j] != '.') continue;

                for (char k = '1'; k <= '9'; k++) {
                    if (isValid(i, j, k, board)) {
                        board[i][j] = k;
                        if (backTracking(board)) return true;
                        board[i][j] = '.';
                    }
                }

                return false;
            }
        }

        return true;
    }

    void solveSudoku(vector<vector<char>>& board) {
        backTracking(board);
    }
};
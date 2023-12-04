#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

struct NMKSolver {
    int n, m, k;
    int** data;

    NMKSolver(int n, int m, int k) {
        this->n = n;
        this->m = m;
        this->k = k;
        data = new int* [n];
        for (int i = 0; i < n; i++)
            data[i] = new int[m];
    }

    void load() {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &data[i][j]);
    }

    void printData() const{
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d ", data[i][j]);
            }
            printf("\n");
        }
    }

    bool isRowWinning(int y, int x) const {
        if (x + k > m)
            return false;
        for (int i = x + 1; i < x + k; i++)
            if (data[y][i] != data[y][i - 1])
                return false;
        return true;
    }

    bool isColumnWinning(int y, int x) const {
        if (y + k > n)
            return false;
        for (int i = y + 1; i < y + k; i++)
            if (data[i][x] != data[i - 1][x])
                return false;
        return true;
    }

    bool isLeftDiagonalWinning(int y, int x) const {
        if (y + k > n || x + k > m)
            return false;
        for (int i = 1; i < k; i++)
            if (data[y + i][x + i] != data[y + i - 1][x + i - 1])
                return false;
        return true;
    }

    bool isRightDiagonalWinning(int y, int x) const {
        if (y + k > n || x - k + 1 < 0)
            return false;
        for (int i = 1; i < k; i++)
            if (data[y + i][x - i] != data[y + i - 1][x - i + 1])
                return false;
        return true;
    }

    int isGameWon() const {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (data[i][j] && (j == 0 || data[i][j - 1] != data[i][j]))
                    if (isRowWinning(i, j))
                        return data[i][j];
                if (data[i][j] && (i == 0 || data[i - 1][j] != data[i][j]))
                    if (isColumnWinning(i, j))
                        return data[i][j];
                if (data[i][j] && (i == 0 || j == 0 || data[i - 1][j - 1] != data[i][j]))
                    if (isLeftDiagonalWinning(i, j))
                        return data[i][j];
                if (data[i][j] && (i == 0 || j == m - 1 || data[i - 1][j + 1] != data[i][j]))
                    if (isRightDiagonalWinning(i, j))
                        return data[i][j];
            }
        return 0;
    }

    int countRight(int y, int x, int move) const {
        int current = 0;
        for (int i = 0; i < k && x + i < m; i++) {
            if (data[y][x + i] == move)
                current++;
            else
                return current;
        }
        return current;
    }

    int countLeft(int y, int x, int move) const {
        int current = 0;
        for (int i = 0; i < k && x - i >= 0; i++) {
            if (data[y][x - i] == move)
                current++;
            else
                return current;
        }
        return current;
    }

    int countTop(int y, int x, int move) const {
        int current = 0;
        for (int i = 0; i < k && y - i >= 0; i++) {
            if (data[y - i][x] == move)
                current++;
            else
                return current;
        }
        return current;
    }

    int countBottom(int y, int x, int move) const {
        int current = 0;
        for (int i = 0; i < k && y + i < n; i++) {
            if (data[y + i][x] == move)
                current++;
            else
                return current;
        }
        return current;
    }

    int countRightBottomDiagonal(int y, int x, int move) const {
        int current = 0;
        for (int i = 0; i < k && y + i < n && x + i < m; i++) {
            if (data[y + i][x + i] == move)
                current++;
            else
                return current;
        }
        return current;
    }

    int countLeftBottomDiagonal(int y, int x, int move) const {
        int current = 0;
        for (int i = 0; i < k && y + i < n && x - i >= 0; i++) {
            if (data[y + i][x - i] == move)
                current++;
            else
                return current;
        }
        return current;
    }

    int countLeftTopDiagonal(int y, int x, int move) const {
        int current = 0;
        for (int i = 0; i < k && y - i >= 0 && x - i >= 0; i++) {
            if (data[y - i][x - i] == move)
                current++;
            else
                return current;
        }
        return current;
    }

    int countRightTopDiagonal(int y, int x, int move) const {
        int current = 0;
        for (int i = 0; i < k && y - i >= 0 && x + i < m; i++) {
            if (data[y - i][x + i] == move)
                current++;
            else
                return current;
        }
        return current;
    }

    bool isMoveWinning(int y, int x, int move) {
        int tmp = data[y][x];
        data[y][x] = move;
        if ((countRight(y, x, move) + countLeft(y, x, move) > k) ||
            (countTop(y, x, move) + countBottom(y, x, move) > k) ||
            (countLeftTopDiagonal(y, x, move) + countRightBottomDiagonal(y, x, move) > k) ||
            (countRightTopDiagonal(y, x, move) + countLeftBottomDiagonal(y, x, move) > k))
        {
            data[y][x] = tmp;
            return true;
        }
        data[y][x] = tmp;
        return false;
    }

    void generateAll(int player, int mode = 0) {
        if (isGameWon()) {
            printf("0\n");
            return;
        }
        int possibleMoves = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (data[i][j] == 0) {
                    possibleMoves++;
                    if (mode == 1 && isMoveWinning(i, j, player)) {
                        printf("1\n");
                        data[i][j] = player;
                        printData();
                        return;
                    }
                }
            }
        printf("%d\n", possibleMoves);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (data[i][j] == 0) {
                    int tmp = data[i][j];
                    data[i][j] = player;
                    printData();
                    data[i][j] = tmp;
                }
            }
    }

    int solveGame(int player, int currentPlayer, bool checkState = false) {
        if (checkState) {
            int result = isGameWon();
            if (result == currentPlayer)
                return 1;
            else if (result > 0)
                return -1;
        }
        if (currentPlayer == 0)
            currentPlayer = 2;
        int best = (player == currentPlayer ? -2 : 2);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (data[i][j] == 0) {
                    if (isMoveWinning(i, j, currentPlayer)) {
                        if (player == currentPlayer)
                            return 1;
                        else
                            return -1;
                    }
                }
            }


        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (data[i][j] == 0) {
                    int tmp = data[i][j];
                    data[i][j] = currentPlayer;
                    int result = solveGame(player, (currentPlayer + 1) % 2);
                    if (player == currentPlayer && result > best) {
                        best = result;
                        if (best == 1) {
                            data[i][j] = tmp;
                            return 1;
                        }
                    }
                    else if (player != currentPlayer && result < best) {
                        best = result;
                        if (best == -1) {
                            data[i][j] = tmp;
                            return -1;
                        }
                    }
                    data[i][j] = tmp;
                }
            }
        if (best == 2 || best == -2)
            return 0;
        else
            return best;
    }

    ~NMKSolver() {
        for (int i = 0; i < n; i++)
            delete[] data[i];
        delete[] data;
    }

};

int main() {
    int n, m, k, player;
    char command[50];
    while (scanf("%s %d %d %d %d", command, &n, &m, &k, &player) > 0) {
        NMKSolver solver(n, m, k);
        solver.load();
        if (strcmp("GEN_ALL_POS_MOV", command) == 0)
            solver.generateAll(player);
        else if (strcmp("GEN_ALL_POS_MOV_CUT_IF_GAME_OVER", command) == 0)
            solver.generateAll(player, 1);
        else {
            int result = solver.solveGame(player, player, true);
            if ((result == 1 && player == 1) || (result == -1 && player == 2))
                printf("FIRST_PLAYER_WINS\n");
            else if ((result == 1 && player == 2) || (result == -1 && player == 1))
                printf("SECOND_PLAYER_WINS\n");
            else
                printf("BOTH_PLAYERS_TIE\n");
        }
    }
}
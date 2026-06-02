#include "Evaluation.h"

static void analyzeDirection(const Board &board, int r, int c, int dx, int dy, char player,
                              int &count, bool &openEnd) {
    int size = board.getSize();
    int nr = r + dx;
    int nc = c + dy;
    count = 0;
    openEnd = false;

    while (nr >= 0 && nr < size && nc >= 0 && nc < size && board.getCell(nr, nc) == player) {
        count++;
        nr += dx;
        nc += dy;
    }

    if (nr >= 0 && nr < size && nc >= 0 && nc < size && board.getCell(nr, nc) == ' ') {
        openEnd = true;
    }
}

static int scorePattern(int length, int openEnds) {
    if (length >= 5) return 100000;

    if (openEnds == 0) {
        return 0;
    }

    if (openEnds == 1) {
        switch (length) {
            case 4: return 5000;  
            case 3: return 200;
            case 2: return 50;
            case 1: return 10;
            default: return 0;
        }
    }

    switch (length) {
        case 4: return 50000;  
        case 3: return 5000;  
        case 2: return 500;
        case 1: return 20;
        default: return 0;
    }
}

int Evaluation::evaluate(const Board &board, char symbol)
{
    int totalScore = 0;
    int size = board.getSize();
    char opponent = (symbol == 'X') ? 'O' : 'X';

    int dx[] = {1, 0, 1, 1};
    int dy[] = {0, 1, 1, -1};

    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            char current = board.getCell(r, c);
            if (current == ' ') {
                continue;
            }

            for (int i = 0; i < 4; ++i) {
                int prevR = r - dx[i];
                int prevC = c - dy[i];
                if (prevR >= 0 && prevR < size && prevC >= 0 && prevC < size && board.getCell(prevR, prevC) == current) {
                    continue;
                }

                int count = 1;
                int nextR = r + dx[i];
                int nextC = c + dy[i];
                while (nextR >= 0 && nextR < size && nextC >= 0 && nextC < size && board.getCell(nextR, nextC) == current) {
                    count++;
                    nextR += dx[i];
                    nextC += dy[i];
                }
                int openEnds = 0;

                if (prevR >= 0 && prevR < size && prevC >= 0 && prevC < size && board.getCell(prevR, prevC) == ' ') {
                    openEnds++;
                }
                if (nextR >= 0 && nextR < size && nextC >= 0 && nextC < size && board.getCell(nextR, nextC) == ' ') {
                    openEnds++;
                }

                int points = scorePattern(count, openEnds);

                if (current == symbol) {
                    totalScore += points;
                } else {
                    totalScore -= static_cast<int>(points * 1.1);
                }
            }
        }
    }

    return totalScore;
}

#include "Minimax.h"
#include "Evaluation.h"
#include <algorithm>
#include <vector>
#include <cmath>

// Lay danh sach o trong gan cac quan da dat (ban kinh radius), hoac tam ban neu chua co quan
static std::vector<std::pair<int, int>> getCandidateMoves(const Board &board, int radius = 2) {
    int size = board.getSize();
    std::vector<std::vector<bool>> isCandidate(size, std::vector<bool>(size, false));
    std::vector<std::pair<int, int>> candidates;
    bool hasAnyPiece = false;

    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (board.getCell(r, c) != ' ') {
                hasAnyPiece = true;
                for (int dr = -radius; dr <= radius; ++dr) {
                    for (int dc = -radius; dc <= radius; ++dc) {
                        int nr = r + dr;
                        int nc = c + dc;
                        if (nr >= 0 && nr < size && nc >= 0 && nc < size && board.getCell(nr, nc) == ' ' && !isCandidate[nr][nc]) {
                            isCandidate[nr][nc] = true;
                            candidates.push_back({nr, nc});
                        }
                    }
                }
            }
        }
    }

    if (!hasAnyPiece) {
        candidates.push_back({size / 2, size / 2});
    }

    return candidates;
}

// Ham de quy Minimax co cat tia Alpha-Beta, danh gia bang Evaluation khi het do sau
static int minimax(Board &board, int depth, int alpha, int beta,
                   bool maximizingPlayer, char playerSymbol, char opponentSymbol) {
    if (depth == 0) {
        return Evaluation::evaluate(board, playerSymbol);
    }

    auto candidates = getCandidateMoves(board, 2);

    if (candidates.empty()) {
        return Evaluation::evaluate(board, playerSymbol);
    }

    if (maximizingPlayer) {
        int bestValue = -1000000;
        for (auto &[r, c] : candidates) {
            board.setCell(r, c, playerSymbol);
            int value = minimax(board, depth - 1, alpha, beta, false, playerSymbol, opponentSymbol);
            board.setCell(r, c, ' ');
            bestValue = std::max(bestValue, value);
            alpha = std::max(alpha, value);
            if (beta <= alpha) {
                break; // cat tia beta
            }
        }
        return bestValue;
    } else {
        int bestValue = 1000000;
        for (auto &[r, c] : candidates) {
            board.setCell(r, c, opponentSymbol);
            int value = minimax(board, depth - 1, alpha, beta, true, playerSymbol, opponentSymbol);
            board.setCell(r, c, ' ');
            bestValue = std::min(bestValue, value);
            beta = std::min(beta, value);
            if (beta <= alpha) break; // cat tia alpha
        }
        return bestValue;
    }
}

// Tim nuoc di co diem cao nhat: uu tien thang ngay, chan thua, roi moi goi Minimax
std::pair<int, int> Minimax::findBestMove(const Board &board, char symbol, int depth) {
    Board copy = board;
    char opponent = (symbol == 'X') ? 'O' : 'X';
    int bestScore = -1000000;
    std::pair<int, int> bestMove = {-1, -1};

    auto candidates = getCandidateMoves(copy, 2);

    if (candidates.empty()) {
        return {copy.getSize() / 2, copy.getSize() / 2};
    }

    // Neu co nuoc thang ngay thi chon luon
    for (auto &[r, c] : candidates) {
        copy.setCell(r, c, symbol);
        if (copy.checkWin(r, c)) {
            copy.setCell(r, c, ' ');
            return {r, c}; 
        }
        copy.setCell(r, c, ' '); 
    }

    // Neu doi phuong thang o nuoc tiep theo thi chan
    for (auto &[r, c] : candidates) {
        copy.setCell(r, c, opponent);
        if (copy.checkWin(r, c)) {
            copy.setCell(r, c, ' ');
            return {r, c}; 
        }
        copy.setCell(r, c, ' '); 
    }

    // Duyet tung nuoc ung vien va chon diem cao nhat
    for (auto &[r, c] : candidates) {
        copy.setCell(r, c, symbol);

        int score = minimax(copy, depth - 1, -1000000, 1000000, false, symbol, opponent);
        copy.setCell(r, c, ' ');

        if (score > bestScore) {
            bestScore = score;
            bestMove = {r, c};
        }
    }

    return bestMove;
}

// Tra ve topN nuoc di co diem cao nhat (sap xep giam dan)
std::vector<std::pair<int, std::pair<int, int>>> Minimax::findTopMoves(const Board &board, char symbol, int depth, int topN) {
    Board copy = board;
    char opponent = (symbol == 'X') ? 'O' : 'X';
    std::vector<std::pair<int, std::pair<int, int>>> topmoves;

    auto candidates = getCandidateMoves(copy, 2);

    if (candidates.empty()) {
        topmoves.push_back({0, {copy.getSize() / 2, copy.getSize() / 2}});
        return topmoves;
    }

    for (auto &[r, c] : candidates) {
        copy.setCell(r, c, symbol);
        if (copy.checkWin(r, c)) {
            copy.setCell(r, c, ' ');
            topmoves.push_back({1000000, {r, c}});
            return topmoves; 
        }
        copy.setCell(r, c, ' ');
    }

    for (auto &[r, c] : candidates) {
        copy.setCell(r, c, opponent);
        if (copy.checkWin(r, c)) {
            copy.setCell(r, c, ' ');
            topmoves.push_back({999999, {r, c}});
            return topmoves; 
        }
        copy.setCell(r, c, ' ');
    }

    for (auto &[r, c] : candidates) {
        copy.setCell(r, c, symbol);
        int score = minimax(copy, depth - 1, -1000000, 1000000, false, symbol, opponent);
        copy.setCell(r, c, ' ');
        topmoves.push_back({score, {r, c}});
    }

    std::sort(topmoves.begin(), topmoves.end(),
              [](const auto &a, const auto &b) { return a.first > b.first; });

    if ((int)topmoves.size() > topN) {
        topmoves.resize(topN);
    }

    return topmoves;
}

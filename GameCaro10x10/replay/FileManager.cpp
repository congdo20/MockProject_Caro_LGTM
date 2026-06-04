#include "FileManager.h"
#include <fstream>
#include <sstream>

// Ghi replay: dong 1 la ten, cac dong sau la row col symbol
bool FileManager::saveReplay(const Replay &replay, const std::string &filename)
{
    std::ofstream output(filename);
    if (!output.is_open()) {
        return false;
    }
    output << replay.getName() << '\n';
    for (const auto &move : replay.getMoves()) {
        output << move.row << ' ' << move.col << ' ' << move.symbol << '\n';
    }
    return true;
}

// Doc replay tu file va nap vao doi tuong Replay
bool FileManager::loadReplay(Replay &replay, const std::string &filename)
{
    std::ifstream input(filename);
    if (!input.is_open()) {
        return false;
    }

    std::string title;
    if (!std::getline(input, title)) {
        return false;
    }
    replay = Replay(title);

    std::string line;
    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }
        std::istringstream parser(line);
        int row, col;
        char symbol;
        parser >> row >> col >> symbol;
        replay.addMove(row, col, symbol);
    }
    return true;
}

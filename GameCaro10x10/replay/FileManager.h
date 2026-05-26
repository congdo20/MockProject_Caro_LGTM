#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Replay.h"
#include <string>

class FileManager
{
public:
    static bool saveReplay(const Replay &replay, const std::string &filename);
    static bool loadReplay(Replay &replay, const std::string &filename);
};

#endif

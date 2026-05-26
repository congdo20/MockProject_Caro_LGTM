# MockProject_Caro_LGTM

GameCaro10x10/
├── main.cpp
├── core/
│   ├── Board.h
│   ├── Board.cpp
│   ├── GameLogic.h
│   ├── GameLogic.cpp
│   ├── Move.h
│   └── Move.cpp
├── player/
│   ├── Player.h
│   ├── Player.cpp
│   ├── PlayerManager.h
│   └── PlayerManager.cpp
├── bot/
│   ├── Bot.h
│   ├── Bot.cpp
│   ├── Minimax.h
│   ├── Minimax.cpp
│   ├── Evaluation.h
│   └── Evaluation.cpp
├── replay/
│   ├── Replay.h
│   ├── Replay.cpp
│   ├── FileManager.h
│   └── FileManager.cpp
├── data/
│   ├── players.txt
│   └── replays.txt
├── ui/
│   ├── Game.h
│   ├── Game.cpp
│   ├── Menu.h
│   └── Menu.cpp
└── docs/
    ├── README.md
    └── ARCHITECTURE.md

## Mục tiêu
Bộ khung này cung cấp:
- Lớp `Board`, `GameLogic`, `Move` để quản lý trạng thái bàn cờ và kiểm tra thắng.
- Lớp `Player`, `PlayerManager` để quản lý người chơi và thông tin cá nhân.
- Bot AI với 3 cấp độ, gồm `Minimax` và `Evaluation`.
- Chức năng `Replay` và `FileManager` để lưu/truy xuất lịch sử trận đấu.
- Giao diện console với `Menu` và `Game`.

## Build

```bash
g++ GameCaro10x10/main.cpp GameCaro10x10/core/*.cpp GameCaro10x10/player/*.cpp GameCaro10x10/bot/*.cpp GameCaro10x10/replay/*.cpp GameCaro10x10/ui/*.cpp -o GameCaro10x10/main.exe
```

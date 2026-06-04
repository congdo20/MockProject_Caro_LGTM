# MockProject_Caro_LGTM

"Giới thiệu"

Trò chơi Caro 10x10 bằng C++:

- Bàn cờ 10x10 và luật thắng 5 ô liên tiếp.
- Chơi 2 người hoặc người vs bot.
- Bot AI nhiều cấp độ, trong đó có chế độ `Hard` dùng thuật toán Minimax.
- Quản lý dữ liệu người chơi và lưu replay.
- Giao diện console đơn giản với menu điều hướng.

"Cấu trúc dự án"

GameCaro10x10/
├── main.cpp
├── manager/
│   ├── GameManager.h
│   └── GameManager.cpp
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
│   ├── PlayerManager.cpp
│   ├── Storage.h
│   └── Storage.cpp
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

"Tính năng chính"

- `core/` chứa logic bàn cờ, kiểm tra thắng thua và lịch sử nước đi.
- `player/` quản lý người chơi, đọc/ghi dữ liệu vào file.
- `bot/` định nghĩa bot AI và thuật toán Minimax cho chế độ khó.
- `replay/` lưu và in lại các nước đi của trận đấu.
- `ui/` xây dựng menu và điều khiển vòng chơi.
- `manager/` điều phối menu chính và lựa chọn chế độ chơi.

"Chạy chương trình"

Từ thư mục `GameCaro10x10`, biên dịch bằng:

```bash
g++ main.cpp manager/*.cpp core/*.cpp player/*.cpp bot/*.cpp replay/*.cpp ui/*.cpp -o main.exe
```

Và chạy:

```bash
./main.exe
```

## Cách dùng Makefile

Mở terminal và vào thư mục GameCaro10x10:

Biên dịch dự án:

```bash
make
```

Chạy chương trình:

```bash
make run
```

Xóa file biên dịch tạm thời và executable:

```bash
make clean
```

Dọn và biên dịch lại từ đầu:

```bash
make rebuild
```

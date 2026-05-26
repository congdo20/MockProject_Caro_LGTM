# MockProject_Caro_LGTM

"Giới thiệu"
Đây là khung trò chơi Caro 10x10 bằng C++ với kiến trúc module rõ ràng, hỗ trợ:

- Bàn cờ 10x10 và luật thắng 5 ô liên tiếp.
- Chơi 2 người hoặc người vs bot.
- Bot AI nhiều cấp độ, trong đó có chế độ `Hard` dùng thuật toán Minimax.
- Quản lý dữ liệu người chơi và lưu replay.
- Giao diện console đơn giản với menu điều hướng.

"Cấu trúc dự án"
GameCaro10x10/
├── main.cpp
├── Manager/
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
- `Manager/` điều phối menu chính và lựa chọn chế độ chơi.

"Chạy chương trình"
Từ thư mục `GameCaro10x10`, biên dịch bằng:

```bash
g++ main.cpp Manager/*.cpp core/*.cpp player/*.cpp bot/*.cpp replay/*.cpp ui/*.cpp -o main.exe
```

Và chạy:

```bash
./main.exe
```

"Lưu ý"

- Dữ liệu người chơi lưu trong `data/players.txt`.
- Replay có thể được mở rộng lưu vào `data/replays.txt`.
- Phiên bản hiện tại đang cung cấp khung chơi và AI mẫu; bạn có thể bổ sung chức năng ghi replay, tính điểm và nâng cấp bot.

# MockProject_Caro_LGTM

GameCaro10x10/
│
├── main.cpp                 <-- [Thành viên 4] Luồng chính & Menu
│
├── Board.h                  <-- [Thành viên 1] Khai báo ma trận & logic bàn cờ
├── Board.cpp                <-- [Thành viên 1] Định nghĩa logic, vẽ, check thắng
│
├── Player.h                 <-- [Chung] Lớp cơ sở cho Người và Bot
├── Bot.h                    <-- [Thành viên 2] Khai báo thuật toán AI
├── Bot.cpp                  <-- [Thành viên 2] Định nghĩa Easy, Normal, Hard (Minimax)
│
├── Storage.h                <-- [Thành viên 3] Khai báo đọc/ghi file, tìm kiếm
├── Storage.cpp              <-- [Thành viên 3] Định nghĩa I/O Stream, Matchmaking
│
└── GameManager.h            <-- [Thành viên 4] Khai báo quản lý trận đấu, Replay
    └── GameManager.cpp      <-- [Thành viên 4] Định nghĩa vòng lặp game, Replay
# QUICK REFERENCE - GameCaro 10x10

## 🎯 Tìm kiếm nhanh chức năng

### Tôi muốn...

#### 🎮 **Chơi trò chơi**
- Vào: `main.cpp` → `GameManager::mainMenu()` → `Game::playHumanVsHuman()` hoặc `Game::playHumanVsBot()`
- File cơ bản: `ui/Game.cpp`, `ui/Menu.cpp`, `core/GameLogic.cpp`, `core/Board.cpp`

#### 🤖 **Hiểu AI bot**
- **Easy**: `bot/Bot.cpp` → `moveEasy()` (random)
- **Normal**: `bot/Bot.cpp` → `moveNormal()` → `Evaluation::evaluate()`
- **Hard**: `bot/Bot.cpp` → `moveHard()` → `Minimax::findBestMove()`
- File chính: `bot/Bot.cpp`, `bot/Evaluation.cpp`, `bot/Minimax.cpp`

#### 💾 **Lưu/Tải người chơi**
- Đọc: `player/PlayerManager::load()` → `Storage::loadFromFile()` → `data/players.txt`
- Ghi: `player/PlayerManager::save()` → `Storage::saveToFile()` → `data/players.txt`
- File cơ bản: `player/PlayerManager.cpp`, `player/Storage.cpp`

#### 🎬 **Lưu/Phát lại trận đấu**
- Lưu: `ui/Game.cpp` → `FileManager::saveReplay()` → `data/replay_*.txt`
- Tải: `Game::showSavedReplays()` → `Game::playReplayFromFile()`
- Phát lại: `Game::playReplayFromFile()` vòng qua `replay.getMoves()`
- File cơ bản: `replay/FileManager.cpp`, `replay/Replay.cpp`

#### 🏆 **Kiểm tra thắng/hòa**
- Thắng: `core/Board::checkWin()` - Quét 4 hướng tìm 5 liên tiếp
- Hòa: `core/Board::checkDraw()` - Kiểm tra bàn cờ đầy
- File: `core/Board.cpp`

#### 📊 **Hiển thị bàn cờ**
- Hàm: `Board::display()` - In bàn cờ 10x10 với border
- File: `core/Board.cpp`

#### 📝 **Nhận input nước đi**
- Hàm: `Game::askMove()` - Nhận 2 số (hàng, cột)
- Parse: `readPairOfInts()` - Parse input bằng getline + istringstream
- File: `ui/Game.cpp`

---

## 📂 Bản đồ file nhanh

```
GameCaro10x10/
├── main.cpp                    ← ENTRY: Khởi tạo GameManager
├── manager/GameManager.cpp     ← Menu routing & main loop
├── ui/
│   ├── Menu.cpp               ← Menu display & input
│   └── Game.cpp               ← Game loop & gameplay
├── core/
│   ├── Board.cpp              ← Board state & win detection ⭐
│   ├── GameLogic.cpp          ← Turn management
│   └── Move.cpp               ← Move data structure
├── bot/
│   ├── Bot.cpp                ← AI opponent (3 levels) ⭐
│   ├── Minimax.cpp            ← Hard AI logic
│   └── Evaluation.cpp         ← Position scoring
├── player/
│   ├── PlayerManager.cpp      ← Player API ⭐
│   ├── Storage.cpp            ← File I/O for players
│   └── Player.cpp             ← Player base class
├── replay/
│   ├── FileManager.cpp        ← Replay file I/O ⭐
│   └── Replay.cpp             ← Replay storage
├── data/
│   ├── players.txt            ← Player statistics
│   ├── replays.txt            ← Replay file index
│   └── replay_*.txt           ← Stored game replays
└── docs/
    ├── ARCHITECTURE.md        ← This file (you are here)
    ├── FILE_INVENTORY.md      ← Detailed file listing
    └── QUICK_REFERENCE.md     ← Quick lookup
```

---

## 🔄 Luồng chính

### Vòng lặp trò chơi Human vs Bot

```
main()
  ↓
GameManager::mainMenu()
  ↓ (user chooses "Play")
Game::playHumanVsBot()
  ├─ Board::reset()
  ├─ Board::display()
  ├─ Loop while game not over:
  │  ├─ Game::askMove() ← Nhận input từ người dùng
  │  ├─ GameLogic::makeMove()
  │  ├─ Board::makeMove()
  │  ├─ Board::display()
  │  ├─ Check Board::checkWin() / Board::checkDraw()
  │  ├─ If not over:
  │  │  ├─ Bot::getNextMove()
  │  │  │  ├─ Easy: moveEasy() [random]
  │  │  │  ├─ Normal: moveNormal() [Evaluation]
  │  │  │  └─ Hard: moveHard() [Minimax]
  │  │  ├─ GameLogic::makeMove()
  │  │  ├─ Board::makeMove()
  │  │  ├─ Board::display()
  │  │  └─ Check win/draw
  │  └─ Continue...
  ├─ PlayerManager::updateResult()
  ├─ FileManager::saveReplay()
  └─ Return to menu

GameManager::mainMenu()  ← Back to menu
```

### Vòng lặp phát lại replay

```
Game::showSavedReplays()
  ├─ Read data/replays.txt
  ├─ Show numbered list
  ├─ Get user choice
  ├─ Call Game::playReplayFromFile(selected_file)
  │  ├─ FileManager::loadReplay()
  │  ├─ Board::reset()
  │  ├─ Board::display()
  │  ├─ Loop through each move:
  │  │  ├─ Print "Move N/Total - X at (row, col)"
  │  │  ├─ Board::makeMove()
  │  │  ├─ Board::display()
  │  │  └─ Wait for Enter
  │  └─ Print "Replay ended"
  └─ Return to menu
```

---

## 🎯 Tìm kiếm theo chủ đề

### Bàn cờ (Board)
- **File**: `core/Board.cpp`
- **Class**: `Board`
- **Key methods**: 
  - `makeMove(row, col, symbol)` - Đặt nước đi
  - `checkWin(row, col)` - Kiểm tra 5 liên tiếp
  - `checkDraw()` - Kiểm tra hòa
  - `display()` - In bàn cờ
- **Dữ liệu**: Ma trận `char board[10][10]`

### AI (Bot)
- **File**: `bot/Bot.cpp`, `bot/Minimax.cpp`, `bot/Evaluation.cpp`
- **Class**: `Bot`, `Minimax`
- **Key methods**:
  - `Bot::getNextMove()` - Lấy nước đi tiếp theo
  - `Minimax::findBestMove()` - Tìm nước đi tối ưu
  - `Evaluation::evaluate()` - Đánh giá vị trí
- **Mức độ khó**: Easy (random) → Normal (evaluation) → Hard (minimax)

### Người chơi (Player)
- **File**: `player/PlayerManager.cpp`, `player/Storage.cpp`
- **Class**: `Player`, `PlayerManager`, `Storage`
- **Key methods**:
  - `PlayerManager::registerPlayer()` - Đăng ký người chơi mới
  - `PlayerManager::updateResult()` - Cập nhật W/L/D
  - `Storage::loadFromFile()` - Tải từ file
  - `Storage::saveToFile()` - Lưu vào file
- **Dữ liệu**: `data/players.txt` (name wins losses draws)

### Replay (Trận đấu lưu trữ)
- **File**: `replay/Replay.cpp`, `replay/FileManager.cpp`
- **Class**: `Replay`, `FileManager`
- **Key methods**:
  - `Replay::addMove()` - Thêm nước đi
  - `FileManager::saveReplay()` - Lưu file
  - `FileManager::loadReplay()` - Tải file
- **Dữ liệu**: `data/replay_*.txt` (title + moves)

### Menu & UI
- **File**: `ui/Menu.cpp`, `ui/Game.cpp`
- **Class**: `Menu`, `Game`
- **Key methods**:
  - `Menu::showMainMenu()` - Menu chính
  - `Game::playHumanVsHuman()` - Chơi người vs người
  - `Game::playHumanVsBot()` - Chơi người vs bot
  - `Game::askMove()` - Nhận input

### Điều khiển (Main loop)
- **File**: `manager/GameManager.cpp`, `main.cpp`
- **Class**: `GameManager`
- **Key methods**:
  - `GameManager::mainMenu()` - Vòng lặp chính
- **Flow**: Menu → Game function → Save → Back to menu

---

## 💻 Lệnh hữu ích

### Biên dịch
```bash
cd GameCaro10x10
make          # Biên dịch
make run      # Biên dịch + chạy
make clean    # Xóa object files
```

### Chạy
```bash
./main.exe
```

### Piped input (test)
```bash
cat <<'EOF' | ./main.exe
1              # Chọn Play
1              # Chọn Human vs Human
0 0            # Nước đi thứ nhất
1 1            # Nước đi thứ hai
...
EOF
```

---

## 📊 Thống kê

- **Total files**: 29 (14 .h + 14 .cpp + 1 main.cpp)
- **Total lines**: ~2,310
- **Status**: ✅ All active (0 unused files)
- **Modules**: 7 (Core, Bot, Player, Replay, UI, Manager, Entry)
- **Key files** (⭐): Board, Bot, Game, PlayerManager, FileManager

---

## ⚡ Performance Tips

1. **AI hạnh chế độ sâu Minimax** (default 3-4) để tăng tốc độ
   - File: `bot/Minimax.cpp` → `findBestMove()` → depth parameter
   
2. **Tối ưu hóa `evaluate()`** nếu muốn AI nhanh hơn
   - File: `bot/Evaluation.cpp` → `evaluate()`
   
3. **Board size** cố định 10x10
   - File: `core/Board.h` → `static const int BOARD_SIZE = 10;`

---

## 🐛 Debugging

### Thêm debug output
```cpp
// File: ui/Game.cpp
std::cerr << "DEBUG: move = (" << row << ", " << col << ")\n";
```

### Xem dữ liệu file
```bash
cat data/players.txt      # Xem người chơi
cat data/replays.txt      # Xem danh sách replay
cat data/replay_*.txt     # Xem nước đi của 1 replay
```

### Compile với debug symbols
```bash
g++ -g -std=c++17 -Wall -Wextra main.cpp ... -o main.exe
gdb ./main.exe
```

---

**Created**: June 3, 2026  
**Version**: 1.0  
**Purpose**: Quick reference for navigating the codebase

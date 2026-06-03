# FILE INVENTORY - GameCaro 10x10

## Tóm tắt

- **Tổng file**: 29 (14 header + 14 implementation + 1 main)
- **Trạng thái**: ✅ **100% ACTIVE** - Không có dead code
- **Tổ chức**: 7 module rõ ràng

---

## 📊 DANH SÁCH ĐẦY ĐỦ

### ⚙️ CORE MODULE (3 files)

#### `core/Move.h` / `core/Move.cpp`
- **Purpose**: Định nghĩa cấu trúc dữ liệu cho một nước đi
- **Responsibility**: Lưu trữ hàng, cột, ký hiệu (X/O) của một nước đi
- **Key Members**: 
  - `int row`, `int col` - Vị trí trên bàn cờ
  - `char symbol` - Ký hiệu người chơi (X hoặc O)
  - Constructor, getters
- **Used By**: GameLogic, Replay, Board operations
- **Size**: ~30 lines (header + implementation)
- **Status**: ✅ ACTIVE - Core data structure

#### `core/Board.h` / `core/Board.cpp`
- **Purpose**: Quản lý bàn cờ 10x10 và logic kiểm tra thắng/hòa
- **Responsibility**: 
  - Lưu ma trận bàn cờ
  - Đặt nước đi
  - Kiểm tra 5 liên tiếp (thắng)
  - Kiểm tra bàn cờ đầy (hòa)
  - Hiển thị bàn cờ
- **Key Methods**:
  - `makeMove(row, col, symbol)` - Đặt nước đi
  - `checkWin(row, col)` - Kiểm tra có thắng không (4 hướng: ngang, dọc, 2 chéo)
  - `checkDraw()` - Kiểm tra hòa
  - `display()` - In bàn cờ ra console
  - `reset()` - Reset bàn cờ
  - `isBoardEmpty()` - Kiểm tra bàn cờ trống
  - `getPiece(row, col)` - Lấy ký hiệu tại vị trí
- **Dependencies**: Move (sử dụng Move để lưu nước đi)
- **Size**: ~250 lines
- **Status**: ✅ ACTIVE ⭐ - Critical (used by 5+ modules)
- **Algorithm**: Quét 4 hướng từ vị trí được đặt để kiểm tra 5 liên tiếp

#### `core/GameLogic.h` / `core/GameLogic.cpp`
- **Purpose**: Quản lý trạng thái trò chơi và lượt hiện tại
- **Responsibility**:
  - Quản lý ai là người chơi hiện tại (X/O)
  - Xác thực nước đi
  - Cập nhật trạng thái trò chơi
  - Reset trò chơi
- **Key Methods**:
  - `makeMove(row, col)` - Đặt nước đi của người chơi hiện tại
  - `switchPlayer()` - Chuyển sang lượt người chơi khác
  - `getCurrentPlayer()` - Lấy ký hiệu người chơi hiện tại
  - `isWinningMove(row, col)` - Kiểm tra nước đi có thắng không
  - `resetGame()` - Reset trò chơi
  - `isMoveValid(row, col)` - Kiểm tra nước đi hợp lệ
- **Dependencies**: Board, Move
- **Size**: ~150 lines
- **Status**: ✅ ACTIVE - Essential game state management

---

### 🤖 BOT AI MODULE (3 files)

#### `bot/Evaluation.h` / `bot/Evaluation.cpp`
- **Purpose**: Đánh giá điểm của một vị trí bàn cờ
- **Responsibility**: 
  - Tính toán score cho mỗi vị trí
  - Quét 4 hướng (ngang, dọc, 2 chéo)
  - Xếp điểm dựa trên số ký hiệu liên tiếp
- **Key Functions**:
  - `evaluate(Board& board, char symbol)` - Tính toán score tổng thể
  - Private helpers: `evaluateDirection(...)` - Quét một hướng
  - `countConsecutive(...)` - Đếm ký hiệu liên tiếp
- **Scoring Logic**:
  - 2-3 ký hiệu liên tiếp = điểm thấp
  - 3-4 ký hiệu liên tiếp = điểm trung bình
  - 4 ký hiệu liên tiếp (cạnh thắng) = điểm rất cao
  - Kiểm tra cả ký hiệu của bot (X) và người chơi (O)
- **Dependencies**: Board
- **Size**: ~200 lines
- **Status**: ✅ ACTIVE - AI intelligence core

#### `bot/Minimax.h` / `bot/Minimax.cpp`
- **Purpose**: Thuật toán Minimax với alpha-beta pruning để tìm nước đi tối ưu
- **Responsibility**:
  - Tìm kiếm nước đi tốt nhất cho chế độ Hard
  - Sử dụng alpha-beta pruning để tối ưu hóa
  - Phát hiện thắng/thua ngay lập tức
- **Key Methods**:
  - `findBestMove(Board& board, char symbol, int depth)` - Tìm nước đi tốt nhất
  - `findTopMoves(Board& board, char symbol, int topN)` - Tìm top N nước đi
  - `minimax(Board& board, int depth, int alpha, int beta, bool isMaximizing)` - Recursive minimax
  - `getScore(Board& board, char symbol, int depth)` - Lấy score của vị trí
- **Pruning**: Alpha-beta để cắt các nhánh vô ích
- **Depth**: Có thể cấu hình (mặc định 3-4 nước)
- **Dependencies**: Evaluation, Board
- **Size**: ~250 lines
- **Status**: ✅ ACTIVE - Hard AI logic

#### `bot/Bot.h` / `bot/Bot.cpp`
- **Purpose**: Lớp AI bot với 3 mức độ khó
- **Responsibility**:
  - Chọn nước đi dựa trên mức độ
  - Giao tiếp với Game class
- **Key Methods**:
  - `getNextMove(Board& board, char symbol)` - Lấy nước đi tiếp theo
  - `moveEasy(Board& board)` - Nước đi random (Easy)
  - `moveNormal(Board& board, char symbol)` - Nước đi heuristic (Normal)
  - `moveHard(Board& board, char symbol)` - Nước đi Minimax (Hard)
  - `setDifficulty(int level)` - Set độ khó
- **Difficulty Levels**:
  - **Easy (0)**: Random move từ danh sách nước đi hợp lệ
  - **Normal (1)**: Dùng Evaluation để chọn nước đi tốt nhất
  - **Hard (2)**: Dùng Minimax để tìm nước đi tối ưu
- **Dependencies**: Evaluation, Minimax, Board, Player (inheritance)
- **Size**: ~200 lines
- **Status**: ✅ ACTIVE ⭐ - Primary AI interface

---

### 👥 PLAYER MANAGEMENT MODULE (3 files)

#### `player/Player.h` / `player/Player.cpp`
- **Purpose**: Lớp cơ sở đại diện một người chơi
- **Responsibility**:
  - Lưu tên người chơi
  - Lưu ký hiệu (X hoặc O)
  - Polymorphic base class để Bot kế thừa
- **Key Methods**:
  - `getName()` - Lấy tên
  - `getSymbol()` - Lấy ký hiệu
  - `setName(name)` - Set tên
  - `setSymbol(symbol)` - Set ký hiệu
- **Inheritance**: Bot kế thừa từ Player
- **Size**: ~50 lines
- **Status**: ✅ ACTIVE - Foundation for polymorphism

#### `player/Storage.h` / `player/Storage.cpp`
- **Purpose**: Quản lý I/O file cho dữ liệu người chơi
- **Responsibility**:
  - Đọc file `data/players.txt`
  - Ghi file `data/players.txt`
  - Cập nhật thống kê người chơi
  - Tìm kiếm người chơi
- **Key Methods**:
  - `loadFromFile(filename)` - Đọc tất cả người chơi từ file
  - `saveToFile(filename)` - Ghi tất cả người chơi vào file
  - `updateResult(name, result)` - Cập nhật kết quả (Win/Loss/Draw)
  - `searchPlayer(name)` - Tìm người chơi theo tên
  - `displayAllPlayers()` - In danh sách người chơi
- **File Format**: `Name wins losses draws\n`
- **Dependencies**: None (standalone)
- **Size**: ~150 lines
- **Status**: ✅ ACTIVE - Data persistence

#### `player/PlayerManager.h` / `player/PlayerManager.cpp`
- **Purpose**: API cấp cao quản lý người chơi
- **Responsibility**:
  - Wrapper xung quanh Storage
  - Cung cấp interface clean cho Game
  - Quản lý vòng đời người chơi
- **Key Methods**:
  - `load()` - Tải danh sách người chơi từ file
  - `save()` - Lưu danh sách người chơi vào file
  - `registerPlayer(name)` - Đăng ký người chơi mới
  - `updateResult(name, result)` - Cập nhật kết quả
  - `findPlayer(name)` - Tìm người chơi
  - `printPlayers()` - In danh sách
- **Dependencies**: Storage, Player
- **Size**: ~150 lines
- **Status**: ✅ ACTIVE - High-level player API

---

### 🎬 REPLAY MODULE (2 files)

#### `replay/Replay.h` / `replay/Replay.cpp`
- **Purpose**: Lưu trữ lịch sử nước đi của một trận đấu
- **Responsibility**:
  - Lưu chuỗi nước đi
  - Lưu metadata (tên, ngày giờ)
  - Cung cấp interface để truy cập nước đi
- **Key Methods**:
  - `addMove(row, col, symbol)` - Thêm nước đi vào replay
  - `getMoves()` - Lấy tất cả nước đi
  - `getName()` - Lấy tên replay
  - `getDate()` - Lấy ngày giờ
  - `print()` - In replay
  - `setName(name)` - Set tên
  - `reset()` - Reset replay
- **Storage**: `std::vector<Move>` lưu tất cả nước đi
- **Dependencies**: Move
- **Size**: ~100 lines
- **Status**: ✅ ACTIVE - Game recording

#### `replay/FileManager.h` / `replay/FileManager.cpp`
- **Purpose**: I/O file cho replay
- **Responsibility**:
  - Lưu replay vào file
  - Tải replay từ file
  - Quản lý danh sách replay
- **Key Methods**:
  - `saveReplay(Replay& replay, filename)` - Lưu replay vào file
  - `loadReplay(Replay& replay, filename)` - Tải replay từ file
  - `loadAllReplays()` - Lấy danh sách tất cả replay
- **File Format**: 
  - Header: `title\n`
  - Nước đi: `row col symbol\n`
  - Ví dụ: `data/replay_Trinh_vs_Bot_20260603_162642.txt`
- **Index File**: `data/replays.txt` lưu danh sách đường dẫn
- **Timestamp**: Tự động thêm vào tên file để tránh xung đột
- **Dependencies**: Replay, Move
- **Size**: ~150 lines
- **Status**: ✅ ACTIVE ⭐ - Game persistence

---

### 🎮 UI & GAME FLOW MODULE (2 files)

#### `ui/Menu.h` / `ui/Menu.cpp`
- **Purpose**: Giao diện menu
- **Responsibility**:
  - Hiển thị menu chính
  - Hiển thị menu chọn chế độ chơi
  - Hiển thị menu chọn độ khó
  - Nhận input từ người dùng
- **Key Methods**:
  - `showMainMenu()` - Menu chính (Play/Players/Replays/Exit)
  - `showGameTypeMenu()` - Chọn chế độ (Human vs Human / Human vs Bot)
  - `showDifficultyMenu()` - Chọn độ khó (Easy/Normal/Hard)
  - `getMenuChoice()` - Nhận input từ người dùng
- **Input Method**: `std::getline()` + `std::istringstream` parsing
- **Language**: Tiếng Việt
- **Dependencies**: None
- **Size**: ~120 lines
- **Status**: ✅ ACTIVE - UI layer

#### `ui/Game.h` / `ui/Game.cpp`
- **Purpose**: Vòng lặp chơi chính
- **Responsibility**:
  - Điều khiển vòng lặp trò chơi
  - Nhận input nước đi từ người dùng
  - Gọi AI cho nước đi bot
  - Hiển thị bàn cờ
  - Kiểm tra thắng/hòa
  - Lưu kết quả
  - Quản lý replay
- **Key Methods**:
  - `playHumanVsHuman()` - Vòng lặp Human vs Human
  - `playHumanVsBot()` - Vòng lặp Human vs Bot
  - `showPlayers()` - Hiển thị danh sách người chơi
  - `showSavedReplays()` - Danh sách replay để xem
  - `playReplayFromFile(filename)` - Phát lại trận đấu
  - `askMove()` - Nhận input nước đi
  - `readPairOfInts()` - Parse input 2 số
- **Features**:
  - Hỗ trợ người chơi mới
  - Lưu thống kê người chơi
  - Lưu replay sau mỗi trận
  - Phát lại trận từng bước
- **Dependencies**: GameLogic, Board, Bot, PlayerManager, Replay, FileManager, Menu
- **Size**: ~400 lines
- **Status**: ✅ ACTIVE ⭐ - Core game coordinator

---

### 🎛️ APPLICATION CONTROL MODULE (1 file)

#### `manager/GameManager.h` / `manager/GameManager.cpp`
- **Purpose**: Điều phối ứng dụng cấp cao
- **Responsibility**:
  - Vòng lặp chính của ứng dụng
  - Kết nối menu với Game
  - Quản lý luồng điều khiển
- **Key Methods**:
  - `mainMenu()` - Vòng lặp menu chính
  - Constructor - Khởi tạo PlayerManager
- **Flow**:
  - Loop: Show menu → Get choice → Route to Game function
  - Menu options:
    1. Bắt đầu trận đấu mới
    2. Xem danh sách người chơi
    3. Xem replay
    0. Thoát chương trình
- **Dependencies**: Game, Menu, PlayerManager
- **Size**: ~100 lines
- **Status**: ✅ ACTIVE - Application router

---

### 🚀 ENTRY POINT (1 file)

#### `main.cpp`
- **Purpose**: Điểm khởi tạo ứng dụng
- **Responsibility**:
  - Tạo GameManager
  - Gọi mainMenu()
  - Return 0
- **Size**: ~10 lines
- **Status**: ✅ ACTIVE - Program entry

---

## 📈 PHÂN TÍCH SỬ DỤNG

### Độ phụ thuộc của từng file (mức độ sử dụng)

| Module | File | Used By Count | Criticality |
|--------|------|---------------|-------------|
| Core | Board | 5+ | ⭐⭐⭐⭐⭐ CRITICAL |
| Core | GameLogic | 2 | ⭐⭐⭐⭐ HIGH |
| Core | Move | 3 | ⭐⭐⭐⭐ HIGH |
| Bot | Bot | 1 | ⭐⭐⭐⭐ HIGH |
| Bot | Minimax | 1 | ⭐⭐⭐ MEDIUM |
| Bot | Evaluation | 1 | ⭐⭐⭐ MEDIUM |
| Player | PlayerManager | 2 | ⭐⭐⭐⭐ HIGH |
| Player | Storage | 1 | ⭐⭐⭐ MEDIUM |
| Player | Player | 2 | ⭐⭐⭐ MEDIUM |
| Replay | FileManager | 1 | ⭐⭐⭐⭐ HIGH |
| Replay | Replay | 1 | ⭐⭐⭐⭐ HIGH |
| UI | Game | 1 | ⭐⭐⭐⭐⭐ CRITICAL |
| UI | Menu | 2 | ⭐⭐⭐⭐ HIGH |
| Manager | GameManager | 1 | ⭐⭐⭐⭐ HIGH |

### Tổng kích thước code

| Module | Files | Lines of Code | Percentage |
|--------|-------|---------------|------------|
| Core | 3 | ~430 | 17% |
| Bot | 3 | ~650 | 26% |
| Player | 3 | ~350 | 14% |
| Replay | 2 | ~250 | 10% |
| UI | 2 | ~520 | 21% |
| Manager | 1 | ~100 | 4% |
| Entry | 1 | ~10 | <1% |
| **Total** | **15** | **~2,310** | **100%** |

---

## ✅ KIỂM ĐỊNH

### Kết luận
- **Không có file không được sử dụng** - 100% của codebase được sử dụng tích cực
- **Không có dead code** - Tất cả file đều phục vụ một chức năng rõ ràng
- **Tổ chức tốt** - 7 module rõ ràng, mỗi module có trách nhiệm duy nhất
- **Coupling thấp** - Các module độc lập, giao tiếp thông qua interface
- **Cohesion cao** - Mỗi file có một trách nhiệm

### Lời khuyên nếu muốn tối ưu hóa
1. ✅ Codebase hiện tại rất sạch, không cần xóa file nào
2. 💡 Có thể tách Game.cpp thành 2 file nếu muốn (Game logic vs UI)
3. 💡 Có thể thêm config file để quản lý constants (board size, depth AI, v.v.)
4. 💡 Có thể thêm logging utility cho debugging

---

**Ngày cập nhật**: June 3, 2026  
**Phiên bản**: 1.0  
**Trạng thái**: ✅ All files active and well-organized

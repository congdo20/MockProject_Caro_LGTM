# Project Architecture

"Mục tiêu"
Tài liệu này mô tả kiến trúc của dự án Caro 10x10, phân chia trách nhiệm giữa các module và hướng luồng dữ liệu chính.

"Tổng quan kiến trúc"
Ứng dụng được thiết kế theo hướng module hóa, mỗi thư mục đảm nhiệm một chức năng riêng:

- `core/`: logic trò chơi và cấu trúc dữ liệu bàn cờ.
- `player/`: quản lý người chơi và dữ liệu lưu trữ.
- `bot/`: AI và thuật toán đánh giá.
- `replay/`: ghi nhận và phát lại trận đấu.
- `ui/`: menu và điều khiển tương tác.
- `Manager/`: điều phối luồng chính và chuyển đổi chế độ chơi.

"Dòng chảy chính"

1. `main.cpp` khởi tạo `GameManager`.
2. `GameManager` hiển thị menu thông qua `ui/Menu`.
3. Khi chọn bắt đầu, `GameManager` gọi `ui/Game` để chạy vòng chơi.
4. `ui/Game` sử dụng `core/GameLogic` để quản lý lượt, đặt nước và kiểm tra thắng/hòa.
5. Với chế độ bot, `ui/Game` gọi `bot/Bot` để chọn nước đi.
6. Các trận đấu, người chơi và replay có thể được lưu lại trong `data/`.

## Thành phần chính

`core/`

- `Board`: lưu trữ ma trận 10x10, xuất bàn cờ và kiểm tra thắng/hòa.
- `GameLogic`: trạng thái trò chơi, lượt hiện tại, lịch sử nước đi và chuyển lượt.
- `Move`: định nghĩa 1 nước đi bao gồm hàng, cột và ký hiệu.

`player/`

- `Player`: lớp cơ sở người chơi.
- `PlayerManager`: quản lý đăng ký người chơi và hiển thị danh sách.
- `Storage`: đọc/ghi file `players.txt`, tìm kiếm và cập nhật dữ liệu.

`bot/`

- `Bot`: class bot AI với ba mức độ.
- `Minimax`: thuật toán tìm nước đi tốt nhất cho chế độ Hard.
- `Evaluation`: hàm đánh giá vị trí để hướng Minimax.

`replay/`

- `Replay`: ghi lại chuỗi nước đi và in lại trận đấu.
- `FileManager`: lưu / load replay vào file.

`ui/`

- `Menu`: menu chính và menu chọn chế độ.
- `Game`: điều khiển vòng lặp trò chơi, nhận input, chạy bot và in kết quả.

`Manager/`

- `GameManager`: tổng điều phối chương trình.
- Chịu trách nhiệm kết nối menu với logic chơi.

"Quan hệ giữa các module"

- `GameManager` ↔ `Menu` ↔ `Game`
- `Game` ↔ `GameLogic` ↔ `Board` ↔ `Move`
- `Game` ↔ `Bot` ↔ `Minimax`/`Evaluation`
- `PlayerManager` ↔ `Storage`
- `Replay` ↔ `FileManager`

"Dữ liệu và file"

- `data/players.txt`: lưu thông tin người chơi.
- `data/replays.txt`: có thể dùng để lưu lịch sử trận đấu.

"Mở rộng tương lai"

- Thêm chế độ chơi Online hoặc mạng LAN.
- Nâng cấp AI với thuật toán Alpha-Beta, heuristic mạnh hơn.
- Bổ sung giao diện đồ họa SDL/Qt.
- Xây dựng chức năng lưu và xem replay chi tiết.

"Lệnh biên dịch"
Từ thư mục `GameCaro10x10`:

```bash
g++ main.cpp Manager/*.cpp core/*.cpp player/*.cpp bot/*.cpp replay/*.cpp ui/*.cpp -o main.exe
```

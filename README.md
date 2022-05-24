# Tetris
# TetrisSDL
*Báo cáo kết quả thực hiện dự án làm game môn Lập Trình Nâng Cao INT 2215_1 K66-UET-VNU*
## 1. Hướng dẫn cài đặt
### Thư viện SDL2 sử dụng bao gồm :
* [SDL2 ](https://www.libsdl.org/download-2.0.php)
* [SDL2_Image ](https://www.libsdl.org/projects/SDL_image/)
* [SDL2_Ttf](https://www.libsdl.org/projects/SDL_ttf/) 
* [SDL2_Mixer](https://www.libsdl.org/projects/SDL_mixer/)
### Cách cài đặt:
*Làm theo những hướng dẫn sau để cài đặt thư viện vào CodeBlocks :*
* [SDL2 ](http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php)
* [SDL2_Image](http://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index.php) 
* SDL2_Mixer , SDL_Ttf cài đặt tương tự như SDL2_Image.
## 2. Mô tả chung:
### Người chơi săp xếp khối gạch để kiếm điểm tăng tiến cấp độ:
* Các khối gạch được sinh ra ngẫu nhiên và rơi xuống sau một khoảng thời gian nhất định của trò chơi.
* Khi các khối gạch lấp đầy một hàng các khối sẽ được xóa đi và cộng điểm cho người chơi.
* Với mỗi hàng được xóa đi người chơi sẽ được công điểm.
* Trò chơi chỉ kết thúc khi có một viên gạch chạm nóc và không thể sinh ra thêm.
## 3. Mô tả các chức năng trong trò chơi:
* Menu trò chơi.
* Âm thanh nền.
* Tính điểm số.
* Chơi lại nhiều lần.
* Các nút điều khiển cơ bản của trò chơi Tetris.
## 4. Các kĩ thuật lập trình được sử dụng: 
* Cấu trúc.
* Đồ họa.
* Mảng.
## 5. Kết luận:
### Hướng phát triển:
* thêm hiệu ứng khi một hàng được xóa đi hoặc khi tất cả các khối bị xóa đi
* Sử dụng các texture để biểu diễn các khối gạch trong game thay vì sử dụng các hàm vẽ khối chữ nhật cơ bản trong SDL
### Kết luận:
* Đây là game đầu tiên em tự code với rất nhiều bỡ ngỡ và thiếu sót(code chưa được clean,khó đọc).về việc tâm đắc với điều gì nhất thì em không có,em chỉ thấy bản thân còn nhiều thiếu sót cần khắc phục
* Tự đánh giá: 6-7;

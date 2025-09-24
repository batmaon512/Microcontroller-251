# Vi Điều Khiển - Vi Xử Lí (HK251)

Đây là kho lưu trữ chứa toàn bộ mã nguồn và tài liệu cho các bài thí nghiệm trong khuôn khổ học phần Vi xử lý - Vi điều khiển. Project tập trung vào việc lập trình cho vi điều khiển STM32, sử dụng thư viện HAL và mô phỏng trên Proteus.

---

## 🚀 Công nghệ sử dụng

*   **Ngôn ngữ lập trình:** C/C++
*   **Vi điều khiển:** STM32F103C6/...
*   **Thư viện:** STM32 HAL (Hardware Abstraction Layer)
*   **IDE:** STM32CubeIDE
*   **Mô phỏng:** Proteus 8 Professional

---

## 📂 Cấu trúc thư mục

Project được tổ chức thành các bài Lab riêng biệt, mỗi bài có cấu trúc như sau:

```
Microcontroller-251/
├── Lab/
│   ├── Lab1_LED_Animations/         # Bài Lab 1: Điều khiển LED cơ bản
│   │   ├── Source_Proteus/          # Chứa các file mô phỏng Proteus
│   │   └── Source_STM32/            # Chứa project STM32CubeIDE
│   │
│   ├── Lab2_Timer/                  # Bài Lab 2: Lập trình Timer
│   │   ├── SoureProtus/             # (Tương tự Lab 1)
│   │   └── SoureSTM32/              # (Tương tự Lab 1)
│   └── ...
└── README.md                        # File bạn đang đọc
```

---

## 🔬 Nội dung các bài thí nghiệm

### Lab 1: LED Animations

*   **Mục tiêu:** Làm quen với việc cấu hình chân GPIO (General Purpose Input/Output) ở chế độ Output và tạo các hiệu ứng LED đơn giản.
*   **Nội dung:** Viết chương trình cho 10 bài tập nhỏ, mỗi bài là một hiệu ứng chớp tắt LED khác nhau, giúp nắm vững cách điều khiển nhiều LED và sử dụng hàm `HAL_Delay()`.

### Lab 2: Timer & Advanced Displays

*   **Mục tiêu:** Nắm vững cách cấu hình và sử dụng Timer ở chế độ ngắt (Interrupt Mode) để tạo các tác vụ định thời, không làm block CPU.
*   **Nội dung:**
    *   **Software Timer:** Xây dựng một thư viện Software Timer đơn giản để quản lý nhiều tác vụ định thời cùng lúc.
    *   **Đồng hồ 7 đoạn:** Sử dụng Timer để quét 4 LED 7 đoạn, hiển thị đồng hồ thời gian thực (giờ, phút).
    *   **Ma trận LED 8x8:** Vận dụng kỹ thuật quét (scanning) và IC đệm (ULN2803) để hiển thị ký tự trên ma trận LED.

---

## 🛠️ Hướng dẫn cài đặt và chạy

Để chạy lại các bài thí nghiệm, bạn cần có các phần mềm đã nêu ở mục công nghệ.

### 1. Chạy project STM32

1.  Mở **STM32CubeIDE**.
2.  Chọn `File > Open Projects from File System...` và trỏ đến thư mục `Source_STM32` của bài Lab tương ứng.
3.  Hãy thay đổi macro `#define EXERCISE 1` để build bài tập cần chạy. 
4.  Nhấn `Project > Build All` (hoặc `Ctrl+B`) để biên dịch project. File `.hex` sẽ được tạo trong thư mục `Debug`.

### 2. Chạy mô phỏng Proteus

1.  Mở file `.pdsprj` của bài muốn chạy trong thư mục `Source_Proteus` (hoặc `SoureProtus`).
2.  Nháy đúp vào vi điều khiển STM32 trong sơ đồ mạch.
3.  Trong cửa sổ **Edit Component**, nhấn vào biểu tượng thư mục ở dòng **Program File**.
4.  Trỏ đến file `.hex` vừa được tạo ở bước trên (trong thư mục `Debug` của project STM32).
5.  Nhấn **OK** và sau đó nhấn nút **Play** ở góc dưới bên trái để bắt đầu mô phỏng.

---

## 👨‍💻 Tác giả

*   **Họ và tên:** Nguyễn Chí Thanh
*   **Giáo viên hướng dẫn:** TS. Lê Trọng Nhân
*   **GitHub:** [[Tại đây](https://github.com/batmaon512/Microcontroller-251)].

---

## 📄 Giấy phép

Project này được cấp phép dưới Giấy phép MIT - xem file `LICENSE` để biết thêm chi tiết (nếu có).

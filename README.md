# 📚 Cấu Trúc Dữ Liệu và Giải Thuật
 
> **Mã học phần:** MTH10405  
> **Học kỳ:** 1 — Năm học 2025–2026  
> **Ngôn ngữ lập trình:** C

---
 
## 📖 Nội Dung Lý Thuyết (Lectures)
 
### Lecture 1 — Why Data Structures Matter
> 📖 *Chương 1 — Why Data Structures Matter*
 
Giới thiệu khái niệm **cấu trúc dữ liệu** và tại sao việc lựa chọn đúng cấu trúc lại ảnh hưởng trực tiếp đến hiệu suất chương trình. Tập trung vào cấu trúc nền tảng là **mảng (Array)**:
 
- Bốn thao tác cơ bản: **Read, Search, Insert, Delete** — phân tích số bước thực hiện của từng thao tác
- So sánh **Array** và **Set**: Set thêm ràng buộc không trùng lặp → ảnh hưởng thế nào đến tốc độ Insert
- Hiểu rằng cùng một thao tác, cấu trúc dữ liệu khác nhau cho hiệu suất khác nhau
---
 
### Lecture 2 — Why Algorithms Matter
> 📖 *Chương 2 — Why Algorithms Matter*
 
Giới thiệu khái niệm **giải thuật (Algorithm)** qua bài toán tìm kiếm:
 
- **Mảng thường (Unsorted Array):** chỉ dùng được Linear Search — O(N)
- **Mảng có thứ tự (Ordered Array):** cho phép dùng **Binary Search** — mỗi bước loại bỏ phân nửa dữ liệu còn lại
- So sánh hiệu suất: với 1.000 phần tử, Linear Search cần tối đa 1.000 bước, Binary Search chỉ cần ~10 bước
- Bài học: **cấu trúc dữ liệu** quyết định **giải thuật** nào có thể áp dụng
---
 
### Lecture 3 — Big O Notation
> 📖 *Chương 3 — Oh Yes! Big O Notation*
 
Ngôn ngữ chính thức để đo và so sánh hiệu suất giải thuật:
 
- **O(1)** — Constant Time: số bước không đổi dù dữ liệu tăng (vd: đọc phần tử mảng)
- **O(N)** — Linear Time: số bước tỉ lệ thuận với kích thước dữ liệu (vd: Linear Search)
- **O(log N)** — Logarithmic Time: số bước tăng rất chậm (vd: Binary Search)
- Khái niệm **Logarithm**: log₂(N) = số lần chia đôi N cho đến khi còn 1
- Nguyên tắc: Big O đo **worst-case scenario** (trường hợp xấu nhất)
---
 
### Lecture 4 — Speeding Up Your Code With Big O
> 📖 *Chương 4 — Speeding Up Your Code with Big O*
 
Ứng dụng Big O để phân tích và cải thiện code qua thuật toán **Bubble Sort**:
 
- **Bubble Sort:** so sánh từng cặp phần tử kề nhau, đẩy phần tử lớn hơn về cuối — lặp lại nhiều lượt
- Độ phức tạp: **O(N²)** — với N phần tử cần ~N² bước so sánh
- Nhận biết **Quadratic Problem** (vòng lặp lồng nhau) và cách tìm giải pháp tuyến tính thay thế
- Biết khi nào O(N²) là chấp nhận được và khi nào cần tối ưu
---
 
### Lecture 5 — Optimizing Code With And Without Big O
> 📖 *Chương 5 — Optimizing Code with and Without Big O*
 
Phân tích sâu hơn về tối ưu, giới thiệu **Selection Sort**:
 
- **Selection Sort:** mỗi lượt tìm giá trị nhỏ nhất và đưa về đúng vị trí
- So sánh với Bubble Sort: cùng là O(N²) nhưng Selection Sort thực hiện **ít lần hoán đổi hơn** → nhanh hơn trong thực tế
- **Bỏ qua hằng số trong Big O:** O(N/2) vẫn được coi là O(N)
- Vai trò thực tế của Big O: phân loại giải thuật theo **bậc tăng trưởng**, không phải tính chính xác từng bước
---
 
### Lecture 6 — Optimizing For Optimistic Scenarios
> 📖 *Chương 6 — Optimizing for Optimistic Scenarios*
 
Giới thiệu **Insertion Sort** và tư duy phân tích đa kịch bản:
 
- **Insertion Sort:** lấy từng phần tử và chèn vào đúng vị trí trong phần đã sắp xếp
- Phân tích **3 kịch bản:** Best Case / Average Case / Worst Case
- Insertion Sort đạt **O(N)** khi mảng gần như đã sắp xếp — tốt hơn hẳn Bubble Sort và Selection Sort trong trường hợp này
- Bài học quan trọng: **Big O không phải yếu tố duy nhất** — kịch bản thực tế của dữ liệu cũng quyết định việc chọn thuật toán
---
 
### Lecture 7 — Blazing Fast Lookup With Hash Tables
> 📖 *Chương 7 — Blazing Fast Lookup with Hash Tables*
 
Giới thiệu **Hash Table** — cấu trúc dữ liệu cho phép tra cứu cực nhanh:
 
- **Hash Function:** chuyển đổi key thành chỉ số mảng → đọc/ghi đạt **O(1)**
- **Collision (xung đột):** hai key khác nhau cho cùng chỉ số → giải quyết bằng **Separate Chaining** (dùng mảng con)
- **Load Factor:** tỉ lệ số phần tử / kích thước bảng — ảnh hưởng đến hiệu suất
- Ứng dụng thực tế: xây dựng từ điển, tra cứu nhanh, loại bỏ phần tử trùng lặp
---
 
### Lecture 8 — Crafting Elegant Code With Stacks And Queues
> 📖 *Chương 8 — Crafting Elegant Code with Stacks and Queues*
 
Hai cấu trúc dữ liệu trừu tượng được xây dựng trên mảng hoặc danh sách liên kết:
 
- **Stack (Ngăn xếp):** LIFO — Last In, First Out. Thao tác: `push` (thêm vào đỉnh), `pop` (lấy từ đỉnh). Ứng dụng: kiểm tra ngoặc hợp lệ, tính biểu thức hậu tố, đảo ngược chuỗi
- **Queue (Hàng đợi):** FIFO — First In, First Out. Thao tác: `enqueue` (thêm vào cuối), `dequeue` (lấy từ đầu). Ứng dụng: quản lý tác vụ, hàng đợi in ấn, hệ thống đăng ký
---
 
### Lecture 9 — Recursively Recurse With Recursion
> 📖 *Chương 9 — Recursively Recurse with Recursion*
 
Nền tảng của đệ quy — một trong những kỹ thuật quan trọng nhất trong lập trình:
 
- **Đệ quy (Recursion):** hàm tự gọi chính nó để giải quyết bài toán nhỏ hơn
- **Base Case (Trường hợp cơ sở):** điều kiện dừng đệ quy — **bắt buộc phải có** để tránh vòng lặp vô tận
- **Call Stack:** mỗi lời gọi đệ quy được đẩy vào stack → hiểu cơ chế thực thi
- Cách đọc và viết code đệ quy: phân tích từ base case trước, rồi mới đến bước đệ quy
---
 
### Lecture 10 — Recursive Algorithms for Speed
> 📖 *Chương 10 — Recursive Algorithms for Speed*
 
Ứng dụng đệ quy vào các thuật toán sắp xếp và tìm kiếm hiệu suất cao:
 
- **Partitioning:** chọn pivot, đưa tất cả phần tử nhỏ hơn sang trái, lớn hơn sang phải — O(N)
- **Quicksort:** đệ quy partition hai nửa → trung bình **O(N log N)**, tốt nhất trong các thuật toán sắp xếp thực tế
- **Worst Case của Quicksort:** O(N²) khi mảng đã sắp xếp và pivot luôn là phần tử nhỏ/lớn nhất
- **Quickselect:** tìm phần tử thứ K mà không cần sắp xếp toàn bộ — **O(N)** trung bình
---
 
### Lecture 11 — Node-based Data Structures
> 📖 *Chương 11 — Node-Based Data Structures*
 
Giới thiệu cấu trúc dữ liệu dựa trên **Node** — linh hoạt hơn mảng:
 
- **Linked List (Danh sách liên kết đơn):** mỗi node chứa dữ liệu + con trỏ đến node tiếp theo
- So sánh với Array: Insert/Delete đầu danh sách đạt **O(1)** (mảng cần O(N) để dịch chuyển), nhưng Read là **O(N)**
- **Doubly Linked List (Danh sách liên kết đôi):** mỗi node có con trỏ hai chiều → hỗ trợ duyệt ngược
- Ứng dụng: làm nền tảng cho Stack, Queue và các cấu trúc phức tạp hơn
---
 
### Lecture 12 — Speeding Up All The Things With Binary Trees
> 📖 *Chương 12 — Speeding Up All the Things with Binary Trees*
 
Cấu trúc cây nhị phân tìm kiếm — kết hợp ưu điểm của mảng có thứ tự và danh sách liên kết:
 
- **Binary Search Tree (BST):** mỗi node có tối đa 2 con; node trái < node hiện tại < node phải
- **Search:** O(log N) — tương tự Binary Search trên mảng
- **Insertion:** O(log N) — không cần dịch chuyển phần tử như mảng
- **Deletion:** 3 trường hợp: node không có con, có 1 con, có 2 con (phức tạp nhất — dùng in-order successor)
- Ứng dụng thực tế: cơ sở dữ liệu, hệ thống file, auto-complete
 
## 🧪 Nội Dung Thực Hành (Labs)
 
| Lab | Chủ đề | Nội dung |
|-----|--------|----------|
| 01 | Arrays and Sets | Thao tác cơ bản trên mảng; so sánh Array vs Set |
| 02 | Binary Search | Cài đặt tìm kiếm nhị phân trên mảng có thứ tự |
| 03 | Big O | Phân tích độ phức tạp của các đoạn code |
| 04 | Bubble Sort | Cài đặt và phân tích Bubble Sort |
| 05 | Sort Algorithms | So sánh Selection Sort, Insertion Sort, Shell Sort |
| 06 | Stacks and Queues | Cài đặt Stack và Queue; bài toán ứng dụng |
| 07 | Recursion | Viết hàm đệ quy; phân tích base case |
| 08 | Quick Sort | Cài đặt Partition và Quicksort |
| 09 | Linked List | Cài đặt Linked List; các thao tác Insert, Delete, Search |
| 10 | Binary Tree | Cài đặt BST; Insert, Search, Delete node |
 
---

## 📌 Ghi Chú

- Chỉ push những bài tập không quá dễ.
- Các file ảnh `.png` là đề bài cho các bài tập.
- Mỗi file `.c` tương ứng với một bài tập hoặc ví dụ trong tuần học thực hành.
- Tên file theo quy tắc: `<cấu-trúc-hoặc-thuật-toán>-<tên-bài>.c`
---

*coded by Nguyen Dang Nhan (24280038)*

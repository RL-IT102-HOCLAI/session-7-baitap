# BÀI TẬP 01: DÒ VẾT LỖI STRUCT THIẾT BỊ THÔNG MINH

## 1. Phân tích lỗi logic

Lỗi nằm ở thứ tự thực hiện các câu lệnh cập nhật thuộc tính của struct `SmartDevice`.

Trong mã nguồn ban đầu, chương trình tính công suất trước:

```c
heater.power_watt = heater.voltage * heater.current;
```

Sau đó, chương trình kiểm tra dòng điện có vượt quá 30 A hay không. Nếu vượt ngưỡng, chương trình cập nhật:

```c
heater.is_overloaded = 1;
heater.is_active = 0;
```

Tuy nhiên, chương trình không cập nhật lại `heater.power_watt` về `0.0f` sau khi thiết bị bị ngắt điện.

Với điện áp 220 V và dòng điện 35 A, công suất ban đầu được tính là:

`P = 220 × 35 = 7700 W`

Khi dòng điện vượt quá 30 A, thiết bị được chuyển sang trạng thái tắt nhưng công suất vẫn giữ giá trị 7700 W. Điều này vi phạm quy tắc nghiệp vụ vì thiết bị đã tắt thì công suất phải bằng 0 W.

**Cách sửa:** Khi phát hiện quá tải, đặt `is_overloaded = 1`, chuyển `is_active = 0` và cập nhật ngay `power_watt = 0.0f`. Ngoài ra, khi thiết bị đang tắt ngay từ đầu, chương trình cũng phải đảm bảo công suất bằng 0 W.

## 2. Bảng Test Cases

| Trường hợp kiểm thử | Dữ liệu đầu vào | Kết quả sai thực tế | Kết quả đúng mong đợi |
|---|---|---|---|
| TC01 - Dòng điện vượt ngưỡng an toàn | `voltage = 220.0`, `current = 35.0`, `is_active = 1` | Trạng thái TẮT, cảnh báo quá tải CÓ, nhưng công suất vẫn là 7700 W | Trạng thái TẮT, cảnh báo quá tải CÓ, công suất bằng 0 W |
| TC02 - Thiết bị đang tắt | `voltage = 220.0`, `current = 5.0`, `is_active = 0` | Nếu vẫn tính công suất theo `V × I`, công suất sẽ là 1100 W dù thiết bị đang tắt | Trạng thái TẮT, công suất bằng 0 W |

## 3. Kết luận

Nguyên nhân gây lỗi là chương trình tính công suất mà không đảm bảo tính nhất quán giữa `power_watt` và `is_active`.

Cần xử lý trạng thái hoạt động trước khi xác định công suất cuối cùng. Khi thiết bị tắt hoặc bị ngắt do quá tải, công suất phải được cập nhật về 0 W.

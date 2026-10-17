1. Phân tích bài toán (Input/Output)
Input
- Cấu trúc SmartDevice:
  - deviceID: mã thiết bị.
  - deviceName: tên thiết bị.
  - status: trạng thái bật/tắt.
  - ratedPowerKW: công suất định mức (kW).
- Cấu trúc EnergySensor:
  - voltageVolts: điện áp (V).
  - currentAmperes: dòng điện (A).
  - unoccupancyMinutes: thời gian phòng trống (phút).
- Biến phụ trợ operatingHours: số giờ hoạt động trong tháng, từ lớn hơn 0 đến tối đa 744 giờ.
Output
- Trạng thái thiết bị sau khi kiểm tra an toàn và phòng trống.
- Cảnh báo quá tải nếu dòng điện vượt 30 A.
- Thông báo tự động tắt nếu phòng trống từ 15 phút trở lên.
- Tổng điện năng tiêu thụ (kWh).
- Tổng tiền điện dự kiến chưa bao gồm VAT.
2. Đề xuất giải pháp
Sử dụng hai biến cấu trúc riêng biệt device và sensor. Truy cập các thuộc tính bằng dấu chấm, ví dụ sensor.currentAmperes hoặc device.status.
Thứ tự xử lý:
1. Nhập dữ liệu cho thiết bị và cảm biến.
2. Kiểm tra điện áp, dòng điện và thời gian phòng trống. Nếu dữ liệu âm, thông báo lỗi và kết thúc chương trình.
3. Kiểm tra thời gian vận hành trong tháng, yêu cầu lớn hơn 0 và không vượt quá 744 giờ.
4. Nếu dòng điện lớn hơn 30 A, ngắt thiết bị và thông báo cảnh báo.
5. Nếu thiết bị vẫn bật và phòng trống từ 15 phút trở lên, tự động tắt thiết bị.
6. Tính điện năng tiêu thụ theo công suất định mức và số giờ vận hành.
7. Tính tiền điện theo bốn bậc giá được đề bài cung cấp.
8. In kết quả.

Giải thích cách tính tiền điện
Tiền điện được tính theo kiểu lũy tiến từng bậc, không lấy toàn bộ điện năng nhân với giá của bậc cao nhất.
Bậc	Điện năng	Đơn giá
1	50 kWh đầu	1.806 đ/kWh
2	50 kWh tiếp theo	1.866 đ/kWh
3	100 kWh tiếp theo	2.167 đ/kWh
4	Phần vượt 200 kWh	2.729 đ/kWh
Ví dụ, nếu tiêu thụ 250 kWh:
- 50 kWh × 1.806 = 90.300 đ
- 50 kWh × 1.866 = 93.300 đ
- 100 kWh × 2.167 = 216.700 đ
- 50 kWh × 2.729 = 136.450 đ
Tổng tiền điện là 536.750 VNĐ, chưa bao gồm VAT.
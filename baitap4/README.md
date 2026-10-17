1. Phân tích Input / Output
Input	Ý nghĩa
Mã, tên thiết bị	Nhận diện điều hòa và đèn
Trạng thái, công suất	Bật/tắt và công suất của từng thiết bị
Điện áp, dòng điện	Chỉ số cảm biến năng lượng
Thời gian phòng trống	Kiểm tra điều kiện tự động tắt điều hòa
Thời gian sử dụng	Ước tính điện năng tiêu thụ
Output	Ý nghĩa
Dashboard thiết bị	Hiển thị trạng thái và công suất
Dashboard cảm biến	Hiển thị điện áp, dòng điện, thời gian phòng trống
Báo cáo năng lượng	Tổng công suất, tổng dòng điện, kWh và chi phí
Cảnh báo	Báo quá tải nếu tổng dòng điện lớn hơn 30A
2. Các bước thiết kế
1. Khai báo ba kiểu struct: SmartDevice, EnergySensor, PowerReport.
2. Khởi tạo riêng hai biến thiết bị: điều hòa và đèn.
3. Nếu phòng trống hơn 15 phút, đặt trạng thái điều hòa bằng 0 và công suất bằng 0.
4. Tính tổng công suất và dòng điện sau khi thực hiện tự động hóa.
5. Tính điện năng tiêu thụ theo thời gian sử dụng, sau đó ước tính chi phí theo giá điện bậc thang.
6. In dashboard và cảnh báo an toàn.
1. Phân tích Input/Output
Input:
- Mã thiết bị: deviceID.
- Trạng thái: status (0 = tắt, 1 = bật).
- Điện áp \(U\), đơn vị V.
- Dòng điện \(I\), đơn vị A.
- Công suất đo được \(P\), đơn vị W.
- Thời gian hoạt động \(t\), đơn vị phút.
Output:
- Kích thước bộ nhớ của struct chưa tối ưu và struct đã tối ưu.
- Công suất tính toán \(P_{calc}=U\times I\).
- Cảnh báo cảm biến công suất sai lệch nếu chênh lệch vượt 5%.
- Cảnh báo quá tải nếu \(I>30A\) hoặc \(P>6600W\).
- Cảnh báo rò rỉ điện hoặc tải ẩn nếu thiết bị tắt nhưng \(I>0.05A\).
- Điện năng tiêu thụ tính bằng kWh.
- Thông báo lỗi và dừng xử lý nếu dữ liệu đầu vào không hợp lệ.
2. Hai giải pháp tái cấu trúc struct
Giải pháp 1: Sắp xếp lại thành phần trong struct phẳng
Giữ các thuộc tính trong cùng một struct, nhưng sắp xếp các thành phần cần căn chỉnh lớn trước, các thành phần kiểu char sau.
Ví dụ:
struct OptimizedDevice
{
    int deviceID;
    int status;
    int operatingMinutes;
    float voltage;
    float current;
    float measuredPower;
    char deviceName[20];
    char unitSymbol;
    char statusLabel;
};


Cách này giúp giảm padding trong những trường hợp các trường kiểu char được đặt xen kẽ với các trường int và float.
Giải pháp 2: Gom nhóm bằng struct lồng nhau
Tách dữ liệu thành các nhóm có cùng chức năng, chẳng hạn thông tin thiết bị và thông số đo lường.
struct DeviceInfo
{
    int deviceID;
    int status;
    char deviceName[20];
};

struct SensorData
{
    float voltage;
    float current;
    float measuredPower;
};

struct SmartDeviceNested
{
    struct DeviceInfo info;
    struct SensorData sensor;
    int operatingMinutes;
};


Khi sử dụng, cần truy cập qua nhiều dấu chấm, ví dụ device.info.deviceID và device.sensor.voltage.
Lưu ý: struct lồng nhau giúp tổ chức và bảo trì dữ liệu tốt hơn, nhưng không đảm bảo kích thước bộ nhớ nhỏ hơn. Kích thước thực tế còn phụ thuộc vào cách căn chỉnh của trình biên dịch.
3. Bảng so sánh và lựa chọn
Tiêu chí	Struct phẳng tối ưu	Struct lồng nhau
sizeof	Có thể giảm padding nếu sắp xếp hợp lý	Có thể giữ nguyên hoặc tăng do căn chỉnh
Truy xuất thành phần	Đơn giản, ví dụ device.voltage	Nhiều cấp, ví dụ device.sensor.voltage
Dễ bảo trì	Phù hợp cấu trúc nhỏ, ít nhóm dữ liệu	Tốt khi dữ liệu có nhiều nhóm chức năng
Khả năng mở rộng	Có thể khó quản lý khi số trường tăng	Dễ mở rộng từng nhóm riêng
Phù hợp bài toán	Tối ưu RAM và thao tác trực tiếp	Ưu tiên tính tổ chức và đóng gói
Lựa chọn: Với yêu cầu của bài tập là giảm kích thước struct trên IoT Gateway có RAM hạn chế, chọn struct phẳng tối ưu làm phương án chính. Sau đó kiểm chứng bằng sizeof() trên đúng trình biên dịch và nền tảng mục tiêu, thay vì giả định rằng mọi cách sắp xếp đều làm giảm kích thước.
4. Các bước xử lý và mã giả
1. Khai báo struct chưa tối ưu và struct đã tối ưu.
2. In kích thước hai struct bằng sizeof.
3. Nhập thông tin thiết bị và các thông số đo được.
4. Kiểm tra dữ liệu: \(U>0\), \(I\geq0\), \(t\geq0\), công suất đo được không âm và status chỉ nhận 0 hoặc 1. Nếu sai, thông báo lỗi và dừng chương trình.
5. Tính \(P_{calc}=U\times I\).
6. Kiểm tra độ lệch công suất, quá tải và rò rỉ điện.
7. Tính điện năng tiêu thụ theo thời gian hoạt động.
8. In báo cáo.
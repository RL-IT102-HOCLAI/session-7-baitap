#include <stdio.h>
#include <string.h>

struct UnoptimizedDevice
{
    char deviceName[20];
    char unitSymbol;
    float voltage;
    char statusLabel;
    float current;
    float measuredPower;
    int deviceID;
    int status;
    int operatingMinutes;
};

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

int main()
{
    struct UnoptimizedDevice oldDevice;
    struct OptimizedDevice device;

    float calculatedPower;
    float powerDifference;
    float energyKWh;

    printf("===== SO SANH KICH THUOC STRUCT =====\n");
    printf("Struct chua toi uu: %zu bytes\n",
           sizeof(oldDevice));
    printf("Struct da toi uu: %zu bytes\n",
           sizeof(device));

    printf("\n===== NHAP THONG TIN THIET BI =====\n");

    printf("Nhap ma thiet bi: ");
    scanf("%d", &device.deviceID);
    while (getchar() != '\n');

    printf("Nhap ten thiet bi: ");
    fgets(device.deviceName, sizeof(device.deviceName), stdin);

    size_t len = strlen(device.deviceName);
    if (len > 0 && device.deviceName[len - 1] == '\n')
    {
        device.deviceName[len - 1] = '\0';
    }

    printf("Nhap trang thai (1: Bat, 0: Tat): ");
    scanf("%d", &device.status);

    printf("Nhap dien ap (V): ");
    scanf("%f", &device.voltage);

    printf("Nhap dong dien (A): ");
    scanf("%f", &device.current);

    printf("Nhap cong suat do duoc (W): ");
    scanf("%f", &device.measuredPower);

    printf("Nhap thoi gian hoat dong (phut): ");
    scanf("%d", &device.operatingMinutes);

    if (device.voltage <= 0 ||
        device.current < 0 ||
        device.measuredPower < 0 ||
        device.operatingMinutes < 0)
    {
        printf("\nLoi: Du lieu cam bien khong hop le!\n");
        return 1;
    }

    if (device.status != 0 && device.status != 1)
    {
        printf("\nLoi: Trang thai thiet bi khong hop le!\n");
        return 1;
    }

    device.unitSymbol = 'W';
    device.statusLabel = device.status == 1 ? 'B' : 'T';

    calculatedPower = device.voltage * device.current;

    printf("\n===== BAO CAO GIAM SAT DIEN NANG =====\n");
    printf("Ma thiet bi: %d\n", device.deviceID);
    printf("Ten thiet bi: %s\n", device.deviceName);
    printf("Trang thai: %s\n",
           device.status == 1 ? "BAT" : "TAT");

    printf("Dien ap: %.2f V\n", device.voltage);
    printf("Dong dien: %.2f A\n", device.current);
    printf("Cong suat do duoc: %.2f %c\n",
           device.measuredPower, device.unitSymbol);
    printf("Cong suat tinh toan: %.2f W\n", calculatedPower);

    powerDifference = device.measuredPower - calculatedPower;

    if (powerDifference < 0)
    {
        powerDifference = -powerDifference;
    }

    if ((calculatedPower == 0 && device.measuredPower > 0) ||
        (calculatedPower > 0 &&
         powerDifference / calculatedPower * 100.0f > 5.0f))
    {
        printf("CANH BAO: Cam bien cong suat bao sai lech!\n");
    }
    else
    {
        printf("Cam bien cong suat hoat dong binh thuong.\n");
    }

    if (device.current > 30.0f ||
        device.measuredPower > 6600.0f)
    {
        printf("CANH BAO: QUA TAI NGUY HIEM!\n");
    }

    if (device.status == 0 && device.current > 0.05f)
    {
        printf("CANH BAO: RO RI DIEN HOAC TAI AN!\n");
    }

    energyKWh = device.measuredPower *
                (device.operatingMinutes / 60.0f) / 1000.0f;

    printf("Thoi gian hoat dong: %d phut\n",
           device.operatingMinutes);
    printf("Dien nang tieu thu: %.4f kWh\n", energyKWh);

    return 0;
}

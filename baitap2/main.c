#include <stdio.h>

struct SmartDevice
{
    int deviceID;
    char deviceName[100];
    int status;
    float ratedPowerKW;
};

struct EnergySensor
{
    float voltageVolts;
    float currentAmperes;
    int unoccupancyMinutes;
};

int main()
{
    struct SmartDevice device;
    struct EnergySensor sensor;

    float operatingHours;
    float energyKWh;
    double electricityCost = 0.0;

    printf("===== SMART HOME ENERGY MANAGEMENT =====\n");

    printf("Nhap ma thiet bi: ");
    scanf("%d", &device.deviceID);
    while (getchar() != '\n');

    printf("Nhap ten thiet bi: ");
    fgets(device.deviceName, sizeof(device.deviceName), stdin);

    int i = 0;
    while (device.deviceName[i] != '\0')
    {
        if (device.deviceName[i] == '\n')
        {
            device.deviceName[i] = '\0';
            break;
        }
        i++;
    }

    printf("Nhap trang thai (1: Bat, 0: Tat): ");
    scanf("%d", &device.status);

    printf("Nhap cong suat dinh muc (kW): ");
    scanf("%f", &device.ratedPowerKW);

    printf("Nhap dien ap (V): ");
    scanf("%f", &sensor.voltageVolts);

    printf("Nhap dong dien (A): ");
    scanf("%f", &sensor.currentAmperes);

    printf("Nhap thoi gian phong trong (phut): ");
    scanf("%d", &sensor.unoccupancyMinutes);

    printf("Nhap so gio hoat dong trong thang: ");
    scanf("%f", &operatingHours);

    if (sensor.voltageVolts < 0 ||
        sensor.currentAmperes < 0 ||
        sensor.unoccupancyMinutes < 0)
    {
        printf("\nLoi: Du lieu cam bien khong hop le!\n");
        return 1;
    }

    if (device.status != 0 && device.status != 1)
    {
        printf("\nLoi: Trang thai thiet bi khong hop le!\n");
        return 1;
    }

    if (device.ratedPowerKW < 0)
    {
        printf("\nLoi: Cong suat dinh muc khong hop le!\n");
        return 1;
    }

    if (operatingHours <= 0 || operatingHours > 744)
    {
        printf("\nLoi: So gio hoat dong phai lon hon 0 va khong vuot qua 744!\n");
        return 1;
    }

    printf("\n===== XU LY THIET BI =====\n");

    if (sensor.currentAmperes > 30.0f)
    {
        device.status = 0;
        printf("CANH BAO: Dong dien qua tai! Nguy co chay no!\n");
        printf("He thong da tu dong ngat dien.\n");
    }
    else if (device.status == 1 &&
             sensor.unoccupancyMinutes >= 15)
    {
        device.status = 0;
        printf("Phong vang nguoi tu 15 phut tro len.\n");
        printf("He thong da tu dong tat thiet bi de tiet kiem dien.\n");
    }

    printf("Ma thiet bi: %d\n", device.deviceID);
    printf("Ten thiet bi: %s\n", device.deviceName);
    printf("Trang thai: %s\n", device.status == 1 ? "BAT" : "TAT");

    energyKWh = device.ratedPowerKW * operatingHours;

    if (energyKWh <= 50)
    {
        electricityCost = energyKWh * 1806;
    }
    else if (energyKWh <= 100)
    {
        electricityCost = 50 * 1806 +
                          (energyKWh - 50) * 1866;
    }
    else if (energyKWh <= 200)
    {
        electricityCost = 50 * 1806 +
                          50 * 1866 +
                          (energyKWh - 100) * 2167;
    }
    else
    {
        electricityCost = 50 * 1806 +
                          50 * 1866 +
                          100 * 2167 +
                          (energyKWh - 200) * 2729;
    }

    printf("\n===== BAO CAO DIEN NANG =====\n");
    printf("Dien ap: %.2f V\n", sensor.voltageVolts);
    printf("Dong dien: %.2f A\n", sensor.currentAmperes);
    printf("Cong suat dinh muc: %.2f kW\n", device.ratedPowerKW);
    printf("So gio hoat dong: %.2f gio\n", operatingHours);
    printf("Tong dien nang: %.2f kWh\n", energyKWh);
    printf("Tien dien du kien: %.0f VND\n", electricityCost);
    printf("Chi phi chua bao gom VAT.\n");

    return 0;
}

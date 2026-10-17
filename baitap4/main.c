#include <stdio.h>
#include <string.h>

struct SmartDevice
{
    int deviceId;
    char deviceName[50];
    int status;
    float powerWatt;
};

struct EnergySensor
{
    float voltage;
    float currentAmp;
    int emptyMinutes;
};

struct PowerReport
{
    float totalPowerWatt;
    float totalCurrentAmp;
    float energyKWh;
    int overloadWarning;
    float estimatedCost;
};

int main()
{
    struct SmartDevice airConditioner;
    struct SmartDevice lighting;
    struct EnergySensor sensor;
    struct PowerReport report;

    float operatingHours = 8.0f;
    float remainingEnergy;
    float tierEnergy;
    float electricityCost = 0.0f;

    airConditioner.deviceId = 1;
    strcpy(airConditioner.deviceName, "Dieu hoa");
    airConditioner.status = 1;
    airConditioner.powerWatt = 6500.0f;

    lighting.deviceId = 2;
    strcpy(lighting.deviceName, "Den chieu sang");
    lighting.status = 1;
    lighting.powerWatt = 500.0f;

    sensor.voltage = 220.0f;
    sensor.currentAmp = 0.0f;
    sensor.emptyMinutes = 10;

    printf("===============================================\n");
    printf("       RKHOME SMART HOME CENTRAL GATEWAY\n");
    printf("===============================================\n");

    printf("\n--- KIEM TRA CAM BIEN HIEN DIEN ---\n");
    printf("Dien ap: %.2f V\n", sensor.voltage);
    printf("Thoi gian phong trong: %d phut\n",
           sensor.emptyMinutes);

    if (sensor.emptyMinutes > 15)
    {
        airConditioner.status = 0;
        airConditioner.powerWatt = 0.0f;

        printf("Tu dong hoa: Phong trong hon 15 phut.\n");
        printf("Da tu dong tat dieu hoa.\n");
    }
    else
    {
        printf("Tu dong hoa: Chua can tat dieu hoa.\n");
    }

    if (airConditioner.status == 0)
    {
        airConditioner.powerWatt = 0.0f;
    }

    if (lighting.status == 0)
    {
        lighting.powerWatt = 0.0f;
    }

    report.totalPowerWatt =
        airConditioner.powerWatt + lighting.powerWatt;

    if (sensor.voltage > 0.0f)
    {
        report.totalCurrentAmp =
            report.totalPowerWatt / sensor.voltage;
    }
    else
    {
        printf("Loi: Dien ap phai lon hon 0 V.\n");
        return 1;
    }

    sensor.currentAmp = report.totalCurrentAmp;

    report.overloadWarning =
        report.totalCurrentAmp > 30.0f ? 1 : 0;

    report.energyKWh =
        report.totalPowerWatt * operatingHours / 1000.0f;

    remainingEnergy = report.energyKWh;

    if (remainingEnergy > 50.0f)
    {
        tierEnergy = 50.0f;
    }
    else
    {
        tierEnergy = remainingEnergy;
    }

    electricityCost += tierEnergy * 1806.0f;
    remainingEnergy -= tierEnergy;

    if (remainingEnergy > 0.0f)
    {
        if (remainingEnergy > 50.0f)
        {
            tierEnergy = 50.0f;
        }
        else
        {
            tierEnergy = remainingEnergy;
        }

        electricityCost += tierEnergy * 1866.0f;
        remainingEnergy -= tierEnergy;
    }

    if (remainingEnergy > 0.0f)
    {
        if (remainingEnergy > 100.0f)
        {
            tierEnergy = 100.0f;
        }
        else
        {
            tierEnergy = remainingEnergy;
        }

        electricityCost += tierEnergy * 2167.0f;
        remainingEnergy -= tierEnergy;
    }

    if (remainingEnergy > 0.0f)
    {
        electricityCost += remainingEnergy * 2729.0f;
    }

    report.estimatedCost = electricityCost;

    printf("\n--- DASHBOARD THIET BI ---\n");
    printf("%-8s %-22s %-12s %12s\n",
           "Ma", "Ten thiet bi", "Trang thai", "Cong suat");
    printf("-------------------------------------------------------\n");

    printf("%-8d %-22s %-12s %9.2f W\n",
           airConditioner.deviceId,
           airConditioner.deviceName,
           airConditioner.status == 1 ? "BAT" : "TAT",
           airConditioner.powerWatt);

    printf("%-8d %-22s %-12s %9.2f W\n",
           lighting.deviceId,
           lighting.deviceName,
           lighting.status == 1 ? "BAT" : "TAT",
           lighting.powerWatt);

    printf("\n--- DASHBOARD CAM BIEN NANG LUONG ---\n");
    printf("Dien ap van hanh:       %.2f V\n",
           sensor.voltage);
    printf("Dong dien tong:         %.2f A\n",
           sensor.currentAmp);
    printf("Thoi gian phong trong:  %d phut\n",
           sensor.emptyMinutes);

    printf("\n--- BAO CAO TONG HOP NANG LUONG ---\n");
    printf("Tong cong suat tai:     %.2f W\n",
           report.totalPowerWatt);
    printf("Tong dong dien:         %.2f A\n",
           report.totalCurrentAmp);
    printf("Thoi gian tinh dien:    %.2f gio\n",
           operatingHours);
    printf("Dien nang tieu thu:     %.3f kWh\n",
           report.energyKWh);
    printf("Chi phi dien uoc tinh:  %.0f VND\n",
           report.estimatedCost);

    printf("\n--- TRANG THAI AN TOAN ---\n");

    if (report.overloadWarning == 1)
    {
        printf("CANH BAO NGUY HIEM: TONG DONG DIEN VUOT 30A!\n");
    }
    else
    {
        printf("He thong an toan: Tong dong dien khong vuot 30A.\n");
    }

    printf("\n===============================================\n");
    printf("              KET THUC GIAM SAT\n");
    printf("===============================================\n");

    return 0;
}

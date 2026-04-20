# VEHICLE-ACCIDENT-DETECTION-AND-ALERT-SYSTEM
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Simulated UART functions (replace with microcontroller UART drivers)
void UART_SendString(char *str) {
    printf("%s", str);
}

char UART_ReadChar() {
    return getchar(); // simulation
}

// Threshold for accident detection
#define THRESHOLD 50

// Function Prototypes
void detect_accident(int sensor_value);
void get_gps_location(char *lat, char *lon);
void send_sms(char *lat, char *lon);

// Global flag
int accident_flag = 0;

int main() {
    int sensor_value;

    char latitude[20];
    char longitude[20];

    printf("System Started...\n");

    while (1) {
        // Simulated sensor input
        printf("Enter sensor value: ");
        scanf("%d", &sensor_value);

        detect_accident(sensor_value);

        if (accident_flag) {
            printf("Accident Detected!\n");

            get_gps_location(latitude, longitude);
            send_sms(latitude, longitude);

            accident_flag = 0; // reset
        }
    }

    return 0;
}

// Accident Detection Logic
void detect_accident(int sensor_value) {
    if (sensor_value > THRESHOLD) {
        accident_flag = 1;
    }
}

// Simulated GPS Function
void get_gps_location(char *lat, char *lon) {
    // In real system, read from GPS via UART
    strcpy(lat, "17.3850");
    strcpy(lon, "78.4867");

    printf("GPS Location Acquired: %s, %s\n", lat, lon);
}

// GSM SMS Sending using AT Commands
void send_sms(char *lat, char *lon) {

    UART_SendString("AT\r\n");
    UART_SendString("AT+CMGF=1\r\n");  // Text mode
    UART_SendString("AT+CMGS=\"+91XXXXXXXXXX\"\r\n");

    UART_SendString("Accident Detected!\nLocation: ");
    UART_SendString("https://maps.google.com/?q=");

    UART_SendString(lat);
    UART_SendString(",");
    UART_SendString(lon);

    UART_SendString("\x1A"); // CTRL+Z to send SMS

    printf("\nSMS Sent Successfully!\n");
}

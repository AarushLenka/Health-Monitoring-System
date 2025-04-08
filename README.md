# Health Monitoring System

The Health Monitoring System is a compact and efficient project powered by ESP8266, designed to track key health parameters. Using the MAX30100 and AD8232 sensors, it measures heart rate, SpO2 levels, and ECG signals. The data is displayed on an OLED screen and sent to Blynk IoT for remote monitoring, while ECG signals can be viewed in real-time using the serial plotter.

## Features

- **Heart Rate and SpO2 Monitoring**:

  - **MAX30100 Sensor**: Measures heart rate and oxygen saturation (SpO2).
  - Data displayed on an OLED screen and sent to Blynk IoT.

- **ECG Monitoring**:

  - **AD8232 Sensor**: Captures ECG signals for cardiac activity.
  - Real-time ECG signal visualization in the Arduino IDE's serial plotter.

- **Remote Monitoring**:

  - Integration with Blynk IoT for remote access to heart rate and SpO2 data.

- **Powered by ESP8266**: Ensures seamless connectivity and efficient data handling.

## Hardware Requirements

- **ESP8266 Microcontroller**
- **MAX30100 Sensor** (for heart rate and SpO2 monitoring)
- **AD8232 Sensor** (for ECG signals)
- **OLED Display** (I2C compatible)
- Power Supply

## Software Requirements

- Arduino IDE
- ESP8266 Board Package (installable via Arduino IDE Board Manager)
- Required Libraries:
  - `ESP8266WiFi` (for ESP8266 connectivity)
  - `Blynk` (for IoT integration)
  - `Adafruit_GFX` and `OakOled` (for OLED display)
  - `MAX30100_PulseOximeter` (for MAX30100 sensor)

## Setup Instructions

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/AarushLenka/Health-Monitoring-System.git
   ```

2. **Install Libraries**:
   Open the Arduino IDE and install the required libraries using the Library Manager.

3. **Upload the Code**:

   - Connect the ESP8266 to your computer via USB.
   - Open the `.ino` file in the Arduino IDE.
   - Configure the WiFi credentials and Blynk Auth Token in the code.
   - Select the ESP8266 board and port.
   - Click the "Upload" button.

4. **Assemble the Hardware**:

   - Connect the MAX30100, AD8232, and OLED display to the ESP8266 as per the circuit diagram (to be included).

5. **Power On**:

   - Supply power to the system and observe the displayed data.

## Usage

- **Heart Rate and SpO2 Monitoring**:
  - View real-time data on the OLED screen and the Blynk app.
- **ECG Monitoring**:
  - Open the Arduino IDE's serial plotter to visualize ECG signals.

## Future Improvements

- Adding notifications or alerts via Blynk for abnormal health readings.
- Integration with cloud storage for data logging and analysis.
- Expanding to monitor additional health parameters.
- Creation of custom PCB to bring down the size of device and increase accuracy

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request for any new features or bug fixes.

## Contact

For any inquiries or suggestions, please contact [lenkaaarush\@gmail.com].



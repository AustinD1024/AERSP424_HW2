#include <iostream>
#include <string>
#include <vector>

// Abstract base class for sensors
class Sensor {
public:
    virtual ~Sensor() {}
    virtual void gatherData() const = 0;
    virtual void processData() const = 0;
};

// Derived class for temperature sensor
class TemperatureSensor : public Sensor {
public:
    void gatherData() const override {
        std::cout << "Gathering data from Temperature Sensor." << std::endl;
    }

    void processData() const override {
        std::cout << "Processing data from Temperature Sensor." << std::endl;
    }
};

// Derived class for pressure sensor
class PressureSensor : public Sensor {
public:
    void gatherData() const override {
        std::cout << "Gathering data from Pressure Sensor." << std::endl;
    }

    void processData() const override {
        std::cout << "Processing data from Pressure Sensor." << std::endl;
    }
};

// Derived class for altitude sensor
class AltitudeSensor : public Sensor {
public:
    void gatherData() const override {
        std::cout << "Gathering data from Altitude Sensor." << std::endl;
    }

    void processData() const override {
        std::cout << "Processing data from Altitude Sensor." << std::endl;
    }
};

// SensorFactory class
class SensorFactory {
public:
    static Sensor* createSensor(const std::string& sensorType) {
        if (sensorType == "Temperature") {
            return new TemperatureSensor();
        }
        else if (sensorType == "Pressure") {
            return new PressureSensor();
        }
        else if (sensorType == "Altitude") {
            return new AltitudeSensor();
        }
        else {
            std::cout << "Unknown sensor type: " << sensorType << std::endl;
            return nullptr;
        }
    }
};

// AerospaceControlSystem class
class AerospaceControlSystem {
public:
    void addSensor(Sensor* sensor) {
        sensors.push_back(sensor);
    }

    void monitorAndAdjust() const {
        for (const auto& sensor : sensors) {
            sensor->gatherData();
            sensor->processData();
        }
        std::cout << "Adjusting controls based on sensor data." << std::endl;
    }

private:
    std::vector<Sensor*> sensors;
};

int main() {
    AerospaceControlSystem ctrlSys;

    // Instantiate and add sensors
    Sensor* tempSensor = SensorFactory::createSensor("Temperature");
    Sensor* pressureSensor = SensorFactory::createSensor("Pressure");
    Sensor* altitudeSensor = SensorFactory::createSensor("Altitude");

    ctrlSys.addSensor(tempSensor);
    ctrlSys.addSensor(pressureSensor);
    ctrlSys.addSensor(altitudeSensor);

    // Monitor and adjust
    ctrlSys.monitorAndAdjust();

    // Cleanup
    delete tempSensor;
    delete pressureSensor;
    delete altitudeSensor;

    return 0;
}

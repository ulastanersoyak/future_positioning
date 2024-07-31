#ifndef DATA_PACKET_PARSER_HPP
#define DATA_PACKET_PARSER_HPP

#include <vector>
#include <cstdint>
#include <cmath>
#include <ctime>
#include "time_and_location/utc.hpp"


struct Xbus {
    float euler[3];
    bool eulerAvailable = false;

    float quat[4];
    bool quaternionAvailable = false;  

    float acc[3];
    bool accAvailable = false;  

    float rot[3];
    bool rotAvailable = false;

    double latlon[2]; //FP16.32
    bool latlonAvailable = false;

    double altitude{ 0.0 }; //FP16.32
    bool altitudeAvailable = false;

    double vel[3]; //FP16.32
    bool velocityAvailable = false;

    float mag[3];
    bool magAvailable = false;

    uint16_t packetCounter{ 0 };
    bool packetCounterAvailable = false;

    uint32_t sampleTimeFine{ 0 };
    bool sampleTimeFineAvailable = false;

    utc time {0, 0, 0};
    bool utcTimeAvailable = false;

    uint32_t statusWord{ 0 };
    bool statusWordAvailable = false;


    static constexpr double rad2deg = 57.295779513082320876798154814105;
    static constexpr double minusHalfPi = -1.5707963267948966192313216916397514420985846996875529104874;
    static constexpr double halfPi = 1.5707963267948966192313216916397514420985846996875529104874;

    static float asinClamped(float x) {
        if (x <= -1.0 ) return static_cast<float>(minusHalfPi);
        if (x >= 1.0) return  static_cast<float>(halfPi);
        return std::asin(x);
    }


    void convertQuatToEuler() {
        if (!quaternionAvailable) {
            // Handle error: Quaternion data not available.
            return;
        }
        
        float sqw = quat[0] * quat[0];
        float dphi = 2.0f * (sqw + quat[3] * quat[3]) - 1.0f;
        float dpsi = 2.0f * (sqw + quat[1] * quat[1]) - 1.0f;
    
        euler[0] = static_cast<float>(std::atan2(2.0f * (quat[2] * quat[3] + quat[0] * quat[1]), dphi) * rad2deg);
        euler[1] = static_cast<float>(-asinClamped(2.0f* (quat[1] * quat[3] - quat[0] * quat[2]))* rad2deg);
        euler[2] = static_cast<float>(std::atan2(2.0f * (quat[1] * quat[2] + quat[0] * quat[3]), dpsi)* rad2deg);

        eulerAvailable = true;
    }
};

class DataPacketParser {
public:
    static void parseDataPacket(const std::vector<uint8_t>& packet, Xbus& xbusData);

private:
    static void dataswapendian(uint8_t* data, int len);
    static void parseMTData2(Xbus* self, uint8_t* data, uint8_t datalength);
    static double parseFP1632(const uint8_t* data);
};

#endif // DATA_PACKET_PARSER_HPP

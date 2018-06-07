#ifndef RAW_SENSOR_DATA_H
#define RAW_SENSOR_DATA_H

struct RawSensorData
{
    size_t id;

    RawSensorData() = default;
    virtual ~RawSensorData() = default;
};

#endif // RAW_SENSOR_DATA_H

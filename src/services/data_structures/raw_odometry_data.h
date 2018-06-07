#ifndef RAW_ODOMETRY_DATA_H
#define RAW_ODOMETRY_DATA_H

struct RawOdometryData
{
    size_t id;
    
    RawOdometryData() = default;
    virtual ~RawOdometryData() = default;
};

#endif // RAW_ODOMETRY_DATA_H

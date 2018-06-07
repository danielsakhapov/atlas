#ifndef PROCESSED_ODOMETRY_DATA_H
#define PROCESSED_ODOMETRY_DATA_H

struct ProcessedOdometryData
{
    size_t id;

    ProcessedOdometryData() = default;
    virtual ~ProcessedOdometryData() = default;
};

#endif // PROCESSED_ODOMETRY_DATA_H

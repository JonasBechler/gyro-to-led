#pragma once

#include "Arduino.h"
#include <GY521.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

/**
 * @brief Data structure to hold various sensor readings from the GY521 sensor.
 */
struct Data_GY521
{
  float AccX;     /**< Acceleration along the X-axis. */
  float AccY;     /**< Acceleration along the Y-axis. */
  float AccZ;     /**< Acceleration along the Z-axis. */
  float AngX;     /**< Angular rotation around the X-axis. */
  float AngY;     /**< Angular rotation around the Y-axis. */
  float AngZ;     /**< Angular rotation around the Z-axis. */
  float GyroX;    /**< Gyroscope reading along the X-axis. */
  float GyroY;    /**< Gyroscope reading along the Y-axis. */
  float GyroZ;    /**< Gyroscope reading along the Z-axis. */
  float Roll;     /**< Roll angle. */
  float Pitch;    /**< Pitch angle. */
  float Yaw;      /**< Yaw angle. */
  float Temp;     /**< Temperature reading. */
  int start_time; /**< Start time for data collection. */
};

/**
 * @brief Initializes the GY521 sensor.
 * @param sensor Pointer to the GY521 sensor object.
 */
void init_GY521(GY521 *sensor);

/**
 * @brief Sets the data in the Data_GY521 structure using readings from the GY521 sensor.
 * @param sensor Pointer to the GY521 sensor object.
 * @param data Pointer to the Data_GY521 structure to store the sensor readings.
 */
void setData_GY521(GY521 *sensor, Data_GY521 *data);

/**
 * @brief Prepares the initial string format for data output.
 * @param buf Reference to the string buffer to store the formatted data.
 */
void getDataStringInit_GY521(String &buf);

/**
 * @brief Converts the data in the Data_GY521 structure to a formatted string.
 * @param data Pointer to the Data_GY521 structure containing sensor readings.
 * @param buf Reference to the string buffer to store the formatted data.
 */
void getDataString_GY521(Data_GY521 *data, String &buf);

/**
 * @brief Negates the values in a Data_GY521 structure.
 * @param dataA Pointer to the Data_GY521 structure whose values will be negated.
 */
void neg_Data_GY521(Data_GY521 *dataA);

/**
 * @brief Adds the values of two Data_GY521 structures element-wise.
 * @param dataA Pointer to the first Data_GY521 structure.
 * @param dataB Pointer to the second Data_GY521 structure.
 */
void add_Data_GY521(Data_GY521 *dataA, Data_GY521 *dataB);

/**
 * @brief Multiplies the values in a Data_GY521 structure by a given factor.
 * @param dataA Pointer to the Data_GY521 structure to be multiplied.
 * @param factor The factor by which to multiply the values.
 */
void mult_Data_GY521(Data_GY521 *dataA, float factor);

/**
 * @brief Checks for overflows and underflows between two Data_GY521 structures.
 * @param now Pointer to the current Data_GY521 structure.
 * @param old Pointer to the old Data_GY521 structure.
 */
void check_over_under_flow(Data_GY521 *now, Data_GY521 *old);

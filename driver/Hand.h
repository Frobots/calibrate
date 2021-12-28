#ifndef HAND_H__
#define HAND_H__

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus.h>

/**
  * @brief     this class represents for the machine hand
  * 
  */ 
class Hand {
 public:
  modbus_t* RtuConnect(modbus_t* ctx, const char *device, int baud, char parity, int data_bit, int stop_bit,int mode);
  int32_t Write(modbus_t* ctx, int address, float value);
  int32_t Initialization(modbus_t* ctx, int address);
  int32_t Close();
}; // Hand


#endif // CAMERA_H__


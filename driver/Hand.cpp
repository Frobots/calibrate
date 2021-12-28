/*************************************************************//**
 * @file        Hand.cpp
 * @brief       This file provides interface functions for the Hand
 * @author      Han Lei (hl_sues@163.com)
 * @date        11/02/2021 (M/D/Y)
 * @details     This file supplied 7 function
 *              1. connect the hand
 *              2. write value to register and make hand work
 *              3. loosen hand
 * 
 ***************************************************************/
 
#include "Hand.h"

uint16_t float_cov_uint16(float value);

/**
  * @brief      RTU connection
  * @param      ctx a printer of context of modbus
  * @param      device The device argument specifies the name of the serial port handled by the OS, eg. "/dev/ttyS0" or "/dev/ttyUSB0".
  * @param      baud The baud argument specifies the baud rate of the communication, eg. 9600, 19200, 57600, 115200, etc.
  * @param      parity The parity argument can have one of the following values,N for none;E for even;O for odd
  * @param      data_bit The data_bits argument specifies the number of bits of data, the allowed values are 5, 6, 7 and 8.
  * @param      stop_bit The stop_bits argument specifies the bits of stop, the allowed values are 1 and 2.
  * @param      mode serial mode:MODBUS_RTU_RS232;MODBUS_RTU_RS485
  * @return     connect success:modbus_t*,connect failed:nullptr;
  */ 
modbus_t* Hand::RtuConnect(modbus_t* ctx,const char *device, int baud, char parity, int data_bit, int stop_bit,int mode)
{
    ctx =  modbus_new_rtu (device,baud,parity,data_bit,stop_bit); 
    if  ( ctx == nullptr)  { 
        fprintf(stderr,"Unable to create the libmodbus context\n"); 
        return nullptr; 
    }

    modbus_set_slave ( ctx , 1);
    modbus_rtu_set_serial_mode(ctx,mode);
    modbus_rtu_set_rts(ctx, MODBUS_RTU_RTS_UP);

    if( modbus_connect(ctx)  ==  - 1 ){ 
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno)); 
        modbus_free (ctx); 
        return nullptr; 
    }
    return ctx;
}

/**
 * @brief modbus_write_register
 * @param ctx a printer of context of modbus
 * @param address register address
 * @param value float value written to register
 * @return success:0 failed:-1
 */
int32_t Hand::Write(modbus_t* ctx, int address, float value){

    uint16_t dest[2];
    modbus_set_float_cdab(value,dest);
    
    
    int rc =  modbus_write_registers( ctx ,address, 2, dest); 
    //对应modbus功能0x10;
    if( rc ==  - 1 ){ 
        fprintf(stderr, "%s\n ", modbus_strerror (errno)); 
        return -1 ; 
    }
    return 0;
}

/**
 * @brief loosen hand
 * @param ctx a printer of context of modbus
 * @param address register address
 * @return success:0 failed:-1
 */
int32_t Hand::Initialization(modbus_t* ctx, int address){
    int rc =  modbus_write_register( ctx ,address,1); 
    //对应modbus功能0x06;
    if( rc ==  - 1 ){ 
        fprintf(stderr, "%s\n ", modbus_strerror (errno)); 
        return -1 ; 
    }
    return 0;
}

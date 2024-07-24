/********************************************************************************
 *
 *  HidDfu.h
 *
 *  Copyright (C) Cambridge Silicon Radio Ltd 
 *
 *  Defines the HidDfu API functions used to perform a Device Firmware Update on 
 *  a CSR BlueCore device using the USB HID interface.
 *
 *******************************************************************************/

#ifndef HID_DFU_H
#define HID_DFU_H

/* This file used in conjunction with a def file gives us undecorated stdcall C exports from the DLL */
#define HIDDFU_API(T) T _stdcall

#include "common/types.h"

/* Error codes - for description use hidDfuGetLastError() */
#define HIDDFU_ERROR_NONE                                   0
#define HIDDFU_ERROR_SEQUENCE                              -1
#define HIDDFU_ERROR_CONNECTION                            -2
#define HIDDFU_ERROR_FILE_OPEN_FAILED                      -3
#define HIDDFU_ERROR_FILE_WRITE_FAILED                     -4
#define HIDDFU_ERROR_FILE_INVALID_FORMAT                   -5
#define HIDDFU_ERROR_FILE_CRC_INCORRECT                    -6
#define HIDDFU_ERROR_FILE_READ_FAILED                      -7
#define HIDDFU_ERROR_UPGRADE_FAILED                        -8
#define HIDDFU_ERROR_RESET_FAILED                          -9
#define HIDDFU_ERROR_OUT_OF_MEM                            -10
#define HIDDFU_ERROR_INVALID_PARAMETER                     -11
#define HIDDFU_ERROR_DRIVER_INTERFACE_FAILURE              -12
#define HIDDFU_ERROR_OPERATION_FAILED_TO_START             -13
#define HIDDFU_ERROR_BUSY                                  -14
#define HIDDFU_ERROR_CLEAR_STATUS_FAILED                   -15
#define HIDDFU_ERROR_DEVICE_FIRMWARE                       -16
#define HIDDFU_ERROR_UNKNOWN                               -20


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************

    Function :      int32 hidDfuGetVersion(uint8* major, uint8* minor, 
                                           uint8* release, uint8* build)

    Parameters :    major - 
                        Location to store the major version number.

                    minor -
                        Location to store the minor version number.

                    release -
                        Location to store the release number.

                    build -
                        Location to store the build number.

    Returns :       An error code, either HIDDFU_ERROR_NONE if successful, or 
                    one of the other HIDDFU_ERROR_ codes defined in this file.

    Description :   This function gets the version information of the HidDfu 
                    DLL. A device connection is not required.

*******************************************************************************/
HIDDFU_API(int32) hidDfuGetVersion(uint8* major, uint8* minor, uint8* release, 
                                   uint8* build);

/*******************************************************************************
    
    Function :      int32 hidDfuConnect(uint16 vid, uint16 pid, uint16 usage, 
                                        uint16 usagePage);

    Parameters :    vid -
                        Target device USB Vendor ID.

                    pid -
                        Target device USB Product ID.

                    usage -
                        Target device USB usage value. Set this value to 0 to 
                        ignore the device usage value.

                    usagePage -
                        Target device USB usagePage value. Set this value to 
                        0 to ignore the device usagePage value.

    Returns :       An error code, either HIDDFU_ERROR_NONE if successful, or 
                    one of the other HIDDFU_ERROR_ codes defined in this file.

    Description :   Attempts to connect to the specified USB device. If
                    multiple matching devices are connected to the system, the 
                    connection attempt will be made with the first device found.
    
*******************************************************************************/
HIDDFU_API(int32) hidDfuConnect(uint16 vid, uint16 pid, uint16 usage, 
                                uint16 usagePage);

/*******************************************************************************
    
    Function :      int32 hidDfuDisconnect(void);

    Parameters :    None

    Returns :       An error code, either HIDDFU_ERROR_NONE if successful, or 
                    one of the other HIDDFU_ERROR_ codes defined in this file.

    Description :   Disconnects from currently connected device. If a device is 
                    not connected, does nothing and returns HIDDFU_ERROR_NONE.

*******************************************************************************/
HIDDFU_API(int32) hidDfuDisconnect(void);

/*******************************************************************************
   
    Function :      int32 hidDfuBackup(const char* fileName);

    Parameters :    fileName -
                        Name of backup image file to write

    Returns :       An error code, either HIDDFU_ERROR_NONE if successful, or 
                    one of the other HIDDFU_ERROR_ codes defined in this file.

    Description :   Reads the image from the connected BlueCore chip and saves 
                    to the specified file. This function starts the operation. 
                    Use hidDfuGetProgress to check for completion and 
                    hidDfuGetResult to get the final status.

*******************************************************************************/
HIDDFU_API(int32) hidDfuBackup(const char* fileName);

/*******************************************************************************
    
    Function :      int32 hidDfuUpgrade(const char* fileName);

    Parameters :    fileName -
                        Name of upgrade image file

    Returns :       An error code, either HIDDFU_ERROR_NONE if successful, or 
                    one of the other HIDDFU_ERROR_ codes defined in this file.

    Description :   Reads an image from the specified file and upgrades the 
                    connected BlueCore device. This function starts the 
                    operation. Use hidDfuGetProgress to check for completion 
                    and hidDfuGetResult to get the final status.

*******************************************************************************/
HIDDFU_API(int32) hidDfuUpgrade(const char* fileName);

/*******************************************************************************
    
    Function :      int32 hidDfuResetDevice(void);

    Parameters :    None

    Returns :       An error code, either HIDDFU_ERROR_NONE if successful, or 
                    one of the other HIDDFU_ERROR_ codes defined in this file.

    Description :   This function resets a connected device, causing the device
                    to exit DFU mode. If the reset is successful, the device 
                    connection is also closed.

*******************************************************************************/
HIDDFU_API(int32) hidDfuResetDevice(void);

/*******************************************************************************
    
    Function :      uint8 hidDfuGetProgress(void);

    Parameters :    None

    Returns :       The progress of an operation (percentage).

    Description :   This function gets the progress of an ongoing operation. If 
                    an operation has finished, 100 is returned.

*******************************************************************************/
HIDDFU_API(uint8) hidDfuGetProgress(void);

/*******************************************************************************
    
    Function :      int32 hidDfuGetResult(void);

    Parameters :    None

    Returns :       The result for the last completed operation, either 
                    HIDDFU_ERROR_NONE if successful, or one of the other 
                    HIDDFU_ERROR_ codes defined in this file.

    Description :   This function gets the result of the last completed 
                    operation. Returns an error if an operation has not been 
                    run, if an operation is ongoing, or if the last operation 
                    failed.
                    <p>Use hidDfuGetLastError to get the description in the 
                    case of an error.

*******************************************************************************/
HIDDFU_API(int32) hidDfuGetResult(void);

/*******************************************************************************
    
    Function :      const char* hidDfuGetLastError(void);

    Parameters :    None

    Returns :       The details of the last error.

    Description :   This function gets a description of the last error.

*******************************************************************************/
HIDDFU_API(const char*) hidDfuGetLastError(void);

/*******************************************************************************

    Function :      int32 hidDfuSendCommand(const uint8* data, uint32 length);

    Parameters :    data -
                        The command data to send.

                    length -
                        Length of the data (in bytes).

    Returns :       An error code, either HIDDFU_ERROR_NONE if successful, or 
                    one of the other HIDDFU_ERROR_ codes defined in this file.

    Description :   Sends a custom command to a connected device. This function 
                    can be used to cause the connected device to switch from 
                    normal mode to DFU mode (after which hidDfuDisconnect and 
                    hidDfuConnect can be called to reconnect using the DFU mode 
                    connection parameters).

*******************************************************************************/
HIDDFU_API(int32) hidDfuSendCommand(const uint8* data, uint32 length);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* HID_DFU_H */

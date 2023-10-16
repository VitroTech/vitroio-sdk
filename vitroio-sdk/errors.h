#ifndef VITROIO_SDK_ERRORS_H
#define VITROIO_SDK_ERRORS_H

/**
 * @file vitroio-sdk/errors.h
 * 
 * @brief The file defines error codes.
 */

#define VITROIO_ERR_SUCCESS 0

// General errors
#define VITROIO_ERR_SET_CALLBACK    -1
#define VITROIO_ERR_MEMORY_ALLOC    -2
#define VITROIO_ERR_INVALID_PARAMS  -3

// Bus errors
#define VITROIO_ERR_BUS_WRITE            -101
#define VITROIO_ERR_BUS_READ             -102
#define VITROIO_ERR_BUS_SET_FRAME_LENGTH -103 

// Flash errors
#define VITROIO_ERR_FLASH_INIT  -201
#define VITROIO_ERR_FLASH_WRITE -202
#define VITROIO_ERR_FLASH_READ  -203
#define VITROIO_ERR_FLASH_ERASE -204

#define VITROIO_ERR_ENCRYPTION_IOT_BLOCK -302
#define VITROIO_ERR_PARAMID_IOT_BLOCK    -303
#define VITROIO_ERR_SIZE_IOT_BLOCK       -304


#endif // VITROIO_SDK_ERRORS_H
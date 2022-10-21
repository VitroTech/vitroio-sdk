#ifndef VITROIO_SDK_DEBUG_H
#define VITROIO_SDK_DEBUG_H

/**
 * @file vitroio-sdk/debug.h
 * 
 * @brief The file defines debug macros.
 * 
 * @details There are 4 debug levels (from highest to lowest):
 * - HINFO
 * - INFO
 * - WARNING
 * - ERROR
 * When some level is defined, the defined one and all of lower levels are
 * enabled. 
 * 
 * @attention Definition of debug level have to define the name of mbed serial
 * port global variable. For instance, when the WARNING level is to be enabled,
 * the user should define:
 * VITROIO_DEBUG_WARNING_LEVEL=pc
 * where pc is a variable name of mbed serial port declared in another file.
 */

#include <mbed.h>

#if defined(VITROIO_DEBUG_HINFO_LEVEL) || \
    defined(VITROIO_DEBUG_INFO_LEVEL) || \
    defined(VITROIO_DEBUG_WARNING_LEVEL) || \
    defined(VITROIO_DEBUG_ERROR_LEVEL)

    #define _VITROIO_DEBUG_PRINTF_(serial, level, module, format, ...) printf("[%s][%s]: " format "\n\r", level, module, ##__VA_ARGS__);

#endif

#if defined(VITROIO_DEBUG_HINFO_LEVEL)

    extern BufferedSerial VITROIO_DEBUG_HINFO_LEVEL;

    #define VITROIO_DEBUG_HINFO(module, format, ...) _VITROIO_DEBUG_PRINTF_(VITROIO_DEBUG_HINFO_LEVEL, "INFO", module, format, ##__VA_ARGS__)

    #define VITROIO_DEBUG_INFO_LEVEL    VITROIO_DEBUG_HINFO_LEVEL

#else

    #define VITROIO_DEBUG_HINFO(module, format, ...)

#endif // VITROIO_DEBUG_HINFO_LEVEL

#if defined(VITROIO_DEBUG_INFO_LEVEL)

    #ifndef VITROIO_DEBUG_HINFO_LEVEL
        extern BufferedSerial VITROIO_DEBUG_INFO_LEVEL;
    #endif

    #define VITROIO_DEBUG_INFO(module, format, ...) _VITROIO_DEBUG_PRINTF_(VITROIO_DEBUG_INFO_LEVEL, "INFO", module, format, ##__VA_ARGS__)

    #define VITROIO_DEBUG_WARNING_LEVEL VITROIO_DEBUG_INFO_LEVEL

#else

    #define VITROIO_DEBUG_INFO(module, format, ...)

#endif // VITROIO_DEBUG_INFO_LEVEL

#if defined(VITROIO_DEBUG_WARNING_LEVEL)

    #ifndef VITROIO_DEBUG_INFO_LEVEL
        extern BufferedSerial VITROIO_DEBUG_WARNING_LEVEL;
    #endif

    #define VITROIO_DEBUG_WARNING(module, format, ...) _VITROIO_DEBUG_PRINTF_(VITROIO_DEBUG_WARNING_LEVEL, "WARNING", module, format, ##__VA_ARGS__)

    #define VITROIO_DEBUG_ERROR_LEVEL   VITROIO_DEBUG_WARNING_LEVEL

#else

    #define VITROIO_DEBUG_WARNING(module, format, ...)

#endif // VITROIO_DEBUG_WARNING_LEVEL

#if defined(VITROIO_DEBUG_ERROR_LEVEL)

    #ifndef VITROIO_DEBUG_WARNING_LEVEL
        extern BufferedSerial VITROIO_DEBUG_ERROR_LEVEL;
    #endif

    #define VITROIO_DEBUG_ERROR(module, format, ...) _VITROIO_DEBUG_PRINTF_(VITROIO_DEBUG_ERROR_LEVEL, "ERROR", module, format, ##__VA_ARGS__)

#else

    #define VITROIO_DEBUG_ERROR(module, format, ...)

#endif // VITROIO_DEBUG_ERROR_LEVEL

#endif // VITROIO_SDK_DEBUG_H

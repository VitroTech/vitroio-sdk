#error The file is modules documentation only.

/**
 * @defgroup bootloader
 * 
 * @brief Contains API for booting target application.
 * 
 * @details  
 * Required modules:
 * - @ref interfaces
 */

/**
 * @defgroup communication
 * 
 * @brief Provides classes for communication with gateway.
 * 
 * @details
 * Required modules:
 * - @ref utils
 */

/**
 * @defgroup control
 * 
 * @brief Provides general control of particular node.
 * 
 * @details
 * Required modules:
 * - @ref utils
 * - @ref interfaces
 * - @ref communication
 */

/**
 * @defgroup measurement-api
 * 
 * @brief Provides functionality of measurement system.
 * 
 * @details 
 * Required modules:
 * - @ref utils
 */

/**
 * @defgroup interfaces
 * 
 * @brief Provides abstraction layer for specific usage of resources.
 * 
 * @details The module is only for internal usage by vitro-shard-sdk.
 */

/**
 * @defgroup utils
 * 
 * @brief Provides auxiliary classes simplifying code development.
 * 
 * @details The module is only for internal usage by vitro-shard-sdk.
 */

/**
 * @defgroup iot-block-api
 * 
 * @brief Provides methods for creation and sending IoT blocks
 * 
 * @details It uses mbed-tls library, and ECC module for encryption.
 */

/**
 * @defgroup shard-edge-lib
 * 
 * @brief Provides classes for communication with shard-edge.
 * 
 * @details The module is only for internal usage by vitro-shard-sdk.
 */
 
 /**
 * @defgroup watchdog
 * 
 * @brief Provides watchdog class.
 * 
 */

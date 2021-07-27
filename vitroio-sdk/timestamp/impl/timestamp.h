#ifndef VITROIO_SDK_TIMESTAMP
#define VITROIO_SDK_TIMESTAMP

#include <mbed.h>
#include <vitroio-sdk/communication/transport_layer.h>
#include <vitroio-sdk/interfaces/impl/environment_interface.h>

namespace vitroio {
namespace sdk {
namespace impl{
/**
 * @addtogroup control
 * @{
 */

/**
 * @brief Class for maintaining timestamp tracking
 *
 * @details This class usese Timer for counting and calculation of timestamps.
 * @note If the timestamp is not set, either by passing its value in constructor
 * or by @ref Timestamp::set_timestamp , the value returned by
 * @ref Timestamp::get_timestamp will be time, given in ms, from boot to now.
 *
 */
class Timestamp{
    public:
        /**
         * @brief Initializes timestamp counting
         *
         * @param comm Communication layer to get timestamp from.
         * @param env_if Environemt interface for timestamp saving
         */
        static void start(Transport_layer* comm, EnvironmentInterface* env_if);

        /**
         * @brief Initializes timestamp counting
         *
         * @param sync_time Time between timestamp synchronization, given in hours
         * @param comm Communication layer to get timestamp from.
         * @param env_if Environemt interface for timestamp saving
         */
        static void start(uint32_t sync_time, Transport_layer* comm, EnvironmentInterface *env_if);

        /**
         * @brief Get the timestamp object
         *
         * @return uint32_t Current timestamp
         */
        static uint32_t get_timestamp();

        static void updater_runner();
        typedef struct {
            uint32_t sync_interval;
            uint32_t last_timestamp;
            Timer ticker;
        } CurrentTime_t;
        static CurrentTime_t current_time;
        static Thread updater;
        static Transport_layer* comm_port;
        static EnvironmentInterface* env;
    private:
        static void set_timestamp(uint32_t timestamp);
};
/**
 * @}
 */
}
}
}

#endif
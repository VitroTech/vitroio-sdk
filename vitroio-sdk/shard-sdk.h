#ifndef SHARD_SDK_H
#define SHARD_SDK_H

//common
#include <vitroio-sdk/consts.h>
#include <vitroio-sdk/debug.h>
#include <vitroio-sdk/errors.h>
#include <vitroio-sdk/types.h>
#include <vitroio-sdk/version.h>
//shard-edge-lib
#include <vitroio-sdk/shard-edge-lib/shard_edge.h>
//measurement-api
#include <vitroio-sdk/measurement-api/abstract_sensor_driver.h>
#include <vitroio-sdk/measurement-api/abstract_sensor_interface.h>
#include <vitroio-sdk/measurement-api/measurement_api.h>
//iot-block
#include <vitroio-sdk/iot-block-api/iot-block.h>
//control
#include <vitroio-sdk/control/node_controller.h>
//communication
#include <vitroio-sdk/communication/canbus_frame.h>
#include <vitroio-sdk/communication/canbus.h>
#include <vitroio-sdk/communication/transport_layer.h>
#include <vitroio-sdk/communication/can_layer.h>

#endif // SHARD_SDK_H

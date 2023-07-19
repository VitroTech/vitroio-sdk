# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/) and this
project adheres to [Semantic Versioning](https://semver.org/).

<!--

TEMPLATE

## [x.y.z] YYYY-MM-DD

### Added

- New features/things that were not available
- ABC

### Changed

- Old features/things that now look/work in different way

### Fixed

- Old features/things that now work as they should

### Removed

- Removed features/things

-->

## [2.0.5] 2023-07-19

### Added

- Added third EXPECTED_CARRIER_BOARD_REV for Shard initialization

### Changed

- CAN bus bitrate set to 500KHz from 125KHz
- Frame with localID request no longer has 0x0 as localID in header; now it is
  based on Shard hardwareID, mentioned in
  [documentation](./FIRMWARE_DEVELOPERS_GUIDE.md#implementing-target-application)
- Shard stays in localID request loop until localID from Crystal is assigned

### Fixed

- Resolved problem with MbedOS HardFault from provisioning
  process

## [2.0.4] 2023-06-14

### Added

- Added placeholder for external frame handler with ID 0x60, can be used within
  user application.

## [2.0.3] 2023-06-14

### Fixed

- Add a NULL pointer check that caused a system fault.
- Provide second Edge board revision, used before making configuration of the
  device.

## [2.0.2] 2023-05-19

### Fixed

- CAN Bus can recover by restarting itself after shutting down permanently due
  to errors.
- CAN Bus initialization now exits properly after encountering errors.


## [2.0.1]

### Fixed

- Fix receiving and requesting timestamps from Crystal

## [2.0.0]

### Changed

- SDK updated to work with mbedOS release 6.16.0

## [1.8.3]

### Fixed

- Fix formatting for ECC ID printing

## [1.8.2]

### Added

- Serial number print in ECC608 constructor. Number is printed on shard start.
- Added debug prints in `node_controller.cpp` informing about OTA status and
  upgraded partition

## [1.8.1]

### Added

- New funtion for [`TransportLayer`](vitroio-sdk/communication/transport_layer.h#68)
  which update `nodeID_` used by `Can_layer` to set `NodeID` for each send frame.

## [1.8.0]

### Added

- Added IO protection keys to increase security which is described
  [here](https://github.com/VitroTech/shared-docs/blob/main/shard-v2-provisioning-v2.md#benefits-of-the-new-provisioning-process),
  more info [here](https://cloud.3mdeb.com/index.php/s/pGxZ5rdXStobSWx) in
  paragraph 2.2.10

## [1.7.2]

### Added

- Added ID/number to CRC frame (provisioning response)

## [1.7.1]

### Added

- Counting and sending checksum for provisioning response data

## [1.7.0]

### Added

- 24V output management

## [1.6.0]

### Added

- Shard SDK is used now for communication with ECC during provisioning

## [1.5.4]

### Added

- Now OTA update do not override firmware on Shard with different fwID

## [1.5.3]

### Fixed

- Fixed false-positive detection of errors while OTA
- Fixed printing fw version and ID

## [1.5.2]

### Added

- Timestamp for internal usage in SDK
- Setting of timestamp synchronization interval in node controlller methods
- Node controller initializes timestamp along with communication

## [1.5.1]

### Added

- IoTBlock blob size getter

### Changed

- Improved documentation

## [1.5.0]

### Added

- Communication abstraction layer for IoT Blocks

### Changed

- IO expander port used for board revision check
- Attenuation values for ADC count to voltage conversion
- IoT Blocks are now send using provided communication layer

## [1.4.0]

### Added

- Predefined sizes of IoTBlock.

### Changed

- IoT Block layout
- ECC object as singletone
- Pins of expander used for board revison check

## [1.3.0]

### Added

- Support for variable size IoT Block creating and sending.

### Changed

- IoT block data fields order.
- ECC508.countSHA256 method, to count SHA of more than 64 bytes of data.
- cryptoauthlib ECC init function is now called only once.
- ECC object in IoTBlock source file changed to static.

## [1.2.2]

### Added

- mbed-cryptoauthlib as submodule
- Patches for mbed-cryptoauthlib
- IoTBlock api
- ECC error handling
- Watchdog class which provides the interface to the Watchdog feature

### Changed

- Memory regions are now defined in SDK,no need to define them in application
  files.
- Node controller doen't need memory regions in constructor.
- Extracted bootloader from vitroio-sdk.
- Extracted ecc508-api from vitroio-sdk.
- Extracted tls_crypto-api from vitroio-sdk.
- Extracted shard-edge-lib from vitroio-sdk

## [1.2.1] - 2020-05-25

### Added

- Support for closed source static version of Vitro Shard SDK.

## [1.2.0] - 2019-02-10

### Added

- Support for new protocol communication protocol - firmware ID handling.

## Changed

- Support for new protocol communication protocol - firmware version handling.

## [1.1.0] - 2018-11-26

### Changed

- Change name from `vitroio-embedded-sdk` to `vitro-shard-sdk`

## [1.0.0] - 2018-10-26

### Added

- Firmware developers guide document.
- Features list was added to `README`.

### Changed

- Removed abstraction layer for communication buses - only CAN Bus is supported
  for now.
- Parameter ID for frame with firmware version changed to `0x30`.

### Fixed

- Doxygen documentation was completed, cleanup and unified.

## [0.1.1] - 2018-09-07

### Fixed

- Handling upgrade process after error occurrence

## [0.1.0] - 2018-09-04

### Added

- Initial implementation of debug macros
- Initial implementation of measurement API:
    - abstract classes for drivers and sensors
    - support for registration of sensors
    - support for setting polling time of measurement parameters
- Initial implementation of CAN bus
- Initial implementation of node controller:
    - support for initialization of environment
    - support for initialization of communication with gateway
    - support for firmware upgrade
- Initial implementation of bootloader

[Unreleased]: https://github.com/VitroTech/vitro-shard-sdk/compare/v2.0.5...HEAD
[2.0.5]: https://github.com/VitroTech/vitro-shard-sdk/compare/v2.0.4...v2.0.5
[2.0.4]: https://github.com/VitroTech/vitro-shard-sdk/compare/v2.0.3...v2.0.4
[2.0.3]: https://github.com/VitroTech/vitro-shard-sdk/compare/v2.0.2...v2.0.3
[2.0.2]: https://github.com/VitroTech/vitro-shard-sdk/compare/v2.0.1...v2.0.2
[2.0.1]: https://github.com/VitroTech/vitro-shard-sdk/compare/v2.0.0...v2.0.1
[2.0.0]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.8.3...v2.0.0
[1.8.3]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.8.2...v1.8.3
[1.8.2]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.8.1...v1.8.2
[1.8.1]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.8.0...v1.8.1
[1.8.0]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.7.2...v1.8.0
[1.7.2]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.7.1...v1.7.2
[1.7.1]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.7.0...v1.7.1
[1.7.0]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.6.0...v1.7.0
[1.6.0]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.5.4...v1.6.0
[1.5.4]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.5.3...v1.5.4
[1.5.3]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.5.2...v1.5.3
[1.5.2]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.5.1...v1.5.2
[1.5.1]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.5.0...v1.5.1
[1.5.0]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.4.0...v1.5.0
[1.4.0]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.3.0...v1.4.0
[1.3.0]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.2.2...v1.3.0
[1.2.2]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.1.0...v1.2.2
[1.2.1]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.2.0...v1.2.1
[1.2.0]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.1.0...v1.2.0
[1.1.0]: https://github.com/VitroTech/vitro-shard-sdk/compare/v1.0.0...v1.1.0
[1.0.0]: https://github.com/VitroTech/vitro-shard-sdk/compare/v0.1.1...v1.0.0
[0.1.1]: https://github.com/VitroTech/vitro-shard-sdk/compare/v0.1.0...v0.1.1
[0.1.0]: https://github.com/VitroTech/vitro-shard-sdk/compare/2878a10257f0f173faee504bc5243e140d36b477...v0.1.0

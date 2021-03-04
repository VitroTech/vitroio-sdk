# vitroio-sdk

This repository contains ready-to-use `vitro-shard-sdk` library which can be
simply added to your project. Specifically, there is compiled static library
with `.a` extension and all necessary header files in `vitroio-sdk` folder.

## Tracking information

Each supported target has its own branch, e.g. `NUCLEO_L486RG` is on branch
`target_nucleo_stm32l486rg`. Each commit on given target should bump to another
Mbed OS revision and its specific commit. This way you can freely chose which
version of `vitroio-sdk` to use to fit your application and version of Mbed OS.  

Every new commit on specific branch should be indicated and described in
CHANGELOG.md document.

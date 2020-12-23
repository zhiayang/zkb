## zkb

WIP. keyboard firmware for Nordic Semiconductor nRF52840 MCU, specifically the [nice!nano](https://docs.nicekeyboards.com/#/nice!nano/) board.

### setup

1. Download the Nordic SDK from [here](https://www.nordicsemi.com/Software-and-tools/Software/nRF5-SDK/Download). Version requirements are currently unknown, but 17.0.2 is known to work
2. Extract the downloaded SDK to `sdk/`, and modify `SDK_PATH` in the `Makefile` accordingly
3. Install the `arm-none-eabi` toolchain (including **binutils** and **gcc**), from [here](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
4. Ensure that the downloaded toolchain is either (a) in your `$PATH` (eg. as `arm-none-eabi-gcc`), or modify the variables in the `Makefile` accordingly
5. Download `adafruit-nrfutil` from [here](https://github.com/adafruit/Adafruit_nRF52_nrfutil) (or install via `pip`)

The final folder structure should look something like this:
```
zkb/
  |- kernel/
  |- sdk/
     |- nrf-sdk-17.0.2/
        |- components
        |- config
        |- ...
```

### building

1. Determine the keyboard you are building for; it should be a folder under `keyboards/`
2. Run `make keyboard=<keyboard_name>`, eg `make keyboard=lily58`

This will compile the firmware into a hex file, as well as generate a `.zip` package for flashing with `adafruit-nrfutil`.

When switching keyboards (ie. building the firmware for another keyboard), you must run `make clean` first.

### flashing

1. Place the board into DFU mode (double-tap reset)
2. Figure out the path to the device (should be somewhere under `/dev/`)
3. Run `make flash DEVICE_PATH=/dev/path-to-device`

Alternatively, to build and flash simultaneously, you need to explicitly set the name of the keyboard, for example:

```shell
$ make flash keyboard=lily58 DEVICE_PATH=/dev/cu.usbmodem14201
```


### license

This project is licensed under the Apache License, version 2.0. The Nordic SDK is licensed under the Nordic 5-Clause
license, but it is not distributed; you must agree to their licensing terms to download the SDK.

No nRF SDK files are distributed with this project.

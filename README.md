# INA226_asukiaaa

A library to communicate with INA226 voltage and current meter.

# Installation

## Arduino IDE

You can install to Arduino IDE with using library manager.

1. Select [Sketch -> Include Library -> Manage Libraries] to open library manager.
2. Search INA226 in library manager.
3. Select `INA226_asukiaaa` and install.

## PlatformIO

Add this library (`INA226_asukiaaa`) to `lib_deps` on platformio.ini.

# Usage
See [example](./examples/printVoltageAndCurrent/printVoltageAndCurrent.ino) or [header file](./src/INA226_asukiaaa.h).

# License

MIT

# References

- [INA226 datasheet (PDF)](http://www.ti.com/lit/ds/symlink/ina226.pdf)
- [電圧/電流計測　INA226をCCS Cで使う](http://denshi-kousaku.fan.coocan.jp/report030.html)
- [INA226 I2Cディジタル電流・電圧・電力計モジュール](https://strawberry-linux.com/catalog/items?code=12031)

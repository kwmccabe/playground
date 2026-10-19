# Circuit Playground BLE + Gizmo TFT

## Module base class
* Defines interface for functions called by main
* module::moduleSetup(), module::moduleTeardown(), module::moduleReset()
* module::leftButton(), module::rightButton()
* module::loop() is called every subclass::getModuleDelay() milliseconds


## Components:
* Finder      - required first module
* About       - reference module
* Blink       - reference module
* Dice        - D2, D3, D4, D6, D8, D10, D12, D20, D100
* Life        - Conway's Game of Life
* MusicBox    - pure-tone tunes
* ColorSensor - display reflected RGB color levels
* LightSensor - display overall light level
* SoundSensor - display sound levels
* TempSensor  - display temperature


| ![Circuit Playground Gizmo](/img/playground_front.jpeg) | ![Circuit Playground Bluefruit](/img/playground_back.jpeg) |
| --- | --- |
| front | back |

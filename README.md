# EEZ Studio example with Renesas EK-RA8D1 and LVGL

![EK-RA8D1 Kit Showing EEZ Studio Application](EK-RA8D1_CounterApp.jpg)

Integration steps:

- Open `counter.eez-project` in the [EEZ Studio](https://github.com/eez-open/studio/releases)

![EEZ Studio Project Editor](EEZ_Studio.png)

- Build the project source code files:

![alt text](EEZ_Studio_Build.png)

Source code files are generated inside `src/ui` folder.

- Add `ui_init()` and `ui_tick()` in `src/LVGL_thread_entry.c`

```
#include "ui/ui.h" // Add this!

// ...

void LVGL_thread_entry(void *pvParameters)
{
    lv_init();
    board_init();

    ui_init(); // Add this!

    // ...
    // Comment out LVGL demo
    // ...

    while (1)
    {
        lv_timer_handler();

        ui_tick(); // Add this!

        vTaskDelay (1);
    }
}
```

# LVGL ported to Renesas EK-RA8D1

## Overview

The EK-RA8D1 evaluation kit enables users to effortlessly evaluate the features of the RA8D1 MCU Group and develop embedded systems applications using Renesas’ Flexible Software Package (FSP) and e2 studio IDE. Utilize rich on-board features along with your choice of popular ecosystem add-ons to bring your big ideas to life.

The MCU has a Cortex-M85 core which utilizes the Helium (SIMD) instruction set of Arm. Besides that the chip is equipped with a GPU (called DAVE2D) to off load the MCU. 

## Buy

You can purchase the Renesas EK-RA8D1 board from many distributors. See the sources at https://renesas.com/ek-ra8d1

## Benchmark

During the benchmark 2 frame buffer were used in the external SRRAM. LVGL was configured to `LV_DISPLAY_RENDER_MODE_DIRECT` and the buffer were swapped on VSYNC to avoid tearing.

As observed in the video, the FPS only drops in highly complex scenarios, while CPU usage remains low. For instance, when multiple ARGB images were rotated, the FPS dropped to 12 and the rendering time increased to 66 ms, but the CPU usage stayed at 10%. Using software rendering only the FPS would be significantly lower, and the CPU usage would peak at 100%.

Check out EK-RA8D1 in action, running LVGL's benchmark demo:
[![image](https://github.com/lvgl/lv_port_renesas_ek-ra8d1/assets/7599318/7dab86d6-b092-495b-a989-2555118d7570)
](https://www.youtube.com/watch?v=WkJPB8wto_U)
## Specification

### CPU and Memory
- **MCU:** R7FA8D1BHECBD (Cortex-M85, 480MHz)
- **RAM:** 1MB internal, 64MB external SDRAM
- **Flash:** 2MB internal, 64MB External Octo-SPI Flash
- **GPU:** Dave2D

### Display and Touch
- **Resolution:** 480x854
- **Display Size:** 4.5”
- **Interface:** 2-lane MIPI
- **Color Depth:** 24-bit
- **Technology:** IPS
- **DPI:** 217 px/inch
- **Touch Pad:** Capacitive

### Connectivity
- Camera expansion board
- Micro USB device cable (type-A male to micro-B male)
- Micro USB host cable (type-A male to micro-B male)
- Ethernet patch cable

## Getting started

### Hardware setup
- Attach the MIPI LCD PCB to the main PCB
- On SW1 DIP switched (middle of the board) 7 should be ON, all others are OFF
- Connect the USB cable to the `Debug1` (J10) connector

### Software setup
- You can clone the repository with the following command:
    ```
    git clone https://github.com/lvgl/lv_port_renesas_ek-ra8d1.git --recurse-submodules
    ```
    Downloading the `.zip` from GitHub doesn't work as it doesn't download the submodules.

- Follow the *RA family* section of the [*documentation*](https://docs.lvgl.io/master/integration/chip/renesas.html#get-started-with-the-renesas-ecosystem) to prepare your environment and import the project

>**Note:** Debug  `printf` output is via the Jlink VCOM port, 921600 8,n,1

## Contribution and Support

If you find any issues with the development board feel free to open an Issue in this repository. For LVGL related issues (features, bugs, etc) please use the main [lvgl repository](https://github.com/lvgl/lvgl). 

If you found a bug and found a solution too please send a Pull request. If you are new to Pull requests refer to [Our Guide](https://docs.lvgl.io/master/CONTRIBUTING.html#pull-request) to learn the basics.


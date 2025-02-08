<h1 align = center >😀Factory Example Instructions🎁</h1>

1. Why is the startup time not displayed?
    To get the time, you need to automatically get the local time after connecting to wifi, but first set up your local time zone and SNTP server.

2. How do I change the local clock?
    find the `./src/Factory/Factory.cpp` file and change the `server1`and`server2` variable to the desired value.
    ```c
    //Example
    //china (UTC+08:00)
    const int time_zone = 8;
    const char* server1 = "ntp.sjtu.edu.cn";
    const char* server2 = "cn.ntp.org.cn";
    //US (UTC−05:00)
    const int time_zone = -5;
    const char* server1 = "pool.ntp.org";
    const char* server2 = "time.google.com";  
    ```
3. How to burn firmware?
    After the device is connected to a PC, hold down the RP2350 `BOOT button` and press the `RUN button` to enter the bootloader mode, the RP2350 drive letter will be displayed on the PC. Then find the firmware folder and drag the UF2 suffix file into the RP2350 drive letter. The drive letter will be automatically identified and burned.


### V1.1
#### 1. Software modification:
1. Fix WIFI connection failure
2. Change ESP32 AT firmware
3. Add the default LVGL time display
4. remove LVGL charging ⚡ icon display

#### 2. Hardware Modification:
1. Increase or decrease the capacitance of esp32c3 peripheral part

### V1.2
#### 1. Software modification:
1. Fix the situation that the esp32-c6 module cannot be found after restarting
2. Add the code safety judgment of esp32 module
3. modify the UI interface text esp32c3->esp32c6
4. Optimize startup time
5. Connect to wifi(xinyuandianzi) by default when powered on and update the current time


### V1.1
#### 1. 软件修改：
    1、修复WIFI连接失败情况
    2、更改ESP32 AT固件
    3、增加默认LVGL时间显示 
    4、删除LVGL充电⚡图标显示

#### 2.硬件修改：
    1、增减esp32c3外围部分电容

### V1.2
#### 1. 软件修改：
    1、修复重启后找不到esp32-c6模块情况
    2、增加esp32模块的代码安全判定
    3、修改UI界面文字esp32c3->esp32c6
    4、优化启动时间
    5、上电默认连接wifi(xinyuandianzi)、更新当前时间
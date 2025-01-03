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

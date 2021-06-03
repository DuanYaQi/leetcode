# Apex

## kdmapper

[KDMapper ](https://github.com/z175/kdmapper)is a [kernel](https://guidedhacking.com/threads/kernel-mode-drivers-info-for-anticheat-bypass.11325/) driver manual mapper using a vulnerable Intel Driver

- Utilizes an embedded vulnerable Intel driver
- Manually Maps your driver
- Provides a simple command line interface
- You just pass it 1 argument and you're driver is loaded



If you use KDMapper you must **bypass these kernel detections**

- PiDDBCacheTable
- MmUnloadedDrivers
- System thread detection
- System pool detection



This driver (iqvw64e.sys) comes as part of **Intel LAN drivers** and it allows to copy, read and write user/kernel memory, map physical memory and perform virtual to physical address translation.

Your driver must be compiled with /GS- option, and have custom **driver entry point defined**. (Basically the same kind of driver that you would use with drvmap or any other driver manual mapper)

https://github.com/TheCruZ/kdmapper

https://github.com/z175/kdmapper



### 编译

```c++
open .sln
release x64
build solution
you will get the kdmapper.exe in floder x64/Release
```



### 加载

每次重启电脑使用都需要加载  `driver.sys`

```shell
@echo off
cd %~dp0
echo [+] Checking current directory
echo [#] Executing
kdmapper.exe driver.sys
pause
```

加载时确定 origin 和 apex 是关闭的，使用管理员运行。

![1620363663075](assets/1620363663075.png)



![1620363610967](assets/1620363610967.png)





# Apex

```powershell
D:\workspace\Reverse\apex\Project-Branthium-main\Project-Branthium-main\build>kdmapper.exe driver.sys                   [<] Loading vulnerable driver                                                                                           [+] NtLoadDriver Status 0x0                                                                                             [+] PiDDBLock Ptr fffff8010e30a591                                                                                      [+] PiDDBCacheTable Ptr fffff8010e30dcfb                                                                                [+] PiDDBLock Locked                                                                                                    [+] PiDDBCacheTable result -> TimeStamp: 5284eac3                                                                       [+] Found Table Entry = FFFF808F14E17D00                                                                                [+] PiDDBCacheTable Cleaned                                                                                             [+] g_KernelHashBucketList Found 0xFFFFF801124B8080                                                                     [+] g_HashCacheLock Locked                                                                                              [+] Found In g_KernelHashBucketList: \Users\ADMINI~1\AppData\Local\Temp\vVqjtVsJWgGIsrkm                                [+] g_KernelHashBucketList Cleaned                                                                                      [+] MmUnloadedDrivers Cleaned: vVqjtVsJWgGIsrkm                                                                         [+] Image base has been allocated at 0xFFFFD201CB0EF000                                                                 [+] Skipped 0x1000 bytes of PE Header                                                                                   [<] Calling DriverEntry 0xFFFFD201CB0EF1B0                                                                              [+] DriverEntry returned 0x00000000                                                                                     [<] Unloading vulnerable driver                                                                                         [+] NtUnloadDriver Status 0x0                                                                                           [+] Vul driver data destroyed before unlink                                                                             [+] success
```



```text
Run as admin Usermode.exe at apex lobby , don't use cmd too

change kdmapper entry point , name / pack usermode and driver / delete traces
```


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



---







## **Stop sharing shit about Glow hacks!**

https://www.unknowncheats.me/forum/apex-legends/397711-stop-sharing-shit-glow-hacks.html

**1.- The context, what fucking is the context?(0x310):**

Basically the game have some predefined **styles** and **colors**, for the team, for the items and other shits... depending the context, the offset to read the glow color/other params will change!

All the people set the **context** as 1 thinking that is like 1/0 boolean value but no, for example **bloodhunt** context is **7**!  



**2.- The color offset(0x1D0):**

Some people put random values in the color and try with the idea that will have luck they think that is a value from 0 to 255 like other structures but again NO it's not a 0-255 value
The color is an structure like

```c++
struct Color {
	float r, g, b;
};
```

and as you see they are **float**!! and is really easy to manage, the color is based in percents, for exame 0% r , 0% g and 0% b = black in any other structure here is the same 0.f, 0.f, 0.f is black(or maybe better to say no color)but what happens with the insensity? and here is the trick that values are not between **0.f and 255.f** or FLT_MAX that values controls the amount of that color and if you put too much in one of these you will see this:

![img](assets/24409022339269deb6e189c1284b8e91.png)

i personally recommend to work only with values between **0 and 15.f** like this:

![img](assets/0d47114bab649904789adc532889feef.png)



**3.- The Glow Style Offset(0x27C):**

- Main body style:

Now why bloodhunt have some lines in horizontal in the color and some strange effects?

easy the offset 0x27C controls how the glow is showed and you really can do a lot of shit they are basically 4 bytes or maybe in general a bit mask(didn't check) the first one controls the main glow style (not the borders)

Styles that i see in this byte(you will need to found it by yourself):

![img](assets/0d47114bab649904789adc532889feef.png)

No color:

![img](assets/240bf318e532fd5db995b4c51b1941e6.png)

Bloodhunt mode:

![img](assets/20b5365d6382828e7d8b048f2b0fcae3.png)

Scanner mode:

https://gyazo.com/e754173b30aa0b82fcc0bd934931e1b3

Something near of wireframed:

![img](assets/c9ecc9c2383076e3858b80aa8f9f7328.png)



- Border style:

The second byte is exactly the same but only for the border for example you can put a border like bloodhunt with the little scanning style

https://gyazo.com/0c98360dd650c7bb15eeaca5a5efd111

- Border Size

the 3th byte is the border size

- Unknown

and the 4th i don't know exactly but some of them makes the character transparent and other visible, i set it as 75(decimal) because is see the game setting it somewhere  



**4.- The render importance/order offset(0x320)**

Now your enemy is visible until he go behind a wall and he disappear

yeah because the game have something like the **"object importance"/"drawing order"** or idk what it's but that value hides the character

the offset is 0x320 and the game normally put it as 5 and we want it as 1(or 0, no difference i think) to show **through walls and smoke**

通过墙和烟雾



**5.-The glow duration:**

I didn't found anything exactly that looks line a duration but a lot of people put the duration in `FLT_MAX` and by some reason it don't work as spected why???

I have check what the game does in some address and don't looks like a duration address there, looks more like the game removes the glow by himself

but in any case use `FLT_MAX` isn't the correct method, after some reversing i see the game sets the global game time to `0x2EC` and for at least 4 values more in the user object this time less `1f`

something like:

```c++
0x2EC = global_time
0x2D8 = global_time - 1.f
0x2DC = global_time - 1.f
0x2E0 = global_time - 1.f
0x2E4 = global_time - 1.f
```

why the game do this? i don't know but with this data at least for me the glow don't disapear

i found the global time in `0xEE4` maybe there are another method to get it.

Some people sets `0x2d0` and `0x2d4` with `FLT_MAX` too but this offsets are like a byte mask to some styles/some shit that makes the glow visible/enable and use the duration, and other values, if this mask is wrong the game will remove the glow **immediately**

im setting both offsets as `0x34000000(872415232)` because the game set it somewhere and works perfectly





> glow magic number is not in 0x27C but in [0x278 + context * 4]
> if your context is 1, then it is indeed in 0x27C
>
> ``` c++
> // About highlight magic:
> // highlight magic = [31 ... 0] bits
> // [07-00] = Inside function
> // [15-08] = Outline function
> // [23-16] = outline radius on the given context
> // [29-24] = Get custom state on the given context
> // [   30] = Tells if this entity will be drawn
> // [   31] = Tells if this highlight will be drawn after all post-processes
> ```
>
> 



## External Apex Glow Esp

https://github.com/SurgeGotTappedAgain/External-Apex-Cheat



driver pasted from: [https://github.com/Rubery/RuberyKernel](https://github.com/Rubery/RuberyKernel) and user mode is pasted from that source and https://github.com/Sndix/Apex-Legends-Simple-Glow







---

https://casualhacks.net/apexstuff/highlight-functions.html



## Script Highlight

https://www.unknowncheats.me/forum/apex-legends/446349-script-highlight.html
# GH1



## 4. Guide - Game Hacking FAQ - Frequently Asked Questions



**How to Bypass anticheat?**

[Guide - How to Get Started with AntiCheat Bypass](https://guidedhacking.com/showthread.php?9882-How-to-Bypass-Anticheat-Tutorial-for-Noobs)

Do not post "how to bypass" shit threads please.
[Read the How to Bypass Anticheat Guide for Noobs](https://guidedhacking.com/showthread.php?9882-How-to-Bypass-Anticheat-Tutorial-for-Noobs)



**Game crashes when loading Cheat Engine?**

Change debugger in CE settings to **VEH Debugger**, if that doesn't work, read the first couple paragraphs of [Guide - How to Get Started with AntiCheat Bypass](https://guidedhacking.com/showthread.php?9882-How-to-Bypass-Anticheat-Tutorial-for-Noobs)



**How to use MultiLevel pointers in C++?**

Use the good ol' [FindDmaAddy](https://guidedhacking.com/finddma) function from Fleep that de-references and adds the offsets for you, we fixed it up a bit to be even nicer



**How to use client.dll+0xDEADBEEF in C++?**

Use the [GetModuleBase ](https://guidedhacking.com/getmodulebase) function which uses the ToolHelp32Snapshot function to walk through the loaded modules and grab the base address on your modules.



**How to find multilevel pointers in cheat engine?**

Part of 2 of  video will show you an excellent method of finding pointers manually. [PointerScanner Video Tutorial](https://guidedhacking.com/showthread.php?9739-Cheat-Engine-How-to-Pointer-Scan-with-Pointermaps)



**How to find offsets?**

Use Cheat Engine "Find what Accesses/Writes", in the assembly the game will access variables using the proper offsets, these are the offsets you will use. [This tutorial ](https://guidedhacking.com/showthread.php?7194-Cheat-Engine-How-To-Hack-Any-Game) is very good for beginners.



**Why isn't my hack working?**

[Learn to Debug Your Hack with the Visual Studio Debugger](https://guidedhacking.com/debug)



**How to inject a DLL?**
[Use the GH Injector!](https://guidedhacking.com/resources/guided-hacking-dll-injector.4/)



**How to update offsets/addresses for a new version of the game?**

Anywhere in the project where addresses or offsets are defined you need to update them. 

[Learn to find pointers/offsets here](https://guidedhacking.com/showthread.php?7194-Cheat-Engine-How-To-Hack-Any-Game-1-10-Difficulty-Part-1-2)



[**What's the difference between internal and external?**](https://guidedhacking.com/showthread.php?9884-Game-Hacking-FAQ&p=53836&viewfull=1#post53836)



**What game should I learn game hacking on?**

**Assault Cube first**, then either CSGO or COD4. Do not learn game hacking on new games, it's too complicated for beginners. These 3 games have tons of resources and everyone on the forum can help you hack them because we have experience with them. If you pick some random new game, no one can help you and it will be a waste of time and extremely frustrating.



**Common Visual Studio ProblemsLinker Errors:**

```C++
Error LNK2019    unresolved external symbol
```

This error means the compiler cannot find the "external symbol". The "external symbol" is usually a function. You're calling a function but it wasn't included properly, like you probably forgot to include the header file or link the lib/dll. The compiler will even tell you what line of code the error is on. You need to correctly link the header file and any LIB/DLL that's needed.



For instance this error:

```cpp
Erro LNK2019    unresolved external symbol glBegin referenced in function "int __stdcall hwglSwapBuffers()
```

Was fixed by adding:

```c++
#pragma comment(lib, "lib\\OpenGL32.Lib")
#include <gl\GL.h>
```



**Unicode/MultiByte Character Set**

Seeing error "cannot convert char* to LPWSTR?" or something similar?This happens because projects can be be set to use a certain type of string literal, Unicode or "regular" Multibyte Character Set (MBCS)Fleep made his tutorials using Multibyte Character Set but the industry standard is Unicode, Visual Studio 2017 has the default set to Unicode.

If you want char* string literals to be single byte chars, set the project to Multibyte Character Set, especially if you're doing a Fleep tutorial. `Project Properties -> General -> Character Set`



[error C2664 cannot convert argument 1 from 'const char 11' to 'LPSTR' - Guided Hacking](https://guidedhacking.com/threads/error-c2664-cannot-convert-argument-1-from-const-char-11-to-lpstr.11827/)



**How to install Windows Forms for Fleep Tutorials on Visual Studio 2017?**

[Visual Studio 2017 - Windows Forms](https://social.msdn.microsoft.com/Forums/vstudio/en-US/e6fbde42-d872-4ab3-8000-41ab22a4a584/visual-studio-2017-windows-forms?forum=winformsdesigner)





**Internal vs.External?**

**External**

External Hacks use `WriteProcessMemory`(WPM) and `ReadProcessMemory`(RPM) to interact with the game process's memory. To do this you need to ask the [kernel](https://guidedhacking.com/threads/kernel-mode-drivers-info-for-anticheat-bypass.11325/) to give you a `handle` to the process by using `OpenProcess()` with the [Process Access Rights](https://msdn.microsoft.com/en-us/library/windows/desktop/ms684880(v=vs.85).aspx) you require, typically `PROCESS_ALL_ACCESS`. The handle is a required parameter for RPM/WPM. 

Kernel mode anticheats can easily block external hacks by using `ObjRegisterCallbacks` to block handle creation. [Info from DouggemHacks](https://douggemhax.wordpress.com/2015/05/27/obregistercallbacks-and-countermeasures/). RPM/WPM is slow because you have **the overhead of the API calls into the kernel** 从应用层到内核的交互开销. You should **limit the frequency** 限制频率of these calls and **store as much information locally as possible** 存储一些信息到本地 to increase the performance of your external hack. 

If the game has no method of detecting RPM making an overlay ESP is a good way of making an `undetected external ESP` because you **only need RPM** to be undetected.


**Pros of external:**

- In my opinion none compared to internal unless you just want to super quickly patch some bytes and then close the hack


**Cons of external:**

- Super easy to detect because of the open process handle
- Harder to use especially for beginners (WPM/RPM, getting the PID) though easy to master because it has no potential
- Less potential
- Slow



**Internal**

Internal hacks are created by **injecting DLLs** into the game process, when you do this you have **direct access to the process's memory** which means fast performance and simplicity. Injected DLL's can be made more sneaky by using different injection methods such as Manual Mapping. View the  [GuidedHacking Injector](https://guidedhacking.com/ghinjector)  thread for more info.

Try a [simple DLL hack source code](https://guidedhacking.com/showthread.php?7451-Assault-Cube-internal-DLL-skeleton) for Assault Cube for learning purposes. When you are internal you create pointers to objects, typecast them and point them to objects in memory. Then you can access variables of that object easily through the pointer. [ReClass](https://guidedhacking.com/resources/reclass-net-download.2/) is a great tool for generating classes from memory. This is an example of how to typecast variables in memory and modify them in an internal cheat:

```c++
DWORD* localPlayerAddress = (DWORD*)(0x509B74);
int * health = (int*)(*localPlayerAddress + 0xf8);
*health = 1337;
```

**Pros of internal:**

- Sick performance
- Easy to start off with
- Much potential
- Can be super sneaky and almost impossible to detect if done properly


**Cons of internal:**

- Hard to master
- Easier to detect when you don't know what you're doing





If anyone is starting internal, I recommend reading this first [Walkthrough: Create and use your own Dynamic Link Library (C++)](https://docs.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp)



---

## 6. How To Hack Any Game - Cheat Engine


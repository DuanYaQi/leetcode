# Guided Hacking

https://guidedhacking.com/forums/the-game-hacking-bible-learn-how-to-hack-games.469/

https://guidedhacking.com/threads/game-hacking-fundamentals-the-game-hacking-book.16550/





- [x] https://guidedhacking.com/threads/getting-started-how-to-find-the-entity-list.10300/
- [x] https://guidedhacking.com/threads/how-to-solve-problems-achieve-goals.14359/
- [x] https://guidedhacking.com/threads/stop-pasting-focus-on-the-basics.14126/
- [ ] https://guidedhacking.com/threads/how-to-learn-c-programming-where-to-learn-c.10820/
- [ ] https://guidedhacking.com/threads/ghb1-start-here-beginner-guide-to-game-hacking.5911/
- [ ] https://guidedhacking.com/threads/finddmaaddy-c-multilevel-pointer-function.6292/
- [ ] https://guidedhacking.com/threads/get-module-base-address-tutorial-dwgetmodulebaseaddress.5781/
- [ ] https://guidedhacking.com/threads/how-to-bypass-anticheat-start-here-beginners-guide.9882/
- [ ] https://guidedhacking.com/threads/how-to-find-the-entitylist-address-tutorial.10235/
- [ ] https://guidedhacking.com/threads/how-to-hack-any-game-tutorial-c-trainer-1-external.10897/
- [ ] https://guidedhacking.com/threads/getting-started-how-to-find-the-entity-list.10300/
- [ ] https://www.unknowncheats.me/forum/general-programming-and-reversing/451666-educational-resources-learning-kernel-dev.html#post3129608





---

## Getting Started How to find the Entity List

https://guidedhacking.com/threads/getting-started-how-to-find-the-entity-list.10300/

**What is an entity?**

In it's simplest terms, an entity is an **object** which is an instance of a class（实体是一个对象，它是一个类的实例）. An entity is typically an actor. An actor is something that interacts with other objects in the game. （实体通常是演员，演员是与游戏中其他对象进行交互的东西）In terms of game hacking, an entity is typically referring to a player object（实体通常是指玩家对象）. When you're playing online the objects which contain the information about yourself and the other players are referred to entities. These objects typically contain the player's `location, angle, health information` and more but not all variables are required to be in this class.



**What is an Entity List?**

An entitylist is a container of entity objects.(一个实体列表是实体对象的容器) In some games the entitylist contains **all** the entities in the game, not just the player objects.



**An entitylist can be many different types of containers**

- an array of entity pointers (most common)   实体指针数组
- an array of entity objects 实体对象数组
- a linked list of entity objects 实体对象的链表
- a linked list of nodes which point to entity objects 指向实体对象的节点链表
- an array of nodes which contain pointers to entity objects (actually a linked list underneath) 指向实体对象的指针的节点数组（链表的底层实现）



**Quake Engine / COD Engine Games** = array of entity objects 实体对象数组

**Assault Cube** = array of entity pointers 实体指针数组

**Unreal Engine** = a linked list of all entity objects (not just players). Sometimes it will have seperate lists containing only the player objects。 所有实体对象（不仅是玩家）的链表。有时是仅包含玩家对象的单独列表

**CSGO** = an array of nodes which point to entity objects 指向实体对象的节点数组



An array of player objects looks like this: 玩家对象的数组

```cpp
struct player
{
    int health;
}

player entityList[32];
```

An array of player pointers looks like this: 玩家指针的数组

```c++
struct player
{
    int health;
}

player* entityList[32];
```



**How to find an Entity List?**

Before you try to find an entity list you need to figure out what type of container it is. If you know the game engine, you already know what type it will be.（确定容器，引擎）

- Start by finding the address of multiple player objects and yourself, write them down（找多人玩家对象和自己的地址）
- Verify the are of the same class: check the vTable pointers, do they **point to the same vtable**?（验证是否具有相同的类，检查vTable指针是否指向相同的vTable）
- Compare the addresses of the objects, do you see any pattern?（比较对象的地址）
- If you subtract bot 1's address from bot 2 address, you get the difference in bytes between the two objects.（计算bot1和bot2的字节差）
- Now subtract bot 3's address from bot 4's address. Is this the same difference as between bot 1 and 2?（计算bot3和bot4的字节差）
- If so, this is the size of the player object and it's most likely **an array of objects** because they are contiguously placed in memory.（如果两个字节差相同，这个差值就是玩家对象的大小，并且很可能是由对象数组存储，因为它们连续地放置在内存中）
- If so, then find the first object in the array, and you have the address of entityList[0], if it's a **static** address then you have the entitylist address（如果是由对象数组存储，则在数组中找到第一个对象，即`entityList[0]` 的地址，如果它是静态地址，则也拿到了 `entitylist` 地址）
- If it's a **dynamic** address, find a **pointer** to it or use **pattern scanning** to get the correct address at runtime（如果是动态地址，请找到指向它的**指针**或使用**模式扫描**在运行时获取正确的地址）



If they are **not contiguous** in memory（不连续）, then these are **dynamically located**（动态定位的） and the game would need **pointers** to get to them（需要指针）, therefore there is an array of player object pointers.（玩家对象指针数组）

- In this case, create a list of pointers to these objects, by scanning for them in Cheat Engine（通过在 CE 中扫描这些对象来创建指向这些对象的指针列表）
- Compare where these pointers are in memory, are some of the pointers near each other?（比较这些指针在内存中的位置，某些指针是否彼此靠近？）
- If so then this is probably **the array of player object pointers**（如果是，那么这可能是玩家对象指针的数组）
- On x64 if you see a loop that looks like "mov eax, [ecx + 8 * ebx]" then ECX points to the array of pointers, 8 is the size of a pointer, and ebx is the iterator or player ID.（在x64上，如果看到的循环看起来像 `mov eax, [ecx + 8 * ebx]`，其中 `ecx` 指向指针数组，8 是指针的大小，而 `ebx`是迭代器或玩家的 ID）
- On x86 you will see a 4 instead of an 8. （在x86下，看到的循环看起来像 `mov eax, [ecx + 4 * ebx]`）



If it's niether an array of objects or an array of pointers, then it's either a **linked list** or an abstract form of the other possibilities.（如果既不是对象数组也不是指针数组，可能是使用链表或更抽象的形式来储存）

If it's a **single linked list**, there will be a pointer in each object which points to the next object（如果是单链表，则每个对象中都有一个指针指向下一个对象）, called the Forward Link or Next Link, just look inside the object for pointers, see if the objects they point to are of the same type by comparing offsets and especially the vTable pointer.（通过比较 指向对象的偏移量 判断它们是否具有相同的类型，尤其是 `vTable` 指针）

If it's a **double linked list**, each object will contain a forward link and back link, pointing to the previous and next node in the linked list.（每个对象有两个指针，指向前驱节点和后继节点）



**Call of Duty / Quake Engine Entitylists**
https://guidedhacking.com/threads/how-to-hack-call-of-duty-games-quake-engine-games.11155/



**Unreal Engine EntityList**
It's a linked list read:
https://guidedhacking.com/threads/unreal-engine-game-hacking.14278/



**Try the Guided Hacking Entity List Finde**

https://guidedhacking.com/resources/gh-entity-list-finder.36/



**Tutorials**
Tutorial - How to find Entity List Pointer in AC!

Tutorial - How to Find Entity List - Wolfenstein Hack Tutorial

Source Code - How To Loop Through Entity List Internally



---

## How to Solve Problems & Achieve Goals

https://guidedhacking.com/threads/how-to-solve-problems-achieve-goals.14359/

**Scientific Method**

- Question
- Hypothesis 假设
- Experiment
- Observation
- Analysis
- Conclusion



**Question**

How do I **access**（访问） the `ammo` variable **dynamically**?



**Hypothesis**

Perhaps there is `ammo` variable inside the `player` class, if I can **access** the `player` object I can then access the `ammo` variable



**Observation**

We open **cheat engine**, find the `health` address and `ammo` address, use "**find what accesses**" to see how they are used. We discover that the offsets **are not offset from the same object address** for each of these variables（这两个变量不是来自同一基址的偏移量）. In addition, when we change guns, the ammo address changes.



**How do you form this hypothesis?**

Pretend you are the developer and come up with your own logic for managing multiple weapons and weapon related variables. How do you keep track of the current weapon you're using so you decrease from the correct ammo variable? Come up with a couple different logical methods that might make sense, and then test them. This is indeed how I would do it when you consider Object Oriented Programming, I would create **dynamic objects** （动态对象）and keep track of them by using **pointers** （指针）and as **the owner of the weapon is the player**（武器的持有者-玩家）, I would **put the pointer in the entity object**.（指针在entity对象内）



**Observation & Analysis**

The structure which `ammo` is in, is indeed the `weapon` object. We find other variables related to the weapon in it. We also notice it is in an array of `other weapon` objects which have the **same structure and act similarly**. When we trace back each `ammo` address to a `dynamic multilevel pointer` for the current weapon, and then change this weapon, we notice **a pointer in the player class which always points to the current weapon ammo**.



**Conclusion**
The game keeps track of the ammo dynamically by using a `pointer` to `the current weapon` object which is inside an array of `weapon` objects（使用指针指向当前武器对象来动态跟踪子弹，该武器对象位于一系列武器对象中）. When you switch weapons, the pointer changes to point at the correct weapon. The `ammo` variable for this `weapon` and other `weapon` variables are accessed from this address by relative offset（从该地址通过相对偏移量访问此武器的弹药变量和其他武器变量。）.



To access the ammo variable dynamically we need only **calculate this multilevel pointer** at run time and it will always **point at the correct ammo address**.（要动态访问ammo变量，我们只需要在运行时计算此多级指针，它将始终指向正确的ammo地址）

So next time you have a little problem like "can't find [entity list](https://guidedhacking.com/threads/getting-started-how-to-find-the-entity-list.10300/), it's not like assault cube". You need to use the scientific method to figure it out, **form multiple hypotheses**. If you can't solve the problem after a few days, then ask your question. **If you can't form solid hypotheses to test, the reason is because you don't have enough knowledge and evidence to form the basis of your experiment, in which case you need to search the forum and watch some tutorials.**（如果您无法形成可靠的假设进行检验，则原因是您没有足够的知识和证据来构成实验的基础，在这种情况下，您需要搜索论坛和看一些教程。）



**Constants**

For example, if you have some weird issue with a lib on one game on one computer, but it works fine on another computer in another game your variables might look like:（如果您在一台计算机上的一个游戏上有一个lib问题，但是在另一游戏中的另一台计算机上它却可以正常工作，则您的变量可能如下所示）

- Game
- Operating System
- Architecture
- Game Logic

You need to **isolate** Game, Operating System & Architecture and define them as constants.（您需要隔离游戏，操作系统和体系结构，并将它们定义为常量） This way you are **only testing for the definition of "Game Logic"**（这样，您仅测试“游戏逻辑”）. If you only define Game, Architecture as constants, when you perform your observation, you will **not be able to** draw a conclusion which defines the cause and effect of the other **two variables** in the experiment.（如果仅将“游戏，体系结构”定义为常量，那么在执行观察时，将无法得出定义实验中其他两个变量的因果关系的结论。）

```c++
With too many non-constant variables you cannot attribute the cause and effect to the correct variable.
```



We see this all too often with questions "dll won't inject, why?". No one can solve this problem because there are too many unknowns, we need constants so we can hypothesize the potential causes of the problem:

- What OS are you on?
- What Injector are you using?
- What game are you injecting into?
- Does it have anticheat?
- Is the game x86 or x64?
- Is the injector x86 or x64?
- Is the DLL x86 or x64?
- What's the source code for the dll?
- Are you compiling in **debug** mode or **release** mode?
- etc...



If you use the scientific method, you can solve almost any problem yourself with time and patience.

**How to Be Successful & Achieve Goals**

Before you can be successful at anything you must:

- Define your goal
- Research what is required to achieve your goal
- Come up with an action plan & timeline
- Assess your ability to achieve the goal 评估
- Commit to achieving the goal
- Perform the Action Plan
- Achieve the goal and declare victory



---

## Stop Pasting - Focus on the Basics

https://guidedhacking.com/threads/stop-pasting-focus-on-the-basics.14126/



**foundational knowledge + intuition + experience + patience = skills**









---

## Guide - Become a great game Hacker by Learning the Fundamentals

https://guidedhacking.com/threads/become-a-great-game-hacker-by-learning-the-fundamentals.14419/

I know @Rake has stressed this many times in the past as well but just to remind you:

```c++
To hack games you have to know how games work
```

As saied we will learn to develop games and engines first.

```c++
A solid fundation is key and gives you the ability to pick up stuff you where not able to understand before
```



- [x] Basics of C++
- [ ] Modern C++
- [ ] Graphics Programming
- [ ] Game Engines
- [ ] Math Fundamentals



---

### Basics of C++

Most games are still and will be developed directly or indirectly in c++ for a long time (some engines support scripting languages like lua or c# to enable content creators to program game logic).

Also most hacks for games are written in c++ as well so it is essential to pick up this language at some point if you want to be successful in game hacking.

https://www.youtube.com/watch?v=vLnPwxZdW4Y

Now that you have the basics down you want to **go more in depth** and **learn modern c++ standards** and **how to write good code**. (i heared c++11 is still heavily used in the industry but most copilers support **c++17** by now so its a good idea to pick up some stuff from there as well since it can help you out in some situations)

Im not gonna lie probably the best way to learn this is by picking up a **book**, since you can clearly tell there went some thought into writing it. (unlike most online resources)

For example i really did enjoy watching the c++ series from "The Cherno". Watch it, its really good:

https://www.youtube.com/watch?v=18c3MTX0PK0&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb

After you read your book and watched through this series you should have **a solid understanding of modern c++ standards and good coding habbits**.

Finally here are some words of wisdom from the creator of c++ himself on modern c++:

https://www.youtube.com/watch?v=fX2W3nNjJIo

Congrats first step is done and you should have a solid fundation in c++ now.
Just in case you need some reference there are ofc: `learncpp.com` 、`cppreference.com` and `msdn.com`

To reach this point you should really take your time. Personally i went through this all in about **3 month**.



C++ primer 6th

Professional C++ 5th



---

### Graphics Programming

To make something more interesting like **mod menus** or even just **esp hacks** and to understand **how game graphics work** you will need to learn a **graphics api**.

Feel free to **learn the api your game is using**. But if you dont have a specific game you are working on do yourself a favor and **start with opengl**. I know its not too common but you can pick it up pretty fast and get an understanding for **how your gpu opperates**.

I would also like to link "The Cherno"s' playlist covering OpenGL here:

https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2



---

### Game Engines

Most games these days are not written from scratch but rather where developed in a game engine like Unreal, Unity, ... which are public game engines but there are also a lot of private game engines which are mostly used by AAA Game Development studios.

So it is a good idea to have a look in a **public game engine** but also have an understanding **how game engines work under the hood**.

For this i would again like to link to a playlist by Cherno where you will learn how to create your own game engine from scratch:

https://www.youtube.com/watch?v=JxIZbV_XjAs&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT

After that you should have a solid understanding about **the concepts of an game engine** and be able to dig deeper into the game engine your game uses. A good practice would also be to have look the source of an open source game engine like [cube2](http://sauerbraten.org/) and figure out how it works.



### Math Fundamentals

there are other fundamentals you should have like math

I would like to add to this topic that **basic math concepts** are pretty important as well. You by no means have to be an expert but especially **trigonometry** and **linear algebra** should be somewhere in your vocabulary. 

https://www.youtube.com/watch?v=sKCF8A3XGxQ&list=PLW3Zl3wyJwWOpdhYedlD-yCB7WQoHf-My

This should cover 99% of the needed math you will need as a game hacker.





------

## GHB0 - Game Hacking Bible Introduction

https://guidedhacking.com/threads/ghb0-game-hacking-bible-introduction.14450/



## GHB1 - Start Here Beginner Guide to Game Hacking

https://guidedhacking.com/threads/ghb1-start-here-beginner-guide-to-game-hacking.5911/



### 1. Video Tutorial - Squally CS420 Game Hacking Course

https://guidedhacking.com/threads/squally-cs420-game-hacking-course.14191

finish in E_HackingBasic.md  Chapter 6

#### 1.1. Game Hacking Course Introduction

#### 1.2. Memory Editing 1

#### 1.3. Base Systems - Hex, Decimal & Binary

#### 1.4. How to Hex Edit Games

#### 1.5. Memory Editing 2 & Data Types

#### 1.6. Virtual Memory

#### 1.7. Virtual Memory 2 & Multilevel Pointers Tutorial

#### 1.8. How to Edit Assembly Tutorial





---

### 2. Guide - Game Hacking FAQ - Frequently Asked Questions

https://guidedhacking.com/threads/game-hacking-faq-frequently-asked-questions.9884/



**How to [Bypass anticheat](https://guidedhacking.com/threads/how-to-get-started-with-anticheat-bypass.9882/)?**

[Read the How to Bypass Anticheat Guide for Noobs](https://guidedhacking.com/showthread.php?9882-How-to-Bypass-Anticheat-Tutorial-for-Noobs)



**Game crashes when loading Cheat Engine?**
Change debugger in CE settings to **VEH Debugger/kernelmode**, if that doesn't work, read the first couple paragraphs of [Guide - How to Get Started with AntiCheat Bypass](https://guidedhacking.com/showthread.php?9882-How-to-Bypass-Anticheat-Tutorial-for-Noobs)



**How to use MultiLevel pointers in C++?**
Use the good ol' [FindDmaAddy ](https://guidedhacking.com/finddma)function from Fleep that de-references and adds the offsets for you, we fixed it up a bit to be even nicer



**How to use client.dll+0xDEADBEEF in C++?**
Use the [GetModuleBase ](https://guidedhacking.com/getmodulebase)function which uses the ToolHelp32Snapshot function to walk through the loaded modules and grab the base address on your modules.



**How to find multilevel pointers in cheat engine?**
Part of 2 of [this Cheat Engine Tutorial](https://guidedhacking.com/showthread.php?9690-Cheat-Engine-6-7-Tutorial-Video-Guide) video will show you an excellent method of finding pointers manually.
[PointerScanner Video Tutorial](https://guidedhacking.com/showthread.php?9739-Cheat-Engine-How-to-Pointer-Scan-with-Pointermaps) : Learn how to use PointerScanner and pointermaps for finding multilevel pointers



**How to find offsets?**
Use Cheat Engine "Find what Accesses/Writes", in the assembly the game will access variables using the proper offsets, these are the offsets you will use. [This tutorial ](https://guidedhacking.com/showthread.php?7194-Cheat-Engine-How-To-Hack-Any-Game)is very good for beginners.



**Why isn't my hack working?**
Because you suck. [Learn to Debug Your Hack with the Visual Studio Debugger](https://guidedhacking.com/debug)



**How to inject a DLL?**
[Use the GH Injector!](https://guidedhacking.com/resources/guided-hacking-dll-injector.4/)



**How to update offsets/addresses for a new version of the game?**
Anywhere in the project where addresses or offsets are defined you need to update them. [Learn to find pointers/offsets here](https://guidedhacking.com/showthread.php?7194-Cheat-Engine-How-To-Hack-Any-Game-1-10-Difficulty-Part-1-2)



**What's the difference between internal and external?**

https://guidedhacking.com/showthread.php?9884-Game-Hacking-FAQ&p=53836&viewfull=1#post53836



**What game should I learn game hacking on?**

**Assault Cube** first, then either **CSGO** or **COD4**. Do not learn game hacking on **new games**, it's too complicated for beginners. 

Do not try to learn game hacking on **Unity, Unreal Engine or Java games**. Only learn game hacking on **native C++** games.



**Common Visual Studio Problems**

**Linker Errors:**

```c++
Error LNK2019    unresolved external symbol
```

This error means the compiler **cannot find the "external symbol"**. The "external symbol" is usually a **function**. You're calling a function but **it wasn't included properly**, like you probably forgot to **include the header file** or **link the lib/dll**. You need to correctly link the header file and any LIB/DLL that's needed.

例如报错

```c++
Erro LNK2019    unresolved external symbol glBegin referenced in function "int __stdcall hwglSwapBuffers()
```

修复

```c++
#pragma comment(lib, "lib\\OpenGL32.Lib")
#include <gl\GL.h>
```



**Unicode/MultiByte Character Set**

Seeing error **"cannot convert char* to LPWSTR?"** or something similar?

This happens because projects can be be set to use a certain type of string literal, Unicode or "regular" Multibyte Character Set (MBCS)

Fleep made his tutorials using Multibyte Character Set but the industry standard is Unicode, Visual Studio 2017 has the default set to Unicode.

If you want char* string literals to be single byte chars, set the project to Multibyte Character Set, especially if you're doing a Fleep tutorial.

Project Properties -> General -> Character Set



```c++
error C2664 cannot convert argument 1 from 'const char [11]' to 'LPSTR'
```

https://guidedhacking.com/threads/error-c2664-cannot-convert-argument-1-from-const-char-11-to-lpstr.11827/



**How to install Windows Forms for Fleep Tutorials on Visual Studio 2017?**
[Visual Studio 2017 - Windows Forms](https://social.msdn.microsoft.com/Forums/vstudio/en-US/e6fbde42-d872-4ab3-8000-41ab22a4a584/visual-studio-2017-windows-forms?forum=winformsdesigner)



**Internal vs. External?**



**External**
External Hacks use `WriteProcessMemory` (WPM) and `ReadProcessMemory` (RPM) to interact with the game process's memory. To do this you need to ask the [kernel](https://guidedhacking.com/threads/kernel-mode-drivers-info-for-anticheat-bypass.11325/) to give you a handle to the process by using `OpenProcess()` with the [Process Access Rights](https://msdn.microsoft.com/en-us/library/windows/desktop/ms684880(v=vs.85).aspx) you require, typically `PROCESS_ALL_ACCESS`. The handle is a required parameter for RPM/WPM. [Kernel](https://guidedhacking.com/threads/kernel-mode-drivers-info-for-anticheat-bypass.11325/) mode anticheats can easily block external hacks by using `ObjRegisterCallbacks` to **block handle creation**. 

[Info from DouggemHacks](https://douggemhax.wordpress.com/2015/05/27/obregistercallbacks-and-countermeasures/). RPM/WPM is **slow** because you have the overhead of the API calls into the kernel. You should **limit the frequency of these calls** and store as much information **locally** as possible to increase the performance of your external hack. If the game has **no method of detecting RPM** making an **overlay ESP** is a good way of making an undetected **external ESP** because you **only need RPM** to be undetected.

Pros of external:

- In my opinion none compared to internal unless you just want to **super quickly patch some bytes and then close the hack**


Cons of external:

- Super **easy to detect** because of the open process handle
- Harder to use especially for beginners (WPM/RPM, getting the PID, blalba) though easy to master because it has no potential
- **Less potential**
- **Slow**



**Internal**

Internal hacks are created by **injecting DLLs** into the game process, when you do this you have direct **access to the process's memory** which means **fast performance and simplicity**. Injected DLL's can be made more **sneaky**(隐蔽) by using **different injection methods** such as Manual Mapping. View the [GuidedHacking Injector](https://guidedhacking.com/ghinjector) thread for more info

Try a [simple DLL hack source code](https://guidedhacking.com/showthread.php?7451-Assault-Cube-internal-DLL-skeleton) for Assault Cube for learning purposes.

When you are internal you create **pointers to objects**, typecast(类型化) them and point them to objects in memory. Then you can access variables（访问变量） of that object easily through the pointer. [ReClass](https://guidedhacking.com/resources/reclass-net-download.2/) is a great tool for generating classes from memory. This is an example of how to typecast variables（类型化变量） in memory and modify（修改） them in an internal cheat:

```c++
DWORD* localPlayerAddress = (DWORD*)(0x509B74);
int * health = (int*)(*localPlayerAddress + 0xf8);
*health = 1337;
```



Pros of internal:

- Sick performance
- Easy to start off with
- Much potential
- Can be super sneaky and almost impossible to detect if done properly


Cons of internal:

- **Hard to master**
- **Easier to detect when you don't know what you're doing**



If anyone is starting internal, I recommend reading this first [Walkthrough: Create and use your own Dynamic Link Library (C++)](https://docs.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp)



---

### 3. Video Tutorial - Cheat Engine Tutorial Video Guide

#### 3.1. Cheat Engine Tutorial Guide 1/3 Steps 1-5

大部分为 4 字节，还有浮点数，双浮点数（扫描双浮点数类型建议禁用 "快速扫描"）



![image-20210510223547168](assets/image-20210510223547168.png)

右键/F5 设置断点，F7 步进

```assembly
#  rax存的是地址
mov [rax], edx #edx的值即RDX的值 00 00 01 3E 赋给 [rax]  318
```

或者右键 replace with code that does nothing



#### 3.2. Cheat Engine Tutorial Guide 2/3 Steps 6-9 Pointers & Code Injection

##### Step 6

搜索这个存储血量的地址

![image-20210510224950837](assets/image-20210510224950837.png)

得到基址（即一个指针，这个指针指向血量）

![image-20210510225040404](assets/image-20210510225040404.png)

手动添加地址（指针）

![image-20210510225150568](assets/image-20210510225150568.png)



green glow means static meaning that it's going to be either relative to the base address (its gonna be the same address in the process every time)

**relative offset**

```c++
int health = 1337;
int* myhealth = &health; //指针myhealth指向血量变量
cout << *myhealth; //1337

//每次血量变量动态分配，pointer指向新的动态地址
while (1) {
	myhealth = new int(health);  
    sleep(4);
}
```



##### Step 7

![image-20210510230725227](assets/image-20210510230725227.png)



##### **Step 8 **- 525927

备注1: 本步骤也可以使用**自动汇编程序脚本**或者使用**指针扫描器**加以解决。
备注2: 在某些情况下，可以改变 CE 软件"代码查找"的相关设置。
当你遇到类似于 `mov eax,[eax]` 的指令时，**调试程序将显示改变之后的寄存器中的值**，也许利用它更容易找出指针的位置。



```c++
//4级指针模板
-> = "points to"
Address = Value = ?
base ptr -> address + offset4 = address
base ptr -> address + offset3 = address
base ptr -> address + offset2 = address
static base -> address + offset1 = address
```



```c++
//模板
-> = "points to"
014C2E08 = Value = 2856
base ptr -> address + offset4 = 014C2E08
base ptr -> address + offset3 = address
base ptr -> address + offset2 = address
static base -> address + offset1 = address
```



find out what access this address `014C2E08`

![image-20210510231822124](assets/image-20210510231822124.png)

```c++
//模板
-> = "points to"
014C2E08 = Value = 376
base ptr -> 014C2DF0 + 0x18 = 014C2E08 // 014C2E08 - 0x18
base ptr -> address + offset3 = address
base ptr -> address + offset2 = address
static base -> address + offset1 = address
```

搜索16进制地址 `014C2DF0`

![image-20210510232258353](assets/image-20210510232258353.png)

```c++
//模板
-> = "points to"
014C2E08 = Value = 376
06275500 -> 014C2DF0 + 0x18 = 014C2E08 // 014C2E08 - 0x18
base ptr -> address + offset3 = 06275500
base ptr -> address + offset2 = address
static base -> address + offset1 = address
```



find out what access this address `06275500`

![image-20210510232540344](assets/image-20210510232540344.png)

```c++
//模板
-> = "points to"
014C2E08 = Value = 376
06275500 -> 014C2DF0 + 0x18 = 014C2E08 // 014C2E08 - 0x18
base ptr -> address + 0 = 06275500
base ptr -> address + offset2 = address
static base -> address + offset1 = address
```

搜索16进制地址 `06275500`

![image-20210510232621231](assets/image-20210510232621231.png)

```c++
//模板
-> = "points to"
014C2E08 = Value = 376
06275500 -> 014C2DF0 + 0x18 = 014C2E08 // 014C2E08 - 0x18
0152A528 -> 06275500 + 0 = 06275500
base ptr -> address + offset2 = 0152A528
static base -> address + offset1 = address
```



find out what access this address `0152A528`

![image-20210510232908839](assets/image-20210510232908839.png)

```c++
//模板
-> = "points to"
014C2E08 = Value = 376
06275500 -> 014C2DF0 + 0x18 = 014C2E08 // 014C2E08 - 0x18
0152A528 -> 06275500 + 0 = 06275500
base ptr -> 0152A510 + 0x18 = 0152A528 // 0152A528 - 0x18
static base -> address + offset1 = address
```

搜索16进制地址 `0152A510`

![image-20210510233222493](assets/image-20210510233222493.png)

```c++
//模板
-> = "points to"
014C2E08 = Value = 376
06275500 -> 014C2DF0 + 0x18 = 014C2E08 // 014C2E08 - 0x18
0152A528 -> 06275500 + 0 = 06275500
0152A2A0 -> 0152A510 + 0x18 = 0152A528 // 0152A528 - 0x18
static base -> address + offset1 = 0152A2A0
```



find out what access this address `0152A2A0`

![image-20210510233323000](assets/image-20210510233323000.png)

```c++
//模板
-> = "points to"
014C2E08 = Value = 376
06275500 -> 014C2DF0 + 0x18 = 014C2E08 // 014C2E08 - 0x18
0152A528 -> 06275500 + 0 = 06275500
0152A2A0 -> 0152A510 + 0x18 = 0152A528 // 0152A528 - 0x18
static base -> 0152A290 + 0x10 = 0152A2A0 //0152A2A0 - 0x10
```

搜索16进制地址 `0152A290`

![image-20210510233459018](assets/image-20210510233459018.png)

```c++
//模板
-> = "points to"
014C2E08 = Value = 376
06275500 -> 014C2DF0 + 0x18 = 014C2E08 // 014C2E08 - 0x18
0152A528 -> 06275500 + 0 = 06275500
0152A2A0 -> 0152A510 + 0x18 = 0152A528 // 0152A528 - 0x18
"Tutorial-x86_64.exe"+306B00 -> 0152A290 + 0x10 = 0152A2A0 //0152A2A0 - 0x10
    
base address = "Tutorial-x86_64.exe"+306B00
```

![image-20210510233550402](assets/image-20210510233550402.png)



##### **Step 9** - 31337157

游戏中的共用代码, 这种代码是通用在除了自己以外的其他同类型对象上。

如果你把健康相关代码移除的话，其结果是你的角色无敌, 但你的敌人也无敌了。

在这种情况下, 你必须想办法**区分自己与敌人**。有时候很简单, 你只要检查**最前面的4个字节**(**函数指针表**), 它通常指向一个独一无二的地址, 代表着游戏玩家角色，而有的时候它是一个团体号码, 或者也可能是一个指针, 它指向另一个指针, 该址针又指向下一个指针,搞不好还指向下下一个指针, 最后指向一个玩家名字。总之完全取决于游戏的复杂度, 以及你的运气

最简单的方法是以"**找出是什么改写了这个地址**"去找出游戏代码，然后使用"**分析(新/旧)数据/结构**"的功能去**比较两种结构**。

当你找到如何区分你和电脑单位的方法后，你可以注入一段自动汇编脚本来检查状态，然后看是要运行游戏的代码还是要做其他的修改。(例如一击必杀)

另外, 你还可以用这个方法去创建一般所说的**"字节数组"的字串, 它可以用来搜寻并产生一份所有你的单位或是敌人单位的列表**





找到四个血量的地址，find out what write this address，然后减去偏移量为基址

查看内存 > 工具 > 分析数据/遍历

![image-20210511003512029](assets/image-20210511003512029.png)

血量 `04` ，[ebx+04]，则队伍 `10`，[ebx+10]，相差 `6` 个字节

这里 string name 的偏移量是 `0015`，health的偏移量是`0010`，

**最前面的4/8个字节**（**函数指针表vTable ptr**）指向的是同一地址

在 Dave 血量的地址 > find out what write this address > 显示反汇编程序 > 自动汇编

**AOB注入**

```assembly
[ENABLE]
//code from here to '[DISABLE]' will be used to enable the cheat

aobscanmodule(INJECT,Tutorial-i386.exe,89 43 04 D9 EE) // should be unique
alloc(newmem,$1000)

label(code)
label(return)

newmem:
  cmp [ebx+10],1 # 如果队伍为1 就不执行正常的减血操作
  jne code
  fldz
  jmp return

code:
  mov [ebx+04],eax
  fldz 
  jmp return

INJECT:
  jmp newmem
return:
registersymbol(INJECT)

[DISABLE]
//code from here till the end of the code will be used to disable the cheat
INJECT:
  db 89 43 04 D9 EE

unregistersymbol(INJECT)
dealloc(newmem)
```



**普通代码注入**

![image-20210511003416965](assets/image-20210511003416965.png)

```assembly
newmem:
cmp [ebx+10] 1          #判断是不是1
jne originalcode		#不是1的话 正常执行 originalcode 减血 不运行下边两条程序了
fldz					#是1的话像 执行fldz
jmp originalcode+5      #执行完 fldz 后执行 fld 与 originalcode 间隔5个byte
#相当于跳过了减血的代码
# 一个jmp是5个字节，编写一个jmp时会覆盖5个字节

originalcode:
mov [ebx+04],eax
fldz
```

![image-20210511003708917](assets/image-20210511003708917.png)

```assembly
#等效
newmem:
cmp [ebx+10] 2
je originalcode
fldz
jmp originalcode+5

originalcode:
mov [ebx+04],eax
fldz
```



Dave 血量动态指针链

搜索时第一级是改写 write，后边都是访问 access

![image-20210511001000469](assets/image-20210511001000469.png)

Eric 血量动态指针链

![image-20210511001308450](assets/image-20210511001308450.png)

HAL 血量动态指针链

![image-20210511001605863](assets/image-20210511001605863.png)

KITT 血量动态指针链

![image-20210511001735651](assets/image-20210511001735651.png)







---

#### 3.3. Cheat Engine Tutorial Guide 3/3 Tutorial Games

##### Level 1

有时候搜索不到值的时候，需要搜索 **总数 - 这个数**，比如子弹数目，有时存储的是打出去的子弹数目，而不是剩余的子弹数目

```c++
//敌人血量
-> = "points to"
018B19C0 = Value = ?
01889618 -> 018B1968 + 58 = 018B19C0
018F5BE4 -> 01889600 + 18 = 01889618
"gtutorial-i386.exe"+2D88C0 -> 018F5750 + 494 = 018F5BE4
```

右键可以使用空指针替换， 然后也可以还原

工具 > 自动汇编 > AOB Injection (find an AOB we can use)

> 特征码定位 signature
>
> 是动态地址，游戏每次重新打开就会改变，而CE用AOB注入的话，CE每次都能够找到这个已变化的地址，然后Jmp到申请的内存地址里
>
> "xxx.exe"+123456就是模块句柄+偏移，模块句柄一般是固定的 你遇到类似u3d做的游戏就不会这么说了，很多代码是动态生成，需要 mono 处理或用 aobscan 和 aobscanmodule 来做特征码定位

```assembly
[ENABLE]

aobscanmodule(INJECT,gtutorial-i386.exe,89 50 58 83 78 54 00) // should be unique
alloc(newmem,$1000)
label(return)

newmem:
  push edx              # 寄存器入栈
  xor edx,edx           # edx = 0
  mov [eax+58],edx      # 直接把血量变为0
  cmp dword ptr [eax+54],00 # 按原内容继续执行
  pop edx
  jmp return

INJECT:
  jmp newmem
  nop 2
return:
registersymbol(INJECT)

[DISABLE]

INJECT:
  db 89 50 58 83 78 54 00

unregistersymbol(INJECT)
dealloc(newmem)
```



##### Level 2

4字节玩家的血量，找到 player 血量的地址

未知的初始值，找到 enemy 血量的地址，可以试试地址 `+4 -4` 找到另一个enemy的地址，并验证。也可以先找一个玩家的血量，**如果玩家和敌人是同一个对象**，那么直接找相关减血的汇编代码如 `sub [eax+50],edx`，右键该行 > find out what addresses this instruction accesses.击打敌人，就可以找到敌人血量的地址。

![image-20210515130234401](assets/image-20210515130234401.png)



这里可以直接全选，右键 > open dissect data with selected address ，就会出现结构分析，找到两个敌人一样，我们跟他们不一样的地方。



查找指针链，找改写地址，再找访问地址。

```c++
//玩家血量
-> = "points to"
018124A8 = Value = ?
0181200C -> 01812458 + 50 = 018124A8
0180625C -> 01811FF8 + 14 = 0181200C
"gtutorial-i386.exe"+2D88C0 -> 01805DC8 + 494 = 0180625C
```



```c++
//ENEMY2血量
-> = "points to"
018120B8 = Value = ?
01812010 -> 01812068 + 50 = 018120B8
0180625C -> 01811FF8 + 18 = 01812010
"gtutorial-i386.exe"+2D88C0 -> 01805DC8 + 494 = 0180625C
```



```c++
//ENEMY2血量
-> = "points to"
018122E8 = Value = ?
01812014 -> 01812298 + 50 = 018122E8
0180625C -> 01811FF8 + 1C = 01812014
"gtutorial-i386.exe"+2D88C0 -> 01805DC8 + 494 = 0180625C
```



查看内存 > 工具 > 分析数据遍历 > 分群组 > 结构/定义新的结构

![image-20210514224056010](assets/image-20210514224056010.png)

找到team变量距离血量 8 个字节，即`eax+58`，AOB注入

```assembly
[ENABLE]

aobscanmodule(INJECT,gtutorial-i386.exe,29 50 50 C3 00 00) // should be unique
alloc(newmem,$1000)

label(code)
label(return)

newmem:
  cmp [eax+58],0 # 如果是我们自己，就不跳
  jne code
  ret
  add [eax],al
  jmp return

code:
  sub [eax+50],edx #  这行改成mov [eax+50],0 实现秒杀
  ret 
  add [eax],al
  jmp return

INJECT:
  jmp newmem
  nop
return:
registersymbol(INJECT)

[DISABLE]

INJECT:
  db 29 50 50 C3 00 00

unregistersymbol(INJECT)
dealloc(newmem)
```



**普通代码注入**

```assembly
[Enable]
alloc(newmem,2048)
label(returnhere)
label(originalcode)
label(exit)

newmem:
cmp [eax+58],0
jne originalcode  #不执行sub 直接接着sub之后的命令
ret
add [eax],al

originalcode:
sub [eax+50],edx  
ret 
add [eax],al

exit:
jmp returnhere

"gtutorial-i386.exe"+385A0:
jmp newmem
nop
returnhere:




[Disable]
dealloc(newmem)
"gtutorial-i386.exe"+385A0:
sub [eax+50],edx
ret 
add [eax],al
//Alt: db 29 50 50 C3 00 00

```





##### Level 3

- find collision（冲突） detect with enemies
- teleport（心灵传输）
- fly

查找X，Y坐标位置，然后浏览相关内存区域，死的时候看附近哪些值变换了，然后就锁定它们。让他们不变。

```c++
//查找坐标位置
-> = "points to"
0194209C = Value = ?
01889618 -> 01942080 + 1C = 0194209C
018F5BE4 -> 01889600 + 18 = 01889618
"gtutorial-i386.exe"+2D88C0 -> 018F5750 + 494 = 018F5BE4
```









---

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


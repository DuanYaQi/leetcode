

---

# Guided Hacking

https://guidedhacking.com/forums/the-game-hacking-bible-learn-how-to-hack-games.469/

https://guidedhacking.com/threads/game-hacking-fundamentals-the-game-hacking-book.16550/





- [x] https://guidedhacking.com/threads/getting-started-how-to-find-the-entity-list.10300/
- [x] https://guidedhacking.com/threads/how-to-solve-problems-achieve-goals.14359/
- [x] https://guidedhacking.com/threads/stop-pasting-focus-on-the-basics.14126/
- [ ] https://guidedhacking.com/threads/ghb1-start-here-beginner-guide-to-game-hacking.5911/

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





#### 1.1. Game Hacking Course Introduction



#### 1.2. Memory Editing 1



#### 1.3. Base Systems - Hex, Decimal & Binary



#### 1.4. How to Hex Edit Games



#### 1.5. Memory Editing 2 & Data Types



#### 1.6. Virtual Memory



#### 1.7. Virtual Memory 2 & Multilevel Pointers Tutorial



#### 1.8. How to Edit Assembly Tutorial







---







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


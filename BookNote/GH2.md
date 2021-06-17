# GH2 - Beginners Guide To Reverse Engineering

https://guidedhacking.com/threads/ghb2-beginners-guide-to-reverse-engineering.13446/



逆向工程就是获取 bits and bytes，并弄清楚它们代表什么，如何使用它们以及为什么。在逆向工程计算机代码的情况下，我们通常谈论从汇编代码中逆向函数，并创建代码目的的更高层次的图片。这篇文章代表了我们的主要逆向工程教程。

我们先从低的角度看，再从高的角度来看。

对于表示数据的字节 bytes，您可以对其数据类型、大小和用途进行逆向工程。它们是整数、浮点数、字符串还是位域 bitfield？它是健康价值还是名称？它是 2 字节还是 4 字节大小的整数？它是签名的还是未签名的？

对于表示代码的字节 bytes，它更复杂。您试图弄清楚它是什么指令，指令的长度是多少以及参数是什么。此外，很高兴知道代码在什么架构上运行， CPU 是什么以及架构是 x86、x64、ARM 的哪一个？它是大端还是小端（编码顺序，从左往右读，从右往左读）？另外我们使用的是什么平台，是 Windows、Linux、Android 等......？所有这些在低级别方面都很重要。

但对我们来说幸运的是，有一些工具可以为我们解决所有这些问题，并以一种易于理解的方式来表示它。您在游戏黑客方面进行逆向工程的主要工具将是作弊引擎。没错，您在 Cheat Engine 中所做的一切都是逆向工程，只是没有 1337 耀斑。调试器用于在运行时反转进程，反汇编器用于静态分析，它们获取位和字节并以我们更容易理解的方式表示它们。  







1. Read this thread below to learn about registers, assembly, calling conventions & the stack
2. [Tutorial - Manually Resolve Relative Addresses as Operands](https://guidedhacking.com/threads/manually-resolve-relative-addresses-as-operands.16912/)
3. [Guide - IDA Pro Beginner Guide](https://guidedhacking.com/threads/ida-pro-beginner-guide.8006/)
4. [Video Tutorial - How to Find CSGO NetVar Offsets Hacking Tutorial Ida Pro](https://guidedhacking.com/threads/how-to-find-csgo-netvar-offsets-hacking-tutorial-ida-pro.11026/)
5. [Video Tutorial - CSGO bDormant - How to find m_bDormant Offset Tutorial](https://guidedhacking.com/threads/csgo-bdormant-how-to-find-m_bdormant-offset-tutorial.11152/)
6. [Video Tutorial - ClassInformer Tutorial - Run Time Type Information Tutorial - RTTI](https://guidedhacking.com/threads/classinformer-tutorial-run-time-type-information-tutorial-rtti.14819/)
7. [Video Tutorial - Reverse Engineering Tutorial - Assault Cube Recoil](https://guidedhacking.com/threads/reverse-engineering-tutorial-assault-cube-recoil.11970/)
8. [Video Tutorial - Reversing Engineering Fly Hack NoClip Cheat Engine IDA pro C++](https://guidedhacking.com/threads/reversing-engineering-fly-hack-noclip-cheat-engine-ida-pro-c.11166/)
9. [Video Tutorial - Reverse Engineering - How To Find the CSGO Entity List](https://guidedhacking.com/threads/reverse-engineering-how-to-find-the-csgo-entity-list.13313/)
10. [Video Tutorial - How to Find TraceLine & Call Traceline with Inline ASM](https://guidedhacking.com/threads/how-to-find-traceline-call-traceline-with-inline-asm.6695/)

**Other GH Reverse Engineering Videos**

- [Video Tutorial - Practical Reverse Engineering Exercise Solutions](https://guidedhacking.com/threads/practical-reverse-engineering-exercise-solutions.15332/)







## Read this thread below to learn about registers, assembly, calling conventions & the stack

凭借您目前的知识，您可以：

```
查找变量和指针 Find variables & pointers
从外部读取和写入地址 Read & Write to addresses externally
在内部读取和写入地址 Read & Write to addresses internally
了解基本汇编 understand basic assembly
反向类 Reverse Classes
```

但是在制作了几个训练器之后，下一步是ESP 和 Aimbot！

这 2 个功能需要您学习如何挂钩和调用函数 how to hook and call functions。您将需要挂钩图形 API 以在游戏中绘制，并且您将需要调用 `TraceLine()` 函数来检测敌人是否可见。

老实说，你只需要知道大约 10 条指令就可以完成 50% 的游戏黑客攻击：

```assembly
mov、lea、cmp、test、push、pop、call、ret、jmp/jne/je、xor、add、sub
```

当然，你可以阅读一堆书籍和教程，您甚至可以学习如何在纯汇编中使用 `FASM/MASM/NASM` 制作可执行文件。但是，只要您理解了基本的 10 条指令，其余的就可以边走边想了。

很多人，包括我自己，刚学过汇编，如果你正在调试一个你不理解的指令，只需搜索。

以下是前 3 个最佳汇编参考内容：

汇编编程教程 - Tutorialspoint
指南 - 不耐烦的加速组装
教程 - 中级 MASM 教程（威震天批准）
x86 和 amd64 指令参考
Mirror of: Into the Void: x86 指令集参考
HJLebbink/asm-dude

如何更好地学习汇编？

实践！您可以做的第一件事是编写自己的简单 C/C++ 应用程序并将它们反转。

或者在任何简单游戏中选择任何功能，例如弹药减量功能的健康状况。在函数顶部放置一个断点。逐行检查每一行代码，用你认为它所做的来注释每一行代码。只需不断地跨过每一行并定义它们。当你到达最后一行时，你就会有一个完整的理解。我知道这听起来很疯狂，但这是一次了不起的学习经历。要有耐心，你会做得很好。

当您跨过每一行时，请务必查看寄存器和堆栈。

寄存器
大多数寄存器现在都是“通用”寄存器，但它们都曾经有特定的用途。

EAX = 用于算术的累加器寄存器，例如加法/减法等......
EBX = 用于索引的基址寄存器
ECX = 用于保持迭代次数的计数器寄存器
EDX = 与 EAX 结合使用以进行算术的数据寄存器

EIP = 指令指针，这指向正在执行的当前指令
ESP = 堆栈指针
EBP = 堆栈基指针

ESI = 用于字符串操作的源索引寄存器
EDI =用于字符串操作的目标索引寄存器

您经常会看到它们以与最初预期相同的容量使用，但事实并非如此需要，并且通过优化，编译器将使用任何最有效的寄存器。

但是这些 AX、AL、RCX 垃圾是什么？
这些是不同的寄存器。EAX、ECX、EDX 这些是易于理解的 32 位寄存器。但是很容易识别不同大小的寄存器表示。

以 RAX 为例：
RAX 是 EAX 的 64 位扩展版本
EAX是32位Ë AX的xtended版本
当寄存器是 16 位的时候，AX 是一个 16 位的寄存器
您仍然可以轻松地将十六进制的 64 位寄存器值分解为更小的组件。
RAX 是总共 64 位
EAX 是低 32 位
AX 是低 16 位
AH表示ħ IGH AX的8位
AL代表升流AX的8位
因此，如果您的 64 位寄存器包含：A0B1C2D3E4F5A6B7
EAX = E4F5A6B7
AX = A6B7
AH = A6
AL = B7
通过打开 Windows 计算器并将其设置为程序员模式、十六进制模式和 QWORD 值，您可以很容易地在视觉上识别这一点。粘贴“A0B1C2D3E4F5A6B7”，然后多次单击 QWORD 以将其类型逐渐变小以查看它在每个阶段的截断值。

有关寄存器的更多信息：
Assembly - Registers - Tutorialspoint

但是 Rake 堆栈是可怕的！
它肯定可以，所以让我们分解它。执行代码上下文中的内存有 4 个分类，堆栈、堆、代码和数据段，我有点喜欢称之为“静态初始化数据”。

代码 - 我在运行时初始化并且不会改变。像 csgo.exe 这样的模块包含一旦加载就是静态的代码。

数据段 -在运行开始时初始化的数据，但这些地址包含的值可以更改，但很多不会。

堆 -动态创建的对象/变量放置在这里。在 C++ 中使用“new”关键字在堆上分配东西，出于效率原因，这些东西在运行时不需要存在于磁盘或内存中。它们在需要时按需创建，不再使用时删除。

堆栈 -这是函数用于局部变量存储的内存位（相对较小）。

堆栈
堆栈是内存的一部分，它：
根据需要扩展和收缩
以“后进先出”的方式访问
表示函数的本地存储
存储函数参数
商店退货地址
用于将数据保存在寄存器中以备后用
堆栈实际上是堆栈帧的集合。每个函数都有自己的堆栈帧。如果函数 foo() 调用调用 snafu() 的 bar() 并且您正在调试 snafu()，则 foo 和 bar 的堆栈帧将保留在内存中，但您当前的堆栈帧当前由 ESP 和 EBP 寄存器定义。

ESP = Extended Stack Pointer EBP = Extended Base Pointer

当一个新函数被调用时，“函数序言”会执行，它会保留前一个堆栈帧，并为下一个函数设置堆栈帧。根据调用约定，它可以由调用者或被调用者完成，这意味着在“调用”指令执行之前或之后。

在“函数序言”或“堆栈设置”发生之前，ESP 指向当前堆栈帧的底部，当设置发生时，使 EBP 指向同一位置，然后 ESP 移动到新位置，即现在代表下一个堆栈帧的顶部。所以当一个函数序言完成时，ESP指向当前栈顶，EBP指向当前栈底。堆栈从 ESP 指向的地方开始，到 EBP 指向的地方结束。当您将东西推入和弹出堆栈时，ESP 指向的堆栈顶部移动。当你压入堆栈时，它会扩展，当你弹出时，它会收缩。

毫无意义的耙子！为什么堆栈底部的数字比顶部的数字大！？！？为什么以上帝的名义扩大地址范围？！

不要问我只看该死的视频


Daax
应用逆向工程的优秀文章：堆栈 - 逆向工程

所有的堆栈谈话让我的大脑爆炸。让我们转向更好的东西。

调用约定
stdcall、cdecl、thiscall 等……也许您听说过它们？这些定义了堆栈设置如何发生、参数如何传递给被调用者、堆栈如何展开以及函数如何返回。

调用者 = 执行调用指令
的函数被调用者 = 被调用者调用

的函数函数序言通常如下所示：
代码：
push ebp
mov  ebp, esp
sub   esp, n
其中 n = 函数用于本地存储的字节数。EBP 被压入堆栈，保留前一个堆栈的地址，然后使 EBP 指向 ESP。然后移动 ESP，以扩展堆栈帧，以便为新堆栈帧中的局部变量和参数留出足够的空间。

函数结语如下所示：
代码：
mov esp, ebp
pop ebp
ret
EBP 指向 ESP，然后旧的 EBP 从堆栈中弹出并返回 ESP，本质上将堆栈帧重置为调用当前函数之前的状态。

cdecl = 调用者展开堆栈

stdcall = 被调用者展开堆栈

thiscall = 本质上是一个 stdcall，其中被调用者清理堆栈，唯一的区别是 this 指针存储在 ECX 中。thiscall 用于成员函数。虚拟表函数使用此调用约定。

fastcall = 前 2 个参数在 ECX 和 edx 中传递，其余参数压入堆栈。堆栈只需通过一系列 pop 和 ret 来清理。

更多关于调用约定：
教程 - 调用约定，以及为什么您需要了解它们！
x86 调用约定 · destructure.io
调用约定揭秘
调用约定
参数传递和命名约定
内部调用约定
https://www.cs.cornell.edu/courses/cs412/2008sp/lectures/lec20.pdf
调用堆栈 - 维基百科
x86 反汇编/函数和堆栈框架 - 维基教科书，开放世界的开放书籍

所以现在在我们逆向工程教程的这一部分，您已经完成了：
从这里开始指南
Rake 的高级倒车视频教程（如下所列）
了解有关汇编、寄存器、调用约定和堆栈的更多信息
你的下一步是练习，花一周时间练习你所学的一切。开始反转整个函数，找出它们的调用约定、参数的数量、它们的类型和返回类型。深入了解堆栈，盯着调试器几个小时。

感觉有点失落？
你真的每节课都做了吗？你真的投入了足够的时间吗？回去巩固你的技能。

一次坐在调试器中 4 小时是游戏黑客的完全正常部分。

不过别担心，接下来的步骤很有趣，学习：
如何调用游戏功能
如何挂钩函数

调用游戏函数

下一组需要观看的视频来自@Traxin。对于指南的这一部分，我们将引导您查看我们的预制指南。您将在此处找到 Traxin 的视频，其中包含一些附加信息，包括一系列良好的链接：

指南 - 如何调用游戏函数的指南


如何挂钩函数

首先，刷新您对外部绕行的记忆：视频教程 - C++ 绕道 / 游戏挂钩函数教程Hacking

对于这部分，我们还没有教程或视频。但是要实现内部挂钩，您通常需要使用蹦床挂钩，这是基于 Solaire 代码的 x86 挂钩：
C++： 
bool Hook(char* src, char* dst, const intptr_t len)
{
    if (len < 5) return false;

    DWORD  curProtection;
    VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);
    
    intptr_t  relativeAddress = (intptr_t)(dst - (intptr_t)src) - 5;
    
    *src = (char)'\xE9'; //truncation of constant values // "\xE9"
    *(intptr_t *)((intptr_t)src + 1) = relativeAddress;
    
    VirtualProtect(src, len, curProtection, &curProtection);
    return true;
}

char* TrampHook(char* src, char* dst, const intptr_t len)
{
    // Make sure the length is greater than 5
    if (len < 5) return 0;

    // Create the gateway (len + 5 for the overwritten bytes + the jmp)
    void* gateway = VirtualAlloc(0, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    
    //Write the stolen bytes into the gateway
    memcpy(gateway, src, len);
    
    // Get the gateway to destination addy
    intptr_t  gatewayRelativeAddr = ((intptr_t)src - (intptr_t)gateway) - 5;
    
    // Add the jmp opcode to the end of the gateway
    *(char*)((intptr_t)gateway + len) = 0xE9; //truncation? 0xe9
    
    // Add the address to the jmp
    *(intptr_t *)((intptr_t)gateway + len + 1) = gatewayRelativeAddr;
    
    // Place the hook at the destination
    Hook(src, dst, len);
    
    return (char*)gateway;
}
这里有几个很好的
钩子来源：源代码 - OpenGL SwapBuffers 钩子模板源代码
源代码 - D3D11 Barebones 钩子 PoC
ELTraxo/dx9HookHelp


此时我已经研究了 3 天，所以本指南的其余部分只是关于我们下一个方向的一些说明。

下一步是什么？
所以现在你是一个中级逆向工程师，你可以调用游戏函数，你可以钩住它们。下一步是什么？

刷新你的 C++ 知识 - LearnCPP.com
- 有什么你不太明白的地方吗？确保您跟上速度。

在 Direct3D 中制作 ESP -
了解 World To Screen 和查看矩阵

制作瞄准
机器人 - 了解更多三角学

- 了解 PE 文件格式和 Windows 加载程序 -了解
Windows 内存保护和布局
-了解操作系统机制，特别是 Windows

其他资源和链接
The Workshop | RE 初学者
讨论 - 分享逆向工程视频
逆向工程和程序理解 | 进入逻辑之家
调试教程第 2 部分：堆栈
调试教程第 3 部分：堆
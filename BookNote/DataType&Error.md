# 数据类型

LP 代表 Long Pointer，长指针

C 代表 Constant，常量

VOID 代表 void

STR 代表字符数组、字符串

D 代表 `Double`

WND 代表 `Windows` 窗口过程

|    type     |                             mean                             |
| :---------: | :----------------------------------------------------------: |
| `uintptr_t` |                 无符号整数，取消地址的 `0x`                  |
|  `HANDLE`   | **句柄**，是 Windows 用来表示对象的（不是C++的对象）<br>在 windows 程序中，有各种各样的资源（窗口、图标、光标等），系统在创建这些资源时会为他们分配内存，并返回标示这些资源的标示号，即句柄 |
|  `SIZE_T`   | 标准 C 库中定义的，在64位系统中为 `long long unsigned int`，非64位系统中为 `long unsigned int`。 |
|             |                                                              |
|             |                                                              |
|   `BOOL`    | `int`，该**类型**与值为 true/false 的**C++类型 **`bool`不同。 |
|   `BSTR`    |               `unsigned short *`，32位字符指针               |
|   `BYTE`    |   等同于 `unsigned char a[3]`，**字节**数组，8位无符号整数   |
|   `DWORD`   | `unsigned long`，32位无符号整数，存放指针、段地址和相关的偏移地址。<br>每个 WORD 为 2 个字节的长度，DWORD 双字(double word)即为4个字节，每个字节是8位，共32位。 |
|   `LONG`    |                    `long`，32位带符号整数                    |
|  `LPARAM`   |       `long`，作为参数传递给窗口过程或回调函数的32位值       |
|   `LPSTR`   | `char *`，指向以 NULL(‘\0’) 结尾的 ANSI 字符数组（字符串）的 32 位**指针** |
|  `LPCSTR`   | `const char *`，指向以 NULL(‘\0’) 结尾的 ANSI 字符数组（字符串）常量的 32 位**指针** |
|  `LPWSTR`   | `char *`，指向以 NULL 结尾的可移植的Unicode和DBCS字符数组（字符串）的 32 位**指针** |
|  `LPCWSTR`  | `const char *`，指向以 NULL 结尾的可移植的Unicode和DBCS字符数组（字符串）常量的 32 位**指针** |
|  `LPVOID`   |      一个`void*` **指针**，指向未定义**类型**的32位指针      |
|  `LPCVOID`  |                  一个`void* const` **指针**                  |
|             |                                                              |
|   `PROC`    |                             函数                             |
|  `WNDPROC`  |                    指向窗口过程的32位指针                    |
|             |                                                              |



---

# Error

1. 无法将参数 2 从“const char [52]”转换为“LPCWSTR”

```
项目 > 属性 > 配置属性 > 高级 > 高级属性 > 字符集 > 改为未设置 
```



2. “无法启动程序，不是有效的Win32应用程序”

```
项目 > 属性 > 配置属性 > 高级 > 高级属性 > 目标文件扩展名 > exe
```

只有 `debug` 模式下，才能进入 `main.cpp` 以外的函数。
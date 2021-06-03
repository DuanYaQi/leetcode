# Error

1. 无法将参数 2 从“const char [52]”转换为“LPCWSTR”

```
项目 > 属性 > 配置属性 > 高级 > 高级属性 > 字符集 > 改为未设置 
```



2. 不能将 "const wchar_t *" 类型的值分配到 "LPCSTR" 类型的实体 / "const wchar_t *" 类型的实参与 "LPCSTR" 类型的形参不兼容

```
项目 > 属性 > 配置属性 > 高级 > 高级属性 > 字符集 > 改为使用Unicode字符集
```



3. “无法启动程序，不是有效的Win32应用程序”

```
项目 > 属性 > 配置属性 > 高级 > 高级属性 > 目标文件扩展名 > exe
```

只有 `debug` 模式下，才能进入 `main.cpp` 以外的函数。



4. use _CRT_SECURE_NO_WARNINGS

```
项目->属性->配置属性->C/C++ -> 预处理器 -> 预处理器定义，增加：
_CRT_SECURE_NO_DEPRECATE
```



5. MSVCRT.lib(exe_main.obj) : error LNK2001: 无法解析的外部符号 _main
   *.exe : fatal error LNK1120: 1 个无法解析的外部命令

```
项目 > 属性 > 配置属性 > 高级 > 高级属性 > 目标文件扩展名 > dll
```



6. error MSB8040: 此项目需要缓解了 Spectre 漏洞的库。

```
打开“Visual Studio Installer”

“使用 C++ 的桌面开发”工作负荷，查看PC安装的MSVC的版本，“MSVC v142 - VS 2019 C++ x64/x86 生成工具(V14.27)”（请注意，其中的 14.27就是可用的最高版本）。

选择“单个组件”，然后搜索“14.27”。 这会返回所有体系结构的工具集，包括 Spectre 缓解库。 选择要为其开发的驱动程序体系结构。

选中Spectre缓解库，点击“修改”，完成安装。
```



7. 字符常量中的字符过多

```
'client.dll'
换成
"client.dll"
```



8. Device driver does not install on any devices, use primitive driver if this is intended.

```
用 Kernel Mode Driver, Empty(KMDF)
源文件为.c 
而不是.cpp
```





---

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


# **1**. Basics of C++

## Windows install

use code::blocks

binary release/windows 10/codeblocks-16.01mingw-setup.exe



## Mac install

open terminal

```shell
gcc -v
```



## Setup & hello world 

create a new project

console application

choose language c++

project title

```c++
#include <iostream>

int main() {
    std::cout << "Hello world!" << std::endl;
    return 0;
}
```



build/run/build and run



## Drawing the picture

```c++
#include <iostream>

int main() {
    std::cout << "   /|" << std::endl;
    std::cout << "  / |" << std::endl;
    std::cout << " /  |" << std::endl;
    std::cout << "/   |" << std::endl;
    return 0;
}
```



## Variables

```c++
#include <iostream>
#include <string>

int main() {
    string characterName = "John";
    int characterAge;
    characterAge = 32;
    std::cout << "His name is " << characterName << std::endl;
    std::cout << "He was " << characterAge << " years old" << std::endl;
    return 0;
}
```



## Data Types

```c++
#include <iostream>

int main() {
    char grade = 'A';
    string s = "AAABBBCCC";
   
    int score = 100;
    float pi = 3.14;
    double gpa = 4.5;
    bool isMale = true;
    
    return 0;
}
```



## Working with Strings

```c++
#include <iostream>
#include <string>

int main() {
    std::cout << "AAABBBCCC\n"; // \n new line
    string s = "AAABBBCCC";
    std::cout << s.length(); 	// 9
    std::cout << s.[0];			// A
	std::cout << s.[3];			// B
    std::cout << s.find("CCC", 0);	// 6
    std::cout << s.substr(4, 3);	// BBC
    return 0;
}
```



## Working with numbers

```c++
#include <iostream>
#include <cmath>

int main() {
    std::cout << 10 % 3; 		// 1
    std::cout << 10 / 3; 		// 3 int
    std::cout << 10.0 / 3.0; 	// 3.33333 double
    
    std::cout << pow(3, 2);     // 9
    std::cout << sqrt(25);      // 5
    
    std::cout << round(3.5);    // 4
    std::cout << ceil(4.1);     // 5
    std::cout << floor(4.1);    // 4
    
    std::cout << fmax(3, 10);   // 10
    std::cout << fmin(3, 10);   // 3
    
    
    return 0;
}
```



## get intput

```c++
#include <iostream>

int main() {
    int age;
    std::cout << "enter you age: ";
    std::cin >> age;
    
    std::cout << "your are " << age << " years old";
    
    return 0;
}
```



```c++
#include <iostream>
#include <string>

int main() {
    string name;
    std::cout << "enter you name: ";
    std::cin >> name;
    // or
    std::getline(std::cin, name);
    std::cout << "your name is " << name << std::endl;
    
    return 0;
}
```



## Building a calculator

```c++
#include <iostream>
#include <string>

int main() {
    double a, b, c;
    std::cout << "Please input your num1";
    std::cin >> a;
    std::cout << "Please input your num2";
    std::cin >> b;
    
    char ope;
    std::cout << "Please input your operator";
    std::cin >> b;
    
    if (ope == '+') {
        c = a + b;
    } else if (ope == '-') {
        c = a - b;
    } else if (ope == '*') {
        c = a * b; 
    } else if (ope == '/') {
        c = a / b; 
    } else {
        std::cout << "erro operator" << std::endl;
        return 0;
    }
    
    std::cout << "the answer is " << c << std::endl;
    
    return 0;
}
```



---

## Mad Libs

```c++
#include <iostream>
#include <cmath>

int main() {
    string color, pluralNoun, celebrity;
    
    std::cout << "enter a color: ";
    std::getline(std::cin, color);
    std::cout << "enter a pluralNoun: ";
    std::getline(std::cin, pluralNoun);
    std::cout << "enter a celebrity: ";
    std::getline(std::cin, celebrity);
    
    std::cout << "Roses are" << color << std::endl;
    std::cout << pluralNoun << " are blue" << std::endl;
    std::cout << "I love "<< celebrity << std::endl;
    
    return 0;
}
```



## Arrays

```c++
#include <iostream>
#include <cmath>

int main() {
    int luckyNums[] = {4, 8, 15, 16, 23, 42};
    std::cout << luckyNums[0]; 		// output 4
    std::cout << luckyNums[2]; 		// output 15
    
    int cluckyNums[20] = {4, 8, 15, 16, 23, 42};
    std::cout << cluckyNums[10]; 	// output 0
    
    int cluckyNums[20];
    std::cout << cluckyNums[0]; 	// output 0
    
    return 0;
}
```



## Functions

```c++
#include <iostream>

void sayHello() {
	cout << "Hello User";    
}

int add(x, y) {
    return x + y;
}

int main() {
    sayHello();
    int c;
    c = add(2, 5);
    std::cout << c; //output 7
    return 0;
}
```



## Pointers

```c++
#include <iostream>
#include <string>

int main() {
    int age = 19;
    double gpa = 2.7;
    string name = "Mike";
    
    std::cout << "Age address: " << &age << std::endl; // 0x6afee8
    std::cout << "gpa address: " << &gpa << std::endl; // 0x6afee0   
    std::cout << "name address: " << &name << std::endl;// 0x6afedc
    
    int *p2age = &age;
    double *p2gpa = &gpa;
    string *p2name = &name;
    
    std::cout << "Age address: " << p2age  << std::endl; // 0x6afee8
    std::cout << "gpa address: " << p2gpa << std::endl; // 0x6afee0   
    std::cout << "name address: " << p2name << std::endl;// 0x6afedc
    
    return 0;
}
```



## classer & objects

```c++
#include <iostream> 
#include <string>

class Book {
    public: 
    	string title;
    	string author;
    	int pages;   	
};

    
int main() {
    Book book1;
    book1.title = "Harry Potter";
    book1.author = "JK Rowling";
    book1.pages = 500;
    
    Book book2;
    book2.title = "Lord of the Rings";
    book2.author = "Tolkein";
    book2.pages = 700;
    
    std::cout << book1.title << book2.title << std::endl;// 0x6afedc
    
    return 0;
}
```



![img](assets/cdbf6c81800a19d865fd770a3efa828ba71e46c7.jpg)

```c++
// public ???????????????????????????????????????????????????
// private ???????????????????????????
// protected ?????????????????????????????????????????????
```



## Constructor Functions

?????????????????????

```c++
#include <iostream> 
#include <string>

class Book {
    public: 
    	string title;
    	string author;
    	int pages;
    	Book() {
    		title = "no Title";
            author = "no Author";
            pages = 0;  
        }
    
    	Book(string aTitle, string aAuthor, int aPages){
        	title = aTitle;
            author = aAuthor;
            pages = aPages;
        }
};

    
int main() {
    Book book1("Harry Potter", "JK Rowling", 500);
    Book book2("Lord of the Rings", "Tolkein", 700);
    Book book3;
    book2.pages = 800;
    
    std::cout << book3.title << book2.pages << std::endl;// 0x6afedc
    
    return 0;
}
```



## Object Functions

```c++
#include <iostream>

class Student {
    public:
    	string name;
    	string major;
    	double gpa;
    	Student(string aName, string aMajor, double aGpa) {
            name = aName;
            major = aMajor;
            gpa = aGpa;
        }
    
    	bool hasHonors() {
            return gpa >= 3.5 ? true : false;
        }
};

int main() {
    Student s1("Jim", "Business", 2.4);
    Student s2("Pam", "Art", 3.6);
    std::cout << s1.hasHonors();
    
    return 0;
}
```



## Getters & Setters

```c++
#include <iostream>

class Movie {
    public:
    	string title;
    	string director;
    	Movie(string aTitle, string aDirector, string aRating) {
            title = aTitle;
            director = aDirector;
            rating = aRating;
        }
    
    private:
    	string rating;
};

int main() {
    Movie avengers("The Avengers", "Joss Whedon", "PG-13");
    
    std::cout << avengers.rating; //error!!! you cant read private member
	return 0;
}
```



```c++
#include <iostream>

class Movie {
    public:
    	string title;
    	string director;
    	Movie(string aTitle, string aDirector, string aRating) {
            title = aTitle;
            director = aDirector;
            setRating(aRating);
        }
    	
    	void setRating(string aRating) {
            rating = aRating;
        }
    
    private:
    	string rating;
};

int main() {
    Movie avengers("The Avengers", "Joss Whedon", "PG-13");
    avengers.rating = "Dog";    //error!!! you cant access private member
    avengers.setRating("PG-13");//success!!! setRating is public function
    return 0;
}
```



```c++
#include <iostream>

class Movie {
    public:
    	string title;
    	string director;
    	Movie(string aTitle, string aDirector, string aRating) {
            title = aTitle;
            director = aDirector;
            setRating(aRating);
        }
    	
    	void setRating(string aRating) {
            if (aRating == "G" || aRating == "PG" || aRating == "PG-13"){
                rating = aRating;
            } else {
                rating = "NR";
            }
        }
    	
    	string getRating(){
            return rating;
        }
    
    private:
    	string rating;
};

int main() {
    Movie avengers("The Avengers", "Joss Whedon", "PG-13");
    avengers.setRating("PG-132");//PG-132 is the illegal; write as NR
    std::cout << avengers.getRating(); // output NR
    return 0;
}
```



## Inheritance

??????

```c++
#include <iostream>

//super class
class Chef {
    public:
    	void makeChicken() {
            std::cout << "The chef makes chicken" << std::endl;
        }
    
    	void makeSalad() {
            std::cout << "The chef makes salad" << std::endl;
        }
    
    	void makeSpecialDish() {
            std::cout << "The chef makes SpecialDish" << std::endl;
        }
};

//sub class
class ItalianChef : public Chef{ // ???????????? Chef 
    public:
        void makePasta(){
            std::cout << "The italianchef makes pasta" << std::endl;
        }
    
    	void makeSpecialDish() { //??????????????????
            std::cout << "The chef makes new SpecialDish" << std::endl;
        }
};

int main() {
    Chef chef;
    chef.makeChicken();
    //chef.makePasta();	//error
    
    ItalianChef ichef;
    ichef.makeSalad();
    ichef.makePasta();	//success
    ichef.makeSpecialDish();
    return 0;
}
```





------

# 2. Modern C++

https://www.youtube.com/watch?v=18c3MTX0PK0&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb



## Welcome

fast code that performs well

C++ is the directly control over hardware.



---

## How to Setup C++ on Windows





---



# 3. Graphics Programming



# 4. Game Engines



# 5. Math Fundamentals





# 6. CS420

## Squally

SPACE - ATTACK



```assembly
#??????????????????
nop

add edi, 256 #???
sub edi, 256 #???

mov ebx, eax #eax????????????ebx


inc edi #??????
dec edi #??????
```



```assembly
#?????????????????????
imul ecx, 1
iadd
isub

#???eax???????????????ecx???????????????????????????eax??????????????????0????????????????????????
mov ecx, 3 # ???????????? 3
idiv ecx   # eax = eax / ecx = eax / 3
```



```assembly

# ???f????????????????????????????????????????????????????????????FPU???????????????????????? ?????????????????????????????????
fadd dword ptr [ebx]
fsub
fdiv
fmul
```



```assembly
#xmm* ??????????????????????????????
#???xmm* ?????????????????????????????????SSE??????
#?????????FPU???????????????????????????

addss #?????????????????????
subss #?????????????????????
```





higher score win!

??????????????????????????????????????????????????????

??????????????????????????????????????????

??????????????????\??????????????????\?????????????????????



??????????????????????????????????????????????????????????????????????????????????????????

?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????

MOV????????? ?????????????????????????????????

ADD????????? ????????????????????????????????????





mov ???hex????????????0

??????????????????????????????????????????????????????????????????????????????2?????????????????????15??????

8 * 2 = 0

9 * 2 = 2



## 6.1. Game Hacking Course Introduction

Squally - A game designed to teach game hacking and x86/x64 assembly



skills you will learn



- Memory editing: edit health, gold, etc. in a running game
- Assembly editing: rewrite the game's code to do what you want it to do.
- Hex editing: edit save-files, and other on-disk resources
- Packet editing: send modified information to servers to cheat in online games
- Botting: write programs to play the game for you



Specialized Topics

- Graphics Injection
- Resource Editing
- Browser game hacking(editing JavaScript, Flash Decompiling)
- JVM/CLR Game Hacking
- Emulated Games
- Anti-cheat systems
- Memory editor implementation

![image-20210508203551692](assets/image-20210508203551692.png)



hack processing:

find thing to exploit or hack > try exploit or hack > see if it worked



---

## 6.2. Memory Editing 1

Operating Systems Basics + Memory Scanning



hardware management

process management (running exe files)



OS take that file(exe) and copies it into RAM 

software crack you generally hack the version on disk rather than the version in RAM.

this is because  software crack need to make a paid program free by removing serial key checks and that sort of thing and game hacking you want to be able to play the game normally when you want to 

so game hacking only hack the version in RAM



memory scanning > memory editing > see if it worked



**TOOLS** 

Cheat Engine

Squalr



**Windows API**

`WriteProcessMemory` function



**Memory Editing**

8 bits = 1 byte

char = 1 byte

int = 4 byte = 4 * 8 bits



bin/bit ??????

![image-20210509123226351](assets/image-20210509123226351.png)



**Memory Scanning**

Ctrl + F ????????????

![image-20210509192924260](assets/image-20210509192924260.png)

??? 0 ?????????????????? 8 ??? bit ??????????????????????????? byte ?????????



### **Examples**

squally.exe change the health

exact value > 4 bytes(int32) > new scan > change health > next scan

find the address > change value > if is not changed > do some thing to refresh the screen





---

## 6.3. Base Systems - Hex, Decimal & Binary

Decimal (Dec)                     10                         4294967295

Hexadecimal (Hex) 0x10  10 => 16               F       F        F        F        F        F        F        F

Binary (Bin)              0b10  10 => 2                1111 1111 1111 1111 1111 1111 1111 1111



4211081215

F        A       F        F        F        F        F        F

1111 1010 1111 1111 1111 1111 1111 1111



---

**Hex**

0 1 2 3 4 5 6 7 8 9

a b c d e f



**Hexadecimal**

0 1 2 3 4 5 6 7 8 9

99999 + 1 = 100000



**Binary**

0 1

01111 + 1 = 10000



![image-20210509203327595](assets/image-20210509203327595.png)

0001 1

0010 2

0100 4

1000 8



hex ??????

![image-20210509204157713](assets/image-20210509204157713.png)



https://flippybitandtheattackofthehexadecimalsfrombase16.com/



---

## 6.4. Hex Edit

find info in save file that you want to hack > hex edit the file > boot up the game and see if it worked

remember backup the file first



**Save file editing**

**Resource editing**

**Raw Memory editing**

**Packet editing**



- just google it
- API monitoring (intercept calls to the OS to see what files the game is using)

![image-20210509204807151](assets/image-20210509204807151.png)

### Examples

????????????????????? https://docs.microsoft.com/zh-cn/sysinternals/

include process from window  > then click on the process > exclude 'ReadFile' > do some change in game > see 'WriteFile' & 'CreateFile'

??? `.sqa` ???????????? `HxD Freeware Hex Editor and Disk Editor`

?????? `text-string`  ?????? `gold` ????????????????????? byte ????????????????????????????????????????????????????????? byte?????? int32 ????????? value ?????????????????????



????????????????????????

little endian??? E7 03 00 00???999 in DEC??????????????? ???Intel AMD64?????????

big endian???   00 00 03 E7???999 in DEC???????????????



?????????????????? `integer number` ?????? `679` ??????????????????gold????????????????????????**?????????????????????????????????????????????**

????????????????????????????????????????????????????????????????????????????????????????????????????????????????????? compare ???????????????

?????????????????????????????????????????????????????????????????????integrity check ???????????? / encrypted files ???????????????

![image-20210509210239169](assets/image-20210509210239169.png)

73???HEX??? - 's'???ASCII???- 115???DEC???

71 - 'q'

75 - 'u'

61 - 'a'

6c - 'l'

6c - 'l'

79 - 'y'

30 - '0'

00 - NULL

????????? 00 ?????????????????????????????????????????????????????????????????????????????????????????????????????????



www.ascii-code.com

 

![image-20210509210543901](assets/image-20210509210543901.png)



![image-20210509210701324](assets/image-20210509210701324.png)





---

## 6.5. Memory Editing & Data Types

![image-20210509213532015](assets/image-20210509213532015.png)

boolean ?????????????????????8??????

0000 0001 true

0000 0000 false



hex

![image-20210509213347957](assets/image-20210509213347957.png)



???????????????????????? ?????????????????????????????????

![image-20210509213442115](assets/image-20210509213442115.png)



?????????/?????????

![image-20210509213503259](assets/image-20210509213503259.png)



**Float**

![image-20210509213807983](assets/image-20210509213807983.png)

**Double**

like floats, but use 8 bytes instead of 4 bytes

more precise than floats

10.5 ?????????double

10.5f  ??? float 



![image-20210509214031024](assets/image-20210509214031024.png)



HEX

![image-20210509214124951](assets/image-20210509214124951.png)



### unknown values scanning

????????????/???????????????????????? (??????????????????????????????)

?????????????????????

?????????????????????

unknown initial value(float) -> increased value -> decreased value

????????????????????????????????????ce?????????????????????????????????????????????????????? 	

?????????????????? x ????????????????????????????????????????????? +4??????**????????????**????????? y ?????????x??????float?????????float????????? 4 ?????????

![image-20210509215130218](assets/image-20210509215130218.png)

???????????????????????????



---

## 6.6. Virtual Memory

![image-20210509223620809](assets/image-20210509223620809.png)



exe ???????????????????????????????????????????????????????????????

![image-20210509223637749](assets/image-20210509223637749.png)



???????????????????????????????????????exe ???????????????????????? 2G

![image-20210509224146257](assets/image-20210509224146257.png)



????????????????????? ??????exe???????????????

![image-20210509224242573](assets/image-20210509224242573.png)





![image-20210509224716945](assets/image-20210509224716945.png)



![image-20210509224752233](assets/image-20210509224752233.png)





![image-20210509224817334](assets/image-20210509224817334.png)



??????????????? flatten ??? VM ????????????

![image-20210509224836774](assets/image-20210509224836774.png)

?????????????????????????????????????????????????????????????????????????????? free memory

?????????????????????????????????????????????????????????????????????????????????free memory??????????????????????????????	

![image-20210509225055364](assets/image-20210509225055364.png)

??????????????????????????????????????????exe???????????????????????????

???????????????????????????????????????????????????squally.exe?????????????????????user interface???????????????????????????????????? class player??????

![image-20210509225724287](assets/image-20210509225724287.png)

????????????????????????????????????????????????????????????????????????????????????????????????

![image-20210509225651284](assets/image-20210509225651284.png)



---

## 6.7. Multilevel Pointers

????????????

????????? user interface ?????? player ??????????????????????????????????????????

![image-20210509230202386](assets/image-20210509230202386.png)



![image-20210509230600347](assets/image-20210509230600347.png)

???????????????????????????????????????????????????

![image-20210509230545693](assets/image-20210509230545693.png)



### **Memory Leak**

???????????????????????????????????????????????????????????????????????????????????????????????????????????????

![image-20210509230837638](assets/image-20210509230837638.png)

??????????????????????????????RAM?????????????????????

![image-20210509230941354](assets/image-20210509230941354.png)



### pointer chain

????????? exe ??? gold ?????????

![image-20210509231104813](assets/image-20210509231104813.png)

> ?????? player health, player x, player y ????????????????????????????????????????????? exe ??????
>
> C???HEX??? ?????? 12???DEC??? 
>
> 32????????? 4?????? 
>
> 64????????? 8??????



![image-20210509231355398](assets/image-20210509231355398.png)

?????? `Squally.exe` ??????????????????????????????????????? `Squally.exe + 4` ???????????? `Player X`

![image-20210509231655751](assets/image-20210509231655751.png)



main tree

![image-20210509232113904](assets/image-20210509232113904.png)

other trees that start from dlls (dynamically linked libraries)	

the main tree starts from the exe but the exe can load up a dll which can then create its own objects the same way in exe can, and dlls can also static

![image-20210509232550171](assets/image-20210509232550171.png)

????????????????????? dll ????????????????????? exe ?????????

![image-20210509232646618](assets/image-20210509232646618.png)



pointer scan > rescan pointerlist > double click on all of them > restart the game > check the value

short path are often more reliable 



pointer depth

tweaking the parameters



---

## 6.8. How to Edit Assembly Tutorial

??????

find relevant assembly code > change it > see if it worked





![image-20210510111151813](assets/image-20210510111151813.png)



bytes can be grouped into instructions

?????????????????? HEX ??????

![image-20210510111224798](assets/image-20210510111224798.png)

nop > no operation



C7 40 ???????????? machine language?????????????????????????????????????????????????????????



![image-20210510111520071](assets/image-20210510111520071.png)



?????????

![image-20210510112042405](assets/image-20210510112042405.png)

```c++
int health = 500;
//mov DWORD PTR [rbp-4], 500
```



![image-20210510112359953](assets/image-20210510112359953.png)

C#?????? ???????????????Unity Engine???????????????????????????????????????????????????



![image-20210510112501383](assets/image-20210510112501383.png)

JVM????????????????????????????????????????????????



![image-20210510112510991](assets/image-20210510112510991.png)

emulator ????????? ???dolphin??? ???????????????????????????????????????????????????



![image-20210510112723615](assets/image-20210510112723615.png)

??????????????????



![image-20210510113043977](assets/image-20210510113043977.png)

??????????????????



![image-20210510113056011](assets/image-20210510113056011.png)

PVM



![image-20210510113202356](assets/image-20210510113202356.png)

?????????????????????

C++???????????????????????????exe???dlls???

JIT???Just In Time??? compile language ???????????????????????? (heap is any of these allocated non-static objects ??????????????????????????????????????????????????????)

scripting language ?????????????????????



?????????????????? hack ????????? C++/C ????????????????????????

???????????????C++????????????????????????????????????????????????

?????????????????? `Mono/`????????????`Assembly-CSharp.dll`???`Mono-Security.dll`???`UnityEngine.dll`,??????????????? C# ???????????????

????????? `UE3ShaderCompileWorker.exe` ??????????????? `UE` ???????????????C++ ??????????????????????????????????????????

?????????????????????????????????exe???dll???????????????????????? C++ ??????????????????



### **Examples**

??????????????????????????? > ?????? `Find out what access this address`  > ???????????????????????? > ???????????? >  `Add to the codelist` > Stop and Close last window > ?????? `Open the disassembler at this location`  > `Replace with code that does nothing` > `Restore with original code`



we need that code to run on the cpu

but cpu has **small storage** so we can't just copy all the games code over

so code keeps **streaming** (from RAM  into the cpu line by line

sometimes code needs to accsee data, but **accessing ram from the cpu is expensive**, so they put a very small amount of storage on the cpu called **registers**

![image-20210510123220522](assets/image-20210510123220522.png)





![image-20210510123336162](assets/image-20210510123336162.png)



![image-20210510123420143](assets/image-20210510123420143.png)



![image-20210510123434914](assets/image-20210510123434914.png)

RAM to get data and code into the cpu, it passed through a series of hardware caches 

for example code end up in L1 Cache(Code) and data streams through to L1 Cache (Data) and some of that ends up in registers.



![image-20210510123748216](assets/image-20210510123748216.png)

scientists hide all of these caches from us so as far as a game hacker is concerned there is only **RAM and registers**

if we want to change something, we need to load it into a register first.



### Register

1.??????????????????

AX???BX???CX???DX4???16????????????

AX(AH???AL)???**??????**???????????????????????????AX(???AL)??????????????????????????? 
BX(BH???BL)???**????????????**??????BX?????????**????????????**??????????????????????????????????????????
CX(CH???CL)???**??????**????????????CX???**????????????????????????????????????**??????????????????CX?????????????????????
DX(DH???DL)???**??????**?????????????????????????????????????????????I/O?????????????????????????????????????????????????????????????????????????????????

2.????????????????????????
BP( Base Pointer regilter)??????????????????????????? 
SP( Stack Pointer Register)???????????????????????????
SI( Source Index register)????????????????????????
DI( Destination Index Register)???????????????????????????

3.????????????CS

4.?????????????????????IP

5.???????????????FR

![image-20210510123937180](assets/image-20210510123937180.png)

????????????????????????????????????????????????32-bits??????4???bytes  00 00 00 64???



![image-20210510124133740](assets/image-20210510124133740.png)

????????????????????????????????????????????????64-bits??????8???bytes  00 00 00 00     00 00 00 64???



![image-20210510124154553](assets/image-20210510124154553.png)



![image-20210510124227731](assets/image-20210510124227731.png)



![image-20210510124322519](assets/image-20210510124322519.png)

???????????????????????????????????????

a good rule of thumb(?????????????????????????????????????????? ??????????????????????????????) when you're starting out is never mess with a register that ends with 'p'

????????????????????????**????????????????????????**???????????????????????????p?????????????????????

RIP/EIP ???????????????????????????**????????????CPU????????????????????????**

disrupt the flow of that program / maybe crash

???????????????????????????R9-R15???????????????????????????



### Instruction

**INC/DEC**

![image-20210510125013644](assets/image-20210510125013644.png)

```assembly
# ??????
inc ecx       # 5
inc [eax]     # 11
inc [edi] + 8 # 501

# ??????
dec ecx       # 3
dec [eax]     # 9
dec [edi] + 4 # 109
```



**ADD/SUB**

![image-20210510125229205](assets/image-20210510125229205.png)

```assembly
# ??????
add eax, 2         	# eax = 4
add ecx, edx 		# ecx = 15
add [ebx], 10		# [ebx] = 20
add [ebp], edi		# [ebp] = 2
add [ebp + 4], 4	# [ebp + 4] = 4
add [ebp + 8], esi	# [ebp + 8] = 3
```



![image-20210510125533947](assets/image-20210510125533947.png)

```assembly
# ??????
add ebx, 2         	# ebx = 1020
add ecx, edx 		# ecx = 4998
add [eax], 10		# [ebx] = 990
add [esp], edi		# [ebp] = 196
add [esp + 4], 100	# [ebp + 4] = 8900
add [esp + 8], esi	# [ebp + 8] = 794
```



**MOV**

![image-20210510125656391](assets/image-20210510125656391.png)

```assembly
# move ????????????
mov ebx, 200    		# ebx = 200
mov ecx, edx			# ecx = 777
mov [eax], 10			# [eax] = 10
mov [esp], edi			# [esp] = 128
mov [esp + 4], 100		# [esp + 4] = 200
mov [esp + 8], esi      # [esp + 8] = 1234
```



**NEG**

![image-20210510130003722](assets/image-20210510130003722.png)

```assembly
# ??????
neg ecx			# ecx = -100
neg [ebx] 		# [ebx] = -10
neg [esi + 12] 	# [esi + 12] = -500
```



**MUL**

![image-20210510130118212](assets/image-20210510130118212.png)

```assembly
# ??????
mul ebx, 2				# ebx = 4
mul ecx, edx			# ecx = 8000
mul [eax], 10			# [eax] = 1000
mul [esp], edi			# [esp] = 40
mul [esp + 4], 100		# [esp + 4] = 1000
mul [esp + 8], esi		# [esp + 8] = 60 
```



**DIV**

![image-20210510130316317](assets/image-20210510130316317.png)

```assembly
# ?????? ?????????????????????eax???????????? ??????????????????
div ecx			# eax = 120 / 12 = 10       ecx = 12
div ecx			# eax = 10 / 12 = 0         ??????edx = 10 
div esi			# 
div [ebx]
div [esp + 4]
div [esp + 8]
```

?????????????????? `DIV` ??????



**PUSH**

moves a number to the **top of the stack**

![image-20210510182820283](assets/image-20210510182820283.png)

???          

![image-20210510182845933](assets/image-20210510182845933.png)

```assembly
push ecx
```

![image-20210510182948982](assets/image-20210510182948982.png)

```assembly
push [ebx]
```

![image-20210510183004764](assets/image-20210510183004764.png)



```assembly
push [esi + 12]
```

![image-20210510183037902](assets/image-20210510183037902.png)



**POP**

removes a number from the top of the stack, **and** **stores** it in the given destination

![image-20210510183244343](assets/image-20210510183244343.png)

![image-20210510183258063](assets/image-20210510183258063.png)

```assembly
pop ecx # ecx = 1
```

![image-20210510183314176](assets/image-20210510183314176.png)

```assembly
pop [ebx] # [ebx] = 92     10 > 92
```



```assembly
pop [esi + 12]  # [esi + 12] = 65536   500 > 65536
```



**SHL**    ????????????

**SHR**	????????????

**NOT**	??????????????????0 > 1, 1 > 0

**AND**	??????AND??????

**OR**	   ??????OR??????

**XOR**     ??????XOR??????

**BSWAP** ??????32????????????????????????



### **Examples**

??????????????????????????? > ?????? `Find out what write this address`  > ???????????????????????? > ???????????? >  `Add to the codelist` > Stop and Close last window > ?????? `Open the disassembler at this location`  > ??????????????????????????????????????????????????????????????????

Tools > auto assemble (Ctrl + A) > ?????? `[Enable]  [Disable]` > Template > Code Infection (Ctrl + I) > 'ok' > 

?????? `//this is allocated memory, you have read,write,execute access //place your code hereoriginalcode:`  ??? `label(originalcode)` > `newmem:` ???????????????????????????`add []`  > file > ??????????????? CT ???

**?????????????????????pointer???????????????????????????pointer?????????**

![image-20210510175443795](assets/image-20210510175443795.png)



![image-20210510175547070](assets/image-20210510175547070.png)






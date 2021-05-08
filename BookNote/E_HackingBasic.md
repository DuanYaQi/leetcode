# 1. Basics of C++

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
// public 所有类、函数都可以访问，完全公开；
// private 只能是类自己访问；
// protected 类自己和他的派生类都可以访问。
```



## Constructor Functions

构造函数，重载

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

继承

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
class ItalianChef : public Chef{ // 继承父类 Chef 
    public:
        void makePasta(){
            std::cout << "The italianchef makes pasta" << std::endl;
        }
    
    	void makeSpecialDish() { //重载父类函数
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



**TOOLS** 

Cheat Engine

Squalr



**Windows API**

`WriteProcessMemory` function



memory editing processing:

memory scanning > memory editing > see if it worked



8 bits = 1 byte

char = 1 byte

int = 4 byte 
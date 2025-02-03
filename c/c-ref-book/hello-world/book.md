A C program is composed of one or more source files, or translation units, each of which contains some part of the entire C program.
> Typically some number of external functions.
Common declarations are often collected into header files and are included into the source files with a special **#include** command. One external function must be named **main**; this function is where your program starts.

A C compiler independently processes each source file and translates the C program text into instructions understood by the computer.
> If the programmer has made an error the compiler can detect, then the compiler issues an message error.
> The output of the compiler is usually called object code or an object module.

When all source files are compiled, the object modules are given to a program called linker. The Linker resolves references between the modules, adds functions from the standard run-time library, and detects some programming errors such as failure to define a needed function.
> The linker is typically not specific to C; each computer system has a standard linker that is used for programs written in many different languages.
> The linker produces a single executable program, which can then be invoked or run.

Example:

Suppose that we have a program to be named "hello" consisting of the two C source files "hello.c" and "main.c". The file "hello.c" might contain these lines:

```
    #include <stdio.h> /* defines the library that contain the printf function */
        void hello(){
            printf("Hello!\n");
    }
```
Since "hello.c" contains facilities (the function **hello**) that will be used by other parts of our program, now we create a header file "hello.h" to declare those facilities. 
It contains the line:
```
    extern void hello();
```
File "main.c" contains the main program, which simply calls function hello;

```
    #include "hello.h"
    int main(){
        hello();
        return 0;
    }
```
On a UNIX system, compiling linking, and executing takes only these two steps:

```
$ gcc -o hello *.c
$ ./hello
```
The first line compiles the source files, adds any standard library functions needed, and writes the executable program to file "hello". The second line then executes the program, and output the result of the **printf** function which print:
```
$ Hello!
```
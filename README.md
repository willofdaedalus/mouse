![plot](./assets/banner.png)

## Authors
[Manny Quansah](https://www.linkedin.com/in/IamDaedalus)

## Mouse-83 Interpreter
Mouse is a small programming language developed by Dr Peter Grogono in the late
70s and early 80s as an extension of an earlier language called MUSYS which was
used to control digital and analogue devices in an electronic studio.  

It was intended to be an efficient and small language for microcomputers which
had limited memory and as such was interpreted. It use a Stack-based system and
[Reverse Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation) to make mathematical calculations.  

Dr Peter designed the interpreter in a way to make as easy as possible to implement
by using symbols that act as operators for various operations. The interpreter
processes a source file as a stream of characters and interprets one character at
a time.  

Each element of a Mouse program, which consists of single character symbols, maps
to a specific function predefined in the interpreter. There are only 26 in built
variables (A - Z) since there's a rule of single character symbols as operators.
Despite the limitations Mouse is complete with conditional statements, loops,
arrays, pointers and more.


## Installation
To install the Mouse interpreter, you need the following installed on your system;  
* gcc
* git

Consult your local package manager on instructions to install them. Once you have
them installed run the following commands in your terminal of choice.

``
git clone https://github.com/IamDaedalus/mouse
cd mouse
gcc -Wall -pedantic -Werror -Wextra -std=gnu99 src/*.c -o
``

This will compile and generate a binary that is ready to use.
To use Mouse on any of the sample code, you can run the binary and the path of the
source file you want to run. For instance to run the source file ``samples/age_calc.mou``,
you need to run the following command:

``./mouse samples/age_calc.mou``


## Operators in Mouse
| Operator | Function                                                                                                           |
| -------- | ------------------------------------------------------------------------------------------------------------------ |
| $        | This signals the end of the file stream and tells the interpreter to exit                                          |
| +        | Plus operator that pops two values from the Stack, adds them and pushes the result back to the Stack               |
| -        | Minus operator that pops two values from the Stack, subtracts them and pushes the result back to the Stack         |
| *        | Multiply operator that pops two values from the Stack, multiplies them and pushes the result back to the Stack     |
| /        | Integer divide operator that pops two values from the Stack, divides them and pushes the integer part to the Stack |
| \        | Modulus operators that pops two values from the Stack, divides them and pushes the remainder to the Stack          |
| ?        | Input operator that reads a number from stdin                                                                      |
| ?'       | Input operator that reads a single character from stdin                                                            |
| !        | Output operator that pops the Stack and prints the number                                                          |
| !'       | Output operator that pops the Stack and prints the ASCII representation of the value                               |
| '(char)  | Push operator that pushes the ASCII value of the next character to the Stack                                       |
| "        | Output operator that prints anything up to the next " operator                                                     |
| <letter> | Gets the variable address of the letter                                                                            |
| :        | Assignment operator that assigns a value to a variable                                                             |
| .        | Dereference operator that prints the value of a variable                                                           |
| <        | Comparison operator that pushes 1 if X < Y otherwise pushes 0                                                      |
| >        | Comparison operator that pushes 1 if X > Y otherwise pushes 0                                                      |
| =        | Comparison operator that pushes 1 if X = Y otherwise pushes 0                                                      |
| [        | Conditional start that pops the Stack. If it's 0 or a negative number skips to the matching ] operator             |
| ]        | Conditional end operator                                                                                           |
| ^        | Break operator that exits a loop if the value of the Stack is false                                                |
| ~        | Comment operator                                                                                                   |
| (number) | Pushes a number on to the Stack                                                                                    |

NB: There are other operators for Mouse but these core operators have been implemented into this version.


## Inner Workings of the Stack and RPN
To illustrate how the Stack works, the following is a demonstration of adding two numbers
in Mouse. To compute ``17 + 56`` in Mouse, the following code is necessary along with
diagrams.

`` 17 56 + ``

| Current Character | Top 0 | Top 1 | Description                                                            |
| ----------------- | ----- | ----- | ---------------------------------------------------------------------- |
| 17                | 17    |       | Put 17 on the Stack                                                    |
| 56                | 56    | 17    | Put 56 on the Stack. This moves 17 to the next space making 56 the Top |
| +                 | 73    |       | Add the numbers in Top 0 and Top 1 put the result in Top 0             |

   
Because of the advantages RPN provides a complex expression such as  
``(22 + 36)  * (60 / 10)``  
could be written in RPN as:  
``22 36 + 60 10 / *``

| Current Character | Top 0 | Top 1 | Top 2 | Description                                                                                     |
| ----------------- | ----- | ----- | ----- | ----------------------------------------------------------------------------------------------- |
| 22                | 22    |       |       | Put 22 on the Stack                                                                             |
| 36                | 36    | 22    |       | Put 36 on the Stack pushing 22 lower                                                            |
| +                 | 58    |       |       | Add the top two values and put their result on the Stack                                        |
| 60                | 60    | 58    |       | Put 60 on the Stack pushing 58 lower                                                            |
| 10                | 10    | 60    | 58    | Put 10 on the Stack further pushing the already existing numbers lower                          |
| /                 | 6     | 58    |       | Divide pops the top two values, divides them and pushes the result on the Stack                 |
| *                 | 348   |       |       | Multiply takes the top two numbers and multiplies them together pushing the result on the Stack |


## Common Expressions
Below are some common expressions in Mouse and their equivalent in the C programming
language and in Python.  

| Mouse Expression | Description                                  |
| ---------------- | ---------------------------------------- |
| 54 N:            | Assign the value of the variable N to 54 |
| N. !             | Recall and print the value of N          |
| Y. X:            | Copy the value of Y into X               |
| N. 1 + N:        | Increment the value of N by 1            |
| N. N. * N:       | Store the square of N into N             |
| X. Y. X: Y:      | Swap the values of x and y               |
| ?!               | Read a number and print it immediately   |


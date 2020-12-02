# IAS_machine
In c language

Description

The instructions implimented and their respective opcodes in
hexadecimal format.
JUMP M(X,0:19) - 0D
JUMP M(X,20:39) - 0E
JUMP + M(X,0:19) - 0F
JUMP + M(X,20:39) - 10
LOAD MQ - 0A
LOAD MQ,M(X) - 09
STOR M(X) - 21
LOAD M(X) - 01
LOAD -M(X) - 02
LOAD |M(X)| - 03
LOAD -|M(X)| - 04
ADD M(X) - 05
ADD |M(X)| - 07
SUB M(X) - 06
SUB |M(X)| - 08
MUL M(X) - 0B
STOR M(X,8:19) - 12
STOR M(X,28:39) - 13

To check programs
Example 1
main()
{
int a = 3;
int b = 5;
int c;
c = a+b;
}

For the above program, the instructions used are
1. 01 003 - To load data from postion 3(i.e value 3) into the accumulator.
2. 05 002 - To add data from position 2(i.e value 5) to the accumulator and put the result in accumulator.
3. 21 004 - To transfer data from accumulator to the memory location 4, which is used as the register c in this case.
4. FF 000 - To halt.
The contents of memory before exectution of the program and after execution of the program are shown for checking.
The Values of registers PC,IR,MAR and MBR are also printed out.
Location 004 (i.e - 5th row of the 2-d array contains the value of c)

Example 2
main()
{
int a = 15;
int b = 5;
int c;
if(a>=b)
c = a-b;
else
c = a+b;
}

For the above program, the instructions used are
1. 01 006 - To load data from postion 6(i.e value 15) into the accumulator.
2. 06 005 - To subtract data from position 5(i.e value 5) from the accumulator and put the result in accumulator.
3. 10 003 - To JUMP to the instruction on the right side of position 3 if the value of accumulator is positive. In this case, as the value of accumulator is positive JUMP is exectuted.
4. 21 004 - Store the value present in the accumulator into the 4th row of the 2-d memory array.
5. The rest of the instructions are for the else case execution. Accumulator is again loaded with value from position 6, then addition is performed and the result is stored in 8th row of the 2-d memory array.
NOTE - 5th step is executed by default.
The contents of memory before exectution of the program and after execution of the program are shown for checking.
The Values of registers PC,IR,MAR and MBR are also printed out.
Location 004 (i.e - 5th row of the 2-d array contains the value of c in this case).

Format to give input

1. Instructions should be given in Hexadecimal format. Each instruction should be 10 digits long. After every 10 digits new line must be given.
2. Only capital letters for A, B, C, D, E and F.
3. If left or right instruction in any set is missing then 0's should be given in the place of missing instruction.
4. FF is the opcode for HOLT instruction.
5. After giving all the instructions. Press enter and give two '*'. With this the input taking process terminates.
6. Please refer to the screenshots for assistance.

# 2024 COMP1056 Coursework 03

**Submission Deadline:** 10/01/2025 15:00

**WARNING**: You must used the supplied skeleton `.c` files  to implement your solution. Using a different file, or changing the names risks your coursework failing to be marked by the pipeline.


## Decoding ARM instructions

### Description

In this coursework, which is **worth 20% of the final mark for COMP1056**, you are going to write a C program that can decode an ARM instruction. In week 03 of COMP1056, we saw how 6502 instructions were encoded following a specific pattern that made it easy to decode which type of instruction was encoded and what addressing mode was being used by looking at specific bits.

The ARM CPU you have been using in COMP1055 is no different and for this final coursework you are going to write a C program that can decode ARM instructions from their binary representation. For simplicity, rather than use your decoding to drive a CPU, instead your program will just generate a string containing the mnemonic you would feed to an assembler -- in other words, you are effectively writing a disassembler.

Each ARM instruction is exactly 32-bits, and so comfortably fits into an `unsigned int`. The way the instructions are allocated into the specific bits are described in section four of the ARM7TDMI document in the 'Resources' section of the COMP1054 Moodle page. An abridged version listing only the instructions you need to decode for this coursework can be found included in this repository.

Page 4-2 of the document contains a helpful table summarising how bits are assigned to identify different groups of instructions. For example, it shows that for a `SWI` instruction bits 24, 25, 26, and 27 will all be set to true, or 1 in binary), or that a Branch instructions (both `B` and `BL`) will have 101 in bits 25, 26 and 27. By considering these bit patterns, it is possible to identify what type of instruction you are decoding, and then extract further information about it, e.g. bit 24 is used to distinguish between a normal branch (`B`) and a branch-with-link (`BL`).


### Submission and Assessment

You will need to fork this repository and then clone it to your Linux system. Submission is then done via a `git commit` and a `git push` as you have done previously done for other courseworks set in the first year. If you click on the **Build** option on the left-hand side of your GitLab interface, you’ll be able to see the marks and feedback for your submission.

You will be given a mark for this exercise, which will be shown along with the feedback in the pipeline. 

The final submission made before the deadline will be taken as your mark for this exercise. Please check that the submission system has correctly received and assigned a mark for your submission  (i.e. that your last submission has a mark displayed alongside it) or you may obtain a mark of zero.

It is not possible to remove a submission. Attempting to do so by deleting the pipeline entry or the commit from the gitlab interface will not remove the mark. If you wish a previous submission to be counted, then you will need to **resubmit** that version of the code.

### Coursework 03 Description: Decoding ARM instructions

For this coursework, you are to implement a C function called `DecodeInstruction()` inside the file `disarm.c`. This function takes in two  parameters:
  1. an `unsigned int` called `instr` which contains the binary opcode for an ARM instruction. You will need to implement this function so that it generates a string containing the correct mnemonic for the instruction passed in. 
  2. a pointer to an empty string, called `decodeStr` which you should fill with a string that contains the decoded version of the string.

How you do this is up to you, you may choose to build up a string in memory and then print it in one go, or to print out the separate parts as you go...

To do this, you will need to follow the same procedure you would by hand to decode an ARM instruction: isolating certain bits to find out what type of instruction it is, and then using that knowledge to process the other bits in the instruction. You can do this in C by using the bitwise operations (and, or, and xor) and bit shifting.

As an example, if we wanted to isolate the condition codes associated with an instruction (stored in the most significant four bits), we could use a bitwise-AND to clear all but the top four bits and a shift right to move them from bits 31—28, to bits 3–0.  So with, the instruction in the `unsigned int instr`, the following code would give the conditional execution code in `ccode`:

	ccode = (instr & 0xF0000000) >> 28;

**Note**: even if the bits you are wanting to extract are expected to be zero, you will still want the 'mask' (i.e. the `0xF0000000` above, since it 'masks off' the bits we want) to have ones in those bit positions

We suggest that you implement the instructions gradually, starting with the simpler ones and once they are working progress to the trickier ones. Our suggestion would be start by processing  `SWI`s, then move to branch instructions, before moving to the data processing instructions and then onto other instruction sets (load/stores, multiply etc). Remember to test your program works properly after you've implemented each set of instructions!

Note that decoding some of the instructions (branches, data processing, for instance) will require you to sign-extend and rotate bits which C does not provide support for. Some simple C functions are provided that perform these operations (see below for details of how they work). 

The basic operation of your function will need to work like this:

  1. Identify  what type of instruction (Data processing, Load/Store, Branch, etc.) is described by the number in `instr`.
      - Note that due to the evolution of the ARM CPU, some instructions can only be decoded once you've decoded that it is not a different type of instruction. For example, both Data Processing and Multiply instructions have 0s in bits 27 and bits 26. This means that to identify a Data Processing instruction, checking for 0s in bits 27 and 26 is not sufficient.
  2. Depending on the type of instruction identified, you will then need to consider the other bits in `instr` to fully decode the instruction. 
      - For example, once you have identified a data processing instruction, you can use bits 21, 22, 23, and 24 to identify whether it is an AND, EOR, SUB, etc. instruction (see the table in Figure 4-4, or Table 4-3 for the full list).
  3. Once you have decoded the instruction, you should build up the string (e.g. by using `sprintf()`, or similar techniques) to build up the disassembled string.
      - Note that this should be similar to the same kind of string that would have appeared in the assembler to generate the instruction, although there are limitations on how far you can go. For example, with branch-type instrutions (`B`, `BL`) then it is not possible to obtain the original label names. Instead, you should print out the positive or negative offset that would be added to the program counter (i.e. the value encoded in the instruction).

**Hint**: The `SWI` instructions are probably the easiest to decode, so we suggest you start here, followed by the branch instructions. Then move onto the data processing instructions, Load-Store instructions etc. As described, in the Assessment Criteria section below, you are not required to compleltely decode all instructions correctly to obtain a passing grade for this coursework.


### Simplifications and Observations

- There's no need to convert registers to anything other than `R0`, `R1` etc. It is perfectly acceptable for the program counter to be converted back to be `R15`.

- Although ARM allows all instructions to potentially be executed conditionally, you are only required to decode the condition codes for the branch instructions.

- The `ADRL` instruction does not exist, instead the assembler uses the value stored in the  program counter (i.e. `R15`) to calculate the address using a combination of `SUB` and `ADD` instructions. Therefore, you will see `ADRL` listed as an instruction to convert (and if you test a program containing one on code that uses it you will find it replaced by `SUB` and `ADD` instructions).

### Supplied Support Functions

To help you with your implementation the following two functions are defined as part of `disarm.c`, `SignExtend()` and `Rotate()`.

#### SignExtend

Some ARM instructions (e.g. the branches) encode a two's-complement number using less than 32-bits. This means that once extracted from the ARM instruction, C will not treat it as negative number (when appropriate). The supplied function:

	int SignExtend(unsigned int x, int bits)

Extends the two's complement number `x`
to fill all 32-bits of an `int`. To use it, extract the bits from the instruction and pass them as the parameter `x`. Also, pass the number of `bits` used to store the number, e.g. for a branch, 26. The return value would be a signed `int` that can be used elsewhere in your program, (e.g. to pass to `sprintf()`).

#### Rotate

Some instructions (e.g. the data-processing instructions) encode a number as an 8 bit value and the number of bits to 'rotate them around to the right'. The function:

	int Rotate(int rotatee, int amount)

will rotate the parameter `rotatee` to the right by `amount` bits and return the results.

**Hint**: the amount of rotation required here is the number of bits to rotate, check the description for how the rotations are encoded. For example, Immediate operand rotates (p4-15) subjects values 'to a rotate right by twice the value in the rotate field'…

### Testing

Since you are only required to implement a function that decodes an instruction, there needs to be a mechanism to test your function. The supplied Makefile will compile your `disarm.c` and link it into a program that will attempted to decode the first ten instructions found within a `.kmd` file (i.e. the files create by the Komodo assembler). The generated program `disarm_test` can be run:

	$ ./disarm_test <kmd file>

where `<kmd file>` can be replaced with the path to any `.kmd` file, which it will attempt to disassemble instructions from. This programing will process the `.kmd` file reading each (potential) instruction before calling and passing it to your `DecodeInstruction()` function. The output from program consists of the address where the instruction would have been placed in Komodo's memory, the hexadecimal number (i.e. the value passed to your function) and the string *output* from your function. 

If you open the `.kmd` file in a text editor, then you can see the assembly language which generated each instruction which you can compare against your output -- although bare in mind the expected differences stated above.

A selection of different test `.kmd` files can be found in supplied folder `Samples`. Running 

	$ make disarm_test_run

will run your program against each of the supplied test files. Please note, these tests are designed to be illustrative, not *exhaustive*. You should also test against other instructions in other files. You can generate your own tests by using Komodo to create simple files containing a few instructions to test.


### Assessment criteria

Any coursework that is able to correctly distinguish between the different groups of instructions (at a minimum between branches, SWI and data processing, while also breaking the data processing down into the individual instruction types (`AND`, `EOR`, `SUB`, etc)  ) will obtained a passing mark (i.e. greater than 40%). 

Any solution fully implementing the decoding of `SWI`s, branches and data-processing instructions (i.e. to the point where it is clear will be awarded the equivalent of a mark in the 2:1 range (60%-70%). 

To obtain the equivalent of a first-class mark (>70%) then you will have needed to also (at least) have implemented the load/store instructions as well.

The pipeline, once released, will mark your solution by providing your `DecodeInstruction()` with a number of instructions to decode and looking at the string output by your solution. You will then be given a percentage mark alongside feedback for the exercise.



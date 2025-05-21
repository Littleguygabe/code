# COMP1005 2024 Coursework 06

## Introduction

This coursework focuses on writing a program to calculate the scores in tenpin bowling games. This coursework will leverage (almost) everything you have learnt in this module.
There are **two tasks** to complete, details of which are given below. Links to external pages are provided in the details below which you will need to follow and read to complete each task.

## Assessment

This coursework is worth **20%** of your final course grade. The overall grade awarded for each task is as follows:

|            |  **Total** |
| ---------- |  :-------: |
| **Task 1** |  **15%**   |
| **Task 2** |  **5%**

A detailed breakdown of the points awarded for your programs is shown in the output of the build pipeline. The overall originality, organisation, and quality of your code for each task is also assessed and will affect your final mark for each task. Each time you push your code, a *similarity score* between 0-100 for each task is calculated and shown in the GitLab assessment pipeline. A lower similarity score is better. Submissions with similarity scores greater than 80 will be carefully reviewed and your mark for a task will be reduced to 0 if this review shows your code lacks originality, is poorly organised, or is of a low quality.

Your provisional score for each task can be viewed on GitLab after every push to `projects.cs.nott.ac.uk`. You can make as many revisions and pushes as you like, hopefully increasing your score as you do so. Your final score will be based on the code in your *last commit* pushed to `projects.cs.nott.ac.uk`. If your last commit is pushed after the coursework deadline, it will be subject to standard [University late policy](https://www.nottingham.ac.uk/qualitymanual/assessment-awards-and-deg-classification/pol-penalties-for-late-submission.aspx) deductions. Submissions on or after the day coursework feedback is provided (usually in the in person lecture the week following the submission deadline) will not be accepted.

After the coursework deadline, your code will undergo further review and, based on this review, your provisional score may go up or down. This further review will include checks for code plagiarism and for trivial implementations e.g. implementations just containing an empty main function or clearly not written following the task guidelines. Final scores will be published on the COMP1005 moodle page usually in the week following the coursework deadline.

This coursework is individual work i.e. *must be your own work* and follow the [University academic integrity and misconduct guidance](https://www.nottingham.ac.uk/studyingeffectively/referencing/integrity/index.aspx) and [policy on academic misconduct](https://www.nottingham.ac.uk/qualitymanual/assessment-awards-and-deg-classification/pol-academic-misconduct.aspx). Use of AI tools to generate or improve code is not permitted.

Your repository contains a file called `.gitlab-ci.yml`. This file is used during the assessment process and *must not* be removed or edited in any way. Any tampering with this file will result in a score of zero for this coursework.

## Background

Even if have played [tenpin bowling](https://en.wikipedia.org/wiki/Ten-pin_bowling) (called bowling for simplicity hereafter), it is likely that you are not 100% clear how scores are calculated, as there are misconceptions and exceptions, as described below. A detailed guide on how scores are calculated can be found [here](https://www.breakdownbowling.com/how-are-bowling-scores-calculated/).

In a bowling game, there are 10 turns that are called **frames**. For now, let's focus on frames 1-9. In each frame, you are given 2 attempts to knock down all the pins. We will refer to these attempts as **rolls**.

* If you knock down all the pins on the first roll, it is called a **strike** and is marked with an `X`.
* If you knock down all the pins in two rolls, it is called a **spare** and is marked with `/`.
* If you knock down fewer than 10 pins in the frame, you simply note down the number of the pins knocked down in each roll. This is called an **open frame**.
* If no pins are knocked down, it is marked with `-` instead of `0`.
* If a player steps on or over the fault line on the bowling lane, they receive 0 points for that roll. This is typically marked with an `F`.

Both *spares* and *strikes* are awarded 10 points initially. What is the benefit of rolling a strike or a spare?

* A **strike** earns `10` points + the points of the next **<ins>two</ins> consecutive rolls**, regardless of which frames they occur in.
* A **spare** earns `10` points + the points of the next **<ins>one</ins> consecutive roll**.

Calculating the scores for spares and strikes requires a look-ahead. Additionally, calculating the score for a spare may require looking back at the current frame's rolls (this will become clearer when we review an example). 

Now, let us see how the 10th frame differs. It is important to note that there is no look-ahead in the 10th frame. A strike is worth 10 points, and a spare is also worth 10 points. However, there are additional benefits for achieving either.

* If you roll an **open frame** (i.e you didn't knock down all the pins in two attempts), the same scoring rules as for **open frames** in frames 1–9 apply.
* If you roll a **spare**, you are awarded <ins>one</ins> extra roll.
* If you roll a **strike**, you are awarded <ins>two</ins> extra rolls.

Thus, the 10th frame can have up to three rolls in total, depending on the player's performance.

Let's make an example. The following game is provided and we need to compute the scores frame by frame:

```
 #1  #2  #3  #4  #5  #6  #7  #8  #9   #10
+-----------------------------------------+
|5 4|7 -|9 /|5 /|8 -|X  |5 /|X  |X  |4 / X|
|   |   |   |   |   |   |   |   |   |     |
+-----------------------------------------+
```

**Frame 1:** This is an **open frame** and the score is simply calculated as the sum of the two rolls, `9` in this case:

```
 #1  #2  #3  #4  #5  #6  #7  #8  #9   #10
+-----------------------------------------+
|5 4|7 -|9 /|5 /|8 -|X  |5 /|X  |X  |4 / X|
|  9|   |   |   |   |   |   |   |   |     |
+-----------------------------------------+
```

**Frame 2:** This is another **open frame** and the score is again calculated as the sum of the two rolls, `7` in this case:

```
 #1  #2  #3  #4  #5  #6  #7  #8  #9   #10
+-----------------------------------------+
|5 4|7 -|9 /|5 /|8 -|X  |5 /|X  |X  |4 / X|
|  9| 16|   |   |   |   |   |   |   |     |
+-----------------------------------------+
```

> [⚠️] The scores in the scoreboard are reported in a cumulative sum, this means that the score of `frame[i]` is summed to the score of `frame[i-1]` (if any). I use here an array syntax for ease of explanation and do not take this as an implementation suggestion. Hence `7+9=16`

**Frame 3**: We have a *spare*, the score is `10` plus the next roll (first roll on Frame 4), which is a `5`. The score for this frame is `15`.

```
 #1  #2  #3  #4  #5  #6  #7  #8  #9   #10
+-----------------------------------------+
|5 4|7 -|9 /|5 /|8 -|X  |5 /|X  |X  |4 / X|
|  9| 16| 31|   |   |   |   |   |   |     |
+-----------------------------------------+
```

**Frame 4**: We have another *spare*, the score is `10` plus the next roll (first roll on Frame 5), which is a `8`. The score for this frame is `18`.

```
 #1  #2  #3  #4  #5  #6  #7  #8  #9   #10
+-----------------------------------------+
|5 4|7 -|9 /|5 /|8 -|X  |5 /|X  |X  |4 / X|
|  9| 16| 31| 49|   |   |   |   |   |     |
+-----------------------------------------+
```

**Frame 5:** This is another **open frame**, `8`

```
 #1  #2  #3  #4  #5  #6  #7  #8  #9   #10
+-----------------------------------------+
|5 4|7 -|9 /|5 /|8 -|X  |5 /|X  |X  |4 / X|
|  9| 16| 31| 49| 57|   |   |   |   |     |
+-----------------------------------------+
```

**Frame 6**: we have a *strike*. The score is `10` plus the next two rolls. The first 'next' roll is `5` and the second 'next' roll is `/`. A spare is worth `10`. Therefore, the score for this frame is `20`.

> [⚠️] The look-ahead is **NOT** recursive. Although the strike is followed by a spare (the second roll of Frame 7), we don't look ahead of that spare.

```
 #1  #2  #3  #4  #5  #6  #7  #8  #9   #10
+-----------------------------------------+
|5 4|7 -|9 /|5 /|8 -|X  |5 /|X  |X  |4 / X|
|  9| 16| 31| 49| 57| 77|   |   |   |     |
+-----------------------------------------+
```

**Frame 7**: We have a *spare*, the score is `10` plus the next roll (first roll on Frame 8), which is a `X`. As the strike is worth `10`, the score for this frame is `20`.

```
 #1  #2  #3  #4  #5  #6  #7  #8  #9   #10
+-----------------------------------------+
|5 4|7 -|9 /|5 /|8 -|X  |5 /|X  |X  |4 / X|
|  9| 16| 31| 49| 57| 77| 97|   |   |     |
+-----------------------------------------+
```

**Frame 8**: we have a *strike*. The score is `10` plus the next two rolls. The first 'next' roll is `X` (first roll on Frame 9), and the second 'next' roll is `4` (first roll on Frame 10). The score for this frame is `24`

```
 #1  #2  #3  #4  #5  #6  #7  #8  #9   #10
+-----------------------------------------+
|5 4|7 -|9 /|5 /|8 -|X  |5 /|X  |X  |4 / X|
|  9| 16| 31| 49| 57| 77| 97|121|   |     |
+-----------------------------------------+
```

**Frame 9**: we have a *strike*. The score is `10` plus the next two rolls. The first 'next' roll is `4` and the second 'next' roll is `/`. A spare is worth `10`. Therefore, the score for this frame is `20`.

```
 #1  #2  #3  #4  #5  #6  #7  #8  #9   #10
+-----------------------------------------+
|5 4|7 -|9 /|5 /|8 -|X  |5 /|X  |X  |4 / X|
|  9| 16| 31| 49| 57| 77| 97|121|141|     |
+-----------------------------------------+
```

**Frame 10**: We have three rolls. Let's see roll by roll:
* `Roll 1`: We have a `4` and we will keep it as is.
* `Roll 2`: We have a spare. Now we have a `/` symbol, but how much is it worth? Mathematically, it's `6` (calculated as `10 - previous_roll` is an implementation trick that I recommend to use).
* `Roll 3`: We have a *strike*, so it's just `10`.
The total of this frame is `4+6+10=20`

```
 #1  #2  #3  #4  #5  #6  #7  #8  #9   #10
+-----------------------------------------+
|5 4|7 -|9 /|5 /|8 -|X  |5 /|X  |X  |4 / X|
|  9| 16| 31| 49| 57| 77| 97|121|141|  161|
+-----------------------------------------+
```

As mentioned in the last frame example, calculating the spare as `10 - previous_roll` is an implementation trick that can be used for any circumstance shown above and may be useful to keep it in mind. I showed you in the last instance because it was better to focus on how scoring works first and then provide you some hints on the implementation later on.

Furthermore, you can use [this website](https://bowlinggenius.com) to practise and make a few examples yourself.

For completeness, the [perfect game](https://en.wikipedia.org/wiki/Perfect_game_(bowling)) is achieved by rolling `12` strikes (a strike for each of frame between 1-9, and three more strikes in the last frame) and it's worth `300`.

## Task 1

### Overview

Your task is to complete the implementation of the function `bowling_score_parser` and `print_scoreboard`. The first function parses a game string and should return a linked list of frames. The second function prints a scoreboard (details below) given a linked list of frames as parameter.

### Details

You are given the following files:
* `linked_list.c`, `linked_list.h`, `queue.c`, `queue.h`: These files are identical to those used in previous assignments.
* `tpb.c`: this is the file you should edit and implement your code. Further details about its contents are provided below. This files comes with a header file `tpb.h` required by the next file.
* `score_calculator.c`: This is a pre-implemented main file. One or more games are provided as command-line arguments and passed to the `bowling_score_parser` function, implemented in `tpb.c`. The main file prints either the scoreboard (details below) or an error (details also below).
* `Makefile` to run tests on both tasks for this coursework and it's organised as seen in previous assignments.

You should not change any of the provided files, **except** `tpb.c`.

Your task is to **parse** a string representing a game and calculate the scores for each frame, as illustrated earlier. If we consider the game shown in the example, this will be represented with the following string: `547-9/5/8-X5/XX4/X`. The major difference between this task and the Task 4 of the last coursework is that summations (referred to as **reductions** hereafter) are performed without operators. For example:

* For a strike, reduce immediately and look ahead (if applicable).
* For a spare, reduce immediately and look ahead (if applicable).
* For two rolls, reduce after parsing them.
* For the last frame, reduction may involve up to three rolls.

Most of the implementation will occur in the `bowling_score_parser` and `print_scoreboard` functions:

* `bowling_score_parser`: This function takes a string (`const char *`) and a pointer to `int` as input and returns a `LinkedList *` containing parsed frames. The function must also handle incomplete games (more details below).
* `print_scoreboard`: This function, also invoked in the main file, prints the game string followed by the scores for each frame. For example:

```
$ ./task1 547-9/5/8-X5/XX4/X
547-9/5/8-X5/XX4/X: 9 16 31 49 57 77 97 121 141 161 
```

The `print_scoreboard` function does not access the command line directly. It operates solely on the linked list produced by `bowling_score_parser`. This serves also as a way to validate your parsing.

If the program is called with multiple games, the following output is expected (note that the 3rd game is intentionally incomplete):

```
$ ./task1 7-35xxxxxx716- x7/xx637/x6/xxx7 xx8-6-
7-35xxxxxx716-: 7 15 45 75 105 135 162 180 188 194 
x7/xx637/x6/xxx7: 20 40 66 85 94 114 134 154 184 211 
xx8-6-: 28 46 54 60 
```

You can also note that the parsing should be case insensitive, i.e. `x` and `X`, and `f` and `F` should be treated equally. A function called `tokenization` is already implemented for you and handles these cases too.

In the case of an error, the second parameter of `bowling_score_parser` (a pointer to `int`) should be set to the **zero-based position** in the string where the error occurred. The error message is already implemented for you in `score_calculator.c` but relies on the position your implementation provides. Examples of incorrect input and their output are as follows:

```
$ ./task1 7-35xxxxxx716-/ x7/xx637xx6/xxx7 x/x8-6-

Invalid token near 15 (token found /)

Invalid token near 9 (token found x)

Invalid token near 2 (token found /)
```

Explanation of the errors:

* **Game 1:** The 3rd roll in the 10th frame is invalid because that frame can only have two rolls.
* **Game 2:** A strike appears as the second roll in a frame (frames 1–9). This is not allowed.
* **Game 3:** A spare follows a strike, which is not permitted.

To handle all the cases and exception, you can help yourself with the following parsing grammar:

```
<game>           ::= <frames> | <frames> <tenth-frame>
<frames>         ::= <frame> | <frame> <frames>
<frame>          ::= <strike> | <spare-frame> | <open-frame>
<strike>         ::= "X"
<spare-frame>    ::= <roll> "/"
<open-frame>     ::= <roll> <roll>
<tenth-frame>    ::= <strike> <bonus-roll> <bonus-roll>
                   | <spare-frame> <bonus-roll>
                   | <strike> <spare-frame>
                   | <open-frame>
<roll>           ::= "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" | "-" | "F"
<bonus-roll>     ::= <strike> | <roll>

```
  
Your implementation does not need to specify the nature of the error, only its position. The provided code handles error reporting for you.

Your implementation should handle dynamically allocated memory correctly i.e. free all dynamically allocated memory. As discussed in lectures, a good tool for assessing if a program has handled dynamic memory allocation correctly is `valgrind`. To check your implementation using `valgrind` you can type:

```bash
$ make task1_test_memcheck
```

If your program has correctly handled dynamic memory allocation, the last line of output should read:

```
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

### Implementation hints

This Task may be challenging, so it's important to carefully follow the suggested implementation steps. The core function, `bowling_score_parser`, should be structured into the following key sections. If you follow these guidelines, your implementation will align with the provided framework.

* **Section 1 - Initialisation:** Initialise all the data structures required for the function. For example:
  1. Define variables to track the state of all the sections you'll see below
  1. Allocate and initialise:
      * A queue to store tokens generated during lexical analysis (next section).
      * An array of linked lists (`frame_list`), one for each frame. Use `FRAME_NUMBER` to define the size of this array. This array can be statically allocated. This array of lists will become handy in _Section 3_.
      * A linked list called `scoreboard` to hold the final parsed and validated frames to be returned.

* **Section 2 - Lexer:** Perform lexical analysis on the input string `game_characters`:
  1. Iterate over the characters in the string:
    * For each character, use the provided `tokenization` function to classify it as a valid token.
    * If tokenization fails (returns false), record the error position inside the 2nd parameter `err_position` and stop further processing. Keep in mind this second parameter is a pointer.
    * Otherwise, assign the token's position (`pos` property of the struct `Lex`) and add it to the queue of tokens (use `push_queue` function).

* **Section 3 - Parser:** Parse the tokens into an intermediate representation use:
  1. Pop tokens from the queue one by one.
     * For each token, append it to the linked list corresponding to the current frame in `frame_list`.
  2. Handle look-ahead tokens:
     * For each token, check its look-ahead value (unless it's the last frame).
     * Copy the required number of look-ahead tokens from the queue into the linked list for the current frame.
  3. Transition frames:
     * After processing the rolls for a frame, determine whether to move to the next frame:
     * Advance to the next frame if the current frame contains enough rolls (accounting for strikes and spares).

> [ℹ️] The array of linked lists `frame_list` aims to implement a data structure resembling an **Abstract Syntax Tree** ([AST](https://en.wikipedia.org/wiki/Abstract_syntax_tree)). An AST is a typical data structue in parsing. However, we don't need its complexity for this task, because we know we have 10 frames and we also know that we have elements of the same type all times (i.e., we don't need to differentiate between literals or operators). If we consider the example `547-9/5/8-X5/XX4/X`, this data structure will look like this at the end of this section:
  
```
   Array of Lists
    +---------+
    | List #0 | -> [5] -> [4]
    +---------+
    | List #1 | -> [7] -> [-] 
    +---------+
    | List #2 | -> [9] -> [/] -> (5)
    +---------+
    | List #3 | -> [5] -> [/] -> (8)
    +---------+
    | List #4 | -> [8] -> [-] 
    +---------+
    | List #5 | -> [X] -> (5) -> (/)
    +---------+
    | List #6 | -> [5] -> [/] -> (X)
    +---------+
    | List #7 | -> [X] -> (X) -> (4)
    +---------+
    | List #8 | -> [X] -> (4) -> (/)
    +---------+
    | List #9 | -> [4] -> [/] -> [X]
    +---------+
```

Square brackets were used to indicate rolls in the frame, parenthesis to indicate look-ahead rolls. If you follow these instructions, the next section will be implemented easily.

* **Section 4 - Reducer:** Build the final scoreboard from the parsed data:
  1. Validate frames:
   * Use helper functions (e.g. `validate_frame` and `validate_last_frame`) to verify the structure of each frame in the linked list.
   * If validation fails, set the error position and stop processing (this is why the `Lex` struct has the `pos` property).
  2. Calculate scores:
   * For each frame, initialise a `Frame` struct to store its rolls, score, and cumulative score.
   * Traverse the linked list for the frame and compute:
      * The score for the frame, including look-ahead rolls if applicable.
      * The cumulative score, by adding the current frame's score to the previous frame's cumulative score (if any).
  3. Update scoreboard:
   * Append the Frame struct to the scoreboard linked list.

* **Section 5 - Epilogue:** 
  1. Free resources:
   * Deallocate memory for the `frame_list` linked lists.
   * If an error occurred, also deallocate the `scoreboard` linked list.
  2. Return:
   * If there were no errors, return the `scoreboard`.
   * In the case of errors, return `NULL`.

> [⚠️] In the case of incomplete games where the last played frame requires a look-ahead, simply consider that frame as 10 (it's either a *strike* or a *spare*). If _Section 4_ is implemented correctly, your code will already handle this feature.

An example of an allowed incomplete games:

```
 #1  #2  #3  #4  #5  #6  #7  #8  #9   #10
+-----------------------------------------+
|5 4|7 -|9 /|5 /|   |   |   |   |   |     |
|  9| 16| 31| 41|   |   |   |   |   |     |
+-----------------------------------------+
               ^
               |_______ We don't know what comes next, but we do know that Frame 4 is at least worth 10 points.
```

You can add to the file `tpb.c` any helper functions you need, as long as you don't edit `tpb.h`.

### File `tpb.c` structure

The tpb.c file contains essential code and utilities needed for your implementation. Below is a breakdown of its components:

  1. **Includes and Macros**: The file begins with a series of `#include` directives. You may add more as needed, e.g., `string.h`, as long as they belong to the Standard library of C (except the maths library, which you are not allowed to use). There is also a custom definition of a `bool` type using `typedef`, along with `true` and `false` macros (this was shown in a lecture):

```
#define true 1
#define false 0
typedef int bool;
```

  This approach ensures compatibility with the ANSI C standard.

  2. **Constants and Enums**: A `#define` statement for `FRAME_NUMBER` (set to 10) is included to represent the fixed number of frames in a bowling game. An enum called Token defines the possible types of tokens used in the game:

```
typedef enum {
  TOKEN_LITERAL,  /* Number 0-9 */
  TOKEN_SPARE,    /* '/' symbol */
  TOKEN_STRIKE,   /* 'X' or 'x' symbol */
  TOKEN_GUTTER,   /* '-' symbol */
  TOKEN_FAULT     /* 'F' or 'f' symbol */
} Token;
```

> [ℹ️] An enumeration contains constant integer values (the first one is typically internally initialised with 0) and also defines a **type**. Although internally everything is treated as `int`, enumerations are a type-safe alternative to `#define` statements. You can read more [here](https://www.geeksforgeeks.org/enumeration-enum-c/).

  3. **Structures**: The `Lex` structure is used to represent each token in the game string. Its fields are:
  * token: The type of token (e.g., TOKEN_STRIKE). The type is the `Token` enum shown above.
  * character: The actual character from the input.
  * look-ahead: Number of rolls to consider for scoring look-ahead (e.g., 2 for a strike).
  * pos: The position of the character in the input string. Example:

```
typedef struct {
  Token token;
  char character;
  int lookahead;
  int pos;
} Lex;
```
  4. **Functions:**  The file provides several functions to assist with the parsing and scoring process:

   * `free_scoreboard`: Frees all memory allocated for the linked list of frames (`scoreboard`). _Recommended usage:_ Call this function whenever an error occurs. The `main` function also invokes `free_scoreboard`.
   * `get_token_value`: Computes the numeric value of a given token. Special handling for _spares_: If the token is a spare `/`, it calculates the score based on the previous roll. Example usage (assuming both parameters are pointers):

```
int value = get_token_value(current_token, previous_token);
```
   * `tokenization`: Converts a character into a `Lex` structure with its corresponding `token` type, `character`, and `lookahead` value. Returns `true` if the character is valid, `false` otherwise. Example usage:

```
Lex lexchar;
if (tokenization('X', &lexchar)) {
  /* Token is valid and lexchar is initialised */
}
else
{
    /* handle error */
}
```

   * `bowling_score_parser`: The main function you will implement, responsible for parsing the game string into a linked list of frames (`scoreboard`).
It follows five main sections: **Initialisation**, **Lexer**, **Parser**, **Reducer**, and **Epilogue**. Returns `NULL` in case of an error, or the constructed LinkedList for the scoreboard if successful.
   * `print_scoreboard`: A function for printing the scoreboard (to be implemented). It should traverse the linked list and display frame information.

### Additional information

You are free to choose whichever method you want to implement your program. You can add any helper functions you need and may even edit the structs in `tpb.c` (as you think more appropriate) with the following restrictions:

* you are not allowed to use global variables
* all dynamically allocated memory should be freed
* the function `bowling_score_parser` must return a linked list of `Frame` structs.
* the function `print_scoreboard` must take a linked list of `Frame` structs as parameter. The last two constraints derive from the fact you are not allowed to change `tpb.h`.

As stated above, you can use any standard library functions (except the maths library).

Your program will be tested against a number real and generated games in the GitLab assessment pipeline. Your program will be also tested against incomplete (but yet valid) games, and will be also tested against invalid games.

## Task 2

### Overview

In this task, you will extend the `print_scoreboard` function to print a visually formatted scoreboard. The scoreboard should produce output the same as the provided examples _below_, with rows displaying frame rolls and their cumulative scores, enclosed within a nicely formatted table. The function must handle both complete and incomplete games, as well as cases with multiple games passed as input. An an example is below:


```
$ ./task2 547-9/5/8-X5/XX5/X
+-----------------------------------------+
|5 4|7 -|9 /|5 /|8 -|X  |5 /|X  |X  |5 / X|
|  9| 16| 31| 49| 57| 77| 97|122|142|  162|
+-----------------------------------------+
```

The first row and last row are border of a table made by mostly `-` (minus) characters. Just the first and last one are `+` (plus) characters. The second line should print each roll for each frame (if a roll is missing, a ` ` should be used instead). The third row prints the score for each frame aligned to the right: this can be simply achieved by using  `%3d` (or `%5d` for the last frame) inside your printf format string. This will ensure the printed integer occupies `3` (or `5`) characters with a right alignment using spaces to pad if needed.

The following example show you what happens with multiple or incomplete games:

```
$ ./task2 7-5/xxxxxx71xxx xxxxxxxxxxxx xx8-6-7/
+-----------------------------------------+
|7 -|5 /|x  |x  |x  |x  |x  |x  |7 1|x x x|
|  7| 27| 57| 87|117|147|174|192|200|  230|
+-----------------------------------------+
+-----------------------------------------+
|x  |x  |x  |x  |x  |x  |x  |x  |x  |x x x|
| 30| 60| 90|120|150|180|210|240|270|  300|
+-----------------------------------------+
+-----------------------------------------+
|x  |x  |8 -|6 -|7 /|   |   |   |   |     |
| 28| 46| 54| 60| 70|   |   |   |   |     |
+-----------------------------------------+
```

### Details

The `main` function, that must not be changed, invokes the function  `print_scoreboard` for each game parsed from the command line. Therefore you have one function but need it to behave in two different ways, depending if your code is compiled for Task 1 or Task 2. If you have a look at the provided `Makefile`, you will notice that, for Task 2, the file `tpb.c` is compiled with an extra flag `-DSCOREBOARD`. This is a hint to use conditional compilation (as seen in [Week 6](https://moodle.nottingham.ac.uk/mod/page/view.php?id=7664819)). If the code is compiled <ins>without</ins> `-DSCOREBOARD`, the function `print_scoreboard` should behave as in Task 1. If the code is compiled with `-DSCOREBOARD`, the function `print_scoreboard` should print a table with the scoreboard as shown in this task.

If you don't remember what the command-line argument `-DSCOREBOARD` for `gcc` is, the lecture on `Week 6` shows a live example and you can rewatch the video.

Your implementation should handle dynamically allocated memory correctly i.e. free all dynamically allocated memory. As discussed in lectures, a good tool for assessing if a program has handled dynamic memory allocation correctly is `valgrind`. To check your implementation using `valgrind` you can type:

```bash
$ make task2_test_memcheck
```

If your program has correctly handled dynamic memory allocation, the last line of output should read:

```
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

The same rules as those for Task 1 apply for this task.

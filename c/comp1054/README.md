# 2024 COMP1054 Coursework 02

**Submission Deadline:** 10/01/2025 15:00

## Missing Vowels

**WARNING**: As with previous exercises, you must use the supplied skeleton files  to implement your solution. In addition, you should not change the names of the supplied variables. Using a different file, or changing the names risks your coursework failing to be marked by the pipeline.

**Length**: We expect this coursework will take most students around 10—15 hours work to complete, and certainly no more than 20 hours.


**Note**: This coursework contains many components, but it is not necessary to complete **ALL** of them to obtain a good mark for this coursework. Remember a pass mark for the coursework, requires your mark to be **greater than 40%**. If you look at the assessment criteria outlined at the end, then you'll see that a mark of 60% (bordering on a 2:1 degree category) can be achieved by implementing the sub-routines marked 'easy' below.

**Hint**: Make sure you read this document *carefully*. There are lots of hints and tips contained within suggesting how to complete it -- please do not just skim read the description and 'have a go'…

### Description

In this coursework, which is **worth 42% of the final mark for COMP1054**, you are going to implement a simple ARM program that plays a variant of the missing vowels round in the BBC2 quiz show 'Only Connect'. In this, a well-known phrase is taken, the vowels are removed and then the spaces shifted about to form a new string of characters. You then have to guess what the original phrase was. The generated version might be:

	BLH BLH BLH

and you would have to guess that the phrase is:

	BLAH BLAH BLAH

The basic structure of the program is already provided in `MissingVowels.s`. This program calls various sub-routines that implement the functionality required for the game. For this coursework, **you** are required to provide implementations of these sub-routines so that the game can run.

Some of these sub-routines are trivial (such as a string copy routine, or a routine to read a string from the keyboard), while others are more complex (such as an implementation of insertion sort) and some (such as the string compare, and one to redistribute the spaces) are provided for you. A list of the sub-routines required along with an estimation of their complexity (easy, medium and hard) and a full description of what you need to implement can be found below. 

### Submission and Assessment

You will need to fork this repository and then clone it to your Linux system. Submission is then done via a `git commit` and a `git push` as you have previously done for the first COMP1005 exercise. If you click on the **Build** option on the left-hand side of your GitLab interface, you’ll be able to see the marks and feedback for your submission.

You will be given a percentage mark for this exercise, which will be shown along with the feedback in the pipeline. An outline of the mark scheme is found at the end of this document.

You are allowed **up to ten submissions** for this coursework, you may continue to submit after the tenth submission, but your mark will not change unless you have submitted valid ECs.

The final submission made before the deadline (or the tenth submission which ever is earlier) will be taken as your mark for this exercise. Please check that the submission system has correctly received and assigned a mark for your submission  (i.e. that your last submission has a mark displayed alongside it) or you may obtain a mark of zero.

It is not possible to remove a submission. Attempting to do so by deleting the pipeline entry or the commit from the gitlab interface will not remove the mark. If you wish  a previous submission to be counted, then you will need to **resubmit** that version of the code.

### Testing

The main game is implemented in `MissingVowels.s`, and once all the subroutines have been created you should be able to play the game by assembling and running this file. To enable, you to test each of the subroutines individually they have been split up in to separate files (`strcpy.s`, `InsertionSort.s`, and so on…) that are then included into `MissingVowels.s` using the assemblers `include` directive.

At the beginning of each source file, there is a small piece of ARM code that will test your subroutine on its own. This means that you can work on each subroutine separately and test them by running the file in Komodo as usual. Once you have the final functionality completed you can then test they work together by assembling and running `missing_vowels.s`.

There is no need to copy your implementation into other files, this is handled automatically by the `include` directives.

### Coursework Description: Missing Vowels

At a high level, the game works as follows. First, the phrase to be guessed is converted to upper case (i.e. all capitals). Then all the vowels (`A`, `E`, `I`, `O` and `U`) are removed from the string. 

Next, an array is built containing the length of all the 'words' left in the phrase. This array is then sorted using insertion sort. This sorted array is then used to redistribute the spaces in the string so that the 'words' get longer as you reach the end of the string.

Finally, the game can begin and the user is shown the phrase with the missing vowels and redistributed spaces and asked to guess what the word might be. A line of text is read from the user, converted to upper case, and then compared against the original string. IF they match then `Correct` is printed and the game ends. If they do not match, then the program loops and asks the user to guess again. This continues to loop until the user correctly guesses the phrase.

The overall logic described above for the game has been implemented in `MissingVowels.s` and so you **are only required** to provide the functionality for the subroutines below. You should not need to modify `MissingVowels.s` and the pipeline will check this is the case.

There are seven subroutines that you need to implement, which are listed below in order of increasing complexity.

#### isVowel

**Difficulty:** Easy

This sub-routine is very straight-forward. It is called with an ASCII character code in `R0`. You should test whether this character is a vowel (for the purposes of this, we define vowels as  `A`, `E`, `I`, `O` and `U`). If the character is a vowel, then the function should return 1 in `R0`, otherwise the sub-routine should return 0 in `R0`. 

*Hint*: You can get the assembler to work out the ASCII code for you by putting the letter in single quotes, e.g. `MOV R0,#'A'` (or anywhere else you might need to use a literal value).

#### strcpy

**Difficulty:** Easy

This subroutine is the equivalent of `strcpy` in C -- it copies a null-terminated (i.e. zero terminated) string at the address in `R1`, to the address in `R0`. Your subroutine will need to load each byte (as our characters are byte wide) in turn and then store that byte at the new address, incrementing the address for each character. You will stop copying when you have reached the null (zero) byte at the end (which should also be copied).

#### MakeUpper

**Difficulty:** Easy

This subroutine is passed the address of a string in `R0`. This subroutine should iterate over *every* character in the string (until the null terminator is reached), and if it is lower case (i.e. between `a` and `z`) it should convert it to upper case (capitals -- `A` to `Z`). This should be done in place.

**Hint***: ASCII defines the upper and lower cases to be exactly 32 positions apart, so, for example, `A` is 65, and `a` is 97, and so on…

**Another Hint**: Think about the encryption lab exercise…

#### ReadString

**Difficulty:** Easy

This subroutine is passed an address in `R0`, and it should read in characters from the keyboard (using `SWI 1`), displaying them to the user as they are typed, until the RETURN/ENTER key is pressed. Each character typed should be stored, in consecutive *bytes*, in memory starting at the address in `R0` to build up a string containing the typed characters. You will need to ensure that the string is null-terminated, by making sure you *store* a literal zero (i.e. `0`, not the digit zero) at the end after RETURN has been pressed.

The newline character (ASCII code 10) generated by the RETURN key should **not** be stored.

**Hint:** Remember `SWI 1` does not print the characters typed, you will need to print them out…

#### RemoveVowels

**Difficulty:** Medium

This subroutine is used to remove any vowels from the string passed to it in `R0`. This should be done in place, i.e. by overwriting characters in the original string when a vowel is found. The approach you want to take with this is relatively straight-forward, given a string such as:

	HELLO WORLD

We want to iterate over each character, and if the character is a vowel (we can call the `isVowel` subroutine you wrote to test for this, you'll note that `isVowel.s` is `include`d into `RemoveVowels.s` for you) then we start copying the characters to the right over the vowel. So the first vowel, `E`, would be removed first creating the string:
	
	HLL...

Then we get the second vowel, `O`, and we do the same to continue producing:

	HLL W...

and so on, until we end up with:

	HLL WRLD

The code for this is similar to the code you wrote for `strcpy` although the locations are different. We **do not** need to pass over the list multiple times, the program can be implemented in a single pass.

**Hint**: Think about your `strcpy` routine, there's no reason the source and destination strings could not be at the same address. In this case every character would be *load*ed into a register, and then *store*d back into the same memory location. Think about what would happen if you did not store and did not update the destination address if the character loaded from the string was a vowel…


#### CountWordLengths

**Difficulty:** Medium

This subroutine is passed the address of a string in `R0`, and the subroutine should count the length of each word in the string and store it in the array passed to it in `R1`. The array is initially empty (and you can assume enough space is available for any conceivable string passed into it), and you should *store* each length consecutively in the string.

We define a word as being a sequence of non-space characters (with ASCII code 32 being the space character, you can ignore other white space characters such as tabs or newlines), and so we can find these quite simply by just stepping over each byte (characters are 8-bits) in the array until we come to a space. As we iterate over each character, we can increment a counter for each non-space character.
When we encounter a space character, we know we have reached the end of the word, so we can *store* the length into our array (remembering to update the index for the array).

We can then reset the counter to zero, and move on to the next character and start counting the length of the next word.

This approach works most of the time, but it fails if we have multiple spaces in a row or a space at the beginning of the array), since the approach above would lead to a zero length word. The solution here is simple, before we *store* the length of the word in the array, we test if it is  zero. If it **is** zero, then we **do not** store the length in array and carry on with the next character. (This can occur if we run the `RemoveVowels` subroutine above on a string that contains words such as '`A`', or '`I`'.)

You will need to return the number of words you have found in `R0`. This can be done relatively simply, because the index you increment and use to store the word length in the array will increment with each word you have found and so at the end will contain the number of elements you have placed in the array.

#### InsertionSort

**Difficulty:** Hard

The `InsertionSort` subroutine take the address of an array of *integers* (i.e. 4-byte, 32-bit wide values) in `R0`, and the number of elements in `R1`. Your subroutine should then sort the array, in-place, into ascending numerical order using *insertion sort*.

Insertion Sort works by stepping through the array element by element in a loop, growing the sorted list behind it. At each array index, it checks the value in the array against the largest value in the sorted list (which happens to be next to it — i.e. at the previous array index). If the element is larger, it leaves the element in its current position and moves onto the next element. If the element is smaller, it finds the correct position within the sorted list and shuffles all the larger values along to make space and inserts the element into that correct position.

More details about insertion sort can be found on the [Insertion Sort Wikipedia](https://en.wikipedia.org/wiki/Insertion_sort) page, and the file `Insertion.md` in this repository contains a walk through of how a simple array would be sorted.

**Hint**: The shuffling part of this algorithm is not dissimilar to part of the implementation  of `RemoveVowels` except here we shuffle the *integers* to the *right* one place, whereas in `RemoveVowels` you shuffled the characters (i.e. bytes) one place to the left.

**Another Hint**: You'll start sorting at index 1 in the array, since otherwise we would effectively be adding the zeroth element into an empty array.




### Assessment criteria

The table below indicates how the coursework will be marked. Within each boundary, marks will be assigned based on how well the individual subroutines are implemented and how well they follow the ARM procedure call standard (i.e. do they preserve the correct registers).


| Mark      | Expected functionality |
| --------- | ----- |
| <30%      | Some sub-routines have been attempted but they are non-functional or they do not output anything resembling the expected output|
| 30% — 40% | Some sub-routines have been attempted, but while some may produce the expected output the vast majority do not. |
| 40% — 60% | The 'easy' subroutines have been attempted and the majority produce the correct result. |
| 50% — 70% | The 'easy' and 'medium' subroutines have been attempted and are producing the correct result. |
| >70%      | All subroutines have been attempted and producing the expected results in all test cases.|

# Insertion Sort

Insertion Sort is a simple sorting algorithm that builds the final sorted array (or list) one item at a time. Insertion Sort works by stepping through the array element by element in a loop, growing the sorted list behind it. At each array index, it checks the value in the array against the largest value in the sorted list (which happens to be next to it — i.e. at the previous array index). If the element to be tested is *greater than or equal to* the previous entry in the array, it leaves the element in its current position and moves onto the next element. 

On the other hand, if the element is *less than*, it finds the correct position within the
sorted list to insert the value and shifts all the larger values along to make space in the array (overwriting as it does the entry in the array) and inserts the element into the correct position. For example, consider this list:

<pre>
10, 25, 13, 44,  9, 15,  6, 27, 36, 42
</pre>

The algorithm would start by assuming the first element in the array (at index 0, the arrays start with index 0) is already a sorted list (of length one) and so compares the element at index 1 (i.e., the value `25`), with the previous element in the array (at index 0, i.e. `10`). In this case, the element is larger (`25` > `10`) and so it moves on to the next element.

The next element (index 2) is `13` which is less than the previous element, `25`. At this point, it is necessary for the algorithm to insert `13` into the already sorted list (between index 0 and index 1, inclusive). This insertion is performed by assigning the value of index 2 (`13`) to a temporary variable (i.e. a register), and then looping back through the sorted elements in the array shifting the values one element along in the array — i.e if this inner loop’s index is
represented by `j` then the array element at index `j` is set to the value as the array element at index `j−1`. This iterates back over the list until either `j` reaches 0 (i.e. the beginning of the array) or the array element at `j−1` is less than the value to be inserted. At this point, the stored value (`13`) can be inserted into the list at position `j`, like this:

<pre>
10, 25, 13, 44, 9, 15, 6, 27, 36, 42
10, <strong>25</strong>, <strong>25</strong>, 44, 9, 15, 6, 27, 36, 42 shuffle
10, <strong>13</strong>, <strong>25</strong>, 44, 9, 15, 6, 27, 36, 42 insert
</pre>

The next array element (index 3) is then tested. `44` is greater than the previous element (`25`) and so it moves straight on to the fifth element (index 4). `9` is not greater `44` and so it needs to be inserted into the correct position in the list. The same steps are used as before, the inner loop shuffles the elements in the sorted list into their new places and then the value (`9`) is inserted at the correct index:

<pre>
10, 13, 25, 44,  9, 15,  6, 27, 36, 42
<strong>10</strong>, <strong>10</strong>, <strong>13</strong>, <strong>25</strong>, <strong>44</strong>, 15,  6, 27, 36, 42 shuffle
<strong> 9</strong>, <strong>10</strong>, <strong>13</strong>, <strong>25</strong>, <strong>44</strong>, 15,  6, 27, 36, 42 insert
</pre>

This continues until the outer loop reaches the end of the array. This results in the array containing the follow-
ing sorted list:
<pre>
 6,  9, 10, 13, 15, 25, 27, 36, 42, 44
</pre>

The full stages of the sort for this array would follow like this:

**Outer Loop Iteration One**
<pre>
10, 25, 13, 44,  9, 15,  6, 27, 36, 42
</pre>

**Outer Loop Iteration Two**
<pre>
10, 25, 13, 44,  9, 15,  6, 27, 36, 42
10, <strong>25</strong>, <strong>25</strong>, 44,  9, 15,  6, 27, 36, 42 shuffle
10, <strong>13</strong>, <strong>25</strong>, 44,  9, 15,  6, 27, 36, 42 insert
</pre>

**Outer Loop Iteration Three**
<pre>
10, 13, 25, 44,  9, 15,  6, 27, 36, 42
</pre>

**Outer Loop Iteration Four**
<pre>
10, 13, 25, 44,  9, 15,  6, 27, 36, 42
<strong>10</strong>, <strong>10</strong>, <strong>13</strong>, <strong>25</strong>, <strong>44</strong>, 15,  6, 27, 36, 42 shuffle
<strong> 9</strong>, <strong>10</strong>, <strong>13</strong>, <strong>25</strong>, <strong>44</strong>, 15,  6, 27, 36, 42 insert
</pre>

**Outer Loop Iteration Five**
<pre>
 9, 10, 13, 25, 44, 15,  6, 27, 36, 42
 9, 10, 13, <strong>25</strong>, <strong>25</strong>, 44,  6, 27, 36, 42 shuffle
 9, 10, 13, <strong>15</strong>, <strong>25</strong>, 44,  6, 27, 36, 42 insert
</pre>

**Outer Loop Iteration Six**
<pre>
 9, 10, 13, 15, 25, 44,  6, 27, 36, 42
<strong> 9</strong>, <strong> 9</strong>, <strong>10</strong>, <strong>13</strong>, <strong>15</strong>, <strong>25</strong>, <strong>44</strong>, 27, 36, 42 shuffle
<strong> 6</strong>, <strong> 9</strong>, <strong>10</strong>, <strong>13</strong>, <strong>15</strong>, <strong>25</strong>, <strong>44</strong>, <strong>27</strong>, 36, 42 insert
</pre>

**Outer Loop Iteration Seven**
<pre>
 6,  9, 10, 13, 15, 25, 44, 27, 36, 42
 6,  9, 10, 13, 15, 25, <strong>44</strong>, <strong>44</strong>, 36, 42 shuffle
 6,  9, 10, 13, 15, 25, <strong>27</strong>, <strong>44</strong>, 36, 42 insert
</pre>

**Outer Loop Iteration Eight**
<pre>
 6,  9, 10, 13, 15, 25, 27, 44, 36, 42
 6,  9, 10, 13, 15, 25, 27, <strong>44</strong>, <strong>44</strong>, 42 shuffle
 6,  9, 10, 13, 15, 25, 27, <strong>36</strong>, <strong>44</strong>, 42 insert
</pre>

**Outer Loop Iteration Nine**
<pre>
 6,  9, 10, 13, 15, 25, 27, 36, 44, 42
 6,  9, 10, 13, 15, 25, 27, 36, <strong>44</strong>, <strong>44</strong>, shuffle
 6,  9, 10, 13, 15, 25, 27, 36, <strong>42</strong>, <strong>44</strong>, insert
</pre>

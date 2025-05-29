1. what is the purpose of the QUEING-FN in the general search algorithm

its purpose is to act as a queue that stores all the fringe nodes - nodes that have been discovered but not yet processed by the algorithm.

**9/10**
**Explicitly state that the Queing function determines the order in which nodes are processed which is crucial for distinguising between different search strategies**

2. In the general search algorithm what happens if the nodes queue is empty?

The search algorithm returns false becuase no goal state has been reached however there are no more pathways to nodes that haven't been processed left to check therefore no solution can be found, which is why the algorithm will return false as there is no valid path to the goal state from the initial state

3. What deos the Goal-Test[p] on State(node) function check for?

the goal test is performed on the state of a node to check if the current node is a goal node and therefore the algorithm has found the goal state of the algorithm - the aim of the algorithm

4. explain what the action of Remove-Front(nodes) in the general-search algorithm

The remove-front function is used to pop a fringe node from the queue for it to be processed - check if it is the goal state, if not get its child nodes and push them to the queue. This ensures that a breadth-first search is performed as the nodes are checked in the order they are added found in the data structure allowing us to perform 'row-by-row' searching

**9/10**

**be more precise that its the enqueue at end that forces this to be a breadth-first-search**

5. What is the branching factor (b) in the context of search tree evalution

Branching factor is the number of branches/child nodes that any given parent has, this is used to evaluate a search algorithm's time and space complexity and this is used along with the depth of the data structure to calculate a worse case scenario for the time and space complexity of an algorithm on a given tree

6. Define the depth of a search tree as used in complexity evalution.

The depth of a search tree refers to the number of 'rows' that the tree structure contains, ie the number of consecutive branches that can be taken down a single pathway within the tree structure. This is used in complexity analysis because if we are using a breadth-first search then it means that every 'row' within the structure will be checked so by knowing the maximum number of rows within the data structure then if we combine this with the branching factor we can get a worst case scenario for the time and space complexity of a given algorithm on a given data structure

7. What does Big 0 notation represent in complexity theory

Big O notation represents how the space or time needed to process a given data input using a certain algorithm grows in relation to the number of inputs/data points within the data input, it is typically represented as a worst case scenario

8. According to the source material which search strategy uses ENQUEUE-AT-END as its queing function?
breadth-first-search as it adds the most recently discovered nodes to the back of the queue to ensure that the data structure is evaluated on a row-by-row basis

9. list the 4 criteria used to evaluate the tree search techniques

Completeness
time complexity
space complexity
optimality

10. Describe the visual pattern of a breadth-first-search moving through a search space

As the breadth-first-search (BFS) moves through a search space it evaluates the space on a 'row-by-row' basis, this makes it appear as though it is a wave moving through the space because it intially completely checks a row and adds all the child nodes of that row to the back of the search queue, and then as the algorithm moves through the queue it will inherently move onto the next row of values.

98/100
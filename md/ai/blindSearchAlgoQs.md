1. what is the primary data structure used to manage teh nodes to be explored in the general-search algorithm

Generally the primary data structure used to manage nodes that need to be processed is a variation of a queue, for example a BFS will use a standard FIFO queue whereas a DFS will use a LIFO queue and uniform cost search uses a cost-based priority queue to handle which nodes next need to be explored

2. How does the queing function determine the order in which nodes are processed in the general search algorithm

The queuing function determines the order in which new nodes to be explored are evaluated, this means that the queue is respoonsible for handling the way in which the algorithm traverses through the data structure by positiong the nodes to explore in a given way. For exaple we can force a breadth-first-search by adding each fringe node to the back of the queue therefore the fringe nodes are the retrieved on a row by row basis when the first node of the queue is popped

3. In breadth-first-search (BFS) how does the queing function operate to prioritise node expansion

The queuing funcion adds new nodes to be explored to the back of the queue for breadth first search which forces the algorithm to expand all parent nodes (making the algorithm row-wise not depth-wise) before moving onto the child nodes, this then means that the algorithm works layer-by-layer through the data structure being searched.

4. How does the queuing function in a depth-first-search (DFS) differ from the queuing function in a BFS

The queuing function in DFS pushes fringe nodes to the front of the queue therefore forcing depth-wise evaluation before moving across the rows of an algorithm, this means that the branches are explored completely before another branch is then searched. BFS on the other hand has fringe nodes pushed to the back of the queue therefore resulting in row-wise evalution

5. Explain why DFS might not terminate if a goal state does not exist in an infinite branch

DFS may not terminate when exploring an infinite branch if a goal state doesn't exist because DFS explores a single branch completely before moving onto the next branch, therfore if it begins evaluating an infinite branch it will never reach the end and therefore never stop evaluating the given infinite branch as no goal state exists within it.

6. Does DFS guarantee finding the optimal solution to a search problem?

DFS doesn't always guarantee finding the optimal solution, this is because it searches branch-by-branch and terminates as soon as it finds a goal state, so when expanding a branch it may find a goal state solution and terminate however on another branch there may be a shorter/lower cost solution however this was never evaluated as the algorithm terminates upon finding the first solution possible

7. How does uniform cost search decide which node to expand next from the queue

Uniform cost search decides which node to expand next through the use of a total-path-cost based priority queue which means that nodes with the lowest cost will sorted to the front of the queue and therefore will be evaluated first. So in summary is decides based on which fringe node currently has the lowest total path cost

8. In UCS how is the cost of a newly generated node determined

The cost is determined by taking the total cost of the current path that is being taken to find the new node that is having its cost calculate. This means taking the cost of each path currently being used to get the new node from the root node and summing them.

9. Why is a goal state found by UCS not immediately recognized unless it is at the front of the queue

A goal state that isn't at the front of the queue may not be immediately found because the queue is prioritised based on a node's lowest total path cost, therefore if there are nodes that have a lower total path cost than the node with the goal state they will be evaluated first as they may provide a lower cost solution to reach the goal state than that which has currently been discovered. Furthermore the UCS algorithm doesn't process nodes until the are popped from the front of the queue, therfore neither does it perform the goal test on a node until it is popped from the queue to be expanded, so even though the goal state is in the processing queue the algorithm will still see it as a fringe node until it is removed to be expanded, at which point it will discover that the node is a goal state. In summary it's because UCS doesn't perform the goal test on a node until it has been removed from the front of the queue for expansion, and as the queue is a lowest total path cost based priority queue the goal state node may not currently have the lowest total path cost and therefore won't be immediately popped to be expanded.

10. Under what condition can UCS guarantee finding the optimal solution 

It can only guarantee finding the optimal solution if all the path costs within the tree are non-negative
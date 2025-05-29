1. what is the primary data structure used to manage teh nodes to be explored in the general-search algorithm

Generally the primary data structure used to manage nodes that need to be processed is a variation of a queue, for example a BFS will use a standard FIFO queue whereas a DFS will use a LIFO queue and uniform cost search uses a cost-based priority queue to handle which nodes next need to be explored

2. How does the queing function determine the order in which nodes are processed in the general search algorithm

The queuing function determines the order in which new nodes to be explored are evaluated, this means that the queue is respoonsible for handling the way in which the algorithm traverses through the data structure by positiong the nodes to explore in a given way. For exaple we can force a breadth-first-search by adding each fringe node to the back of the queue therefore the fringe nodes are the retrieved on a row by row basis when the first node of the queue is popped

3. In breadth-first-search (BFS) how does the queing function operate to prioritise node expansion

The queuing funcion adds new nodes to be explored to the back of the queue for breadth first search which forces the algorithm to expand all parent nodes (making the algorithm row-wise not depth-wise) before moving onto the child nodes, this then means that the algorithm works layer-by-layer through the data structure being searched.
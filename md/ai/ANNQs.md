1. What is the fundamental idea behind supervised machine learning as applied the Artificial Neural Networks

Instead of the programmer hard coding the rules to produce predictions or classify outputs the model itself adjust weight to control the manipulate the input values and discover the rules of the system, therefore allowing it to identify patterns and rules that may not have existed before.

2. According to the source material what were the two key concepts introduced by McCulloch & Pitts in their 1943 neural network model

- Showed that you can use neurons to construct simple logical systems
- if these logical systems are the wired into one another you can compute any computable problem

3. What significant limitation of the perceptron model was highlighted by the minsky & paper paper in '69 leading to an 'AI winter'

The limitation was that the perceptron can only learn relationships for linearly seperable output values therefore they could not learn the rules of an XOR gate let alone more complex non-linear relationships between input values

4. What is the primary function of a neuron in the context of artificial neural networks

To take multiple weighted inputs and combine them into a single output value that can then be passed onto the next layer of the network or as an output to the user

5. How is the firing of a neuron determined in the basic McCulloch-Pitts model

By adding threshold values to determine whether the combined inputs constitute whether or not a neuron has reached the point at which is should be triggered

6. Explain the difference between the training value and the output value in the context of training a neural network

The training value is the value that is expected to be produced by the model (known as the data is labelled) where as the output is the actual output that we get from the model. 

7. What is the purpose of the learning rate in the weight update formula

To be able to dictate how much the model changes the weight of a given neuron depending on the output, it is useful because it means that we can tailor it to either make larger jumps which will result in finding the global minimum quicker, however it can also mean the model makes changes that are too significant so the model won't actually acheive the best minimum it could. On the other hand we can use it make smaller changes so that the model is more likely to find the absolute minimum however it may also mean the model gets stuck in a local minimum rather than a global minimum

8. What type of functions can a single layer neural network (perceptron) represent 

Any function that has linearly seperable output values

9. What are 3 advantages of neural networks

- can model more complex relationships
- can be more accurate
- can handle a large number of input paramaters (features)

10. What is a Convolutional Neural Network and how does it differ from simpler feed forward networks

A CNN differs from simpler feed-forward networks because it is also a deep network, this means that it has mutliple hidden neuron layers.
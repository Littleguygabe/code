1. what is the priamry characteristic that distiguishes supervised learning from unsupervised learning base on the training data used

Supervised learning uses training data that has a set target value that the predicted output of the model can be comapred to to determin the models accuracy, on the other hand unsupervised learning's training data has not set label therefore the model's aim is to try and distinguish patterns within the data that may not have been seen before

2. Describe the main goal of the supervised learning task

The main goal of supervised learning is to produce a model that can accurately predict outcomes from a set of data inputs based on rules that it has taught itself through the training process

3. What is the primary goal of reinforcement learning

The main goal of reinforcement learning is to train a model based on a reward system to perform desired actions/ learn specific behaviours

4. list the 3 mains types of machine learning tasks
Supervised Learning
un-Supervised Learning
Reinforcement Learning

5. According to the source what are the 3 pillars of machine learning? 
- Model
- Computation
- Data

6. Why is the total dataset typically partitioned into a training set and a tests set in supervised learning

This is done so that once the model has initially been trained on the training data set, it can then be tested using un-seen data to get an unbiased accuracy metric for the performance of the system. We need to perform tests/benchmarks on a seperate set of data because if the model has already seen the data then there is potential it may have just remember the outcome (overfitted) for the given data rather than generating a new outcome based on generalised rules it has generated from the data. This would therefore give an over-inflated accuracy metric for the system.

7. in the context of a dataset for machine learning, what is the difference between a feature and a label/target

A feature is just one of the types of input data that is used to perform machine learning for a given data set, whereas a label/target is the expected output of the system. This means that in supervised learning situations the program will be able to compare the predicted output with the expected output to evaluate the accuracy of the model. In summary it can be seen as features are input data and the target is the desired output data

8. what is data pre-processing and why is it considered time consuming

Data pre-processing is ensuring that the data being which is intended to be used for machine learning is actually in a suitable format for an algorithm to be able to operate on it, for example the algorithm won't be able to understand non-numeric values so they need to be quantified. The reason it's time consuming is because there are multiple steps that need to be performed within the data pre-processing procces which include steps such and quantification of natural language, removing null values and sometimes normalising an attribute of the data set.

9. Give 2 examples of data cleaning steps

- Removing null/NaN values from the data set
- changing natural language into quantitative values, for example good or bad could become 1 and 0 respectively.

1. Define Machine Learning according to tom mitchell's definition, explain what is meant by the experience, task and performance measure

A machine is to learn from experience E with respect to task T and performance metric P if its performance in task T as measured by metric P improves with experience E - essentially if the performance of a machine at a given task improves as it experiences more data then it is said to be learning

2. Compare and contrast the top-down classic approach to AI with the bottom-up approach and discuss the concept of the acquisition bottleneck

The top down approach to Artifical Intelligence is the idea that as a developer we create all the rules for how the system should respond to certain data and then hard code these into the system, the program simply then just looks at the data inputted and passes it through the system of rules to produce an output, typically this is performed on un-labelled data to try and categorise it. On the other hand bottom up approaches try to find the rules for data analysis themselves by looking for patterns within the input data to see if certain sections can be clustered and then have rules generated to be able to identify them

3. What are the 3 pillars of machine learning and briefly explain the significance of each for successful machine learning, Discuss how big data relates to one of these pillars

- model
The model refers to the type of machine learning algorithm is used because certain algorithms are specialised for certain approaches where they perform incredibly badly on other types of data - for example on linear data linear regression is really strong, however for more complex relationships it becomes a lot weaker

- computation
Computation refers to the amount of processing power and memory that is needed for machine learning and how it has changed since the main induction of ML, a general rule-of-thumb is that every 5 years the size of transistors halves/the number of transistors on a chip will doubled

- data
Data refers to the data that is actually used in the training and running of machine learning, this is where big data becomes relevant as models need incredibly large amounts of data to train on to be accurate therefore having access to incredibly large amounts of data is important for companies to produce high quality machine learning models

4. Explain the difference between data mining and machine learning & what is the goal of each

The difference between data mining and data analysis is that data mining aims to produce patterns in the data that are valid and useful whereas machine learning is aimed at producing predictions. So data mining's main aim is to develop patterns from data that already exists - looking to the past - whereas machine learning is uesd to predict for value that haven't happened yet - ie trying to guess what will happen in the future.

5. List the four properties of valid patterns in the context of data mining

- Valid
- Useful
- Novel
- Understandable

7. Describe the main task and goal of supervised learning and how does it differ from unsupervised learning, provide examples of both supervised and unsupervised learning.

The main goal of supervised learning is to develop a model that can accurately predict the label of a piece of data that is inputted. Supervised learning differs from unsupervised learning as supervised learning uses labelled data and therefore when training the model we can directly test its performance by seeing how accurately it predicts the label on data that we already ahve the label for, which can then allow us to compare the model's labels to the actual data labels and hence see how accurately the labels are being applied. Unsupervised learning on the other hand uses unlabelled data, therefore we have no simple way to evaluate the performance of the algorithm at processing the data.

One example of supervised learning is training a neural network on stock market data to be able to understand if the price of a given stock is likely to increase or decrease because we can look at past data and compare the open/close price to label if the stock actually went up or down, then when we begin training the neural network we can evaluate the prediction performance of the stock on historic data as we already know the actual outcome.

On the other hand one example of unsupervised learning would be clustering, this is where an algorithm takes points on a graph and organises them into n clusters of data. However as the data is unlabelled and typically there is incredibly large amounts of it if we are working with big data then it can be hard to actually verify that the model has correctly found clusters of data or not.

in summary supervised learning works on labelled data meaning we can benchmark its performance and easily verify the results, un-supervised learning on the other hand runs on un-labelled data and therefore it can be harder to directly verify the output of the algorithm as we typcially cannot see the rules it has generated for the system either.

8. Explain the concept of re-inforcement learning in the context of supervised learning and provide examples of applications of reinforcement learning

Re-inforcement learning is the concept that when a machine learning algorithm performs a favourable behaviour or produces a favourable output then we 'reward' the system which then encourages that given behaviour to continue and therefore produce better and better outputs. One example of this is evolutionary algorithms where we only carry models that exhibit favourable behaviour onto the next generation rather than all behaviour

9. Outline the general process for machine learning in the context of supervised learning. 
The general proces for machine learning has 3 main steps:
- Data
Initially we need to ensure that the data we are going to use for supervised learning, is cleaned, has no natural and is labelled. This means going through the data set to make sure that there are no missing values within the data and that any natural language is tokenised before being process, for example turning yes and no into 1 and 0

- Model
The second step is defining the model that we are going to use for the machine learning process, this means selecting a model that is specialised for the current task to ensure the most accurate possible outcomes, as selecting a model that is not suited for the current application can harm the performance of your system.

- Training
The third part of the machine learning process is training the model, this means taking our cleaned input data and the defined model we decided to use and then passing in each item of the training data one at a time, comparing the predicted output produced by the model and then adjusting the weights of the algorithm based on a large number of parameters. We then run the system through all of the training data to get the weights defined, then pass in the training data to get the performance of the model on unseeen data which is the true indicator of how accurate it is

10. Describe the purpose of data pre-processing in machine learning, list at least three common data processing steps.

Data pre-processing is performed to ensure that the data being used to train a machine learning algorithm is in a suitable format for the algorithm to analyse.

This means performing a variety of different steps to make sure the data can be used:
- Normalisation
Normalisation scales all the values of a given column between given values - typically 1 and 0 - so that the actual magnitude of the numbers is seperated from the relationship between them.

- Tokenisation
Tokenisation is the process of going through the data set and converting any natural language that can't be processed into values that can be used for analysis, for example we might map yes and no to 1 and 0 respecitvely in the data so the ML algorithm can better understand the input paramaetes

- Removing missing values
In the data set some 'NaN' values may exist which cannot be processed by the machine learning algorithm so in the data pre-processing we need to remove these so we don't get errors when processing. There are multiple methods for handling missing values but a couple of the more common ones are:

-- Dropping the row, this means dropping the row of data that contains the missing value therefore you don't lose any data integrity by subsitituting values in like with other methods of handling, the only issue is if a large number of data points within the data set contain empty values then we may lose a large proportion of the dataset and therefore it can harm the generalisation of the machine learning algorithm so it may not perform as well as if we had more data.

-- Subsituting averages, this method takes either the median or mean (typically median) value for that given data column and then any missing values are replaced with their respective column's median data value, this way we maintain the size of the dataset however as certain values also appear more frequently it can mean that the algorithm may find it harder to find relationships between values.

11. explain what overfitting is

In terms of a model overfitting is when the model specialises to the training data rather than finding concrete relationships and generalising to the data, this means the model will perform well on seen data however when shown unseen data it will typically perform poorly in comparison to the training data

12. Supervised learning tasks can broadly be divided into classification and regression. Explain the difference between these two tasks, mentioning whether each output is categorical or continuous

The differnce between classification and regression is that classification is categorical whereas regression is continuous, this means that given a piece of input data classification will place it in a category, for example with predicting stock price it will classify the given stock to be in 1 of 3 categories - the value will either increase, stay the same or decrease - whereas regression on the other hand would predict how much the value of the stock will change rather than giving it a category.

13. Explain the concept of lienar regression and how a linear regression function is typically represented mathematically and how does polynomial linear regression differ from simple linear regression.

Linear regression is the idea that based on the training data an algorithm tries to plot a linear line function that can then be used to predict the output of an input data value based on the established linear relationship between the 2 components. Typically linear regression is represented as a graph with a function in the form of y = mx+c where y is the output value to be predicted and y is the output value. 

polynomial linear regression differs from simple linear regression as simple linear regression can only plot a linear function and therefore can only accurately map linear relationships between inputs and an output, polynomial linear regression on the other hand has a higher order of magnitude and therefore can represent non-linear polynomial relationships making it more appropriate for more complex relationships with large numbers of paramaters.

14. What is the mean squared error and how is it used in regression training and testing

Mean sqaured error is a performance metric that is used to analyse the accuracy of a data model based on the output it predicted compared to the actual output value. Mean sqaured error is calculated by taking squaring the size of the error between the model predicted output and the actual output and then calculating the mean of every squared error value to get the average error size. By squaring the mean this results in the model becoming more senstive to larger errors than smaller errors which can therefore help optimise training speed as it adds greater encouragement to the model to establish a better fitting function to represent the relationship

15. Discuss the pros and cons of linear regression

Pros: 
Fast training time - as the model is simple it will in turn have faster training times.
Simpler to understand - as the model is simply producing a linear function that predicts an output based on a given input it means that the model is easier to interpret than highly complex models such as neural networks or deep decision trees.

Cons:
Can only plot linear relationships - as the function created is only a simple linear gradient function it means that it cannot plot more complex relationships such as that which can be predicted by polynomial regression models or neural networks.
Sensitive to noise/outliers - as the model uses MSE this means that any major outliers will have a very strong influence on the size of the error for the model so as a result the model tries to minimise that by adjusting the gradient function however this then results in the general trend not being properly plotted as the model is trying to cover every scenario.

16. for decision trees, describe the role of internal nodes, branches and leaf nodes

In decision trees, the internal nodes represent evlautive statements/functions - ie if x>2 - and then the branches from a given node are the operators associated with that internal node, and then once the tree reaches a leaf node for a given data input the class/output associated with that leaf node is the final output of the system/classification of the input value

17. list atleast 3 pros and 3 cons of decision trees

Pros:
easy to implement
easy to interpret
reasonable training time
can handle a large number of features - unlike linear regression

Cons:
can only define simple decision boundaries
an overly complex tree can result in overfitting to the training data
cannot handle complex relationships
problems with large amounts of missing data

1. What is the primary task of supervised learning algorithms

To learn from labelled data to produce a model that can accurately label previously unseen data 

2. Give two example of tasks that well-suited for supervised learning

- classification
- predictions based on previous data

3. Explain the difference between classification and regression in the context of supervised learning labels

The difference between classification and regression is that classification aims to label the data into one category out of a given number of categories and hence the training data must have a label that shows which category each row of data should be in so that the model can evaluate its performance. On the other hand regression generates a scalar value rather than each piece of data being fit into one of many categories, this means that its training data must have the target column just be an output value meaning the algorithm can calculate the mean squared error and therefore adjust its regression line

4. what is the goal when training a regression model

To produce a model that can accurately predict an output value based on a function generated for the regression line and unseen input values

5. what does mean squared error represent in the context of regression model evaluation

MSE shows the difference between the expected output and the predict output, therefore allowing us to see how accurate the predicted output values are from the model based on distance to the correct value. 

6. How does polynomial linear regression differe from simple linear regression

Polynomial linear regression uses a more complex function to allow the model to accurately predict more complex relationships. The function is more complex as it allows us to use a degree that is greater than 1 therefore we can map relationships that are non-linear. Linear regression on the other hand has a simple regression line function so it can only map linear relationships accurately.

7. What is overfitting in machine learning, and how is it related to regression models

Overfitting is when the model specialises to the training data rather than discovering overall trends for the data set, this means that although in training accuracy may seem high once ran on unseen data the model will generally be inaccurate as it hasn't found the general trend for the data, just the pattern of answers for the training dataset. This is related to regression models because when using polynomial regression if we make the algorithm overly complex then the function it can use for the regression line can also be more complex, however this means that at a certain point it becomes so compelx it tailors perfectly to the training data rather than the generlised relationship which is overrfitting.

8. Describe the components of a decision tree model

- Inner Node, decision rules on features
- Branch, course of decision or action - shows the flow between decisions
- Leaf, predicted class label (output)

9. What is the main challenge associated with interpreting complex decision trees

10. What is the purpose of splitting data into training and testing sets

The reason we split a dataset into training and testing sets is because it means that once the model has been trained on the training set then we can use the testing set to get a performance benchmark of the model on un-seen data, this can help to avoid over-inflation of performance metrics as a result of overfitting
# build a convolutional neural network
# create a convolutional function that applies a given filter to a given input matrix and then produces an output after the filter has been applied to every section in the input
# then have a pooling layer that iterates over the filtered input and pools the values together to create a simplified feature map
# then repeat this a few times

# take a dictionary of known output matrices (just examples) that are normalised between 1 and 0
# normalise the output from the pooling and convolutional layers
# then perform dot product between the normalised output and each of the known matrix patterns
# the closer to 1 the output of the dot product the more likely it is that we have a match (could also use euclidean distance)


#perform the filter mask


import numpy as np


def featureFilter(inputMatrix,Filter):

    print(inputMatrix)



def main():
    print('running...')
    

    inputMatrix = inputMatrix.reshape(10,10)
    inputMatrix = np.arange(0,100)

    inputMatrix = np.round(np.random.rand(100),2)


    featureFilter(inputMatrix,2)


if __name__ == '__main__':
    main()
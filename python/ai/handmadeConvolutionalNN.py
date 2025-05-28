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


def featureFilter(inputMatrix,filterMatrix):

    imh,imw = inputMatrix.shape
    fmh,fmw = filterMatrix.shape

    if not (imh%fmh==0) or not (imw%fmw==0):
        print('Cannot completely apply the filter')
        return -1

    print(filterMatrix)
    print(inputMatrix)

    #pad the matrix
    hpad = fmh//2
    wpad = fmh//2

    print(hpad,wpad)



def createRandFilter(size):
    filterMatrix = np.random.rand(size,size)
    return filterMatrix.round()

def main():
    print('running...')
    inputSize = 30

#    inputMatrix = np.arange(0,inputSize**2)
#    inputMatrix = inputMatrix.reshape(inputSize,inputSize)
#    filterMatrix = createRandFilter(6)


    inputMatrix = np.round(np.random.rand(inputSize**2),2)
    inputMatrix = inputMatrix.reshape(inputSize,inputSize)

    filterMatrix = np.array([[1,0,-1],
                             [1,0,-1],
                             [1,0,-1]])

 

    featureFilter(inputMatrix,filterMatrix)


if __name__ == '__main__':
    main()
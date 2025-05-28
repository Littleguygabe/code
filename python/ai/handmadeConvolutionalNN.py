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

class ConvolutionalPoolLayer:
    def __init__(self,filterMatrix) -> None:
        self.filterMatrix= filterMatrix

    def processData(self,matrix):
        matrix = self.featureFilter(matrix)
        matrix = self.applyReLU(matrix)
        matrix = self.normaliseMatrix(matrix)
        matrix = self.pool(matrix)

        return matrix

    def featureFilter(self,inputMatrix):

        imh,imw = inputMatrix.shape
        fmh,fmw = self.filterMatrix.shape

        #pad the matrix
        padSize = fmh//2

        pm = np.pad(inputMatrix,pad_width=padSize,mode='constant')

        output = np.zeros((imh,imw))

        #iterate over the input matrix apply the filter over the given area then sum the 3 by 3 so also get the inputs of the neighbours
        for i in range(0,imw):
            for j in range(0,imh):

                region = pm[i:i+fmh,j:j+fmw]
                output[i,j] = np.sum(region*self.filterMatrix)

        return output

    def applyReLU(self,matrix):
        return np.maximum(0,matrix)
    
    def pool(self,matrix):
        poolSize = 2

        mh,mw = matrix.shape

        outputMatrix = np.zeros((mh//2,mw//2))

        for i in range(0,mw-1,poolSize):
            for j in range(0,mh-1 ,poolSize):
                region = matrix[i:i+poolSize,j:j+poolSize]
                outputMatrix[int(i/2),int(j/2)] = region.max()


        return outputMatrix

    def normaliseMatrix(self,matrix):
        return ((matrix-matrix.min())/(matrix.max()-matrix.min())).round(3)


def createRandFilter(size):
    filterMatrix = np.random.rand(size,size)
    return filterMatrix.round()


def main():
    inputSize = 25

    # inputMatrix = np.arange(0,inputSize**2)
    # inputMatrix = inputMatrix.reshape(inputSize,inputSize)
    # filterMatrix = createRandFilter(6)


    inputMatrix = np.round(np.random.rand(inputSize**2),2)
    inputMatrix = inputMatrix.reshape(inputSize,inputSize)

    filterMatrix = np.array([[1,0,-1],
                             [1,0,-1],
                             [1,0,-1]])


    layer = ConvolutionalPoolLayer(filterMatrix)


    layerOutput = layer.processData(inputMatrix)



    print(layerOutput)


    
if __name__ == '__main__':
    main()
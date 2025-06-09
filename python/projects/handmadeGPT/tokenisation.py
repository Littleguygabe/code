import torch

torch.manual_seed(1337)
trainSize = 0.9
blockSize = 8 #the number of tokens that are gathered for each sample -> context length
batchSize = 4 #how many independent sequences will we process in parallel




with open('input.txt','r') as f:
    text = f.read()
    f.close()

chars = sorted(list(set(text)))
vocabSize = len(chars) #all the possible characters that could appear -> will become the potential outputs from the model

#tokenisation -> converting chars to ints -> be setting each char to its ascii code
stoi = {ch:i for i,ch in enumerate(chars)}
itos = {i:ch for i,ch in enumerate(chars)}
encode = lambda s: [stoi[c] for c in s] #for every letter in the string convert to ascii code
decode = lambda l: ''.join([itos[i] for i in l])
# ^^^ very simple tokenisation

data = torch.tensor(encode(text),dtype=torch.long)

#create the train test split
n = int(trainSize*len(data))
trainData = data[:n]
valData = data[n:]



def getBatch(split):
    data = trainData if split=='train' else valData #dictates which data to sample the tokens from 
    ix = torch.randint(len(data)-blockSize,(batchSize,)) #gets a random index position to sample from, from the dataset that is being used
    # has -blockSize so that we don't get index out of range issues
    # batchSize arg dictates the number of random nums that are generated 

    x = torch.stack([data[i:i+blockSize] for i in ix]) #creates a torch stack of the input sample data for each random position generated in ix
    y = torch.stack([data[i+1:i+blockSize+1] for i in ix]) #gets the next token for each of the input positions so we can analyse the context
    # ^^^ the y allows us to compare the predicted output to the actual output of the system

    return x,y


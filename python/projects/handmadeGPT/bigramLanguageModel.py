from tokenisation import *
import torch
import torch.nn as nn
from torch.nn import functional as F
torch.manual_seed(1337)



# bigram model only looks at the previous token to choose which token to produce next rather than looking at a bunch of the previous tokens
# so not the most intelligent system



class BigramLanguageModel(nn.Module):
    def __init__(self, vocabSize) -> None:
        super().__init__()
        self.token_embedding_table = nn.Embedding(vocabSize,vocabSize)

    def forward(self,idx,targets=None):
        logits = self.token_embedding_table(idx) # returns in format of (Batch,time,channel)

        if targets==None:
            loss = None
        
        else:

            B,T,C = logits.shape
            logits = logits.view(B*T,C) #converts the logits matrix to be a vector that can be used by the cross entropy function

            targets = targets.view(B*T)

            loss = F.cross_entropy(logits,targets)
        # measures the quality of the logits with respect to the target character

        return logits,loss
    
    def generate(self,idx,maxNewTokens):
        for _ in range(maxNewTokens):
            logits,loss = self(idx)
            logits = logits[:,-1,:]
            probs = F.softmax(logits,dim=-1)
            idxNext = torch.multinomial(probs,num_samples=1)
            idx = torch.cat((idx,idxNext),dim=1)

        return idx


m = BigramLanguageModel(vocabSize)


xb,yb = getBatch('train')

logits,loss = m(xb,yb)
print(logits.shape)
print(loss)

idx = torch.zeros((1,1),dtype=torch.long)
print(decode(m.generate(idx,maxNewTokens=100)[0].tolist()))
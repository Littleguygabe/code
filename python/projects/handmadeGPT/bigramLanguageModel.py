from tokenisation import *
import torch
import torch.nn as nn
from torch.nn import functional as F
torch.manual_seed(1337)

class BigramLanguageModel(nn.Module):
    def __init__(self, vocabSize) -> None:
        super().__init__()
        self.token_embedding_table = nn.Embedding(vocabSize,vocabSize)

    def forward(self,idx,targets):
        logits = self.token_embedding_table(idx)

        return logits
    

m = BigramLanguageModel(vocabSize)


xb,yb = getBatch('train')

out = m(xb,yb)
print(out.shape)



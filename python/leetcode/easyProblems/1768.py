class Solution:
    def mergeAlternately(self, word1: str, word2: str) -> str:
        string = ''
        i=0
        while i < (min(len(word1),len(word2))):
            string+=word1[i]
            string+=word2[i]
            i+=1
        
        if len(word1)>len(word2):
            string+=word1[i:]

        elif len(word2)>len(word1):
            string+=word2[i:]

        return string

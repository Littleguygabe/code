class Solution:
    def isPalindrome(self, s: str) -> bool:
        s=s.lower()
        string = ''.join(c for c in s if c.isalnum())
        string2 = ''
        for i in range(len(string)-1,-1,-1):
            string2 += str(string[i])
        
        return string == string2
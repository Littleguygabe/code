class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        anagram_groups = {}
        for word in strs:
            group_key = ''.join(sorted(word))
            if group_key not in anagram_groups:
                anagram_groups[group_key] = [word]

            else:
                anagram_groups[group_key].extend({word})

        return anagram_groups.values()
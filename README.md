# spell-checker-dsa-project
Spell checker project for Data Structures and Algorithms

Authors: Hriday Baghar (15BEC0467), Shashwat Singh (16BCI0180) and Insaf Muhammed Ali (16BCI0144).

 A comparison of performance of data structures in order to store and fetch results from a wordlist.
 
 The following data structures have been used:
 - Array
 - Trie
 - Ternary Search Tree
 
Functionality of code:
- Enter a word and check if it is found in wordlist or not
- If not found, return words with closest Levenshtein Distance (taken as <=2)
- Print time taken to perform search and suggestion

Results:
- Trie saves a great deal of time in scenarios of prefix matching, i.e, it can return words with longest matching prefix. The trie however is not space efficient as each node has 26 pointers (one for each alphabet). Another drawback is that it is not very intuitive as:
  1. If first character is wrong it cannot return accurate suggestion. Eg: iello will not return hello rather it will check if words starting from i or ie.. exist.
  2. If any wrong character is entered it can't always return accurate results. Eg: helld will not return hello if words starting with prefix helld exist in word list.
 - To counter the above problems we can perform full tree traversals but the time taken to perform traversal of the whole trie are not very less compared to that of binary search in array. In order to address space complexity, a ternary search tree gives a much better response as each node has only three pointers.
 - An array search returns good word suggestions as it scans the entire list for the same. Trees still prove better in time complexity but only by a fraction.
 - Trees are hence better suited for search engine autocomplete and not word correction as a lot of words need to be compared to return accurate results, which may not come in the path of traversal.

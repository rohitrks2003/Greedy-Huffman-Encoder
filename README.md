# Greedy-Huffman-Encoder

Greedy Huffman Encoder is an Advanced algorithm which can compress the string so that we have to store less number of bits for the same string. It is preferred for the large strings because the preprocessing will be costly for the small strings.

# Logic for Encoding the string

We can encode the string using the logic of greedy huffman encoder, the tricky part comes when we encode the mapping string which will be used at the decoding end to decode the string.

In mapping string, we split each character contribution in 2 parts
1. first 8 bits will tell us the ASCII value of the character 
2. then 24 bits will tell us the frequency of the character

combining these we will get the frequency of all the characters in the string, then this can be used to decode the string while travelling on the string.

# Logic for Decoding the string

Using the mapping string we can find out the characters and their frequency. Using this data, we can easily make a heap that will store the data for the greedy huffman encoding. Using the heap, we can travel on the encrypted string and decrypt it.
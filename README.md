# Networks-Packet-classifier
Implement an IP lookup table based on a binary trie.
The implementation support three operations:
* ADD/REMOVE 
* inserting/deleting a given prefix with the action to/from the trie 
*FIND a new prefix

 The input is read from a file in the following format: action, prefix, result.
 
 ## Example: 
Input file:  
ADD 255.255.255.0/24 A  
FIND 255.255.255.255  
REMOVE 255.255.255.0/24 A  
    
Expected output:  
Added 255.255.255/24 A at the depth <depth in the binary trie>, total nodes <notal nodes in binary trie>   
Found 255.255.255.255 <found action> at the depth <depth in the binary trie>    
Removed 255.255.255/24 A at the depth <depth in the binary trie> total nodes <notal nodes in binary trie>   

 

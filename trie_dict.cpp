#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;

class TrieNode{
    public:
	bool isLeaf;
        class TrieNode* nextChar[26];			//26 possible next pointers of each character
        TrieNode(){														//initializing all values to defualt
            for(int i=0;i<26;i++){
                nextChar[i]=NULL;
            }
            isLeaf=false;
        }
};

void insert(class TrieNode *root, string word)
{
    int length = word.length();
    int index;
    TrieNode *ptrTrav= new TrieNode;			//creating node to add each character to trie
	ptrTrav=root;
    for (int level=0; level<length; level++)
    {
        index = (int)word[level]-97;			//normalizing ascii value between 0-25 (26 letters in the alphabet)
        if (!ptrTrav->nextChar[index])		
            ptrTrav->nextChar[index] = new TrieNode;	//create new node if not created already for same prefix
 
        ptrTrav = ptrTrav->nextChar[index];
    }
    ptrTrav->isLeaf = true; 				// mark last node as leaf
}

int main(){
    ifstream in("wordlist.txt");
    string word,key;
    TrieNode *root= new TrieNode;
    while(in){															//read all words from wordlist and store in trie
        in>>word;
        insert(root,word);
    }
    in.close();
    cout<<"Trie Construction Successful"<<endl;
    cout<<"Enter the word to be searched for : ";
    cin>>key;
    return 0;
}

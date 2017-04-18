#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<chrono>		//compile using -std=c++11
using namespace std;

class TrieNode{
    public:
	bool isLeaf;
	string Word;
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
    ptrTrav->isLeaf = true;				// mark last node as leaf
    ptrTrav->Word=word;
}
void find(string key,int pos, class TrieNode *root){
    if((key != root->Word) && (root->nextChar[key[pos]-97] != NULL))
        find(key,pos+1,root->nextChar[key[pos]-97]);
    else if(key==root->Word){
        cout<<"The spelling of the word '"<<root->Word<<"' is correct"<<endl;
        //found=1;
	}
	else{
		cout<<key<<" not found!"<<endl;
	}
}
bool search(class  TrieNode *root, string key)
{
    int level;
    int length = key.length();
    int index;
    struct TrieNode *ptrTrav = root;
 
    for (level = 0; level < length; level++)
    {
        index = (int)key[level]-97;
        if (!ptrTrav->nextChar[index])
            return false;
 
        ptrTrav= ptrTrav->nextChar[index];
    }
    return (ptrTrav!= NULL && ptrTrav->isLeaf);
}
int main(){
    ifstream in("wordlist.txt");
    string word,key;
    long long ctr=0;
    TrieNode *root= new TrieNode;
    while(in){										//read all words from wordlist and store in trie
        in>>word;
        ctr++;
        insert(root,word);
    }
    in.close();
    cout<<"Trie Construction Successful, "<<ctr<<" words available"<<endl;
    int ch=1;
    while(ch!=0){
	    cout<<"Enter the word to be searched for : ";
	    cin>>key;
	    auto start = chrono::high_resolution_clock::now();
		find(key,0,root);
		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		long long nano = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
		cout<<nano<<" ns taken to perform operation"<<endl;
		cout<<"Press 0 to exit 1 to continue"<<endl;
		cin>>ch;
	}
	return 0;
}

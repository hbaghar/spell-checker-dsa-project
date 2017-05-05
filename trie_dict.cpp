#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<chrono>		//compile using -std=c++11
#define MIN(x,y) ((x) < (y) ? (x) : (y))
int d[100][100];
using namespace std;

class TrieNode{
    public:
	bool isLeaf;
	string Word;
        class TrieNode* nextChar[26];			//26 possible next pointers of each character
        TrieNode(){								//initializing all values to defualt
            for(int i=0;i<26;i++){
                nextChar[i]=NULL;
            }
            isLeaf=false;
        }
};

int LD(string a, string b)
{
    int i,j,m,n,temp,tracker;

    m = a.length();
    n = b.length();

    for(i=0;i<=m;i++)
    d[0][i] = i;
    for(j=0;j<=n;j++)
    d[j][0] = j;

    for (j=1;j<=m;j++)
    {
        for(i=1;i<=n;i++)
        {
            if(a[i-1] == b[j-1])
            {
                tracker = 0;
            }
            else
            {
                tracker = 1;
            }
            temp = MIN((d[i-1][j]+1),(d[i][j-1]+1));
            d[i][j] = MIN(temp,(d[i-1][j-1]+tracker));
        }
    }
    return(d[n][m]);
}

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
void printall(class TrieNode * root, string key){
    for(int i=0;i<26;i++){
        if(root->nextChar[i]!=NULL){
            printall(root->nextChar[i],key);
        }
	}
    if(root->Word != "")
		if(LD(root->Word,key)==1)
			cout<<" -> "<<root->Word<<endl;
}
void suggest(string key,int pos, class TrieNode * root){
	int index=(int)key[pos]-97;
    if((key != root->Word)&&(root->nextChar[index] != NULL)){
            suggest(key,pos+1,root->nextChar[index]);
    }
    else{
		printall(root,key);
	}
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
		bool found= search(root,key);
		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		long long nano = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
		cout<<nano<<" ns taken to perform operation"<<endl;
		auto start1 = chrono::high_resolution_clock::now();
		if(!found)
			suggest(key,0,root);
		auto elapsed1 = std::chrono::high_resolution_clock::now() - start1;
		long long nano1 = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed1).count();
		cout<<nano1<<" ns taken to perform operation"<<endl;
		cout<<"Press 0 to exit 1 to continue"<<endl;
		cin>>ch;
	}
	return 0;
}

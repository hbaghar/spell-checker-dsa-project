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
        TrieNode(){								//initializing all values to defualt
            for(int i=0;i<26;i++){
                nextChar[i]=NULL;
            }
            isLeaf=false;
        }
};
size_t LD(const std::string &s1, const std::string &s2)
{
  const size_t m(s1.size());
  const size_t n(s2.size());
  if( m==0 ) return n;
  if( n==0 ) return m;
  size_t *costs = new size_t[n + 1];
  for( size_t k=0; k<=n; k++ ) costs[k] = k;
  size_t i = 0;
  for ( std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i )
  {
    costs[0] = i+1;
    size_t corner = i;
    size_t j = 0;
    for ( std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j )
    {
      size_t upper = costs[j+1];
      if( *it1 == *it2 )
      {
		  costs[j+1] = corner;
	  }
      else
	  {
		size_t t(upper<corner?upper:corner);
        costs[j+1] = (costs[j]<t?costs[j]:t)+1;
	  }
      corner = upper;
    }
  }
  size_t result = costs[n];
  delete [] costs;

  return result;
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
		if(LD(root->Word,key)<=2)
			cout<<" -> "<<root->Word<<endl;
}
void suggest(string key,int pos, class TrieNode * root){
	int index=(int)key[pos]-97;
    if(/*(key != root->Word) &&*/ (root->nextChar[index] != NULL)){
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

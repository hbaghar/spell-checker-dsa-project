#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#define MAX 50
#define MIN(x,y) ((x) < (y) ? (x) : (y))

// A Naive recursive C++ program to find minimum number
// operations to convert str1 to str2
#include<bits/stdc++.h>
int d[100][100];
// Utility function to find minimum of three numbers
int min(int x, int y, int z)
{
   return min(min(x, y), z);
}

int editDist(char a[25], char b[25])
{
    int i,j,m,n,temp,tracker;

    m = strlen(a);
    n = strlen(b);

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

// A node of ternary search tree
struct Node
{
    char data;

    // True if this character is last character of one of the words
    unsigned isEndOfString: 1;

    struct Node *left, *eq, *right;
};

// A utility function to create a new ternary search tree node
struct Node* newNode(char data)
{
    Node* temp = new Node;
    temp->data = data;
    temp->isEndOfString = 0;
    temp->left = temp->eq = temp->right = NULL;
    return temp;
}

// Function to insert a new word in a Ternary Search Tree
void insert(struct Node** root, char *word)
{
    // Base Case: Tree is empty
    if (!(*root))
        *root = newNode(*word);

    // If current character of word is smaller than root's character,
    // then insert this word in left subtree of root
    if ((*word) < (*root)->data)
        insert(&( (*root)->left ), word);

    // If current character of word is greate than root's character,
    // then insert this word in right subtree of root
    else if ((*word) > (*root)->data)
        insert(&( (*root)->right ), word);

    // If current character of word is same as root's character,
    else
    {
        if (*(word+1))
            insert(&( (*root)->eq ), word+1);

        // the last character of the word
        else
            (*root)->isEndOfString = 1;
    }
}
	
// A recursive function to traverse Ternary Search Tree
void traverseTSTUtil(struct Node* root, char buffer[25], int depth,char key[25])
{
    if (root)
    {
        // First traverse the left subtree
        traverseTSTUtil(root->left, buffer, depth,key);

        // Store the character of this node
        buffer[depth] = root->data;
        if (root->isEndOfString)
        {
            buffer[depth+1] = '\0';
            if(editDist(buffer,key)==1)
               cout<<"\n"<< buffer;
        }
        // Traverse the subtree using equal pointer (middle subtree)
        traverseTSTUtil(root->eq, buffer, depth + 1,key);

        // Finally Traverse the right subtree
        traverseTSTUtil(root->right, buffer, depth,key);
    }
}

// The main function to traverse a Ternary Search Tree.
// It mainly uses traverseTSTUtil()
void traverseTST(struct Node* root,char key[25])
{
    char buffer[25];
    traverseTSTUtil(root, buffer, 0,key);
}

// Function to search a given word in TST
int searchTST(struct Node *root, char *word)
{
    if (!root)
        return 0;

    if (*word < (root)->data)
        return searchTST(root->left, word);

    else if (*word > (root)->data)
        return searchTST(root->right, word);

    else
    {
        if (*(word+1) == '\0')
            return root->isEndOfString;

        return searchTST(root->eq, word+1);
    }
}

int main(){

    ifstream in("wordlist.txt");
    char word[25],key[25];
    Node *root=NULL;
    while(in){
        in>>word;
        insert(&root,word);
    }
    in.close();
    cout<<endl<<"Ternary Search Tree Construction Successful"<<endl;
    int ch=1;
    int found=-1;
    while(ch!=0){
	    cout<<"Enter the word to be searched for : ";
	    cin>>key;
	    (searchTST(root,key))?found=1:found=0;
	    auto start = chrono::high_resolution_clock::now();
	    if(!found){
			cout<<key<<" not found\n\nDid you mean:"<<endl;
			traverseTST(root,key);
		}
		else
			cout<<key<<" was found!"<<endl;
		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		long long nano = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
		cout<<endl<<endl<<nano<<" us taken to perform operation"<<endl;
		cout<<"Press 0 to exit 1 to continue"<<endl;
		cin>>ch;

	}
    return 0;
} 

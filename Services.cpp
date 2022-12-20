#include<bits/stdc++.h>
#include<fstream>
using namespace std;


// ---------------------------------------------------------------------------------------------------------------------------//

/*
     This code contains all the services                                            Encoding The string 
*/

struct TreeNode
{
	int countOfCharacters;
	bool isLeaf;
	int asciiValue;
	TreeNode* leftNode;
	TreeNode* rightNode;
};

TreeNode* createNode(bool leaf,int asciiValue)
{
	TreeNode* node=new TreeNode();
	node->countOfCharacters=0;
	node->leftNode=NULL;
	node->rightNode=NULL;
	node->isLeaf=leaf;
	node->asciiValue=asciiValue;
	return node;
}

void travellingTheTree(TreeNode* node,map<char,string>& mapping,string& path)
{
	// checkwhether the current node is leaf or not
	if(node->isLeaf)
	{
		char currentCharacter=(char)node->asciiValue;
		mapping[currentCharacter]=path;
	}
	else
	{
		path+='0';
		travellingTheTree(node->leftNode,mapping,path);
		path.pop_back();
		path+='1';
		travellingTheTree(node->rightNode,mapping,path);
		path.pop_back();
	}
}

string convertToBinary(int x,int requiredLength)
{
	string binaryString="";
	for(int i=requiredLength-1;i>=0;i--)
	{
		int curr=1<<i;
		if(x&curr)
		{
			binaryString+='1';
		}
		else 
		{
			binaryString+='0';
		}
	}
	return binaryString;
}

TreeNode* createTree(map<int,int> frequencyOfCharacters)
{
	
	priority_queue<pair<pair<int,int>,TreeNode*>,vector<pair<pair<int,int>,TreeNode*>>, greater<pair<pair<int,int>,TreeNode*>>> pq;
	TreeNode* root;
	int time=0;
	for(auto x:frequencyOfCharacters)
	{
		int frequency=x.second;
		TreeNode* currentNode=createNode(true,x.first);
		currentNode->countOfCharacters=frequency;
		pq.push(make_pair(make_pair(frequency,time),currentNode));
		root=currentNode;
		time++;
	}
	
	if(pq.size()==1)
	{
		TreeNode* currentNode=createNode(false,-1);
		root=currentNode;
		root->leftNode=pq.top().second;
		root->rightNode=NULL;
		return root;
	}
	
	
	while(pq.size()>1)
	{
		pair<pair<int,int>,TreeNode*> tempNode1,tempNode2;
		TreeNode* node1;
		TreeNode* node2;
		tempNode1=pq.top();
		pq.pop();
		tempNode2=pq.top();
		pq.pop();
		
		node1=tempNode1.second;
		node2=tempNode2.second;
		
		int totalCharacters=node1->countOfCharacters+node2->countOfCharacters;
		TreeNode* currentNode=createNode(false,-1);
		currentNode->countOfCharacters=totalCharacters;
		currentNode->leftNode=node1;
		currentNode->rightNode=node2;
		root=currentNode;
		
		pq.push(make_pair(make_pair(totalCharacters,time),currentNode));
		time++;
	}
	
	return root;
}

int binaryToDecimal(string binaryString)
{
	int numberOfBits=binaryString.length();
	int value=0;
	for(int i=numberOfBits-1;i>=0;i--)
	{
		int power=1<<i;
		if(binaryString[numberOfBits-i-1]=='1')
		{
			value+=power;
		}
	}
	return value;
}

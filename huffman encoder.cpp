#include<bits/stdc++.h>
#include<fstream>
using namespace std;


// ---------------------------------------------------------------------------------------------------------------------------//

/*
                                                 Encoding The string 
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

pair<string,string> encode(string data)
{
	map<int,int> frequencyOfCharacters;
	for(auto x:data)
	{
		int asciiValue=int(x);
		frequencyOfCharacters[asciiValue]++;
	}
	
	TreeNode* root=createTree(frequencyOfCharacters);
	
	// Since we have the root, we can use it to store the vlaues in a map to use accordingly
	
	map<char,string> mapping;
	string path="";
	travellingTheTree(root,mapping,path);
	string encodedString="";
	string mappingString="";
	
	for(auto x:data)
	{
		encodedString+=mapping[x];
	}
	
	for(auto x:frequencyOfCharacters)
	{
		
		int asciiValue=x.first;
		int frequency=x.second;
		
		string binaryValueOfAscii=convertToBinary(asciiValue,8);
		string binaryValueOfFrequency=convertToBinary(frequency,24);
		mappingString+=binaryValueOfAscii;
		mappingString+=binaryValueOfFrequency;
	}
	
	/*
	int bitSaved=(8*data.length())-encodedString.length()-mappingString.length();
	cout<<"We saved "<<bitSaved<<" bits\n";
	*/
	
	return {encodedString,mappingString};
	
}



// ---------------------------------------------------------------------------------------------------------------------------//

/*
                                                 Decoding The string 
*/

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

string decode(string encodedString,string mappingString)
{
	int lengthOfMappingString=mappingString.length();
	map<int,int> frequencyOfCharacters;
	for(int i=0;i<lengthOfMappingString;i+=32)
	{
		string asciiValueBinaryString=mappingString.substr(i,8);
		string frequencyBinaryString=mappingString.substr(i+8,24);
		
		int asciiValue=binaryToDecimal(asciiValueBinaryString);
		int frequency=binaryToDecimal(frequencyBinaryString);
		frequencyOfCharacters[asciiValue]=frequency;
	}
	
	TreeNode* root=createTree(frequencyOfCharacters);
	
	int lengthOfEncodedString=encodedString.length();
	TreeNode* currentNode=root;
	string decodedString="";
	for(int i=0;i<lengthOfEncodedString;i++)
	{
		if(encodedString[i]=='0')
		{
			currentNode=currentNode->leftNode;
		}
		else 
		{
			currentNode=currentNode->rightNode;
		}
		
		if(currentNode->isLeaf)
		{
			char ascii=char(currentNode->asciiValue);
			decodedString+=ascii;
			currentNode=root;
		}
	}
	return decodedString;
}


// ---------------------------------------------------------------------------------------------------------------------------//

/*
                                                 Taking input in the main function 
*/

signed main()
{
    // first we will take input as file
    fstream  file;
	file.open("C:/Users/rks20/Desktop/Greedy huffman encoder/input.txt", ios::out | ios::in );
	string data;
	getline(file,data);
	pair<string,string> encodedData=encode(data);
	string encodedString=encodedData.first;
	string mappingString=encodedData.second;
	
	// now we have the encodedString and mapping string that will tell us the frequency of the charaters, so that we can make the tree again 
	
	string decodedString=decode(encodedString,mappingString);
	cout<<decodedString<<"\n";
	
}
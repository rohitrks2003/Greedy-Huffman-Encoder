#include "Services.cpp"

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


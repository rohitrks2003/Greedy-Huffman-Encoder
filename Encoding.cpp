#include "Decoding.cpp"

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


signed main()
{
    string data;
	getline(cin,data);
	pair<string,string> encodedData=encode(data);
	string encodedString=encodedData.first;
	string mappingString=encodedData.second;
	
	// now we have the encodedString and mapping string that will tell us the frequency of the charaters, so that we can make the tree again 
	
	string decodedString=decode(encodedString,mappingString);
	cout<<decodedString<<"\n";
	
}
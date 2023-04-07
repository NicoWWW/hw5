#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
#endif


using namespace std;

// Add prototypes of helper functions here
std::set<std::string> wordleHelper(string& prefix, const string& in, const string& floating);
 
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> allCombos;
		std::string prefix = "";

		if (in == prefix){
			return allCombos;
		}

		allCombos = wordleHelper(prefix, in, floating);

		std::set<std::string> output;
    for(std::set<std::string>::iterator it = allCombos.begin(); it != allCombos.end(); ++it){
        if(dict.find(*it) != dict.end()){
          output.insert(*it);
        }
    }

		return output;
}

// Define any helper functions here
std::set<std::string> wordleHelper(string& prefix, const string& in, const string& floating){
	set<string> output;
	
	if((in.size()-prefix.size())==1){ 
		if(floating.size()==1){ 
			std::string temp = prefix + floating;
			set<string> t = {temp};
			return t;
		}
		else if(in[in.size()-1] != '-'){ 
			std::string temp = prefix + in[in.size()-1];
			std::set<std::string> t = {temp};
			return t;
		}
		else{ 
			std::set<std::string> newWord;
			for(char letter = 'a'; letter <= 'z'; letter++){
				std::string temp = prefix + letter;
				newWord.insert(temp);
			}
			return newWord;
		}
	}

	else{
		unsigned int x = prefix.size(); 
		unsigned int dashCount = 0;
		while(x!=in.size()){
			if(in[x]=='-'){
				dashCount++;
			}
			x++;
		}

		if(in[prefix.size()] != '-'){
			std::string temp = prefix + in[prefix.size()];
			output = wordleHelper(temp, in, floating);
		}

		else if(floating.size() == dashCount){
			for(unsigned int i = 0; i < floating.size(); i++){ 
				std::string newFloat = floating.substr(0, i) + floating.substr(i+1);
				std::string temp = prefix + floating[i];
				std::set<std::string> results = wordleHelper(temp, in, newFloat);
				output.insert(results.begin(), results.end());
			}

		}

		else{
			for(char letter = 'a'; letter <= 'z'; letter++){
				if(floating.find(letter) == string::npos){ 
					std::string temp = prefix + letter; 
					std::set<std::string> results = wordleHelper(temp, in, floating);
					output.insert(results.begin(), results.end());
				}
				else{ 
					int index = floating.find(letter);
					std::string newFloat = floating.substr(0, index) + floating.substr(index+1);
					std::string temp = prefix + letter;
					std::set<std::string> results = wordleHelper(temp, in, newFloat);
					output.insert(results.begin(), results.end());
				}
			}
		}
	}
	return output;
} 

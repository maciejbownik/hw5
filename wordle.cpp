#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(string word, string floating, int pos, const set<string>& dict, set<string>& results);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		set<string> results;

		wordleHelper(in, floating, 0, dict, results);

		return results;
}

// Define any helper functions here

void wordleHelper(string word, string floating, int pos, const set<string>& dict, set<string>& results){
	if (word.length() == pos){
		if(dict.count(word) > 0 and floating.empty()){
			results.insert(word);
		}
		return;
	}

	if(word[pos] != '-'){
		wordleHelper(word, floating, pos + 1, dict, results);
		return;
	}

	for(int i = 0; i < floating.length(); i++){
		char floatChar = floating[i];

		string remainingFloat = floating;

		remainingFloat.erase(i, 1);

		string newWord = word;

		newWord[pos] = floatChar;

		wordleHelper(newWord, remainingFloat, pos + 1, dict, results);
	}

	if (word.length() - pos > floating.length()){
		for(char c = 'a'; c <= 'z'; c++){
			bool is_floating = false;
			for(int i = 0; i < floating.length(); i++){
				if(c == floating[i]){
					is_floating = true;
					break;
				}
		}

			if(!is_floating){
				string newWord = word;
				newWord[pos] = c;
				wordleHelper(newWord, floating, pos + 1, dict, results);
			}
		}
	}
}

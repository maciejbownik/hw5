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
void wordleHelper(const string& word,const string& floating, size_t pos, const set<string>& dict, set<string>& results);
int dashesRemain(string input, int index);


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

void wordleHelper(const string& word,const string& floating, size_t pos, const set<string>& dict, set<string>& results){
	size_t dashes = dashesRemain(word, pos);

	if(floating.length() > dashes){
		return;
	}

	if(dashes == 0){
		if((dict.find(word) != dict.end()) and (floating.size() == 0)){
			results.insert(word);
		}
		return;
	}


/*
	if (pos == word.length()){
		if((dict.find(word) != dict.end()) and (floating.size() == 0)){
			results.insert(word);
		}
		return;
	} */

	if(word[pos] != '-'){
		wordleHelper(word, floating, pos + 1, dict, results);
		return;
	}

	for(size_t i = 0; i < floating.length(); i++){
		char floatChar = floating[i];
		string remainingFloat = floating;
		remainingFloat.erase(i, 1);

		string newWord = word;
		newWord[pos] = floatChar;

		wordleHelper(newWord, remainingFloat, pos + 1, dict, results);
	}

	if (floating.length() < dashes){
		for(char c = 'a'; c <= 'z'; c++){
			/*
			bool is_floating = false;
			for(int i = 0; i < floating.length(); i++){
				if(c == floating[i]){
					is_floating = true;
					break;
				}
				*/
				//if(floating.find(c) != string::npos) continue;

				string newWord = word;
				newWord[pos] = c;

				wordleHelper(newWord, floating, pos +1, dict, results);
		}
		/*

			if(!is_floating){
				string newWord = word;
				newWord[pos] = c;
				wordleHelper(newWord, floating, pos + 1, dict, results);
			}
			*/
		}
	}

int dashesRemain(string input, int index){
	int count = 0;
	for(size_t i = index; i < input.length(); i++){
		if(input[i] == '-'){
			count++;
		};
	}
	return count;
}

//}

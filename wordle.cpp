#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "wordle.h"
#include "dict-eng.h"

using namespace std;

// Add prototypes of helper functions here

// Define any helper functions here

// helper function to generate combinations recursively
void generateCombinations(const string& in, const string& floating, int index,
                          string current, set<string>& result, const set<string>& dict) {
    // base case: if the current combination has the same length as the input
    if (index == in.size()) {
        result.insert(current);  // checks if the combination is a valid word and add it to the result set
        return;
    }

    // if the current character is fixed, use it and move to the next position
    if (in[index] != '-') {
        generateCombinations(in, floating, index + 1, current + in[index], result, dict);
    } else {
        // if the current position is not fixed, try all possible floating characters
        for (char c : floating) {
            generateCombinations(in, floating, index + 1, current + c, result, dict);
        }
        // also, try all other valid characters (a-z) if floating characters are not enough
        for (char c = 'a'; c <= 'z'; ++c) {
            if (floating.find(c) == string::npos) {
                generateCombinations(in, floating, index + 1, current + c, result, dict);
            }
        }
    }
}

// primary Wordle function
set<string> wordle(const string& in, const string& floating, const set<string>& dict) {
    set<string> result;

    // start generating combinations from the first position
    generateCombinations(in, floating, 0, "", result, dict);

    // filter out invalid words based on the dictionary
    set<string> validWords;
    for (const string& word : result) {
        if (dict.find(word) != dict.end()) {
            validWords.insert(word);
        }
    }

    return validWords;
}


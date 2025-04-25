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
void wordleHelper(
    const std::string& current,
    const std::string& floating,
    const std::set<std::string>& dict,
    set<string>& results,
    int index);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  set<string> results;
  wordleHelper(in, floating, dict, results, 0);
  return results;
}

// Define any helper functions here
void wordleHelper(
    const std::string& current,
    const std::string& floating,
    const std::set<std::string>& dict,
    set<string>& results,
    int index)
{
  if(index == current.size()){
    if(floating.empty() && dict.find(current) != dict.end()){
      results.insert(current);
    }

    return;
  }

  if (current[index] != '-'){
    wordleHelper(current, floating, dict, results, index + 1);
  }else{
    
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for(size_t i = 0; i <alphabet.size(); ++i){
      char ch = alphabet[i];
      
      string newWord = current;
      newWord[index] = ch;

      bool found = false;
      size_t pos = 0;

      while(pos < floating.size()){
        if(floating[pos] == ch){
          found = true;
          break;
        }
        ++pos;
      }
      std::string newFloating = floating;
      if(found){
        newFloating.erase(pos, 1);
      }

      wordleHelper(newWord, newFloating, dict, results, index +1);
    }
  }
}
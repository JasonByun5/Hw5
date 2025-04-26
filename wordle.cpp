#ifndef RECCHECK
// For debugging
#include <iostream>
#include <string>
// For std::remove
#include <algorithm> 
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"

using namespace std;


// Add prototypes of helper functions here
static int countEmpty(const string& in){
  int cnt = 0;
  for(char c: in){
    if(c == '-'){
      cnt++;
    }
  }

  return cnt;
}

void helper(
  std::string& currentWord,
  const std::string& floating,
  const std::set<std::string>& dict,
  std::set<std::string>& results,
  int index,
  int empty);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  std::set<std::string> results;
  std::string currentWord = in;
  int empty = countEmpty(in);
  helper(currentWord, floating, dict, results, 0, empty);

  return results;
}

void helper(
  std::string& currentWord,
  const std::string& floating,
  const std::set<std::string>& dict,
  std::set<std::string>& results,
  int index,
  int empty){

    int n = currentWord.size();

  if(index == n){
    if(floating.empty() && dict.count(currentWord)){
      results.insert(currentWord);
    }
    
    return;
  }



  if (currentWord[index] != '-'){
    helper(currentWord, floating, dict, results, index + 1, empty);
    return;
  }

  for(char c = 'a'; c<= 'z'; ++c){
    currentWord[index] = c;
    
    size_t pos = floating.find(c);
    if(pos != string::npos){
      string newFloating = floating.substr(0, pos) + floating.substr(pos + 1);
      helper(currentWord, newFloating, dict, results, index + 1, empty - 1);
    }
    else if(empty > (int)floating.size()){
      helper(currentWord, floating, dict, results, index + 1, empty - 1);
    }

    currentWord[index] = '-';
  }


}
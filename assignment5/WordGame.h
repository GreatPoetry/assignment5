
#ifndef WORDGAME_H
#define WORDGAME_H

#include <string>
#include <iostream>
#include <deque>
#include <exception>
#include <set>
#include <ostream>
#include "trienode.hpp"

class Board
{
public:
  Board();
  Board(std::string letters, int nc);
  ~Board();
  void IntializeBoardDebug();
  void setNumRows(const int nr);
  void setNumCols(const int nc);
  int getNumRows() const;
  int getNumCols() const;
  char letterByRC(int r, int c);
  void showBoard();

private:
  std::string letters;
  int numRows;
  int numCols;
};

class InvalidBoard : public std::exception
{
public:
  const char * what () const noexcept 
  {
    return "Mismatch between board letters and number of columns";
  }
};

class Dictionary
{
public:
  Dictionary();
  Dictionary(const std::string &wordFile);
  bool Contains(const std::string word);
  bool IsPrefix(const std::string word);
  void loadWords(const std::string &wordfile);
private:
  Trie vocab;
  std::vector<std::vector<bool>> visited;
};

class WordFinder
{
public:
  WordFinder(const Board &brd, Dictionary &dict);
  void FindWords(int maxLength=9);
  void printResults();
private:
  void resetSearch();
  void search(int r, int c, int maxLength);
  std::vector<std::vector<bool>> visited;
  Board board;
  Dictionary* dict;
  std::set<std::string> foundWords;
  std::string currentStr;
};

#endif

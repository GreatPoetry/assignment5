#include "trienode.hpp"
#include "WordGame.h"

int main()
{
  Board myBoard;
  myBoard.IntializeBoardDebug();
  myBoard.showBoard();

  Dictionary dict1("/Users/monicas/Dropbox/notes-2020/Cpp_prog_712/assignment5/assignment5/WordsList.txt");
  
  WordFinder wf(myBoard, dict1);
  wf.FindWords(9);
  std::cout << "***************" << std::endl;
  wf.printResults();

  return 0;
}


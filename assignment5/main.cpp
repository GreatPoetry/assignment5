#include "trienode.hpp"
#include "WordGame.h"

int main()
{
    // TestResult tr;
    // TestRegistry::runAllTests(tr);
  Board myBoard;
  myBoard.IntializeBoardDebug();
  myBoard.showBoard();
  
//  Board board2("abcd", 2);
//  board2.showBoard();
//
//  try {
//    Board board3("abcde", 2);
//  } catch (const InvalidBoard& e)
//  {
//  std::cerr << e.what();
//  }


  Dictionary dict1("/Users/monicas/Dropbox/notes-2020/Cpp_prog_712/assignment5/assignment5/WordsList.txt");
  
  //WordFinder wf = WordFinder( myBoard, "/Users/monicas/Dropbox/notes-2020/Cpp_prog_712/assignment5/assignment5/WordsList.txt");
  WordFinder wf(myBoard, dict1);
  wf.FindWords();
  std::cout << "***************" << std::endl;
  wf.printResults();

  return 0;
}


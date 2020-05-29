
#include <string>
#include "WordGame.h"
#include <stdexcept>
#include <set>
#include <fstream>

Board::Board() : numCols(0), numRows(0), letters(""){};

Board::Board(std::string letters, int nc)
{
  if (letters.size() % nc != 0) { throw InvalidBoard(); }
  this->letters = letters;
  numCols = nc;
  numRows = letters.size() / nc;
}

Board::~Board(){};

void Board::setNumRows(const int nr)
{
  Board::numRows = nr;
}

void Board::setNumCols(const int nc)
{
  Board::numCols = nc;
}

int Board::getNumRows() const
{
  return Board::numRows;
}

int Board::getNumCols() const
{
  return Board::numCols;
}

void Board::IntializeBoardDebug()
{
  setNumCols(4);
  setNumRows(4);
  
  Board::letters = "apexnotsetinryeg";
}

void Board::showBoard()
{
  auto cnt = 0;
  for(const auto x: Board::letters )
  {
    std::cout << x;
    
    if (++cnt % numCols == 0)
    {
      std::cout << std::endl;
    }
  }
}

char Board::letterByRC(int r, int c)
{
  if (r < 0 || c < 0 || r >= numRows || c >= numCols)
  {
    throw std::out_of_range("Invalid row or column value");
  }
  int index = r * getNumCols() + c;
  if ((index < 0) || (index > numRows * numCols))
  {
    throw std::out_of_range("Indexing beyond board range");
  }
  return letters[index];
}

Dictionary::Dictionary(): vocab() {}

Dictionary::Dictionary(const std::string & wordFile)
{
  loadWords(wordFile);
}

void Dictionary::loadWords(const std::string & wordFile)
{
  std::ifstream file;
  file.open(wordFile);
  if (!file.is_open())
  {
    std::cout << "Cannot find " << wordFile << std::endl;
  }
  std::string word;
  while (file >> word)
  {
    vocab.Insert(word);
  }
  file.close();
}

bool Dictionary::Contains(const std::string word) { return vocab.Contains(word);}
bool Dictionary::IsPrefix(const std::string prefix) { return vocab.IsPrefix(prefix);}





WordFinder::WordFinder(const Board &brd,  Dictionary &d)
{
  board = brd;
  dict = &d;
  visited.resize(board.getNumRows(), std::vector<bool>(board.getNumCols(), 0));
  
}

void WordFinder::printResults()
{
  int cnt = 0;
  for(auto x: foundWords)
  {
    std::cout << x << " ";
    cnt++;
  }
  std::cout << std::endl;
  std::cout << "Number of words found: " << cnt << std::endl;
}

void WordFinder::resetSearch()
{
  for(int row=0;row<board.getNumRows();row++)
  {
    for(int col=0;col<board.getNumCols();col++)
    {
      visited[row][col]=false;
    }
  }
  currentStr = "";
}
void WordFinder::FindWords()
{
  
  for(int row = 0; row < board.getNumRows(); row++)
  {
    for(int col = 0; col < board.getNumCols(); col++)
    {
      resetSearch();
      search(row,col);
    }
  }
}

void WordFinder::search(int r, int c)
{
  visited[r][c] = true;
  std::cout << currentStr << std::endl;
  currentStr.push_back(board.letterByRC(r, c));
  if (dict->Contains(currentStr))
  {
    foundWords.insert(currentStr);
  }
  if (dict->IsPrefix(currentStr))
  {
    for(int row = r-1; row <= r+1; row++)
    {
      for(int col = c-1; col <= c+1; col++)
      {
        if(row >=0 && col >=0 && row < board.getNumRows() && col < board.getNumCols() && !visited[row][col] && currentStr.length() < 9)
        {
          
          search(row, col);
          currentStr.pop_back();
          visited[row][col] = false;
        }
      }
    }
  }
  
}


/*
search(r,c)
  visited(r,c)=true
  if CurrentStr is prefix
    if CurrentStr is word
      add word to set
    for s in all neighbors
      if s not visited
        CurrentStr = CurrentStr + letter at s
        FindWords(r,c)
        Pop off last letter from CurrentStr
        search(r,c) = False
      
 */

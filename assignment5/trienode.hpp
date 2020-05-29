//
//  trienode.hpp
//  assignment4


#ifndef trienode_hpp
#define trienode_hpp

#include <iostream>
#include <vector>
const int kAlphabetSize = 26;



class TrieNode
{
public:
  TrieNode();
  ~TrieNode();
  bool IsWordEnd() const;
  void SetWordEnd();
  TrieNode* AddChild(int position, TrieNode* tn);
  TrieNode* GetChild(int position) const;
private:
  std::vector<TrieNode *> mNodes;
  bool mIsWordEnd;
};

class Trie
{
public:
  Trie();
  void Insert(const std::string & str);
  bool Contains(const std::string & str) const;
  bool IsPrefix(const std::string & str) const;
private:
  TrieNode mNode;
};


#endif /* trienode_hpp */

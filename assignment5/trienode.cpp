//
//  trienode.cpp
//  assignment4

#include "trienode.hpp"

TrieNode::TrieNode()
{
  //create an empty node
  //mNodes.reserve(kAlphabetSize);
  for(auto i=0; i<kAlphabetSize; i++) {mNodes.push_back(nullptr);}
}

TrieNode::~TrieNode()
{
  for(TrieNode* p: mNodes) {delete p;}
}

bool TrieNode::IsWordEnd() const
{
  return mIsWordEnd;
}

void TrieNode::SetWordEnd()
{
  mIsWordEnd = true;
}

TrieNode* TrieNode::AddChild(int position, TrieNode* tn)
{
  mNodes.at(position) = tn;
  return tn;
}

TrieNode* TrieNode::GetChild(int position) const
{
    return mNodes.at(position);
}

Trie::Trie()
{
  // Tries always start as a root node with no children
  mNode = TrieNode();
}



void Trie::Insert(const std::string & str)
{
  //Loop through each character of the string
  //For each each character in the string add a new node if appropriate
  //Mark last node as word end
  TrieNode* currentNode = &mNode;
  for (auto ch: str)
  {
    int index = ch - 'a';
    if (!currentNode->GetChild(index)) { currentNode = currentNode->AddChild(index, new TrieNode);}
    else {currentNode = currentNode->GetChild(index);}
  }
  currentNode->SetWordEnd();
}

bool Trie::Contains(const std::string & str) const
{
  if (str == ""){return false;}
  const TrieNode* currentNode = &mNode;
  for (auto ch: str)
  {
    int index = ch - 'a';
    if (!currentNode->GetChild(index)) { return false;}
    currentNode = currentNode->GetChild(index);
  }
  return currentNode->IsWordEnd();
}

bool Trie::IsPrefix(const std::string & str) const
{
  if (str == ""){return false;}
  const TrieNode* currentNode = &mNode;
  for (auto ch: str)
  {
    int index = ch - 'a';
    if (!currentNode->GetChild(index)) { return false;}
    currentNode = currentNode->GetChild(index);
  }
  return true;
}

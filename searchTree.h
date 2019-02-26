#ifndef __SEARCH_TREE
#define __SEARCH_TREE

#include <vector>

#include "./board.h"

class SearchTreeNode
{
public:
  SearchTreeNode(int _value, Board *_board, int _move, SearchTreeNode * _parent)
  {
    value = _value;
    board = _board;
    move = _move;
    parent = _parent;
    avoid = false;
  }

  ~SearchTreeNode()
  {
    delete board;

    for (int i = 0; i < children.size(); i++)
    {
      SearchTreeNode * child = children[i];
      delete child;
    }
  }

  int getId()
  {
    int id = 0;

    for (int i = 0; i < 9; i++)
    {
      id += (*board)[i] * pow(10, i);
    }

    return id;
  }

  int pow(int a, int b)
  {
    int result = 1;

    for (int i = 0; i < b; i++)
    {
      result *= a;
    }

    return result;
  }

  bool operator==(const SearchTreeNode &other) const
  {
    for (int i = 0; i < board->boardSize; i++)
    {
      if ((*board)[i] != (*other.board)[i])
      {
        return false;
      }
    }

    return true;
  }

  int value;
  Board *board;

  int move;
  bool avoid;

  SearchTreeNode * parent;
  std::vector<SearchTreeNode *> children;
};

class SearchTree
{
public:
  SearchTree(SearchTreeNode *node)
  {
    rootNode = node;
  }

  ~SearchTree()
  {
    delete rootNode;
  }

  SearchTreeNode *rootNode;
};

#endif
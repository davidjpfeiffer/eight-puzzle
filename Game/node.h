#ifndef __NODE
#define __NODE

#include <vector>
#include <cmath>

#include "./board.h"
#include "./algorithm.h"

class Node
{
public:
  Node(int _value, Board *_board, int _move, Node *_parent)
  {
    value = _value;
    board = _board;
    move = _move;
    parent = _parent;

    if (parent != nullptr)
    {
      depth = parent->depth + 1;
    }
    else
    {
      depth = 1;
    }
  }

  ~Node()
  {
    delete board;

    for (int i = 0; i < children.size(); i++)
    {
      Node *child = children[i];
      delete child;
    }
  }

  static Node *createRootNode(Board *board, Algorithm *algorithm)
  {
    return new Node(algorithm->quantifyBoardState(board), board, -1, nullptr);
  }

  int getId()
  {
    int id = 0;

    for (int i = 0; i < 9; i++)
    {
      id += (*board)[i] * std::pow(10, i);
    }

    return id;
  }

  int value, depth, move;
  Board *board;
  Node *parent;
  std::vector<Node *> children;
};

#endif
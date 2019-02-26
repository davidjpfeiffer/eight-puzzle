#ifndef __NODE
#define __NODE

#include <vector>

#include "./board.h"
#include "./algorithm.h"
#include "../Helpers/mathService.h"

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

    for (int i = 0; i < Board::boardSize; i++)
    {
      id += (*board)[i] * MathService::pow(10, Board::boardSize - i - 1);
    }

    return id;
  }

  int value, depth, move;
  static const int SOLUTION_ID = 12345678;
  Board *board;
  Node *parent;
  std::vector<Node *> children;
};

#endif
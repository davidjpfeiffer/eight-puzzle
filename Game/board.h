#ifndef __BOARD
#define __BOARD

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "./invalidMoveException.h"
#include "../Helpers/randomService.h"

class Board
{
public:
  Board(int *board)
  {
    boardState = board;
  }

  Board(const Board &board)
  {
    boardState = getSolvedBoardState();

    for (int i = 0; i < boardSize; i++)
    {
      boardState[i] = board[i];
    }
  }

  ~Board()
  {
    delete[] boardState;
  }

  void print() const
  {
    std::cout << boardState[0] << ' ' << boardState[1] << ' ' << boardState[2] << '\n';
    std::cout << boardState[3] << ' ' << boardState[4] << ' ' << boardState[5] << '\n';
    std::cout << boardState[6] << ' ' << boardState[7] << ' ' << boardState[8] << '\n';
    std::cout << std::endl;
  }

  static Board *getRandomBoard(int difficulty)
  {
    Board *newBoardState = new Board(getSolvedBoardState());
    int previousMove = -1;

    for (int i = 0; i < difficulty; i++)
    {
      std::vector<int> moves = newBoardState->getValidMoves(true);
      int randomMove = moves[randomService.getRandomNumber(0, moves.size() - 1)];

      while (randomMove == previousMove)
      {
        randomMove = moves[randomService.getRandomNumber(0, moves.size() - 1)];
      }

      newBoardState->makeMove(randomMove, true);
      previousMove = randomMove;
    }

    return newBoardState;
  }

  Board *getBoardAfterMove(int move) const
  {
    if (isValidMove(move))
    {
      int *newBoardState = new int[boardSize];

      for (int i = 0; i < boardSize; i++)
      {
        newBoardState[i] = boardState[i];
      }

      Board * newBoard = new Board(newBoardState);
      newBoard->makeMove(move);
      return newBoard;
    }
    else
    {
      throw invalidMoveException;
    }
  }

  void makeMove(int move, bool allowInvalidMove = false)
  {
    if (isValidMove(move) || allowInvalidMove)
    {
      boardState[getEmptySlotIndex()] = boardState[move];
      boardState[move] = 0;
    }
    else
    {
      throw invalidMoveException;
    }
  }

  bool isValidMove(int move) const
  {
    std::vector<int> validMoves = getValidMoves();
    return std::find(validMoves.begin(), validMoves.end(), move) != validMoves.end();
  }

  std::vector<int> getValidMoves(bool ignoreSolved = false) const
  {
    if (isSolved() && ignoreSolved == false)
    {
      return {};
    }

    switch (getEmptySlotIndex())
    {
    case 0:
      return {1, 3};
    case 1:
      return {0, 2, 4};
    case 2:
      return {1, 5};
    case 3:
      return {0, 4, 6};
    case 4:
      return {1, 3, 5, 7};
    case 5:
      return {2, 4, 8};
    case 6:
      return {3, 7};
    case 7:
      return {4, 6, 8};
    case 8:
      return {5, 7};
    }
  }

  int getEmptySlotIndex() const
  {
    int slot;

    for (int i = 0; i < boardSize; i++)
    {
      if (boardState[i] == 0)
      {
        slot = i;
        break;
      }
    }

    return slot;
  }

  bool isSolved() const
  {
    for (int i = 0; i < boardSize; i++)
    {
      if (boardState[i] != i)
      {
        return false;
      }
    }

    return true;
  }

  int operator[](int index) const
  {
    if (index < 0 || index >= boardSize)
    {
      throw std::out_of_range("Array index out of bound");
    }

    return boardState[index];
  }

  static const int boardSize = 9;

private:
  int *boardState;

  static int *getSolvedBoardState()
  {
    int *newBoardState = new int[boardSize];

    for (int i = 0; i < boardSize; i++)
    {
      newBoardState[i] = i;
    }

    return newBoardState;
  }
};

#endif
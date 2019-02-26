#ifndef __GAME_ENGINE
#define __GAME_ENGINE

#include <iostream>
#include <string>
#include <map>

#include "./gameEngineSettings.h"
#include "./board.h"
#include "./algorithm.h"
#include "./node.h"

class GameEngine
{
public:
  GameEngine(GameEngineSettings _settings)
  {
    settings = _settings;
  }

  void play()
  {
    for (int game = 1; game <= settings.numberOfGames; game++)
    {
      Board *randomBoard = Board::getRandomBoard(settings.difficulty);
      solveBoard(randomBoard);
    }
  }

private:
  void solveBoard(Board *board)
  {
    memory.clear();
    Node *rootNode;

    try
    {
      rootNode = Node::createRootNode(board, settings.algorithm);
      generateTree(rootNode);
      Node *solutionNode = getSolutionNode(rootNode);

      if (solutionNode != nullptr)
      {
        printSolution(rootNode, solutionNode);
      }
      else
      {
        std::cout << "Unable to solve this puzzle.\n";
      }
    }
    catch (std::bad_alloc)
    {
      std::cout << "Need more RAM to solve this particular puzzle.\n";
    }
    catch (std::exception e)
    {
      std::cout << "Something went wrong. Unable to solve puzzle.\n";
      std::cout << e.what() << '\n';
    }

    delete rootNode;
    rootNode = nullptr;
  }

  void printSolution(Node *rootNode, Node *solutionNode)
  {
    std::cout << "Solved puzzle in " << solutionNode->depth << " moves.\n";

    if (settings.showMoves)
    {
      std::vector<Node *> path;
      Node *current = solutionNode;

      while (current != rootNode)
      {
        path.insert(path.begin(), current);
        current = current->parent;
      }

      path.insert(path.begin(), rootNode);

      for (int i = 0; i < path.size(); i++)
      {
        path[i]->board->print();
      }
    }
  }

  Node *getSolutionNode(Node *rootNode)
  {
    std::vector<Node *> children = getChildren(rootNode);

    for (int i = 1; i < children.size(); i++)
    {
      if (children[i]->value == 0)
      {
        return children[i];
      }
    }

    return nullptr;
  }

  std::vector<Node *> getChildren(Node *node)
  {
    std::vector<Node *> results;

    if (node->children.size() > 0)
    {
      for (int i = 0; i < node->children.size(); i++)
      {
        Node *child = node->children[i];
        results.push_back(child);
        std::vector<Node *> childResults = getChildren(child);

        for (int j = 0; j < childResults.size(); j++)
        {
          results.push_back(childResults[j]);
        }
      }
    }

    return results;
  }

  void generateTree(Node *rootNode)
  {
    memory[rootNode->getId()] = true;
    generateChildNodes(rootNode);
    bool solutionFound = false;

    std::vector<Node *> children = rootNode->children;

    while (children.size() > 0)
    {
      std::vector<Node *> newChildren;

      for (int i = 0; i < children.size(); i++)
      {
        generateChildNodes(children[i]);

        for (int j = 0; j < children[i]->children.size(); j++)
        {
          newChildren.push_back(children[i]->children[j]);
        }
      }

      children = newChildren;
      newChildren.clear();
    }
  }

  void generateChildNodes(Node *node)
  {
    if (node->children.size() == 0)
    {
      std::vector<int> theoreticalMoves = node->board->getValidMoves();

      for (int i = 0; i < theoreticalMoves.size(); i++)
      {
        int theoreticalMove = theoreticalMoves[i];

        if (node->parent == nullptr || theoreticalMove != node->parent->move)
        {
          Board *theoreticalBoard = node->board->getBoardAfterMove(theoreticalMove);
          int value = settings.algorithm->quantifyBoardState(theoreticalBoard);
          Node *newNode = new Node(value, theoreticalBoard, theoreticalMove, node);
          int newNodeId = newNode->getId();

          if (memory[newNodeId])
          {
            delete newNode;
          }
          else
          {
            memory[newNodeId] = true;
            node->children.push_back(newNode);
          }
        }
      }
    }
  }

  GameEngineSettings settings;
  std::map<int, bool> memory;
};

#endif
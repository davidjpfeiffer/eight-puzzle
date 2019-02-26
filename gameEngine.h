#ifndef __GAME_ENGINE
#define __GAME_ENGINE

#include <iostream>
#include <string>
#include <map>

#include "./board.h"
#include "./algorithm.h"
#include "./searchTree.h"

class GameEngine
{
public:
  bool executeAlgorithm(Algorithm *algorithm)
  {
    int iterations = 0;
    memory.clear();
    Board *board = Board::getRandomBoard(500);

    try
    {
      SearchTreeNode *rootNode = new SearchTreeNode(algorithm->quantifyBoardState(board), board, -1, nullptr);
      memory[rootNode->getId()]++;
      SearchTreeNode *currentNode = rootNode;

      while (currentNode->board->isSolved() == false)
      {
        generateNodesForLookAheadMoves(currentNode, algorithm);
        SearchTreeNode *bestLeaf = getBestChild(currentNode);

        if (bestLeaf == currentNode)
        {
          if (currentNode == rootNode)
          {
            log("This should only happen when the board is unsolvable.", true);
            return false;
          }

          log("Initiating backtrack procedure.");
          currentNode->avoid = true;
          currentNode = currentNode->parent;
        }
        else if (*bestLeaf == *currentNode) // might be able to get rid of this check
        {
          log("Initiating avoidance procedure.");
          bestLeaf->avoid = true;
          currentNode = currentNode->parent;
        }
        else
        {
          currentNode = bestLeaf;
        }

        iterations++;

        if (iterations >= maxIterations)
        {
          log("Unable to solve this puzzle. I got overwhelmed.", true);
          return false;
        }
      }

      printSolution(rootNode, currentNode, iterations);
      return true;
    }
    catch (std::bad_alloc)
    {
      log("Need more RAM to solve this particular puzzle.", true);
      return false;
    }
    catch (std::exception e)
    {
      log("Something went wrong. Unable to solve puzzle.", true);
      log(e.what(), true);
      return false;
    }
  }

private:
  void printSolution(SearchTreeNode *rootNode, SearchTreeNode *solvedNode, int iterations)
  {
    std::vector<SearchTreeNode *> path;
    SearchTreeNode *current = solvedNode;

    while (current != rootNode)
    {
      path.insert(path.begin(), current);
      current = current->parent;
    }

    path.insert(path.begin(), rootNode);

    std::cout << "Solved puzzle in " << path.size() << " moves using " << iterations << " iteration(s).\n";

    for (int i = 0; i < path.size(); i++)
    {
      // path[i]->board->print();
    }
  }

  SearchTreeNode *getFirstNotAvoided(std::vector<SearchTreeNode *> nodes)
  {
    for (int i = 0; i < nodes.size(); i++)
    {
      if (nodes[i]->avoid == false)
      {
        return nodes[i];
      }
    }

    return nullptr;
  }

  SearchTreeNode *getBestChild(SearchTreeNode *node)
  {
    std::vector<SearchTreeNode *> children = getChildren(node);
    SearchTreeNode *best = getFirstNotAvoided(children);

    if (best == nullptr)
    {
      return node;
    }

    for (int i = 1; i < children.size(); i++)
    {
      if (children[i]->value < best->value && children[i]->avoid == false)
      {
        best = children[i];
      }
    }

    return best;
  }

  std::vector<SearchTreeNode *> getChildren(SearchTreeNode *node)
  {
    std::vector<SearchTreeNode *> results;

    if (node->children.size() > 0)
    {
      for (int i = 0; i < node->children.size(); i++)
      {
        SearchTreeNode *child = node->children[i];
        results.push_back(child);
        std::vector<SearchTreeNode *> childResults = getChildren(child);

        for (int j = 0; j < childResults.size(); j++)
        {
          results.push_back(childResults[j]);
        }
      }
    }

    return results;
  }

  void generateNodesForLookAheadMoves(SearchTreeNode *node, Algorithm *algorithm)
  {
    generateChildNodes(node, algorithm);
    bool solutionFound = false;

    std::vector<SearchTreeNode *> children = node->children;

    while (children.size() > 0)
    {
      std::vector<SearchTreeNode *> newChildren;

      for (int i = 0; i < children.size(); i++)
      {
        solutionFound = generateChildNodes(children[i], algorithm);

        for (int j = 0; j < children[i]->children.size(); j++)
        {
          newChildren.push_back(children[i]->children[j]);
        }

        if (solutionFound)
        {
          return;
        }
      }

      children = std::vector<SearchTreeNode *>(newChildren); // try children = newChildren
      newChildren.clear();
    }
  }

  bool generateChildNodes(SearchTreeNode *node, Algorithm *algorithm)
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
          int value = algorithm->quantifyBoardState(theoreticalBoard);
          SearchTreeNode *newNode = new SearchTreeNode(value, theoreticalBoard, theoreticalMove, node);
          int newNodeId = newNode->getId();

          if (memory[newNodeId] == 0)
          {
            memory[newNodeId]++;
            node->children.push_back(newNode);
          }
          else
          {
            delete newNode;
          }

          if (value == 0)
          {
            return true;
          }
        }
      }
    }

    return false;
  }

  void log(std::string message, bool important = false)
  {
    std::cout << message << '\n';
  }

  int maxIterations = 100000;
  std::map<int, int> memory;
};

#endif
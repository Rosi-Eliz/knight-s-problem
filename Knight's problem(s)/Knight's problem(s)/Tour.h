//
//  Tour.h
//  Knight's problem(s)
//
//  Created by Rosi-Eliz Dzhurkova on 13.08.20.
//  Copyright © 2020 Rosi-Eliz Dzhurkova. All rights reserved.
//

#ifndef KNIGHTS_H
#define KNIGHTS_H

#include <utility>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <cstdint>
#include <queue>
#include <math.h>

using std::pair;
using std::make_pair;
using std::vector;
using std::priority_queue;

typedef vector<pair<int,int> > Path;
typedef pair<int,int> Pair;


/** Helper function: adds two pairs of ints */
pair<int,int> operator+(const pair<int,int> & a, const pair<int,int> & b) {
    return make_pair(a.first + b.first, a.second + b.second);
}


// Utilities
const static vector<Pair> translationCoefficients = {{2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, {-1,-2}, {1,-2}, {2,-1}};

vector<Pair> moves(Pair fromPosition)
{
  
    vector<Pair> validMoves;
    for (int i{ 0 }; i <translationCoefficients.size() ; i++)
    {
        Pair move = fromPosition + translationCoefficients[i];
        validMoves.push_back(move);
    }
    
    return validMoves;
}


vector<Pair> legal_moves(int boardSize, Path path, pair<int,int> position)
{
    vector<Pair> allMoves = moves(position);
    vector<Pair> legalMoves;
    for(Pair pair: allMoves)
    {
        bool isWithinBoardSize = pair.first < boardSize && pair.first >= 0 && pair.second < boardSize && pair.second >= 0;
        bool isAlreadyVisited = find(path.begin(), path.end(), pair) != path.end();
        if(isWithinBoardSize && !isAlreadyVisited)
        {
            legalMoves.push_back(pair);
        }
    }
    return legalMoves;
}

double euclidianDistanceFromCenter(int boardSize, Pair pair)
{
    int boardCenter = (boardSize - 1 )/ 2;
    double vectorInitialPoint = boardCenter - pair.first;
    double vectorFinalPoint = boardCenter - pair.second;
    double distance = sqrt(pow(vectorInitialPoint, 2) + pow(vectorFinalPoint, 2));
    return distance;
}


pair<Path,bool> first_tour(int boardSize, Path currentPath)
{
    if(currentPath.empty())
    {
        throw std::runtime_error("Invalid starting position.");
    }
    
    bool traversedAllPositions = currentPath.size() == boardSize * boardSize;
    bool boardSizeIsValid = boardSize > 4 || boardSize == 1;
   
    if(traversedAllPositions)
    {
        return {currentPath, true};
    }
    else if (!boardSizeIsValid)
    {
        return {Path(), false};
    }
    Pair currentPosition = currentPath.back();
    
    auto comparator = [&](Pair& firstPair, Pair& secondPair) {
        size_t firstPairLegalMovesSize = legal_moves(boardSize, currentPath, firstPair).size();
        size_t secondPairLegalMovesSize = legal_moves(boardSize, currentPath, secondPair).size();
        
        if(firstPairLegalMovesSize == secondPairLegalMovesSize)
        {
            double firstPositionEuclidianDistance = euclidianDistanceFromCenter(boardSize, firstPair);
            double secondPositionEuclidianDistance = euclidianDistanceFromCenter(boardSize, secondPair);
            return firstPositionEuclidianDistance < secondPositionEuclidianDistance;
        }
        else
        {
            return firstPairLegalMovesSize > secondPairLegalMovesSize;
        }
    };
    
    priority_queue<Pair, vector<Pair>, decltype(comparator)> adjacentPositions(comparator);
    
    vector<Pair> currentPositionLegalMoves = legal_moves(boardSize, currentPath, currentPosition);
    for(Pair position : currentPositionLegalMoves)
    {
        adjacentPositions.push(position);
    }
    
    if(adjacentPositions.empty())
    {
        throw std::runtime_error("No more valid moves.");
    }
    
    Pair nextPosition = adjacentPositions.top();
    currentPath.push_back(nextPosition);
    return first_tour(boardSize, currentPath);
}


#endif

//
//  Non-attacking knights.h
//  Knight's problem(s)
//
//  Created by Rosi-Eliz Dzhurkova on 13.08.20.
//  Copyright © 2020 Rosi-Eliz Dzhurkova. All rights reserved.
//

#ifndef Non_attacking_knights_h
#define Non_attacking_knights_h
#include "Tour.h"
#include <unordered_map>
using namespace std;

int combineIndices(int i, int j) {
    return i*10+j;
}

struct Location
{
    int row;
    int column;
    bool hasKnight;
    Location(int row, int column, bool hasKnight = false) : row(row), column(column)
    {
        this->hasKnight = hasKnight;
        
    };
    bool operator==(const Location& location)
    {
        return row == location.row && column == location.column;
    }
};


class Board{
public:
    int n;
    int m;
    unordered_map<int, Location*> fields;
    vector<Location*> knightLocations;
    Board(int n, int m) : n(n), m(m)
    {
        for(int i{0}; i < n; i++)
        {
            for(int j{0}; j < m; j++)
            {
                Location* newLocation = new Location(i, j, false);
                fields.emplace(combineIndices(i,j), newLocation);
            }
        }
    };

    Location* getLocation(int row, int col) const {
    unordered_map<int, Location*>::const_iterator bucket = fields.find(combineIndices(row, col));
        if(bucket != fields.end())
            return bucket->second;
        return nullptr;
    };
    
    vector<Location*> moves(Location* fromPosition)
    {
        vector<Location*> validMoves;
        for (int i{ 0 }; i <translationCoefficients.size() ; i++)
        {
            int newRow = fromPosition->row + translationCoefficients[i].first;
            int newColumn = fromPosition->column + translationCoefficients[i].second;
            Location* result = getLocation(newRow, newColumn);
            if(result != nullptr)
                validMoves.push_back(result);
        }
        
        return validMoves;
    }

    
    bool fieldIsInConflict(Location* location)
    {
//        vector<Location*> knightLocations;
//        unordered_map<int, Location*>::const_iterator bucket = fields.begin();
//        for(int i{0}; i < fields.bucket_count(); i++)
//        {
//           if(bucket->second->hasKnight)
//               knightLocations.push_back(bucket->second);
//            ++bucket;
//        }
        for(Location* loc : knightLocations)
        {
            vector<Location*> availableMoves = moves(loc);
            if(find(availableMoves.begin(), availableMoves.end(), location) != availableMoves.end())
                return true;
        }
        return false;
    };
    
    
    void print() const
    {
        for(int i{0}; i < n; i++)
        {
            for(int j{0}; j < m; j++)
            {
                Location* location = fields.at(combineIndices(i,j));
                if(location->hasKnight)
                    cout<<" [K] ";
                else
                    cout<<" [ ] ";
            }
            cout<<endl;
        }
    };
};


int numberOfValidPlacements(int currentMax, Board& board, Location* fromLocation)
{
    //Edge cases:
    if(board.n == 1 || board.m == 1)
        return max(board.n, board.m);
    
    else if (board.m == 2 || board.n == 2)
    {
        int quadrantsTotal = max(board.m, board.n) / 2;
        int populatedQuadrants = quadrantsTotal % 2 == 0? quadrantsTotal / 2 : quadrantsTotal - 2;
        return populatedQuadrants * 4;
    }
    
    vector<Location*> availableLocations = board.moves(fromLocation);
    //shuffle?
    for(Location* location : availableLocations)
    {
        if(!board.fieldIsInConflict(location) && !location->hasKnight)
        {
            location->hasKnight = true;
            board.knightLocations.push_back(location);
            int result = numberOfValidPlacements(currentMax + 1, board, location);
            currentMax = max(result, currentMax);
        }
    }
    return currentMax;
};


#endif /* Non_attacking_knights_h */

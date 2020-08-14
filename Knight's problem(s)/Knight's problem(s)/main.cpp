//
//  main.cpp
//  Knight's problem(s)
//
//  Created by Rosi-Eliz Dzhurkova on 13.08.20.
//  Copyright © 2020 Rosi-Eliz Dzhurkova. All rights reserved.
//
#include "Tour.h"
#include "Non-attacking knights.h"
#include <utility>
#include <algorithm>

using std::make_pair;

#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, const char * argv[]) {
   //Test knight's tour problem
//    for (int dim = 1; dim <= 8; ++dim) {
//        cout << "Looking for tour on a " << dim << " x " << dim << " board\n";
//        auto tour = first_tour(dim, Path{{0,0}});
//
//        if (!tour.second) {
//            cout << "No tour found -- this is okay for boards of size 2,3 or 4 only\n";
//        } else {
//            for (int row = 0; row < dim; ++row) {
//                for (int col = 0; col < dim; ++col) {
//                    cout << std::setw(2);
//                    cout << std::distance(tour.first.begin(),
//                                          std::find(tour.first.begin(), tour.first.end(), make_pair(row,col)));
//                    cout << " ";
//                }
//                cout << endl;
//            }
//        }
//    }
    
    //Test non - attacking knights problem
    int n, m;
    cout<<"Enter board dimensions"<<endl;
    cin>> n;
    cin>> m;
    int result {0};
    int maximum = -INFINITY;
    while(result < maximum)
    {
        Board board = Board(n, m);
        int randomRow = rand() % board.n;
        int randomColumn = rand() % board.m;
        Location* randomLocation = board.fields.at(combineIndices(randomRow, randomColumn));
        result = numberOfValidPlacements(0, board, randomLocation);
        maximum = max(maximum, result);
        board.print();
        
        cout<<endl<<maximum;
        
    }
    
    return 0;
}

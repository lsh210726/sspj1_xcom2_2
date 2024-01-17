#pragma once
#include <utility> // std::pair
#include <stack> // std::stack

typedef std::pair<int, int> Pair;
extern std::stack<Pair> pathStack;
//std::stack<Pair> pathStack;


void PathFind(int grid[20][20], Pair src, Pair dest);

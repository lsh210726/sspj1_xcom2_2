// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AStarPathFinder.h"

#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>



//using namespace std;
//
////전체 격자공간의 크기
//#define ROW 10
//#define COL 10
//
//// Creating a shortcut for int, int pair type
////pair클래스는 두 객체를 하나의 객체로 취급 할 수 있게 묶어주는 클래스, STL에서 데이터 쌍을 표현할 때 사용, <utility>헤더
//typedef pair<int, int> Pair;
//
//// Creating a shortcut for pair<int, pair<int, int>> type
//typedef pair<double, pair<int, int> > pPair;
//
//stack<Pair> pathStack;
//
//
//// A structure to hold the necessary parameters
//struct cell {
//    // Row and Column index of its parent
//    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
//    //부모의 좌표 저장. 부모는 아마 이전 셀의 위치
//    int parent_i, parent_j;
//    // f = g + h
//    //g는 시작부터 현재까지의 거리, h는 현재부터 목적지까지의 거리, f는 g와 h를 더한 전체 경로의 비용
//    double f, g, h;
//};
//
//// A Utility Function to check whether given cell (row, col)
//// is a valid cell or not.
////주어진 좌표의 셀이 존재하는 지 확인하는 함수
//bool isValid(int row, int col)
//{
//    // Returns true if row number and column number
//    // is in range
//    return (row >= 0) && (row < ROW) && (col >= 0)
//        && (col < COL);
//}
//
//// A Utility Function to check whether the given cell is
//// blocked or not
////블록이 막혔는지 아닌지 확인하는 함수. 만약 막히지 않았다면 트루
//bool isUnBlocked(int grid[][COL], int row, int col)
//{
//    // Returns true if the cell is not blocked else false
//    if (grid[row][col] == 1)
//        return (true);
//    else
//        return (false);
//}
//
//// A Utility Function to check whether destination cell has
//// been reached or not
////좌표의 셀이 목적지인지 아닌지 확인하는 함수
//bool isDestination(int row, int col, Pair dest)
//{
//    if (row == dest.first && col == dest.second) // dest의 첫번째가 목적지의 행, 두번째가 열
//        return (true);
//    else
//        return (false);
//}
//
//// A Utility Function to calculate the 'h' heuristics.
////휴리스틱 값 계산 함수. 삼각함수
//double calculateHValue(int row, int col, Pair dest)
//{
//    // Return using the distance formula
//    return ((double)sqrt(
//        (row - dest.first) * (row - dest.first)
//        + (col - dest.second) * (col - dest.second)));
//}
//
//// A Utility Function to trace the path from the source
//// to destination
//// 시작점부터 목적지까지의 경로를 추적해주는 함수
//// 경로 스택 출력 함수
//void tracePath(cell cellDetails[][COL], Pair dest)
//{
//    printf("\nThe Path is ");
//    int row = dest.first;
//    int col = dest.second;
//
//    stack<Pair> Path;//경로 저장 스택
//
//    while (!(cellDetails[row][col].parent_i == row
//        && cellDetails[row][col].parent_j == col)) {//이전 셀의 좌표가 목적지가 아니라면
//        Path.push(make_pair(row, col));//경로 저장 스택에다 셀 좌표 저장
//        int temp_row = cellDetails[row][col].parent_i;
//        int temp_col = cellDetails[row][col].parent_j;
//        row = temp_row;
//        col = temp_col;
//    }
//
//    Path.push(make_pair(row, col));
//    pathStack = Path;
//    while (!Path.empty()) {//경로저장스택이 빌 때까지 내부 값 출력하기
//        pair<int, int> p = Path.top();
//        Path.pop();
//        printf("-> (%d,%d) ", p.first, p.second);
//    }
//
//    return;
//}
//
//// A Function to find the shortest path between
//// a given source cell to a destination cell according
//// to A* Search Algorithm
//// a*길찾기 알고리즘 함수
//void aStarSearch(int grid[][COL], Pair src, Pair dest)
//{
//    // If the source is out of range
//    if (isValid(src.first, src.second) == false) {
//        printf("Source is invalid\n");
//        return;
//    }
//
//    // If the destination is out of range
//    if (isValid(dest.first, dest.second) == false) {
//        printf("Destination is invalid\n");
//        return;
//    }
//
//    // Either the source or the destination is blocked
//    if (isUnBlocked(grid, src.first, src.second) == false
//        || isUnBlocked(grid, dest.first, dest.second)
//        == false) {
//        printf("Source or the destination is blocked\n");
//        return;
//    }
//
//    // If the destination cell is the same as source cell
//    if (isDestination(src.first, src.second, dest)
//        == true) {
//        printf("We are already at the destination\n");
//        return;
//    }
//
//    // Create a closed list and initialise it to false which
//    // means that no cell has been included yet This closed
//    // list is implemented as a boolean 2D array
//    // 가장 가까운 셀 부울 리스트를 선언 후 초기화하기
//    bool closedList[ROW][COL];
//    memset(closedList, false, sizeof(closedList));
//
//    // Declare a 2D array of structure to hold the details
//    // of that cell
//    // 전체 셀의 2차원 배열
//    cell cellDetails[ROW][COL];
//
//    int i, j;
//
//    // 전체 셀의 배열에 기본으로 최대 비용 값을 넣어줌
//    for (i = 0; i < ROW; i++) {
//        for (j = 0; j < COL; j++) {
//            cellDetails[i][j].f = FLT_MAX;
//            cellDetails[i][j].g = FLT_MAX;
//            cellDetails[i][j].h = FLT_MAX;
//            cellDetails[i][j].parent_i = -1;
//            cellDetails[i][j].parent_j = -1;
//        }
//    }
//
//    // Initialising the parameters of the starting node
//    // 시작 노드의 비용 초기화
//    i = src.first, j = src.second;
//    cellDetails[i][j].f = 0.0;
//    cellDetails[i][j].g = 0.0;
//    cellDetails[i][j].h = 0.0;
//    cellDetails[i][j].parent_i = i;
//    cellDetails[i][j].parent_j = j;
//
//    /*
//     Create an open list having information as-
//     <f, <i, j>>
//     where f = g + h,
//     and i, j are the row and column index of that cell
//     Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
//     This open list is implemented as a set of pair of
//     pair.*/
//     // 경로 전체 비용과 행렬을 저장할 리스트
//    set<pPair> openList;
//
//    // Put the starting cell on the open list and set its
//    // 'f' as 0
//    // 전체 비용이 0인 시작 셀을 리스트에 넣기
//    openList.insert(make_pair(0.0, make_pair(i, j)));
//
//    // We set this boolean value as false as initially
//    // the destination is not reached.
//    // 목적지에 도달 여부 변수 = 거짓
//    bool foundDest = false;
//
//    while (!openList.empty()) {
//        pPair p = *openList.begin();//시작점
//
//        // Remove this vertex from the open list
//        openList.erase(openList.begin());
//
//        // Add this vertex to the closed list
//        i = p.second.first;//시작점의 행
//        j = p.second.second;//시작점의 열
//        closedList[i][j] = true;
//
//        /*
//         Generating all the 8 successor of this cell
//
//             N.W   N   N.E
//               \   |   /
//                \  |  /
//             W----Cell----E
//                  / | \
//                /   |  \
//             S.W    S   S.E
//
//         Cell-->Popped Cell (i, j)
//         N -->  North       (i-1, j)
//         S -->  South       (i+1, j)
//         E -->  East        (i, j+1)
//         W -->  West           (i, j-1)
//         N.E--> North-East  (i-1, j+1)
//         N.W--> North-West  (i-1, j-1)
//         S.E--> South-East  (i+1, j+1)
//         S.W--> South-West  (i+1, j-1)*/
//
//         // To store the 'g', 'h' and 'f' of the 8 successors
//         //8가지 방향 인접 셀들에 대한 비용 계산하기
//        double gNew, hNew, fNew;
//
//        //----------- 1st Successor (North) ------------
//
//        // Only process this cell if this is a valid one
//        if (isValid(i - 1, j) == true) {
//            // If the destination cell is the same as the
//            // current successor
//            // 만약 해당 방향의 셀이 목적지라면
//            if (isDestination(i - 1, j, dest) == true) {
//                // Set the Parent of the destination cell
//                cellDetails[i - 1][j].parent_i = i;
//                cellDetails[i - 1][j].parent_j = j;
//                printf("The destination cell is found\n");
//                tracePath(cellDetails, dest);
//                foundDest = true;
//                return;
//            }
//            // If the successor is already on the closed
//            // list or if it is blocked, then ignore it.
//            // Else do the following
//            // 만약 해당 방향 셀이 인접셀 리스트에 없고 해당 셀이 장애물이 아니라면 해당 셀의 경로 비용 계산
//            else if (closedList[i - 1][j] == false
//                && isUnBlocked(grid, i - 1, j)
//                == true) {
//                gNew = cellDetails[i][j].g + 1.0;
//                hNew = calculateHValue(i - 1, j, dest);
//                fNew = gNew + hNew;
//
//                // If it isn’t on the open list, add it to
//                // the open list. Make the current square
//                // the parent of this square. Record the
//                // f, g, and h costs of the square cell
//                //                OR
//                // If it is on the open list already, check
//                // to see if this path to that square is
//                // better, using 'f' cost as the measure.
//                // 만약 오픈 리스트에 해당 방향 셀이 없다면, 오픈 리스트에 더한다. 이전 셀을 이 셀의 부모로 한다. f,g,h 값을 계산한다.
//                // 혹은 이미 오픈 리스트에 해당 방향 셀이 있다면, f값으로 비교해서 어떤 경로가 더 효율적인지 비교한다.
//                if (cellDetails[i - 1][j].f == FLT_MAX// 오픈 리스트에 해당 셀이 없음
//                    || cellDetails[i - 1][j].f > fNew) /*현재 경로를 통한 해당 셀의 비용이 오픈 리스트에 저장된 셀의 경로 비용보다 적음*/ {
//                    openList.insert(make_pair(
//                        fNew, make_pair(i - 1, j)));
//
//                    // Update the details of this cell
//                    // 해당 방향의 셀 정보 갱신
//                    cellDetails[i - 1][j].f = fNew;
//                    cellDetails[i - 1][j].g = gNew;
//                    cellDetails[i - 1][j].h = hNew;
//                    cellDetails[i - 1][j].parent_i = i;
//                    cellDetails[i - 1][j].parent_j = j;
//                }
//            }
//        }
//
//        //----------- 2nd Successor (South) ------------
//
//        // Only process this cell if this is a valid one
//        if (isValid(i + 1, j) == true) {
//            // If the destination cell is the same as the
//            // current successor
//            if (isDestination(i + 1, j, dest) == true) {
//                // Set the Parent of the destination cell
//                cellDetails[i + 1][j].parent_i = i;
//                cellDetails[i + 1][j].parent_j = j;
//                printf("The destination cell is found\n");
//                tracePath(cellDetails, dest);
//                foundDest = true;
//                return;
//            }
//            // If the successor is already on the closed
//            // list or if it is blocked, then ignore it.
//            // Else do the following
//            else if (closedList[i + 1][j] == false
//                && isUnBlocked(grid, i + 1, j)
//                == true) {
//                gNew = cellDetails[i][j].g + 1.0;
//                hNew = calculateHValue(i + 1, j, dest);
//                fNew = gNew + hNew;
//
//                // If it isn’t on the open list, add it to
//                // the open list. Make the current square
//                // the parent of this square. Record the
//                // f, g, and h costs of the square cell
//                //                OR
//                // If it is on the open list already, check
//                // to see if this path to that square is
//                // better, using 'f' cost as the measure.
//                if (cellDetails[i + 1][j].f == FLT_MAX
//                    || cellDetails[i + 1][j].f > fNew) {
//                    openList.insert(make_pair(
//                        fNew, make_pair(i + 1, j)));
//                    // Update the details of this cell
//                    cellDetails[i + 1][j].f = fNew;
//                    cellDetails[i + 1][j].g = gNew;
//                    cellDetails[i + 1][j].h = hNew;
//                    cellDetails[i + 1][j].parent_i = i;
//                    cellDetails[i + 1][j].parent_j = j;
//                }
//            }
//        }
//
//        //----------- 3rd Successor (East) ------------
//
//        // Only process this cell if this is a valid one
//        if (isValid(i, j + 1) == true) {
//            // If the destination cell is the same as the
//            // current successor
//            if (isDestination(i, j + 1, dest) == true) {
//                // Set the Parent of the destination cell
//                cellDetails[i][j + 1].parent_i = i;
//                cellDetails[i][j + 1].parent_j = j;
//                printf("The destination cell is found\n");
//                tracePath(cellDetails, dest);
//                foundDest = true;
//                return;
//            }
//
//            // If the successor is already on the closed
//            // list or if it is blocked, then ignore it.
//            // Else do the following
//            else if (closedList[i][j + 1] == false
//                && isUnBlocked(grid, i, j + 1)
//                == true) {
//                gNew = cellDetails[i][j].g + 1.0;
//                hNew = calculateHValue(i, j + 1, dest);
//                fNew = gNew + hNew;
//
//                // If it isn’t on the open list, add it to
//                // the open list. Make the current square
//                // the parent of this square. Record the
//                // f, g, and h costs of the square cell
//                //                OR
//                // If it is on the open list already, check
//                // to see if this path to that square is
//                // better, using 'f' cost as the measure.
//                if (cellDetails[i][j + 1].f == FLT_MAX
//                    || cellDetails[i][j + 1].f > fNew) {
//                    openList.insert(make_pair(
//                        fNew, make_pair(i, j + 1)));
//
//                    // Update the details of this cell
//                    cellDetails[i][j + 1].f = fNew;
//                    cellDetails[i][j + 1].g = gNew;
//                    cellDetails[i][j + 1].h = hNew;
//                    cellDetails[i][j + 1].parent_i = i;
//                    cellDetails[i][j + 1].parent_j = j;
//                }
//            }
//        }
//
//        //----------- 4th Successor (West) ------------
//
//        // Only process this cell if this is a valid one
//        if (isValid(i, j - 1) == true) {
//            // If the destination cell is the same as the
//            // current successor
//            if (isDestination(i, j - 1, dest) == true) {
//                // Set the Parent of the destination cell
//                cellDetails[i][j - 1].parent_i = i;
//                cellDetails[i][j - 1].parent_j = j;
//                printf("The destination cell is found\n");
//                tracePath(cellDetails, dest);
//                foundDest = true;
//                return;
//            }
//
//            // If the successor is already on the closed
//            // list or if it is blocked, then ignore it.
//            // Else do the following
//            else if (closedList[i][j - 1] == false
//                && isUnBlocked(grid, i, j - 1)
//                == true) {
//                gNew = cellDetails[i][j].g + 1.0;
//                hNew = calculateHValue(i, j - 1, dest);
//                fNew = gNew + hNew;
//
//                // If it isn’t on the open list, add it to
//                // the open list. Make the current square
//                // the parent of this square. Record the
//                // f, g, and h costs of the square cell
//                //                OR
//                // If it is on the open list already, check
//                // to see if this path to that square is
//                // better, using 'f' cost as the measure.
//                if (cellDetails[i][j - 1].f == FLT_MAX
//                    || cellDetails[i][j - 1].f > fNew) {
//                    openList.insert(make_pair(
//                        fNew, make_pair(i, j - 1)));
//
//                    // Update the details of this cell
//                    cellDetails[i][j - 1].f = fNew;
//                    cellDetails[i][j - 1].g = gNew;
//                    cellDetails[i][j - 1].h = hNew;
//                    cellDetails[i][j - 1].parent_i = i;
//                    cellDetails[i][j - 1].parent_j = j;
//                }
//            }
//        }
//
//        //----------- 5th Successor (North-East)
//        //------------
//
//        // Only process this cell if this is a valid one
//        if (isValid(i - 1, j + 1) == true) {
//            // If the destination cell is the same as the
//            // current successor
//            if (isDestination(i - 1, j + 1, dest) == true) {
//                // Set the Parent of the destination cell
//                cellDetails[i - 1][j + 1].parent_i = i;
//                cellDetails[i - 1][j + 1].parent_j = j;
//                printf("The destination cell is found\n");
//                tracePath(cellDetails, dest);
//                foundDest = true;
//                return;
//            }
//
//            // If the successor is already on the closed
//            // list or if it is blocked, then ignore it.
//            // Else do the following
//            else if (closedList[i - 1][j + 1] == false
//                && isUnBlocked(grid, i - 1, j + 1)
//                == true) {
//                gNew = cellDetails[i][j].g + 1.414;
//                hNew = calculateHValue(i - 1, j + 1, dest);
//                fNew = gNew + hNew;
//
//                // If it isn’t on the open list, add it to
//                // the open list. Make the current square
//                // the parent of this square. Record the
//                // f, g, and h costs of the square cell
//                //                OR
//                // If it is on the open list already, check
//                // to see if this path to that square is
//                // better, using 'f' cost as the measure.
//                if (cellDetails[i - 1][j + 1].f == FLT_MAX
//                    || cellDetails[i - 1][j + 1].f > fNew) {
//                    openList.insert(make_pair(
//                        fNew, make_pair(i - 1, j + 1)));
//
//                    // Update the details of this cell
//                    cellDetails[i - 1][j + 1].f = fNew;
//                    cellDetails[i - 1][j + 1].g = gNew;
//                    cellDetails[i - 1][j + 1].h = hNew;
//                    cellDetails[i - 1][j + 1].parent_i = i;
//                    cellDetails[i - 1][j + 1].parent_j = j;
//                }
//            }
//        }
//
//        //----------- 6th Successor (North-West)
//        //------------
//
//        // Only process this cell if this is a valid one
//        if (isValid(i - 1, j - 1) == true) {
//            // If the destination cell is the same as the
//            // current successor
//            if (isDestination(i - 1, j - 1, dest) == true) {
//                // Set the Parent of the destination cell
//                cellDetails[i - 1][j - 1].parent_i = i;
//                cellDetails[i - 1][j - 1].parent_j = j;
//                printf("The destination cell is found\n");
//                tracePath(cellDetails, dest);
//                foundDest = true;
//                return;
//            }
//
//            // If the successor is already on the closed
//            // list or if it is blocked, then ignore it.
//            // Else do the following
//            else if (closedList[i - 1][j - 1] == false
//                && isUnBlocked(grid, i - 1, j - 1)
//                == true) {
//                gNew = cellDetails[i][j].g + 1.414;
//                hNew = calculateHValue(i - 1, j - 1, dest);
//                fNew = gNew + hNew;
//
//                // If it isn’t on the open list, add it to
//                // the open list. Make the current square
//                // the parent of this square. Record the
//                // f, g, and h costs of the square cell
//                //                OR
//                // If it is on the open list already, check
//                // to see if this path to that square is
//                // better, using 'f' cost as the measure.
//                if (cellDetails[i - 1][j - 1].f == FLT_MAX
//                    || cellDetails[i - 1][j - 1].f > fNew) {
//                    openList.insert(make_pair(
//                        fNew, make_pair(i - 1, j - 1)));
//                    // Update the details of this cell
//                    cellDetails[i - 1][j - 1].f = fNew;
//                    cellDetails[i - 1][j - 1].g = gNew;
//                    cellDetails[i - 1][j - 1].h = hNew;
//                    cellDetails[i - 1][j - 1].parent_i = i;
//                    cellDetails[i - 1][j - 1].parent_j = j;
//                }
//            }
//        }
//
//        //----------- 7th Successor (South-East)
//        //------------
//
//        // Only process this cell if this is a valid one
//        if (isValid(i + 1, j + 1) == true) {
//            // If the destination cell is the same as the
//            // current successor
//            if (isDestination(i + 1, j + 1, dest) == true) {
//                // Set the Parent of the destination cell
//                cellDetails[i + 1][j + 1].parent_i = i;
//                cellDetails[i + 1][j + 1].parent_j = j;
//                printf("The destination cell is found\n");
//                tracePath(cellDetails, dest);
//                foundDest = true;
//                return;
//            }
//
//            // If the successor is already on the closed
//            // list or if it is blocked, then ignore it.
//            // Else do the following
//            else if (closedList[i + 1][j + 1] == false
//                && isUnBlocked(grid, i + 1, j + 1)
//                == true) {
//                gNew = cellDetails[i][j].g + 1.414;
//                hNew = calculateHValue(i + 1, j + 1, dest);
//                fNew = gNew + hNew;
//
//                // If it isn’t on the open list, add it to
//                // the open list. Make the current square
//                // the parent of this square. Record the
//                // f, g, and h costs of the square cell
//                //                OR
//                // If it is on the open list already, check
//                // to see if this path to that square is
//                // better, using 'f' cost as the measure.
//                if (cellDetails[i + 1][j + 1].f == FLT_MAX
//                    || cellDetails[i + 1][j + 1].f > fNew) {
//                    openList.insert(make_pair(
//                        fNew, make_pair(i + 1, j + 1)));
//
//                    // Update the details of this cell
//                    cellDetails[i + 1][j + 1].f = fNew;
//                    cellDetails[i + 1][j + 1].g = gNew;
//                    cellDetails[i + 1][j + 1].h = hNew;
//                    cellDetails[i + 1][j + 1].parent_i = i;
//                    cellDetails[i + 1][j + 1].parent_j = j;
//                }
//            }
//        }
//
//        //----------- 8th Successor (South-West)
//        //------------
//
//        // Only process this cell if this is a valid one
//        if (isValid(i + 1, j - 1) == true) {
//            // If the destination cell is the same as the
//            // current successor
//            if (isDestination(i + 1, j - 1, dest) == true) {
//                // Set the Parent of the destination cell
//                cellDetails[i + 1][j - 1].parent_i = i;
//                cellDetails[i + 1][j - 1].parent_j = j;
//                printf("The destination cell is found\n");
//                tracePath(cellDetails, dest);
//                foundDest = true;
//                return;
//            }
//
//            // If the successor is already on the closed
//            // list or if it is blocked, then ignore it.
//            // Else do the following
//            else if (closedList[i + 1][j - 1] == false
//                && isUnBlocked(grid, i + 1, j - 1)
//                == true) {
//                gNew = cellDetails[i][j].g + 1.414;
//                hNew = calculateHValue(i + 1, j - 1, dest);
//                fNew = gNew + hNew;
//
//                // If it isn’t on the open list, add it to
//                // the open list. Make the current square
//                // the parent of this square. Record the
//                // f, g, and h costs of the square cell
//                //                OR
//                // If it is on the open list already, check
//                // to see if this path to that square is
//                // better, using 'f' cost as the measure.
//                if (cellDetails[i + 1][j - 1].f == FLT_MAX
//                    || cellDetails[i + 1][j - 1].f > fNew) {
//                    openList.insert(make_pair(
//                        fNew, make_pair(i + 1, j - 1)));
//
//                    // Update the details of this cell
//                    cellDetails[i + 1][j - 1].f = fNew;
//                    cellDetails[i + 1][j - 1].g = gNew;
//                    cellDetails[i + 1][j - 1].h = hNew;
//                    cellDetails[i + 1][j - 1].parent_i = i;
//                    cellDetails[i + 1][j - 1].parent_j = j;
//                }
//            }
//        }
//    }
//
//    // When the destination cell is not found and the open
//    // list is empty, then we conclude that we failed to
//    // reach the destination cell. This may happen when the
//    // there is no way to destination cell (due to
//    // blockages)
//    //오픈리스트가 빌 때까지 목적지 셀을 찾지 못한다면 목적지 셀까지 도달할 수 없다는 뜻
//    if (foundDest == false)
//        printf("Failed to find the Destination Cell\n");
//
//    return;
//}
//
//// Driver program to test above function
////int main()
////{
////    /* Description of the Grid-
////     1--> The cell is not blocked
////     0--> The cell is blocked    */
////    int grid[ROW][COL]
////        = { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
////            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
////            { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
////            { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
////            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
////            { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
////            { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
////            { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
////            { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };
////
////    // Source is the left-most bottom-most corner
////    Pair src = make_pair(8, 0);
////
////    // Destination is the left-most top-most corner
////    Pair dest = make_pair(0, 0);
////
////    aStarSearch(grid, src, dest);
////
////    return (0);
////}
//
//
//
//
//AStarPathFinder::AStarPathFinder()
//{
//}
//
//AStarPathFinder::~AStarPathFinder()
//{
//}
//
//void AStarPathFinder::PathFind(int grid[10][10], Pair src, Pair dest)
//{
//    aStarSearch(grid, src, dest);
//}
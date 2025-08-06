#pragma once

#include "../Headers/arrow.hpp" // Use 'std::vector<std::pair<int, int>> instead
#include "../Headers/Queue.hpp" // Use STL <queue> instead
#include <set>
#include <map>
#include <utility>

// Shortcut
using couple = std::pair<int, int>;

// Helper function

// Main function
Arrow<couple> BFS(const Arrow<Arrow<int>>& maze, const int& start_row, const int& start_column, const int& TARGET, const Arrow<int>& walkable) {

    if (maze.empty() || maze[start_row][start_column] == TARGET)
        throw std::logic_error("Cannot resolve given maze.");

    // Limit dimension
    const size_t R = maze.size();
    const size_t C = maze[0].size();

    // Block Holder (maze[row][column])
    Queue<couple> Q;

    // Visited block holder
    std::set<couple> visited;

    // Block tracker (We got to the curr)
    std::map<couple, couple> parent;

    // valid directions
    const Arrow<couple> direction = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Returned path (If found)
    Arrow<couple> path;

    // Starting block
    const couple START = {start_row, start_column};
    // Current Block indecies
    int r, c;
    // Neighbor Block indecies
    int nr, nc;

    Q.enqueue(START);
    while (!Q.empty()) {
        couple curr = Q.dequeue();
        std::tie(r, c) = curr;

        if (maze[r][c] == TARGET) {
            while (curr != START) {
                path.append(curr);
                curr = parent[curr];
            }

            path.append(START);
            path.reverse();
            return path;
        }

        // Check every neighbor block
        for (auto& [dr, dc] : direction) {
            nr = r + dr;
            nc = c + dc;

            // couple neighbor = std::make_pair(nr, nc);
            couple neighbor = {nr, nc};

            // Validate neighbor block
            if (
                (((nr>=0) && (nr<R)) && ((nc>=0) && (nc<C))) &&
                ( walkable.contains(maze[nr][nc]) ) &&
                (!visited.count(neighbor))
            ) {
                visited.insert(neighbor);
                Q.enqueue(neighbor);
                parent[neighbor] = curr;
               }
        }
    }

    // Not found
    throw std::invalid_argument("Cannot find a valid path.");
}
#include "Escaper.h"

#include <limits>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <functional>
#include <iostream>

std::vector<int> Escaper::escape(int steps)
{
    int bestScore = std::numeric_limits<int>::min();
    std::vector<int> bestMove = {m_escaperPosition};

    bool foundEscape = false;
    std::set<std::vector<int>> paths = GetAllPaths(m_escaperPosition, steps, foundEscape);

    if (foundEscape)
    {
        for (const auto &path : paths)
        {
            if (!path.empty())
            {
                m_escaperPosition = path.back();
                return path;                    
            }
        }
    }

    for (const auto &path : paths)
    {
        int lastPosition = path.back();

        int minEscapeDist = std::numeric_limits<int>::max();
        for (int escapePoint : m_escapePoints)
        {
            minEscapeDist = std::min(minEscapeDist, m_minDistances[lastPosition][escapePoint]);
        }

        int minHunterDist = std::numeric_limits<int>::max();
        for (int hunterPosition : m_hunterPositions)
        {
            minHunterDist = std::min(minHunterDist, m_minDistances[lastPosition][hunterPosition]);
        }

        int score = minHunterDist - minEscapeDist;
        if (score > bestScore)
        {
            bestScore = score;
            bestMove = path;
        }
    }

    m_escaperPosition = bestMove.back();
    return bestMove;
}

std::set<std::vector<int>> Escaper::GetAllPaths(int currentPosition, int steps, bool& foundEscape) {
    std::set<std::vector<int>> result;
    foundEscape = false;

    std::function<bool(std::vector<int>&, int, int, std::unordered_set<int>&)> searchUntilEscape;
    
    searchUntilEscape = [&](std::vector<int>& path, int nodeId, int depth, std::unordered_set<int>& visited) -> bool {
        if (m_escapePoints.count(nodeId)) {
            foundEscape = true;
            result.clear();
            result.insert(path);
            return true;
        }

        if (depth == steps) {
            result.insert(path);
            return false;
        }

        for (int neighbor : m_nodes[nodeId]->connected) {
            if (visited.count(neighbor)) continue;
            path.push_back(neighbor);
            visited.insert(neighbor);

            if (searchUntilEscape(path, neighbor, depth + 1, visited)) return true;

            path.pop_back();
            visited.erase(neighbor);
        }

        return false;
    };

    std::vector<int> path = { currentPosition };
    std::unordered_set<int> visited = { currentPosition };
    searchUntilEscape(path, currentPosition, 0, visited);

    return result;
}

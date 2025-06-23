#include "Hunter.h"
#include <algorithm>
#include <set>
#include <vector>
#include <unordered_set>
#include <functional>
#include <limits>
#include <iostream>

struct HunterInfo
{
    int id;
    int distance;
    std::vector<int> path;
};

std::vector<int> Hunter::GetSortedHuntersByEscaperDistance(
    const std::vector<int> &huntersPositions,
    const std::vector<std::vector<int>> &minDistances,
    int escaperPosition)
{
    std::vector<HunterInfo> hunterInfos;

    for (int hid : huntersPositions)
    {
        int dist = minDistances[hid][escaperPosition];
        hunterInfos.push_back({hid, dist, {}});
    }

    std::sort(hunterInfos.begin(), hunterInfos.end(),
              [](const HunterInfo &a, const HunterInfo &b)
              {
                  return a.distance < b.distance;
              });

    std::vector<int> sortedHunters;
    for (const auto &info : hunterInfos)
    {
        sortedHunters.push_back(info.id);
    }

    return sortedHunters;
}

std::vector<std::vector<int>> Hunter::hunt(int steps)
{
    std::vector<int> sortedHunters = GetSortedHuntersByEscaperDistance(
        m_huntersPositions, m_minDistances, m_escaperPosition);

    std::set<int> reservedPositions;
    std::vector<std::vector<int>> retPaths;
    std::vector<int> huntterNewPositions;
    bool escaperCaught = false;

    for (int index = 0; index < sortedHunters.size(); ++index)
    {
        int currentPosition = sortedHunters[index];

        std::set<std::vector<int>> allPaths = GetAllPaths(currentPosition, steps, escaperCaught);
        if (escaperCaught) // If the escaper is caught, we can stop processing further
        {
            huntterNewPositions.push_back(m_escaperPosition);
            retPaths.push_back(*allPaths.begin());
            return retPaths;
        }

        std::vector<int> path = {currentPosition};
        if (index < sortedHunters.size() / 2) // weight the path by the distance to the escaper
        {
            int bestDist = std::numeric_limits<int>::max();
            for (const auto &p : allPaths)
            {
                int lastPosition = p.back();
                if (m_minDistances[lastPosition][m_escaperPosition] < bestDist &&
                    reservedPositions.count(lastPosition) == 0)
                {
                    bestDist = m_minDistances[lastPosition][m_escaperPosition];
                    path = p;
                    currentPosition = lastPosition;
                }
            }
        }
        else // weight the path by the distance to the escape points
        {
            int bestDist = std::numeric_limits<int>::max();
            for (const auto &p : allPaths)
            {
                int lastPosition = p.back();
                if (reservedPositions.count(lastPosition) != 0)
                {
                    continue; // Skip already reserved positions
                }
                int minEscapeDist = std::numeric_limits<int>::max();
                for (int escapePoint : m_escapePoints)
                {
                    minEscapeDist = std::min(minEscapeDist, m_minDistances[lastPosition][escapePoint]);
                }
                if (minEscapeDist < bestDist)
                {
                    bestDist = minEscapeDist;
                    path = p;
                    currentPosition = lastPosition;
                }
            }
        }

        huntterNewPositions.push_back(currentPosition);
        reservedPositions.insert(currentPosition);
        retPaths.push_back(path);
    }

    m_huntersPositions = huntterNewPositions;

    return retPaths;
}

std::set<std::vector<int>> Hunter::GetAllPaths(int currentPosition, int steps, bool &escaperCaught)
{
    std::set<std::vector<int>> allPaths;

    std::function<bool(std::vector<int> &, int, int, std::unordered_set<int> &)> searchPathUntilCapture;

    searchPathUntilCapture = [&](std::vector<int> &path, int current, int remainingSteps, std::unordered_set<int> &visited) -> bool
    {
        if (current == m_escaperPosition)
        {
            escaperCaught = true;
            allPaths.clear();
            allPaths.insert(path);
            return true;
        }

        if (remainingSteps == 0)
        {
            if (!m_escapePoints.count(path.back()))
            {
                allPaths.insert(path);
            }
            return false;
        }

        for (int neighbor : m_nodes[current]->connected)
        {
            if (visited.count(neighbor))
            {
                continue;
            }

            path.push_back(neighbor);
            visited.insert(neighbor);

            if (searchPathUntilCapture(path, neighbor, remainingSteps - 1, visited))
            {
                return true;
            }

            path.pop_back();
            visited.erase(neighbor);
        }

        return false;
    };

    std::vector<int> path = {currentPosition};
    std::unordered_set<int> visited = {currentPosition};
    searchPathUntilCapture(path, currentPosition, steps, visited);

    return allPaths;
}

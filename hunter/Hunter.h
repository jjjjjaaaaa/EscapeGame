#pragma once
#include <vector>
#include <set>

#include "node/Node.h"

class Hunter {
public:
    Hunter(
        const std::vector<Node*>& nodes,
        const std::vector<std::vector<int>>& minDistances,
        const std::set<int>& escapePoints,
        const int& escaperPosition,
        std::vector<int>& hunterPositions
    ) : m_nodes(nodes),
        m_minDistances(minDistances),
        m_escapePoints(escapePoints),
        m_escaperPosition(escaperPosition),
        m_huntersPositions(hunterPositions)
         {}

    virtual ~Hunter() = default;

    virtual std::vector<std::vector<int>> hunt(int steps = 1);

private:
    const std::vector<Node*>& m_nodes;
    const std::vector<std::vector<int>>& m_minDistances;
    const std::set<int>& m_escapePoints;
    std::vector<int>& m_huntersPositions;
    const int& m_escaperPosition;

    std::set<std::vector<int>> GetAllPaths(int currentPosition, int steps, bool& escaperCaught);

    static std::vector<int> GetSortedHuntersByEscaperDistance(
        const std::vector<int>& huntersPositions,
        const std::vector<std::vector<int>>& minDistances,
        int escaperPosition);
};
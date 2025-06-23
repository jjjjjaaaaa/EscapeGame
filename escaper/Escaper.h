#pragma once
#include <vector>
#include <set>

#include "Node/Node.h"

class Escaper {
public:
    Escaper(
        const std::vector<Node*>& nodes,
        const std::vector<std::vector<int>>& minDistances,
        const std::set<int>& escapePoints,
        const std::vector<int>& hunterPositions,
        int& escaperPosition
    ) : m_nodes(nodes), 
        m_minDistances(minDistances),
        m_escapePoints(escapePoints), 
        m_hunterPositions(hunterPositions), 
        m_escaperPosition(escaperPosition) {}

    virtual ~Escaper() = default;

    virtual std::vector<int> escape(int steps = 2);

private:
    const std::vector<Node*>& m_nodes;
    const std::vector<std::vector<int>>& m_minDistances;
    const std::set<int>& m_escapePoints;
    const std::vector<int>& m_hunterPositions;
    int& m_escaperPosition;

    std::set<std::vector<int>> GetAllPaths(int currentPosition, int steps, bool& foundEscape);

};
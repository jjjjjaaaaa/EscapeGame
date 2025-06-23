#include <queue>
#include <vector>
#include <set>
#include <iostream>

#include "hunter/Hunter.h"
#include "escaper/Escaper.h"
#include "node/Node.h"

std::vector<std::vector<int>> GetMinDistance(const std::vector<Node*>& nodes) {
    int N = nodes.size();
    std::vector<std::vector<int>> distMap(N, std::vector<int>(N, -1));

    for (int start = 0; start < N; ++start) {
        std::queue<int> q;
        distMap[start][start] = 0;
        q.push(start);

        while (!q.empty()) {
            int current = q.front(); q.pop();
            int curDist = distMap[start][current];

            for (int neighborId : nodes[current]->connected) {
                if (distMap[start][neighborId] == -1) {
                    distMap[start][neighborId] = curDist + 1;
                    q.push(neighborId);
                }
            }
        }
    }

    return distMap;
}

int main()
{
    const int nodeCount = 10;
    std::vector<Node*> nodes(nodeCount);
    for (int i = 0; i < nodeCount; ++i) {   
        nodes[i] = new Node(i);
    }

    nodes[0]->connected = {8, 9};
    nodes[1]->connected = {2, 4, 6};
    nodes[2]->connected = {1, 3, 4, 5};
    nodes[3]->connected = {2, 5};
    nodes[4]->connected = {1, 2, 5, 6, 7};
    nodes[5]->connected = {2, 3, 4, 7, 8};
    nodes[6]->connected = {1, 4, 7, 9};
    nodes[7]->connected = {4, 5, 6, 8, 9};
    nodes[8]->connected = {5, 7, 9, 0};
    nodes[9]->connected = {6, 7, 8, 0};

    const std::vector<std::vector<int>> minDistances = GetMinDistance(nodes);
    const std::set<int> escapePoints = {6, 9};
    std::vector<int> hunterPositions = {8, 8, 0, 0};
    int escaperPosition = 3;

    Hunter hunter(nodes, minDistances, escapePoints, escaperPosition, hunterPositions);
    Escaper escaper(nodes, minDistances, escapePoints, hunterPositions, escaperPosition);

    while (true) {
        std::cout << "Hunter moved" << std::endl;
        std::vector<std::vector<int>> hunterPaths = hunter.hunt();
        for (const auto& path : hunterPaths) {
            if (!path.empty()) {
                std::cout << "Hunter's moved path: ";
                for (int pos : path) {
                    std::cout << pos << " ";
                    if (escaperPosition == pos) {
                        std::cout << "\nEscaper is caught by hunter at position " << pos << "!" << std::endl;
                        return 0;
                    }
                }
                std::cout << std::endl;
            }
        }

        std::cout << "Escaper moved" << std::endl;
        std::vector<int> escaperPath = escaper.escape();
        std::cout << "Escaper's moved path: ";
        for (int pos : escaperPath) {
            std::cout << pos << " ";
        }
        std::cout << std::endl;
        if (escapePoints.count(escaperPosition) != 0) {
            std::cout << "Escaper has escaped successfully!" << std::endl;
            return 0;
        }
    }


    return 0;
}

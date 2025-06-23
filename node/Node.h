#pragma once
#include <vector>

typedef struct Node {
    int id;
    std::vector<int> connected;

    Node(int nodeId) : id(nodeId) {}
} Node;
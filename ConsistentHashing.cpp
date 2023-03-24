#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>
#include <stdexcept>
#include "models.h"

class ConsistentHashing : public Router {
private:
    std::map<Node, std::vector<long>> nodePositions;
    std::map<long, Node> nodeMappings;
    std::function<long(std::string)> hashFunction;
    int pointMultiplier;

public:
    ConsistentHashing(const std::function<long(std::string)>& hashFunction, const int pointMultiplier)
            : hashFunction(hashFunction), pointMultiplier(pointMultiplier) {
        if (pointMultiplier == 0) {
            throw std::invalid_argument("Point multiplier cannot be zero");
        }
    }

    void addNode(Node node) {
        nodePositions[node] = std::vector<long>();
        for (int i = 0; i < pointMultiplier; i++) {
            for (int j = 0; j < node.getWeight(); j++) {
                const long point = hashFunction(std::to_string(i * pointMultiplier + j) + std::to_string(node.getId()));
                nodePositions[node].push_back(point);
                nodeMappings[point] = node;
            }
        }
    }

    void removeNode(Node node) {
        for (const auto& point : nodePositions[node]) {
            nodeMappings.erase(point);
        }
        nodePositions.erase(node);
    }

    Node getAssignedNode(Request request) {
        const long key = hashFunction(request.getId());
        const auto& entry = std::upper_bound(nodeMappings.begin(), nodeMappings.end(), key,
                                             [](const long& key, const std::pair<long, Node>& nodeEntry) {
                                                 return key < nodeEntry.first;
                                             });
        if (entry == nodeMappings.end()) {
            return nodeMappings.begin()->second;
        } else {
            return entry->second;
        }
    }
};
/*The provided code implements the Consistent Hashing algorithm for a distributed system, which is used for efficient and consistent distribution of requests across multiple nodes in the system.

The ConsistentHashing class implements the Router interface, which defines the behavior of a router in the system.

The class contains four private member variables:

nodePositions: a map that stores the list of positions (i.e., points on a hash ring) for each*/


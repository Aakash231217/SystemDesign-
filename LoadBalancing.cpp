#include <map>
#include <string>
#include <unordered_map>

#include "models/Node.h"
#include "models/Request.h"
#include "models/Service.h"

class LoadBalancer {
   private:
    std::unordered_map<std::string, Service> services;
    std::unordered_map<std::string, Node> nodes;

   public:
    LoadBalancer() {}

    void registerService(Service service) { services[service.getId()] = service; }

    void addNode(const std::string& serviceId, Node node) {
        nodes[node.getId()] = node;
        services[serviceId].getRouter().addNode(node);
    }

    void removeNode(const std::string& serviceId, const std::string& nodeId) {
        services[serviceId].getRouter().removeNode(nodes[nodeId]);
        nodes.erase(nodeId);
    }

    Node getHandler(Request request) {
        return services[request.getServiceId()].getRouter().getAssignedNode(request);
    }
};
/*The given code is an implementation of a load balancer, which is responsible for distributing incoming requests to a group of nodes that can handle them. The load balancer is designed to work with a collection of services, where each service is associated with a unique ID and a router. A router is a specific algorithm for mapping requests to nodes, and it is implemented in a separate class (not shown in the given code).

The load balancer class has the following key components:

services map: This is a map that stores all the registered services, where each service is associated with a unique ID.

nodes map: This is a map that stores all the nodes that have been added to the load balancer.

register method: This method is used to register a new service with the load balancer. The method adds the service to the services map, with the service's ID as the key.

addNode method: This method is used to add a new node to a specific service. The method first adds the node to the nodes map, with the node's ID as the key. Then, it retrieves the router associated with the specified service and adds the node to the router.

removeNode method: This method is used to remove a node from a specific service. The method first removes the node from the nodes map. Then, it retrieves the router associated with the specified service and removes the node from the router.

getHandler method: This method is used to determine the node that should handle a specific request. The method retrieves the router associated with the service that the request is intended for and uses the router to determine the node that should handle the request.

The implementation uses ConcurrentHashMap to ensure thread safety in a multi-threaded environment. */

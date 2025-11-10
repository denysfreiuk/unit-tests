/**
 * @file Graph.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of the Graph, Vertex, and Edge classes for the Zoo Management System.
 *
 * This header defines a basic graph data structure used for modeling
 * relationships between zoo entities such as aviaries or locations.
 * The graph consists of vertices (nodes) and weighted edges (connections).
 *
 * @details
 * The Graph class provides methods for adding, removing, and querying vertices and edges,
 * as well as for computing paths and connectivity between nodes. It forms the backbone
 * of the ZooGraph subsystem used in spatial and route-based operations.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <memory>
#include <string>

using namespace std;

/**
 * @class Vertex
 * @brief Represents a vertex (node) in the zoo's graph structure.
 *
 * Each vertex corresponds to a unique entity in the system (e.g., an aviary, zone, or point of interest).
 *
 * @details
 * The vertex is identified by a unique string ID. It can be extended in derived
 * classes to store additional metadata (e.g., coordinates, capacity, etc.).
 *
 * @example
 * @code
 * Vertex v("A1");
 * cout << v.getId(); // Outputs: A1
 * @endcode
 */
class Vertex {

private:
    string id; ///< Unique identifier for the vertex.

public:
    /// @name Constructors and Destructors
    /// @{

    /** @brief Default constructor creating an empty vertex. */
    Vertex();

    /**
     * @brief Constructs a vertex with a specific ID.
     * @param id Unique string identifier for the vertex.
     */
    explicit Vertex(const string& id);

    /** @brief Virtual destructor for proper cleanup of derived classes. */
    virtual ~Vertex();

    /// @}

    /// @name Accessors
    /// @{

    /**
     * @brief Returns the vertex's unique identifier.
     * @return The vertex ID as a string.
     */
    [[nodiscard]] string getId() const;

    /// @}
};

/**
 * @class Edge
 * @brief Represents a connection (edge) between two vertices in the graph.
 *
 * Each edge connects two vertices and may carry an associated weight
 * representing distance, cost, or any measurable value.
 *
 * @details
 * Edges are typically stored in a vector within the Graph class and used
 * to determine adjacency and compute paths.
 *
 * @example
 * @code
 * Edge e("A1", "A2", 25.5);
 * cout << e.getWeight(); // Outputs: 25.5
 * @endcode
 */
class Edge {

private:
    string fromId; ///< ID of the starting vertex.
    string toId;   ///< ID of the destination vertex.
    double weight; ///< Weight (distance or cost) of the edge.

public:
    /**
     * @brief Constructs an edge between two vertices.
     * @param from Starting vertex ID.
     * @param to Destination vertex ID.
     * @param w Weight of the connection.
     */
    Edge(const string& from, const string& to, double w)
        : fromId(from), toId(to), weight(w) {}

    /// @name Accessors
    /// @{

    /** @return The ID of the starting vertex. */
    [[nodiscard]] string getFrom() const;

    /** @return The ID of the destination vertex. */
    [[nodiscard]] string getTo() const;

    /** @return The weight of the edge. */
    [[nodiscard]] double getWeight() const;

    /// @}
};

/**
 * @class Graph
 * @brief Represents a weighted graph structure for the zoo system.
 *
 * The Graph class models the layout of aviaries and paths connecting them.
 * It supports common graph operations such as adding/removing vertices or edges,
 * finding paths, and checking connectivity.
 *
 * @details
 * The graph uses an adjacency-based design, storing vertices in an unordered_map
 * and edges in a vector. Paths can be computed using traversal or weighted search.
 *
 * @note This class serves as the base for ZooGraph, which adds zoo-specific logic.
 *
 * @example
 * @code
 * Graph g;
 * g.addVertex(make_shared<Vertex>("A1"));
 * g.addVertex(make_shared<Vertex>("A2"));
 * g.addEdge("A1", "A2", 15.0);
 * auto path = g.findPath("A1", "A2");
 * @endcode
 */
class Graph {

private:
    unordered_map<string, shared_ptr<Vertex>> vertices; ///< Collection of all vertices indexed by ID.
    vector<Edge> edges; ///< List of edges connecting vertices.

protected:
    /// @name Accessors
    /// @{

    /** @return Constant reference to the map of vertices. */
    [[nodiscard]] const unordered_map<string, shared_ptr<Vertex>>& getVertices() const;

    /** @return Constant reference to the vector of edges. */
    [[nodiscard]] const vector<Edge>& getEdges() const;

    /**
     * @brief Retrieves an edge between two vertices if it exists.
     * @param fromId Starting vertex ID.
     * @param toId Destination vertex ID.
     * @return Pointer to the found Edge, or nullptr if none exists.
     */
    [[nodiscard]] const Edge* getEdge(const string& fromId, const string& toId) const;

    /**
     * @brief Retrieves a vertex by its ID.
     * @param id Vertex identifier.
     * @return Shared pointer to the Vertex, or nullptr if not found.
     */
    [[nodiscard]] shared_ptr<Vertex> getVertex(const string& id) const;

    /**
     * @brief Returns all neighbor vertex IDs for a given vertex.
     * @param id Vertex identifier.
     * @return Vector of IDs representing adjacent vertices.
     */
    [[nodiscard]] vector<string> getNeighbors(const string& id) const;

    /// @}

    /// @name Mutators
    /// @{

    /**
     * @brief Replaces the current set of vertices with a new collection.
     * @param newVertices Map of vertex IDs to Vertex pointers.
     */
    void setVertices(const unordered_map<string, shared_ptr<Vertex>>& newVertices);

    /**
     * @brief Replaces the current set of edges with a new vector.
     * @param newEdges Vector containing the new edges.
     */
    void setEdges(const vector<Edge>& newEdges);

    /// @}

    /// @name Graph Modification
    /// @{

    /**
     * @brief Adds a new vertex to the graph.
     * @param v Shared pointer to the Vertex to add.
     */
    void addVertex(shared_ptr<Vertex> v);

    /**
     * @brief Adds a new edge between two vertices.
     * @param fromId Starting vertex ID.
     * @param toId Destination vertex ID.
     * @param weight Edge weight (distance or cost).
     */
    void addEdge(const string& fromId, const string& toId, double weight);

    /**
     * @brief Removes a vertex and all connected edges.
     * @param id ID of the vertex to remove.
     */
    void removeVertex(const string& id);

    /**
     * @brief Removes an edge between two vertices.
     * @param fromId Starting vertex ID.
     * @param toId Destination vertex ID.
     */
    void removeEdge(const string& fromId, const string& toId);

    /// @}

    /// @name Pathfinding and Analysis
    /// @{

    /**
     * @brief Finds a simple path between two vertices.
     * @param startId ID of the starting vertex.
     * @param endId ID of the destination vertex.
     * @return Vector of vertex IDs representing the path.
     */
    [[nodiscard]] vector<string> findPath(const string& startId, const string& endId);

    /**
     * @brief Finds a path between two vertices optimized by edge weight.
     * @param startId ID of the starting vertex.
     * @param endId ID of the destination vertex.
     * @return Vector of vertex IDs representing the shortest or least costly path.
     */
    [[nodiscard]] vector<string> findPathByWeight(const string& startId, const string& endId) const;

    /**
     * @brief Calculates the total distance between two vertices.
     * @param fromId Starting vertex ID.
     * @param toId Destination vertex ID.
     * @return Sum of weights between the given vertices.
     */
    [[nodiscard]] double distanceBetween(const string& fromId, const string& toId) const;

    /**
     * @brief Checks if the graph is fully connected.
     * @return True if every vertex can reach all others, false otherwise.
     */
    [[nodiscard]] bool checkConnectivity() const;

    /// @}

    /// @name Output and Debugging
    /// @{

    /**
     * @brief Prints a readable representation of the graph structure.
     *
     * Displays all vertices and edges with their connections and weights.
     */
    void printGraph() const;

    /// @}
};

#endif // GRAPH_H

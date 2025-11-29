/**
 * @file PathRepository.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of the PathRepository class used in the Zoo Management System.
 *
 * The PathRepository class manages the database layer for paths (connections) between
 * aviaries within the zoo. It provides methods for creating, deleting, retrieving,
 * and clearing stored paths in the database. Each path represents a directional or
 * bidirectional connection with a specific distance (length).
 *
 * @details
 * This class serves as the persistent storage interface for the ZooGraph subsystem.
 * It enables saving the zoo's graph structure (paths between aviaries) in a relational
 * database through the DatabaseManager component.
 */

#ifndef PATHREPOSITORY_H
#define PATHREPOSITORY_H

#include "DatabaseManager.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>
#include <string>

using namespace std;

class Path;

/**
 * @class PathRepository
 * @brief Provides persistent storage and access operations for Path entities.
 *
 * The PathRepository encapsulates all low-level database operations related to
 * paths between aviaries. It allows initializing tables, adding or removing paths,
 * retrieving all connections, and clearing stored data.
 *
 * @note This class interacts closely with DatabaseManager and the ZooGraph structure.
 * @see DatabaseManager, ZooGraph, Path
 *
 * @example
 * @code
 * DatabaseManager db("zoo.db");
 * PathRepository repo(db);
 * repo.initTable();
 * repo.addPath("A1", "A2", 42.5);
 * auto paths = repo.getAllPaths();
 * @endcode
 */
class PathRepository {

private:
    DatabaseManager& db; ///< Reference to the database manager used for persistent operations.

public:
    /// @name Constructors and Initialization
    /// @{

    /**
     * @brief Constructs a PathRepository connected to a database.
     * @param database Reference to the DatabaseManager instance.
     *
     * Establishes the repository for storing and retrieving path information.
     */
    explicit PathRepository(DatabaseManager& database) : db(database) {}

    /**
     * @brief Initializes the paths table in the database.
     *
     * Creates the required schema for storing path information (IDs, distance, etc.)
     * if it does not already exist.
     */
    void initTable();

    /// @}

    /// @name Path Management
    /// @{

    /**
     * @brief Adds a new path record to the database.
     * @param fromId ID of the starting aviary.
     * @param toId ID of the destination aviary.
     * @param length Distance or length of the path between the aviaries.
     *
     * Stores a new connection between two aviaries in the persistent layer.
     */
    void addPath(const string& fromId, const string& toId, double length);

    /**
     * @brief Removes a path record from the database.
     * @param fromId ID of the starting aviary.
     * @param toId ID of the destination aviary.
     *
     * Deletes the connection between the specified aviaries, if it exists.
     */
    void removePath(const string& fromId, const string& toId);

    /// @}

    /// @name Retrieval and Maintenance
    /// @{

    /**
     * @brief Retrieves all paths from the database.
     * @return A vector of shared pointers to Path objects representing all stored paths.
     *
     * Used to rebuild the zoo's path network into memory when initializing ZooGraph.
     */
    [[nodiscard]] vector<shared_ptr<Path>> getAllPaths();

    /**
     * @brief Clears all stored path records.
     *
     * Removes all connections between aviaries from the database. Primarily used
     * during testing or system reinitialization.
     */
    void clearAll();

    /// @}
};

#endif // PATHREPOSITORY_H

/**
 * @file DatabaseManager.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of the DatabaseManager class used in the Zoo Management System.
 *
 * The DatabaseManager class provides an interface for connecting to and interacting
 * with an SQLite database. It supports opening and closing connections, executing
 * SQL statements, preparing queries, and accessing the raw database handle.
 *
 * @details
 * This class serves as the core database abstraction for all repository layers
 * (e.g., AnimalRepository, EmployeeRepository, AccountRepository). It ensures
 * safe connection management and query execution through SQLite's C API.
 */

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <sqlite3.h>
#include <string>
#include <iostream>

using namespace std;

/**
 * @class DatabaseManager
 * @brief Handles low-level database operations for the Zoo Management System.
 *
 * The DatabaseManager encapsulates the logic for interacting with the SQLite engine.
 * It is responsible for connection lifecycle management and executing SQL commands.
 * All repository classes depend on it for consistent access to the same database instance.
 *
 * @note This class is a thin wrapper around the SQLite C API (`sqlite3.h`).
 * @see sqlite3, AccountRepository, AnimalRepository, AviaryRepository
 *
 * @example
 * @code
 * DatabaseManager db("zoo.db");
 * if (db.open()) {
 *     db.execute("CREATE TABLE IF NOT EXISTS animals (id TEXT, name TEXT);");
 *     db.close();
 * }
 * @endcode
 */
class DatabaseManager {

private:
    sqlite3* db;      ///< Pointer to the underlying SQLite database connection.
    string dbName;    ///< Name (or path) of the SQLite database file.

public:
    /// @name Constructors and Destructors
    /// @{

    /**
     * @brief Constructs a DatabaseManager for the specified database file.
     * @param name Name or path of the SQLite database file (default: "zoo.db").
     *
     * Initializes the database manager with the given file path but does not
     * open the connection automatically — call `open()` to establish it.
     */
    explicit DatabaseManager(const string& name = "zoo.db");

    /**
     * @brief Destructor — automatically closes the database if still open.
     */
    ~DatabaseManager();

    /// @}

    /// @name Connection Management
    /// @{

    /**
     * @brief Opens a connection to the database.
     * @return True if the database was successfully opened, false otherwise.
     *
     * @details
     * This method must be called before executing or preparing any statements.
     * If the file does not exist, it will be created automatically by SQLite.
     */
    bool open();

    /**
     * @brief Closes the current database connection.
     *
     * Safely terminates the SQLite session and releases internal resources.
     * It is safe to call this method multiple times.
     */
    void close();

    /// @}

    /// @name SQL Execution and Query Preparation
    /// @{

    /**
     * @brief Executes a single SQL command.
     * @param sql SQL statement to execute (e.g., CREATE, INSERT, UPDATE).
     * @return True if the statement executed successfully, false otherwise.
     *
     * @details
     * This method is intended for non-parameterized queries such as table creation
     * or record modification. For prepared statements, use `prepare()`.
     */
    bool execute(const string& sql);

    /**
     * @brief Prepares an SQL statement for execution.
     * @param sql SQL query string to compile.
     * @param stmt Pointer to an SQLite statement object (output parameter).
     * @return True if the statement was successfully prepared, false otherwise.
     *
     * @note The caller is responsible for finalizing the prepared statement
     *       with `sqlite3_finalize()` after use.
     */
    bool prepare(const string& sql, sqlite3_stmt** stmt);

    /// @}

    /// @name Accessors
    /// @{

    /**
     * @brief Returns the underlying SQLite database handle.
     * @return Raw pointer to the active SQLite database connection.
     *
     * @warning Use this only if you need direct access to SQLite C API functions.
     */
    [[nodiscard]] sqlite3* getDB() const;

    /// @}
};

#endif // DATABASEMANAGER_H

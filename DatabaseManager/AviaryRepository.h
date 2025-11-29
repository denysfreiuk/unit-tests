/**
 * @file AviaryRepository.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of the AviaryRepository class used in the Zoo Management System.
 *
 * The AviaryRepository class provides database-level operations for managing
 * aviary data in the Zoo Management System. It handles the persistent storage
 * and retrieval of aviary records, including relationships with employees and animals.
 *
 * @details
 * This class acts as a data access layer between the ZooGraph or AviaryManager
 * and the database. It is responsible for CRUD operations, employee–aviary
 * assignment updates, and bulk retrieval of all aviaries from persistent storage.
 */

#ifndef AVIARYREPOSITORY_H
#define AVIARYREPOSITORY_H

#include "DatabaseManager.h"
#include <unordered_map>
#include <memory>
#include <iostream>

using namespace std;

class Aviary;

/**
 * @class AviaryRepository
 * @brief Provides persistent storage and retrieval operations for Aviary entities.
 *
 * The AviaryRepository class encapsulates all database operations related to
 * aviaries. It supports initialization, addition, removal, assignment updates,
 * and full listing of aviaries within the system.
 *
 * @note This class operates in conjunction with the DatabaseManager to perform
 * actual SQL or file-based data persistence.
 * @see DatabaseManager, Aviary, Employee
 *
 * @example
 * @code
 * DatabaseManager db("zoo.db");
 * AviaryRepository repo(db);
 * repo.initTable();
 * repo.addAviary(Aviary("A1", "Savannah Habitat", 5));
 * repo.updateAviaryEmployee("A1", "E001");
 * auto aviaries = repo.getAllAviaries();
 * @endcode
 */
class AviaryRepository {

private:
    DatabaseManager& db; ///< Reference to the database interface for persistent operations.

public:
    /// @name Constructors and Initialization
    /// @{

    /**
     * @brief Constructs an AviaryRepository linked to a database.
     * @param database Reference to the DatabaseManager instance.
     *
     * Establishes a database connection for managing aviary records.
     */
    explicit AviaryRepository(DatabaseManager& database) : db(database) {}

    /**
     * @brief Initializes the aviary table in the database.
     *
     * Creates or verifies the table structure needed for storing aviary data.
     */
    void initTable();

    /// @}

    /// @name CRUD Operations
    /// @{

    /**
     * @brief Adds a new aviary to the database.
     * @param a Reference to the Aviary object to insert.
     *
     * Serializes the aviary’s properties and writes them to persistent storage.
     */
    void addAviary(const Aviary& a);

    /**
     * @brief Removes an aviary record from the database.
     * @param id Unique identifier of the aviary to remove.
     *
     * Deletes both the aviary and its associations from the database.
     */
    void removeAviary(const string& id);

    /// @}

    /// @name Relationship Management
    /// @{

    /**
     * @brief Updates the employee assignment for a specific aviary.
     * @param aviaryId ID of the aviary.
     * @param employeeId ID of the employee assigned to the aviary.
     *
     * Updates the database record to reflect the new responsible employee.
     */
    void updateAviaryEmployee(const string& aviaryId, const string& employeeId);

    /// @}

    /// @name Retrieval and Maintenance
    /// @{

    /**
     * @brief Retrieves all aviaries stored in the database.
     * @return Unordered map where each key is an aviary ID and the value is a shared pointer to an Aviary object.
     *
     * Used by higher-level managers to access all existing aviary data.
     */
    [[nodiscard]] unordered_map<string, shared_ptr<Aviary>> getAllAviaries();

    /**
     * @brief Removes all aviary records from the database.
     *
     * This is typically used for system resets or testing.
     */
    void clearAll();

    /// @}
};

#endif // AVIARYREPOSITORY_H

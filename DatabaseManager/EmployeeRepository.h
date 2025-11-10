/**
 * @file EmployeeRepository.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of the EmployeeRepository class used in the Zoo Management System.
 *
 * The EmployeeRepository class defines a data access layer for managing employee records
 * within the Zoo Management System. It interacts with the DatabaseManager to store,
 * update, and retrieve employee information, as well as to handle aviary assignments.
 *
 * @details
 * This class is used by EmployeeManager to synchronize in-memory employee data with
 * persistent storage. It provides CRUD operations, employee–aviary relationship updates,
 * and utility methods for bulk data access.
 */

#ifndef EMPLOYEEREPOSITORY_H
#define EMPLOYEEREPOSITORY_H

#include "DatabaseManager.h"
#include <unordered_map>
#include <memory>

using namespace std;

class Employee;
class EmployeeManager;

/**
 * @class EmployeeRepository
 * @brief Provides persistent storage and database access for Employee entities.
 *
 * The EmployeeRepository encapsulates SQL-level operations for the Employee table.
 * It supports insertion, deletion, reassignment between aviaries, and removal from them.
 *
 * @note This class depends on the DatabaseManager for executing SQL statements
 * and is used by EmployeeManager for synchronization.
 * @see DatabaseManager, EmployeeManager, Employee
 *
 * @example
 * @code
 * DatabaseManager db("zoo.db");
 * EmployeeRepository repo(db);
 * repo.initTable();
 * repo.addEmployee(Employee("E001", "John Doe", 35, 1200, 10, "A1,A2"));
 * repo.assignEmployeeToAviary("E001", "A3");
 * auto employees = repo.getAllEmployes();
 * @endcode
 */
class EmployeeRepository {

private:
    DatabaseManager& db; ///< Reference to the database interface used for persistence.

public:
    /// @name Constructors and Initialization
    /// @{

    /**
     * @brief Constructs an EmployeeRepository connected to a database.
     * @param database Reference to the DatabaseManager instance.
     *
     * Establishes the repository interface for performing employee data operations.
     */
    explicit EmployeeRepository(DatabaseManager& database) : db(database) {}

    /**
     * @brief Initializes the employee table in the database.
     *
     * Creates the necessary table structure for employee data if it does not already exist.
     */
    void initTable();

    /// @}

    /// @name Employee Management
    /// @{

    /**
     * @brief Adds a new employee record to the database.
     * @param e Reference to the Employee object to insert.
     *
     * Stores all essential information about the employee, including their ID, name,
     * age, salary, experience, and aviary assignments.
     */
    void addEmployee(const Employee& e);

    /**
     * @brief Removes an employee record from the database.
     * @param id Unique identifier of the employee to remove.
     *
     * Deletes both the employee data and their aviary relationships from the database.
     */
    void removeEmployee(const string& id);

    /// @}

    /// @name Employee–Aviary Relationship Management
    /// @{

    /**
     * @brief Moves an employee from one aviary to another.
     * @param employeeId ID of the employee being moved.
     * @param oldAviary ID of the current aviary.
     * @param newAviary ID of the destination aviary.
     *
     * Updates the database to reflect the employee’s new assignment.
     */
    void moveEmployee(const string& employeeId, const string& oldAviary, const string& newAviary);

    /**
     * @brief Assigns an employee to a specific aviary.
     * @param employeeId ID of the employee to assign.
     * @param aviaryId ID of the aviary to which the employee will be assigned.
     * @return True if the assignment was successful, false otherwise.
     *
     * Creates a new record linking the employee and the specified aviary.
     */
    bool assignEmployeeToAviary(const string& employeeId, const string& aviaryId);

    /**
     * @brief Removes an employee from an aviary.
     * @param employeeId ID of the employee.
     * @param aviaryId ID of the aviary to remove the employee from.
     * @return True if the relationship was successfully removed, false otherwise.
     *
     * Deletes the record linking the specified employee to the given aviary.
     */
    bool removeEmployeeFromAviary(const string& employeeId, const string& aviaryId);

    /// @}

    /// @name Data Retrieval and Maintenance
    /// @{

    /**
     * @brief Retrieves all employees from the database.
     * @return Unordered map of employee IDs mapped to shared Employee pointers.
     *
     * Used to populate in-memory structures during initialization or synchronization.
     */
    [[nodiscard]] unordered_map<string, shared_ptr<Employee>> getAllEmployes();

    /**
     * @brief Clears all employee records from the database.
     *
     * Removes all employees and associated relationships — primarily for system resets or testing.
     */
    void clearAll();

    /// @}
};

#endif // EMPLOYEEREPOSITORY_H

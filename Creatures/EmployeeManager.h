/**
 * @file EmployeeManager.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of the EmployeeManager class used in the Zoo Management System.
 *
 * The EmployeeManager class is responsible for managing all zoo staff members.
 * It maintains a collection of employees, provides methods to assign or remove
 * them from aviaries, handles employee creation, loading, and reassignment,
 * and ensures synchronization between the in-memory data and the repository.
 *
 * @details
 * The class acts as an intermediary between the business logic (ZooGraph) and
 * the data persistence layer (EmployeeRepository). It provides efficient access
 * to employee records and supports common operations such as searching, linking,
 * and displaying information.
 */

#ifndef EMPLOYEEMANAGER_H
#define EMPLOYEEMANAGER_H

#include "Employee.h"
#include "../DatabaseManager/EmployeeRepository.h"
#include <unordered_map>
#include <vector>
#include <memory>

class ZooGraph;

/**
 * @class EmployeeManager
 * @brief Centralized manager for handling all employee-related operations.
 *
 * The EmployeeManager maintains an internal map of all zoo employees, allowing
 * efficient querying, assignment management, and synchronization with
 * persistent storage. It ensures that employees are properly assigned to
 * aviaries and can be reassigned or removed when necessary.
 *
 * @note This class interacts closely with ZooGraph and EmployeeRepository.
 * @see ZooGraph, EmployeeRepository, Employee
 *
 * @example
 * @code
 * EmployeeManager manager(graph, repo);
 * manager.addEmployee(make_shared<Employee>("E001", "John Doe", 35, 1200, 10, "A1,A2"));
 * manager.assignEmployeeToAviary("E001", "A3");
 * manager.listAllEmployees();
 * @endcode
 */
class EmployeeManager {

private:
    ZooGraph& zooGraph; ///< Reference to the zoo structure (ZooGraph) managing relationships.
    EmployeeRepository& employeeRepo; ///< Reference to the employee repository (persistent storage handler).
    unordered_map<string, shared_ptr<Employee>> employees; ///< In-memory collection of all employees, indexed by ID.

public:
    /// @name Constructors and Initialization
    /// @{

    /**
     * @brief Constructs an EmployeeManager instance.
     * @param graph Reference to the zoo's structure graph.
     * @param employeeRepo Reference to the employee repository for persistence.
     *
     * Initializes the manager and prepares it for operations such as loading,
     * assignment, and synchronization.
     */
    EmployeeManager(ZooGraph& graph, EmployeeRepository& employeeRepo);

    /**
     * @brief Loads all employees from the repository into memory.
     * @param employeeRepo Reference to the employee repository to read data from.
     *
     * Typically used during system initialization to populate the in-memory
     * employee map with existing data from storage.
     */
    void loadEmployeesFromRepo(EmployeeRepository& employeeRepo);

    /// @}

    /// @name Accessors and Queries
    /// @{

    /**
     * @brief Retrieves an employee by their unique identifier.
     * @param id Unique employee ID.
     * @return Shared pointer to the Employee object, or nullptr if not found.
     */
    [[nodiscard]] shared_ptr<Employee> getEmployee(const string& id) const;

    /**
     * @brief Retrieves all employees currently managed by the system.
     * @return Constant reference to the internal employee map.
     */
    [[nodiscard]] const unordered_map<string, shared_ptr<Employee>>& getAllEmployees() const;

    /**
     * @brief Retrieves a list of employees not currently assigned to any aviary.
     * @return Vector of shared pointers to unassigned Employee objects.
     */
    [[nodiscard]] vector<shared_ptr<Employee>> getUnassignedEmployees() const;

    /// @}

    /// @name Employee Management Operations
    /// @{

    /**
     * @brief Adds a new employee to the system.
     * @param employee Shared pointer to the Employee object to add.
     * @return True if successfully added, false otherwise.
     *
     * The new employee is added both to memory and the underlying repository.
     */
    bool addEmployee(const shared_ptr<Employee>& employee);

    /**
     * @brief Removes an employee from the system entirely.
     * @param id ID of the employee to remove.
     * @return True if the removal was successful, false otherwise.
     */
    bool removeEmployee(const string& id);

    /// @}

    /// @name Assignment and Reassignment Operations
    /// @{

    /**
     * @brief Assigns an employee to a specific aviary.
     * @param employeeId ID of the employee.
     * @param aviaryId ID of the aviary to assign.
     * @return True if the assignment was successful, false otherwise.
     *
     * Updates the employee’s record and may trigger repository synchronization.
     */
    bool assignEmployeeToAviary(const string& employeeId, const string& aviaryId);

    /**
     * @brief Reassigns an employee from one aviary to another.
     * @param empId ID of the employee.
     * @param fromAviaryId ID of the current aviary.
     * @param toAviaryId ID of the target aviary.
     * @return True if reassignment succeeded, false otherwise.
     */
    bool reassignEmployee(const string& empId, const string& fromAviaryId, const string& toAviaryId);

    /**
     * @brief Removes an employee's assignment from a specific aviary.
     * @param employeeId ID of the employee.
     * @param aviaryId ID of the aviary to remove the employee from.
     * @return True if successfully unassigned, false otherwise.
     */
    bool removeEmployeeFromAviary(const string& employeeId, const string& aviaryId);

    /// @}

    /// @name Display and Debugging
    /// @{

    /**
     * @brief Prints a formatted list of all employees.
     *
     * Displays all basic information such as ID, name, age, salary,
     * experience, and assigned aviaries. Useful for logging and UI rendering.
     */
    void listAllEmployees() const;

    /// @}
};

#endif // EMPLOYEEMANAGER_H

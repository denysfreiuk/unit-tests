/**

* @file Employee.h
* @author Denys Freyuk
* @date 27.10.2025
* @version 1.1
* @brief Declaration of the Employee class used in the Zoo Management System.
*
* This header defines the Employee class, which represents a zoo employee
* responsible for maintaining one or several aviaries. Each employee has
* basic personal and professional information, including a list of aviary IDs
* they are assigned to. The class provides a full interface for managing
* employee data, linking with aviaries, and generating formatted information
* about the employee.
  */

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <vector>
#include <string>

using namespace std;

class ZooGraph;

/**

* @class Employee
* @brief Represents an employee in the zoo management system.
*
* The Employee class encapsulates all information related to a zoo worker:
* identification, personal details, salary, work experience, and the aviaries
* under their supervision. It also includes utility methods for modifying
* assignments, generating formatted info strings, and checking assignment status.
*
* @note This class is part of the ZooGraph subsystem and interacts with aviary data.
* @see ZooGraph
*
* @example
* @code
* Employee emp("E001", "John Doe", 35, 1200, 10, "A1,A2,A3");
* cout << emp.getFullInfoAboutEmployee() << endl;
* emp.assignAviary("A4");
* emp.replaceAviary("A1", "A5");
* @endcode
  */
  class Employee {
  private:
  string id;                      ///< Unique employee identifier (e.g., "E001")
  string name;                    ///< Full name of the employee
  int age;                        ///< Employee's age in years
  int salary;                     ///< Monthly salary in monetary units
  int experience;                 ///< Work experience in years
  vector<string> aviaryIds;       ///< List of aviary IDs assigned to the employee

public:
/**
* @brief Constructs a fully initialized Employee object.
* @param id Unique employee identifier.
* @param name Full name of the employee.
* @param age Employee’s age.
* @param salary Monthly salary amount.
* @param experience Years of professional experience.
* @param aviaryIds Comma-separated list of aviary IDs (e.g. "A1,A2,A3").
*
* This constructor is typically used when reading data from a file or database.
*/
Employee(const string& id, const string& name, int age, int salary, int experience, const string& aviaryIds);

/**
 * @brief Constructs a new Employee object without an explicit ID or aviaries.
 * @param name Full name of the employee.
 * @param age Employee’s age.
 * @param salary Monthly salary amount.
 * @param experience Years of professional experience.
 *
 * The ID is typically assigned automatically later (e.g., by a repository class).
 */
Employee(const string& name, int age, int salary, int experience);

/// @name Basic Getters
/// @{

/** @return The unique identifier of the employee. */
[[nodiscard]] string getId() const;

/** @return The employee's name. */
[[nodiscard]] string getName() const;

/** @return The employee's age. */
[[nodiscard]] int getAge() const;

/** @return The employee's monthly salary. */
[[nodiscard]] int getSalary() const;

/** @return The employee's total years of work experience. */
[[nodiscard]] int getExperience() const;

/// @}

/// @name Aviary Management
/// @{

/**
 * @brief Returns a comma-separated string of assigned aviary IDs.
 * @return A formatted string (e.g., "A1, A2, A3").
 */
[[nodiscard]] string getAssignedAviaries() const;

/**
 * @brief Sets assigned aviaries using a formatted string.
 * @param assignedAviaries Comma-separated aviary list (e.g., "A1,A2,A3").
 */
void setAssignedAviaries(const string& assignedAviaries);

/**
 * @brief Sets assigned aviaries using a vector of strings.
 * @param assignedAviaries Vector of aviary identifiers.
 */
void setAssignedAviaries(vector<string> assignedAviaries);

/**
 * @brief Converts a comma-separated string into a vector of aviary IDs.
 * @param assignedAviaries Input string of IDs.
 * @return Vector of parsed aviary IDs.
 */
vector<string> assignedAviaries(const string& assignedAviaries);

/**
 * @brief Assigns a new aviary to the employee.
 * @param aviary ID of the aviary to be added.
 *
 * If the aviary already exists in the list, it is not duplicated.
 */
void assignAviary(const string& aviary);

/**
 * @brief Replaces an existing aviary assignment with another.
 * @param fromAviary ID of the current aviary.
 * @param toAviary ID of the new aviary to replace with.
 *
 * If `fromAviary` is not found, no change occurs.
 */
void replaceAviary(const string& fromAviary, const string& toAviary);

/**
 * @brief Removes an aviary from the employee’s assignment list.
 * @param aviaryId ID of the aviary to remove.
 */
void removeAviary(const string& aviaryId);

/**
 * @brief Checks whether the employee is currently assigned to any aviary.
 * @return True if the employee has at least one aviary assigned, false otherwise.
 */
[[nodiscard]] bool isAssigned() const;

/**
 * @brief Returns the vector of assigned aviary IDs.
 * @return Constant reference to the aviary ID vector.
 */
[[nodiscard]] const vector<string>& getAviaryIds() const;

/// @}

/// @name Information Output
/// @{

/**
 * @brief Returns a formatted string containing all employee information.
 * @return Multi-field formatted summary (ID, name, age, salary, experience, aviaries).
 *
 * This method is useful for displaying detailed employee information in UI or logs.
 */
[[nodiscard]] string getFullInfoAboutEmployee() const;

/**
 * @brief Generates a simple list of aviary IDs assigned to the employee.
 * @return A formatted string suitable for display or logging.
 */
[[nodiscard]] string listAviaries() const;

/// @}

};

#endif // EMPLOYEE_H

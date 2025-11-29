/**
 * @file Account.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of the Account and Role entities for the Zoo Management System.
 *
 * This header defines the `Account` class and `Role` enumeration used to represent
 * authentication and authorization data in the Zoo Management System.
 * Each account has a username, hashed password, and a specific role (ADMIN, MANAGER, EMPLOYEE).
 * The class provides utility methods for serialization, deserialization, and role conversions.
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <sstream>

using namespace std;

/**
 * @enum Role
 * @brief Represents user access levels within the Zoo Management System.
 *
 * The Role enumeration defines the hierarchy of user privileges:
 * administrators have full access, managers handle staff and operations,
 * and employees have limited access for daily tasks.
 *
 * @example
 * @code
 * Role r = Role::MANAGER;
 * string roleName = Account::roleToString(r);
 * @endcode
 */
enum class Role {
    ADMIN = 0,   ///< Full system access and administrative privileges.
    MANAGER = 1, ///< Managerial access — can modify employee and animal data.
    EMPLOYEE = 2 ///< Standard employee access — limited operational rights.
};

/**
 * @class Account
 * @brief Represents a user account in the Zoo Management System.
 *
 * The Account class stores user authentication details (username, password hash)
 * and authorization role. It provides convenient serialization for saving
 * to persistent storage and deserialization for loading from files or databases.
 *
 * @details
 * Passwords are not stored in plaintext — instead, a secure hash is kept.
 * The class supports conversions between `Role` enums, integer codes, and
 * their string representations for storage or UI display.
 *
 * @example
 * @code
 * Account admin("admin", 12345678, Role::ADMIN);
 * cout << admin.serialize() << endl;
 * @endcode
 */
class Account {

private:
    string username;    ///< Unique username for system login.
    size_t passwordHash;///< Hashed password (for secure authentication).
    Role role;          ///< User role defining system privileges.

public:
    /// @name Constructors
    /// @{

    /** @brief Default constructor for an empty Account object. */
    Account() = default;

    /**
     * @brief Constructs a fully initialized account.
     * @param u Username of the account.
     * @param hash Password hash.
     * @param r User role (ADMIN, MANAGER, EMPLOYEE).
     *
     * This constructor is typically used when creating or loading user records.
     */
    Account(string u, size_t hash, Role r);

    /// @}

    /// @name Getters
    /// @{

    /** @return Constant reference to the account's username. */
    [[nodiscard]] const string& getUsername() const;

    /** @return The hashed password value. */
    [[nodiscard]] size_t getPasswordHash() const;

    /** @return The role assigned to this account. */
    [[nodiscard]] Role getRole() const;

    /// @}

    /// @name Role Conversion Utilities
    /// @{

    /**
     * @brief Converts a Role enumeration to a readable string.
     * @param r Role value.
     * @return String representation of the role (e.g., "ADMIN", "MANAGER", "EMPLOYEE").
     */
    static string roleToString(Role r);

    /**
     * @brief Converts an integer to a corresponding Role value.
     * @param v Integer value (0, 1, 2).
     * @return Corresponding Role enum.
     *
     * @note If the value is invalid, defaults to Role::EMPLOYEE.
     */
    static Role intToRole(int v);

    /**
     * @brief Converts a Role enum to its integer equivalent.
     * @param r Role value.
     * @return Integer representation (0, 1, 2).
     */
    static int roleToInt(Role r);

    /// @}

    /// @name Serialization
    /// @{

    /**
     * @brief Serializes account data into a single line string.
     * @return Formatted string combining username, hash, and role.
     *
     * @example
     * @code
     * Account acc("user", 987654, Role::EMPLOYEE);
     * string data = acc.serialize();
     * @endcode
     */
    [[nodiscard]] string serialize() const;

    /**
     * @brief Deserializes a line of text into an Account object.
     * @param line Input line containing serialized account data.
     * @return Deserialized Account instance.
     *
     * @example
     * @code
     * Account restored = Account::deserialize("user 987654 2");
     * @endcode
     */
    static Account deserialize(const string& line);

    /// @}
};

#endif // ACCOUNT_H

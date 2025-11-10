/**
 * @file AccountRepository.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of the AccountRepository class used in the Zoo Management System.
 *
 * The AccountRepository class provides the data access layer for all account-related
 * operations in the Zoo Management System. It communicates with the DatabaseManager
 * to execute SQL-like queries for creating, updating, retrieving, and deleting user
 * accounts. This class isolates the persistence logic from higher-level application code.
 *
 * @details
 * The repository interacts with the database using the DatabaseManager interface.
 * It handles CRUD operations for Account objects, manages user roles, and supports
 * initialization of account tables. It is primarily used by AuthManager for authentication.
 */

#ifndef ACCOUNTREPOSITORY_H
#define ACCOUNTREPOSITORY_H

#include "DatabaseManager.h"
#include "../Accounts/Account.h"
#include <string>
#include <vector>
#include <optional>

using namespace std;

/**
 * @class AccountRepository
 * @brief Provides persistent storage and retrieval operations for Account objects.
 *
 * The AccountRepository encapsulates all database operations related to user accounts.
 * It enables the creation, modification, deletion, and querying of user credentials,
 * maintaining a consistent interface for the authentication system.
 *
 * @note This class depends on DatabaseManager for executing SQL operations.
 * @see DatabaseManager, Account, AuthManager
 *
 * @example
 * @code
 * DatabaseManager db("zoo.db");
 * AccountRepository repo(db);
 * repo.initTable();
 * repo.addAccount("admin", 123456, Role::ADMIN);
 * auto accounts = repo.getAllAccounts();
 * @endcode
 */
class AccountRepository {

private:
    DatabaseManager& db; ///< Reference to the database interface for executing operations.

public:
    /// @name Constructors and Initialization
    /// @{

    /**
     * @brief Constructs an AccountRepository bound to a database instance.
     * @param database Reference to the DatabaseManager instance.
     *
     * This establishes a persistent connection for performing account-related operations.
     */
    explicit AccountRepository(DatabaseManager& database);

    /**
     * @brief Initializes the accounts table in the database.
     *
     * Ensures the necessary schema exists for storing account data
     * (username, password hash, and role fields).
     */
    void initTable();

    /// @}

    /// @name CRUD Operations
    /// @{

    /**
     * @brief Adds a new account record to the database.
     * @param username Unique username of the account.
     * @param passwordHash Secure hash of the account password.
     * @param role Role assigned to the account (ADMIN, MANAGER, EMPLOYEE).
     * @return True if the operation succeeded, false otherwise.
     */
    bool addAccount(const string& username, size_t passwordHash, Role role);

    /**
     * @brief Removes an account record from the database.
     * @param username Username of the account to remove.
     * @return True if the deletion succeeded, false otherwise.
     */
    bool removeAccount(const string& username);

    /**
     * @brief Updates an existing account record.
     * @param username Current username to identify the record.
     * @param newUsername New username (optional).
     * @param newPasswordHash New password hash (optional).
     * @param newRole New user role (optional).
     * @return True if the update succeeded, false otherwise.
     *
     * @details
     * Allows partial updates — any optional parameter left unset will keep its previous value.
     */
    bool updateAccount(const string& username,
                       const string& newUsername,
                       optional<size_t> newPasswordHash,
                       optional<Role> newRole);

    /// @}

    /// @name Retrieval and Queries
    /// @{

    /**
     * @brief Retrieves a single account by its username.
     * @param username Username of the account.
     * @return Optional containing the Account object if found; empty otherwise.
     */
    [[nodiscard]] optional<Account> getAccount(const string& username);

    /**
     * @brief Retrieves all accounts from the database.
     * @return A vector of Account objects representing all registered users.
     */
    [[nodiscard]] vector<Account> getAllAccounts();

    /**
     * @brief Checks whether an account with a given username exists in the database.
     * @param username Username to check.
     * @return True if the account exists, false otherwise.
     */
    [[nodiscard]] bool accountExists(const string& username);

    /// @}
};

#endif // ACCOUNTREPOSITORY_H

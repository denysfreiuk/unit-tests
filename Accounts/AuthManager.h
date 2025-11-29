/**
 * @file AuthManager.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of the AuthManager class for the Zoo Management System.
 *
 * The AuthManager class is responsible for user authentication, registration,
 * and account management. It interacts with the AccountRepository to verify
 * credentials, manage roles, and perform CRUD operations on user accounts.
 *
 * @details
 * This class encapsulates all logic related to user login and account control,
 * including verifying username and password combinations, listing users,
 * and modifying or deleting existing accounts. It supports both interactive
 * authentication and direct method-based operations.
 */

#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include "Account.h"
#include <optional>
#include <string>
#include <vector>

class AccountRepository;

/**
 * @class AuthManager
 * @brief Provides authentication and account management functionality.
 *
 * The AuthManager acts as an intermediary between the application logic
 * and the account database. It provides a consistent interface for:
 * - authenticating users,
 * - adding new accounts,
 * - editing and removing existing ones,
 * - listing registered usernames.
 *
 * @note This class operates on top of the AccountRepository and depends on it
 * for persistent data storage and retrieval.
 * @see Account, AccountRepository, Role
 *
 * @example
 * @code
 * AuthManager auth(repo);
 * if (auto result = auth.authenticateInteractive()) {
 *     cout << "Welcome, " << result->first << endl;
 * }
 * auth.addAccount("admin", "12345", Role::ADMIN);
 * @endcode
 */
class AuthManager {

private:
    AccountRepository& repo; ///< Reference to the account repository handling storage.

public:
    /// @name Constructors
    /// @{

    /**
     * @brief Constructs an AuthManager instance.
     * @param repository Reference to the AccountRepository for account data access.
     *
     * Initializes the authentication system with the provided repository.
     */
    explicit AuthManager(AccountRepository& repository);

    /// @}

    /// @name Authentication
    /// @{

    /**
     * @brief Authenticates a user interactively (e.g., via console input).
     * @return An optional pair containing the username and role if authentication succeeds;
     *         otherwise, an empty optional.
     *
     * @details
     * This method requests credentials from the user, verifies them against
     * stored accounts, and returns the corresponding account information upon success.
     */
    [[nodiscard]] std::optional<std::pair<std::string, Role>> authenticateInteractive();

    /// @}

    /// @name Account Management
    /// @{

    /**
     * @brief Adds a new account to the system.
     * @param username Unique username for the new account.
     * @param password Plaintext password to be securely hashed.
     * @param role Role of the new account (ADMIN, MANAGER, EMPLOYEE).
     * @return True if the account was successfully created, false otherwise.
     *
     * @note Passwords are hashed before being stored.
     */
    bool addAccount(const std::string& username, const std::string& password, Role role);

    /**
     * @brief Removes an existing account.
     * @param username Username of the account to remove.
     * @return True if the account was successfully deleted, false otherwise.
     */
    bool removeAccount(const std::string& username);

    /**
     * @brief Edits an existing account.
     * @param username Username of the account to modify.
     * @return True if the account was successfully updated, false otherwise.
     *
     * @details
     * This method allows updating account details such as role or password.
     */
    bool editAccount(const std::string& username);

    /// @}

    /// @name Queries and Utilities
    /// @{

    /**
     * @brief Checks whether an account with the given username exists.
     * @param username Username to check.
     * @return True if the account exists, false otherwise.
     */
    [[nodiscard]] bool accountExists(const std::string& username) const;

    /**
     * @brief Retrieves a list of all registered usernames.
     * @return Vector containing all usernames in the system.
     */
    [[nodiscard]] std::vector<std::string> listUsernames() const;

    /// @}
};

#endif // AUTHMANAGER_H

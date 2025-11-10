/**
 * @file Menu.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of the Menu class used to route users to their respective interfaces.
 *
 * The Menu class serves as the central entry point for user interaction within
 * the Zoo Management System. Depending on the user’s role (Admin, Manager, or Employee),
 * it launches the corresponding interface module.
 *
 * @details
 * The `Menu` class simplifies program flow by abstracting role-based redirection.
 * It connects authentication (via `AuthManager`) with the structural logic
 * (via `ZooGraph`) and delegates control to the proper menu handler:
 * - **Admin** → `AdminMenu::show()`
 * - **Manager** → `ManagerMenu::show()`
 * - **Employee** → `EmployeeMenu::show()`
 *
 * @example
 * @code
 * AuthManager auth(repo);
 * ZooGraph zoo(avRepo, pathRepo, animalRepo, empRepo);
 *
 * string username = "admin";
 * Role role = Role::ADMIN;
 *
 * Menu::showFor(username, role, auth, zoo);
 * @endcode
 */

#ifndef MENU_H
#define MENU_H

#include "../Accounts/Account.h"
#include "../Accounts/AuthManager.h"
#include "../Graphs/ZooGraph.h"
#include <string>

/**
 * @class Menu
 * @brief Handles the main user interface routing by user role.
 *
 * The `Menu` class determines which role-specific interface to display
 * (Administrator, Manager, or Employee) and delegates control to the
 * corresponding menu namespace. It acts as a high-level controller in
 * the application’s user interaction layer.
 *
 * @note This class does not maintain any state — all methods are static.
 */
class Menu {

public:
    /// @name Interface Routing
    /// @{

    /**
     * @brief Displays the appropriate menu interface for a given user.
     * @param username The username of the currently logged-in account.
     * @param role The user’s role (Admin, Manager, or Employee).
     * @param auth Reference to the authentication manager.
     * @param zoo Reference to the main ZooGraph containing zoo data.
     *
     * @details
     * This static method acts as the main dispatcher. It determines the user’s
     * privileges and routes execution flow to the correct interactive console menu.
     */
    static void showFor(const std::string& username, Role role, AuthManager& auth, ZooGraph& zoo);

    /// @}
};

#endif // MENU_H

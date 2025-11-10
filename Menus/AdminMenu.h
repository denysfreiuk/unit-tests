/**
* @file AdminMenu.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of the AdminMenu namespace used in the Zoo Management System.
 *
 * The AdminMenu module defines functions for displaying and managing the
 * administrator interface of the Zoo Management System. It integrates
 * authentication, employee and animal management, and system-level operations.
 *
 * @details
 * The menu provides access to administrative tools such as:
 * - Viewing and editing user accounts;
 * - Managing aviaries, paths, and assigned employees;
 * - Viewing and modifying animals and their locations;
 * - Monitoring system logs and connectivity.
 *
 * @example
 * @code
 * #include "AdminMenu.h"
 *
 * AuthManager auth(repo);
 * ZooGraph zoo(avRepo, pathRepo, animalRepo, empRepo);
 * AdminMenu::show("admin", auth, zoo);
 * @endcode
 */

#ifndef ADMINMENU_H
#define ADMINMENU_H

#include "../Accounts/AuthManager.h"
#include "../Graphs/ZooGraph.h"

/**
 * @namespace AdminMenu
 * @brief Contains functions related to the administrator’s console menu.
 *
 * Provides an interactive interface for system administrators
 * to manage data within the ZooGraph and handle user accounts.
 */
namespace AdminMenu {

    /**
     * @brief Displays the main administrator menu interface.
     * @param username The name of the currently logged-in administrator.
     * @param auth Reference to the authentication manager used for account operations.
     * @param zoo Reference to the ZooGraph containing all zoo data and managers.
     *
     * @details
     * This function serves as the entry point for the admin control panel.
     * It provides navigation through user management, animal management,
     * aviary operations, and path visualization.
     */
    void show(const std::string& username, AuthManager& auth, ZooGraph& zoo);
}

#endif // ADMINMENU_H

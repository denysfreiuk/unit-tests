/**
 * @file ManagerMenu.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of the ManagerMenu namespace used in the Zoo Management System.
 *
 * The ManagerMenu module provides the interactive interface for zoo managers.
 * It allows management of animals, aviaries, and employees under the manager’s supervision,
 * as well as general system monitoring operations.
 *
 * @details
 * The ManagerMenu serves as a mid-level administrative control panel that
 * complements the higher-privileged AdminMenu. It enables managers to:
 * - View and feed animals;
 * - Assign or reassign employees;
 * - Manage aviaries and occupancy;
 * - Review zoo structure and paths.
 *
 * @example
 * @code
 * #include "ManagerMenu.h"
 *
 * AuthManager auth(repo);
 * ZooGraph zoo(avRepo, pathRepo, animalRepo, empRepo);
 * ManagerMenu::show("manager", auth, zoo);
 * @endcode
 */

#ifndef MANAGERMENU_H
#define MANAGERMENU_H

#include "../Accounts/Account.h"
#include "../Accounts/AuthManager.h"
#include "../Graphs/ZooGraph.h"
#include <string>

/**
 * @namespace ManagerMenu
 * @brief Contains functions for the zoo manager’s control interface.
 *
 * Provides menu-based interaction for managing employees, aviaries, and animals.
 * The functions within this namespace are used to handle real-time operations
 * in the zoo under the manager's authority.
 */
namespace ManagerMenu {

    /**
     * @brief Displays the main manager menu interface.
     * @param username The name of the currently logged-in manager.
     * @param auth Reference to the AuthManager used for authentication operations.
     * @param zoo Reference to the ZooGraph instance managing zoo data and relations.
     *
     * @details
     * This function acts as the entry point for the zoo manager’s console interface.
     * It enables access to data manipulation tools such as:
     * - Animal feeding and relocation;
     * - Employee reassignment;
     * - Aviary and path management.
     */
    void show(const std::string& username, AuthManager& auth, ZooGraph& zoo);
}

#endif // MANAGERMENU_H

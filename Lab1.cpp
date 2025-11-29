/**
 * @file Lab1.cpp
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Entry point for the Zoo Management System (Lab 1 implementation).
 *
 * @details
 * This file contains the main function that initializes and runs
 * the Zoo Management System. It connects all core subsystems:
 * - Database management and repositories;
 * - Authentication and user role routing;
 * - Zoo graph construction and interaction logic;
 * - Central logging through `LoggerGlobal`.
 *
 * The program supports interactive login and role-based menus:
 * - **Admin** → full system control (`AdminMenu`)
 * - **Manager** → management of employees and animals (`ManagerMenu`)
 * - **Employee** → feeding and reporting tasks (`EmployeeMenu`)
 *
 * ANSI color output is enabled automatically on Windows.
 *
 * @example
 * @code
 * // Typical launch
 * > ./ZooManagementSystem
 * Username: admin
 * Password: *****
 * [INFO] Welcome, admin!
 * @endcode
 */

#include "Logger/LoggerGlobal.h"
#include "Graphs/ZooGraph.h"
#include "Menus/Menu.h"
#include "DatabaseManager/AccountRepository.h"
#include <string>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
/**
 * @brief Enables ANSI color sequences for Windows console output.
 * @note Called automatically at program startup under Windows.
 */
void enableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

using namespace std;

/**
 * @brief Main entry point of the Zoo Management System.
 *
 * @details
 * Initializes all database repositories, authentication, and the
 * zoo graph model. Prompts the user to log in, then opens the corresponding
 * role-based interface using `Menu::showFor()`.
 *
 * @return Exit status code (0 for success).
 */
int main() {
#ifdef _WIN32
    enableANSI();
#endif

    // === Initialization of core components ===
    DatabaseManager db("zoo.db");
    AccountRepository accRepo(db);
    AuthManager auth(accRepo);
    AviaryRepository aviaryRepo(db);
    PathRepository pathRepo(db);
    AnimalRepository animalRepo(db);
    EmployeeRepository employeeRepo(db);
    ZooGraph zoo(aviaryRepo, pathRepo, animalRepo, employeeRepo);

    // === Interactive authentication loop ===
    while (true) {
        auto session = auth.authenticateInteractive();
        if (!session.has_value()) {
            cout << "Try again? (y/n): ";
            char c; cin >> c;
            if (c == 'y' || c == 'Y') continue;
            break;
        }

        string username = session->first;
        Role role = session->second;

        // Launch corresponding role-based menu
        Menu::showFor(username, role, auth, zoo);

        cout << "Exit the program or return to login? (q - exit, any other key - login): ";
        char c; cin >> c;
        if (c == 'q' || c == 'Q') break;
    }

    cout << "Bye!\n";
    return 0;
}

/**
* @file SQLUtils.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of SQL utility functions for the Zoo Management System.
 *
 * The SQLUtils header defines helper functions for safely constructing SQL queries.
 * These utilities handle special character escaping and help prevent SQL injection
 * when working with dynamically built SQL strings.
 *
 * @details
 * This file is part of the database layer utilities used by repository classes.
 * The provided helper function escapes user input before inserting it into
 * SQL statements to ensure proper syntax and safety.
 */

#ifndef SQLUTILS_H
#define SQLUTILS_H

#include <string>

using namespace std;

/**
 * @brief Escapes a string value to make it safe for use in SQL statements.
 * @param value The input string to escape.
 * @return A new string with all special SQL characters properly escaped.
 *
 * @details
 * The function replaces single quotes and other critical SQL characters
 * with their escaped equivalents to prevent injection attacks.
 *
 * @note Always use this function before concatenating user input into SQL queries.
 *
 * @example
 * @code
 * string name = "O'Reilly";
 * string safe = escapeSQL(name);
 * // Result: "O''Reilly"
 * @endcode
 */
string escapeSQL(const string& value);

#endif // SQLUTILS_H

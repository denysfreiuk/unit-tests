/**
 * @file Logger.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of the Logger class used for system logging.
 *
 * The Logger class provides a simple but effective logging utility for
 * the Zoo Management System. It supports multiple log levels, colored console output,
 * and optional file logging for debugging and system monitoring.
 *
 * @details
 * The logger supports four log levels (DEBUG, INFO, WARN, ERROR), which can be enabled
 * or disabled individually. Messages are timestamped and color-coded in the console.
 *
 * @example
 * @code
 * Logger log("zoo_log.txt");
 * log.enable(Logger::DEBUG | Logger::INFO | Logger::ERROR);
 * log.info("Zoo system initialized successfully.");
 * log.error("Failed to load animal repository!");
 * @endcode
 */

#ifndef LOGGER_H
#define LOGGER_H

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#undef ERROR

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/**
 * @class Logger
 * @brief Provides configurable logging with multiple levels and color-coded output.
 *
 * This class supports output to both console and file. Logging levels
 * can be combined using bitwise flags to fine-tune verbosity.
 *
 * @note This class is part of the Zoo Management System core utilities.
 * @see Logger::Level
 */
class Logger {

public:
    /**
     * @enum Level
     * @brief Defines the available log severity levels.
     *
     * Levels can be combined via bitwise operations, e.g.:
     * `Logger::DEBUG | Logger::ERROR`.
     */
    enum Level {
        DEBUG = 1 << 0, ///< Detailed debugging information.
        INFO  = 1 << 1, ///< General operational information.
        WARN  = 1 << 2, ///< Warnings about potential issues.
        ERROR = 1 << 3  ///< Serious runtime errors.
    };

private:
    int flags;        ///< Bitmask representing active log levels.
    ofstream file;    ///< Output file stream for persistent logging.

    // === Console color codes for better visibility ===
    const string RESET  = "\033[0m";  ///< Resets color.
    const string GRAY   = "\033[94m"; ///< Debug/info messages.
    const string GREEN  = "\033[92m"; ///< Successful operations.
    const string YELLOW = "\033[93m"; ///< Warnings.
    const string RED    = "\033[91m"; ///< Errors.

    /**
     * @brief Returns the current system time formatted as a string.
     * @return Current time in HH:MM:SS format.
     */
    [[nodiscard]] string currentTime() const;

    /**
     * @brief Converts a log level to its string name.
     * @param lvl The log level.
     * @return Corresponding text label (e.g., "INFO", "ERROR").
     */
    [[nodiscard]] string levelToStr(Level lvl) const;

    /**
     * @brief Returns the ANSI color code for the given log level.
     * @param lvl The log level.
     * @return Corresponding ANSI color escape sequence.
     */
    [[nodiscard]] string levelToColor(Level lvl) const;

public:
    /// @name Constructors and Destructors
    /// @{

    /**
     * @brief Constructs a logger and optionally opens a file for logging.
     * @param filename Output file path (default: "log.txt").
     *
     * Opens the specified file in append mode. If the file cannot be opened,
     * logging will continue in the console only.
     */
    explicit Logger(const string& filename = "log.txt");

    /**
     * @brief Destructor — closes the file stream safely.
     */
    ~Logger();

    /// @}

    /// @name Configuration
    /// @{

    /**
     * @brief Enables one or more logging levels.
     * @param lvls Bitmask of levels to enable.
     *
     * Example: `enable(Logger::DEBUG | Logger::INFO);`
     */
    void enable(int lvls);

    /**
     * @brief Disables one or more logging levels.
     * @param lvls Bitmask of levels to disable.
     */
    void disable(int lvls);

    /**
     * @brief Checks if a log level is currently enabled.
     * @param lvl Log level to check.
     * @return True if enabled, false otherwise.
     */
    [[nodiscard]] bool isEnabled(Level lvl) const;

    /**
     * @brief Prints a list of currently enabled log levels.
     */
    void listEnabledLevels();

    /// @}

    /// @name Logging Methods
    /// @{

    /**
     * @brief Logs a message with a specific severity level.
     * @param lvl Log level to use.
     * @param msg Message text to log.
     *
     * Prepends the message with a timestamp, level, and color formatting.
     * If file logging is enabled, the message is also written to the log file.
     */
    void log(Level lvl, const string& msg);

    /**
     * @brief Logs a debug-level message.
     * @param msg Debug information to record.
     */
    void debug(const string& msg);

    /**
     * @brief Logs an informational message.
     * @param msg Informational text.
     */
    void info(const string& msg);

    /**
     * @brief Logs a warning message.
     * @param msg Warning text.
     */
    void warn(const string& msg);

    /**
     * @brief Logs an error message.
     * @param msg Error details.
     */
    void error(const string& msg);

    /// @}
};

#endif // LOGGER_H

/**
* @file LoggerGlobal.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of the global Logger instance for the Zoo Management System.
 *
 * This header exposes a single global `Logger` object that can be used across
 * the entire application for consistent logging. It allows all modules to log
 * messages without creating their own local instances.
 *
 * @details
 * The global logger simplifies integration between subsystems by providing
 * a shared logging interface. It is typically defined in `LoggerGlobal.cpp`
 * and initialized once at program startup.
 *
 * @example
 * @code
 * #include "LoggerGlobal.h"
 *
 * void initSystem() {
 *     logger.enable(Logger::INFO | Logger::ERROR);
 *     logger.info("System initialization complete.");
 * }
 * @endcode
 */

#ifndef LOGGERGLOBAL_H
#define LOGGERGLOBAL_H

#include "Logger.h"

/**
 * @brief Global instance of the Logger used throughout the Zoo Management System.
 *
 * Declared as `extern` to allow shared access across multiple translation units.
 * The instance is defined in `LoggerGlobal.cpp`.
 */
extern Logger logger;

#endif // LOGGERGLOBAL_H

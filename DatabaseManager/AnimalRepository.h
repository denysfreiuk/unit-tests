/**
 * @file AnimalRepository.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of the AnimalRepository class for the Zoo Management System.
 *
 * The AnimalRepository class provides the data access layer for animal-related
 * operations. It interacts with the DatabaseManager to store, retrieve, and manage
 * animal information and their aviary assignments in the database.
 *
 * @details
 * This class is responsible for persistent storage of Animal entities and for
 * maintaining the integrity of animal–aviary relationships. It supports basic
 * CRUD operations, linking, and movement tracking between aviaries.
 */

#ifndef ANIMALREPOSITORY_H
#define ANIMALREPOSITORY_H

#include "DatabaseManager.h"
#include <unordered_map>
#include <memory>

using namespace std;

class Animal;
class AnimalManager;

/**
 * @class AnimalRepository
 * @brief Provides database operations for Animal entities.
 *
 * The AnimalRepository encapsulates low-level database logic for handling
 * Animal objects. It allows insertion, removal, migration between aviaries,
 * and full retrieval of all stored animals.
 *
 * @note This class is used by AnimalManager to synchronize in-memory data with
 * the persistent database layer.
 * @see DatabaseManager, AnimalManager, Animal
 *
 * @example
 * @code
 * DatabaseManager db("zoo.db");
 * AnimalRepository repo(db);
 * repo.initTable();
 * repo.addAnimal(Animal("Leo", "Lion", 5, 180.0, "Mammal"));
 * auto animals = repo.getAllAnimals();
 * @endcode
 */
class AnimalRepository {

private:
    DatabaseManager& db; ///< Reference to the DatabaseManager for executing storage operations.

public:
    /// @name Constructors and Initialization
    /// @{

    /**
     * @brief Constructs an AnimalRepository linked to a database.
     * @param database Reference to the DatabaseManager instance.
     *
     * Establishes a connection for persistent animal operations.
     */
    explicit AnimalRepository(DatabaseManager& database) : db(database) {}

    /**
     * @brief Initializes the animal table in the database.
     *
     * Creates necessary structures for storing animal data and
     * maintaining relationships with aviaries.
     */
    void initTable();

    /// @}

    /// @name Animal Management
    /// @{

    /**
     * @brief Adds a new animal record to the database.
     * @param a Reference to the Animal object to store.
     *
     * The animal’s data (ID, name, species, age, weight, type, aviary)
     * is serialized and persisted in the database.
     */
    void addAnimal(const Animal& a);

    /**
     * @brief Removes an animal record from the database.
     * @param id Unique identifier of the animal to remove.
     * @return True if removal was successful, false otherwise.
     */
    bool removeAnimal(const string& id);

    /// @}

    /// @name Aviary Relationship Management
    /// @{

    /**
     * @brief Links an existing animal to an aviary.
     * @param aviaryId Identifier of the aviary.
     * @param animalId Identifier of the animal to assign.
     *
     * This creates a relationship entry between the given animal and aviary.
     */
    void addAnimalInAviary(const string& aviaryId, const string& animalId);

    /**
     * @brief Removes an animal–aviary association.
     * @param aviaryId ID of the aviary.
     * @param animalId ID of the animal to remove from the aviary.
     *
     * Used when an animal is moved or its enclosure assignment changes.
     */
    void removeAnimalFromAviary(const string& aviaryId, const string& animalId);

    /**
     * @brief Moves an animal between two aviaries.
     * @param id ID of the animal being moved.
     * @param oldAviaryId Current aviary ID.
     * @param newAviaryId Destination aviary ID.
     * @return True if the operation succeeded, false otherwise.
     *
     * @details
     * Updates the internal mapping of the animal to reflect its new location.
     */
    bool moveAnimal(const string& id, const string& oldAviaryId, const string& newAviaryId);

    /// @}

    /// @name Retrieval and Maintenance
    /// @{

    /**
     * @brief Retrieves all animals from the database.
     * @return Unordered map of animal IDs mapped to shared Animal pointers.
     *
     * Provides full access to stored animal data for higher-level managers.
     */
    [[nodiscard]] unordered_map<string, shared_ptr<Animal>> getAllAnimals();

    /**
     * @brief Clears all animal records from the database.
     *
     * This is a maintenance operation used for resetting or reinitializing the system.
     */
    void clearAll();

    /// @}
};

#endif // ANIMALREPOSITORY_H

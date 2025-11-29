/**
 * @file AnimalManager.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of the AnimalManager class used in the Zoo Management System.
 *
 * The AnimalManager class acts as a high-level controller responsible for
 * managing all animal-related operations in the zoo system. It interacts
 * with the ZooGraph (which represents the zoo’s structure) and the
 * AnimalRepository (which provides data persistence). The class maintains
 * a collection of all animals, supports creation, movement, feeding, and
 * linking to aviaries, and provides tools for synchronization and data queries.
 */

#ifndef ANIMALMANAGER_H
#define ANIMALMANAGER_H

#include "Animals.h"
#include "../DatabaseManager/AnimalRepository.h"
#include <unordered_map>
#include <vector>
#include <memory>

class ZooGraph;

/**
 * @class AnimalManager
 * @brief Centralized manager for handling animal operations.
 *
 * The AnimalManager is responsible for creating, assigning, feeding, and
 * relocating animals between aviaries. It maintains an in-memory map of
 * all animals for efficient access and ensures synchronization with the
 * underlying repository and zoo structure.
 *
 * @note This class is part of the ZooGraph subsystem and interacts with
 * both `ZooGraph` and `AnimalRepository`.
 * @see ZooGraph, AnimalRepository, Animal
 *
 * @example
 * @code
 * AnimalManager manager(graph, repo);
 * manager.createAnimal("Leo", "Lion", 5, 180.0, "Mammal");
 * manager.addAnimalInAviary("AV01", "A001");
 * manager.feedById("A001");
 * manager.listAllAnimals();
 * @endcode
 */
class AnimalManager {

private:
    ZooGraph& zooGraph; ///< Reference to the ZooGraph structure managing aviaries and relationships.
    AnimalRepository& animalRepo; ///< Reference to the AnimalRepository handling persistent storage.
    unordered_map<string, shared_ptr<Animal>> animals; ///< Map of all animals indexed by their unique IDs.

public:
    /// @name Constructors
    /// @{

    /**
     * @brief Constructs an AnimalManager instance.
     * @param graph Reference to the zoo's graph structure.
     * @param animalRepo Reference to the animal repository for data access.
     *
     * This constructor links the manager with the overall zoo structure and
     * database, allowing animal synchronization between memory and storage.
     */
    AnimalManager(ZooGraph& graph, AnimalRepository& animalRepo);

    /// @}

    /// @name Linking and Data Synchronization
    /// @{

    /**
     * @brief Links animals with their corresponding aviaries.
     *
     * This method synchronizes the in-memory list of animals with their
     * aviary assignments, ensuring consistent state between the ZooGraph
     * and AnimalRepository.
     */
    void linkAnimalsToAviaries();

    /// @}

    /// @name Accessors
    /// @{

    /**
     * @brief Retrieves all animals currently managed.
     * @return Constant reference to an unordered map of animal IDs to Animal objects.
     */
    [[nodiscard]] const unordered_map<string, shared_ptr<Animal>>& getAnimals() const;

    /// @}

    /// @name Animal Creation and Removal
    /// @{

    /**
     * @brief Creates a new animal and adds it to the repository and internal map.
     * @param name Animal's name.
     * @param species Biological species (e.g., tiger, parrot, snake).
     * @param age Age of the animal in years.
     * @param weight Weight of the animal in kilograms.
     * @param type General type (e.g., Mammal, Bird, Reptile).
     *
     * The animal is added both to the repository and the in-memory structure.
     */
    void createAnimal(const string& name, const string& species, int age, double weight, const string& type);

    /**
     * @brief Removes an animal completely from the system.
     * @param animalId ID of the animal to remove.
     * @return True if the removal was successful, false otherwise.
     *
     * This operation deletes the animal both from memory and from the repository.
     */
    bool removeAnimalFromAnimals(const string& animalId);

    /// @}

    /// @name Aviary Assignment Operations
    /// @{

    /**
     * @brief Adds an animal to a specific aviary.
     * @param aviaryId ID of the target aviary.
     * @param animalId ID of the animal to be added.
     * @return True if the assignment was successful, false otherwise.
     */
    bool addAnimalInAviary(const string& aviaryId, const string& animalId);

    /**
     * @brief Removes an animal from a given aviary.
     * @param aviaryId ID of the aviary.
     * @param animalId ID of the animal to remove.
     * @return True if the animal was successfully removed, false otherwise.
     */
    bool removeAnimalFromAviary(const string& aviaryId, const string& animalId);

    /**
     * @brief Moves an animal between two aviaries.
     * @param fromAviaryId ID of the current aviary.
     * @param toAviaryId ID of the destination aviary.
     * @param animalId ID of the animal to move.
     * @return True if the transfer was successful, false otherwise.
     */
    bool moveAnimalBetweenAviaries(const string& fromAviaryId, const string& toAviaryId, const string& animalId);

    /// @}

    /// @name Query and Utility Methods
    /// @{

    /**
     * @brief Retrieves all animals that are not currently assigned to any aviary.
     * @return A vector of shared pointers to unassigned animals.
     */
    [[nodiscard]] vector<shared_ptr<Animal>> getAnimalsNotInAviaries() const;

    /**
     * @brief Checks whether all animals in the system are assigned to aviaries.
     * @return True if every animal has an assigned aviary, false otherwise.
     */
    [[nodiscard]] bool allAnimalsAssigned() const;

    /// @}

    /// @name Feeding and Maintenance
    /// @{

    /**
     * @brief Feeds an animal by its ID.
     * @param animalId ID of the animal to feed.
     *
     * Updates the animal’s `isFed` status and may trigger log updates
     * or feeding history tracking.
     */
    void feedById(const string& animalId);

    /// @}

    /// @name Output and Display
    /// @{

    /**
     * @brief Prints formatted information about all animals.
     *
     * Displays basic attributes (name, type, aviary, feeding status) of all
     * managed animals in the console or UI for administrative purposes.
     */
    void listAllAnimals() const;

    /// @}
};

#endif // ANIMALMANAGER_H

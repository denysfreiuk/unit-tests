/**
 * @file ZooGraph.h
 * @author Denys Freyuk
 * @date 27.10.2025
 * @version 1.1
 * @brief Declaration of the ZooGraph subsystem used in the Zoo Management System.
 *
 * This header defines the core classes representing the spatial graph of the zoo:
 * - **Aviary** — a vertex representing an animal enclosure;
 * - **Path** — a weighted connection between aviaries;
 * - **ZooGraph** — the main graph structure combining all zoo entities and repositories.
 *
 * @details
 * The ZooGraph integrates database repositories, employee and animal managers,
 * and graph traversal algorithms. It forms the core of the system’s spatial logic.
 */

#ifndef ZOOGRAPH_H
#define ZOOGRAPH_H

#include <memory>
#include <string>
#include <vector>
#include "Graph.h"
#include "../Creatures/EmployeeManager.h"
#include "../Creatures/AnimalManager.h"
#include "../DatabaseManager/AviaryRepository.h"
#include "../DatabaseManager/PathRepository.h"
#include "../DatabaseManager/AnimalRepository.h"
#include "../DatabaseManager/EmployeeRepository.h"

using namespace std;

/**
 * @class Aviary
 * @brief Represents an aviary (enclosure) in the zoo.
 *
 * Each Aviary contains animals, has an assigned employee, and stores physical
 * attributes such as type, area, and capacity. It is implemented as a graph vertex.
 *
 * @details
 * The Aviary class inherits from Vertex and extends it with additional zoo-related
 * data such as resident animals and assigned caretaker.
 *
 * @example
 * @code
 * Aviary a("Aviary1", "Bird", 150.5, 12);
 * a.setAssignedEmployee("E001");
 * a.addAnimal(make_shared<Mammal>("Leo", "Tiger", 5, 180.0, "Mammal"));
 * @endcode
 */
class Aviary : public Vertex {

private:
    string name; ///< Name of the aviary.
    string type; ///< Type of aviary (e.g., Mammal, Bird, Reptile).
    double area; ///< Physical area in square meters.
    int capacity; ///< Maximum number of animals allowed.
    vector<shared_ptr<Animal>> animals; ///< Animals residing in this aviary.
    string assignedEmployee; ///< ID of the employee assigned to this aviary.
    string animalsStrTemp; ///< Temporary serialized string of animals (used for database sync).

public:
    /// @name Constructors
    /// @{

    /**
     * @brief Constructs a new aviary (for in-memory creation).
     * @param name Name of the aviary.
     * @param type Type of animals hosted.
     * @param area Physical area of the aviary (m²).
     * @param capacity Maximum allowed number of animals.
     */
    Aviary(string& name, string& type, double area, int capacity);

    /**
     * @brief Constructs an aviary with full attributes (e.g., loaded from a database).
     * @param id Aviary ID.
     * @param name Aviary name.
     * @param type Type (category) of the aviary.
     * @param area Size of the aviary.
     * @param capacity Capacity (max animals).
     * @param assignedEmployee ID of the assigned employee.
     * @param animalsStr Serialized animal list.
     */
    Aviary(string id, string name, string type, double area, int capacity,
           string assignedEmployee, const string animalsStr);

    /// @}

    /// @name Accessors
    /// @{

    [[nodiscard]] const string& getAnimalsStrTemp() const;
    [[nodiscard]] vector<shared_ptr<Animal>>& getAnimalsRef();
    [[nodiscard]] string getIdAviary() const;
    [[nodiscard]] string getName() const;
    [[nodiscard]] string getType() const;
    [[nodiscard]] double getArea() const;
    [[nodiscard]] int getCapacity() const;
    [[nodiscard]] const vector<shared_ptr<Animal>>& getAnimals() const;
    [[nodiscard]] shared_ptr<Animal> getAnimalById(const string& id) const;
    [[nodiscard]] string getAssignedEmployee() const;
    [[nodiscard]] string getAnimalsStr() const;

    /// @}

    /// @name Mutators
    /// @{

    void clearAnimalsStrTemp();
    void setName(const string& n);
    void setType(const string& t);
    void setArea(double a);
    void setCapacity(int c);
    void setAnimals(vector<shared_ptr<Animal>> an);
    void setAssignedEmployee(const string& employeeId);
    void setAnimals(const string& animals);

    /// @}

    /// @name Functional Methods
    /// @{

    void printInfoAboutAviary() const;
    [[nodiscard]] bool hasAnimal(const string& animalId) const;
    [[nodiscard]] bool canAddAnimal(const shared_ptr<Animal>& animal) const;
    bool addAnimal(const shared_ptr<Animal>& animal);
    bool removeAnimal(const string& id);
    void removeAssignedEmployee();
    void listAnimals() const;

    /// @}
};

/**
 * @class Path
 * @brief Represents a physical or logical connection between two aviaries.
 *
 * Each path corresponds to a walkway or transport link between enclosures,
 * with an associated distance (length). It inherits from Edge.
 *
 * @example
 * @code
 * Path p("A1", "A2", 42.0);
 * cout << p.getLength(); // Outputs: 42.0
 * @endcode
 */
class Path : public Edge {

public:
    /**
     * @brief Constructs a path between two aviaries.
     * @param from Starting aviary ID.
     * @param to Destination aviary ID.
     * @param length Distance in meters.
     */
    Path(const string& from, const string& to, double length)
        : Edge(from, to, length) {}

    [[nodiscard]] string getFromId() const;
    [[nodiscard]] string getToId() const;
    [[nodiscard]] double getLength() const;
};

/**
 * @class ZooGraph
 * @brief Represents the complete zoo graph with all aviaries, paths, and managers.
 *
 * The ZooGraph integrates database repositories and management subsystems for
 * animals and employees. It extends the generic Graph structure with zoo-specific
 * entities (Aviary, Path) and provides utilities for distance and connectivity checks.
 *
 * @details
 * This class serves as the central orchestrator of the zoo's logical structure.
 * It loads data from repositories, manages animals and employees, and performs
 * spatial computations such as pathfinding and connectivity verification.
 *
 * @example
 * @code
 * ZooGraph graph(avRepo, pathRepo, animalRepo, empRepo);
 * graph.loadAviariesFromRepo(avRepo);
 * graph.loadPathsFromRepo(pathRepo);
 * graph.printZoo();
 * @endcode
 */
class ZooGraph : public Graph {

private:
    AviaryRepository& repoAv; ///< Repository for aviary data.
    PathRepository& repoPth; ///< Repository for path data.
    AnimalRepository& animalRepo; ///< Repository for animal data.
    EmployeeRepository& employeeRepo; ///< Repository for employee data.

    AnimalManager animalManager; ///< Manages all animal-related operations.
    EmployeeManager employeeManager; ///< Manages all employee-related operations.

public:
    /// @name Constructors
    /// @{

    /**
     * @brief Constructs the ZooGraph with connected repositories.
     * @param aviaryRrepository Reference to the AviaryRepository.
     * @param pathRepository Reference to the PathRepository.
     * @param animalRepository Reference to the AnimalRepository.
     * @param employeeRepository Reference to the EmployeeRepository.
     */
    ZooGraph(AviaryRepository& aviaryRrepository, PathRepository& pathRepository,
             AnimalRepository& animalRepository, EmployeeRepository& employeeRepository);

    /// @}

    /// @name Data Loading
    /// @{

    void loadAviariesFromRepo(AviaryRepository& repo);
    void loadPathsFromRepo(PathRepository& repo);

    /// @}

    /// @name Accessors
    /// @{

    [[nodiscard]] AnimalManager& getAnimalManager();
    [[nodiscard]] EmployeeManager& getEmployeeManager();

    [[nodiscard]] const unordered_map<string, shared_ptr<Vertex>>& getAviaries() const;
    [[nodiscard]] vector<Edge> getPaths() const;
    [[nodiscard]] const Edge* getPath(const string& fromId, const string& toId) const;
    [[nodiscard]] shared_ptr<Vertex> getAviaryById(const string& id) const;
    [[nodiscard]] string getAviaryNameById(const string& id) const;
    [[nodiscard]] vector<string> getNeighborsNames(const string& aviaryId) const;
    [[nodiscard]] vector<string> getNeighborsId(const string& aviaryId) const;

    /// @}

    /// @name Graph Modification
    /// @{

    void addAviary(shared_ptr<Aviary> aviary);
    void addPath(const string& fromId, const string& toId, double length);
    void removeAviary(const string& id);
    void removePath(const string& fromId, const string& toId);

    /// @}

    /// @name Graph Algorithms
    /// @{

    [[nodiscard]] vector<string> findShortestPath(const string& startId, const string& endId) const;
    [[nodiscard]] double distanceBetweenAviaries(const string& fromId, const string& toId) const;
    [[nodiscard]] bool isZooConnected() const;

    /// @}

    /// @name Visualization and Output
    /// @{

    void printPathBetweenAviaries(const string& fromId, const string& toId) const;
    void listAnimals() const;
    void listEmployees() const;
    void printAviaries() const;
    void printZoo() const;

    /// @}
};

#endif // ZOOGRAPH_H

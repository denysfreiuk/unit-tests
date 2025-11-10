/**

* @file Animals.h
* @author Denys
* @date 27.10.2025
* @version 1.1
* @brief Declaration of the Animal hierarchy for the Zoo Management System.
*
* This header defines the abstract base class Animal and several derived
* classes representing different biological types of animals (mammals, birds,
* reptiles, fish, amphibians, insects, arachnids). Each class stores specific
* information about an animal and provides polymorphic behavior for actions
* such as feeding, moving, and making sounds.
  */

#ifndef ANIMALS_H
#define ANIMALS_H

#include <string>
#include <memory>

using namespace std;

class ZooGraph;

/**

* @class Animal
* @brief Base abstract class for all animals in the zoo.
*
* The Animal class encapsulates shared attributes (name, species, age, weight,
* type, aviary assignment, feeding status) and behaviors common to all animals.
* Derived classes must implement the `makeSound()` method to specify the sound
* characteristic for that animal group.
*
* @details
* Each animal can belong to a specific aviary, has a feeding status, and may be
* interacted with through polymorphic calls. The class supports behavior
* simulation such as moving, feeding, and compatibility checks.
*
* @example
* @code
* shared_ptr<Animal> tiger = make_shared<Mammal>("Leo", "Tiger", 5, 180.0, "Mammal");
* tiger->feed();
* tiger->makeSound();
* @endcode
  */
  class Animal {

protected:
string id;          ///< Unique animal identifier.
string name;        ///< Animal's name.
string species;     ///< Biological species (e.g., lion, tiger, parrot).
int age;            ///< Age of the animal in years.
double weight;      ///< Weight of the animal in kilograms.
string type;        ///< General type (e.g., Mammal, Bird, Reptile).
string aviaryId;    ///< Identifier of the aviary where the animal resides.
bool isFed = false; ///< Indicates whether the animal has been fed today.

public:
/**
* @brief Constructs an animal without explicit ID or aviary.
* @param name Animal's name.
* @param species Biological species.
* @param age Animal's age.
* @param weight Animal's weight.
* @param type General classification (Mammal, Bird, etc.).
*
* Used when creating new animals that have not yet been persisted in storage.
*/
Animal(const string& name, const string& species, int age, double weight, const string& type);

/**
 * @brief Constructs a fully initialized animal.
 * @param id Unique animal identifier.
 * @param name Animal's name.
 * @param species Biological species.
 * @param age Animal's age.
 * @param weight Animal's weight.
 * @param type Animal's classification.
 * @param aviaryId ID of the aviary the animal belongs to.
 *
 * Typically used when loading data from a file or database.
 */
Animal(const string& id, string& name, string& species, int age, double weight, const string& type, string& aviaryId);

/** @brief Virtual destructor for correct cleanup through base pointers. */
virtual ~Animal() = default;

// === Getters ===

/** @return The animal's unique identifier. */
[[nodiscard]] string getId() const;

/** @return The animal's name. */
[[nodiscard]] string getName() const;

/** @return The biological species of the animal. */
[[nodiscard]] string getSpecies() const;

/** @return The classification type of the animal (Mammal, Bird, etc.). */
[[nodiscard]] string getType() const;

/** @return The animal's age in years. */
[[nodiscard]] int getAge() const;

/** @return The animal's weight in kilograms. */
[[nodiscard]] double getWeight() const;

/** @return True if the animal has been fed today. */
[[nodiscard]] bool getIsFed() const;

/** @return The ID of the aviary this animal is assigned to. */
[[nodiscard]] string getAviaryId() const;

// === Setters ===

/** @brief Assigns the animal to a specific aviary. */
void setAviaryId(const string& id);

/** @brief Changes the animal's name. */
void setName(const string& n);

/** @brief Updates the animal's age. */
void setAge(int a);

/** @brief Updates the animal's weight. */
void setWeight(double w);

// === Behavioral Methods ===

/**
 * @brief Marks the animal as fed.
 *
 * Updates the `isFed` flag to true and may later trigger logging or feeding
 * history tracking in the system.
 */
virtual void feed();

/**
 * @brief Emits the typical sound for this animal.
 * @note Pure virtual — must be implemented in each derived class.
 */
virtual void makeSound() const = 0;

/**
 * @brief Simulates animal movement.
 *
 * Default implementation prints a generic movement message; can be
 * overridden in derived classes to simulate flight, swimming, crawling, etc.
 */
virtual void move() const;

/**
 * @brief Determines compatibility between two animals.
 * @param other Another animal for comparison.
 * @return True if both animals can coexist peacefully (default — true).
 *
 * Derived classes can override to define custom compatibility logic
 * (e.g., predator-prey exclusion, same species grouping).
 */
[[nodiscard]] virtual bool isCompatibleWith(const shared_ptr<Animal>& other) const;

/**
 * @brief Prints formatted information about the animal.
 *
 * Can be overridden to include more detailed or formatted output.
 */
virtual void printInfoAboutAnimal() const;

};

// ======================================================================
// === DERIVED CLASSES ==================================================
// ======================================================================

/**

* @class Mammal
* @brief Represents mammal species in the zoo.
* @details Overrides sound behavior and may later include mammal-specific logic.
*
* @example
* @code
* Mammal lion("Simba", "Lion", 6, 200.0, "Mammal");
* lion.makeSound(); // "Roar!"
* @endcode
  */
  class Mammal : public Animal {
  public:
  Mammal(const string& name, const string& species, int age, double weight, const string& type);
  Mammal(const string& id, string& name, string& species, int age, double weight, const string& type, string& aviaryId);

  /** @brief Emits a mammal-specific sound (e.g., roar or growl). */
  void makeSound() const override;
  };

/**

* @class Bird
* @brief Represents bird species (parrots, eagles, etc.).
* @details Provides custom sound and movement (flight).
  */
  class Bird : public Animal {
  public:
  Bird(const string& name, const string& species, int age, double weight, const string& type);
  Bird(const string& id, string& name, string& species, int age, double weight, const string& type, string& aviaryId);

  /** @brief Emits a chirping or squawking sound. */
  void makeSound() const override;

  /** @brief Simulates flying behavior. */
  void move() const override;
  };

/**

* @class Reptile
* @brief Represents reptile species (snakes, lizards, etc.).
* @details Provides custom sound and behavior for cold-blooded reptiles.
  */
  class Reptile : public Animal {
  public:
  Reptile(const string& name, const string& species, int age, double weight, const string& type);
  Reptile(const string& id, string& name, string& species, int age, double weight, const string& type, string& aviaryId);

  /** @brief Emits a reptilian sound (e.g., hiss). */
  void makeSound() const override;
  };

/**

* @class Fish
* @brief Represents aquatic animals.
* @details Overrides sound and movement (swimming behavior).
  */
  class Fish : public Animal {
  public:
  Fish(const string& name, const string& species, int age, double weight, const string& type);
  Fish(const string& id, string& name, string& species, int age, double weight, const string& type, string& aviaryId);

  /** @brief Emits bubbles or water-related sounds (symbolically). */
  void makeSound() const override;

  /** @brief Simulates swimming motion. */
  void move() const override;
  };

/**

* @class Amphibian
* @brief Represents amphibians (frogs, salamanders, etc.).
* @details Overrides both movement (crawling/jumping) and sound (croak).
  */
  class Amphibian : public Animal {
  public:
  Amphibian(const string& name, const string& species, int age, double weight, const string& type);
  Amphibian(const string& id, string& name, string& species, int age, double weight, const string& type, string& aviaryId);

  /** @brief Emits croaking or similar amphibian sounds. */
  void makeSound() const override;

  /** @brief Simulates amphibian movement (jump or crawl). */
  void move() const override;
  };

/**

* @class Insect
* @brief Represents insect species (bees, butterflies, beetles, etc.).
* @details Defines buzzing or chirping sounds and flying movement.
  */
  class Insect : public Animal {
  public:
  Insect(const string& name, const string& species, int age, double weight, const string& type);
  Insect(const string& id, string& name, string& species, int age, double weight, const string& type, string& aviaryId);

  /** @brief Emits buzzing or chirping sound. */
  void makeSound() const override;

  /** @brief Simulates flying or crawling movement. */
  void move() const override;
  };

/**
* @class Arachnid
* @brief Represents arachnids (spiders, scorpions, etc.).
* @details Provides quiet movement and subtle behavioral patterns.
  */
  class Arachnid : public Animal {
  public:
  Arachnid(const string& name, const string& species, int age, double weight, const string& type);
  Arachnid(const string& id, string& name, string& species, int age, double weight, const string& type, string& aviaryId);

  /** @brief Emits subtle hissing or clicking sound. */
  void makeSound() const override;

  /** @brief Simulates crawling movement. */
  void move() const override;
  };

#endif // ANIMALS_H

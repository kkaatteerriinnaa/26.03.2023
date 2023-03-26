#include <iostream>
#include <vector>

// Abstract Product
class Herbivore {
public:
    virtual int getWeight() = 0;
    virtual void eatGrass() = 0;
    virtual bool isAlive() = 0;
};

class Carnivore {
public:
    virtual int getPower() = 0;
    virtual void eat(Herbivore* herbivore) = 0;
};

// Concrete Products
class Wildebeest : public Herbivore {
private:
    int weight;
    bool alive;
public:
    Wildebeest() : weight(50), alive(true) {}

    int getWeight() override {
        return weight;
    }

    void eatGrass() override {
        weight += 10;
    }

    bool isAlive() override {
        return alive;
    }

    void kill() {
        alive = false;
    }
};

class Bison : public Herbivore {
private:
    int weight;
    bool alive;
public:
    Bison() : weight(100), alive(true) {}

    int getWeight() override {
        return weight;
    }

    void eatGrass() override {
        weight += 10;
    }

    bool isAlive() override {
        return alive;
    }

    void kill() {
        alive = false;
    }
};

class Lion : public Carnivore {
private:
    int power;
public:
    Lion() : power(50) {}

    int getPower() override {
        return power;
    }

    void eat(Herbivore* herbivore) override {
        if (herbivore->getWeight() < power) {
            power += 10;
            herbivore->kill();
        }
        else {
            power -= 10;
        }
    }
};

class Wolf : public Carnivore {
private:
    int power;
public:
    Wolf() : power(30) {}

    int getPower() override {
        return power;
    }

    void eat(Herbivore* herbivore) override {
        if (herbivore->getWeight() < power) {
            power += 10;
            herbivore->kill();
        }
        else {
            power -= 10;
        }
    }
};

// Abstract Factory
class Continent {
public:
    virtual Herbivore* createHerbivore() = 0;
    virtual Carnivore* createCarnivore() = 0;
};

// Concrete Factories
class Africa : public Continent {
public:
    Herbivore* createHerbivore() override {
        return new Wildebeest();
    }

    Carnivore* createCarnivore() override {
        return new Lion();
    }
};

class NorthAmerica : public Continent {
public:
    Herbivore* createHerbivore() override {
        return new Bison();
    }

    Carnivore* createCarnivore() override {
        return new Wolf();
    }
};

// Ðåàëèçàöèÿ æèâîòíûõ êîíòèíåíòà Åâðàçèÿ
class Elk : public Carnivore {
public:
    void feed() override { std::cout << "Elk is eating grass!\n"; }
};

class Tiger : public Carnivore {
public:
    void feed() override { std::cout << "Tiger is hunting!\n"; }
};

class EurasianAnimalFactory : public Herbivore {
public:
    Herbivore* createHerbivore() override { return new Elk; }
    Carnivore* createCarnivore() override { return new Tiger; }
};

// Êëèåíò
class AnimalWorld {
private:
    std::vector<Herbivore*> herbivores_;
    std::vector<Carnivore*> carnivores_;

public:
    AnimalWorld(Herbivore& factory) {
        herbivores_.push_back(factory.createHerbivore());
        herbivores_.push_back(factory.createHerbivore());
        herbivores_.push_back(factory.createHerbivore());

        carnivores_.push_back(factory.createCarnivore());
        carnivores_.push_back(factory.createCarnivore());
        carnivores_.push_back(factory.createCarnivore());
    }

    void herbivoreMeals() {
        std::cout << "Herbivores are eating:\n";
        for (auto h : herbivores_) {
            h->feed();
        }
    }

    void carnivoreNutrition() {
        std::cout << "Carnivores are hunting:\n";
        for (auto c : carnivores_) {
            c->feed();
        }
    }

    ~AnimalWorld() {
        for (auto h : herbivores_) {
            delete h;
        }
        for (auto c : carnivores_) {
            delete c;
        }
    }
};

int main() {
    Carnivore* africanFactory = new AfricanAnimalFactory;
    AnimalWorld africanWorld(*africanFactory);
    africanWorld.herbivoreMeals();
    africanWorld.carnivoreNutrition();
    delete africanFactory;

    Carnivore* eurasianFactory = new EurasianAnimalFactory;
    AnimalWorld eurasianWorld(*eurasianFactory);
    eurasianWorld.herbivoreMeals();
    eurasianWorld.carnivoreNutrition();
    delete eurasianFactory;

    return 0;
}
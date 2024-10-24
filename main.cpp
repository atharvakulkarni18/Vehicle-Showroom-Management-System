#include <iostream>

// Constants
const int MAX_VEHICLES = 100;

// Base class: Vehicle
class Vehicle {
protected:
    char brand[50];
    char model[50];
    double price;
    int year;

public:
    Vehicle(const char* brand, const char* model, double price, int year) {
        for (int i = 0; brand[i] != '\0' && i < 49; ++i) {
            this->brand[i] = brand[i];
        }
        this->brand[49] = '\0'; // Ensure null termination

        for (int i = 0; model[i] != '\0' && i < 49; ++i) {
            this->model[i] = model[i];
        }
        this->model[49] = '\0'; // Ensure null termination

        this->price = price;
        this->year = year;
    }

    virtual void displayInfo() const {
        std::cout << "Brand: " << brand << ", Model: " << model
                  << ", Price: $" << price << ", Year: " << year << "\n";
    }

    virtual double calculateInsurance() const {
        return price * 0.05; // Default insurance calculation
    }

    const char* getBrand() const {
        return brand;
    }

    const char* getModel() const {
        return model;
    }

    virtual ~Vehicle() {}
};

// Derived class: Car
class Car : public Vehicle {
    int numberOfDoors;

public:
    Car(const char* brand, const char* model, double price, int year, int doors)
        : Vehicle(brand, model, price, year), numberOfDoors(doors) {}

    void displayInfo() const override {
        std::cout << "[Car] ";
        Vehicle::displayInfo();
        std::cout << "Number of doors: " << numberOfDoors << "\n";
    }

    double calculateInsurance() const override {
        return price * 0.07; // Cars have a higher insurance rate
    }
};

// Derived class: Bike
class Bike : public Vehicle {
    bool hasGear;

public:
    Bike(const char* brand, const char* model, double price, int year, bool gear)
        : Vehicle(brand, model, price, year), hasGear(gear) {}

    void displayInfo() const override {
        std::cout << "[Bike] ";
        Vehicle::displayInfo();
        std::cout << "Has Gear: " << (hasGear ? "Yes" : "No") << "\n";
    }

    double calculateInsurance() const override {
        return price * 0.03; // Bikes have a lower insurance rate
    }
};

// Derived class: Truck
class Truck : public Vehicle {
    double loadCapacity; // tons

public:
    Truck(const char* brand, const char* model, double price, int year, double capacity)
        : Vehicle(brand, model, price, year), loadCapacity(capacity) {}

    void displayInfo() const override {
        std::cout << "[Truck] ";
        Vehicle::displayInfo();
        std::cout << "Load Capacity: " << loadCapacity << " tons\n";
    }

    double calculateInsurance() const override {
        return price * (0.1 + (loadCapacity * 0.01)); // Higher insurance based on load capacity
    }
};

// Showroom class to manage vehicles
class Showroom {
    Vehicle* vehicles[MAX_VEHICLES];
    int vehicleCount;

public:
    Showroom() : vehicleCount(0) {}

    // Add a vehicle to the showroom
    void addVehicle(Vehicle* vehicle) {
        if (vehicleCount < MAX_VEHICLES) {
            vehicles[vehicleCount++] = vehicle;
        } else {
            std::cout << "Showroom is full!\n";
        }
    }

    // Remove a vehicle by model
    void removeVehicle(const char* model) {
        for (int i = 0; i < vehicleCount; ++i) {
            // Manual string comparison
            bool match = true;
            for (int j = 0; model[j] != '\0' || vehicles[i]->getModel()[j] != '\0'; ++j) {
                if (model[j] != vehicles[i]->getModel()[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                delete vehicles[i]; // Free memory
                vehicles[i] = vehicles[--vehicleCount]; // Move last vehicle to removed spot
                return;
            }
        }
        std::cout << "Vehicle not found!\n";
    }

    // Search for vehicles by brand
    void searchByBrand(const char* brand) const {
        for (int i = 0; i < vehicleCount; ++i) {
            // Manual string comparison
            bool match = true;
            for (int j = 0; brand[j] != '\0' || vehicles[i]->getBrand()[j] != '\0'; ++j) {
                if (brand[j] != vehicles[i]->getBrand()[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                vehicles[i]->displayInfo();
                std::cout << "Insurance: $" << vehicles[i]->calculateInsurance() << "\n\n";
            }
        }
    }

    // Display all vehicles
    void displayAllVehicles() const {
        for (int i = 0; i < vehicleCount; ++i) {
            vehicles[i]->displayInfo();
            std::cout << "Insurance: $" << vehicles[i]->calculateInsurance() << "\n\n";
        }
    }

    // Showroom summary
    void showroomSummary() const {
        double totalValue = 0;
        for (int i = 0; i < vehicleCount; ++i) {
            totalValue += vehicles[i]->calculateInsurance();
        }
        std::cout << "Total number of vehicles: " << vehicleCount << "\n";
        std::cout << "Total showroom insurance value: $" << totalValue << "\n\n";
    }

    ~Showroom() {
        for (int i = 0; i < vehicleCount; ++i) {
            delete vehicles[i]; // Clean up allocated memory
        }
    }
};

// Menu-driven interface
void showroomMenu(Showroom& showroom) {
    int choice;
    do {
        std::cout << "\n--- Vehicle Showroom Menu ---\n";
        std::cout << "1. Add Car\n";
        std::cout << "2. Add Bike\n";
        std::cout << "3. Add Truck\n";
        std::cout << "4. Remove Vehicle by Model\n";
        std::cout << "5. Search Vehicle by Brand\n";
        std::cout << "6. Display All Vehicles\n";
        std::cout << "7. Showroom Summary\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            char brand[50], model[50];
            double price;
            int year, doors;
            std::cout << "Enter Car details (brand model price year doors): ";
            std::cin >> brand >> model >> price >> year >> doors;
            showroom.addVehicle(new Car(brand, model, price, year, doors));
        } else if (choice == 2) {
            char brand[50], model[50];
            double price;
            int year;
            bool gear;
            std::cout << "Enter Bike details (brand model price year hasGear [1 for Yes, 0 for No]): ";
            std::cin >> brand >> model >> price >> year >> gear;
            showroom.addVehicle(new Bike(brand, model, price, year, gear));
        } else if (choice == 3) {
            char brand[50], model[50];
            double price, capacity;
            int year;
            std::cout << "Enter Truck details (brand model price year loadCapacity): ";
            std::cin >> brand >> model >> price >> year >> capacity;
            showroom.addVehicle(new Truck(brand, model, price, year, capacity));
        } else if (choice == 4) {
            char model[50];
            std::cout << "Enter model to remove: ";
            std::cin >> model;
            showroom.removeVehicle(model);
        } else if (choice == 5) {
            char brand[50];
            std::cout << "Enter brand to search: ";
            std::cin >> brand;
            showroom.searchByBrand(brand);
        } else if (choice == 6) {
            showroom.displayAllVehicles();
        } else if (choice == 7) {
            showroom.showroomSummary();
        }
    } while (choice != 8);
}

int main() {
    Showroom showroom;
    showroomMenu(showroom); // Start the showroom menu

    return 0;
}

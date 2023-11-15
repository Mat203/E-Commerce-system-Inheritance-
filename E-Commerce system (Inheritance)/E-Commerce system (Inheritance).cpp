#include <iostream>
#include <string>


class Product {
private:
    int productID;
    std::string name;
    double price;
    int quantityInStock;

public:
    virtual void displayDetails() const = 0;
    double calculateTotalCost() {
        return price * quantityInStock;
    }
};

class Electronics : public Product {
private:
    std::string brand;
    std::string model;
    double powerConsumption;

public:
    void displayDetails() const override {
        std::cout << "Power Consumption: " << powerConsumption << std::endl;
    }
};

class Books : public Product {
private:
    std::string author;
    std::string genre;
    std::string ISBN;

public:
    void displayDetails() const override {
        std::cout << "Author: " << author << std::endl;
    }
};

class Clothing : public Product {
private:
    std::string size;
    std::string color;
    std::string material;

public:
    void displayDetails() const override {
        std::cout << "Size: " << size << std::endl;
    }
};

int main() {
    return 0;
}
#include <iostream>
#include <string>
#include <vector>


class Product {
private:
    int productID;
    std::string name;
    double price;
    int quantityInStock;

public:
    Product(int id, std::string n, double p, int q) : productID(id), name(n), price(p), quantityInStock(q) {}

    int getQuantityInStock() const {
        return quantityInStock;
    }

    std::string getName() const {
        return name;
    }

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
    Electronics(int id, std::string n, double p, int q, std::string b, std::string m, double pc)
        : Product(id, n, p, q), brand(b), model(m), powerConsumption(pc) {}

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
    Books(int id, std::string n, double p, int q, std::string a, std::string g, std::string isbn)
        : Product(id, n, p, q), author(a), genre(g), ISBN(isbn) {}

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
    Clothing(int id, std::string n, double p, int q, std::string s, std::string c, std::string m)
        : Product(id, n, p, q), size(s), color(c), material(m) {}

    void displayDetails() const override {
        std::cout << "Size: " << size << std::endl;
    }
};


class Inventory {
private:
    std::vector<Product*> products; 
    int lowStockThreshold;

public:
    Inventory(int threshold) : lowStockThreshold(threshold) {}

    void addProduct(Product* product) {
        products.push_back(product);
    }

    void subtractQuantity(Product* product, int quantity) {
    }

    void notifyLowStock() {
        for (Product* product : products) {
            if (product->getQuantityInStock() <= lowStockThreshold) {
                std::cout << "Product " << product->getName() << " is low in stock." << std::endl;
            }
        }
    }

    std::vector<Product*> getProductsToRestock() {
        std::vector<Product*> productsToRestock;
        for (Product* product : products) {
            if (product->getQuantityInStock() <= lowStockThreshold) {
                productsToRestock.push_back(product);
            }
        }
        return productsToRestock;
    }

    void displayAllProducts() {
        for (Product* product : products) {
            product->displayDetails();
        }
    }
};


int main() {
    return 0;
}
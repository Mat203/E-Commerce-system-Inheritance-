#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


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

    int getProductID() const {
        return productID;
    }

    double getPrice() const {
        return price;
    }

    virtual void displayDetails() const = 0;

    double calculateTotalCost() {
        return price * quantityInStock;
    }

    void decreaseQuantity() {
        if (quantityInStock > 0) {
            quantityInStock--;
        }
        else {
            std::cout << "No more stock for product " << name << std::endl;
        }
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
        std::cout << "Product ID: " << getProductID() << std::endl;
        std::cout << "Name: " << getName() << std::endl;
        std::cout << "Price: " << getPrice() << std::endl;
        std::cout << "Quantity in Stock: " << getQuantityInStock() << std::endl;
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
        std::cout << "Product ID: " << getProductID() << std::endl;
        std::cout << "Name: " << getName() << std::endl;
        std::cout << "Price: " << getPrice() << std::endl;
        std::cout << "Quantity in Stock: " << getQuantityInStock() << std::endl;
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
        std::cout << "Product ID: " << getProductID() << std::endl;
        std::cout << "Name: " << getName() << std::endl;
        std::cout << "Price: " << getPrice() << std::endl;
        std::cout << "Quantity in Stock: " << getQuantityInStock() << std::endl;
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

    void subtractQuantity(int productID, int quantity) {
        for (Product* product : products) {
            if (product->getProductID() == productID) {
                product->decreaseQuantity();
            }
        }
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

    Product* findProductByID(int productID) {
        for (Product* product : products) {
            if (product->getProductID() == productID) {
                return product;
            }
        }
        return nullptr; 
    }


    ~Inventory() {
        for (Product* product : products) {
            delete product;
        }
    }
};

class ConfigReader {
private:
    std::string filename;
    Inventory* inventory;

public:
    ConfigReader(const std::string& filename, Inventory* inv) : filename(filename), inventory(inv) {}


    void readConfigFile() {
        std::ifstream file(filename);

        if (!file) {
            std::cout << "Unable to open file " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {

            std::istringstream iss(line);
            std::string type;
            std::getline(iss, type, ',');

            if (type == "Electronics") {
                readElectronics(iss);
            }
            else if (type == "Books") {
                readBooks(iss);
            }
            else if (type == "Clothing") {
                readClothing(iss);
            }
        }

        file.close();
    }

    int generateID() {
        int id = rand() % 10;
        id = id * 1000 + rand();
        return id;
    }


    void readElectronics(std::istringstream& iss) {
        std::string name, brand, model;
        double price, powerConsumption;
        int quantityInStock;

        std::getline(iss, name, ',');
        iss >> price;
        iss.ignore();
        iss >> quantityInStock;
        iss.ignore();
        std::getline(iss, brand, ',');
        std::getline(iss, model, ',');
        iss >> powerConsumption;

        int id = generateID();

        Electronics* e = new Electronics(id, name, price, quantityInStock, brand, model, powerConsumption);
        inventory->addProduct(e);
    }

    void readBooks(std::istringstream& iss) {
        std::string name, author, genre, ISBN;
        double price;
        int quantityInStock;

        std::getline(iss, name, ',');
        iss >> price;
        iss.ignore();
        iss >> quantityInStock;
        iss.ignore();
        std::getline(iss, author, ',');
        std::getline(iss, genre, ',');
        std::getline(iss, ISBN, ',');

        int id = generateID();

        Books* b = new Books(id, name, price, quantityInStock, author, genre, ISBN);
        inventory->addProduct(b);
    }

    void readClothing(std::istringstream& iss) {
        std::string name, size, color, material;
        double price;
        int quantityInStock;

        std::getline(iss, name, ',');
        iss >> price;
        iss.ignore();
        iss >> quantityInStock;
        iss.ignore();
        std::getline(iss, size, ',');
        std::getline(iss, color, ',');
        std::getline(iss, material, ',');

        int id = generateID();

        Clothing* c = new Clothing(id, name, price, quantityInStock, size, color, material);
        inventory->addProduct(c);
    }
};

class Order {
private:
    int orderID;
    std::string customer;
    std::vector<Product*> products;
    double totalCost;
    std::string orderStatus;

public:
    Order(int id, const std::string& cust)
        : orderID(id), customer(cust), totalCost(0.0), orderStatus("Created") {}

    void addProduct(int productID, Inventory* inventory) {
        Product* product = inventory->findProductByID(productID);
        if (product != nullptr) {
            products.push_back(product);
            totalCost += product->getPrice();
            inventory->subtractQuantity(productID, 1); 
        }
        else {
            std::cout << "Product with ID " << productID << " not found." << std::endl;
        }
    }



    double calculateTotalCost() {
        return totalCost;
    }

    void changeOrderStatus(const std::string& status) {
        orderStatus = status;
    }

    void displayOrderDetails() {
        std::cout << "Order ID: " << orderID << std::endl;
        std::cout << "Customer: " << customer << std::endl;
        std::cout << "Total Cost: " << totalCost << std::endl;
        std::cout << "Order Status: " << orderStatus << std::endl;
        std::cout << "Products: " << std::endl;
        for (Product* product : products) {
            product->displayDetails();
        }
    }
};


int main() {
    Electronics* e1 = new Electronics(1, "TV", 500.0, 3, "Samsung", "Model1", 100.0);
    Electronics* e2 = new Electronics(2, "Fridge", 1000.0, 5, "LG", "Model2", 200.0);

    Inventory inventory(2);

    inventory.addProduct(e1);
    inventory.addProduct(e2);

    inventory.displayAllProducts();

    inventory.subtractQuantity(1, 1);
    std::cout << "-------" << std::endl;
    inventory.displayAllProducts();

    inventory.notifyLowStock();

    ConfigReader reader("config.txt", &inventory);
    reader.readConfigFile();
    std::cout << "-------" << std::endl;
    inventory.displayAllProducts();

    Order order(1, "Customer1");
    order.addProduct(1, &inventory);
    order.addProduct(2, &inventory);
    std::cout << "-------" << std::endl;
    order.displayOrderDetails();

    return 0;
}


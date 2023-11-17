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

class ProductManager {
private:
    std::vector<Product*> products;

public:
    void addProduct(Product* product) {
        products.push_back(product);
    }

    Product* findProductByID(int productID) {
        for (Product* product : products) {
            if (product->getProductID() == productID) {
                return product;
            }
        }
        return nullptr;
    }

    void removeProduct(int productID) {
        Product* product = findProductByID(productID);
        if (product != nullptr) {
            products.erase(std::remove(products.begin(), products.end(), product), products.end());
            delete product;
        }
        else {
            std::cout << "Product with ID " << productID << " not found." << std::endl;
        }
    }

    std::vector<Product*> getProducts() {
        return products;
    }


    ~ProductManager() {
        for (Product* product : products) {
            delete product;
        }
    }
};


class Inventory {
private:
    ProductManager* productManager;
    int lowStockThreshold;

public:
    Inventory(ProductManager* pm, int threshold) : productManager(pm), lowStockThreshold(threshold) {}

    void subtractQuantity(int productID, int quantity) {
        Product* product = productManager->findProductByID(productID);
        if (product != nullptr) {
            product->decreaseQuantity();
        }
    }

    Product* findByID(int productID) {
        Product* product = productManager->findProductByID(productID);
        return product;
    }

    void notifyLowStock() {
        for (Product* product : productManager->getProducts()) {
            if (product->getQuantityInStock() <= lowStockThreshold) {
                std::cout << "Product " << product->getName() << " is low in stock." << std::endl;
            }
        }
    }

    std::vector<Product*> getProductsToRestock() {
        std::vector<Product*> productsToRestock;
        for (Product* product : productManager->getProducts()) {
            if (product->getQuantityInStock() <= lowStockThreshold) {
                productsToRestock.push_back(product);
            }
        }
        return productsToRestock;
    }

    void displayAllProducts() {
        for (Product* product : productManager->getProducts()) {
            product->displayDetails();
        }
    }
};


class ProductCatalog {
private:
    ProductManager* productManager;

public:
    ProductCatalog(ProductManager* pm) : productManager(pm) {}

    void addProduct(Product* product) {
        productManager->addProduct(product);
    }

    void updateProduct(int productID, Product* updatedProduct) {
        Product* product = productManager->findProductByID(productID);
        if (product != nullptr) {
            productManager->removeProduct(productID);
            productManager->addProduct(updatedProduct);
        }
        else {
            std::cout << "Product with ID " << productID << " not found." << std::endl;
        }
    }

    void removeProduct(int productID) {
        productManager->removeProduct(productID);
    }

    void viewProducts() {
        for (Product* product : productManager->getProducts()) {
            product->displayDetails();
            std::cout << "--------------------" << std::endl;
        }
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
    Order(const std::string& cust)
        : customer(cust), totalCost(0.0), orderStatus("Created") {
        orderID = rand();
    }

    void addProduct(int productID, Inventory* inventory) {
        Product* product = inventory->findByID(productID);
        if (product != nullptr) {
            products.push_back(product);
            totalCost += product->getPrice();
            inventory->subtractQuantity(productID, 1); 
        }
        else {
            std::cout << "Product with ID " << productID << " not found." << std::endl;
        }
    }

    int get_id() {
        return orderID;
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

class OrdersSet {
private:
    std::vector<Order> orders;

public:
    void addOrder(const Order& order) {
        orders.push_back(order);
    }

    Order* findOrderById(int id) {
        for (auto& order : orders) {
            if (order.get_id() == id) {
                return &order;
            }
        }
        return nullptr;
    }
};

class ProductReader {
public:
    static Electronics* readElectronics(std::istream& iss) {
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

        return new Electronics(id, name, price, quantityInStock, brand, model, powerConsumption);
    }

    static Books* readBooks(std::istream& iss) {
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

        return new Books(id, name, price, quantityInStock, author, genre, ISBN);
    }

    static Clothing* readClothing(std::istream& iss) {
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

        return new Clothing(id, name, price, quantityInStock, size, color, material);
    }

private:
    static int generateID() {
        int id = rand() % 10;
        id = id * 1000 + rand();
        return id;
    }
};

class ConfigReader {
private:
    std::string filename;
    ProductManager* productManager;

public:
    ConfigReader(const std::string& filename, ProductManager* pm) : filename(filename), productManager(pm) {}

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
                Electronics* e = ProductReader::readElectronics(iss);
                productManager->addProduct(e);
            }
            else if (type == "Books") {
                Books* b = ProductReader::readBooks(iss);
                productManager->addProduct(b);
            }
            else if (type == "Clothing") {
                Clothing* c = ProductReader::readClothing(iss);
                productManager->addProduct(c);
            }
        }

        file.close();
    }
};


int main() {
    ProductManager productManager;
    Inventory inventory(&productManager, 2);
    ProductCatalog productCatalog(&productManager);
    ConfigReader reader("config.txt", &productManager);
    reader.readConfigFile();

    OrdersSet ordersSet;

    std::string command;

    std::cout << "Enter your role (worker/customer): ";
    std::string role;
    std::cin >> role;

    while (true) {
        if (role == "worker") {
        std::cout << "Enter your command: ";
        std::cin >> command;
            if (command == "view_products") {
                productCatalog.viewProducts();
            }
            else if (command == "add_product") {
                std::string input;
                std::getline(std::cin, input);
                std::istringstream iss(input);
                std::string type;
                std::getline(iss, type, ',');
                std::cout << type << std::endl;
                if (type == " Electronics") {
                    Electronics* e = ProductReader::readElectronics(iss);
                    productCatalog.addProduct(e);
                }
                else if (type == " Books") {
                    Books* b = ProductReader::readBooks(iss);
                    productCatalog.addProduct(b);
                }
                else if (type == " Clothing") {
                    std::cout << "afsfs" << std::endl;
                    Clothing* c = ProductReader::readClothing(iss);
                    productCatalog.addProduct(c);
                }
            }

            else if (command == "remove_product") {
                int productID;
                std::cin >> productID;
                productCatalog.removeProduct(productID);
                std::cout << "Prodduct have removed" << std::endl;
            }
            else if (command == "exit") {
                break;
            }
            else {
                std::cout << "Invalid command\n";
            }
        }
        else if (role == "customer") {
            std::cout << "Enter your command: ";
            std::cin >> command;
            if (command == "view_products") {
                productCatalog.viewProducts();
            }
            else if (command == "create_order") {
                std::string customer;
                std::cin >> customer;
                Order order(customer);
                ordersSet.addOrder(order);
                std::cout << "Order created for customer " << customer << " with ID " << order.get_id() << std::endl;
            }
            else if (command == "add_item") {
                int orderId, productId;
                std::cin >> orderId >> productId;
                Order* order = ordersSet.findOrderById(orderId);
                if (order != nullptr) {
                    order->addProduct(productId, &inventory);
                    std::cout << "Product " << productId << " added to order " << orderId << std::endl;
                }
                else {
                    std::cout << "Order not found\n";
                }
            }
            else if (command == "get_total_cost") {
                int orderId;
                std::cin >> orderId;
                Order* order = ordersSet.findOrderById(orderId);
                if (order != nullptr) {
                    std::cout << "Total cost of order: " << order->calculateTotalCost() << std::endl;
                }
                else {
                    std::cout << "Order not found\n";
                }
            }
            else if (command == "exit") {
                break;
            }
            else {
                std::cout << "Invalid command\n";
            }
        }
        else {
            std::cout << "Invalid role\n";
        }
    }

    return 0;
}

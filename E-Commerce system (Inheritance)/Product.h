#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int productID;
    std::string name;
    double price;
    int quantityInStock;

public:
    Product(int id, std::string n, double p, int q);

    int getQuantityInStock() const;

    std::string getName() const;

    int getProductID() const;

    double getPrice() const;

    virtual void displayDetails() const = 0;

    virtual std::string getType() const = 0;

    double calculateTotalCost();

    void decreaseQuantity();
};

#endif // PRODUCT_H

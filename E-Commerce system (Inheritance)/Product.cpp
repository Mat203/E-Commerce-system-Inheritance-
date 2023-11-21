#include "Product.h"
#include <iostream>

Product::Product(int id, std::string n, double p, int q) : productID(id), name(n), price(p), quantityInStock(q) {}

int Product::getQuantityInStock() const {
    return quantityInStock;
}

std::string Product::getName() const {
    return name;
}

int Product::getProductID() const {
    return productID;
}

double Product::getPrice() const {
    return price;
}

double Product::calculateTotalCost() {
    return price * quantityInStock;
}

void Product::decreaseQuantity() {
    if (quantityInStock > 0) {
        quantityInStock--;
    }
    else {
        std::cout << "No more stock for product " << name << std::endl;
    }
}

void Product::print() const {
    std::cout << "Product ID: " << productID << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Price: " << price << std::endl;
    std::cout << "Quantity in Stock: " << quantityInStock << std::endl;
}
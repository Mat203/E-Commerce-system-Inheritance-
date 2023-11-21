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

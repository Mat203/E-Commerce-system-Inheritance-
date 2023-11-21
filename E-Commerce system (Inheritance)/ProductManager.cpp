#include "ProductManager.h"
#include <algorithm>
#include <iostream>

void ProductManager::addProduct(Product* product) {
    products.push_back(product);
}

Product* ProductManager::findProductByID(int productID) {
    for (Product* product : products) {
        if (product->getProductID() == productID) {
            return product;
        }
    }
    return nullptr;
}

void ProductManager::removeProduct(int productID) {
    Product* product = findProductByID(productID);
    if (product != nullptr) {
        products.erase(std::remove(products.begin(), products.end(), product), products.end());
        delete product;
    }
    else {
        std::cout << "Product with ID " << productID << " not found." << std::endl;
    }
}

std::vector<Product*> ProductManager::getProducts() {
    return products;
}

ProductManager::~ProductManager() {
    for (Product* product : products) {
        delete product;
    }
}

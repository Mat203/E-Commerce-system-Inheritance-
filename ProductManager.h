#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include <vector>
#include "Product.h"

class ProductManager {
private:
    std::vector<Product*> products;

public:
    void addProduct(Product* product);

    Product* findProductByID(int productID);

    void removeProduct(int productID);

    std::vector<Product*> getProducts();

    ~ProductManager();
};

#endif // PRODUCTMANAGER_H

#ifndef ORDER
#define ORDER

#include <string>
#include <mutex> 
#include <iostream>

#include "order_book.h"
#include "stock.h"

class Trader; 

class Order {
private:
    int m_order_id;
    std::string m_stock_name;
    double m_price;
    int m_quantity;

public:
    Order(int id, std::string name, double price, int quantity);

    virtual ~Order();

    int get_order_id() const;
    double get_price() const;
    int get_quantity() const;
    std::string get_stock_name() const;

    void set_quantity(int q);

    virtual void execute(Order_Book& order_book, Stock* stock, Trader* trader) = 0;

};

class Market_Order : public Order {
public:
    Market_Order(int order_id, std::string name, double price, int quantity);

    void execute(Order_Book& order_book, Stock* stock, Trader* trader) override;
};

class Limit_Order : public Order {
private: 
    int limit;
public:
    Limit_Order(int order_id, std::string name, double price, int quantity, int limit = 50);
    
    void execute(Order_Book& order_book, Stock* stock, Trader* trader) override;
};

class Order_Strategy {
private:
    Order* m_order;
public:
    void set_order(Order* order);
    
    void execute_order(Order_Book& order_book, Stock* stock, Trader* trader);
};

class Order_Factory_Manager {
public:
    static Order* Instance(const std::string& type, int order_id, std::string name, int quantity) 
    {
        if(type == "Limit") {
            double price = 0.0;
            std::cout << "Enter stock price: ";
            std::cin >> price;
            return new Limit_Order(order_id, name, price, quantity);
        } else if(type == "Market") {
            return new Market_Order(order_id, name, 0, quantity);
        } else {
            return nullptr;
        }
    }
};

#endif    // Order

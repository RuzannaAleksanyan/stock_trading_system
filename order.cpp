#include <iostream>

#include "order.h"
#include "stock.h"
#include "trader.h"
#include "order_book.h"

Order::Order(int id, std::string name, double price, int quantity)
    : m_order_id(id), m_stock_name(name), m_price(price), m_quantity(quantity)
{ }

Order::~Order() 
{ } 

int Order::get_order_id() const 
{
    return m_order_id;
}

std::string Order::get_stock_name() const 
{
    return m_stock_name;
}

double Order::get_price() const 
{
    return m_price;
}

int Order::get_quantity() const 
{
    return m_quantity;
}

Market_Order::Market_Order(int id, std::string name, double price, int quantity)
    : Order(id, name, price, quantity) 
{ }

Limit_Order::Limit_Order(int id, std::string name, double price, int quantity, int limit)
    : Order(id, name, price, quantity)
{ }

void Limit_Order::execute(Order_Book& order_book, Stock* stock, Trader* trader) 
{
    std::lock_guard<std::mutex> lock(order_book.book_mutex); // Lock for thread safety

    if(stock == nullptr && trader == nullptr) {
        std::cout << "Not Order!" << std::endl; 
        return;
    }

    if (stock->get_current_price() == get_price()) {
        order_book.buy_stock(trader, stock, get_quantity());
    } else {
        auto& book = order_book.get_book();
        book[trader].push_back(this);
    }
}

void Market_Order::execute(Order_Book& order_book, Stock* stock, Trader* trader) 
{
    order_book.buy_stock(trader, stock, get_quantity());
}

void Order_Strategy::set_order(Order* order) 
{
    m_order = order;
}

void Order_Strategy::execute_order(Order_Book& order_book, Stock* stock, Trader* trader) 
{
    if(m_order) {
        m_order->execute(order_book, stock, trader);
    } else {
        throw std::runtime_error("No Strategy set!");
    }
}

void Order::set_quantity(int q) 
{
    m_quantity = q;
}

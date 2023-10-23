#include "stock.h"

Stock::Stock(const std::string& stock_name, double initial_price, int quantity) 
    : m_name(stock_name), m_current_price(initial_price), m_quantity(quantity)
{ }

std::string Stock::get_stock_name() const 
{
    return m_name;
}

double Stock::get_current_price() const 
{
    return m_current_price;
}

void Stock::set_quantity(int new_quantity) 
{
    m_quantity = new_quantity;
}

int Stock::get_quantity() const 
{
    return m_quantity;
}

void Stock::randomize_price() 
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    
    double percentage_change = (rand() % 11 - 5) / 100.0;

    m_current_price = (1.0 + percentage_change);
}

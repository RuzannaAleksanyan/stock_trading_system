#include "trader.h"

Trader::Trader(const std::string& name, int id, double balance)
    : m_name(name), m_accaunt_balance(balance), m_trader_id(id)
{ }

void Trader::update_account_balance(double amount) 
{
    m_accaunt_balance = amount;
}

double Trader::get_account_balance() const 
{
    return m_accaunt_balance;
}

std::string Trader::get_name() const 
{  
    return m_name;
}

int Trader::get_trader_ID() const {
    return m_trader_id;
}

std::unordered_map<Stock*, int> Trader::get_stocks() const 
{
    return m_stocks;
}

void Trader::add_stock_count(Stock* stock, int quantity) 
{
    if(stock == nullptr) {
        std::cout << " " << std::endl;
        return;
    }
    m_stocks[stock] += quantity;
}

void Trader::sub_stock_count(Stock* stock, int quantity) 
{
    if(stock == nullptr) {
        std::cout << " " << std::endl;
        return;
    }
    m_stocks[stock] -= quantity;
}

void Trader::set_stocks(std::unordered_map<Stock*, int> stocks) 
{
    m_stocks = stocks;
}

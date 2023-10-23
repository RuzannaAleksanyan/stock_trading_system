#ifndef TREADER
#define TREADER

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "order.h"
#include "stock.h"

class Trader {
private:
    std::string m_name;
    double m_accaunt_balance;
    int m_trader_id;
    std::unordered_map<Stock*, int> m_stocks;

public:
    Trader(const std::string& name, int id, double balance = 5000);
    
    void update_account_balance(double amount);

    void add_stock_count(Stock* stock, int quantity);
    void sub_stock_count(Stock* stock, int quantity);

    double get_account_balance() const;
    int get_trader_ID() const;
    std::string get_name() const;
    std::unordered_map<Stock*, int> get_stocks() const;

    void set_stocks(std::unordered_map<Stock*, int> stocks);
};

#endif

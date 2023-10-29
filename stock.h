#ifndef STOCK
#define STOCK

#include <unordered_map>
#include <string>
#include <cstdlib>   
#include <ctime>     

class Stock {
private:
    std::string m_name;
    double m_current_price;
    int m_quantity;

public:
    Stock(const std::string& stock_name, double initial_price, int quantity = 0);

    std::string get_stock_name() const;
    double get_current_price() const;
    int get_quantity() const;

    void set_quantity(int new_quantity);
    
    void randomize_price();
};

#endif    // STOCK

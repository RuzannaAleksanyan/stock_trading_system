#ifndef STOCK_SYSTEM
#define STOCK_SYSTEM

#include <vector>
#include <thread>
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "trader.h"
#include "stock.h"
#include "order_book.h"

class Trading_System {
private:
    std::vector<Trader*> traders;
    std::unordered_map<Stock*, int> stocks;
    Order_Book order_book;

public:
    Trading_System() = default;
    ~Trading_System();

    void execute(int trader_id, const std::string& stock_name, int quantity, int flag);

    void display_stocks() const; 

    void register_trader(); 
    void create_stock(); 

    int user_register_trader(); 

    void randomize_stock_prices(); 

    void write_container_trader_data_to_file(); 
    void write_container_stock_data_to_file(); 
    void write_order_book_data_to_file();

    void read_container_trader_data_from_file(); 
    void read_container_stock_data_from_file(); 
    void read_order_book_data_from_file();
    
    Stock* find_stock_by_symbol(const std::string& symbol);

    bool return_id(int id);
};

#endif

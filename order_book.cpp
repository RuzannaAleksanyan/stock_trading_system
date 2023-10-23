#include <thread>
#include <fstream>
#include "order_book.h"
#include "stock.h"  
#include "trader.h" 
#include <iostream>

void Order_Book::buy_stock(Trader* trader, Stock* stock, int quantity) 
{
    std::lock_guard<std::mutex> lock(book_mutex); // Lock for thread safety
    
    if (!trader || !stock) {
        std::cerr << "Invalid trader or stock pointer." << std::endl;
        return;
    }

    double total_cost = stock->get_current_price() * quantity;
    if (trader->get_account_balance() < total_cost) {
        std::cout << "Insufficient funds to buy " << quantity << " shares of " << stock->get_stock_name() << std::endl;
        return;
    }

    trader->update_account_balance(trader->get_account_balance() - total_cost);
    trader->add_stock_count(stock, quantity);
    std::cout << "The buy done!" << std::endl;
}

void Order_Book::sell_stock(Trader* trader, Stock* stock, int quantity) 
{
    std::lock_guard<std::mutex> lock(book_mutex); // Lock for thread safety
    
    if (!trader || !stock) {
        std::cerr << "Invalid trader or stock pointer." << std::endl;
        return;
    }
    
    trader->sub_stock_count(stock, quantity);
    double total_cost = stock->get_current_price() * quantity;
    trader->update_account_balance(trader->get_account_balance() + total_cost);
    std::cout << "The sell done!" << std::endl;
}

void Order_Book::write_order_book_data_to_file() 
{
    std::string filename = "trading_system_order_book_data.txt";
    std::ofstream out_file(filename, std::ios::app);

    if (!out_file.is_open()) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return;
    }

    for (const auto& trader_orders_pair : book) {
        Trader* trader = trader_orders_pair.first;
        const std::vector<Order*>& orders = trader_orders_pair.second;

        // Write trader data to the file
        out_file << "Orders Data: " << "\n";
        out_file << "Trader!" << "\n";
        out_file << "Trader Name: " << trader->get_name() << "\n";
        out_file << "Trader ID: " << trader->get_trader_ID() << "\n";
        out_file << "Account Balance: " << trader->get_account_balance() << "\n";
        // Write trader's stocks:
        out_file << "Trader Stocks:\n";
        for (const auto& stock_entry : trader->get_stocks()) {
            Stock* stock = stock_entry.first;
            int quantity = stock_entry.second;
            out_file << "  Stock Name: " << stock->get_stock_name() << "\n";
            out_file << "  Stock Price: " << stock->get_current_price() << "\n";
            out_file << "  Stock quantity: " << stock->get_quantity() << "\n";
        }
        out_file << "\n";

        // Write order data for this trader
        out_file << "Orders!\n";
        for (const Order* order : orders) {
            out_file << "Order ID: " << order->get_order_id() << "\n";
            out_file << "Stock Name: " << order->get_stock_name() << "\n";
            out_file << "Price: " << order->get_price() << "\n";
            out_file << "Quantity: " << order->get_quantity() << "\n";
            out_file << "\n";
        }

        out_file << "\n";
    }

    out_file << "\n";

    out_file.close();
}

void Order_Book::read_order_book_data_from_file(const std::vector<Trader*>& traders) 
{
    std::string filename = "trading_system_order_book_data.txt";
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cerr << "Failed to open the file for reading." << std::endl;
        return;
    }

    // Acquire a lock on the book_mutex to ensure no other thread modifies the data while reading
    std::lock_guard<std::mutex> lock(book_mutex);

    book.clear(); // Clear existing order book data

    std::string line;
    while (std::getline(input_file, line)) {
        if (line == "Order Data:") {
            Trader* current_trader = nullptr;
            Order* current_order = nullptr;
            int quantity = 0;

            while (std::getline(input_file, line) && !line.empty()) {
                if (line == "Trader!") {
                    // Read trader information
                    std::string trader_name;
                    double trader_balance;
                    int trader_ID;

                    std::getline(input_file, line);
                    size_t colon_pos = line.find(": ");
                    if (colon_pos != std::string::npos) {
                        trader_name = line.substr(colon_pos + 2);
                    }

                    std::getline(input_file, line);
                    colon_pos = line.find(": ");
                    if (colon_pos != std::string::npos) {
                        trader_balance = std::stod(line.substr(colon_pos + 2));
                    }

                    std::getline(input_file, line);
                    colon_pos = line.find(": ");
                    if (colon_pos != std::string::npos) {
                        trader_ID = std::stoi(line.substr(colon_pos + 2));
                    }

                    Trader* trader = nullptr;
                    for(int i = 0; i < traders.size(); ++i) {
                        if(traders[i]->get_name() == trader_name && traders[i]->get_account_balance() == trader_balance && traders[i]->get_trader_ID() == trader_ID) {
                            trader = traders[i];
                        }
                    }

                    if(!trader) {
                        std::cout << "There is no such trader!" << std::endl;
                        return;
                    }

                    while(std::getline(input_file, line)) {
                        if(line == "Orders:") {
                            // Read Order information
                            int order_id = 0;
                            std::string stock_name;
                            double price = 0.0;
                            int quantity = 0;

                            std::getline(input_file, line);
                            size_t colon_pos = line.find(": ");
                            if (colon_pos != std::string::npos) {
                                order_id = std::stoi(line.substr(colon_pos + 2));
                            }

                            std::getline(input_file, line);
                            colon_pos = line.find(": ");
                            if (colon_pos != std::string::npos) {
                                stock_name = line.substr(colon_pos + 2);
                            }

                            std::getline(input_file, line);
                            colon_pos = line.find(": ");
                            if (colon_pos != std::string::npos) {
                                price = std::stod(line.substr(colon_pos + 2));
                            }

                            std::getline(input_file, line);
                            colon_pos = line.find(": ");
                            if (colon_pos != std::string::npos) {
                                quantity = std::stoi(line.substr(colon_pos + 2));
                            }

                            Order* order = Order_Factory_Manager::Instance("Market", order_id, stock_name, quantity);
                            
                            book[trader].push_back(order);
                        }
                    }
                } 
            }
        }
    }

    input_file.close();

}

Order_Book::~Order_Book() 
{
    for (auto& trader_orders_pair : book) {
        for (Order* order : trader_orders_pair.second) {
            delete order;
        }
    }

    book.clear();
}

std::unordered_map<Trader*, std::vector<Order*>>& Order_Book::get_book () 
{
    return book;
}

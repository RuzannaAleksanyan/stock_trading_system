#include "stock_trading_system.h"

#include <sstream>

Trading_System::~Trading_System() 
{
    traders.clear();
    stocks.clear();
}

void Trading_System::write_container_trader_data_to_file() 
{
    std::string filename = "trading_system_trader_data.txt";
    std::ofstream output_file(filename);

    if (!output_file.is_open()) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return;
    }

    // Write trader data:
    output_file << "Trader Data:\n";
    for (const auto& trader : traders) {
        output_file << "Trader Name: " << trader->get_name() << "\n";
        output_file << "Trader ID: " << trader->get_trader_ID() << "\n";
        output_file << "Trader Balance: " << trader->get_account_balance() << "\n";
        
        // Write trader's stocks:
        output_file << "Trader Stocks:\n";
        for (const auto& stock_entry : trader->get_stocks()) {
            Stock* stock = stock_entry.first;
            int quantity = stock_entry.second;
            output_file << "  Stock Name: " << stock->get_stock_name() << "\n";
            output_file << "  Stock Price: " << stock->get_current_price() << "\n";
            output_file << "  Stock quantity: " << stock->get_quantity() << "\n";
            output_file << "  Number of trader's stocks: " << quantity << "\n";
        }
        
        output_file << "\n";
    }

    output_file.close();
}

void Trading_System::write_container_stock_data_to_file() 
{
    std::string filename = "trading_system_stock_data.txt";
    std::ofstream output_file(filename);

    if (!output_file.is_open()) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return;
    }

    // Write stock data
    output_file << "Stock Data:\n";
    for (const auto& stock_quantity_pair : stocks) {
        Stock* stock = stock_quantity_pair.first;
        int quantity = stock_quantity_pair.second;
        output_file << "Stock Name: " << stock->get_stock_name() << "\n";
        output_file << "Current Price: " << stock->get_current_price() << "\n";
        output_file << "Quantity Available: " << quantity << "\n\n";
    }

    output_file.close();
}

void Trading_System::write_order_book_data_to_file() 
{
    order_book.write_order_book_data_to_file();
}

Stock* Trading_System::find_stock_by_symbol(const std::string& symbol) 
{
    for (const auto& entry : stocks) {
        Stock* stock = entry.first;
        if (stock && stock->get_stock_name() == symbol) {
            return stock; // Return the stock pointer if found
        }
    }
    return nullptr; // Return nullptr if the stock is not found
}

void Trading_System::read_container_trader_data_from_file() 
{
    std::string filename = "trading_system_trader_data.txt";
    std::ifstream input_file(filename);

    if (!input_file.is_open()) {
        std::cerr << "Failed to open the file for reading." << std::endl;
        return;
    }

    traders.clear(); // Clear existing trader data

    std::string line;
    while (std::getline(input_file, line)) {
        if (line == "Trader Data:") {
            std::string trader_name;
            int trader_ID = 0;
            double trader_balance = 0.0;
            std::unordered_map<Stock*, int> trader_stocks; // Create a map to store trader's stocks

            while (std::getline(input_file, line) && !line.empty()) {
                size_t colon_pos = line.find(": ");
                
                if (colon_pos != std::string::npos) {
                    std::string key = line.substr(0, colon_pos);
                    std::string value = line.substr(colon_pos + 2);

                    if (key == "Trader Name") {
                        trader_name = value;
                    } else if (key == "Trader ID") {
                        trader_ID = std::stoi(value);
                    } else if (key == "Trader Balance") {
                        trader_balance = std::stod(value);
                    } else if(key == "Trader Stocks:") {

                    } else if (key == "Stock Name") {
                        std::string stock_name = value;

                        // Read stock price:
                        std::getline(input_file, line);
                        colon_pos = line.find(": ");
                        if (colon_pos != std::string::npos) {
                            double stock_price = std::stod(line.substr(colon_pos + 2));

                            // Read stock quantity:
                            std::getline(input_file, line);
                            colon_pos = line.find(": ");
                            if (colon_pos != std::string::npos) {
                                int stock_quantity = std::stoi(line.substr(colon_pos + 2));

                                // Read trader's stock quantity:
                                std::getline(input_file, line);
                                colon_pos = line.find(": ");
                                if (colon_pos != std::string::npos) {
                                    int traders_stock_quantity = std::stoi(line.substr(colon_pos + 2));

                                    Stock* stock = find_stock_by_symbol(stock_name);
                                    if (stock) {
                                        trader_stocks[stock] = traders_stock_quantity;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // Create a trader and set their data, including m_stocks
            Trader* trader = new Trader(trader_name, trader_ID, trader_balance);
            trader->set_stocks(trader_stocks);
            traders.push_back(trader);
        }
    }

    input_file.close();
}

void Trading_System::read_container_stock_data_from_file() 
{
    std::string filename = "trading_system_stock_data.txt";
    std::ifstream input_file(filename);

    if (!input_file.is_open()) {
        std::cerr << "Failed to open the file for reading." << std::endl;
        return;
    }

    stocks.clear();  // Clear existing stock data

    std::string line;
    while (std::getline(input_file, line)) {
        if (line == "Stock Data:") {
            while (std::getline(input_file, line) && !line.empty()) {
                std::string stock_name;
                double stock_price = 0.0; // Initialize to a default value
                int quantity = 0; // Initialize to a default value

                // Read stock name
                size_t colon_pos = line.find(": ");
                if (colon_pos != std::string::npos) {
                    stock_name = line.substr(colon_pos + 2);
                }

                // Read stock price
                std::getline(input_file, line);
                colon_pos = line.find(": ");
                if (colon_pos != std::string::npos) {
                    stock_price = std::stod(line.substr(colon_pos + 2));
                }

                // Read stock quantity
                std::getline(input_file, line);
                colon_pos = line.find(": ");
                if (colon_pos != std::string::npos) {
                    quantity = std::stoi(line.substr(colon_pos + 2));
                }

                Stock* stock = new Stock(stock_name, stock_price);
                stocks[stock] = quantity;

                // Read and ignore the empty line between records
                std::getline(input_file, line);
            }
        }
    }

    input_file.close();
}

void Trading_System::read_order_book_data_from_file() 
{
    order_book.read_order_book_data_from_file(traders);
}

void Trading_System::display_stocks() const 
{
    for (const auto& stock : stocks) {
        std::cout << "Stock Name: " << stock.first->get_stock_name() << std::endl;
        std::cout << "Current Price: " << stock.first->get_current_price() << std::endl;
        std::cout << "Quantity Available: " << stock.second << std::endl << std::endl;
    }
}

void Trading_System::execute(int trader_id, const std::string& stock_name, int quantity, int flag) 
{
    Trader* trader = nullptr;
    for(auto& tr : traders) {
        if(tr->get_trader_ID() == trader_id) {
            trader = tr;
            break;
        }
    }
    
    if (trader == nullptr) {
        std::cout << "Trader with ID " << trader_id << " does not exist." << std::endl;
        return;
    }

    Stock* stock = nullptr;
    for(auto& st : stocks) {
        if(st.first->get_stock_name() == stock_name) {
            stock = st.first;
            break;
        }
    }

    if(stock == nullptr) {
        std::cout << "Stock with name " << stock_name << " does not exist." << std::endl;
        return;
    }

    if(flag == 1) {
        if(stocks[stock] < quantity) {
            std::cout << "Stoch with quantity " << quantity << " does not exist." << std::endl;
            return;
        }

        stocks[stock] -= quantity;
        order_book.buy_stock(trader, stock, quantity);

    } else if(flag == 2) {
        if (trader->get_stocks()[stock] >= quantity) {
            std::cout << "Insufficient stocks to sell " << quantity << " shares of " << stock->get_stock_name() << std::endl;
        } else {
            stocks[stock] += quantity;
            order_book.sell_stock(trader, stock, quantity);
        }

    } else if(flag == 3) {
        std::string order_type;
        std::cout << "Enter Order Type. Limit or Market: ";
        std::cin >> order_type;

        static int order_id = 0;
        Order_Strategy ob_strategy;
        ob_strategy.set_order(Order_Factory_Manager::Instance(order_type, ++order_id, stock_name, quantity));
        ob_strategy.execute_order(order_book, stock, trader);
    }
}

bool Trading_System::return_id(int id) {
    for(int i = 0; i < traders.size(); ++i) {
        if(traders[i]->get_trader_ID() == id) {
            return true;
        }
    }
    return false;
}

void Trading_System::randomize_stock_prices() 
{
    for (auto& stock : stocks) {
        stock.first->randomize_price();
    }
}

// Unused function.
void Trading_System::register_trader() 
{
    static int trader_id = 0;
    Trader* trader = new Trader("RozAle", ++trader_id);
    traders.push_back(trader);

    Trader* trader1 = new Trader("VardGhuk", ++trader_id);
    traders.push_back(trader1);

    Trader* trader2 = new Trader("ManAlex", ++trader_id);
    traders.push_back(trader2);
    
}

int Trading_System::user_register_trader() 
{
    static int trader_id = traders.size();
    std::string trader_name;
    std::cout << "Enter Trader Name: ";
    std::cin >> trader_name;

    Trader* trader = new Trader(trader_name, ++trader_id);
    traders.push_back(trader);
    std::cout << "Trader registr! " << std::endl;

    return trader_id;
}

// Unused function.
void Trading_System::create_stock() 
{
    Stock* stock1 = new Stock("APPLE", 700);
    Stock* stock2 = new Stock("NIKE", 500);
    Stock* stock3 = new Stock("AMD", 600);

    stocks[stock1] = 50;
    stocks[stock2] = 50;
    stocks[stock3] = 50;
}

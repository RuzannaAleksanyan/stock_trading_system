#include "test.h"

// Function to periodically randomize stock prices
void price_randomizer(Trading_System& trading_system, bool& stopFlag, std::mutex& price_mutex) {
    while (!stopFlag) {
        std::lock_guard<std::mutex> lock(price_mutex); // Lock the mutex
        trading_system.randomize_stock_prices();
        
        std::this_thread::sleep_for(std::chrono::seconds(2));  // Adjust the sleep duration as needed
    }
}

// Function to handle post-action prompts
bool handle_post_action(Trading_System& trading_system, bool& stop_flag, std::thread& price_thread) {
    int choice = 0;
    std::cout << "Would you like to continue working?" << std::endl;
    std::cout << "1. Yes" << std::endl;
    std::cout << "2. No" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (choice == 2) {
        {
            trading_system.write_container_stock_data_to_file();
            trading_system.write_container_trader_data_to_file();

            trading_system.write_order_book_data_to_file();
        }

        stop_flag = true; // Signal the price_randomizer thread to stop

        // Wait for the price_randomizer thread to finish
        if (price_thread.joinable()) {
            price_thread.join();
        }

        std::cout << "Exiting the program." << std::endl;
    }
    return stop_flag;
}

void run_stock_trading_system() {
    Trading_System trading_system;

    trading_system.read_container_trader_data_from_file();
    trading_system.read_container_stock_data_from_file();
    trading_system.read_order_book_data_from_file();

    bool stop_flag = false;
    std::mutex price_mutex; // Mutex for protecting price updates

    std::thread price_thread(price_randomizer, std::ref(trading_system), std::ref(stop_flag), std::ref(price_mutex));

    int trader_id = 0;
    std::cout << "Enter Trader ID: ";
    std::cin >> trader_id;
    bool flag = trading_system.return_id(trader_id);
    if(!flag) {
        std::cout << "There is no trader with such id in the system, would you like to register?" << std::endl;
        std::cout << "1. Yes" << std::endl;
        std::cout << "2. No" << std::endl;
        std::cout << "Enter your choice: ";
        int choice = 0;
        std::cin >> choice;
        if(choice == 1) {
            trader_id = trading_system.user_register_trader();
        } else {
            return;
        }
    }
    

    while (!stop_flag) {
        std::cout << "Options:" << std::endl;
        std::cout << "1. Place Buy Order" << std::endl;
        std::cout << "2. Place Sell Order" << std::endl;
        std::cout << "3. Register Order" << std::endl;
        std::cout << "4. Display system stocks" << std::endl;
        std::cout << "5. Quit" << std::endl;
        std::cout << "Enter your choice: ";

        int choice = 0;
        std::cin >> choice;

        switch (choice) {
            case 1:
            case 2:
            case 3: {
                std::string stock_name;
                int quantity = 0;
                std::cout << "Enter stock name: ";
                std::cin >> stock_name;
                std::cout << "Enter quantity: ";
                std::cin >> quantity;
                trading_system.execute(trader_id, stock_name, quantity, choice);
                if (handle_post_action(trading_system, stop_flag, price_thread)) {
                    return;
                }

                break;
            }
            case 4: {
                trading_system.display_stocks();
                if (handle_post_action(trading_system, stop_flag, price_thread)) {
                    return;
                }

                break;
            }            
            case 5:{
                if (handle_post_action(trading_system, stop_flag, price_thread)) {
                    // Ensure that the price_thread is stopped before returning
                    if (price_thread.joinable()) {
                        price_thread.join();
                    }
                    return;
                }
            }
            default: {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    }
    return;
}

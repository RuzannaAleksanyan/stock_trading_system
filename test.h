#ifndef TEST
#define TEST

#include <iostream>
#include <string>
#include <chrono>
#include <mutex>

#include "order_book.h"
#include "stock_trading_system.h"
#include "stock.h"
#include "trader.h"

void price_randomizer(Trading_System& trading_system, bool& stopFlag, std::mutex& priceMutex);
bool handle_post_action(Trading_System& trading_system, bool& stop_flag, std::thread& price_thread);

void run_stock_trading_system();

#endif

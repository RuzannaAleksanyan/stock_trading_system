#ifndef ORDER_BOOK
#define ORDER_BOOK

#include <mutex> 
#include <unordered_map>
#include <vector>

class Order;
class Trader; 
class Stock; 

class Order_Book {
private:
    std::unordered_map<Trader*, std::vector<Order*>> book;

public:
    std::mutex book_mutex;

    Order_Book() = default;

    ~Order_Book();
    
    std::unordered_map<Trader*, std::vector<Order*>>& get_book ();
    
    void buy_stock(Trader* trader, Stock* stock, int quantity);
    void sell_stock(Trader* trader, Stock* stock, int quantity);
    void write_order_book_data_to_file();
    void read_order_book_data_from_file(const std::vector<Trader*>& traders);
    
};

#endif

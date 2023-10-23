# Stock Trading System
Stock Trading System is a C++ program that simulates stock trading activities of sellers and order registrations. It provides traders with the ability to buy and sell stocks, register new traders, and create different types of orders (Limit and Market). The system ensures data stability of main traders and stocks, and it includes real-time price randomization for stocks.
## Table of Contents

1. [Getting Started](#getting-started)
   - [Prerequisites](#prerequisites)
   - [Installation](#installation)
2. [Usage](#usage)
   - [Actions](#actions)
3. [Components](#components)
4. [Usage](#usage)


## Getting Started

### Prerequisites
Before using the Stock Trading System, make sure you have the following:

- C++ development environment
- A computer that supports C++11 and newer

### Installation

1. Clone the repository to your local machine.
2. Compile the program using your C++ compiler.

## Usage

The Stock Trading System allows users to perform various actions related to stock trading. Here are the available actions:


### Actions

1. **Buy Stocks**: Select option 1 and provide the stock_name, and quantity.
2. **Sell Stocks**: Select option 2 and provide the stock_name, and quantity.
3. **Register an Order (Limit or Market)**: Select option 3 and provide the necessary details for registering an order.
4. **Show system shares**. Select option 4 to see system stocks.
5. **Exit the Program**: Choose option 5 to exit the program.

## Components

The Stock Trading System is built from the following main components:

1. **Trader**: Represents traders by name, ID, account balance, and owned stock container.
2. **Stock**: Introduces stocks by name, current price, and available quantity.
3. **Order**: An abstract base class for various types of orders, including Market_order and Limit_Order.
4. **Order_Book**: Manages and executes orders, processes trader and stock data, and provides chain security via mutex.
5. **Trading_System**: The main class that includes all information about traders, stocks, and orders in the form of containers, along with the main functionality of the Stock Trading System.
6. **Test header file**: Contains functions for managing real-time operations and running the program.

The program is designed to run in a terminal or command line, allowing users to interact with the system through a simple interface.

## Usage

1. **Build MyShell:**

   - Before using Stock Trading System, ensure you have G++ installed on your system.
   - Navigate to the directory containing the Stock Trading System source code and the Makefile.
   - Open a terminal window and run the following command to build Stock Trading System:
     ```
     make
     ```

2. **Run Stock Trading System:**

   - After successfully building Stock Trading System, run it by executing the following command:
     ```
     ./myshell
     ```
     
3. **Customization:**

   - You can customize Stock Trading System by modifying the source code in `test.cpp`. Add new commands or functionality to suit your specific needs. You can also customize compiler flags and options in the Makefile.

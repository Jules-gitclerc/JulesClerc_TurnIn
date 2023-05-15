##Presentation of the Automated Trading Project based on Interactive Brokers' TWS API

###I. Introduction

The aim of this project was to develop an automated trading solution based on Interactive Brokers' TWS API. The primary objective was to build a system that could generate trading positions for various contracts, calculate the net capital requirement under SEA Rule 15c3-1, and produce a detailed report in a CSV file.

###II. Technologies Used

Python: This is the programming language used for the development of this project. Python is widely used in the field of quantitative finance due to its simplicity and the availability of numerous libraries for scientific computation and data analysis.
TWS API: This is the trading API offered by Interactive Brokers. This API allows interaction with the TWS trading platform to retrieve contract information, place trading orders, etc.
ib_insync: This is a Python library that facilitates the use of the TWS API by providing a more Pythonic and asynchronous interface.
Pandas: This is a Python library for data manipulation and analysis. It was used to handle trading data in the form of DataFrame and to save the data in a CSV file.

###III. Project Description

TThe project was divided into three main parts: bond selection, trading position generation, and net capital requirement calculation.

**Part 1: Bond Selection**

In this part, the program selects a basket of Government Bonds, Corporate Bonds, and Municipal Bonds as the target for trading. This is an essential step as it determines the potential opportunities for trading.

**Part 2: Trading Position Generation**

In this part, the program connects to the TWS API and retrieves the details of specified contracts. For each contract, a position (long or short) is randomly generated and a quantity is set. This information is then formatted and saved in a CSV file (bond.csv).

**Part 3: Net Capital Requirement Calculation**

In this part, the program reads the CSV file generated in part 2 and for each contract, it calculates the net capital requirement under SEA Rule 15c3-1. The net capital requirement is calculated as 1% of the cash allocation for each contract. It then calculates the totals for different measures (total number of long and short positions, total number of long and short shares, total long and short dollar amount, total cash, and total net capital requirement) and saves these totals in another CSV file (totals.csv).

###IV. Challenges and Limitations

The TWS API does not directly provide the price and cash allocation for each contract. An appropriate method to obtain this information needs to be put in place.
The calculation of the net capital requirement is based on a simplified assumption (1% of cash allocation). This calculation needs to be adapted to the specific needs of the trader.
Automated trading code can carry significant risks, especially if it involves the use of leverage.

###V. Code Explanation
```
The code is structured in several blocks of functions for ease of understanding and maintenance.

Helper Functions
These functions provide utilities for interacting with the TWS API and manipulating data. They include:

bond_contract_details: This function retrieves the details of a contract from the TWS API.
save_to_csv and save_to_txt: These functions save data to a CSV or text file.
format_desc_append: This function formats the description of contracts for better presentation.

API Connection
The program connects to the TWS API using the local IP address (127.0.0.1) and a specific clientId (1 in this case).

Trading Position Generation
The program iterates over a list of defined contracts and for each contract, it generates a trading position (long or short) and a quantity. This information is then formatted and saved in a CSV file (bond.csv).

Net Capital Requirement Calculation
The program reads the previously generated CSV file and for each contract, it calculates the net capital requirement. It also calculates the totals for different measures and saves these totals in another CSV file (totals.csv).
```
###VI. Conclusion

* *This automated trading project uses Interactive Brokers' TWS API to generate trading positions and calculate the net capital requirement under SEA Rule 15c3-1. The program produces two CSV files containing the details of the trading positions and the totals for various measures.* *

###VII. Future Perspectives

Improve the accuracy of the net capital requirement calculation by taking into account other factors specified in SEA Rule 15c3-1.
Implement more robust error handling to deal with cases where the TWS API cannot provide the details of a contract.
Add a feature to place trading orders based on the generated positions.
Develop a user interface to facilitate the use of the program.
Integrate the program with a portfolio management system to track the performance of the trading positions.

import pandas as pd
from ib_insync import IB, Contract

# Connect to the TWS API
ib = IB()
ib.connect('127.0.0.1', 7497, clientId=1)

# Load the existing data
df = pd.read_csv('bond.csv')

# Prepare a list to hold the new data
new_data = []

# Iterate over the rows in the DataFrame
for _, row in df.iterrows():
    contract_id = row['Contract ID']
    contract_details = row['descAppend']
    position = row['Positions']
    quantity = row['sizeIncrement100']

    # Define the contract
    contract = Contract(conId=contract_id)

    # Request contract details
    ib_details = ib.reqContractDetails(contract)[0]

    # Extract additional data
    ticker = ib_details.contract.symbol
    price = ib_details.contract.price
    cash_allocation = ib_details.contract.cashAllocation

    # Calculate the SEA Rule 15c3-1 NET CAPITAL REQUIREMENT
    net_capital_requirement = 0.01 * cash_allocation

    # Append to new_data
    new_data.append([contract_id, ticker, contract_details, position, quantity, price, cash_allocation, net_capital_requirement])

# Create a new DataFrame
df_new = pd.DataFrame(new_data, columns=['ITEMA', 'TICKER', 'CONTRACT DETAILS', 'POSITION (LONG/SHORT)', 'QUANTITY', 'PRICE', 'CASH ALLOCATION', 'SEA Rule 15c3-1 NET CAPITAL REQUIREMENT'])

# Save to CSV
df_new.to_csv('bond_new.csv', index=False)

# Disconnect from the API
ib.disconnect()

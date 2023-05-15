import pandas as pd
from ib_insync import IB, Contract

# Connect to the TWS API
ib = IB()
ib.connect('127.0.0.1', 7497, clientId=1)

# Load the existing data
df = pd.read_csv('bond.csv')

# Prepare variables to hold the total values
total_long_pos = total_short_pos = total_shares_long = total_shares_short = total_long = total_short = total_cash = total_capital_req = 0

# Iterate over the rows in the DataFrame
for _, row in df.iterrows():
    contract_id = row['Contract ID']
    position = row['Positions']
    quantity = row['sizeIncrement100']

    # Define the contract
    contract = Contract(conId=contract_id)

    # Request contract details
    ib_details = ib.reqContractDetails(contract)[0]

    # Extract additional data
    price = ib_details.contract.price
    cash_allocation = ib_details.contract.cashAllocation

    # Calculate the SEA Rule 15c3-1 NET CAPITAL REQUIREMENT
    net_capital_requirement = 0.01 * cash_allocation

    # Update total values based on the position
    if position == 'INTENT=LONG':
        total_long_pos += 1
        total_shares_long += quantity
        total_long += price * quantity
    else:
        total_short_pos += 1
        total_shares_short += quantity
        total_short += price * quantity

    total_cash += cash_allocation
    total_capital_req += net_capital_requirement

# Create a DataFrame with the total values
df_totals = pd.DataFrame(
    {
        'CT LONG POS': [total_long_pos],
        'CT SHORT POS': [total_short_pos],
        'TTL SHARES LONG': [total_shares_long],
        'TTL SHARES SHORT': [total_shares_short],
        'TTL $LONG': [total_long],
        'TTL $SHORT': [total_short],
        'TTL $LONG + $SHORT CASH': [total_cash],
        'TTL 15c3-1 CAPITAL REQ.': [total_capital_req]
    }
)

# Save to CSV
df_totals.to_csv('totals.csv', index=False)

# Disconnect from the API
ib.disconnect()

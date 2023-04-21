import os
import csv
import random
import re
from ib_insync import IB, Contract

def bond_contract_details(bond_type, exchange, con_id):
    contract = Contract()
    contract.secType = bond_type
    contract.exchange = exchange
    contract.conId = con_id

    details = ib.reqContractDetails(contract)
    return details

def save_to_csv(filename, header, rows):
    with open(filename, 'w', newline='') as csvfile:
        csvwriter = csv.writer(csvfile)
        csvwriter.writerow(header)
        csvwriter.writerows(rows)

def save_to_txt(filename, data):
    with open(filename, 'w') as txtfile:
        txtfile.write(data)

def format_desc_append(desc_append, sec_type):
    # Insert security type after the first space
    desc_append = desc_append[:desc_append.find(' ') + 1] + sec_type + ' ' + desc_append[desc_append.find(' ') + 1:]
    
    # Update fraction to percentage
    match = re.search(r'(\d+)\s+(\d+)/(\d+)', desc_append)
    if match:
        whole_part, numerator, denominator = map(int, match.groups())
        decimal = whole_part + (numerator / denominator)
        percentage = decimal
        desc_append = re.sub(r'\d+\s+\d+/\d+', f'{percentage:.3f}%', desc_append)
    
    # Update date format
    date_match = re.search(r'(\d{2})/(\d{2})/(\d{2})', desc_append)
    if date_match:
        year = date_match.group(3)
        full_year = f'20{year}'
        desc_append = re.sub(r'\d{2}/\d{2}/\d{2}', full_year, desc_append)
    
    return desc_append

ib = IB()
ib.connect('127.0.0.1', 7497, clientId=1)

exchange = 'SMART'
contracts = {
    29157676: ('CORP'),
    29133084: ('CORP'),
    185858451: ('CORP'),
    415066061: ('CORP'),
    285736417: ('CORP'),
    175912959: ('CORP'),
    242880990: ('CORP'),
    79492744: ('CORP'),
    150258828: ('CORP'),

}

header = ['Contract ID', 'descAppend', 'Positions', 'sizeIncrement100']
rows = []
txt_data = ''

for con_id, (sec_type) in contracts.items():
    details_list = bond_contract_details(sec_type, exchange, con_id)

    for details in details_list:
        desc_append = format_desc_append(details.descAppend, sec_type)
        size_increment = details.minSize * 100
        positions = random.choice(["INTENT=LONG", "INTENT=SHORT"])

        row = [con_id, f'{desc_append}', positions, f'QUANTITY={size_increment}']
        rows.append(row)
        txt_data += ', '.join(map(str, row)) + '\n'

save_to_csv('bond.csv', header, rows)
save_to_txt('bond.txt', txt_data)

ib.disconnect()
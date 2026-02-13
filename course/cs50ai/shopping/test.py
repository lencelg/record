import csv

def read_csv_with_dictreader(filename):
    with open(filename, mode='r', newline='', encoding='utf-8') as file:
        # DictReader treats the first row as headers
        reader = csv.DictReader(file)
        
        # To store data by column, you can use a defaultdict or regular dict
        columns = {}
        for header in reader.fieldnames:
            columns[header] = []
            
        for row in reader:
            # Each row is an ordered dictionary mapping column names to values
            for column_name, value in row.items():
                columns[column_name].append(value)
                
    return columns
# Example usage:
# Assuming a file named 'data.csv' with columns like 'Name', 'Age', 'City'
data = read_csv_with_dictreader('shopping.csv')

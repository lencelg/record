import csv
import sys

from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier

TEST_SIZE = 0.4


def main():

    # Check command-line arguments
    if len(sys.argv) != 2:
        sys.exit("Usage: python shopping.py data")

    # Load data from spreadsheet and split into train and test sets
    evidence, labels = load_data(sys.argv[1])
    X_train, X_test, y_train, y_test = train_test_split(
        evidence, labels, test_size=TEST_SIZE
    )

    # Train model and make predictions
    model = train_model(X_train, y_train)
    predictions = model.predict(X_test)
    sensitivity, specificity = evaluate(y_test, predictions)

    # Print results
    print(f"Correct: {(y_test == predictions).sum()}")
    print(f"Incorrect: {(y_test != predictions).sum()}")
    print(f"True Positive Rate: {100 * sensitivity:.2f}%")
    print(f"True Negative Rate: {100 * specificity:.2f}%")


def load_data(filename):
    """
    Load shopping data from a CSV file `filename` and convert into a list of
    evidence lists and a list of labels. Return a tuple (evidence, labels).

    evidence should be a list of lists, where each list contains the
    following values, in order:
        - Administrative, an integer
        - Administrative_Duration, a floating point number
        - Informational, an integer
        - Informational_Duration, a floating point number
        - ProductRelated, an integer
        - ProductRelated_Duration, a floating point number
        - BounceRates, a floating point number
        - ExitRates, a floating point number
        - PageValues, a floating point number
        - SpecialDay, a floating point number
        - Month, an index from 0 (January) to 11 (December)
        - OperatingSystems, an integer
        - Browser, an integer
        - Region, an integer
        - TrafficType, an integer
        - VisitorType, an integer 0 (not returning) or 1 (returning)
        - Weekend, an integer 0 (if false) or 1 (if true)

    labels should be the corresponding list of labels, where each label
    is 1 if Revenue is true, and 0 otherwise.
    """
    import csv

def load_data(filename):
    evidence = []
    labels = []
    
    month_map = {
        'Jan': 0, 'Feb': 1, 'Mar': 2, 'Apr': 3, 'May': 4, 'Jun': 5,
        'Jul': 6, 'Aug': 7, 'Sep': 8, 'Oct': 9, 'Nov': 10, 'Dec': 11
    }
    
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        next(reader)

        for row in reader:
            admin = int(row[0])
            admin_dur = float(row[1])
            info = int(row[2])
            info_dur = float(row[3])
            product = int(row[4])
            product_dur = float(row[5])
            bounce = float(row[6])
            exit_rate = float(row[7])
            page_values = float(row[8])
            special_day = float(row[9])
            
            month_str = row[10]
            month = month_map.get(month_str, 0)  
            os = int(row[11])
            browser = int(row[12])
            region = int(row[13])
            traffic = int(row[14])
            visitor_type = 1 if row[15] == 'Returning_Visitor' else 0
            weekend = 1 if row[16] == 'TRUE' else 0
            
            evidence.append([
                admin, admin_dur, info, info_dur, product, product_dur,
                bounce, exit_rate, page_values, special_day, month,
                os, browser, region, traffic, visitor_type, weekend
            ])
            
            label = 1 if row[17] == 'TRUE' else 0
            labels.append(label)
    
    return (evidence, labels)


def train_model(evidence, labels):
    """
    Given a list of evidence lists and a list of labels, return a
    fitted k-nearest neighbor model (k=1) trained on the data.
    """
    return KNeighborsClassifier(n_neighbors=1).fit(evidence, labels)

def evaluate(labels, predictions):
    """
    Given a list of actual labels and a list of predicted labels,
    return a tuple (sensitivity, specificity).

    Assume each label is either a 1 (positive) or 0 (negative).

    `sensitivity` should be a floating-point value from 0 to 1
    representing the "true positive rate": the proportion of
    actual positive labels that were accurately identified.

    `specificity` should be a floating-point value from 0 to 1
    representing the "true negative rate": the proportion of
    actual negative labels that were accurately identified.
    """
    total_number = len(labels)
    TP = 0
    TN = 0 
    FP = 0
    FN = 0
    for i in range(total_number):
        if labels[i] == predictions[i] == 1:
            TP += 1
        if labels[i] == predictions[i] == 0:
            TN += 1
        if labels[i] == 1 and predictions[i] == 0:
            FN += 1
        if labels[i] == 0 and predictions[i] == 1:
            FP += 1
    sensitvity = TP / (TP + FN) 
    specificity = TN / (TN + FP)
    return (sensitvity, specificity)


if __name__ == "__main__":
    main()

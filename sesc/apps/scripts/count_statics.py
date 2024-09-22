import os

"""
Read the log file from c++ branch counts and create a python dictionary to 
process the log file for what we need.

:returns Dictionary of branch data with each key as an int, and each value as a dict of 'CorrectPrediction',
'BranchType', and 'BranchID'
"""
def read_log_file_and_create_dict(fileName):
    init_index = 0
    txt_data_dictionary = {}
    with open(fileName, 'r') as file:
        print("Creating txt file dict")

        # Skip the header line
        next(file)
        for line in file:
            line = line.strip()
            parts = line.split(", ")

            # Extract the relevant data from the line
            branch_id = parts[0].split(": ")[1]
            correct_prediction = parts[1].split(": ")[1]
            direction_prediction_correct = parts[2].split(": ")[1]
            branch_type = parts[3].split(": ")[1]

            # Create dictionary of data from the log 
            txt_data_dictionary[init_index] = {
                "BranchID": branch_id,
                "CorrectPrediction": correct_prediction,
                "DirectionPredictionCorrect": direction_prediction_correct,
                "BranchType": branch_type
            }

            init_index += 1
    return txt_data_dictionary

"""
Get all the branch IDs from the dictionary and store in array for counting

: returns python array of all branch IDs
"""
def get_branch_ids_from_dictionary(log_dictionary):
    print("Getting branch IDs from log dictionary")
    branch_ids = []
    for key in log_dictionary:
        if isinstance(log_dictionary[key], dict) and 'BranchID' in log_dictionary[key]:
            branch_ids.append(log_dictionary[key]['BranchID'])
        else:
            print("Invalid entry at key: ", key, " -> ", log_dictionary[key])
    return branch_ids

"""
Count the frequency of all unique branch IDs, and store them in a dictionary

: returns dictionary of unique branch IDs and counts
"""
def count_branch_id_frequencies(branch_ids):
    print("Counting branch frequencies")
    branch_id_counts = {}
    for unique_id in branch_ids:
        if unique_id in branch_id_counts:
            branch_id_counts[unique_id] += 1
        else:
            branch_id_counts[unique_id] = 1
    return branch_id_counts

"""
Assigns branch counts to the following buckets to count statics
1-19 executions
20-199 executions
200-1999 executions
2000+ executions

: returns a dictionary of each count bucket
"""
def assign_static_counts_to_buckets(branch_id_counts):
    bucket_1_19 = 0
    bucket_20_199 = 0
    bucket_200_1999 = 0
    bucket_2000_plus = 0

    for branch_id, count in branch_id_counts.items():
        if 1 <= count <= 19:
            bucket_1_19 += 1
        elif 20 <= count <= 199:
            bucket_20_199 += 1
        elif 200 <= count <= 1999:
            bucket_200_1999 += 1
        elif count >= 2000:
            bucket_2000_plus += 1

    return {
        "1-19 executions": bucket_1_19,
        "20-199 executions": bucket_20_199,
        "200-1999 executions": bucket_200_1999,
        "2000+ executions": bucket_2000_plus
    }    

"""
Function that gets the count of correct/incorrect predictions per branch. 

: returns a dictionary of prediction counts, with the key as the branch ID
"""
def get_count_of_correct_and_incorrect_predictions_per_branch(branch_data, unaccepted_branch_types):

    print("Obtaining count of correct/incorrect branch predictions")

    prediction_counts = {}

    for index, branch_info in branch_data.items():
        branch_id = branch_info['BranchID']
        branch_type = branch_info["BranchType"]

        if branch_type in unaccepted_branch_types:
            continue

        if branch_id not in prediction_counts:
            prediction_counts[branch_id] = {"Correct": 0, "Incorrect": 0}

        # Comment this in for Hybrid predictor
        if branch_type == "Unconditional":
            prediction_counts[branch_id]["Correct"] += 1
        else:
            # For BTB Included and NT, change this value to "CorrectPrediction", for excluded "DirectionPredictionCorrect"
            is_correct = branch_info["CorrectPrediction"]
        
            if is_correct == "true":
                prediction_counts[branch_id]["Correct"] += 1
            else:
                prediction_counts[branch_id]["Incorrect"] += 1

        # Comment this in for NT Predictor
        # is_correct = branch_info["CorrectPrediction"]
    
        # if is_correct == "true":
        #     prediction_counts[branch_id]["Correct"] += 1
        # else:
        #     prediction_counts[branch_id]["Incorrect"] += 1

    return prediction_counts

"""
Assigns prediction count branches to buckets based on sum of predictions, and keeps track of correct/incorrect
for accuracy calculation

: returns dictionary of buckets with total correct/incorrect predictions
"""
def assign_prediction_count_branches_to_buckets(prediction_counts):
    
    print("Assigning bucket groupings for branch predictions")

    bucket_groupings = {
        "1-19 executions": {"branch_count": 0, "total_correct": 0, "total_incorrect": 0},
        "20-199 executions": {"branch_count": 0, "total_correct": 0, "total_incorrect": 0},
        "200-1999 executions": {"branch_count": 0, "total_correct": 0, "total_incorrect": 0},
        "2000+ executions": {"branch_count": 0, "total_correct": 0, "total_incorrect": 0}
    }   

    for branch_id, counts in prediction_counts.items():
        total_executions = counts["Correct"] + counts["Incorrect"]

        if 1 <= total_executions <= 19:
            bucket = "1-19 executions"
        elif 20 <= total_executions <= 199:
            bucket = "20-199 executions"
        elif 200 <= total_executions <= 1999:
            bucket = "200-1999 executions"
        elif total_executions >= 2000:
            bucket = "2000+ executions"

        bucket_groupings[bucket]["branch_count"] += 1
        bucket_groupings[bucket]["total_correct"] += counts["Correct"] 
        bucket_groupings[bucket]["total_incorrect"] += counts["Incorrect"]

    return bucket_groupings

"""
Calculates accuracy of each bucket in the bucket_groupings dictionary

: returns dictionary of bucket accuracy
"""
def calculate_accuracy_per_bucket(bucket_groupings):
    
    print("Calculating bucket accuracy")

    bucket_accuracies = {}

    for bucket, bucket_data in bucket_groupings.items():
        total_correct = bucket_data["total_correct"]
        total_predictions = bucket_data["total_correct"] + bucket_data["total_incorrect"]

        # float to avoid problems with integer division in python 2
        accuracy = (float(total_correct) / total_predictions)
        bucket_accuracies[bucket] = accuracy
    
    return bucket_accuracies

"""
Method to process a given log file in the format of: BranchAddr: Branch ID, Correct Prediction: true/false, BranchType: type

Does the following:
(1) Counts static branches as they pertain the the buckets outlined in section G/H
(2) Calculates accuracy of those branches in their respective buckets
(3) Prints the results to the console

"""
def process_log_file(filename):

    # Edit this to change unaccepted branch types
    unaccepted_branch_types = ["Return"]

    # Change this to true to exclude effect of BTB
    # exclude_btb_effect = True

    # Get static branch counts of executions per bucket
    branch_data_from_txt = read_log_file_and_create_dict(filename)
    branch_id_array = get_branch_ids_from_dictionary(branch_data_from_txt)
    branch_frequency_map = count_branch_id_frequencies(branch_id_array)
    static_branch_frequencies = assign_static_counts_to_buckets(branch_frequency_map)

    # Calculate accuracy per bucket
    branch_prediction_counts = get_count_of_correct_and_incorrect_predictions_per_branch(branch_data_from_txt, unaccepted_branch_types)
    prediction_bucket_groupings = assign_prediction_count_branches_to_buckets(branch_prediction_counts)
    bucket_accuracies = calculate_accuracy_per_bucket(prediction_bucket_groupings)

    print("-" * 30)
    print("Static branch frequencies:")
    for key, value in sorted(static_branch_frequencies.items()):
        print("Bucket:", key, " Count:", value)
    print("\n")
    print("Bucket accuracies:")
    for key, value in sorted(bucket_accuracies.items()):
        print("Bucket:", key, " Accuracy:", value)
    print("-" * 30)

"""
Notes for use:

(1) Replace the branch_log.txt path with the correct path for the sim
(2) Input unaccepted branch types in the corresponding array (unaccepted_branch_types) within process_log_file
(3) Output will go to the console

No venv is required as no external dependencies are used 
"""
if __name__ == "__main__":
    # Replace 'branch_log.txt' with the actual filename if different
    log_file = os.path.expanduser(os.path.join('~/sesc/apps/Splash2/raytrace/', 'branch_log.txt'))
    process_log_file(log_file)
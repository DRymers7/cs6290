import os
import re

def process_log_file(filename):
    # Dictionary to store per-branch statistics
    # Key: BranchAddr (int)
    # Value: {'total': total_executions, 'correct': correct_predictions}
    branch_stats = {}

    # Open the log file and read line by line
    with open(filename, 'r') as f:
        # Skip header line
        header = f.readline()

        # Define the regex pattern to match each log line
        pattern = re.compile(r'BranchAddr: (\d+), Correct Prediction: (true|false), BranchType: (\w+)')

        # Read each line
        for line in f:
            line = line.strip()
            match = pattern.match(line)
            if match:
                branch_addr_str, correct_prediction_str, branch_type = match.groups()
                branch_addr = int(branch_addr_str)
                correct_prediction = correct_prediction_str == 'true'

                # Update branch statistics
                if branch_addr not in branch_stats:
                    # Initialize counts for a new static branch
                    branch_stats[branch_addr] = {'total': 0, 'correct': 0}

                branch_stats[branch_addr]['total'] += 1
                if correct_prediction:
                    branch_stats[branch_addr]['correct'] += 1
            else:
                # If the line doesn't match the pattern, you can skip or log an error
                print("Warning: Line doesn't match pattern")

   # Define execution frequency buckets
    buckets = {
        '1-10': {'branch_count': 0, 'total_predictions': 0, 'correct_predictions': 0},
        '11-100': {'branch_count': 0, 'total_predictions': 0, 'correct_predictions': 0},
        '101-1000': {'branch_count': 0, 'total_predictions': 0, 'correct_predictions': 0},
        '>1000': {'branch_count': 0, 'total_predictions': 0, 'correct_predictions': 0}
    }

        # Assign each static branch to a bucket based on execution frequency
    for branch_addr, stats in branch_stats.items():
        total_executions = stats['total']
        correct_predictions = stats['correct']

        # Determine the bucket for the current branch
        if 1 >= total_executions < 20:
            bucket_name = '1-19'
        elif 20 <= total_executions < 200:
            bucket_name = '20-199'
        elif 200 <= total_executions < 2000:
            bucket_name = '200-1999'
        else:  # total_executions > 1000
            bucket_name = '2000+'

        # Update bucket statistics
        buckets[bucket_name]['branch_count'] += 1
        buckets[bucket_name]['total_predictions'] += total_executions
        buckets[bucket_name]['correct_predictions'] += correct_predictions

    # Print the results
    print("Bucket\t\tNumber of Static Branches\tPrediction Accuracy")
    for bucket_name, bucket_stats in buckets.iteritems():
        branch_count = bucket_stats['branch_count']
        total_predictions = bucket_stats['total_predictions']
        correct_predictions = bucket_stats['correct_predictions']
        if total_predictions > 0:
            accuracy = (correct_predictions / total_predictions) * 100  # Percentage
        else:
            accuracy = 0.0
        print("{0}\t\t{1}\t\t\t\t{2:.2f}%".format(bucket_name, branch_count, accuracy))

if __name__ == "__main__":
    # Replace 'branch_log.txt' with the actual filename if different
    log_file = os.path.expanduser(os.path.join('~/sesc/apps/Splash2/lu/', 'branch_log.txt'))
    process_log_file(log_file)
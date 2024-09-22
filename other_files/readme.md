- To handle NT predictor (BTB excluded)
1. unaccepted_branch_types = ["Return"]
2. type          = "NotTaken"

- To handle Hybrid predictor (BTB excluded)
1. unaccepted_branch_types = ["Return"]
2. type          = "Hybrid"
3. Change "CorrectPrediction" to "DirectionPredictionCorrect" in accuracy calculation

- Troubleshooting:
1. Remove the conditional logic for counting unconditional branches accuracy if trying to replicate numbers and getting abberant results (if including BTB)
2. Restart container
3. Re compile BPred
4. Check output of branch_log.txt and make sure directional indication working as expected
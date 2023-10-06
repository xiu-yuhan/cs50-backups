import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) < 2:
        print("usage: python dna.py (database.csv) (sequence.txt)")
    # TODO: Read database file into a variable
    database = {}
    keys = []
    looper = 0
    with open(sys.argv[1]) as d:
        read = csv.DictReader(d)
        for i in read:
            keys = list(i.keys())
            database[looper] = i
            looper += 1
    # TODO: Read DNA sequence file into a variable
    sequence = open(sys.argv[2]).read()
    # TODO: Find longest match of each STR in DNA sequence
    match = {}
    for i in range(len(keys)):
        match[keys[i]] = longest_match(sequence,keys[i])
    # TODO: Check database for matching profiles
    matching = False
    for i in range(len(database)):
        matching = True
        for j in range(1,len(keys)):
            if (int(database[i][keys[j]]) != int(match[keys[j]])):
                matching = False
        if(matching):
            print(database[i]['name'])
            return
    print("No Match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()

import argparse
import csv
import pprint
import sys
from observation_timeline import ObservationTimeline, DataError
from observation import Observation


def load_timeline(filename):
    """Loads an observations CSV file.

    :param str filename: The name of the observations CSV file to read

    :returns: A tuple with the following items:

                - A dictionary that maps a suspect's name to the
                  item they are currently carrying (based on data in
                  the CSV file).

                - An ObservationTimeline that contains the observation
                  data loaded from the CSV file.

    :rtype: tuple

    :raises ValueError: If there is an issue unpacking the values of a
        row into name, location, time, and item. Note that this is
        thrown when unpacking too few or two many values into a tuple
        of variables.

    :raises ValueError: If there is an issue loading the time (third
        column in each row) into a datetime object.

    :raises OSError: If there is an issue finding or opening the
        file. Note that this is thrown by the open() function.

    """
    timeline = ObservationTimeline()
    briefcases = {}
    try:
        with open(filename, newline='') as f:
            reader = csv.reader(f)
            for line in reader:
                if line[3] != '':
                    briefcases[line[0]] = line[3]
                curobs = Observation(line[0], line[1], line[2])
                timeline.add(curobs)
    except ValueError:
        print("""There was an error unpacking values from the file into the
            timeline. Exiting.""")
        sys.exit(1)
    except OSError:
        print("There was an error opening the file. Exiting.")
        sys.exit(1)

    return (briefcases, timeline)


def main(args):
    """Program entry point.

    - Loads a CSV file of observations

    - Determines how items were exchanged during various rendezvous

      - Prints the exchanges as they happen, if desired

    - Prints the latest owner of a specific item, if desired.

      - Otherwise neatly prints a dictionary mapping suspects to
        the item they currently own.

    This program will return an exit code of `1` in one of two
    situations:

    - If the CSV file cannot be opened (i.e., load_timeline raises an
      :class:`OSError`), this program will simply print the exception
      and end.

    - If the CSV file cannot be loaded (i.e., load_timeline raises a
      :class:`ValueError`), we will print an error messsage and end.

    :param argparse.Namespace args: A Namespace that contains parsed
        command line arguments.

    :returns: Nothing

    """
    briefcases, timeline = load_timeline(args.observations)

    try:
        for switch in timeline.rendezvous():
            if args.exchanges:
                print('{0} meets with {1} to exchange {2} for {3}.'.format(
                    switch[0].name, switch[1].name, briefcases[switch[0].name],
                    briefcases[switch[1].name]))
            tempobject = briefcases[switch[0].name]
            briefcases[switch[0].name] = briefcases[switch[1].name]
            briefcases[switch[1].name] = tempobject
    except ValueError:
        print("""Attempted to initialize an observation with the incorrect
                 datetime formatting. Exiting.""")
        sys.exit(1)
    except DataError:
        print("Three operatives listed at one rendezvous. Exiting")
        sys.exit(1)

    if args.item:
        for k, v in briefcases.items():
            if v == args.item:
                # Example online has no period on the end, leaving it that way
                print('{0} had the {1}'.format(k, v))
    else:
        pprint.pprint(briefcases)

if __name__ == '__main__':
    # Initialize CLI argument parser
    parser = argparse.ArgumentParser(
        description='List rendezvous exchanges based on a '
        'spreadsheet of suspect observations.'
    )

    # Add a positional argument for the observations file.
    parser.add_argument('observations',
                        help='A CSV file to read observations from.')

    # Add an optional flag, so that the user can tell us which item
    # they want to see the owner of
    parser.add_argument('--item', type=str, default='',
                        help='An optional item to print the owner of.')

    # Add an optional flag, that will tell us to print exchanges as
    # AND mapping of items
    parser.add_argument('--exchanges', action='store_true',
                        help='Print all exchanges')

    # Parse the arguments
    args = parser.parse_args()

    # GO!
    main(args)

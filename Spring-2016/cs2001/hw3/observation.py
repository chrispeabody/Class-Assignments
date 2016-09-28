# observation.py

import datetime


class Observation:
    def __init__(self, name, location, time):
        """Observation constructor

        :param str name: The name of the observed suspect.
        :param str location: The location where the suspect was observed.
        :param datetime.datetime time: The time the suspect was observed at
        the location.

        :raises ValueError: If the datetime could not be created with the
        time argument.

        :return: Returns the constructed Observation
        """
        self.name = name
        self.location = location

        self.time = datetime.datetime.strptime(time, "%Y-%m-%d %H:%M:%S")

    def __lt__(self, other):
        """Overload the < operator

        :param Observation other: The observation object we're comparing
        against.

        :return: True if this object's time is less than the other's time
        """
        return self.time < other.time

    def __le__(self, other):
        """Overload the <= operator

        :param Observation other: The observation object we're comparing
        against.

        :return: True if this object's time is less than or equal to the
        other's time
        """
        return self.time < other.time or self.time == other.time

    def __gt__(self, other):
        """Overload the > operator

        :param Observation other: The observation object we're comparing
        against.

        :return: True if this object's time is less than the other's time
        """
        return self.time > other.time

    def __ge__(self, other):
        """Overload the >= operator

        :param Observation other: The observation object we're comparing
        against.

        :return: True if this object's time is less than or equal to the
        other's time
        """
        return self.time > other.time or self.time == other.time

    def __str__(self):
        """Turns an observation into a string with format: <name> at
        <location> (<time>)

        :returns: The observation as a string
        """
        return self.name + " at " + self.location + " (" + self.time.strftime(
            "%Y-%m-%d %H:%M:%S") + ")"

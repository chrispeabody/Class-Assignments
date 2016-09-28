# observation_timeline.py

import datetime


class DataError(Exception):
    # An error thrown by ObservationTimeline
    pass


class ObservationTimeline:
    def __init__(self):
        """ Initializes an ObservationTimeline
        """
        self.observations = []

    def add(self, observation):
        """ Adds an Observation to the timeline of observations

        :param Observation observation: The Observation to add

        :return: None
        """
        self.observations.append(observation)
        self.observations = sorted(self.observations)

    def windows(self, window_size=datetime.timedelta(0, 3600)):
        """ A generator for iterating over windows of a given size.

        Iterates over the timeline's collection of Observations, yielding
        tuples of Observations that occured within a timedelta of
        window_size after the first observation in the window.

        :param datetime.timedelta window_size: The size of the window for
        looking into the future. Defaults to one hour (3600 seconds)

        :return: An iterable that yields tuples of Observations that occured
        within a time delta of window_size from the first Observation in the
        tuple. The size of the tuple will vary depending on the size of the
        window.
        """
        for base in self.observations:
            start = base.time
            end = start + window_size

            oblist = []
            for obs in self.observations:
                if obs.time >= start and obs.time < end:
                    oblist.append(obs)

            yield tuple(oblist)

    def rendezvous(self, window_size=datetime.timedelta(0, 3600)):
        """ A generator for chronologically iterating over rendezvous

        Iterates over windows (of duration window_size) to determine which
        of those windows contain a rendezvous. We detect a rendezvous for
        a window by checking whether the first observation in the window
        shares a location with any other observations in the window.

        :param datetime.timedelta window_size: The size of the window
        for looking into the future. Defaults to one hour (3600 seconds)

        :return: An iterable that yields pairs of Observation. Each pair
        corrisponds to two suspects who met at the same location within
        window_size of one another. Pairs are tuples, and each will have
        exactly two items.

        :raises DataError: if we detect a rendezvous has more than two
        members, ad DataError is raised. Something must be wrong with
        the input data.
        """
        for window in self.windows():
            for obs1 in window:
                twoalready = False
                for obs2 in window[window.index(obs1)+1:]:
                    if obs1.location == obs2.location:
                        if twoalready:
                            raise DataError
                        else:
                            twoalready = True
                            yield (obs1, obs2)

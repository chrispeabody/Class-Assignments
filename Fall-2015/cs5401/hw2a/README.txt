README

To use the program, type the following in to the command line:

python gpac.py

This will use the default configuration for the program, found in configs/default.cfg. If you wish to override the configuration, you should use the following:

python gpac.py <configpath>

Where '<configpath>' show be the local path to your desired configuration file.

----

Configuration files are made up of a list of labeld values. Each line has a label, followed by a space and the desired value for what is labeled. The order doesn't matter, but all labels must be used (except solfile currently) in the config at one point. The follow is a list of the labels:

height:
width:
pilldensity:
seed:
runs:
evals:
logfile:
solfile:
bestfile:

Height and width set the dimensions of the game board. Pill density is the percent chance (0-100) that a pill will be at a given location. Seed can be set to 'random' or a string representing a seed for the random generator. Runs and evals detail how many runs in an experiment and how many evaluations per run you would like. Log file is the relative path to the log for that config. Sol File will be the relative path to the solution file for the config. Best file is the relative path to the world file for the best run of the game in your experiment.
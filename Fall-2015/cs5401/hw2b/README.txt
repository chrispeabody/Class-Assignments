README

To use the program, type the following in to the command line:

python gpac.py

This will use the default configuration for the program, found in configs/default.cfg. If you wish to override the configuration, you should use the following:

python gpac.py <configpath>

Where '<configpath>' show be the local path to your desired configuration file.

----

Configuration files are made up of a list of label values. Each line has a label, followed by a space and the desired value for what is labeled. The order doesn't matter, but all labels must be used in the config at one point. The follow is a list of the labels:

height:
width:
pilldensity:
seed:
runs:
evals:
logfile:
solfile:
bestfile:
depthmax:
lambda:
mu:
noimprovementcount:
recombpercent: 
overselectprop:
parentselection:
surivivalselection:
kvalue:
parsepressure:

Explaination of labels. . .

height and width set the dimensions of the game board.

pilldensity is the percent chance (0-100) that a pill will be at a given location.

seed can be set to 'random' or a string representing a seed for the random generator.

runs and evals detail how many runs in an experiment and how many evaluations per run you would like.

logfile is the relative path to the log for that config.

solfile will be the relative path to the solution file for the config.

bestfile is the relative path to the world file for the best run of the game in your experiment.

The depthmax is the maximmum depth of the parse trees when they are first initialized (Note: the root itself is depth 0).

lambda and mu are use for population control. lambda is the number in any population, and mu is the number added per generation.

noimprovementcount is the number of generations where it is acceptable for the best fitness individual not to change before the run will terminate. Set to -1 if no-change-in-best-fitness termation should be deactivated.

recombpercent refers to the percent of time recombination will be used rather than mutation. A value of 50 will use recombination 50% of the time and mutation 50% of the time. A value of 70 will use recombination 70% of the time and mutation 30% of the time.

overselectprop is the percentage of the population that is put into the upper tier when using the over selection parent selection type.

parentselection is the type of parent selection to be used. Valid values are 'proportional' or 'overselection'. If an invalid type is given, proportional will be used.

survivalselction is the type of survival selection to be employed. Valid values are 'truncation' or 'ktournament'

kvalue is only necessary when survival selection is set to ktournament. It refers to the size of the k tournament.

parsepressure refers to the weight of the penalty that trees over depthmax in depth suffer on their fitness score. It's this number multiplied by the amount of depth further than the soft cap.

---

Test 3 and 4 are my official tests for this assignment. Earlier tests were to try finding a good configuration.
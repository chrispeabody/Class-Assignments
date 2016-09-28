To run the program with default configuration: python evoalgo1.py
This will create the output files at logs/log1.txt and solutions/sol1.txt

To run the program with a specified configuration: python evolve.py <configlocation>

The configuration file is setup as follows:
-----

<File path to the CNF file>
<File path to log file for this experiment>
<File path to solution file for this experiment>
<A string for the seed, or 'random' for a random seed>
<Number of runs for the experiment>
<Type of parent selection>
<Type of survival selection>
<Use evals termination? 'True' or 'False' followed by a number for how many evals>
<Use no avg change termination? 'True' or 'False' followed by a number for n>
<Use no best change termination? 'True' or 'False' followed by a number for n>
<Use r-elitist restarts? 'True' or 'False' followed by a number for r>
<Population size Mu>
<Offspring size Lambda>
<'No seed' for uniform random initialization, or a filepath to a seed file>
<Survival strategy. 'plus' or 'comma'>
<Self-Adapting recombination? 'True' or 'False'>

-----

Replace each <field> with the desired information. Each field is separated by a newline.

For parent selection, the following values are acceptable.
'proportional'
'tournament k' replace k with an integer
'random'
If an invalid parent selection is specified, proportional will be the default.

For survival selection, the follow values are acceptable.
'truncation'
'proportional'
'random'
'tournament k' replace k with an integer
If an invalid survival selection is specified, truncation will be the default.

If an invalid survival strategy is specified, plus will be the default

Note: There may be issues running the program if the solution and log files are not pre-created. I am working on fixing this.

Example config file:

-----

cnfs/1.cnf
logs/log1.txt
solutions/sol1.txt
random
30
tournament 10
truncation
True 10000
True 100
True 100
True 2
100
50
No seed
plus
True

-----








Seed files for the initial population should look as the following:
-----

-1 2 3 -4 5 -6 -7 -8 9 10 -11 . . . <up to the number of variables>
1 -2 -3 4 -5 -6 -7 8 9 -10 -11
1 2 -3 -4 -5 6 7 -8 -9 10 11
.
.
.

<up to the number of seeded population members>

----- (Do not include the '.' or sections in '< >')

Each line you include will represent a population member, where each element in the line is a variable's value. '-1', for example, will mean the first variable is False. While '1' would mean the first variable is true. The variable which is changed is non-dependant on the number which follows, and is instead dependant on the position. So the string '-2 1 4 -3' would make the first and fourth variable False, rather than the second and fourth.

You may include as many population seeds as you would like. Including a number less than the initial population size will randomize the remaining members, while including a number more than the initial population size will truncate the population to the first Mu seeds given.

-----



statalyzer.py ---> This python file is only used as a tool for stat testing. It takes in a log file and creates a SHEET file in the sheets folder, where the data is more easily copied into a spreadsheet editor like excel. Not used in the actual generation of data, purely auxillary. 

To use it, type:
python statalyzer.py <path to log file>

It will automatically generate the sheet file and put it in the sheets folder.

-----

To replicate results:
All the configuration files I used for testing can be found in the configs folder. 1.cfg, 2.cfg, etc, are the config files without adaptation or restarts. 1adapt.cfg, 2adapt.cfg, etc are the config files using self-adaptation but not restarts. 1restart.cfg, 2retart.cfg, etc are the config files using restarts but not self adaptation. 1both.cfg, 2both.cfg, etc are the config files where both self-adaptation and r-restarts were used.
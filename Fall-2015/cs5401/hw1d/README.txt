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
<Use no top-curve change termination? 'True' or 'False' followed by a number for n>
<Use r-elitist restarts? 'True' or 'False' followed by a number for r>
<Population size Mu>
<Offspring size Lambda>
<'No seed' for uniform random initialization, or a filepath to a seed file>
<Survival strategy. 'plus' or 'comma'>
<File path to the pareto front file>

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
True 2
100
50
No seed
plus
fronts/1paretos.txt

-----








Seed files for the initial population should look as the following:
-----

-1 2 3 -4 5 -6 -7 -8 9 10 ? . . . <up to the number of variables>
1 -2 ? 4 -5 -6 -7 8 9 -10 -11
1 2 -3 -4 -5 ? 7 ? ? 10 11
.
.
.

<up to the number of seeded population members>

----- (Do not include the '.' or sections in '< >')

Each line you include will represent a population member, where each element in the line is a variable's value. '-1', for example, will mean the first variable is False. While '1' would mean the first variable is true. The variable which is changed is non-dependant on the number which follows, and is instead dependant on the position. So the string '-2 1 4 -3' would make the first and fourth variable False, rather than the second and fourth. Additionally, '?' can be used to indicate a variable should not be set. The program will interpret that as an unset variable in the genes.

You may include as many population seeds as you would like. Including a number less than the initial population size will randomize the remaining members, while including a number more than the initial population size will truncate the population to the first Mu seeds given.

-----



statalyzer.py ---> This python file is only used as a tool for stat testing. It takes in two front files and outputs a SHEET file containing the percentages that each run of either file dominates the other. This is used for stat-testing two executions of the program agaisnt one another.

To use it, type:
python statalyzer.py <path to first front file> <path to second front file>

It will automatically generate the sheet file and put it in the sheets folder.
The program will also ask for the path to the solution files for both executions. It will then calculate the diversity of the generated solution.

-----

To replicate results:
All the configuration files I used for testing can be found in the configs folder.
test1.cfg
test2.cfg
test3.cfg
test4.cfg
test5.cfg
These were the files used. Each file was a different configuration, and each was a modification of the first test, test1.cfg. For details on the purpose for each, see the analysis.
To run the program with default configuration: python evoalgo1.py
This will create the output files at logs/log1.txt and solutions/sol1.txt

To run the program with a specified configuration: python evoalgo1.py <configlocation>

The configuration file is setup as follows:
-----

<File path to the CNF file>
<File path to log file for this experiment>
<File path to solution file for this experiment>
<A string for the seed, or 'random' for a random seed>
<Number of runs for the experiment>
<Type of parent selection. 'proportional' or 'tournament k' replace k with an int>
<Type of survival selection. 'truncation' or 'tournament k' replace k with an int>
<Use evals termination? 'True' or 'False' followed by a number for how many evals>
<Use no avg change termination? 'True' or 'False' followed by a number for n>
<Use no best change termination? 'True' or 'False' followed by a number for n>
<Population size Mu>
<Offspring size Lambda>

-----

Replace each <field> with the desired information. Each field is separated by a newline.

If an invalid parent selection is specified, proportional will be the default.
If an invalid survival selection is specifid, truncation will be the default.

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
100
50

-----

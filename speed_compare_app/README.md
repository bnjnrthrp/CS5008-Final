# Speed Compare Application


The Speed Compare Application is a program that compares the speed of different data structures. It is designed to be run from the command line, and takes in a few arguments. This application is completed for you. It is just meant to help you generate empirical data for analysis, and to provide an example of another way to generate data for tests. 

> STUDENT TODO:  
> Go through the code making comments helping you better understand the file distribution and how the code works. Ask yourself it there are any unique design aspects that stand out, anything you would have done differently, and anything you would like to know more about. Make sure to ask in the Teams channel if you have questions. 


## Operation

Running `make speed-compare` will build the executable. Running `./speed_compare.out` will run the program. It takes in a few arguments. You can always review the arguments by running `./speed-compare.out -h`. 

```
Usage: ./speed_compare_app [OPTIONS] input_file
This program compares the speed of the SortedLinkedList, SortedVector, and BST implementations
Input file (required): a file with movie titles listed on each line.
Options:
  -h, --help                    Prints this help message. Ends the program.
  -v, --verbose                 Prints extra information about the program.
  -d, --debug                   Prints debug information about the program. Setting debug will also enable verbose.
  -o, --output [FILE]           Prints the test output to the given file, assumes CSV format. Defaults to output.csv if not provided.
  -i, --increment [NUM]         Sets the increment amount for the number of movies to test. Defaults to 1000 if not provided.


Example Usage:
  ./speed_compare_app -v -o results.csv movie_titles_us_unique.txt
  ```

The above is the help message. It shows the required input file, and the options. The options are all optional, and have default values. 

### Recommended Usage
It is first recommended you run the program using a smaller input file. For example,

```bash 
$ ./speed_compare.out -d -o results_10k.csv -i 500 movie_titles_us_10000.txt
```

This will give you an example of what is printed to the console, and what is added to results_10k.csv.  You can open the excel file in VSCode (or any text file), excel, or google sheets. We found it helpful to have the [Rainbow CSV](https://marketplace.visualstudio.com/items?itemName=mechatroner.rainbow-csv) extension installed in VSCode to help align columns when looking in VSCode. 

However, once you are ready to run the full experiment, it is often better to let it run in the background. Running programs in the background are common, and the following explains how to run in the background on linux and macOS. Windows users can use the [Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/install-win10) to run linux commands.


### Running in the background

To run in the background, you can use the `&` symbol. For example, 

```bash
$ ./speed_compare.out -d -o results_100k.csv movie_titles_us_100000.txt &
```

However, that will print a lot of information to the screen, which can be really confusing when an application is running in the background. Instead, we would like to redirect the output to a file. To do this, we use the `>` symbol. For example, 

```bash
$ ./speed_compare.out -d -o results_100k.csv movie_titles_us_100000.txt > log.txt &
```

The log.txt then becomes a searchable file that gets updated as the program runs with anything that would have printed to the console. You should first feel free to try this command with the smaller 10k file to see how it works.

```bash
$ ./speed_compare.out -d -o results_10k.csv movie_titles_us_10000.txt > log.txt &
```

> **WSL/WINDOWS IMPORTANT NOTE**  
> DO NOT close your terminal while it is running, even if it is running in the background. Depending on how windows is setup, this can kill your background processes as it may close the linux subsystem/shut down the linux OS on windows. Instead, minimize the terminal. Restarting the computer will kill the background processes also. 

### Checking progress of the run

Depending on the number of movies, running the speed test can take a while. For example, as I write this, speed_compare has been running for 15 hours, 6 minutes and 22 seconds. It is currently at N of 166,000 of 925,175. How did I find that all out, I relied on my trusty linux command line! There are a number of programs that you will find useful for running your experiment.

* ps    - gives you the current processes running
* kill  - ends/kills a process
* tail  - gives you the last few lines of a file
* wc    - gives you the word count of a file, but with the right option only gives the lines
* shuf  - randomly shuffles the lines of a file (good for building test files)



#### ps

Once your program is running in the background, you will want to check it. You can do this at any time by running

```bash
$ ps
```

It will list the current processes active in that shell/terminal. However, if you closed the terminal (mac and linux, for windows see the warning above!), you can still check the processes. You can do this by running

```bash
$ ps -a | grep speed_compare
```

Grep is a way to filter/search the results, `-a` gives you all processes being ran by you. The `|` symbol is called a pipe, and it takes the output of the first command and uses it as the input for the second command. So the above command will give you all processes that have speed_compare in the name.

#### kill

If you want to kill the speed_compare application, you can do so by running

```bash
$ kill [PID]
```

Where `[PID]` is the process ID. You can get the process ID by running `ps` or `ps -a | grep speed_compare`. The process ID is the first number on the line. For example, 

```bash
$ ps -a | grep speed_compare
  5012 pts/0    15:17:19 speed_compare.o
```

The process ID is 5012. So to kill the process, I would run

```bash
$ kill 5012
```

Why would I do this? If I managed to put in too large of a file or I think my results file has enough results in it for me to get a good idea of the speed curves. Also good if I write a program that accidentally hangs / has an infinite loop in it. As such, programmers who use the command line often get to know `kill` very well. If kill doesn't work, you can use `kill -9 [PID]` which will force kill the process, however, it is often better to use `kill` first, and then `kill -9` if that doesn't work.

#### tail
The tail command will help you see the last few lines of a file. This is useful for checking the progress of your program and works well since speed_compare.out saves the file after every line is written, so you can consistently check its progress without interrupting the written file. For example, 

```bash
$ tail results_100k.csv
```

Will produce the last few lines of the file. You can also do the same thing with your log file.

```bash
$ tail log.txt
```

Here are example outputs for both.

```bash
$ tail solution_results.csv 
157000.000000,68.240333,87.508171,0.075335,0.068438,264.005251,0.135747,0.028657,0.036908,0.025300,8.570443,196.373988,0.160037,19.096969,0.007534,0.001210,0.004496,20.858299,0.005015,0.001161,148.397659,0.000961,89.712631
158000.000000,69.684683,88.936405,0.087649,0.082920,266.916027,0.115461,0.027489,0.035339,0.024558,8.717734,198.413238,0.166560,19.200617,0.007424,0.001209,0.004428,21.084978,0.006240,0.001155,145.573453,0.000889,91.142659
159000.000000,70.614821,90.038150,0.084871,0.080045,274.169876,0.146459,0.029730,0.037773,0.025838,8.828256,203.098166,0.172856,19.430721,0.006478,0.001185,0.003261,21.313240,0.004524,0.001139,153.097946,0.000795,92.532066
160000.000000,71.347628,118.791620,0.096447,0.088582,350.054422,0.160327,0.026531,0.034052,0.027635,8.999419,272.393764,0.176569,19.811771,0.007779,0.001217,0.006905,21.679725,0.007171,0.001193,228.651168,0.001091,140.816580
161000.000000,82.156935,113.838534,0.088165,0.087451,322.503280,0.147674,0.029284,0.038629,0.026550,9.083538,213.478309,0.170687,19.987035,0.007431,0.001244,0.006249,21.999286,0.006597,0.001262,167.617023,0.000977,98.078812
162000.000000,75.148954,98.396080,0.091104,0.084788,300.622665,0.151312,0.029065,0.038553,0.027133,9.145468,224.242345,0.176502,20.308625,0.007737,0.001243,0.005053,22.249196,0.005882,0.001214,216.228453,0.000946,106.445655
163000.000000,91.512504,136.402025,0.116716,0.100478,421.749849,0.174010,0.031319,0.040441,0.029949,9.816287,346.341407,0.195707,20.961762,0.010981,0.001249,0.006141,22.611989,0.005971,0.001213,316.397031,0.000968,213.836888
164000.000000,95.728739,142.383774,0.118728,0.108882,394.766700,0.166764,0.040588,0.038882,0.030273,9.646471,320.447345,0.176398,20.753143,0.008511,0.001218,0.004174,22.853343,0.005384,0.001173,255.045384,0.000937,161.553738
165000.000000,88.423752,112.388845,0.099373,0.088836,352.039632,0.139397,0.023762,0.031340,0.028102,9.591725,275.391383,0.164962,21.006987,0.007700,0.001312,0.005144,23.115972,0.006113,0.001182,249.845058,0.000987,137.600736
166000.000000,88.763036,115.032805,0.102085,0.096797,442.953898,0.204604,0.025920,0.036054,0.029787,9.979916,394.792745,0.245750,22.106283,0.009931,0.001288,0.005429,23.599280,0.006384,0.001289,181.371902,0.000981,158.927898
```
```bash
$ tail log.txt 
(DEBUG): Removing from list
(DEBUG): ...result was 177.600384
(INFO): Finished running tests

(INFO): Running Tests on 170000 movies
(INFO): Adding movies 170000 to each data structure
(DEBUG): Adding to sorted vector
(DEBUG): ...result was 80.459596
(DEBUG): Adding to sorted list
```

You can also open the files in VSCode or another text editor while the program is running since they are constantly being saved. You may want to avoid opening them in excel as it may lock out the files for saving causing an access conflict.


#### Adding your own test files
Of the test files provided in the [speed_test_files](../speed_test_files/) folder, you will see what have 1000, 10000, 100000, and unique movies. The number of unique movies is rather large, as you can tell doing a quick word count.

```bash
$ wc -l speed_test_files/movie_titles_us_unique.txt 
925175 speed_test_files/movie_titles_us_unique.txt
```
That is 925,175 lines in the file! That is a lot of movies. The original data set had 1,000,000 movies, but we removed duplicates using the `unique` command line program. However, while 100,000 may be useful, you may want to create your own test files. You can do this using the `shuf` command. For example, 

```bash
$ shuf -n 50000 speed_test_files/movie_titles_us_unique.txt > speed_test_files/movie_titles_us_50000.txt
```

That will randomly shuffle the lines in the file, and then take the first 50,000 lines and save them to a new file. You can then use that file for your own tests. You can also do the same creating maybe 150,000 line file. 

> **What, why so many commands? To the rescue man(ual)!**  
> In linux/macOS it is the philosophy to have a program that does one thing and does it well. You then have program
> arguments to add options to that command. There are many tools
> on the command line for manipulating, reading, and handling text files. These tools are great for helping 
> with tests, finding information on the computer, and automating tasks. Learning more about the command line
> and the many tools will often make you a better and more efficient programmer. However, very few people
> remember all combinations. Instead, they often look up the commands they need. For example, I knew I wanted
> to a smaller file using the shuf command, I used `man shuf` to learn more about the shuf command, and what
> options I had. 

### Summary 
Using the above commands and some careful thought (and exploration), you should be able to generate a fair number of
lines in your .CSV file that helps you determine the trend of the algorithms runtime. You can then use this data to
help answer questions in your report.
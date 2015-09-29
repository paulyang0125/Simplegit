# Simplegit
simplegit is essentially a simpler version of git, which is developed to let you understand the basic operations of git init, add, rm, commit, branch, checkout, status and log. 



## How it work

simplegit supports the command line and can track individual files in the current working directory (no subdirectories!). It maintains a .simplegit/ subdirectory containing information about your repository. For each commit that the user makes, a directory is created inside the .simplegit/ directory (.simplegit/<ID>, where <ID> is the ID of the commit). The .simplegit/ directory additionally contains two files: .index (a list of all currently tracked files, one per line, no duplicates) and .prev (contains the ID of the last commit, or 0..0 if there is no commit yet). Each .simplegit/<ID> directory contains a copy of each tracked file (as well as the .index file) at the time of the commit, a .msg file that contains the commit message (one line) and a .prevfile that contains the commit ID of the previous commit.


## File structure

- simplegit.c - The core implementation of simplegit.
- cunittests.c - the unit tests to test your code.
- simplegit.h - This file contains declarations of various constructs in simplegit.c along with convenient #defines. See the "Important Numbers" section below.
- cunittests.h - Declarations needed for use with the cunit library.
- main.c - Contains the main for simplegit (which parses command line options and calls into the functions defined in simplegit.c).
- Makefile - This tells the program make how to build your code when you run the make command. This is a convenient alternative to having to repeatedly type long commands involving gcc.
- util.h - Contains helper functions declarations.
- util.c - Contains implementation of the helper functions declaraed in until.h. 

## Automated basic tests and UnitTest

You can run the following command to observe the simplegit's outputs 

```
make check

Running test cases...

  [  OK  ] simplegit_test_add_0
  [  OK  ] simplegit_test_add_1
  [  OK  ] simplegit_test_rm_0
  [  OK  ] simplegit_test_commit_0

  More...

TESTS PASSING: 4 / 10

```

I use [CUnit](http://cunit.sourceforge.net/doc/index.html) for unittest purpose. In order to run tests, you should do the following:

```
[assumes you are inside your proj1 directory]
$ make simplegit-unittest
$ source init_test
$ simplegit-unittest

Suite: Suite_1
  Test: Simple Test #1 ...passed
Suite: Suite_2
  Test: Log output test ...passed

Run Summary:    Type  Total    Ran Passed Failed Inactive
              suites      2      2    n/a      0        0
               tests      2      2      2      0        0
             asserts      4      4      4      0      n/a

Elapsed time =    0.007 seconds     

```


## Limitations:

simplegit does not track diffs between files. Instead, each time you make a commit, it simply copies all files that are being tracked into the .simplegit/<ID> directory (where <ID> is the commit ID).


## License:
The MIT License (MIT) Copyright (c) 2015 Yang Yao-Nien 

Permission is hereby granted, free of charge, to any person obtaining a copy ofthis software and associated documentation files (the "Software"), to deal inthe Software without restriction, including without limitation the rights touse, copy, modify, merge, publish, distribute, sublicense, and/or sell copies ofthe Software, and to permit persons to whom the Software is furnished to do so,subject to the following conditions: The above copyright notice and this permission notice shall be included in allcopies or substantial portions of the Software. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS ORIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESSFOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS ORCOPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHERIN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR INCONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.




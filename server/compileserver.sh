#!/bin/bash
gcc -o webserver webserver.c http.c serverwrappers.c controlwrappers.c ../file-handling/fhandling.c


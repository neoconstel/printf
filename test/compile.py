# this script is to simply make it quicker to compile our code, so we need not 
# type a long compile command

# to use, do:
# python3 compile.py


import os

os.system("rm testrun") # remove former one so we are sure any 'testrun' we see means a compile success
os.system("gcc main.c ../_printf.c -o testrun") # compile and name the output 'testrun'
os.system("./testrun")  # run it -- or comment out this line if you don't want it to run
# I have made this sript for making the process of diagnosing errors with betty
# faster.

# ---Why it is needed---:
# While working with betty checker, supposing there are so many errors that fill
# the screen it becomes difficult while scrolling to know whether you're seeing 
# the new betty output or the former outputs which you may have fixed already. 
# You then have to scroll  until you come to the beginning of the most recent 
# betty output. Of course the solution is to do a <clear> first in the terminal, 
# but it becomes time-consuming when you have to run 
# <clear> and <betty ../printf.c> each time.


# ---What the script does---:
# So then, this script combines those two functionalities in one go -- so all you
# need is to run this file, and it clears the screen first then tests our c file.


# ---How to use it---
# while in the directory "test", simply run: python3 betty.py


import os

os.system("clear")
os.system("betty ../_printf.c")
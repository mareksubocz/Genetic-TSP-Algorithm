import glob
import os
from termcolor import colored

for filepath in glob.iglob('data/*.tsp'):
    
    print(colored(filepath + ":", 'green'))
    filepath2 = filepath[0:-3]
    filepath2 = filepath2 + "opt.tour"
    if not glob.glob(filepath2):
    	filepath2 = ""
    os.system("./a.out " + filepath +" "+ filepath2)

import glob
import os

for filepath in glob.iglob('data/*.tsp'):
    print("-" + filepath + ":")
    filepath2 = filepath[0:-3]
    filepath2 = filepath2 + "opt.tour"
    os.system("g++-8 greedy.cpp && ./a.out " + filepath +" "+ filepath2)
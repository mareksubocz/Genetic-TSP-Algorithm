import glob
import os, re
from termcolor import colored
os.system("g++-7 greedy.cpp")

#generatedData
arr = glob.iglob('generatedData/*.tsp')
arr = sorted(arr, key = lambda x: int(x.split("/")[-1].replace("test","").replace(".tsp","")))
# arr = sorted(arr, key = lambda x: int(re.search('test(.*).tsp', x).group(1)) )
#tsplibData
# arr = sorted(glob.iglob('data/*.tsp'))

for filepath in arr:
    print(colored(filepath + ":", 'green'))
    filepath2 = filepath[0:-3]
    filepath2 = filepath2 + "opt.tour"
    if not glob.glob(filepath2):
    	filepath2 = ""
    os.system("./a.out " + filepath +" "+ filepath2)

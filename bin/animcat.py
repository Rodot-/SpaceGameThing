import sys
from PIL import Image
import numpy as np

f1 = sys.argv[1] #first file
f2 = sys.argv[2] #second file
f3 = sys.argv[3] # outfile
order = sys.argv[4] #row or column (r or c)
axis = 0 if order[0] == 'c' else 1

Image.fromarray(np.concatenate((np.array(Image.open(f1)), np.array(Image.open(f2))), axis = axis)).save(f3)



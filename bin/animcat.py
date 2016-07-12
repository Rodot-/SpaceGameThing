import sys
from PIL import Image
import numpy as np

if len(sys.argv) == 2:

	f1 = sys.argv[1]
	Image.fromarray(np.concatenate([np.array(Image.open(f1))[:,i*128:(i+1)*128:,:] for i in xrange(12)], axis = 1)[:,::-1,:]).save("reversed"+f1)

if len(sys.argv) == 5:

	f1 = sys.argv[1] #first file
	f2 = sys.argv[2] #second file
	f3 = sys.argv[3] # outfile
	order = sys.argv[4] #row or column (r or c)
	axis = 0 if order[0] == 'c' else 1

	Image.fromarray(np.concatenate((np.array(Image.open(f1)), np.array(Image.open(f2))), axis = axis)).save(f3)

elif len(sys.argv) == 3:
	import glob, re
	files = glob.glob(sys.argv[1]+'*')
	Image.fromarray(np.concatenate(map(lambda x: np.array(Image.open(x)), sorted(files, key = lambda x: int(re.findall('\d+',x)[0]))), axis = 1)).save(sys.argv[2])
	
print len(sys.argv)

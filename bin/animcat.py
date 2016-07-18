'''
Program: animcat.py
Purpose: quickly manipulate multiple images to creat animation tilesheets
Author: Jack O'Brien
Requires:
	Python Image Library (PIL) for image i/o
	Numpy for mathematical operations on arrays

usage:
	$ python animcat.py [args] [filenames] 

output: .png file contents to be piped into a file

args:
   -c				column concatenate
   -r				row concatenate (default)
   -f				flip frames
   -s[N]			scale by a factor of N 
   --help 			display (this) help message 
   --example [N]	display example N as a tutorial. N can be any of the following:
		blank			N is set to 1 by default, show example 1
		1				how to save the output
		2				how to concatenate multiple files
		3				how to flip an image
		4				how to flip a sequence of images (flip animation)
		5				how to resize an image
		6				how to use multiple commands at once
		7				how to use multiple runs for more complex tasks
'''

import sys, re

#make sure that the user has the proper libraries installed
try:
	from PIL import Image
except ImportError as e:
	print e
	print "Python Image Library Required, Please Install Through pip or Online"
	exit(1)
try: 
	import numpy as np
except ImportError as e:
	print e
	print "Numpy Required, Please Install Through pip or Online"
	exit(1)

if len(sys.argv) == 1: #make sure we at least have some arguments
	print "No Arguments Specified.  Try using --help for help"
	exit(0)

if sys.argv[1] == '--help': #check if the user needs help
	print __doc__ #if so, display the file docstring (documentation)
	exit(0) #and then exit

if sys.argv[1] == '--example': #check if the user wants an example/tutorial

	if len(sys.argv) >= 3: #an example number was provided 
		assert (re.match("[1-7]", sys.argv[2]) is not None), "N must be an integer from 1 to 7!"
		exampleNo = int(sys.argv[2])
	else: exampleNo = 1 #by default, the example number is 1
	with open("README.md",'rb') as readme: #open the readme to get the examples
		text = [] #list of lines of text we'll be outputting
		isReading = False #are we currently adding text to our list?
		for line in readme: 
			if ('Python Script: animcat.py' in line): #find where the section starts
				isReading = True
			if (line.startswith('\t%i' % exampleNo)): #ditto
				isReading = True
			if (line.startswith('\t%i' % (exampleNo+1)) or line.startswith('-')): #break at section ends
				isReading = False
			if isReading: #if we're reading, add the line to our display text
				text.append(line)
		text = "".join(text)	# concatenate the lines, text should already have the newline characters
	print text #print the example
	exit(0)	

outfile = sys.stdout #print the result to stdout so it can be saved by a pipe
form = 'png' #save all of these as png images
axis = 1 #row by default
args = [] 
index = 1 #offset where the image files start in the cline args
resize = False #are we resizing the image?
for i, arg in enumerate(sys.argv[1:]):

	if arg.startswith('-'): args.append(arg[1:]) #get our arguments
	else: 
		index += i #set the index
		break #break out when we have no more args
	
image_files = sys.argv[index:]

#some general assertions to make sure we can continue
assert (not (('r' in args) and ('c' in args))), "Can only chose 'row' or 'column', not both!"
assert (len(image_files)), "No files specified!"
assert (all(map(lambda x: x.endswith(form), image_files))), "All images must be .%s files!" % form

images = [np.array(Image.open(i)) for i in image_files] #open all of the images after the ith term

#test is all images are the same size
comp = lambda x,y: all([x[i] == y[i] for i in xrange(len(x))]) #compare sizes
s = map(lambda x: x.shape, images) #get the size of each image
N = len(s) #get the number of images
size_test = all([comp(s[i], s[j]) for i in xrange(N) for j in xrange(N)]) #make sure all are the same
assert (size_test), "Not all images have the same dimensions!"

for arg in args:

	if arg == 'r': axis = 1 #if row, set the concatenation axis to 1 (side by side)

	elif arg == 'c': axis = 0 #if column, set it to 0 (stacked on top of eachother)

	elif arg == 'f': #if flip, flip the images and their order (make l/r animations)
	
		image_func = lambda x: x[:,::-1,:] #function that flips the images horizontally
		images = map(image_func, images) #flip each image

	elif arg.startswith('s'): #do some up/downsampling

		factor_str = arg[1:] #string of the number we'll use as the resampling factor
		ptrn = "^(\d+|(\d+\.\d*))$" #regular expression to match ints and floats
		#more assertions to keep Nick from fucking up
		assert (len(factor_str)), "No resampling factor specified!"
		assert (re.match(ptrn, factor_str) is not None), "Invalid resampling factor: %s" % factor_str
		resize_factor = float(factor_str) #factor by which we'll resize
		resize = True #Let the program know we're going to resize the image

new_image = np.concatenate(images, axis = axis) #concatenate the images along our chosen axis

semifinal_image = Image.fromarray(new_image) #create a new image object from the array

if resize: #do the resizing through PIL (because Fourier analysis is hard)

	height, width, _ = new_image.shape #get the current dimensions of our image in pixels
	size = np.array([width, height], dtype = 'float64') #create the size array (will later be a tuple)
	size *= resize_factor #rescale the image dimensions
	size = map(round, size) #round the height and width to nearest int
	size = map(int, size) #make sure these are ints
	size = tuple(size) #the final new image size as a tuple
	final_image = semifinal_image.resize(size, Image.ANTIALIAS) #resize the image using antialiasing

else: final_image = semifinal_image # out final image has not been scaled

final_image.save(outfile, form) #save the image as a png and send it to stdout


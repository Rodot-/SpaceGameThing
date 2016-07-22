'''
Program: animcat.py
Purpose: quickly manipulate multiple images to create animation tilesheets
Author: Jack O'Brien
Requires:
	Python Image Library (PIL) for image i/o
	Numpy for mathematical operations on arrays

usage:
	$ python animcat.py [args] [filenames] 

output: .png file contents to be piped into a file

args:
   -i				interactive mode 
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

import sys, re, os

#some quick global values
outfile = sys.__stdout__ #print the result to stdout so it can be saved by a pipe
sys.stdout = sys.__stderr__
form = 'png' #save all of these as png images
axis = 1 #row by default
args = [] 
index = 1 #offset where the image files start in the cline args
resize = False #are we resizing the image?

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

if sys.argv[1] == '-i':
	print "Interactive mode enabled"
	print "------------------------\n"
	print "What files are you working with?"
	print "Please type one file at a time and press enter"
	print "When you are done, press enter again to continue"
	file_list = [] #list of image files we'll use
	value = None
	index = 1
	while (value != ''):
		#prompt user for a file name
		value = raw_input("File %i:" % index).strip()
		if value != '': 
			if os.path.isfile(value): #verify that it's a file
				file_list.append(value) #if so, add it to our list
				index += 1 
			else:
				print "That file does not exist"
		else:
			if not len(file_list): #make sure the list is not empty
				print "No files selected, exiting..."
				exit(0)
	print "\nHere are the files you selected:"
	for f in file_list: #print the selected files
		print "     %s" % f
	yn = ''
	while (yn != "N" and yn != "Y"): #make sure the user agrees with it
		yn = raw_input("Is this correct? (y/n):").upper().strip()

	if yn == 'N': #if not, just quit, no time to make the loop bigger
		print "Exiting..."
		exit(0)

	print "\nWhat actions would you like to perform?"
	print "Options are: "
	print "     row     (Row Concatenation)"
	print "     column  (Column Concatenation)"
	print "     flip    (Flip the Animation)"
	print "     scale   (Scale the Animation)"
	print "Please type one option at a time and press enter"
	print "When you are done, press enter again to continue"
	value = None
	allowed_actions = ["ROW","COLUMN","FLIP","SCALE"] #possible actions that can be done
	arguments = dict(zip(allowed_actions, ['-r','-c','-f','-s'])) #mapping to valid args 
	actions = [] #list of properly converted args
	index = 1
	while value != '':
		#prompt the user for an argument
		value = raw_input("Action %i:" % index).strip().upper() 
		if value == '': 
			if (not len(actions)): #make sure we have valid arguments
				print "No actions selected, exiting..."
				exit(0)
			else:
				break
		elif value not in allowed_actions: #is the action valid?	
			print "That is not a valid option"	
			continue
		else:
			argument = arguments[value] #convert to an argument
		if argument in actions: #make sure we don't duplicate anything except scaling
			print "You've already selected this option"
		else:
			if argument == '-s': #if we are scaling, ask for the scaling factor
				bad = True
				ptrn = r"^(\d+|(\d+\.\d*))$" #regular expression to match ints and floats
				while (bad):
					scale = raw_input("By what factor would you like to scale the image by?:").strip() 	
					if (re.match(ptrn, scale) is not None): #make sure the input is a number
						if (0 < float(scale)): #make sure the input is positive 
							argument += scale #complete the argument
							bad = False
						else:
							print "That is not a valid number"
					else:
						print "That is not a valid number"
			actions.append(argument) #add our argument to the list
			index += 1

	print "\nHere are the actions you are going to perform:"
	for action in actions: #verify with the users that actions that will be done
		if action == '-r':
			print "     Concatenate the image sequence row-wise"
		elif action == '-c':
			print "     Concatenate the image sequence column-wise"
		elif action == '-f':
			print "     Flip each image in the sequence"	
		elif action[:2] == '-s':
			print "     Scale image by a factor of %s" % action[2:]

	yn = ''
	while (yn != "N" and yn != "Y"):
		yn = raw_input("Is this correct? (y/n):").upper().strip()

	if yn == 'N':
		print "Exiting..."
		exit(0)

	#ask the user where he wants to save the file to
	bad = True
	print "\nWhere would you like to save the file?"
	while (bad):
		outFileName = raw_input("Filename:")
		if outFileName == '': #make sure it's a valid file name
			print "Invalid File Name"
		elif os.path.isfile(outFileName): #check if the user wants to overwrite
			yn = ''
			while (yn != "N" and yn != "Y"):
				yn = raw_input("That file already exists, would you like to overwrite it? (y/n):").strip().upper()
			if yn == 'Y': #if yes, DO IT
				bad = False
		else:
			bad = False	
		
	#concatenate the lists to create a functional set of args
	sys.argv = [sys.argv[0]] + actions + file_list 
	#set the output to the file selected by the user
	outfile = open(outFileName,'wb')
	index = 1 #reset our index	
	#now let the new sys.argv go through the rest of the program
	print "\nRunning animcat with the parameters provided..."

if sys.argv[1] == '--help': #check if the user needs help
	print __doc__ #if so, display the file docstring (documentation)
	exit(0) #and then exit

if sys.argv[1] == '--example': #check if the user wants an example/tutorial

	if len(sys.argv) >= 3: #an example number was provided 
		assert (re.match("[1-7]", sys.argv[2]) is not None), "N must be an integer from 1 to 7!"
		exampleNo = int(sys.argv[2])
	else: exampleNo = 1 #by default, the example number is 1
	assert (os.path.isfile("README.md")), "Could not find README.md, cannot show examples!"
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

for i, arg in enumerate(sys.argv[1:]):

	if arg.startswith('-'): args.append(arg[1:]) #get our arguments
	else: 
		index += i #set the index
		break #break out when we have no more args
else:
	index += i + 1 #if everything is an arg, we need an extra index, even though it wont matter

image_files = sys.argv[index:] #get our image files

#some general assertions to make sure we can continue
for f in image_files: assert (os.path.isfile(f)), "Could not find file: %s" % f
assert (not (('r' in args) and ('c' in args))), "Can only chose 'row' or 'column', not both!"
assert (len(image_files)), "No files specified!"
assert (all(map(lambda x: x.endswith(form), image_files))), "All images must be .%s files!" % form


#try to sort the image files using a regular expressions pattern matching if we can
print "Attemping to sort image files by name..."
ptrn = r"(\d+|(\d+(\.|-|_)\d*))\.%s$" % form # pattern matching numbers at the end of a filename
argsort = [] #array that contains the numerical values by which we sort
for f in image_files:
	search = re.search(ptrn, f) #Search for a number at the end of the file name
	if search is None: #check if we found anything.  If not, tell the user we can't sort
		print "Attempt to sort images failed, continuing..."
		break #since we can no longer sort, we'll break out here
	else:
		value = search.group(1) #get the regex patten match
		value = re.sub(r'(-|_)','.', value) #sub - and _ with decimal points
		value = re.sub(r'^0*','',value) #get rid of left zeros
		argsort.append(float(value)) #convert the result to a float and add it to our list
else:
	print "Images will be sorted..."
	image_files = zip(*sorted(zip(image_files, argsort), key = lambda x: x[1]))[0] #argsort them

print "Loading Images..."
images = [np.array(Image.open(i)) for i in image_files] #open all of the images after the ith term
#test is all images are the same size
assert (reduce(lambda x,y: x if x == y else False, map(np.shape, images))), "Not all images have the same dimensions!"

for arg in args:

	if arg == 'r': axis = 1 #if row, set the concatenation axis to 1 (side by side)

	elif arg == 'c': axis = 0 #if column, set it to 0 (stacked on top of eachother)

	elif arg == 'f': #if flip, flip the images and their order (make l/r animations)
	
		image_func = lambda x: x[:,::-1,:] #function that flips the images horizontally
		images = map(image_func, images) #flip each image

	elif arg.startswith('s'): #do some up/downsampling

		factor_str = arg[1:] #string of the number we'll use as the resampling factor
		ptrn = r"^(\d+|(\d+\.\d*))$" #regular expression to match ints and floats
		#more assertions to keep Nick from fucking up
		assert (len(factor_str)), "No resampling factor specified!"
		assert (re.match(ptrn, factor_str) is not None), "Invalid resampling factor: %s" % factor_str
		resize_factor = float(factor_str) #factor by which we'll resize
		resize = True #Let the program know we're going to resize the image

print "Concatenating Images..."
new_image = np.concatenate(images, axis = axis) #concatenate the images along our chosen axis

semifinal_image = Image.fromarray(new_image) #create a new image object from the array

if resize: #do the resizing through PIL (because Fourier analysis is hard)

	print "Resizing Image..."
	height, width, _ = new_image.shape #get the current dimensions of our image in pixels
	size = np.array([width, height], dtype = 'float64') #create the size array (will later be a tuple)
	size *= resize_factor #rescale the image dimensions
	size = map(round, size) #round the height and width to nearest int
	size = map(int, size) #make sure these are ints
	size = tuple(size) #the final new image size as a tuple
	final_image = semifinal_image.resize(size, Image.ANTIALIAS) #resize the image using antialiasing

else: final_image = semifinal_image # out final image has not been scaled

print "Saving..."
final_image.save(outfile, form) #save the image as a png and send it to stdout


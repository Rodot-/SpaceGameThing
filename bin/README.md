README.md
This folder contains all game art assets as well as game scripts and image manipulation tools

use of the '-' character at the end of a line indicates the end of a section

Python Script: animcat.py

Examples:
	This is a tutorial for the usage of this script.
	The '$' symbol indicates the bash prompt 
	Elipses, '...', indicate further arguments (etc.)
	File names support globbing
	This Tutorial is purely symbolic:
		arguments inside square brackets [] need to be substituted by the user

-
	1. Saving the Output
		To save the output of a run, use the '>' operation 
		on the command line to pipe the result into a file

			$ python animcat.py [args] [fileNames] > [outFileName]

	2. Concatenating Files
		Files can be concatenated in two ways:

		First, row wise by using the argument '-r'
		This will concatenate images horizontally, left to right

			$ python animcat.py -r [file1] [file2] ... > [outFileName]

		Second, column wise by using the argument '-c'
		This will concatenate images vertically, top to bottom

			$ python animcat.py -c [file1] [file2] ... > [outFileName]

	3. Flipping an Image
		Single images can be flipped using the argument '-f'

			$ python animcat.py -f [fileName] > [outFile]

	4. Flipping an Animation
		A sequence of images can also be flipped, and their
		order will be reversed. This is useful for making 
		left and right versions of the same animation

			$python animcat.py -f [file1] [file2] ... > [outFileName]

	5. Resizing and Image 
		The resulting image can be resized using the argument '-s[N]'
		where 'N' represents a scaling factor.
		To down sample the image by a factor of 4 (half height, half width)
		
			$ python animcat.py -s0.5 [fileNames] > [outFileName]
		
		To up sample the image by a factor of 4 (double height, double width)

			$python animcat.py -s2 [fileNames] > [outFileName]

	6. Doing Mutiple Operations at Once
		Multiple arguments can be supplied to perform multiple 
		operations in a single run. 

		To concatenate a sequence of images	vertically while 
		shrinking the size of the final image by a factor of 4

			$ python animcat.py -c -s0.5 [file1] [file2] ... > [outFileName] 

		To concatenate a sequence of images, flip each one, reverse their order,
		and up scale the resulting image by a factor of 2 (sqrt(2) in each direction)

			$ python animcat.py -r -f -s1.41 [file1] [file2] ... > [outFileName]

	7. Multstep Image Manipulation
		More complex operations can be performed over mutiple runs
		We'll demonstrate an example in which we create a multi-row
		tilesheet containing a left and right animation on each row
		starting from an image sequence.

		First, we'll create the forward animation tilesheet

			$ python animcat.py -r [frame1] [frame2] ... > [forwardAnimation]

		Next, we'll create the backwards animation in the same way

			$ python animcat.py -r -f [frame1] [frame2] ... > [backwardsAnimation]

		Now that we have two animation tilesheets, we just have to stack them on top
		of eachother

			$ python animcat.py -c [forwardAnimation] [backwardsAnimation] > [fullTileSheet]

		Now we have a tile sheet with the forwards and backwards 
		animation on their own rows
-



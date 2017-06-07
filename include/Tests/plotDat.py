from matplotlib.pyplot import subplots, show
import numpy as np
import sys
import time	

fig, ax = subplots(1,1)
fig.canvas.draw()
show(False)
for i in sys.argv[1:]:
	with open(i,'r') as f:
		data = np.array([map(float, line.split()) for line in f])
		line = {}
		ax.set_xlim(0,26)
		ax.set_ylim(0, 5)
		for j in xrange(10):
			line[j], = ax.plot([],[])
		#show(False)
		for t in xrange(len(data)):
			ax.draw_artist(ax.patch)
			for j in xrange(10):
				line[j].set_data(data[:t,1+2*j], data[:t,2+2*j])
				ax.draw_artist(line[j])
			#fig.canvas.draw()
			fig.canvas.update()
			fig.canvas.flush_events()
			#time.sleep(0.001)
show()	

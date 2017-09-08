##import numpy as np
##import matplotlib.pyplot as plt
##
##
##xvals = np.arange(-2, 1, 0.01) # Grid of 0.01 spacing from -2 to 10
##yvals = np.cos(xvals) # Evaluate function on xvals
##plt.plot(xvals, yvals) # Create line plot with yvals against xvals
###plt.show()
##
##newyvals = 1 - 0.5 * xvals**2 # Evaluate quadratic approximation on xvals
##plt.plot(xvals, newyvals, 'ro--') # Create line plot with red dashed line
##plt.title('Example plots')
##plt.xlabel('Input')
##plt.ylabel('Function values')
##plt.show() # Show the figure (remove the previous instance)
##

##import numpy as np
##import pylab as pl
##
### Make an array of x values
##x = [1, 2, 3, 4, 5]
### Make an array of y values for each x value
##y = [1, 4, 9, 16, 25]
### use pylab to plot x and y as red circles
##pl.plot(x, y, 'ro--')
### show the plot on the screen
##pl.show()


# lineplotFigLegend.py
import numpy as np
import pylab as pl
# Make x, y arrays for each graph
x_5000 = [7828.32580780983, 10810.881423711777, 18243.627557992935]
y_5000 = [250, 350, 600]

x_1000 = [1541.928147315979, 2436.4371016025543, 3640.2352323532104]
y_1000 = [250, 400, 600]
#x2 = [1, 2, 4, 6, 8]
#y2 = [2, 4, 8, 12, 16]

# use pylab to plot x and y : Give your plots names
plot_5000 = pl.plot(x_5000, y_5000, 'g--', label='5000 samples')
plot_5000_2 = pl.plot(x_5000, y_5000, 'rx')

plot_1000 = pl.plot(x_1000, y_1000, 'b--', label='1000 samples')
plot_1000_2 = pl.plot(x_1000, y_1000, 'rx')
#plot2 = pl.plot(x2, y2, 'go')
pl.title('Plot of SOM iteration vs. Time taken for clustering')
# make axis labels
pl.xlabel('Time (milliseconds)')
pl.ylabel('SOM iteration count')

# make legend
pl.legend(loc='lower right')
# show the plot on the screen
pl.show()

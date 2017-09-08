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
x_250 = [1541.928147315979, 4711.35699391, 7828.32580780983]
y_250 = [1000, 3000, 5000]

##x_400 = [2436.4371016025543, 21450.216341495514]
##y_400 = [1000, 5000]
##
##x_600 = [3640.2352323532104, 18243.627557992935]
##y_600 = [1000, 5000]


# use pylab to plot x and y : Give your plots names
plot_250 = pl.plot(x_250, y_250, 'g--', label='250 SOM iteration')
plot_250_2 = pl.plot(x_250, y_250, 'rx')

##plot_400 = pl.plot(x_400, y_400, 'b--', label='400 SOM iteration')
##plot_400_2 = pl.plot(x_400, y_400, 'rx')
##
##plot_600 = pl.plot(x_600, y_600, 'y--', label='400 SOM iteration')
##plot_600_2 = pl.plot(x_600, y_600, 'rx')

#plot2 = pl.plot(x2, y2, 'go')
pl.title('Plot of Sample size vs. Time taken for clustering')
# make axis labels
pl.xlabel('Time (milliseconds)')
pl.ylabel('Sample size')

# make legend
pl.legend(loc='lower right')
# show the plot on the screen
pl.show()

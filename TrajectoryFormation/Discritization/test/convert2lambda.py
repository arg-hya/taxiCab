import pycrs
import mpl_toolkits.basemap.pyproj as pyproj # Import the pyproj module
import shapefile as shp
import matplotlib.pyplot as plt

arr = []
with open("output.txt") as f:
    for line in f:
        # print line
        strings = line.split(" ")
        for strg in strings:
            if (strg != ''):
                arr.append(int(strg))
print(arr)
N = len(arr)
x = range(N)
width = 1/1.5
plt.bar(x, arr, width, color="blue")
#plt.xticks(x, order)
plt.ylabel('Order')
plt.title('Rechability Plot') 
plt.show()
#plt.plot(arr, 'ro')    

plt.show()


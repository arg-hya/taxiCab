import json
import shapefile as shp
import matplotlib.pyplot as plt
import random

def mean(numbers):
    return float(sum(numbers)) / max(len(numbers), 1)


numbersX = []  
numbersY = []  

TaskPoints = {}

shpFilePath = r"taxi_zones\taxi_zones"  


sf = shp.Reader(shpFilePath)
records = sf.records()

plt.figure()
for shape in sf.shapeRecords():
    #print(records[0][3])
    x = [i[0] for i in shape.shape.points[:]]
    meanX = mean(x)
    numbersX.append(meanX)  
    y = [i[1] for i in shape.shape.points[:]]
    meanY = mean(y)
    numbersY.append(meanY)
    plt.plot(x,y)
    
num = 0 ##range(263)
for x, y in zip(numbersX, numbersY):
    plt.text(x, y, str(num), color="red", fontsize=12)
    num = num + 1
    
plt.plot(numbersX, numbersY, 'o', color='blue', markersize=7, markeredgewidth=0.0)    
#print (len(numbersX))
#print (numbersY)
plt.show()


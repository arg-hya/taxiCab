import json
import shapefile as shp
import matplotlib.pyplot as plt
import random

def mean(numbers):
    return float(sum(numbers)) / max(len(numbers), 1)


numbersX = []  
numbersY = []  

TaskPoints = {}

shpFilePath = r"D:\TaxiCab\mycode\Plots\ShapefileAndTrajectory\taxi_zones\taxi_zones"  


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

Date_min = 1
Date_max = 30
Beta_min = 2
Beta_max = 30
#print (range(len(numbersX)))
for i in range(len(numbersX)):
    date = "2017/1/"
    TaskPoints_trace = []
    TaskPoints_trace.append(records[i][3])
    TaskPoints_trace.append(numbersX[i])
    TaskPoints_trace.append(numbersY[i])
    TaskPoints_trace.append(random.randint(Beta_min, Beta_max))
    date += str(random.randint(Date_min, Date_max))
    TaskPoints_trace.append(date)
    TaskPoints[i] = TaskPoints_trace

json.dump(TaskPoints, open('Data1/TaxiZone_TaskPoints.json', 'w'), indent=4, sort_keys=True, separators=(',', ':'))



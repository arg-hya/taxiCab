import json
import shapefile as shp
import matplotlib.pyplot as plt
import random

def mean(numbers):
    return float(sum(numbers)) / max(len(numbers), 1)

def WriteNodePoints(sorted_lat,sorted_lon) :
    target = open(r"NodePoints.data",'w')
    for i in range(len(sorted_lat)):
        target.write("%s,%s" % (str(sorted_lat[i]),str(sorted_lon[i])))
        target.write("\n")
    target.close()

if __name__ == "__main__":
        
    numbersX = []  
    numbersY = []  

    TaskPoints = {}

    shpFilePath = "..\\taxi_zones\\taxi_zones"  


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
        

    plt.plot(numbersX, numbersY, 'o', color='blue', markersize=7, markeredgewidth=0.0)    
    #print (len(numbersX))
    #print (numbersY)
    plt.show() 

    WriteNodePoints(numbersX,numbersY)
    

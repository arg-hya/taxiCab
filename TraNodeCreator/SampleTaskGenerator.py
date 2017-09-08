import json
import shapefile as shp
import matplotlib.pyplot as plt
import random

def mean(numbers):
    return float(sum(numbers)) / max(len(numbers), 1)


numbersX = []  
numbersY = []  

shpFilePath = "Data1\\taxi_zones"  


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

epoch_min = 0
epoch_max = 720

target = open(r"TestTask.data",'w') 
target.write("Total count of epoch = %s" % (epoch_max))
for i in range(len(numbersX)):
    target.write("\n")
    rand_epoch = random.randint(epoch_min + 1, epoch_max - 1)
    target.write("%s,%s" % (str(numbersX[i]),str(numbersY[i])))
    target.write(",%s,%s" % ("0",str(rand_epoch)))
   
target.close()

target = open(r"SpecifiedTasks.data",'w') 
target.write("Total count of epoch = %s" % (epoch_max))
for i in range(len(numbersX)):
    target.write("\n")
    rand_epoch = random.randint(epoch_min + 1, epoch_max - 1)
    target.write("%s,%s" % (str(numbersX[i]),str(numbersY[i])))
    target.write(",%s,%s" % ("0",str(rand_epoch)))
target.close()

import numpy as np
import pycrs
import mpl_toolkits.basemap.pyproj as pyproj # Import the pyproj module
import shapefile as shp
import matplotlib.pyplot as plt

REF_LAT = 900000
REF_LON = 120000

def sortPoints(lat,lon,sorted_lat,sorted_lon) :

    #Appending 0,0 for unspecified points
    sorted_lat.append(0)
    sorted_lon.append(0)
    
    numPoints = len(lat)

    for i in range(numPoints):
        minlat = lat[0]
        minlon = lon[0]

        min_dist = (minlat - REF_LAT)**2 + (minlon - REF_LON)**2
        index = 0
        for j in range(1, len(lat)):
            dist = (lat[j] - REF_LAT)**2 + (lon[j] - REF_LON)**2
            if (min_dist > dist):
                dist = min_dist
                index = j
        #print("%f %f %f" %(lat[index],lon[index],min_dist))
        sorted_lat.append(lat[index])
        sorted_lon.append(lon[index])
        del lat[index]
        del lon[index]

    #print sorted co-ordinates

def WriteNodePoints(sorted_lat,sorted_lon) :
    target = open(r"SortedNodePoints.data",'w')
    for i in range(len(sorted_lat)):
        target.write("%s,%s" % (str(sorted_lat[i]),str(sorted_lon[i])))
        target.write("\n")
    target.close()

def PopulateNodePoints(lat,lon) :
    with open(r"NodePoints.data") as f:
         #next(f)
         for line in f:
             strings = line.split(",")
             for i in range(0,len(strings),2):
                 co1 = float(strings[i])
                 co2 = float(strings[i+1])
                 lat.append(co1)
                 lon.append(co2)


def GetNopePoint(lat_temp,lon_temp) :
    min_dist = 0
    indx = 0
    for i in range(len(sorted_lat)):
        dist = (sorted_lat[i] - lat_temp) ** 2 + (sorted_lon[i] - lon_temp) ** 2
        if (min_dist > dist) or (i == 0):
            min_dist = dist
            indx = i
    return indx
    


if __name__ == "__main__":

    lat = []
    lon = []
    sorted_lat = []
    sorted_lon = []
    PopulateNodePoints(lat,lon)
    ind = 0

   # print(lat)
   # print(lon)

    sortPoints(lat,lon,sorted_lat,sorted_lon)

    WriteNodePoints(sorted_lat,sorted_lon)
    
    target = open(r"AllTrajecsNopePoints.data",'w')  
##    target.write(r"1")
##    target.write("\n")
##    target.write("5000")
##    target.write("\n")
	
    with open(r"..\TrajectoryFormation\Output\Sampled_Trajecs\AllTrajecs.data") as f:
        next(f)
        for line in f:            
            strings = line.split(",")
            point_list = []
            for i in range(0,len(strings),2):                
                co1 = float(strings[i])                
                co2 = float(strings[i+1])
##                if(co1 == 0) or (co2 == 0):
##                    continue
                point = GetNopePoint(co1,co2)
                point_list.append(point)
##                point_list.append(i)
            #target.write("%s " % str(ind))
            #target.write("%s " % str(len(point_list)))
            for index , k in enumerate(point_list):
                target.write("%s" % str(k))
                if index != len(point_list) - 1:
                    target.write(" ")
            if ind % 100 == 0 :
                print (ind)
            ind = ind + 1
                
            target.write("\n")
            
    target.close()

import numpy as np
import pycrs
import mpl_toolkits.basemap.pyproj as pyproj # Import the pyproj module
import shapefile as shp
import matplotlib.pyplot as plt


def PopulateNodePoints(lat,lon) :
    with open(r"NodePoints.data") as f:
         next(f)
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
    for i in range(len(lat)):
        dist = (lat[i] - lat_temp) ** 2 + (lon[i] - lon_temp) ** 2
        if (min_dist > dist) or (i == 0):
            min_dist = dist
            indx = i
    return indx
    


if __name__ == "__main__":

    lat = []
    lon = []
    PopulateNodePoints(lat,lon)
    ind = 0

    print(lat)
    print(lon)
    
    target = open(r"AllTrajecsNopePoints.data",'w')  
##    target.write(r"1")
##    target.write("\n")
##    target.write("5000")
##    target.write("\n")
	
    with open(r"AllTrajecs.data") as f:
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
            print (ind)
            ind = ind + 1
                
            target.write("\n")
            
    target.close()

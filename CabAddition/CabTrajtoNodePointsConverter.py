import numpy as np
import pycrs
import mpl_toolkits.basemap.pyproj as pyproj # Import the pyproj module
import shapefile as shp
import matplotlib.pyplot as plt
import os


def PopulateNodePoints(lat,lon,nodepoints_path) :
    with open(nodepoints_path) as f:
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
    point_list = []

    Path = os.path.dirname(os.path.abspath(__file__))
    Path = Path + r"\Data"
    print (Path)
    cab_nodepoints_path = Path + r"\2013000001_nodepoints.traj"
    cab_sampled_path = Path + r"\2013000001_sampled.traj"
    nodepoints_path = Path + r"\NodePoints.data"
    print (cab_nodepoints_path)


    PopulateNodePoints(lat,lon,nodepoints_path)
    target = open(cab_nodepoints_path,'w')
    
    with open(cab_sampled_path) as f:
        for line in f:
            line = line.rstrip()
            strings = line.split(" ")
            co1 = float(strings[0])                
            co2 = float(strings[1])           
            point = GetNopePoint(co1,co2)
            point_list.append(point)
            
    print(point_list)
    for index , k in enumerate(point_list):
        target.write("%s" % str(k))
        target.write("\n")


            
    target.close()

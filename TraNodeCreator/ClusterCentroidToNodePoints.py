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

    target = open(r"FinalClustersNopePoints.data",'w')  

    Convert = 0
    header_skip = 4
    with open(r"FinalClusters.data") as f:
        for line in f:
            if header_skip > 0 :
                Convert = 0
                header_skip = header_skip - 1
               
            if Convert == 1:
                Convert = 0
                line = line.rstrip()
                strings = line.split(" ")
                point_list = []
                for i in range(0,len(strings),2):                
                    co1 = float(strings[i])                
                    co2 = float(strings[i+1])
                    #print(co2)
                    point = GetNopePoint(co1,co2)
                    point_list.append(point)
                
                for index , k in enumerate(point_list):
                    target.write("%s" % str(k))
                    if index != len(point_list) - 1:
                        target.write(" ")
                target.write("\n")

            else:
                target.write(line)
                #target.write("\n")
                Convert = 1


            
    target.close()

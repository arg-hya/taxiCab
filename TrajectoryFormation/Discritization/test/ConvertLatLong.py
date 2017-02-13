import numpy as np
import pycrs
import mpl_toolkits.basemap.pyproj as pyproj # Import the pyproj module
import shapefile as shp
import matplotlib.pyplot as plt

shpFilePath = r"D:\TaxiCab\mycode\python\taxi_zones\taxi_zones"

sf = shp.Reader(shpFilePath)
records = sf.records()

plt.figure()
for shape in sf.shapeRecords():
    x = [i[0] for i in shape.shape.points[:]]
    y = [i[1] for i in shape.shape.points[:]]
    plt.plot(x,y)

projobj = pycrs.loader.from_file(r'D:\TaxiCab\mycode\python\taxi_zones\taxi_zones.prj')
proj4string = projobj.to_proj4()
print(proj4string)

isn2004=pyproj.Proj(proj4string, preserve_units=True)

wgs84=pyproj.Proj("+init=EPSG:4326")


if __name__ == "__main__":

    target = open("AllTrajecsConverted.data",'w')
    target.write(r"Cab ID:     <<Trajectory >>")
    target.write("\n")
    
    with open("AllTrajecs.data") as f:
        next(f)
        for line in f:            
            strings = line.split(",")
            indx = 0
            for i in range(int(len(strings)/2)):
                co1 = float(strings[indx])
                co2 = float(strings[indx+1])
                indx += 1
                x2,y2 = pyproj.transform(wgs84,isn2004 ,co1,co2)
                if (i != 0):
                    target.write(",")
                target.write(str(x2))
                target.write(",")
                target.write(str(y2))
                
            target.write("\n")
            
    target.close()

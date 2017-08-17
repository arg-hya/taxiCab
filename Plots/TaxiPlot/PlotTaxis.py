import pycrs
import mpl_toolkits.basemap.pyproj as pyproj # Import the pyproj module
import shapefile as shp
import matplotlib.pyplot as plt

shpFilePath = r"D:\TaxiCab\mycode\Plots\ShapefileAndTrajectory\taxi_zones\taxi_zones"

sf = shp.Reader(shpFilePath)
records = sf.records()

#plt.figure()
for shape in sf.shapeRecords():
    x = [i[0] for i in shape.shape.points[:]]
    y = [i[1] for i in shape.shape.points[:]]
    plt.plot(x,y,color='black')


##projobj = pycrs.loader.from_file(r'D:\TaxiCab\mycode\Plots\ShapefileAndTrajectory\taxi_zones\taxi_zones.prj')
##proj4string = projobj.to_proj4()
##print(proj4string)
##
##isn2004=pyproj.Proj(proj4string, preserve_units=True)
##
##wgs84=pyproj.Proj("+init=EPSG:4326")
i = 0
lat = []
lon = []


with open("2013000356_trajectory.traj") as f:
    #next(f)
    for line in f:
        i += 1

        # print line
        strings = line.split(",")
        co1 = float(strings[2])
        co2 = float(strings[3])
        #x2,y2 = pyproj.transform(wgs84,isn2004 ,co1,co2)
        lat.append(co1)
        lon.append(co2)
		   
x1 = lat
y1 = lon
plt.plot(x1, y1, 'o', color='blue', markersize=3, markeredgewidth=0.0)    

with open("2013001991_trajectory.traj") as f:
    #next(f)
    for line in f:
        i += 1

        # print line
        strings = line.split(",")
        co1 = float(strings[2])
        co2 = float(strings[3])
        #x2,y2 = pyproj.transform(wgs84,isn2004 ,co1,co2)
        lat.append(co1)
        lon.append(co2)
		   
x1 = lat
y1 = lon
plt.plot(x1, y1, 'o', color='red', markersize=3, markeredgewidth=0.0)    

with open("2013000201_trajectory.traj") as f:
    #next(f)
    for line in f:
        i += 1

        # print line
        strings = line.split(",")
        co1 = float(strings[2])
        co2 = float(strings[3])
        #x2,y2 = pyproj.transform(wgs84,isn2004 ,co1,co2)
        lat.append(co1)
        lon.append(co2)
		   
x1 = lat
y1 = lon
plt.plot(x1, y1, 'o', color='green', markersize=2, markeredgewidth=0.0)    


plt.show()


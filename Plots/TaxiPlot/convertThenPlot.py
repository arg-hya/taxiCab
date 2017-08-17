import pycrs
import mpl_toolkits.basemap.pyproj as pyproj # Import the pyproj module
import shapefile as shp
import matplotlib.pyplot as plt

shpFilePath = r"D:\TaxiCab\mycode\Plots\ShapefileAndTrajectory\taxi_zones\taxi_zones"

sf = shp.Reader(shpFilePath)
records = sf.records()

plt.figure()
for shape in sf.shapeRecords():
    x = [i[0] for i in shape.shape.points[:]]
    y = [i[1] for i in shape.shape.points[:]]
    plt.plot(x,y)

projobj = pycrs.loader.from_file(r'D:\TaxiCab\mycode\Plots\ShapefileAndTrajectory\taxi_zones\taxi_zones.prj')
proj4string = projobj.to_proj4()
print(proj4string)

isn2004=pyproj.Proj(proj4string, preserve_units=True)

wgs84=pyproj.Proj("+init=EPSG:4326")
i = 0
lat = []
lon = []
#1 foot = 0.3048 meters
conv = 0.3048

with open("trip_data_1_next_trip_start_location.txt") as f:
    next(f)
    for line in f:
        i += 1

        # print line
        strings = line.split(",")
        co1 = float(strings[0])
        co2 = float(strings[1])
        x2,y2 = pyproj.transform(wgs84,isn2004 ,co1,co2)
        lat.append(x2)
        lon.append(y2)

      #  if i == 14450:
       #    break

        if i == 1169120:
           break		   
x1 = lat
y1 = lon
plt.plot(x1, y1, 'o', color='blue', markersize=7, markeredgewidth=0.0)    

plt.show()


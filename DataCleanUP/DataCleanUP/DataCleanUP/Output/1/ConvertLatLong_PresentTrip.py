import numpy as np
import pycrs
import mpl_toolkits.basemap.pyproj as pyproj # Import the pyproj module
import shapefile as shp
import matplotlib.pyplot as plt


projobj = pycrs.loader.from_file(r'..\..\..\..\..\taxi_zones\taxi_zones.prj')
proj4string = projobj.to_proj4()
print(proj4string)

isn2004=pyproj.Proj(proj4string, preserve_units=True)

wgs84=pyproj.Proj("+init=EPSG:4326")


if __name__ == "__main__":

    target = open("trip_data_1_present_trip_end_location_converted.txt",'w')
    target.write(r"converted_longitude,converted_latitude")
    target.write("\n")
    
    with open("trip_data_1_present_trip_end_location.txt") as f:
        next(f)
        for line in f:            
            strings = line.split(",")
            co1 = float(strings[0])
            co2 = float(strings[1])
            x2,y2 = pyproj.transform(wgs84,isn2004 ,co1,co2)
            target.write(str(x2))
            target.write(",")
            target.write(str(y2))
            target.write("\n")

            
    target.close()

# import simplekml

'''
Takes in a string e.g '3752.45N/12215.48W' and parses it to
latitude and longitude
'''
og_str = input('Enter a Lat and Long in degrees decimal minutes as one string: ')

#Split string into N and W
for i in range(len(og_str)):
    if og_str[i] == '/':
        middle = i

og_north = og_str[:middle-1]
og_west = og_str[(middle + 1):-1]
north = round((float(og_north) / 100), 2)
west = round((float(og_west) * -1 / 100), 2)
print(str(north) + ", " + str(west))

def updateKml(lat, longi):
    kml = simplekml.Kml()
    pnt = kml.newpoint(name="HAB", description = "STAC HAB-1", coords=[(lat, longi)])
    pnt.style.iconstyle.scale = 5  # Icon thrice as big
    pnt.style.iconstyle.icon.href = 'placemark_circle.png'
    pnt.lookat = simplekml.LookAt(gxaltitudemode=simplekml.GxAltitudeMode.relativetoseafloor,
                              latitude=lat, longitude=longi,
                              range=3000, heading=0, tilt=0)
    kml.save("balloonlocation.kml")

# updateKml(north, west)

# import simplekml

'''
Takes in a string e.g '37.8775N/-122.0375W' and parses it to
degrees, minutes, and seconds
'''
past = []
og_str = input('Enter a Latitude and Longitude as one string: ')

#Split string into N and W
for i in range(len(og_str)):
    if og_str[i] == '/':
        middle = i

og_north = og_str[:middle-1]
og_west = og_str[(middle + 1):-1]
north = float(og_north)
west = float(og_west)
print(north)
print(west)

#Find index in string of where decimal points are
def get_decimal_index(s):
    for i in range(len(s)):
        if s[i] == '.':
            return i

north_dec = get_decimal_index(og_north)
west_dec = get_decimal_index(og_west)

assert north_dec >= 2 and west_dec >= 2, "Error w/ index of decimal"

def get_dms(s, i):
    ''' Takes in a string of lat or long coords and the decimal index'''
    seconds = float(s[i:]) * 60
    return s[:i-2], s[i-2:i], seconds

n_deg, n_min, n_sec = get_dms(og_north, north_dec)
w_deg, w_min, w_sec = get_dms(og_west, west_dec)

print(n_deg + " degrees, " + n_min + " mins, " + "{0:.2f}".format(n_sec) + " seconds N")
print(w_deg + " degrees, " + w_min + " mins, " + "{0:.2f}".format(w_sec) + " seconds W")

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
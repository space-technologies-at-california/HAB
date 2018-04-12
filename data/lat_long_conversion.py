import simplekml

'''
Takes in a string e.g '3752.45N/12215.48W' and parses it to
degrees, minutes, and seconds
'''

og_str = input('Enter a Latitude and Longitude as one string: ')

#Split string into N and W
for i in range(len(og_str)):
    if og_str[i] == '/':
        middle = i

og_north = og_str[:middle-1]
og_west = og_str[(middle + 1):-1]
print(og_north)
print(og_west)
north = float(og_north)
west = float(og_west[:-1])
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

def updateKml(lat, long):
	kml = simplekml.Kml()
	kml.newpoint(name="HAB", coords=[(north, west)])
	kml.save("balloonlocation.kml")
	return kml

updateKml(north, west)
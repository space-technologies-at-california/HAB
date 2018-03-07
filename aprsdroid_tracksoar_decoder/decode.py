import sys

def get_lat_dms_from_nmea(nmea):
    N_index = nmea.find("N")
    return nmea[:N_index]

def get_long_dms_from_nmea(nmea):
    slash_index = nmea.find("/")
    return nmea[slash_index+1:-1]

def dms_to_decimal(dms):
    minute = float(dms[-5:])
    degree = int(dms[:-5])
    return degree + minute / 60

def build_lat_long(lat, long):
    return str(lat) + " N, " + str(long) + " W"

def nmea_to_lat_long(nmea):
    return build_lat_long(dms_to_decimal(get_lat_dms_from_nmea(nmea)), dms_to_decimal(get_long_dms_from_nmea(nmea)))

def parse_line(line):
    start = line.find("h") + 1
    end = line.find("W", start)
    if(end == -1):
        print("Invalid coordinates")
        return 0
    nmea = line[start:end+1]
    return nmea
	
with open(sys.argv[1], "r") as f:
    for line in f:
        nmea = parse_line(line)
        if(nmea != 0):
            print(nmea_to_lat_long(nmea))
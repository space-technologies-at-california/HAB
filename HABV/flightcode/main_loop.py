import struct

def setmode(rf):  # writitng to pins depends on which lib we are using rcpy?
    digitalWrite(CTR1, LOW)
    digitalWrite(CTR2, LOW)

    if rf == 1:
        digitalWrite(CTR1, HIGH)

    elif rf == 2
        digitalWrite(CTR2, HIGH)

    elif rf == 3
        digitalWrite(CTR1, HIGH)
        digitalWrite(CTR2, HIGH)

def get_all_data():
    gpsData = getGPSData()
    altimeterData = getAltimeterData()
    thermocoupleData = getThermocoupleData()
    rtcData = getRTCData()
    imuData = getIMUData() # True for DPS values
    uvbData = getUVBData()
    return gpsData, altimeterData, thermocoupleData, rtcData, imuData, uvbData

def main():
    all_data = get_all_data()
    write_all_to_SD(all_data)

    # The data will be written to a dataString in this format:
    # <TripNumber>:<Hour>:<Minute>:<FixQuality>:<Speed>:<Angle>:<Lon>:<Lat>:<Altitude>:<ExternalTemp>
    datastring = str("202")
    for i in range(len(all_data)):
        datastring += ':' + str(all_data[i])
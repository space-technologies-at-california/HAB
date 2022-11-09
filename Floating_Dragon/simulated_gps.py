# File to read trajectory from CSV file and act as a gps sensor
import csv
import pandas as pd

class gps_sensor:
    def __init__(self, csv_file):
        self.df = pd.read_csv(csv_file, header=None)
        self.row = 0

    def read(self):
        lat = self.df.iloc[self.row][1]
        long = self.df.iloc[self.row][2]
        self.row += 1
        return lat, long
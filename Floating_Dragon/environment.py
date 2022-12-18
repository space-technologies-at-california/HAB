import math
import random


class WindEnv: #still have to do unit conversions

    def __init__(self, x, y, z, time, nodearea, nodemass): #environment is created right when node hits 20k feet and parafoil deploys
        self.refwind = [9906, 20.1]  # m, m/s
        self.printmode = False
        self.airdenslist = {0: 0.02166, 2268: 0.01866, 4536: 0.01600, 6804: 0.001362, 9072: 0.001155}  # kg/m^3 <-have to convert this to proper units
        self.terminalvelocity = 249
        self.nodearea = nodearea
        self.nodemass = nodemass
        self.timehistory = [time]    #all histories get intialized
        self.windhistory = [[0, 0, 0]]
        self.winddirhistory = [self.winddir()]
        self.velhistory = [[0, 0, self.terminalvelocity]] #m/s
        self.gpshistory = [[x , y, z]] # have to convert back to lat long m

    def update(self, xacc, yacc, zacc, x, y, z, time):  #returns the delta x y z
        self.winddirupd()
        self.windvelupd(z)
        self.nodevelupd(xacc, yacc, zacc, x, y, z, time)
        print("velhist", self.velhistory)
        if z % 2268 >= 1134:
            airdens = self.airdenslist[z + (2268 - z % 2268)]
        else:
            airdens = self.airdenslist[z - z % 2268]

        dflist = self.dragforce(airdens)
        wflist = self.windforce(airdens)
        flist = []

        deltatime = time - self.timehistory[-1]
        for i in range(3):
            if wflist[i] > 0:
                dflist[i] *= -1
            flist.append(wflist[i] + dflist[i])
            flist[i] = 0.5 * (flist[i]/self.nodemass) * deltatime ** 2
        self.timehistory.append(time)
        self.gpshistory.append([x, y, z])
        if self.printmode: #make a print mode to dsiplay
            pass
        return flist

    def windforce(self, airdens): #calculates wind load
        listwf = []
        for i in range(3):
            print("test1", self.windhistory[-1][i])
            listwf.append(0.5 * airdens * self.windhistory[-1][i] ** 2 * self.nodearea)
        return listwf

    def dragforce(self, airdens):  # calculates drag force
        listdf = []
        for i in range(3):
            print("test2" , self.velhistory[-1][i])
            listdf.append((1/2) * airdens * self.velhistory[-1][i] ** 2 * 1.05 * self.nodearea)
        return listdf

    def nodevelupd(self, xacc, yacc, zacc, x, y, z, time):  #gets new node velocity
        deltatime = time - self.timehistory[-1]
        xvel = self.velhistory[-1][0] + xacc * deltatime
        yvel = self.velhistory[-1][1] + yacc * deltatime
        zvel = self.velhistory[-1][2] + zacc * deltatime
       # print("test2", x, y, z, self.gpshistory[-1][0], self.gpshistory[-1][1], self.gpshistory[-1][2])
        #xvel2 = (x - self.gpshistory[-1][0]) * 111120/deltatime
        #yvel2 = (y - self.gpshistory[-1][1]) * 111120/deltatime
        #zvel2 = (z - self.gpshistory[-1][2])/deltatime
        #print("test", xvel2, yvel2, zvel2)
        #xvelf = 0.8 * xvel + 0.2 * xvel2
        #yvelf = 0.8 * yvel + 0.2 * yvel2
        #zvelf = 0.8 * zvel + 0.2 * zvel2

        self.velhistory.append([xvel, yvel, zvel])
        return [xvel, yvel, zvel]

    def windvelupd(self, alt):                    #randomly adjusts wind
        adjust1 = random.randint(-1,1) # feet and mph
        adjust2 = random.uniform(0, 2)
        self.refwind[1] = self.refwind[1] + adjust1 * adjust2 * self.refwind[1] + 20
        print(self.refwind[1])
        altwind = self.refwind[1] * (math.log(alt/0.01)) / math.log(self.refwind[0]/0.01)
        altwind = altwind + adjust1 * adjust2 * altwind
        self.refwind = [alt, altwind]

        windvel = []
        listxyz = self.winddirupd()
        for i in range(3):
            print("test3", altwind*math.sin(listxyz[i]*math.pi/180))
            windvel.append(altwind*math.sin(listxyz[i]*math.pi/180)) 
            # have to make a version that updates it instead of init
        self.windhistory.append(windvel)
        return windvel

    def winddir(self):    #randomly sets wind dir
        randx = random.randint(-90, 90)
        randy = random.randint(-90, 90)
        randz = random.randint(-25, 25)
        return [randx, randy, randz]

    def winddirupd(self):   #adjusts wind dir
        listxyz = self.winddirhistory[-1]
        listxyz[0] = listxyz[0] + random.randint(-10, 10)
        listxyz[1] = listxyz[1] + random.randint(-10, 10)
        testz = listxyz[2] +  random.randint(-3, 3)
        if -25 < testz < 25:
            listxyz[2] = testz

        self.winddirhistory.append(listxyz)
        return listxyz


import math
import random

class WindEnv: #still ahve to do unit conversions

    refwind = [9906, 20.1] # m, m/s
    velhistory = []
    windhistory = []
    winddirhistory = []
    timehistory = []
    gpshistory = []
    printmode = False

    airdenslist = {0:0.765, 5000:0.659,10000:0.565,15000:0.0481,20000:0.0408} #lbs/ft^3 <-have to convert this to proper units
    def __init__(self, xacc, yacc, zacc, x, y, z, time): #environment is created right when node hits 20k feet and parafoil deploys
        self.nodearea = placeholder1
        self.nodemass = placeholder2
        self.timehistory.append(time)     #all histories get intialized
        self.windhistory.append([0, 0, 0])
        self.winddirhistory.append(self.winddir())
        self.velhistory.append([0, terminalvelocity, 0]) #m/s
        self.gpshistory.append([x , y, z]) # have to convert back to lat long m

    def update(self, xacc, yacc, zacc, x, y, z, time):  #returns the delta x y z
        self.winddirupd()
        self.windvelupd(y)
        self.nodevelupd(xacc, yacc, zacc, x, y, z, time)

        if z % 5000 >= 2500:
            airdens = self.airdenslist[z + (5000 - z % 5000)]
        else:
            airdens = self.airdenslist[z - z % 5000]

        dflist = self.dragforce(airdens)
        wflist = self.windforce(airdens)
        flist = []

        deltatime = time - self.timehistory[-1]
        for i in range(3):
            if wflist[i] > 0:
                dflist[i] *= -1
            flist.append(wflist[i] + dflist)
            flist[i] = 0.5 * (flist[i]/self.nodemass) * deltatime ** 2
        self.timehistory.append(time)
        self.gpshistory.append([x, y, z])
        if self.printmode: #make a print mode to dsiplay
            pass
        return flist

    def windforce(self, airdens): #calculates wind load
        listwf = []
        for i in range(3):
            listwf.append(0.5 * airdens * self.windhistory[-1][i] ** 2 * self.nodearea)
        return listwf

    def dragforce(self, airdens):  # calculates drag force
        listdf = []
        for i in range(3):
            listdf.append((1/2) * airdens * self.velhistory[-1][i] ** 2 * 1.05 * self.nodearea)
        return listdf



    def nodevelupd(self, xacc, yacc, zacc, x, y, z, time):  #gets new node velocity
        deltatime = time - self.timehistory[-1]
        xvel = self.velhistory[-1][0] + xacc * deltatime
        yvel = self.velhistory[-1][1] + yacc * deltatime
        zvel = self.velhistory[-1][2] + zacc * deltatime

        xvel2 = (x - self.gpshistory[-1][0]) * 111120/deltatime
        yvel2 = (y - self.gpshistory[-1][1]) * 111120/deltatime
        zvel2 = (z - self.gpshistory[-1][2])/deltatime

        xvelf = 0.8 * xvel + 0.2 * xvel2
        yvelf = 0.8 * yvel + 0.2 * yvel2
        zvelf = 0.8 * z888vel + 0.2 * zvel2

        self.velhistory.append([xvelf, yvelf, zvelf])
        return [xvelf, yvelf, zvelf]

    def windvelupd(self, alt):                    #randomly adjusts wind
        adjust1 = random.randint([-1,1]) # feet and mph
        adjust2 = random.random()
        self.refwind[1] = self.refwind[1] + adjust1 * adjust2 * self.refwind[1]

        altwind = self.refwind[1] * (math.log(alt/0.01)) / math.log(self.refwind[0]/0.01)
        altwind = altwind + adjust1 * adjust2 * altwind
        self.refwind = [alt, altwind]

        windvel = []
        listxyz = self.winddirupd()
        for i in range(3):
            windvel.append(altwind*math.sin(listxyz[i]*math.pi/180)) # have to make a version that updates it instead of init
        self.windhistory.append(windvel)
        return windvel

    def winddir(self):    #randomly sets wind dir
        randx = random.randint([-90, 90])
        randy = random.randint([-90, 90])
        randz = random.randint([-25, 25])
        return [randx, randy, randz]

    def winddirupd(self):   #adjusts wind dir
        listxyz = self.winddirhistory[-1]
        listxyz[0] = listxyz[0] + random.randint([-10, 10])
        listxyz[1] = listxyz[1] + random.randint([-10, 10])
        testz = listxyz[2] +  random.randint([-3, 3])
        if testz > -25 and testz < 25:
            listxyz[2] = testz

        self.winddirhistory.append(listxyz)
        return listxyz
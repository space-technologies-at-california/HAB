

class TrajectoryGenerator:
    def __init__(self, target, tolerance, dist_thresh, alt_cutoff):
        self.phase = 0
        self.target = target  #(lat, lon, alt)
        self.error = 0.0
        self.tolerance = tolerance
        self.dist_to_tar = 0.0
        self.dist_thresh = dist_thresh  # To determine when to start spiral
        self.alt_cut = alt_cutoff
        self.tar_bearing = self.bearing_calc(target)
        self.tar_radius = 0

    def run(self, curr_pos):
        self.det_phase(curr_pos)

        if self.phase == 0:
            pass
        elif self.phase == 1:
            curr_bearing = self.bearing_calc(curr_pos)
            self.error = curr_bearing - self.tar_bearing
        elif self.phase == 2:
            pass
        else:
            pass

        if self.error > self.tolerance:
            self.generate_path(curr_pos)
        else:
            pass

    def fetch_output(self):
        return self.error

    def det_phase(self, curr_pos):
        if self.phase == 0:
            if curr_pos[2] <= self.alt_cut[0]:
                self.phase = 1

        elif self.phase == 1:
            if (self.dist_to_tar <= self.dist_thresh) or curr_pos[2] <= self.alt_cut[1]:
                self.phase = 2

        elif self.phase == 2:
            if curr_pos[2] <= self.alt_cut[2]:
                self.phase = 3

        self.error = 0.0
        self.dist_to_tar = 0.0


    def bearing_calc(self, curr_pos):
        bearing = curr_pos - self.target  # TODO Fix this. Only as a place holder

        return bearing

    def radius_calc(self, curr_pos):
        pass

    def generate_path(self, curr_pos):  # generates path based on phase, called at the start of phase and whenever we regen path
        if self.phase == 0:
            pass
        elif self.phase == 1:
            pass
        elif self.phase == 2:
            pass
        else:
            pass
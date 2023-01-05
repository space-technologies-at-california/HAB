import numpy as np

class TrajGen: 
  """
  Attributes:
    phase (int): Current phase
    tar_point (np.array): Target position vector [lat, long, alt]      
    alt_thresh_a (float): Altitude threshold to start phase 1
    alt_thresh_b (float): Altitude threshold to start phase 3
    dist_thresh (float): Distance from target threshold to start phase 2
    ph_1 (dict): Phase 1 working data
                 {
                    "err_thresh" (float): Error threshold for trajectory 
                                          regeneration (in radians)
                    "dir_vec" (np.array): Direction vector to "ep" [lat, long]
                    "ep" (np.array): Phase endpoint [lat, long]
                    "hplane" (dict): {"a": float, "b": float, "c": float} 
                                      Defines hyperplane a[lat] + b[long] + c 
                                      = 0 to determine turning direction
                 }
    ph_2 (dict): Phase 2 working data
                 {
                    "err_thresh" (float): Error threshold for trajectory 
                                          regeneration (in meters)
                    "center" (np.array): Center of rotation [lat, long]
                    "radius" (float): Rotation radius
                 }
    ph_3 (dict): Phase 3 working data
                 {
                    "err_thresh_v" (float): Vertical error threshold for 
                                            trajectory regeneration (in radians)
                    "err_thresh_h" (float): Horizontal error threshold for 
                                            trajectory regeneration (in radians)                          
                    "dir_vec" (np.array): Direction vector to target [lat, long]     
                    "hplane" (dict): {"a": float, "b": float, "c": float} 
                                      Defines hyperplane a[lat] + b[long] + c 
                                      = 0 to determine turning direction
                    "ref_flight_ang" (float): Descent flight angle
                 }
  """   
  def __init__(self, tar, alt_threshs, dist_thresh, err_threshs, ph_2_radius):
    """
    Initializes a new TrajGen with the passed in altitude, distance,and error 
    thresholds and phase working variables set appropriately. TrajGen operates 
    on points that are implemented using numpy arrays, taking on the form 
    [lat, long, alt]. 
     
    Args: 
      tar (dict): {"lat": float, "long": float, "alt": float}
      alt_threshs (dict): {"a": float, "b", float} for thresh a and thresh b
      dist_thresh (float): Distance from target threshold to start phase 2
      error_thresh (dict): {"1": float, "2": float, "3v": float, "3h": float}
    """
    self.phase = 0                            
    self.tar_point = np.array([tar["lat"], tar["long"], tar["alt"]])
    self.curr_point = None # This is continually set in update(). 
    self.alt_thresh_a = alt_threshs["a"]                           
    self.alt_thresh_b = alt_threshs["b"]                           
    self.dist_thresh = dist_thresh
    self.ph_1 = {"err_thresh": err_threshs["1"]}
    self.ph_2 = {
                  "err_thresh": err_threshs["2"], 
                  "radius": ph_2_radius
                }
    self.ph_3 = {
                  "err_thresh_v": err_threshs["3v"], 
                  "err_thresh_h": err_threshs["3h"],
                }
    # The rest of the phase state variables are added when needed.
    
  def vec_2(p_1, p_2, dim=2):
    """
    Returns a direction vector from p1 to p2 as well as the distance between 
    these points. In most cases, we only want to consider directionality in 
    two-dimensions (ignoring altitude), but there are three-dimensional cases.
    
    Args:
      p1 (np.array): An initial point
      p2 (np.array): A target point
      dim (int, optional): Dimensions wanting to be considered. Defaults to 2

    Returns:
      dir_vec_uv (np.array): Direction vector between p1 and p2
      dist (float): Distance between p1 and p2
    """
    if dim == 2:
      p_1 = p_1[:2]
      p_2 = p_2[:2] 
    dir_vec = p_2 - p_1
    dist = np.linalg.norm(dir_vec)
    dir_vec_uv = dir_vec / dist
    return dir_vec_uv, dist
              
  def update(self, curr_state):
    """
    Takes in the current state and returns the appropriate error value to 
    maintain correct trajectroy as well as the current phase in order to select 
    the required controller. 
    
    Args:
      curr_state (dict): {"lat": float, "long": float, "alt": float}
        
    Returns:
      phase (int): Current phase to determine which controller to use
      err (float or tuple of float): PID error for next iteration. In the case 
                                     of phase 3, there are two error terms for 
                                     vertical and horizontal control
    """
    curr_lat = curr_state["lat"]
    curr_long = curr_state["long"]
    curr_alt = curr_state["alt"]
    self.curr_point = np.array([curr_lat, curr_long, curr_alt])
    
    if self.phase == 0:
      err = self.update_phase_0()
    elif self.phase == 1:
      err = self.update_phase_1()
    elif self.phase == 2:
      err = self.update_phase_2()
    elif self.phase == 3:
      err = self.update_phase_3()   # (vertical_error, horizontal_error)
    # Potentially add states 4 and 5...
    
    return self.phase, err
    
  def update_phase_0(self):
    """
    Processes the case where we are in phase 0. This involves determining 
    whether we are below the altitude threshold to start controlling by entering 
    phase 1.
    
    Returns:       
      err (float): PID error. None when we are freefalling and not controlling 
                   and the result of setup_phase_1 otherwise
    """
    if self.curr_point[2] < self.alt_thresh_a:
      return self.setup_phase_1() 
    err = None
    return err
    
  def setup_phase_1(self):
    """ 
    Sets up the working environment for phase 1 controls. This involves 
    finding an endpoint for the phase, a direction vector between the current
    point and the endpoint, and a hyperplane equation to determine which 
    direction to turn throughout the phase.  
      
    Returns:
      err (float): PID error. Angle difference, in radians, between the 
                   planned path and current path to the phase endpoint
    """
    self.phase = 1
    
    dir_2_ep, _ = TrajGen.vec_2(self.curr_point, self.tar_point)            
    # The endpoint is 1/2(dist_thresh) away from the target in the direction 
    # towards the current point. Ensures we hit the threshold to start phase 2.    
    ep = (-self.dist_thresh/2 * dir_2_ep) + self.tar_point[:2] 
    #Eq of line A(lat) + B(long) + C = 0 to figure turning orientation
    #a=y1−y2 , b=x2−x1, and c=x1y2−x2y1.
    a = self.curr_point[1] - ep[1]
    b = ep[0] - self.curr_point[0]
    c = (self.curr_point[0] * ep[1]) - (ep[0] * self.curr_point[1])
    
    self.ph_1["dir_vec"] = dir_2_ep
    self.ph_1["ep"] = ep
    self.ph_1["hplane"] = {"a": a, "b": b, "c": c}
    
    err = 0
    return err
  
  def update_phase_1(self):
    """
    Facilitates a phase 1 update. This includes determining whether to move 
    on to another phase, whether to reset phase trajectory, and the error for 
    the phase. 
    
    Returns:
      err (float): PID error. This is the angle measurement (in radians) or the 
                   result of setup_phase_3 or setup_phase_2 
    """
    if self.curr_point[2] < self.alt_thresh_b:
      return self.setup_phase_3()
    
    _, dist_2_tar = TrajGen.vec_2(self.curr_point, self.tar_point)            
    if dist_2_tar < self.dist_thresh:  
      return self.setup_phase_2()
    
    dir_to_ep, _ = TrajGen.vec_2(self.curr_point, self.ph_1["ep"])
    ph_dir_vec = self.ph_1["dir_vec"]
    err = np.arccos(np.clip(np.dot(dir_to_ep, ph_dir_vec), -1.0, 1.0))
    if err > self.ph_1["err_thresh"]:
      return self.setup_phase_1() # Regenerate phase 1
    a = self.ph_1["hplane"]["a"]
    b = self.ph_1["hplane"]["b"]
    c = self.ph_1["hplane"]["c"]
    h_value = a * self.curr_point[0] + b * self.curr_point[1] + c
    err = np.sign(h_value) * err # Negative angle is left turn
    return err
    
  def setup_phase_2(self):
    """
    Sets up the working environment for phase 2 controls. This involves finding 
    a center to circle around. 
    
    Returns:
      err (float): PID error. This will be an difference in radius measurement
    """
    self.phase = 2
    
    dir_to_tar, _ = TrajGen.vec_2(self.curr_point, self.tar_point)
    center = self.curr_point[:2] + (self.ph_2["radius"] * dir_to_tar)
    self.ph_2["center"] = center
    err = 0
    return err
    
  def update_phase_2(self):
    """
    Facilitates a phase 2 update. This includes determining whether to move 
    on to another phase, whether to reset phase trajectory, and the error for 
    the phase. 
    
    Returns:      
      err (float): PID error. This a difference in radius measurement or the 
                   result of setup_phase_3 or setup_phase_2.
    """
    if self.curr_point[2] < self.alt_thresh_b:
      return self.setup_phase_3()
    
    _, dist_to_tar = TrajGen.vec_2(self.curr_point, self.tar_point)
    if dist_to_tar > self.dist_thresh:
      return self.setup_phase_1()
   
    _, dist_to_center = TrajGen.vec_2(self.curr_point, self.ph_2["center"])
    err = self.ph_2["radius"] - dist_to_center
    if np.abs(err) > self.ph_2["err_thresh"]:
      return self.setup_phase_2()
    return err # Negative diff implies a left turn

  def setup_phase_3(self):
    """
    Sets up the working environment for phase 3 controls. This involves finding 
    a direction vector between the current point and the target point, a 
    hyperplane equation to determine which direction to turn throughout the 
    phase, and the flight angle to be maintained throughout the descent.
    
    Returns:                                     
      err_v (float): PID error. This is the difference between the current 
                     flight angle and the planned flight angle
      err_h (float): PID error. Angle difference, in radians, between the 
                     planned path and current path to the phase endpoint                     
    """ 
    self.phase = 3
      
    dir_vec, _ = TrajGen.vec_2(self.curr_point, self.tar_point)
    #Eq of line A(lat) + B(long) + C = 0 to figure turning orientation
    #a=y1−y2 , b=x2−x1 and c=x1y2−x2y1.  
    a = self.curr_point[1] - self.tar_point[1]
    b = self.tar_point[0] - self.curr_point[0]
    c = (self.curr_point[0] * self.tar_point[1]) \
        - (self.tar_point[0] * self.curr_point[1])  
    
    tar_alt = self.tar_point[2]
    gnd_point = np.array([self.curr_point[0], self.curr_point[1], tar_alt])
    gnd_vec, _ = TrajGen.vec_2(gnd_point, self.tar_point, 3)
    glide_slope, _ = TrajGen.vec_2(self.curr_point, self.tar_point, 3)
    flight_ang = np.arccos(np.clip(np.dot(gnd_vec, glide_slope), -1.0, 1.0))
    
    self.ph_3["dir_vec"] = dir_vec
    self.ph_3["hplane"] = {"a": a, "b": b, "c": c}
    self.ph_3["ref_flight_ang"] = flight_ang
      
    err_v = 0
    err_h = 0
    return err_v, err_h
  
  def update_phase_3(self): 
    """
    Facilitates a phase 3 update. This includes determining whether to reset 
    phase trajectory and both vertical and horizontal error for the phase
    the phase. 
    
    Returns:                                     
      err_v (float): PID error. This is the difference between the current 
                     flight angle and the planned flight angle
      err_h (float): PID error. Angle difference, in radians, between the 
                     planned path and current path to the phase endpoint                    
    """
    tar_alt = self.tar_point[2]
    gnd_point = np.array([self.curr_point[0], self.curr_point[1], tar_alt])
    gnd_vec, _ = TrajGen.vec_2(gnd_point, self.tar_point, 3)
    glide_slope, _ = TrajGen.vec_2(self.curr_point, self.tar_point, 3)
    flight_ang = np.arccos(np.clip(np.dot(gnd_vec, glide_slope), -1.0, 1.0))
    # Positive value means we are above where we should be. 
    err_v =  flight_ang - self.ph_3["ref_flight_ang"]
    if err_v > self.ph_3["err_thresh_v"]:
      return self.setup_phase_3()
  
    dir_2_tar, _ = TrajGen.vec_2(self.curr_point, self.tar_point)
    ph_dir_vec = self.ph_3["dir_vec"]
    err_h = np.arccos(np.clip(np.dot(dir_2_tar, ph_dir_vec), -1.0, 1.0))
    if err_h > self.ph_3["err_thresh_h"]:
      return self.setup_phase_3() # Regenerate phase 3
    
    a = self.ph_1["hplane"]["a"]
    b = self.ph_1["hplane"]["b"]
    c = self.ph_1["hplane"]["c"]
    h_value = a * self.curr_point[0] + b * self.curr_point[1] + c
   
    err_h = np.sign(h_value) * err_h # Negative angle is left turn
    
    return err_v, err_h
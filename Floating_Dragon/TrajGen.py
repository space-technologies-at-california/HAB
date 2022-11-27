import numpy as np
  
class TrajectoryGenerator:
    
  def __init__(self, tar_lat, tar_long, tar_alt, alt_thresh_a, alt_thresh_b, 
               alt_thresh_c, dist_thresh, p1_error_thresh, p2_error_thresh, 
               p2_radius, p3_v_error_thresh, p3_h_error_thresh):
    """
    Initializes a new TrajectoryGenerator with predetermined state variables and 
    altitude, distance, & error thresholds set appropriately. 
    TrajectoryGenerator operates on points (position vectors) that are 
    implemented using numpy arrays taking on the form 
    [latitude, longitude, altitude]. *We may want to turn this into a class 
    later*.
           
    Attributes:
      phase (int): Current phase
      tar_point (np.array): Vector representing [latitude, longitude, altitude]      
      alt_thresh_a (int): Altitude threshold to start phase 1
      alt_thresh_b (int): Altitude threshold to start phase 3
      alt_thresh_c (int): Altitude threshold to deploy parachute two in 
                          uncontrollable cases. 
      dist_thresh (int): Distance from target threshold to start phase 2
      phase_1 (dict): Phase 1 working data. Added to/modified as needed. 
                      {
                        "error_thresh" (int): Error threshold for regenenation 
                        "dir_vec" (np.array): Direction vector to phase endpoint
                        "ep" (np.array): Phase endpoint 
                        "hplane" (dict): {"a": int, "b": int, "c": int} Defines 
                                         hyperlane ax + by - c  = 0
                      }
      phase_2 (dict): Phase 2 working data. Added to/modified as needed.

      phase_3 (dict): Phase 3 working data. Added to/modified as needed. 
    """
    self.phase = 0                            
    self.tar_point = np.array([tar_lat, tar_long, tar_alt])
    self.curr_point = None # This is continually set in update. 
    self.alt_thresh_a = alt_thresh_a                              
    self.alt_thresh_b = alt_thresh_b
    self.alt_thresh_c = alt_thresh_c
    self.dist_thresh = dist_thresh
    self.phase_1 = {"error_thresh": p1_error_thresh}
    self.phase_2 = {"error_thresh": p2_error_thresh, "radius": p2_radius}
    self.phase_3 = {"ver_error_thresh": p3_v_error_thresh, 
                    "hor_error_thresh": p3_h_error_thresh,
                    "ver": True}
    
  def vec_2(self, p2, dim=2):
    """
    Returns a direction vector from the current point to a target point p2 as 
    well as the distance between these points. In most cases, we only want to 
    consider directionality in two-dimensions (ignoring altitude), but there 
    are three-dimensional cases.
    
    Args:
      p2 (np.array): A target point
      dim (int, optional): Dimensions wanting to be considered. Defaults to 2.

    Returns:
      dir_vec_uv (np.array): Direction vector between the current point and p2. 
      dist (int): Distance between current point and p2.
    """
    p1 = self.current_point
    if dim == 2:
      p1 = p1[:2] # only want lat ang long in [lat, long, alt]
      p2 = p2[:2]      
    dir_vec = p2 - p1
    dist = np.linalg.norm(dir_vec)
    dir_vec_uv = dir_vec / dist
    return dir_vec_uv, dist
              
  def update(self, curr_lat, curr_long, curr_alt):
    """
    Takes in the arguments representing the current state and 
    returns the appropriate setpoint and error for the PID controller as well 
    as the current phase in order to select the required controller.
    
    Args:
      curr_lat (int): Current latitutude 
      curr_long (int): Current longitude 
      curr_alt (int): Current altitude
        
    Returns:
      phase (int): Current phase (to determine which controller to use)
      setpoint (int): PID setpoint for next iteration 
      error (int): PID error for next iteration 
    """
    self.curr_point = np.array([curr_lat, curr_long, curr_alt])
    
    if self.phase == 0:
      setpoint, error = self.update_phase_0()
    elif self.phase == 1:
      setpoint, error = self.update_phase_1()
    elif self.phase == 2:
      setpoint, error = self.update_phase_2()
    elif self.phase == 3:
      setpoint, error = self.update_phase_3()
    
    return self.phase, setpoint, error
    
  def update_phase_0(self):
    """
    Processes the case where we are in phase 0. This involves determining 
    whether we are below the altitude threshold to start controlling by entering 
    phase 1.
    
    Returns: 
      setpoint (int): PID setpoint. None as we freefall--not controlling yet 
      error (int): PID error. None as we freefall--not controlling yet 
    """
    if self.curr_point[2] <= self.alt_thresh_a:
      return self.setup_phase1() 
    return None, None
    
  def setup_phase_1(self):
    """ 
    Sets up the working environment for phase 1 controls. This involves 
    finding an endpoint for the phase, a direction vector between the current
    point and the endpoint, and a hyperplane equation in that direction 
    which is used to determine which direction to turn.  
      
    Returns:
      setpoint (int): PID setpoint. Defined as the angle between planned path 
                      and actual path to the phase endpoint. This is 0
      error (int): PID error. The actual angle measurment.
    """
    self.phase = 1
    dir_2_tar, _ = self.vec_2(self.target_point)            
    # The endpoint is 1/2(dist_thresh) away from the target in the direction 
    # towards the current point. Ensure we hit the threshold to start phase 2.    
    ep = (-self.dist_thresh/2 * dir_2_tar) + self.target_point 
    #Eq of line A(lat) + B(long) - C = 0 to figure turning orientation
    #a=y1−y2 , b=x2−x1, and c=x1y2−x2y1.  
    a = self.curr_point[1] - ep[1]
    b = ep[0] - self.curr_point[0]
    c = (self.curr_point[0] * ep[1]) - (self.curr_point[1] * ep[0])
    self.phase_1["dir_vec"] = dir_2_tar
    self.phase_1["ep"] = ep
    self.phase_1["hplane"] = {"a": a, "b": b, "c": c}
    return 0, 0
  
  def update_phase_1(self):
    """
    Facilitates a phase 1 update. This includes determining whether to reset or 
    move on to another phase as well as measuring the angle between the planned 
    path and actual path to the phase endpoint, which is our error. 
    
    Returns:
      setpoint (int): PID setpoint. Defined as the angle between the planned
                      path and actual path to the phase endpoint. This is 0
      error (int): PID error. This is the angle measurement 
    """
    if self.curr_point[2] <= self.alt_thresh_b:
      return self.setup_phase_3()
    
    _, dist_to_tar = self.vec_2(self.target)            
    if dist_to_tar <= self.dist_thresh:  
      return self.setup_phase_2()
    
    dir_to_ep, _ = self.vec_2(self.phase_1["endpoint"])
    
    angle = np.arccos(np.clip(np.dot(dir_to_ep, self.phase_1["ep"]), -1.0, 1.0))
    if angle > self.phase_1["error_thresh"]:
      return self.setup_phase_1() # Regenerate phase 1
    
    a = self.phase_1["hplane"]["a"]
    b = self.phase_1["hplane"]["b"]
    c = self.phase_1["hplane"]["c"]
    h_value = a * self.curr_point[0] + b * self.curr_point[1] - c
    # negative angle is left turn
    if self.curr_point[0] > self.phase_1["endpoint"][0] and h_value > 0:
      return 0, -angle 
    elif self.curr_point[0] > self.phase_1["endpoint"][0] and h_value < 0:
      return 0, angle
    elif self.curr_point[0] < self.phase_1["endpoint"][0] and h_value > 0:
      return 0, angle
    else:
      return 0, -angle # 0,0 when we are on the correct path. 
    
  def setup_phase_2(self):
    """
    Sets up the working environment for phase 2 controls. This involves finding 
    a center to spiral around. 
    
    Returns:
      setpoint (int): PID setpoint for next iteration. Defined as difference in 
                      wanted and actual radius--want this to be 0.
      error (int): PID error for next iteration. Will be an difference in radius 
                   measurement. Look at update_phase_2 for more details. 
    """
    self.phase = 2
    dir_to_tar, _ = self.vec_2(self.t)
    center = self.curr_point + (self.phase_2["radius"] * dir_to_tar)
    self.phase_2["center"] = center
    return 0, 0
    
  def update_phase_2(self):
    """
    Facilitates a phase 2 update. This includes determining whether to reset or 
    move on to another phase as well figuring out how far from the center we 
    are. If less than the radius that we want to circle at, we will turn right 
    in order to circle wider. The opposite is true if we are farther than the 
    radius. So long as we don't wait too long to update, this will force 
    circling behavior. 
    
    Returns:
      setpoint (int): PID setpoint for next iteration. PID setpoint for next 
                      iteration. Defined as difference in wanted and actual 
                      radius--want this to be 0.
      error (int): PID error for next iteration. This is an radius measurement. 
    """
    if self.curr_point[2] <= self.alt_thresh_b:
      return self.setup_phase_3()
    _, dist_to_tar = self.vec_2(self.tar_point)
    if dist_to_tar >= self.dist_thresh:
      return self.setup_phase_1()
    _, dist_to_center = self.vec_2(self.phase_2["center"])
    if dist_to_center > self.phase_2["error"]:
      return self.setup_phase_2()
    diff = dist_to_center - self.phase_2["error_thresh"]
    return 0, diff #negative implies a right turn

  def setup_phase_3(self):
    """
    Sets up the working environment for phase 3 controls. This involves finding 
    a direction vector representing our glide slope as well as defining a 
    hyperplane to determine horizonal positioning. We will have two sets of 
    alternating controller values, one for horizontal control and one for 
    vertical control
    
    Returns:
      setpoint (int): PID setpoint for next iteration. In both cases this is 0. 
                      We define the setpoint to be the difference between the 
                      wanted values and the actual values (altitude difference
                      in the case of vertical control and difference in path 
                      angle for horizontal control).                                   
      error (int): PID error for next iteration. Will be an difference in 
                   altitude or path angle. Look at update_phase_3 for more 
                   details.     
    """
    self.phase = 3
    dim = 3
    glide_slope, _ = self.vec_2(self.target, dim)
    glide_slope_dir = glide_slope[:2]
    #Eq of line A(lat) + B(long) - C = 0 to figure turning orientation
    #a=y1−y2 , b=x2−x1 and c=x1y2−x2y1.  
    a = self.curr_point[1] - self.tar_point[1]
    b = self.tar_point[0] - self.curr_point[0]
    c = (self.curr_point[0] * self.targ[1]) - (self.curr_point[1] * self.tar_point[0])  
    self.phase_3["dir_vec"] = glide_slope_dir
    self.phase_3["hplane"] = {"a": a, "b": b, "c": c}
    self.phase_3["sp"] = self.curr_point
    self.phase_3["ver"] = True
    return 0, 0
  
  def update_phase_3(self): 
    """
    Facilitates a phase 3 update. This includes determining whether to reset the 
    trajectory as well figuring out how the difference in altitude or difference 
    in path angle depending on what is being controlled in the current iteration.
  
    Returns:
      setpoint (int): PID setpoint for next iteration. In both cases this is 0. 
                      We define the setpoint to be the difference between the 
                      wanted values and the actual values (altitude difference
                      in the case of vertical control and difference in path 
                      angle for horizontal control).                                   
      error (int): PID error for next iteration. Will be an difference in 
                   altitude or path angle. Look at update_phase_3 for more 
                   details.   
    """
    hor = self.phase_3["ver"]
    self.phase_3["ver"] = not self.phase_3["ver"]
    if hor:
      # Project the current point onto the glide scope. We can use this to 
      # determing what the current altitude should be, finding a difference. 
      curr_2_start, _ = self.vec_2(self.phase_3["sp"])
      start_2_curr = -curr_2_start
      projection_dist = np.dot(start_2_curr, self.phase_3["dir_vec"])
      projection = self.phase["sp"] + (projection_dist * self.phase_3["dir_vec"])
      req_height = projection[2]
      curr_height = self.curr_point[2]
      diff = curr_height - req_height
      if diff > self.phase_3["hor_error_thresh"]:
        return self.setup_phase_3()  
      return 0, diff #neg means we need to descend less quickly
    else:  
      dir_to_tar, _ = self.vec_2(self.tar_point)                      
      angle = np.arccos(np.clip(np.dot(dir_to_tar, self.phase_3["dir_vec"]), -1.0, 1.0))      
      if angle > self.phase_3["ver_error_thresh"]:
        return self.setup_phase_3()        
      a = self.phase_3["hplane"]["a"]
      b = self.phase_3["hplane"]["b"]
      c = self.phase_3["hplane"]["c"]
      h_value = a * self.curr_point[0] + b * self.curr_point[1] - c
      # negative angle is left turn
      if self.curr_point[0] > self.tar_point[0] and h_value > 0:
        return 0, -angle 
      elif self.curr_point[0] > self.tar_point[0] and h_value < 0:
        return 0, angle
      elif self.curr_point[0] < self.tar_point[0] and h_value > 0:
        return 0, angle
      else:
        return 0, -angle # 0,0 when we are on the correct path.
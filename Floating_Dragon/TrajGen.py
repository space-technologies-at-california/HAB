import numpy as np
import math

class TrajectoryGenerator:
      
  def __init__(self, target, t_a, t_b, t_c, t_d, p1_e):
    self.phase = 0                    
    self.target = target    #dictionary w/ keys latitude, longitude
    self.alt_thresh_a = t_a                              
    self.alt_thresh_b = t_b  
    self.alt_thresh_c = t_c
    self.dist_thresh = t_d
    self.phase_1_data = {"error_thresh": p1_e}  #dictionary w/ data need throughout phase 1
    self.last_2_states = [None, None]
  
  #current_state is a dict w/ keys latitude, longitude, and altitude
  def update(self, current_state): 
    if self.phase == 0:
      setpoint, error = self.update_phase0(current_state)
    elif self.phase == 1:
      setpoint, error = self.update_phase1(current_state)
    elif self.phase == 2:
      setpoint, error = self.update_phase2(current_state)
    elif self.phase == 3:
      setpoint, error = self.update_phase3(current_state)
    elif self.phase == 4:
      setpoint, error = self.update_phase4(current_state)
    elif self.phase == 5:
      setpoint, error = self.update_phase5(current_state)
    
    self.last_2_states[0] = self.last_2_states[1]
    self.last_2_states[1] = current_state
    
    return {"setpoint": setpoint, "error": error}
  
  #current_state is a dict w/ keys latitude, longitude, and altitude
  def update_phase0(self, current_state):
    if current_state['altitude'] <= self.t_a: 
      setpoint, error = self.update_phase1(current_state)
      return setpoint, error
    else:
      None, None # An indication that to PID that we're not yet controlling
    
  def setup_phase1(self, current_state):
    vector_to_target = np.array([[self.target["latitude"] - current_state["latitude"], 
                                 self.target["longitude"] - current_state["longitude"]]])
    distance_to_target = np.linalg.norm(vector_to_target)
    
    if distance_to_target <= self.dist_thresh:
      setpoint, error = self.setup_phase2(current_state, )
      return setpoint, error

    self.phase = 1
    target_direction_uv = vector_to_target / np.linalg.norm(vector_to_target) 
    phase_1_endpoint = self.dist_thresh/2 * (-1 * target_direction_uv) + \
      np.array([[self.target["latitude"], current_state["latitude"]]])
    self.phase_1_data["path direction"] = target_direction_uv
    self.phase_1_data["endpoint"] = phase_1_endpoint
    return 0, 0 
    
  def update_phase1(self, current_state):
    vector_to_target = np.array([[self.target["latitude"] - current_state["latitude"], 
                                 self.target["longitude"] - current_state["longitude"]]])
    
    distance_to_target = np.linalg.norm(vector_to_target)
    
    if distance_to_target <= self.dist_thresh:
      setpoint, error = self.setup_phase2(current_state)
      return setpoint, error
    
    vector_to_target_uv = vector_to_target / np.linalg.norm(vector_to_target) 
    angle = np.arccos(np.clip(np.dot(vector_to_target_uv, self.phase_1_data["path direction"]), -1.0, 1.0))
    
    if angle > self.phase_1_data["error_thresh"]:
      setpoint, error = self.setup_phase1(current_state)
      return setpoint, error 

  
    
       

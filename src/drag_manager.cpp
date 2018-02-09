#include "drag_manager.hpp"

namespace drag_manager{

  bool stop_surface_drag(int touch_id, ActiveHits & active_hits){
    auto is_a_hit = active_hits.touches.find(touch_id);
    if( is_a_hit != active_hits.touches.end() ){
      active_hits.touches.erase(is_a_hit);
    }
    if(active_hits.touches.size() > 0){
      return true;
    }else{
      return false;
    }
  }

  bool stop_joints_drag(int touch_id, ActiveJoints & active_joints){
    auto is_a_hit = active_joints.touches.find(touch_id);
    return is_a_hit != active_joints.touches.end();
  }

};

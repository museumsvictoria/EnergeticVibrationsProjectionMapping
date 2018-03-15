#include "drag_manager.hpp"
#include <assert.h>

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


  // This pocess could be speed up by using a set - map combo
  // but theres only ever a few joints so it will be fast
  int current_joint_index(int touch_id, const ActiveJoints & active_joints) {
	  int index = -1;
	  for (auto const & aj : active_joints.touches) {
		  if (touch_id == aj.second) {
			  index = aj.first;
		  }
	  }
	  return index;
  }

};

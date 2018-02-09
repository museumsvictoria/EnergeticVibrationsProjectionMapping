#pragma once
#include <set>
#include <map>

namespace drag_manager{

  struct ActiveHits{
    std::set<int> touches;
  };

  struct ActiveJoints{
    std::map<int, int> touches;
  };

  bool stop_surface_drag(int, ActiveHits &);

  bool stop_joints_drag(int, ActiveJoints &);
  
};

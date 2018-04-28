//
//  multi_touch_test.cpp
//  UnitTests
//
//  Created by Tom Gowan on 9/2/18.
//

#include "catch.hpp"
#include "drag_manager.hpp"

using drag_manager::ActiveHits;
using drag_manager::ActiveJoints;
using drag_manager::stop_surface_drag;
using drag_manager::stop_joints_drag;

TEST_CASE("stop_surface_drag"){
  auto ah = ActiveHits();
  REQUIRE(stop_surface_drag( 1, ah ) == false);
  REQUIRE(ah.touches.size() == 0);
  ah.touches.insert(1);
  REQUIRE(stop_surface_drag( 1, ah ) == false);
  REQUIRE(ah.touches.size() == 0);
  ah.touches.insert(1);
  ah.touches.insert(2);
  REQUIRE(stop_surface_drag( 1, ah ) == true);
  REQUIRE( *ah.touches.begin() == 2 );
}

TEST_CASE("stop joints drag"){
  auto aj = ActiveJoints();
  REQUIRE(stop_joints_drag(1, aj) == false);
  aj.touches.insert(std::pair<int, int>(1, 0));
  REQUIRE(stop_joints_drag(1, aj) == true);
  REQUIRE(aj.touches.size() == 1);
}

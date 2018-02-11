#pragma once
#include <set>
#include <map>

namespace drag_manager {

	/*
	set of touches ids
	that are currently
	touching the selected surface
	*/
	struct ActiveHits {
		std::set<int> touches;
	};

	/*
	links between touches id and
	joint index
	<JointIndex, TouchID>
	*/
	struct ActiveJoints {
		std::map<int, int> touches;
	};

	/*
	Takes a touch id and ActiveHits
	if the touch id is in the ActiveHits
	it is removed.
	Returns
	true if touch id was in set
	*/
	bool stop_surface_drag(int touch_id, ActiveHits &);

	/*
	Takes a touch id and the ActiveJoints.
	if the touch id is in Active joints
		Returns: the index of the joint (from joints[] in ProjectionEditorWidget)
	otherwise
		Returns -1
	*/
	int current_joint_index(int touch_id, const ActiveJoints &);

};

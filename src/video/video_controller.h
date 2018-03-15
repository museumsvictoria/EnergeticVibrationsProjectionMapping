#pragma once
#include <string>
#include <ofUtils.h>

namespace video_controller {
	static constexpr auto VIDEO_PATH = "sources/videos";
	static constexpr int NUM_VIDEOS = 7;
	static constexpr int NUM_TYPES = 2;
	static constexpr char* FILE_TYPES[NUM_TYPES] = { {"mp4"}, {"mov"} };

	struct Loader {
		ofDirectory dir;
		size_t num_vids;
		int count;
		Loader() : dir(VIDEO_PATH), count(0){}
		bool has_next();
		std::string next();
	};

	Loader load();

};

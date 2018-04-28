#include "video_controller.h"

namespace video_controller {
	bool Loader::has_next() {
        return count < num_vids;
	}

	std::string Loader::next() {
		std::string path = "";
		if (has_next()) {
			path = std::string(VIDEO_PATH) + "/" + dir.getName(count);
			count++;
		}
		return path;
	}

	Loader load() {
		Loader l;
		for (int i = 0; i < NUM_TYPES; ++i) {
			l.dir.allowExt(FILE_TYPES[i]);
		}
		l.num_vids = l.dir.listDir();
		return l;
	}
};

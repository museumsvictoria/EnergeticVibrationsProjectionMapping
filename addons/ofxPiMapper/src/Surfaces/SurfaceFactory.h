#pragma once

#include "ofMain.h"
#include "BaseSurface.h"
#include "SurfaceType.h"
#include "TriangleSurface.h"
#include "QuadSurface.h"
#include "GridWarpSurface.h"
#include "HexagonSurface.h"

namespace ofx {
namespace piMapper {

// The surface factory singleton
class SurfaceFactory {
	public:
		static SurfaceFactory * instance();
	
		// Create new surface based on type
		BaseSurface * createSurface(SurfaceType type);
    
        //Josh Additions
        void init_defaults();
        float default_scale;
        ofVec2f default_pos;

		
    
	private:
		static SurfaceFactory * _instance;

		
	
		TriangleSurface * createTriangleSurface();
		QuadSurface * createQuadSurface();
		GridWarpSurface * createGridWarpSurface();
		HexagonSurface * createHexagonSurface();
	};

} // namespace piMapper
} // namespace ofx

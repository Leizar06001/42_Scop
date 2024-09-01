#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <scop.hpp>

bool loadOBJ(
	const char * path,
	std::vector<Vec3<float>> & out_trivertices,
	std::vector<Vec2<float>> & out_triuvs,
	std::vector<Vec3<float>> & out_trinormals,
    std::vector<Vec3<float>> & out_quadvertices,
	std::vector<Vec2<float>> & out_quaduvs,
	std::vector<Vec3<float>> & out_quadnormals
);

#endif

#include "objloader.hpp"

// Very, VERY simple OBJ loader.
// Here is a short list of features a real function would provide :
// - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
// - Animations & bones (includes bones weights)
// - Multiple UVs
// - All attributes should be optional, not "forced"
// - More stable. Change a line in the OBJ file and it crashes.
// - More secure. Change another line and you can inject code.
// - Loading from memory, stream, etc

bool loadOBJ(
	const char * path,
	std::vector<Vec3<float>> & out_trivertices,
	std::vector<Vec2<float>> & out_triuvs,
	std::vector<Vec3<float>> & out_trinormals,
    std::vector<Vec3<float>> & out_quadvertices,
	std::vector<Vec2<float>> & out_quaduvs,
	std::vector<Vec3<float>> & out_quadnormals
){
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> triVertexIndices, triUvIndices, triNormalIndices;
    std::vector<unsigned int> quadVertexIndices, quadUvIndices, quadNormalIndices;
	std::vector<Vec3<float>> temp_vertices;
	std::vector<Vec2<float>> temp_uvs;
	std::vector<Vec3<float>> temp_normals;

	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}
    int ret;
	int nb_faces = 0;

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if ( strcmp( lineHeader, "v" ) == 0 ){
			Vec3<float> vertex;
			ret = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);

		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			Vec2<float> uv;
			ret = fscanf(file, "%f %f\n", &uv.x, &uv.y );
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);

		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			Vec3<float> normal;
			ret = fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);

		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3, vertex4;
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
            char line[128];

            if (fgets(line, sizeof(line), file)) {
                int matches = sscanf(line, "%u/%u/%u %u/%u/%u %u/%u/%u\n",
                                        &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                        &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                        &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                if (matches == 9) {
					++nb_faces;
                    for(int i = 0; i < 3; i++) {
                        triVertexIndices.push_back(vertexIndex[i]);
                        triUvIndices    .push_back(uvIndex[i]);
                        triNormalIndices.push_back(normalIndex[i]);
                    }

                } else {
                    // Essayez de lire seulement les indices de vertex
                    matches = sscanf(line, "%u %u %u %u\n",
                        &vertexIndex[0], &vertexIndex[1], &vertexIndex[2], &vertexIndex[3]);

                    if (matches == 4) {
						++nb_faces;
                        // std::cout << "Quad" << std::endl;
                        // Cas avec seulement les indices de vertex
                        for(int i = 0; i < 4; i++) {
                            quadVertexIndices.push_back(vertexIndex[i]);
                            quadUvIndices    .push_back(-1);
                            quadNormalIndices.push_back(-1);
                        }

                    } else {

                        matches = sscanf(line, "%u %u %u\n",
                        &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);

                        if (matches == 3) {
							++nb_faces;
                            // std::cout << "Tri : ";
                            // Cas avec seulement les indices de vertex
                            for(int i = 0; i < 3; i++) {
                                // std::cout << vertexIndex[i] << " ";
                                triVertexIndices.push_back(vertexIndex[i]);
                                triUvIndices    .push_back(-1);
                                triNormalIndices.push_back(-1);
                            }
                            // std::cout << std::endl;

                        } else {
                            // Format non reconnu
                            printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                            return false;
                        }
                    }
                }
            }

		} else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			if (fgets(stupidBuffer, 1000, file)){
			}
		}
	}
    (void)ret;

	// For each vertex of each triangle
	for( unsigned int i=0; i < triVertexIndices.size(); i++ ){

		// Get the indices of its attributes
		int vertexIndex = triVertexIndices[i];
		int uvIndex = triUvIndices[i];
		int normalIndex = triNormalIndices[i];

		// Get the attributes thanks to the index
		Vec3<float> vertex = temp_vertices[ vertexIndex-1 ];
        Vec2<float> uv;
        Vec3<float> normal;
        if (uvIndex > 0) {
            uv = temp_uvs[ uvIndex-1 ];
        } else {
            uv = Vec2<float>(0, 0);
        }
        if (normalIndex > 0) {
            normal = temp_normals[ normalIndex-1 ];
        } else {
            normal = Vec3<float>(0, 0, 0);
        }
		// Vec2<float> uv = temp_uvs[ uvIndex-1 ];
		// Vec3<float> normal = temp_normals[ normalIndex-1 ];

		// Put the attributes in buffers
		out_trivertices.push_back(vertex);
		out_triuvs     .push_back(uv);
		out_trinormals .push_back(normal);
	}

    // For each vertex of each quads
	for( unsigned int i=0; i < quadVertexIndices.size(); i++ ){

		// Get the indices of its atquadbutes
		int vertexIndex = quadVertexIndices[i];
		int uvIndex = quadUvIndices[i];
		int normalIndex = quadNormalIndices[i];

		Vec3<float> vertex = temp_vertices[ vertexIndex-1 ];
        Vec2<float> uv;
        Vec3<float> normal;
        if (uvIndex > 0) {
            uv = temp_uvs[ uvIndex-1 ];
        } else {
            uv = Vec2<float>(0, 0);
        }
        if (normalIndex > 0) {
            normal = temp_normals[ normalIndex-1 ];
        } else {
            normal = Vec3<float>(0, 0, 0);
        }
		// Vec2<float> uv = temp_uvs[ uvIndex-1 ];
		// Vec3<float> normal = temp_normals[ normalIndex-1 ];

		// Put the atquadbutes in buffers
		out_quadvertices.push_back(vertex);
		out_quaduvs     .push_back(uv);
		out_quadnormals .push_back(normal);
	}

	std::cout << "Nb faces : " << nb_faces << std::endl;

	return true;
}

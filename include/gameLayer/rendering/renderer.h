#pragma once
#include "rendering/shader.h"
#include <vector>
#include "rendering/camera.h"
#include "rendering/skyBoxRenderer.h"
#include <gl2d/gl2d.h>

struct BlocksLoader;
struct ChunkSystem;

struct Renderer
{
	Shader defaultShader;
	GLint u_viewProjection = -1;
	GLint u_typesCount = -1;
	GLint u_positionInt = -1;
	GLint u_positionFloat = -1;
	GLint u_texture = -1;
	GLint u_time = -1;
	GLuint u_vertexData = GL_INVALID_INDEX;
	GLuint u_vertexUV = GL_INVALID_INDEX;
	GLuint u_textureSamplerers = GL_INVALID_INDEX;

	void create(BlocksLoader &blocksLoader);
	void updateDynamicBlocks();
	void render(std::vector<int> &data, Camera &c, gl2d::Texture &texture);

	void renderFromBakedData(ChunkSystem &chunkSystem, Camera &c, gl2d::Texture &texture);


	SkyBoxRenderer skyBoxRenderer;

	GLuint vao = 0;
	GLuint vertexBuffer = 0;
	GLuint vertexDataBuffer = 0;
	GLuint vertexUVBuffer = 0;
	GLuint textureSamplerersBuffer = 0;
	
};

struct GyzmosRenderer
{

	struct CubeData
	{
		int x=0, y=0, z=0;
	};

	void create();
	Shader gyzmosCubeShader;
	GLint u_viewProjection = -1;
	GLint u_positionInt = -1;
	GLint u_positionFloat = -1;
	GLuint vao = 0;
	GLuint vertexDataBuffer = 0;
	GLuint blockPositionBuffer = 0;
	GLuint cubeIndices = 0;

	std::vector<CubeData> cubes;

	void drawCube(int x, int y, int z) { cubes.push_back({x, y, z}); };
	void drawCube(glm::ivec3 pos) { drawCube(pos.x, pos.y, pos.z); };
	void render(Camera &c, glm::ivec3 posInt, glm::vec3 posFloat);

};

struct PointDebugRenderer
{

	void create();
	Shader pointDebugShader;
	GLint u_viewProjection = -1;
	GLint u_positionInt = -1;
	GLint u_positionFloat = -1;
	GLint u_blockPositionInt = -1;
	GLint u_blockPositionFloat = -1;

	void renderPoint(Camera &c, glm::dvec3 point);

	void renderCubePoint(Camera &c, glm::dvec3 point);

};

constexpr int mergeShorts(short a, short b)
{
	int rez = 0;
	((short*)&rez)[0] = a;
	((short*)&rez)[1] = b;
	return rez;
}
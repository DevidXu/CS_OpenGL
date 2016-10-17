#ifndef _MAP_H__
#define _MAP_H__

#include "Shape.h"
class Map
{
public:
	Map();
	void Init();
	void Render(Camera &camera, glm::mat4 &projection, glm::mat4 &view);
private:
	GLfloat size;
	Shape shape[10];
};

#endif
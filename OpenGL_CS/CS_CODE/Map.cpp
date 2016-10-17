#include "stdafx.h"
#include "Map.h"

#include "iostream"

Map::Map()
{
	size = 1.0f;
}

void Map::Init()
{
	std::cout << "Map is being initialized! Pleasing waiting..." << std::endl;

	shape[0].Init("Quad", "shaders/wall/aroundWall.vs", "shaders/wall/aroundWall.frag",
		"resources/Wall/AroundWall.jpg", "resources/Wall/AroundWall-N.jpg", "resources/Wall/AroundWall-D.jpg");
	shape[1].Init("Cube", "shaders/wall/aroundWall.vs", "shaders/wall/aroundWall.frag",
		"resources/Wall/Block.jpg", "resources/Wall/Block-N.jpg", "resources/Wall/Block-D.jpg");
	shape[2].Init("Prism", "shaders/wall/aroundWall.vs", "shaders/wall/aroundWall.frag",
		"resources/Wall/Sharp.jpg", "resources/Wall/Sharp-N.jpg", "resources/Wall/Sharp-D.jpg");
	shape[3].Init("Prism", "shaders/wall/aroundWall.vs", "shaders/wall/aroundWall.frag",
		"resources/Wall/AroundWall.jpg", "resources/Wall/AroundWall-N.jpg", "resources/Wall/AroundWall-D.jpg");
	shape[4].Init("Cube", "shaders/wall/aroundWall.vs", "shaders/wall/aroundWall.frag",
		"resources/Wall/Brick.jpg", "resources/Wall/Brick-N.jpg", "resources/Wall/Brick-D.jpg");
	shape[5].Init("Quad", "shaders/wall/aroundWall.vs", "shaders/wall/aroundWall.frag",
		"resources/Wall/Floor.jpg", "resources/Wall/Floor-N.jpg", "resources/Wall/Floor-D.jpg");

	std::cout << "Map is initialized successfully!" << std::endl;
}

void Map::Render(Camera &camera, glm::mat4 &projection, glm::mat4 &view)
{
	for (int i = 0; i < 4; i++)
	{
		glm::mat4 model = glm::mat4();
		model = glm::rotate(model, glm::radians(90.0f * i), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(16.0f, 5.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.5f, 0.5f, 16.0f));
		shape[0].Render(camera, projection, view, model);

		model = glm::mat4();
		model = glm::rotate(model, glm::radians(90.0f * i), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(16.0f, 5.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f, 0.5f, 16.0f));
		shape[0].Render(camera, projection, view, model);
		
		if (i % 2 == 0)
		{
			model = glm::mat4();
			model = glm::rotate(model, glm::radians(90.0f * i), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, glm::vec3(-14.7f, 0.7f, 0.0f));
			model = glm::scale(model, glm::vec3(2.61f, 1.4f, 0.4f));  // Here we enlarge 2.5->2.51 to avoid overlap
			shape[1].Render(camera, projection, view, model);
		}

		if (i % 2 == 0)
		{
			model = glm::mat4();
			model = glm::rotate(model, glm::radians(90.0f * i), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(2.0f, 5.0f, 5.0f));
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, -3.21f));// Here we enlarge 3.2->3.21 to avoid overlap
			shape[2].Render(camera, projection, view, model);
		}

		model = glm::mat4();
		model = glm::rotate(model, glm::radians(90.0f * (i - 0.5f)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 5.0f, 2.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, 10.85f));
		shape[3].Render(camera, projection, view, model);

		model = glm::mat4();
		GLfloat k = -1.0f;
		if (i >= 2) k = 1.0f;
		model = glm::translate(model, glm::vec3((i % 2 - 0.5) * 2 * 10.75f, 1.0f, k*9.25f));
		model = glm::scale(model, glm::vec3(2.51f, 2.0f, 0.4f));  // Here we enlarge 2.5->2.51 to avoid overlap
		shape[1].Render(camera, projection, view, model);

		model = glm::mat4();
		model = glm::rotate(model, glm::radians(90.0f * i), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.0f, 7.0f));
		model = glm::translate(model, glm::vec3(0.85f, 0.5f, 0.85f));
		shape[4].Render(camera, projection, view, model);
	}

	glm::mat4 model = glm::mat4();
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(32.0f, 32.0f, 1.0f));
	shape[5].Render(camera, projection, view, model);
}
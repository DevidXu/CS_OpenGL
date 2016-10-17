#include "stdafx.h"
#include "iostream"
#include "vector"
#include "stdio.h"
#include<time.h>

#include "Game.h"
extern float dx, dy;

void ShootDegreeUpdate(GLfloat deltatime, bool shoot);

Game::Game(GLuint width, GLuint height)
{
	Width = width;
	Height = height;
}

void Game::Init()
{

	skybox.Init();

	map.Init();

	man.Init();

	for (int i = 0; i < costar_num; i++)
		costar[i].Init();
	costar[0].position = glm::vec3(0.0f, 0.0f, 0.0f);
	costar[1].position = glm::vec3(10.0f, 0.0f, 0.0f);
	costar[2].position = glm::vec3(0.0f, 0.0f, 10.0f);
	costar[3].position = glm::vec3(5.0f, 0.0f, 0.0f);
	costar[4].position = glm::vec3(0.0f, 0.0f, 3.0f);

	gun.Init();

}

void Game::ProcessInput(GLfloat deltatime)
{

}

void Game::Update(GLfloat deltatime, int left_button)
{
	// Control the camera
	GLfloat cameraSpeed = camera.cameraspeed * deltatime;
	if (keys[GLFW_KEY_W])
		camera.Position += cameraSpeed * camera.Front;
	if (keys[GLFW_KEY_S])
		camera.Position -= cameraSpeed * camera.Front;
	if (keys[GLFW_KEY_A])
		camera.Position -= glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;
	if (keys[GLFW_KEY_D])
		camera.Position += glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;
	camera.Position.y = 1.63f;

	// Here update the main man parameters.
	if (left_button) man.SetShoot(true);
	else man.SetShoot(false);
	
	// Update the move degree of the shoot
	ShootDegreeUpdate(deltatime, left_button);

	man.GetPostion(camera);
	man.Update(deltatime, keys);
	
	// Here update the costar parameters.
	for (int i = 0; i < costar_num; i++)
		costar[i].Update(deltatime, keys);
}

void ShootDegreeUpdate(GLfloat deltatime, bool left_button)
{
	srand((unsigned)time(NULL));
	float angle = (rand() % 60 + 60)*0.017;
	if (left_button)
	{
		if (dx > 6.0f) dx -= deltatime *25.0f*cos(angle);
		if (dy > 6.0f) dy -= deltatime *25.0f*sin(angle);
		dx += deltatime * 25.0f*cos(angle);
		dy += deltatime * 25.0f*sin(angle);
	}
	else if (dy > 0.0f)
	{
		if (dx > 0) dx -= deltatime *25.0f; else dx += deltatime *25.0f;
		dy -= deltatime *25.0f;
	}
	// if (dx < 0.0f) dx = 0.0f;
	if (dy < 0.0f) dy = 0.0f;
}

void Game::Render()
{
	glm::mat4 projection = glm::perspective(camera.Zoom, (float)Width / (float)Height, 0.1f, 100.0f);
	skybox.Render(camera, projection);

	glm::mat4 view = glm::lookAt(camera.Position, camera.Position + camera.Front, camera.Up);
	map.Render(camera, projection, view);
	man.Render(camera, projection, view, gun);

	for (int i = 0; i < costar_num;i++)
		costar[i].Render(camera, projection, view, gun);

}


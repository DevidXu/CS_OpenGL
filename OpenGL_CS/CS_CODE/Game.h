#ifndef _GAME_H__
#define _GAME_H__

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "SkyBox.h"
#include "Map.h"
#include "Man.h"

#define costar_num 5

class Game
{
public:
	GLboolean keys[1024];
	GLuint Width, Height;

	Camera camera;
	SkyBox skybox;
	Map map;
	MainMan man;
	Man costar[costar_num];
	Gun gun;

	Game(GLuint width, GLuint height);

	//��ʼ����Ϸ��������ɫ��������ȣ�
	void Init();
	//��Ϸѭ��
	void ProcessInput(GLfloat deltatime);
	void Update(GLfloat deltatime, int left_button);
	void Render();

private:

};

#endif

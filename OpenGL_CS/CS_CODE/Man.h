#ifndef _MAN_H__
#define _MAN_H__

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Gun.h"
#include "Body.h"
#include "Camera.h"
#include "Post.h"
// Node Tree
struct Node
{
	Node* next;    // 同级结点
	Node* chain;   // 子节点
	Body* part;

	bool constriant = true;
	glm::mat4 model;
	glm::mat4 S = glm::mat4();
	float max, min;        // This is the max angle allowed to rotate.
	float rotate = 0.0f;
	float dir = 1.0f, inv = 1.0f;
	void(*R)(Node* n,float angle, float x, float y, float z);
	void(*BR)(Node *n, float angle, float dx, float dy, float dz, float x, float y, float z);

	void Assign(Node* n, Node* c, glm::mat4& m, float angle1, float angle2, 
		void(*fp1)(Node*, float, float, float, float),
		void(*fp2)(Node*, float, float, float, float, float, float, float)
		)
	{
		chain = c; next = n; model = m; max = angle1; min = angle2;
		R = fp1; BR = fp2;
	}
};

class Man
{
public:
	Man();
	~Man();
	glm::vec3 position;
	void Init();
	void Update(GLfloat deltatime, GLboolean *keys);
	void Render(Camera &camera, glm::mat4 &projection, glm::mat4 &view, Gun &gun);
	void SetShoot(bool ifshoot);
private:
	Body body[10];
	int bone_num;

	float life;
	int state;            // 0:stop; 1:move
	int jump;             // 0:not jump 1:jump
	bool shoot;           // 0:no shoot  1: shoot

	void Run(GLfloat deltatime, GLboolean *keys);
	void Jump(GLfloat deltatime, GLboolean *keys);

protected:
	Node* node[10];
	Post post;
};

class MainMan :public Man
{
public:
	void GetPostion(Camera &camera);
	void Render(Camera &camera, glm::mat4 &projection, glm::mat4 &view, Gun &gun);
};
#endif
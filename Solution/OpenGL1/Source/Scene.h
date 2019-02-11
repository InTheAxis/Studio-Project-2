#ifndef SCENE_H
#define SCENE_H

#define DEBUG _debug

#include "GL\glew.h"
#include "Windows.h"
#include "Application.h"
#include "Mtx44.h"
#include "shader.hpp"
#include "Camera2.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
#include "GameObject.h"

#include <string>
#include <iostream>

enum UNIFORM_TYPE
{
	U_MVP = 0,
	U_MODELVIEW,
	U_MODELVIEW_INVERSE_TRANSPOSE,
	U_MATERIAL_AMBIENT,
	U_MATERIAL_DIFFUSE,
	U_MATERIAL_SPECULAR,
	U_MATERIAL_SHININESS,

	U_LIGHTENABLED,
	U_NUMLIGHTS,

	U_LIGHT0_POSITION,
	U_LIGHT0_COLOR,
	U_LIGHT0_POWER,
	U_LIGHT0_KC,
	U_LIGHT0_KL,
	U_LIGHT0_KQ,
	U_LIGHT0_TYPE,
	U_LIGHT0_SPOTDIRECTION,
	U_LIGHT0_COSCUTOFF,
	U_LIGHT0_COSINNER,
	U_LIGHT0_EXPONENT,

	U_LIGHT1_POSITION,
	U_LIGHT1_COLOR,
	U_LIGHT1_POWER,
	U_LIGHT1_KC,
	U_LIGHT1_KL,
	U_LIGHT1_KQ,
	U_LIGHT1_TYPE,
	U_LIGHT1_SPOTDIRECTION,
	U_LIGHT1_COSCUTOFF,
	U_LIGHT1_COSINNER,
	U_LIGHT1_EXPONENT,

	U_LIGHT2_POSITION,
	U_LIGHT2_COLOR,
	U_LIGHT2_POWER,
	U_LIGHT2_KC,
	U_LIGHT2_KL,
	U_LIGHT2_KQ,
	U_LIGHT2_TYPE,
	U_LIGHT2_SPOTDIRECTION,
	U_LIGHT2_COSCUTOFF,
	U_LIGHT2_COSINNER,
	U_LIGHT2_EXPONENT,

	U_LIGHT3_POSITION,
	U_LIGHT3_COLOR,
	U_LIGHT3_POWER,
	U_LIGHT3_KC,
	U_LIGHT3_KL,
	U_LIGHT3_KQ,
	U_LIGHT3_TYPE,
	U_LIGHT3_SPOTDIRECTION,
	U_LIGHT3_COSCUTOFF,
	U_LIGHT3_COSINNER,
	U_LIGHT3_EXPONENT,

	U_LIGHT4_POSITION,
	U_LIGHT4_COLOR,
	U_LIGHT4_POWER,
	U_LIGHT4_KC,
	U_LIGHT4_KL,
	U_LIGHT4_KQ,
	U_LIGHT4_TYPE,
	U_LIGHT4_SPOTDIRECTION,
	U_LIGHT4_COSCUTOFF,
	U_LIGHT4_COSINNER,
	U_LIGHT4_EXPONENT,

	U_COLOR_TEXTURE_ENABLED,
	U_COLOR_TEXTURE,

	U_TEXT_ENABLED,
	U_TEXT_COLOR,

	U_TOTAL,
};

class Scene
{
public:
	Scene();
	~Scene();

	//children of this class should not be calling these! 
	//Override the private virtual functions available at the end of this file
	void Init();
	void Update(double dt);
	void Render();
	void Exit();
protected:
	//essentials for opengl
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	MS modelStack, viewStack, projectionStack;

	//other objects required
	Camera2 camera;
	Light lights[5];

	//essential gameobjects
	GameObject AXES;
	GameObject LIGHTBALL;
	GameObject TEXT;

	//materials
	Material bright, dull, shiny;

	//other variables
	unsigned fps;
	bool _debug;
	double bounceTime, elapsedTime;
	bool lightOn;
	bool captureMouse;
	int numLights;

	//helper functions to separate the init
	void InitUniforms();
	void InitLights();
	void InitGameObjects();
	void InitSceneVariables();

	//handle mouse position
	Vector3 HandleMouseMovement();

	//helper render functions
	void RenderLights();
	void RenderObject(GameObject* go, bool enableLight = true);
	void RenderMeshOnScreen(GameObject* go, bool enableLight = true);
	void RenderText(GameObject* go, std::string text, Color color);
	void RenderTextOnScreen(GameObject* go, std::string text, Color color, float size, float x, float y);
	
	/*FUNCTIONS FOR DERIVED CLASSES TO OVERRIDE*/
	virtual void InitDerived() = 0;
	virtual void RenderDerived() = 0;
	virtual void UpdateDerived(double dt) = 0;
	virtual void UpdateDerivedBounced(double dt) = 0;
};

#endif
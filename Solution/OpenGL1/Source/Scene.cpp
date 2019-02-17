#include "Scene.h"

Scene::Scene()
{
	targetSceneIndex = 999;
	changingScene = false;
	pause = false;
}

void Scene::RequestChangeScene(int index)
{
	this->targetSceneIndex = index;
	this->changingScene = true;
}

bool Scene::GetChangeSceneEvent(int* outIndex)
{
	if (changingScene)
	{
		*outIndex = this->targetSceneIndex;
		changingScene = false;
		return true;
	}
	else return false;
}

bool Scene::GetCaptureMouse()
{
	return captureMouse;
}

std::vector<Color> Scene::ReadFromFBO(unsigned fboID)
{
	//read from our custom fbo
	glBindFramebuffer(GL_FRAMEBUFFER, fboID);
	glReadBuffer(GL_COLOR_ATTACHMENT0);

	int x = 800;//Application::RESOLUTION_X;
	int y = 600;// Application::RESOLUTION_Y;
	long textureSize = x * y * 3;
	std::vector<GLfloat> data(textureSize);
	std::vector<Color> ret(x * y);

	//reading pixels, returning BGR
	glReadPixels(0, 0, x, y, GL_BGR, GL_FLOAT, &data[0]);

	//assigning results in data to rgb Color struct format to return 
	for (int i = 0; i < textureSize; i += 3)
	{
		ret[i / 3] = Color(data[i + 2], data[i + 1], data[i]);
	}

	//bind back default
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	return ret;
}

void Scene::WriteFromFBO(unsigned fboID, std::string fileDest)
{
	//read from our custom fbo
	glBindFramebuffer(GL_FRAMEBUFFER, fboID);
	glReadBuffer(GL_COLOR_ATTACHMENT0);

	int x = Application::RESOLUTION_X;
	int y = Application::RESOLUTION_Y;
	long imageSize = x * y * 3;
	unsigned char *data = new unsigned char[imageSize];

	//reading pixels 
	glReadPixels(0, 0, x, y, GL_BGR, GL_UNSIGNED_BYTE, data);
	
	//assembling header
	int xa = x % 256;
	int xb = (x - xa) / 256; 
	int ya = y % 256;
	int yb = (y - ya) / 256;
	unsigned char header[18] = { 0,0,2,0,0,0,0,0,0,0,0,0,(char)xa,(char)xb,(char)ya,(char)yb,24,0 };
	
	//write
	std::ofstream file(fileDest, std::ios::out | std::ios::binary);
	file.write(reinterpret_cast<char *>(header), sizeof(char) * 18);
	file.write(reinterpret_cast<char *>(data), sizeof(char)*imageSize);
	file.close();

	//clean up pointer
	delete[] data;
	data = nullptr;

	//bind back default
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Scene::~Scene()
{
}

void Scene::InitUniforms()
{
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	//lights
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");

	m_parameters[U_LIGHT3_POSITION] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
	m_parameters[U_LIGHT3_COLOR] = glGetUniformLocation(m_programID, "lights[3].color");
	m_parameters[U_LIGHT3_POWER] = glGetUniformLocation(m_programID, "lights[3].power");
	m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID, "lights[3].kC");
	m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID, "lights[3].kL");
	m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID, "lights[3].kQ");
	m_parameters[U_LIGHT3_TYPE] = glGetUniformLocation(m_programID, "lights[3].type");
	m_parameters[U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[3].spotDirection");
	m_parameters[U_LIGHT3_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[3].cosCutoff");
	m_parameters[U_LIGHT3_COSINNER] = glGetUniformLocation(m_programID, "lights[3].cosInner");
	m_parameters[U_LIGHT3_EXPONENT] = glGetUniformLocation(m_programID, "lights[3].exponent");

	m_parameters[U_LIGHT4_POSITION] = glGetUniformLocation(m_programID, "lights[4].position_cameraspace");
	m_parameters[U_LIGHT4_COLOR] = glGetUniformLocation(m_programID, "lights[4].color");
	m_parameters[U_LIGHT4_POWER] = glGetUniformLocation(m_programID, "lights[4].power");
	m_parameters[U_LIGHT4_KC] = glGetUniformLocation(m_programID, "lights[4].kC");
	m_parameters[U_LIGHT4_KL] = glGetUniformLocation(m_programID, "lights[4].kL");
	m_parameters[U_LIGHT4_KQ] = glGetUniformLocation(m_programID, "lights[4].kQ");
	m_parameters[U_LIGHT4_TYPE] = glGetUniformLocation(m_programID, "lights[4].type");
	m_parameters[U_LIGHT4_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[4].spotDirection");
	m_parameters[U_LIGHT4_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[4].cosCutoff");
	m_parameters[U_LIGHT4_COSINNER] = glGetUniformLocation(m_programID, "lights[4].cosInner");
	m_parameters[U_LIGHT4_EXPONENT] = glGetUniformLocation(m_programID, "lights[4].exponent");

	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);
}

void Scene::InitLights()
{
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	lights[0].position.Set(0, 50, 0);
	lights[0].defaultPos = lights[0].position;
	lights[0].color.Set(1, 0.9f, 1);
	lights[0].power = 1;
	lights[0].type = Light::LIGHT_DIRECTIONAL;
	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	lights[1].position.Set(10, 10, 0);
	lights[1].defaultPos = lights[1].position;
	lights[1].color.Set(1, 0, 0);
	lights[1].power = 3;
	lights[1].type = Light::LIGHT_SPOT;
	glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &lights[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], lights[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], lights[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], lights[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], lights[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], lights[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], lights[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], lights[1].exponent);

	lights[2].position.Set(-10, 10, 0);
	lights[2].defaultPos = lights[2].position;
	lights[2].color.Set(0, 1, 0);
	lights[2].power = 3;
	lights[2].type = Light::LIGHT_SPOT;
	glUniform1i(m_parameters[U_LIGHT2_TYPE], lights[2].type);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &lights[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], lights[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], lights[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], lights[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], lights[2].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], lights[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], lights[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], lights[2].exponent);

	lights[3].position.Set(0, 10, -10);
	lights[3].defaultPos = lights[3].position;
	lights[3].color.Set(1, 1, 1);
	lights[3].power = 3;
	lights[3].type = Light::LIGHT_SPOT;
	glUniform1i(m_parameters[U_LIGHT3_TYPE], lights[3].type);
	glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &lights[3].color.r);
	glUniform1f(m_parameters[U_LIGHT3_POWER], lights[3].power);
	glUniform1f(m_parameters[U_LIGHT3_KC], lights[3].kC);
	glUniform1f(m_parameters[U_LIGHT3_KL], lights[3].kL);
	glUniform1f(m_parameters[U_LIGHT3_KQ], lights[3].kQ);
	glUniform1f(m_parameters[U_LIGHT3_COSCUTOFF], lights[3].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT3_COSINNER], lights[3].cosInner);
	glUniform1f(m_parameters[U_LIGHT3_EXPONENT], lights[3].exponent);

	lights[4].position.Set(0, 10, 10);
	lights[4].defaultPos = lights[4].position;
	lights[4].color.Set(1, 1, 0.5f);
	lights[4].power = 1;
	lights[4].type = Light::LIGHT_SPOT;
	glUniform1i(m_parameters[U_LIGHT4_TYPE], lights[4].type);
	glUniform3fv(m_parameters[U_LIGHT4_COLOR], 1, &lights[4].color.r);
	glUniform1f(m_parameters[U_LIGHT4_POWER], lights[4].power);
	glUniform1f(m_parameters[U_LIGHT4_KC], lights[4].kC);
	glUniform1f(m_parameters[U_LIGHT4_KL], lights[4].kL);
	glUniform1f(m_parameters[U_LIGHT4_KQ], lights[4].kQ);
	glUniform1f(m_parameters[U_LIGHT4_COSCUTOFF], lights[4].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT4_COSINNER], lights[4].cosInner);
	glUniform1f(m_parameters[U_LIGHT4_EXPONENT], lights[4].exponent);

}

void Scene::Init()
{
	/*Default Initialisation of cameras*/
	camera[0]->Init(Vector3(0, 10, -20), Vector3(0, 0, 0), Vector3(0, 1, 0));
	camera[1]->Init(Vector3(0, 10, -20), Vector3(0, 0, -1), Vector3(0, 1, 0));
	/*Windows Console Settings*/
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_MOUSE_INPUT);
	/*OpenGL Settings*/
	//enable culling
	glEnable(GL_CULL_FACE);
	//enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//default fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//enable depth test
	glEnable(GL_DEPTH_TEST);
	/*Generate VAO*/
	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	/*Generate FBO*/
	glGenFramebuffers(1, &m_frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
	//generate a rbo for depth testing
	glGenRenderbuffers(1, &m_renderBufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Application::_RESOLUTION_X, Application::_RESOLUTION_Y);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//generate texture
	glGenTextures(1, &m_frameBufferTexture);
	glBindTexture(GL_TEXTURE_2D, m_frameBufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Application::_RESOLUTION_X, Application::_RESOLUTION_Y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	//attach it current fbo
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_frameBufferTexture, 0);
	//check if fbo is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	/*Load shaders and link to mvp*/
	//Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader///Text.fragmentshader");
	//init uniforms, get programId
	InitUniforms();

	//init required game objects
	InitGameObjects();
	//init variables here
	InitSceneVariables();
	//default init camera, feel free to re-call in derived
	//camera.Init(Vector3(0, 10, -20), Vector3(-1, 25, 0), Vector3(0, 1, 0));
	//init lights
	InitLights();
	//init projection matrix
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 10000.f);  //FOV, Aspect Ratio, Near plane, Far plane
	projectionStack.LoadMatrix(projection);

	InitDerived(); //for derived scenes to inject their own
}

void Scene::InitGameObjects()
{
	AXES.Init(MeshBuilder::GenerateAxes(10000, 5000, 10000));
	LIGHTBALL.Init(MeshBuilder::GenerateCube(Color(1, 1, 0.9f)));
	TEXT.Init(MeshBuilder::GenerateText(16, 16), "Image//Fonts//calibri.tga");
}

void Scene::InitSceneVariables()
{
	bright.Set(0.5f, 0.5f, 0.5f, 10.0f);
	dull.Set(0.4f, 0.3f, 0.1f, 10.0f);
	shiny.Set(0.4f, 0.3f, 0.6f, 30.0f);
	
	DEBUG = false;
	fps = 0;
	elapsedTime = bounceTime = 0.0;
	lightOn = true;
	currentCam = 1;
	orthSize = Vector3(60, 30, 0);
}

void Scene::Update(double dt)
{
	/*frequent priority checks*/

	//0 is fixed, 1 is free
	if (!currentCam)
		camera[0]->Update(dt, Vector3(0, 10, -10), Vector3(0, 0, 0)); //default values, overwrite this
	else
		camera[1]->Update(dt, Vector3(0, 10, -10), Vector3(Application::cursorX, Application::cursorY, 0)); //update camera

	UpdateDerived(dt);
	/*Bounced checks*/
	elapsedTime += dt;
	if (bounceTime >= elapsedTime) return;
	bounceTime = elapsedTime + 0.2f;

	fps = std::ceil(1.0f / dt);

	//debugging controls
	if (Application::IsKeyPressed(VK_TAB))
	{
		DEBUG = !DEBUG;
	}
	if (Application::IsKeyPressed('1'))
	{
		glEnable(GL_CULL_FACE);
	}
	else if (Application::IsKeyPressed('2'))
	{
		glDisable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('3'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	}
	else if (Application::IsKeyPressed('4'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	}

	//noclip toggle
	if (Application::IsKeyPressed('5'))
	{
		dynamic_cast<FreeCam*>(camera[1])->ToggleNoClip();
	}

	//light toggle
	if (Application::IsKeyPressed('6'))
	{
		lightOn = !lightOn;
	}

	//toggle mouse capture
	if (Application::IsKeyPressed('7'))
	{
		captureMouse = !captureMouse;
	}

	if (Application::IsKeyPressed('8'))
	{
		currentCam = !currentCam;
	}
	if (Application::IsKeyPressed('9'))
	{
		dynamic_cast<FreeCam*>(camera[1])->ToggleInvert(1, 0);
	}
	if (Application::IsKeyPressed('0'))
	{
		dynamic_cast<FreeCam*>(camera[1])->ToggleInvert(0, 1);
	}

	//reset 
	if (Application::IsKeyPressed('R'))
	{
		//shouldnt have moved so this is unneeded
		//for (int i = 0; i < 5; ++i) //5 lights
		//{
		//	lights[i].position = lights[i].defaultPos;
		//}

		camera[currentCam]->Reset();
	}

	UpdateDerivedBounced(dt);
}

void Scene::Render()
{
	//set background color
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	// Clear color and depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera[currentCam]->position.x, camera[currentCam]->position.y, camera[currentCam]->position.z,
		camera[currentCam]->target.x, camera[currentCam]->target.y, camera[currentCam]->target.z, camera[currentCam]->up.x, camera[currentCam]->up.y,
		camera[currentCam]->up.z);

	modelStack.LoadIdentity();

	Mtx44 mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //>update the shader with new MVP

	//axes
	if (DEBUG)
		RenderObject(&AXES, false);
	//lights
	RenderLights();

	//for dervied classes
	RenderDerived();

	//UI
	if (DEBUG)
	{
		std::string temp = "FPS: " + std::to_string(fps);
		RenderTextOnScreen(&TEXT, temp, Color(1, 0, 1), 1, 0.5f, 28.5f); //fps
		temp = "COORDS: " + std::to_string((int)camera[currentCam]->position.x) + " "
			+ std::to_string((int)camera[currentCam]->position.y) + " "
			+ std::to_string((int)camera[currentCam]->position.z);
		RenderTextOnScreen(&TEXT, temp, Color(1, 0, 1), 1, 0.5f, 27.5f); //coordinates
	}

}

void Scene::Exit()
{
	// Cleanup VBO here
	glDeleteProgram(m_programID);
}

//helper functions
void Scene::RenderObject(GameObject* go, bool enableLight)
{
	modelStack.PushMatrix();
	//trs
	modelStack.Translate(go->GetTranslate().x, go->GetTranslate().y, go->GetTranslate().z);
	if (go->GetRotate().x != 0)
		modelStack.Rotate(go->GetRotate().x, 1, 0, 0);
	if (go->GetRotate().y != 0)
		modelStack.Rotate(go->GetRotate().y, 0, 1, 0);
	if (go->GetRotate().z != 0)
		modelStack.Rotate(go->GetRotate().z, 0, 0, 1);
	modelStack.Scale(go->GetScale().x, go->GetScale().y, go->GetScale().z);

	Mtx44 mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with new MVP

	if (lightOn && enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);

		Mtx44 modelView, modelView_inverse_transpose;
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &go->GetMaterial()->kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &go->GetMaterial()->kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &go->GetMaterial()->kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], go->GetMaterial()->kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	if (go->GetTextureID() > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, go->GetTextureID());
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	go->Render();

	if (go->GetTextureID() > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	modelStack.PopMatrix();
}

void Scene::RenderObjectOnScreen(GameObject* go, bool enableLight)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, orthSize.x, 0, orthSize.y, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //no need camera for ortho
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //reset modelstack

	//trs
	modelStack.Translate(go->GetTranslate().x, go->GetTranslate().y, go->GetTranslate().z);
	if (go->GetRotate().x != 0)
		modelStack.Rotate(go->GetRotate().x, 1, 0, 0);
	if (go->GetRotate().y != 0)
		modelStack.Rotate(go->GetRotate().y, 0, 1, 0);
	if (go->GetRotate().z != 0)
		modelStack.Rotate(go->GetRotate().z, 0, 0, 1);
	modelStack.Scale(go->GetScale().x, go->GetScale().y, go->GetScale().z);

	Mtx44 mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with new MVP

	if (lightOn && enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);

		Mtx44 modelView, modelView_inverse_transpose;
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &go->GetMaterial()->kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &go->GetMaterial()->kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &go->GetMaterial()->kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], go->GetMaterial()->kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	if (go->GetTextureID() > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, go->GetTextureID());
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	go->Render();

	if (go->GetTextureID() > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void Scene::RenderText(GameObject* go, std::string text, Color color)
{
	if (!go || go->GetTextureID() <= 0) //Proper error check
		return;
	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform4fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, go->GetTextureID());
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.8f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		go->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void Scene::RenderTextOnScreen(GameObject* go, std::string text, Color color, float size, float x, float y)
{
	if (go == nullptr || go->GetTextureID() <= 0) //Proper error check
		return;
	glDisable(GL_DEPTH_TEST);

	Mtx44 ortho;
	ortho.SetToOrtho(0, orthSize.x, 0, orthSize.y, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //no need camera for ortho
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //reset modelstack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);


	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform4fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, go->GetTextureID());
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.8f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		go->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void Scene::RenderLights()
{
	modelStack.PushMatrix();

	//rendering light 0
	if (lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (lights[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else if (lights[0].type == Light::LIGHT_POINT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}
	//rendering light 1
	if (lights[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[1].position.x, lights[1].position.y, lights[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (lights[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else if (lights[1].type == Light::LIGHT_POINT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}
	//rendering light 2
	if (lights[2].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[2].position.x, lights[2].position.y, lights[2].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (lights[2].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[2].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT2_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else if (lights[2].type == Light::LIGHT_POINT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
	}
	//rendering light 3
	lights[3].power = lights[3].enabled ? 3 : 0;
	glUniform1f(m_parameters[U_LIGHT3_POWER], lights[3].power);

	if (lights[3].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[3].position.x, lights[3].position.y, lights[3].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (lights[3].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[3].position;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[3].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT3_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else if (lights[3].type == Light::LIGHT_POINT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[3].position;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
	}
	//rendering light 4
	if (lights[4].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[4].position.x, lights[4].position.y, lights[4].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (lights[4].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[4].position;
		glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[4].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT4_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else if (lights[4].type == Light::LIGHT_POINT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[4].position;
		glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (DEBUG)
	{
		modelStack.PushMatrix();
		modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		RenderObject(&LIGHTBALL, false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(lights[1].position.x, lights[1].position.y, lights[1].position.z);
		RenderObject(&LIGHTBALL, false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(lights[2].position.x, lights[2].position.y, lights[2].position.z);
		RenderObject(&LIGHTBALL, false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(lights[3].position.x, lights[3].position.y, lights[3].position.z);
		RenderObject(&LIGHTBALL, false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(lights[4].position.x, lights[4].position.y, lights[4].position.z);
		RenderObject(&LIGHTBALL, false);
		modelStack.PopMatrix();
	}

	modelStack.PopMatrix();
}
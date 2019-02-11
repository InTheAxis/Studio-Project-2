#ifndef MATERIAL_H
#define MATERIAL_H

struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f)
	{ Set(r, g, b); }
	void Set(float r, float g, float b)
	{ this->r = r; this->g = g; this->b = b; }
};

class Material
{

public:
	Material()
	{
		this->kAmbient.Set(0.1f, 0.1f, 0.1f);
		this->kDiffuse.Set(0.6f, 0.6f, 0.6f);
		this->kSpecular.Set(0.3f, 0.3f, 0.3f);
		this->kShininess = 5.0f;
	}

	void Set(float ambientWhite, float diffuseWhite, float specularWhite, float shininess)
	{
		this->kAmbient.Set(ambientWhite, ambientWhite, ambientWhite);
		this->kDiffuse.Set(diffuseWhite, diffuseWhite, diffuseWhite);
		this->kSpecular.Set(specularWhite, specularWhite, specularWhite);
		this->kShininess = shininess;
	}

	void Set(Component ambient, Component diffuse, Component specular, float shininess)
	{
		this->kAmbient = ambient;
		this->kDiffuse = diffuse;
		this->kSpecular = specular;
		this->kShininess = shininess;
	}

	~Material() {}

	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;
};

#endif 
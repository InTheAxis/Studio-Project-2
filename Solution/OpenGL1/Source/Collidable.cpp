#include "Collidable.h"



Collidable::Collidable()
{
	collider = nullptr;
}

void Collidable::DefineRect2DCollider(Vector3 size)
{
	if (collider != nullptr) { std::cout << "Already defined a collider!"; return; }
	Vector3 halfSize = size * 0.5f;
	Vector3 points[4] = {
		Vector3(translate.x + halfSize.x, 0, translate.z + halfSize.z),
		Vector3(translate.x + halfSize.x, 0, translate.z - halfSize.z),
		Vector3(translate.x - halfSize.x, 0, translate.z - halfSize.z),
		Vector3(translate.x - halfSize.x, 0, translate.z + halfSize.z),
	};
	
	collider = new Collider;
	this->collider->SetScale(halfSize);
	for (int i = 0; i < 4; ++i)
		this->collider->PushToHullPoints(points[i]);
}

void Collidable::DefineCircle2DCollider(Vector3 radius)
{
	if (collider != nullptr) { std::cout << "Already defined a collider!"; return; }

	Vector3 points[8] = {
		Vector3(translate.x + radius.x, 0, 0),
		Vector3(0, 0, translate.z + radius.z),

		Vector3(translate.x + radius.x * 0.5f, 0, translate.z + radius.z * 0.5f),
		Vector3(translate.x + radius.x * 0.5f, 0, translate.z - radius.z * 0.5f),

		Vector3(translate.x - radius.x, 0, 0),
		Vector3(0, 0, translate.z - radius.z),

		Vector3(translate.x - radius.x * 0.5f, 0, translate.z - radius.z * 0.5f),
		Vector3(translate.x - radius.x * 0.5f, 0, translate.z + radius.z * 0.5f),
	};

	collider = new Collider;

	this->collider->SetScale(radius);
	for (int i = 0; i < 8; ++i)
		this->collider->PushToHullPoints(points[i]);
}

Collider * Collidable::GetCollider()
{
	return this->collider;
}


void Collidable::UpdateCollider()
{
	collider->UpdateHull(this->translate, this->rotate);
}

Collidable::~Collidable()
{
}

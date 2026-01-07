#pragma once
#include "../GameObjects/GameObject.h"

class BackgroundObject : public GameObject
{
public:
    BackgroundObject(ObjectType objType) : GameObject(objType) {}

    void Initialise(const char* imageFile, Vector2D position, double angle, double scale)
    {
        GameObject::Initialise(imageFile, position, angle, scale);
        SetDrawDepth(0); 
    }

   
};

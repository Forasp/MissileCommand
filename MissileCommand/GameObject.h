#pragma once
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Listener.h"
#include <memory>
#include "Resources.h"

class Controller;
class Game;
class Message;

class GameObject : public virtual Listener, public sf::Transformable
{
public:
	GameObject(Game* _Game, GameObject* _Parent = nullptr) { mRenderStates = sf::RenderStates::Default; mAddedToRenderer = false; mGame = _Game; mParent = _Parent;  mRotation = 0; }
	GameObject() { mGame = nullptr; mParent = nullptr; };
	~GameObject();
	virtual void RenderTick(sf::RenderWindow* _RenderWindow);
	virtual void Tick(sf::Time _DeltaTime);
	virtual void ControllerTick(sf::Time _DeltaTime);
	virtual void SetController(std::shared_ptr<Controller> _Controller) { mController = _Controller; }
	virtual std::shared_ptr<Controller> GetController() { return mController; }
	virtual void SetTexResources(TextureResources* _ResourceHolder);
	virtual std::pair<double, double> GetPosition() { return mPosition; }
	virtual std::pair<double, double> GetVelocity() { return mVelocity; }
	virtual std::pair<double, double> GetSize() { return mSize; }
	virtual double GetRotation() { return mRotation; }
	virtual void HandleMessage(Message* _Message) {}
	void ReadMessage(Message* _Message);
	virtual void SetPosition(std::pair<double, double> _Position) { mPosition = _Position; }
	virtual void SetRotation(double _Rotation) { mRotation = _Rotation; }
	virtual void AddVelocity(std::pair<double, double> _Velocity) 
	{ 
		mVelocity.first += _Velocity.first; 
		mVelocity.second += _Velocity.second;
	}
	virtual void RemoveChild(GameObject* _GameObject);
	virtual void AddChild(std::shared_ptr<GameObject> _GameObject);
	//virtual void InitializeGameObject() = 0;

	bool mAddedToRenderer;								// Whether or not the object has been handed to the renderer yet.

protected:
	std::pair<double, double> mPosition;				// The object's position
	std::pair<double, double> mSize;					// The object's size
	std::pair<double, double> mVelocity;				// The object's velocity

	double mRotation;									// The Object's rotation
	double mMass;										// The Object's mass
	double mIntegrity;									// The Object's Hitpoints
	double mHardness;									// The Object's Resistance
	
	bool mPhysical;										// Whether or not the Object can collide.

	int  mLayer;										// The Object's layer (for rendering and physics)

	std::vector<std::shared_ptr<GameObject>> mChildren;	// The Object's children

	sf::Sprite mSprite;									// The Object's image
	sf::RenderStates mRenderStates;						// The Object's RenderStates

	TextureResources* mResourceHolder;					// A pointer to resource holder for object texture

	Game* mGame;										// A Pointer to the Game.

	GameObject* mParent;								// A Pointer to the Parent Object

	std::shared_ptr<Controller> mController;
};
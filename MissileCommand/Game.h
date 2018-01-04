#pragma once
#include <thread>
#include "SFML/System/Clock.hpp"
#include "SFML/Graphics.hpp"
#include <memory>
#include "Listener.h"
#include <map>
#include <queue>

class World;
class Messenger;
class Message;
class GameObject;
class MessengerSystem;

class Game : public Listener
{
public:
	Game() {};
	Game(sf::RenderWindow* _RenderWindow);
	~Game();

	void PhysicsThread();
	void ControllerThread();
	void RenderingThread();
	void MessagingThread();

	void LockAllThreads();
	void UnlockAllThreads();

	void EndGame() { mActive = false; }

	std::shared_ptr<Messenger> GetMessenger(std::string _MessengerName);

	void QueueMessage(std::string _MessengerName, std::shared_ptr<Message> _Message);

	bool IsActive() { return (mActive || mPhysicsThreadActive || mRenderingThreadActive || mControllerThreadActive); }

	virtual void ReadMessage(Message* _Message);

	virtual void AddObjectToRenderer(GameObject* _GameObject, int _Layer);
	virtual void RemoveObjectFromRenderer(GameObject* _GameObject, int _Layer);

	virtual std::shared_ptr<World> GetNewWorld();

protected:
	void InitializeGame(sf::RenderWindow* _RenderWindow);

	std::shared_ptr<World> mCurrentWorld;
	std::queue<std::pair<std::string, std::unique_ptr<Message>>> mMessageQueue;

	sf::RenderWindow* mRenderWindow;

	std::shared_ptr<MessengerSystem> mMessengerSystem;

	sf::Clock mClock;

	std::thread mPhysicsThread;
	std::thread mControllerThread;
	std::thread mRenderingThread;
	std::thread mMessagingThread;

	bool mRendering;
	bool mPhysicTicking;
	bool mControllerTicking;
	bool mMessengerTicking;
	bool mActive;
	bool mPhysicsThreadActive;
	bool mRenderingThreadActive;
	bool mControllerThreadActive;
	bool mMessagingThreadActive;
	bool mBlockAllThreads;

	sf::Time mLastPhysicsTime;
	sf::Time mLastControllerTime;
	sf::Time mLastRenderTime;
	sf::Time mLastMessagingTime;

	virtual void CheckControls(int _OverrideControl = -1);

	std::vector<std::vector<GameObject*>> mObjectsToRender;
};
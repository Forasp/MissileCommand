#pragma once
#include <string>

#define MESSAGE_TYPE_INVALID	-1
#define MESSAGE_TYPE_STRING		1
#define MESSAGE_TYPE_DOUBLE		2
#define MESSAGE_TYPE_INPUT		3
#define MESSAGE_TYPE_QUIT		4
#define MESSAGE_TYPE_MOUSE		5
#define MESSAGE_TYPE_FULL		6
#define MESSAGE_TYPE_EVENT		7
#define MESSAGE_TYPE_COLLISION_PTR		8
#define MESSAGE_TYPE_COLLISION_EVENT 9
#define MESSAGE_TYPE_BUTTON_EVENT		10
#define MESSAGE_TYPE_CITY_DESTRUCTION	11
#define MESSAGE_TYPE_CITY_STATE			12

#define COLLISION_WITH_SELF 1
#define RESTART_LEVEL 2
#define TICK_EVENT 3
#define EXPLODE_MISSILE 4
#define END_EXPLOSION 5

class Message
{
public:
	// Empty constructors/destructors
	Message() {};
	~Message() {};

	// Constructor with only message type
	Message(int _MessageType, bool _Consumable = false) : mMessageType(_MessageType), mConsumable(_Consumable), mConsumed(false) {}

	// Constructors with message type and  a single parameter
	Message(int _MessageType, int _MessageInt, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageInt(_MessageInt), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, double _MessageDouble, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageDouble(_MessageDouble), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, std::pair<double, double> _MessageDoublePair, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageDoublePair(_MessageDoublePair), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, std::string _MessageString, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageString(_MessageString), mConsumable(_Consumable), mConsumed(false) {}

	// Constructors with message type and two parameters
	Message(int _MessageType, int _MessageInt, double _MessageDouble, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageInt(_MessageInt), mMessageDouble(_MessageDouble), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, int _MessageInt, std::pair<double, double> _MessageDoublePair, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageInt(_MessageInt), mMessageDoublePair(_MessageDoublePair), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, int _MessageInt, std::string _MessageString, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageInt(_MessageInt), mMessageString(_MessageString), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, double _MessageDouble, std::pair<double, double> _MessageDoublePair, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageDouble(_MessageDouble), mMessageDoublePair(_MessageDoublePair), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, double _MessageDouble, std::string _MessageString, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageDouble(_MessageDouble), mMessageString(_MessageString), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, std::pair<double, double> _MessageDoublePair, std::string _MessageString, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageDoublePair(_MessageDoublePair), mMessageString(_MessageString), mConsumable(_Consumable), mConsumed(false) {}

	// Constructors with message type and three parameters
	Message(int _MessageType, int _MessageInt, double _MessageDouble, std::pair<double, double> _MessageDoublePair, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageInt(_MessageInt), mMessageDouble(_MessageDouble), mMessageDoublePair(_MessageDoublePair), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, int _MessageInt, double _MessageDouble, std::string _MessageString, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageInt(_MessageInt), mMessageDouble(_MessageDouble), mMessageString(_MessageString), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, double _MessageDouble, std::pair<double, double> _MessageDoublePair, std::string _MessageString, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageDouble(_MessageDouble), mMessageDoublePair(_MessageDoublePair), mMessageString(_MessageString), mConsumable(_Consumable), mConsumed(false) {}

	// Constructor with all parameters
	Message(int _MessageType, int _MessageInt, double _MessageDouble, std::pair<double, double> _MessageDoublePair, std::string _MessageString, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageInt(_MessageInt), mMessageDouble(_MessageDouble), mMessageDoublePair(_MessageDoublePair), mMessageString(_MessageString), mConsumable(_Consumable), mConsumed(false) {}

	// New, not fully tested. TODO - Add new constructors for any combo with this parameter.
	Message(int _MessageType, void* _VoidPtr, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageVoidPtr(_VoidPtr), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, double _MessageDouble, void* _VoidPtr, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageDouble(_MessageDouble), mMessageVoidPtr(_VoidPtr), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, std::pair<double, double> _MessageDoublePair, void* _VoidPtr, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageDoublePair(_MessageDoublePair), mMessageVoidPtr(_VoidPtr), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, double _MessageDouble, std::pair<double, double> _MessageDoublePair, void* _VoidPtr, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageDouble(_MessageDouble), mMessageDoublePair(_MessageDoublePair), mMessageVoidPtr(_VoidPtr), mConsumable(_Consumable), mConsumed(false) {}

	void Consume()
	{
		if (mConsumable)
		{
			mConsumed = true;
		}
	}

	void SetConsumable(bool _Consumable)
	{
		mConsumable = _Consumable;
	}

	int GetMessageType() { if (!mConsumed) { return mMessageType; } return NULL; }
	int GetMessageInt() { if (!mConsumed) { return mMessageInt; } return NULL; }
	double GetMessageDouble() { if (!mConsumed) { return mMessageDouble; } return NULL; }
	std::pair<double, double> GetMessageDoublePair() { if (!mConsumed) { return mMessageDoublePair; } return std::pair<double, double>(NULL, NULL); }
	std::string GetMessageString() { if (!mConsumed) { return mMessageString; } return NULL; }

	// New, not fully tested. 
	void* GetMessageVoidPtr() { if (!mConsumed) { return mMessageVoidPtr; } return NULL; }

protected:
	bool mConsumed;
	bool mConsumable;

	int mMessageType;
	int mMessageInt;
	double mMessageDouble;
	std::pair<double, double> mMessageDoublePair;
	std::string mMessageString;

	// New, not fully tested.
	void* mMessageVoidPtr;
};
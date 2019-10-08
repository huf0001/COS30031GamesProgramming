#include "pch.h"

#ifndef LOCK_H
#define LOCK_H

class Lock : Component
{
private:
	//Private Fields
	bool isLocked;
	std::vector<std::string> unlockableWith;

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	bool GetIsLocked();

	//Constructor
	Lock(GameObject* gameObject, bool isLocked, std::vector<std::string> unlockableWith);

	//Public Methods
	bool UnlockableWith(std::string unlockWith);
	void Unlock(std::string unlockWith);
};

#endif

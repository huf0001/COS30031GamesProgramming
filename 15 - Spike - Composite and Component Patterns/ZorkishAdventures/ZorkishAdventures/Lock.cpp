#include "Lock.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

bool Lock::GetIsLocked()
{
	return isLocked;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Lock::Lock(GameObject* gameObject, bool isLocked, std::vector<std::string> unlockableWith) : Component("lock", gameObject)
{
	this->isLocked = isLocked;
	this->unlockableWith = unlockableWith;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

bool Lock::UnlockableWith(std::string unlockWith)
{
	for (std::string key : unlockableWith)
	{
		if (key == unlockWith)
		{
			return true;
		}
	}

	return false;
}

void Lock::Unlock(std::string unlockWith)
{
	if (UnlockableWith(unlockWith))
	{
		isLocked = false;
	}
}

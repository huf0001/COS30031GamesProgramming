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

Message* Lock::Notify(Message* message)
{
	if (message->GetSenderID() == gameObject->GetID())
	{
		std::vector<std::string> messageContent = *(std::vector<std::string>*)message->GetContent();

		if (messageContent.size() == 2 && messageContent[0] == "unlock")
		{
			if (UnlockableWith(messageContent[1]))
			{
				Unlock(messageContent[1]);
				return new Message(
					gameObject->GetID(), "lock", 
					gameObject->GetParentID(), gameObject->GetParentType(),
					message->GetSenderID(), message->GetSenderType(), 
					message->GetSenderParentID(), message->GetSenderParentType(), 
					(void*) new std::string("unlocked")
				);
			}
			else
			{
				return new Message(
					gameObject->GetID(), "lock",
					gameObject->GetParentID(), gameObject->GetParentType(),
					message->GetSenderID(), message->GetSenderType(),
					message->GetSenderParentID(), message->GetSenderParentType(),
					(void*) new std::string("can't unlock")
				);
			}
		}
	}

	return nullptr;
}

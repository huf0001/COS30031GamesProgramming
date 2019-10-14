#include "CommandUse.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string CommandUse::GetSyntax()
{
	std::string result;

	result += "USE\n";
	result += "----------------------------\n";
	result += "Function:\n";
	result += "\t- Use an item (e.g. a button) at your location.\n";
	result += "Syntax:\n";
	result += "\t- \"use [item]\"\n";

	if (aliases.size() > 0)
	{
		result += "Aliases for \"use\":\n";

		for (std::string alias : aliases)
		{
			result += "\t- \"" + alias + "\"\n";
		}
	}

	return result;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

CommandUse::CommandUse() : Command("USE")
{
	AddKeyword("use");
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string CommandUse::Process(std::vector<std::string> input, World* world, Player* player)
{
	input.erase(input.begin());

	std::string usableName = StringManager::Instance()->VectorToString(input, ' ');
	Item* usableItem = nullptr;
	
	if (((Container*)player->GetComponent("container"))->HasItem(input))
	{
		usableItem = ((Container*)player->GetComponent("container"))->GetItem(input);
	}
	else if (((Container*)world->GetCurrentLocation()->GetComponent("container"))->HasItem(input))
	{
		usableItem = ((Container*)world->GetCurrentLocation()->GetComponent("container"))->GetItem(input);
	}

	if (usableItem == nullptr)
	{
		return "You cannot find \"" + usableName + "\" at your current location or in your inventory.";
	}
	else if (!usableItem->HasComponent("button"))
	{
		return "You cannot use " + usableItem->GetName() + ".";
	}
	else
	{
		std::string result = "";
		Message* msgUse = new Message(
			"USE", "command",
			"null", "null",
			usableItem->GetID(), "button",
			usableItem->GetParentID(), usableItem->GetParentType(),
			(void*) new std::string("use")
		);
		Message* replyUse = MessageManager::Instance()->SendMessage(msgUse);
		std::vector<std::string> messageContent = *(std::vector<std::string>*)replyUse->GetContent();
		MessageManager::Instance()->SendQueuedMessages("remove");

		for (int i = 0; i < (int)messageContent.size(); i++)
		{
			if (i != 0)
			{
				result += "\n";
			}

			result += messageContent[i];
		}

		return result;
	}
}

#include "pch.h"

#ifndef NOTIFIABLE_H
#define NOTIFIABLE_H

class Message;

class Notifiable
{
private:
	//Private Fields

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties

	//Constructor
	Notifiable();

	//Public Methods
	virtual Message* Notify(Message* message);
};

#endif

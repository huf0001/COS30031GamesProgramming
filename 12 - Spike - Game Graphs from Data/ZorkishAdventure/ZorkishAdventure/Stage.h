#ifndef STAGE_H
#define STAGE_H

#include <string>

class Stage
{
private:
	//Private Fields

	//Private Methods

protected:
	//Protected Fields
	std::string name;
	bool setup;

	//Protected Methods
	virtual std::string Setup() = 0;
public:
	//Public Properties
	std::string GetName();
	bool GetSetup();
	void SetSetup(bool value);

	//Constructor
	Stage();

	//Public Methods
	virtual std::string Update(std::string input) = 0;
};

#endif
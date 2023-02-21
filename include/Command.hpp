#ifndef COMMAND_HEADER_INCLUDED
#define COMMAND_HEADER_INCLUDED

#include "GameObject.hpp"

/*
 * Add functionality here by deriving from Command and defining execute()
 */

// todo: try overloading execute()?
class Command {
	public:
	virtual ~Command(){}
	virtual void execute( GameObject& go ) = 0;
	//virtual void execute( void ) = 0;
};

class QuitCommand : public Command {
	public:
	virtual void execute( GameObject& go ) {
		std::cout << "Quitting normally with a GameObject...\n";
		//g_gameRunning = false;
	}

	//virtual void execute( void ) {
	//	std::cout << "Quitting normally without a GameObject...\n";
	//}
};

// Representing a no-op
class NullCommand : public Command {
	virtual void execute( GameObject& go ){}
};

#endif

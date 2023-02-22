#ifndef COMMAND_HEADER_INCLUDED
#define COMMAND_HEADER_INCLUDED

#include "GameObject.hpp"

/*
 * Add functionality here by deriving from Command and defining execute()
 */

// todo: maybe try overloading execute() to include GameObjects?
class Command {
	public:
	virtual ~Command(){}
	virtual void execute( void ) = 0;
};

#endif

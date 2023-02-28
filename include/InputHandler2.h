#ifndef INPUT_HANDLER_2_HEADER_DEFINED
#define INPUT_HANDLER_2_HEADER_DEFINED

// Prints a warning to stderr in the form
// <filename>:<linenumber>:<functionName>(): <warningLevel>: <moreDetails>
#define WARNING_MACRO(WLEVEL,WSTRING)\
	fprintf(stderr,\
		"%s:%d:%s(): %s: %s\n",\
		__FILE__, __LINE__, __func__,\
		WLEVEL, WSTRING);

// Let command2 be a typedef to a function pointer
// which takes in void and returns a void
typedef void (Command2)(void);

struct InputHandler2 {
	// The buttons supported by the game
	Command2* quitFunctionCallback;
};

// Much preferable to do a `InputHandler2 ih2 = {0};`
void InputHandler2_ctor(InputHandler2* ih2){
	if(!ih2){
		WARNING_MACRO("Warning", "Null argument");
		return;
	}

	ih2->quitFunctionCallback = NULL;
}

#undef WARNING_MACRO
#endif

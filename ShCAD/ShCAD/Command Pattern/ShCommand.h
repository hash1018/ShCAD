

#ifndef _SHCOMMAND_H
#define _SHCOMMAND_H

class ShCommand {

public:
	virtual ~ShCommand() = 0;
	virtual void Execute() = 0;

protected:
	ShCommand();

};

#endif //_SHCOMMAND_H

#ifndef _SHCOMMANDTYPE_H
#define _SHCOMMANDTYPE_H

enum CommandType {

	Empty_Cancel,
	Empty_PreviousAction,
	AbsoluteCoordinate,
	RelativeCoordinate,
	PolarCoordinate,
	CustomCommand,
	DistanceFromBase,
};

#endif //_SHCOMMANDTYPE_H
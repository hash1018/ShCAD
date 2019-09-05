
#ifndef _SHCOMMANDTYPE_H
#define _SHCOMMANDTYPE_H

enum CommandType {

	Empty_Cancel,
	Empty_CancelBackToPrevious,
	AbsoluteCoordinate,
	RelativeCoordinate,
	PolarCoordinate,
	CustomCommand,
	DistanceFromBase,
	AngleFromBase,
};

#endif //_SHCOMMANDTYPE_H
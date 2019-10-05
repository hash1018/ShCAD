
#ifndef _SHSINGLETON_H
#define _SHSINGLETON_H

#define DeclareSingleton(className)\
\
private:\
	className(); \
	~className();\
\
public:\
	static className* getInstance() {\
	\
		static className instance; \
		return &instance; \
    }\

#endif //_SHSINGLETON_H
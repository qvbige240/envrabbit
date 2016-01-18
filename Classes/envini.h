// 2015年12月07日 星期一 14时55分11秒 
// configure game etc

#ifndef __INI_H__
#define __INI_H__

#define ANDROID

//LINUX
#ifdef ENVEEPC
#define ENVEE_Y			106
#define ENVEE_X			108
#define ENVEE_A			105
#define ENVEE_B			107
#define ENVEE_LEFT_KEY		97
#define ENVEE_RIGHT_KEY		100
#define ENVEE_UP_KEY 		119
#define ENVEE_DOWN_KEY		115
#endif

//ANDROID
#ifdef ANDROID
#define ENVEE_Y			38
#define ENVEE_X			40
#define ENVEE_A			37
#define ENVEE_B			39
#define ENVEE_LEFT_KEY		29
#define ENVEE_RIGHT_KEY		32
#define ENVEE_UP_KEY 		51
#define ENVEE_DOWN_KEY		47
#endif

//PCU23
#ifdef PCU23
#define ENVEE_Y			32
#define ENVEE_X			46
#define ENVEE_A			18
#define ENVEE_B			33
#define ENVEE_LEFT_KEY		66
#define ENVEE_RIGHT_KEY		67
#define ENVEE_UP_KEY 		65
#define ENVEE_DOWN_KEY		64
#endif

//PCU6
#ifdef PCU6
#define ENVEE_Y			24
#define ENVEE_X			49
#define ENVEE_A			25
#define ENVEE_B			16
#define ENVEE_LEFT_KEY		105
#define ENVEE_RIGHT_KEY		106
#define ENVEE_UP_KEY 		103
#define ENVEE_DOWN_KEY		108
#endif

// EX3
#ifdef EX3
#define ENVEE_Y			167
#define ENVEE_X			166
#define ENVEE_A			164
#define ENVEE_B			165
#define ENVEE_LEFT_KEY		83
#define ENVEE_RIGHT_KEY		85
#define ENVEE_UP_KEY 		80
#define ENVEE_DOWN_KEY		88
#endif

// GEN3
#ifdef GEN3
#define ENVEE_Y			40
#define ENVEE_X			54
#define ENVEE_A			26
#define ENVEE_B			41
#define ENVEE_LEFT_KEY		74
#define ENVEE_RIGHT_KEY		75
#define ENVEE_UP_KEY 		73
#define ENVEE_DOWN_KEY		72
#endif

#endif // __INI_H__


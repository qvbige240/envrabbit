/*
enum airlines
{ 
    AIRLINES_airchina, 	//0
    AIRLINES_hainan, 	//1
    AIRLINES_tibet, 		//2
    AIRLINES_xiamen, 	//3
};
*/

#define AIRLINES_hainan

#ifdef AIRLINES_airchina
	#define LOADING_IMG_CNT	3
	#ifdef RESOLUTION_845x480
		#define LOADING_ANIM_POS_X	500
		#define LOADING_ANIM_POS_Y	400
	#endif
	#ifdef RESOLUTION_1024x600
		#define LOADING_ANIM_POS_X	648
		#define LOADING_ANIM_POS_Y	460
	#endif
	#ifdef RESOLUTION_1280x720
		#define LOADING_ANIM_POS_X	798
		#define LOADING_ANIM_POS_Y	540
	#endif
#endif

#ifdef AIRLINES_hainan
	#define LOADING_IMG_CNT	3
	#ifdef RESOLUTION_845x480
		#define LOADING_ANIM_POS_X	500
		#define LOADING_ANIM_POS_Y	400
	#endif
	#ifdef RESOLUTION_1024x600
		#define LOADING_ANIM_POS_X	648
		#define LOADING_ANIM_POS_Y	460
	#endif
	#ifdef RESOLUTION_1280x720
		#define LOADING_ANIM_POS_X	798
		#define LOADING_ANIM_POS_Y	540
	#endif
#endif

#ifdef AIRLINES_tibet
	#define LOADING_IMG_CNT	3
	#ifdef RESOLUTION_845x480
		#define LOADING_ANIM_POS_X	500
		#define LOADING_ANIM_POS_Y	400
	#endif
	#ifdef RESOLUTION_1024x600
		#define LOADING_ANIM_POS_X	648
		#define LOADING_ANIM_POS_Y	460
	#endif
	#ifdef RESOLUTION_1280x720
		#define LOADING_ANIM_POS_X	798
		#define LOADING_ANIM_POS_Y	540
	#endif
#endif

#ifdef AIRLINES_xiamen
	#define LOADING_IMG_CNT	3
	#ifdef RESOLUTION_845x480
		#define LOADING_ANIM_POS_X	500
		#define LOADING_ANIM_POS_Y	400
	#endif
	#ifdef RESOLUTION_1024x600
		#define LOADING_ANIM_POS_X	648
		#define LOADING_ANIM_POS_Y	460
	#endif
	#ifdef RESOLUTION_1280x720
		#define LOADING_ANIM_POS_X	798
		#define LOADING_ANIM_POS_Y	540
	#endif
#endif
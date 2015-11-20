#ifndef __LogoScene_SCENE_H__
#define __LogoScene_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "MainScene.h"
#include "AirlineDefine.h"

#ifndef RESOLUTION_1024x600
#define RESOLUTION_1024x600
#endif
class LogoScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
	void GoScene( float fTime );
    // implement the "static node()" method manually
    LAYER_NODE_FUNC(LogoScene);
};

#endif  // __LogoScene_SCENE_H__

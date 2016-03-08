#include "main.h"
#include "cocos2d.h"

#include "AppDelegate.h"

#define kLanguageEnglish 0
#define kLanguageChinese 1

int main(int argc, char **argv) {

    // create the application instance
    if(argc > 1)
	{
		if(!strcmp(argv[1], "0"))
		{
			cocos2d::CCApplication::setCurrentLanguage(kLanguageEnglish);
		}
		else if(!strcmp(argv[1], "1"))
		{
			cocos2d::CCApplication::setCurrentLanguage(kLanguageChinese);
		}
	}
    
    //printf("argc is %d\n", argc);
    if (argc > 2)
    {   
        if (!strcmp(argv[2], "armh") || !strcmp(argv[2], "handset") || !strcmp(argv[2], "x86h"))	
        {
            cocos2d::CCDirector::sharedDirector()->setHandset(true);
        }
        else
        {
            cocos2d::CCDirector::sharedDirector()->setHandset(false);
        }
    }

	AppDelegate app;

    return cocos2d::CCApplication::sharedApplication().run();
}

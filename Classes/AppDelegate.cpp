#include "AppDelegate.h"
#include "GameLand.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	pDirector->setOpenGLView(pEGLView);

	// turn on display FPS
	pDirector->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);
	float width = CCDirector::sharedDirector()->getWinSize().width;
	float height = CCDirector::sharedDirector()->getWinSize().height;

	float proportion = width / height;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC ||         \
	CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 ||       \
	CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

	if (proportion > 1.5f)
	{
		height = MIN(height, 800);
		width = height * proportion;
	}
	else
	{
		width = MIN(width, 1200);
		height = width / proportion;
	}
	pEGLView->setDesignResolutionSize(width, height, kResolutionShowAll);

#else

	if (width < 960 || height < 640)
	{
		if (proportion > 1.5f)
		{
			height = MAX(height, 640);
			width = height * proportion;
		}
		else
		{
			width = MAX(width, 960);
			height = width / proportion;
		}
		pEGLView->setDesignResolutionSize(width, height, kResolutionShowAll);
	}
	else if (width > 960 || height > 640)
	{
		if (proportion > 1.5f)
		{
			height = MIN(height, 640);
			width = height * proportion;
		}
		else
		{
			width = MIN(width, 960);
			height = width / proportion;
		}
		pEGLView->setDesignResolutionSize(width, height, kResolutionShowAll);
	}

#endif

	CCTexture2D::PVRImagesHavePremultipliedAlpha(true);

	// create a scene. it's an autorelease object
	CCScene *pScene = GameLand::scene();

	// run
	pDirector->runWithScene(pScene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	CCDirector::sharedDirector()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

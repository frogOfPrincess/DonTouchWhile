#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Block.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	//别踩白块黄色开始条
	void addStart();
	//别踩白块绿色结束条
	void addEnd();
	//别踩白块 黑白色块
	void addBnW( unsigned int index );

	//开始回调
	void funForStart();

	void update(float dt);
	//注册监听事件需重载以下函数
	//教程中使用的是3.0版本引擎的用法auto listener = EventListenerTouchOneByOne::create();
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	//色块下滑函数
	void moveDown();
};

#endif // __HELLOWORLD_SCENE_H__

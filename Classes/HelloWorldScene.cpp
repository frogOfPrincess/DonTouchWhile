#include "HelloWorldScene.h"


//使用Block.cpp中的blocks块容器变量
extern myContainer<Block*> blocks;

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }


 /* 屏蔽原代码

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
*/

	addStart();

	funForStart();
	
	//开启监听触屏 参数为 对象,优先级,是否吞噬即不再往下传递事件,,,
	//顺带提一下CCMenu优先级为-128,数值越小越优先,有点像minHeap
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-200,false);
    
	return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

//加入起跑黄线
void HelloWorld::addStart()
{
	CCSize size = CCDirector::sharedDirector()->getVisibleSize() ;

	Block* pBlock = Block::createWithArgs(
		ccYELLOW ,
		CCSizeMake(size.width,size.height/4) ,
		"start",
		24,
		ccBLACK );

	pBlock->setLineIndex(0);
	
	addChild( pBlock ) ;
}

//游戏结束画面
void HelloWorld::addEnd()
{
	CCSize size = CCDirector::sharedDirector()->getVisibleSize() ;

	Block* pBlock = Block::createWithArgs( ccGREEN , size , "Game Over!~~" , 40 , ccRED );
	pBlock->setLineIndex(0);
	addChild(pBlock);
}

//加入黑白块
void HelloWorld::addBnW( unsigned int index )
{
	Block *pBlock = NULL ;
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	unsigned int blackIndex = rand()%4 ;

	for (unsigned int i = 0 ; i<4 ; ++i )
	{
		pBlock = Block::createWithArgs(
			blackIndex==i?ccBLACK:ccWHITE ,
			CCSizeMake( size.width/4-1 , size.height/4-1 ),
			"",
			0,
			ccWHITE );
		pBlock->setLineIndex(index);
		pBlock->setPosition( ccp(i*size.width/4,index*size.height/4) );
		this->addChild(pBlock);
		
	}

	
}

//游戏开始
void HelloWorld::funForStart()
{
	addBnW(1);
	addBnW(2);
	addBnW(3);
}

bool HelloWorld::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	//测试是否成功开启监听触屏
	CCLOG("ccTouchBegan~~");
	CCPoint touchPoint = pTouch->getLocation();
	Block* pBlock = NULL ;
	/*

	Block* pBlock = blocks.getData( 2 ) ;
	if ( pBlock->boundingBox().containsPoint(touchPoint))
	{
		CCLOG("contain~~!!");
	}
	else
	{
		//addEnd();
	}

	*/
	
	//遍历所有块
	for (int i = 0 ; i<blocks.m_nCount ; ++i )
	{
		pBlock = blocks.getData( i+1 );
		
		//教程中pBlock->getColor() == ccColor3B::ccBLACK
		//2.2版本中并没有重载 == 运算符去做相应计算而是提供了ccc3DEqual(ccColor3B&,ccColor3B&)函数
		//碰撞检测原教程中使用pBlock->getTextureRect()获得矩形,估计是3.0的特性,2.2中显示并不正确
		//故在此采用pBlock->boundingBox()来获得矩形再作判断
		//此处还可加条件限制只在第2行触碰黑块有效
		if ( pBlock->getLineIndex() == 1  && pBlock->boundingBox().containsPoint(touchPoint) )
		{
			if (ccc3BEqual( pBlock->getColor() , ccBLACK ))
			{
				pBlock->setColor( ccGRAY );
				moveDown();
			}
			else
			{
				CCMessageBox("congratulation","game over");
			}
			
		}
		
		
	}
	
	
	return true ;
}

void HelloWorld::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void HelloWorld::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}


void HelloWorld::moveDown()
{
	addBnW(4) ;
	Block* pBlock = NULL ;
	for (unsigned int i =1 ; i<=blocks.m_nCount ; ++i )
	{
		pBlock = blocks.getData( i );
		pBlock->moveDown();
	}
}
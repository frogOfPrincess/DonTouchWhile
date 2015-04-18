#include "HelloWorldScene.h"


//ʹ��Block.cpp�е�blocks����������
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


 /* ����ԭ����

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
	
	//������������ ����Ϊ ����,���ȼ�,�Ƿ����ɼ��������´����¼�,,,
	//˳����һ��CCMenu���ȼ�Ϊ-128,��ֵԽСԽ����,�е���minHeap
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

//�������ܻ���
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

//��Ϸ��������
void HelloWorld::addEnd()
{
	CCSize size = CCDirector::sharedDirector()->getVisibleSize() ;

	Block* pBlock = Block::createWithArgs( ccGREEN , size , "Game Over!~~" , 40 , ccRED );
	pBlock->setLineIndex(0);
	addChild(pBlock);
}

//����ڰ׿�
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

//��Ϸ��ʼ
void HelloWorld::funForStart()
{
	addBnW(1);
	addBnW(2);
	addBnW(3);
}

bool HelloWorld::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	//�����Ƿ�ɹ�������������
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
	
	//�������п�
	for (int i = 0 ; i<blocks.m_nCount ; ++i )
	{
		pBlock = blocks.getData( i+1 );
		
		//�̳���pBlock->getColor() == ccColor3B::ccBLACK
		//2.2�汾�в�û������ == �����ȥ����Ӧ��������ṩ��ccc3DEqual(ccColor3B&,ccColor3B&)����
		//��ײ���ԭ�̳���ʹ��pBlock->getTextureRect()��þ���,������3.0������,2.2����ʾ������ȷ
		//���ڴ˲���pBlock->boundingBox()����þ��������ж�
		//�˴����ɼ���������ֻ�ڵ�2�д����ڿ���Ч
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
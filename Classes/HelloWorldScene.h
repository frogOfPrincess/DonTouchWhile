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

	//��Ȱ׿��ɫ��ʼ��
	void addStart();
	//��Ȱ׿���ɫ������
	void addEnd();
	//��Ȱ׿� �ڰ�ɫ��
	void addBnW( unsigned int index );

	//��ʼ�ص�
	void funForStart();

	void update(float dt);
	//ע������¼����������º���
	//�̳���ʹ�õ���3.0�汾������÷�auto listener = EventListenerTouchOneByOne::create();
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	//ɫ���»�����
	void moveDown();
};

#endif // __HELLOWORLD_SCENE_H__

#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"
#include "MyContainer.h"

USING_NS_CC;

class Block:public CCSprite
{
public:
	

	virtual bool initWithArgs(	ccColor3B color, 
								CCSize size, 
								char *label, //�̳���ʹ��std::string
								float fontSize, 
								ccColor3B textColor );//�̳���ʹ��ccColor4B



	static Block* createWithArgs(	ccColor3B color,
									CCSize size,
									char *label, //�̳���ʹ��std::string
									float fontSize,
									ccColor3B textColor);//�̳���ʹ��ccColor4B
	
	void removeBlock( Block * );
	void removeBlock();
	void moveDown();
	//���ٶ���ɶ�д��Ա���������д����set get 
	CC_SYNTHESIZE( int ,lineIndex , LineIndex );//��������initxxxx()��ʼ��

};
	
#endif
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
								char *label, //教程中使用std::string
								float fontSize, 
								ccColor3B textColor );//教程中使用ccColor4B



	static Block* createWithArgs(	ccColor3B color,
									CCSize size,
									char *label, //教程中使用std::string
									float fontSize,
									ccColor3B textColor);//教程中使用ccColor4B
	
	void removeBlock( Block * );
	void removeBlock();
	void moveDown();
	//快速定义可读写成员变量及其读写函数set get 
	CC_SYNTHESIZE( int ,lineIndex , LineIndex );//别忘了在initxxxx()初始化

};
	
#endif
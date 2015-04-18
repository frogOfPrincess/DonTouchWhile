#include "Block.h"

//ɫ������
myContainer<Block*> blocks ;


bool Block::initWithArgs(	ccColor3B color,
							CCSize size,
							char  *label, //�̳���ʹ��std::string
							float fontSize,
							ccColor3B textColor )//�̳���ʹ��ccColor4B
{
	CCSprite::init();
	
	//���ÿ�
	setContentSize( size );
	setColor(color);
	setAnchorPoint(CCSizeZero);
	setTextureRect( CCRectMake(0,0,size.width,size.height) );

	//��������
	CCLabelTTF* pLable = CCLabelTTF::create();
	pLable->setString( label );
	pLable->setFontSize( 24 );
	pLable->setColor( textColor );
	pLable->setPosition( ccp(size.width/2 ,size.height/2) );
	addChild( pLable );
	 
	return true ;
}

Block*  Block::createWithArgs(	ccColor3B color,
								CCSize size,
								char *label, //�̳���ʹ��std::string
								float fontSize,
								ccColor3B textColor)//�̳���ʹ��ccColor4B
{
	Block* pBlock = new Block();
	if( pBlock && pBlock->initWithArgs( color , size , label , fontSize , textColor ) )
	{
		pBlock->autorelease() ;
		blocks.push_back( pBlock );
	}
	
	
	return pBlock ;
}

void Block::removeBlock()
{
	if ( lineIndex<0 )
	{
		removeBlock( this );
	}
}


void Block::removeBlock( Block *block )
{
	this->removeFromParent();
	blocks.remove(block);
	
}

void Block::moveDown()
{
	CCLOG("Block::moveDown");
	--lineIndex ;
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();

	CCFiniteTimeAction *action1 = CCMoveTo::create(
		0.1f ,
		ccp( this->getPosition().x ,lineIndex*size.height/4 ) );

	CCFiniteTimeAction *action2 = CCCallFunc::create( 
		this,
		callfunc_selector(Block::removeBlock) );

	runAction( CCSequence::create(action1,action2,NULL));
}

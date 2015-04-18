#ifndef __MYCONTAINER_H__
#define __MYCONTAINER_H__

#define NULL 0

//节点类
template <typename type>
class dataNode
{
public:
	 dataNode( type d );

	~dataNode();
public:
	type            m_mData ;
	dataNode<type>* m_pNext ;

};


//容器类
template <typename type>
class myContainer
{
public:
	dataNode<type>* m_pHead ;
	dataNode<type>* m_pBack ;
	unsigned int    m_nCount;
public:
	myContainer();
	
	~myContainer();

	void push_back( type ) ;
	type getData( unsigned int );

	bool remove( type ) ;

	
};



//节点类定义
template <typename type>
dataNode<type>::dataNode( type d )
{
	m_mData = d ;
	m_pNext = NULL ;
}

template <typename type>
dataNode<type>::~dataNode()
{

}

//容器类定义

template <typename type>
myContainer<type>::myContainer()
{
	m_pHead = new dataNode<type>( 0 ) ;
	m_pBack = m_pHead ;
	m_nCount= 0 ;
}

template <typename type>
myContainer<type>::~myContainer()
{

}

template <typename type>
void myContainer<type>::push_back( type d )
{
	m_pBack->m_pNext = new dataNode<type>( d );
	if ( m_pBack->m_pNext )
	{
		m_pBack = m_pBack->m_pNext ;
		++m_nCount ;
	}
	else
	{
		
	}

}


template <typename type>
type myContainer<type>::getData( unsigned int index )
{
	if ( m_nCount != 0 && index<=m_nCount )
	{
		dataNode<type> *pRet = m_pHead ;
		for ( unsigned int i = 0 ; i<index ; ++i )
		{
			pRet = pRet->m_pNext ;
		}
		return pRet->m_mData ;
	}
	else
	{
		return 0 ;
	}
}

template <typename type>
bool myContainer<type>::remove( type d = 0 )
{
	if ( d && m_pHead && m_nCount>0 )
	{
		dataNode<type> *iterater = m_pHead ;
		for ( ; iterater->m_pNext != NULL ; iterater = iterater->m_pNext )
		{
			if ( iterater->m_pNext->m_mData == d )
			{
				dataNode<type>* pTem = iterater->m_pNext->m_pNext ;
				delete iterater->m_pNext ;
				iterater->m_pNext = pTem ;
				--m_nCount ;
			}
		}
	}

	return true ;
}


#endif

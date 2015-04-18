#include "MyContainer.h"



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
		exit(1);
	}
		
}


template <typename type>
type myContainer<type>::getBack()
{
	return m_pBack->m_mData ;
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


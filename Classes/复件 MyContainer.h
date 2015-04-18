#ifndef __MYCONTAINER_H__
#define __MYCONTAINER_H__



//�ڵ���
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


//������
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
	type getBack();

	bool remove( type ) ;
};

#endif
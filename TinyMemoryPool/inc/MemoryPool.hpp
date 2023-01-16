#pragma once

template<typename T, size_t NUM_OF_OBJECT = 32>
class MemoryPool
{
private:
	/**
		@brief �սڵ�
	**/
	struct Node{
		char data[sizeof(T)];
		Node *pNext;
	};


	struct Block{
		Block *pNext;
		Node data[NUM_OF_OBJECT];
	};

	Node *pFreeNodeHead = nullptr;
	Block *pBlockHead = nullptr;
public:
	void *allocate();
	void free(void *p);
};

template<typename T, size_t NUM_OF_OBJECT>
void *MemoryPool<T, NUM_OF_OBJECT>::allocate()
{
	if(nullptr == pFreeNodeHead)
	{
		// ��û�п��ÿսڵ������������ڴ��
		Block *pNewBlock = new Block;
		pBlockHead = pNewBlock;

		// �����ڴ���еĽڵ�
		pFreeNodeHead = &pNewBlock -> data[0];
		for(size_t i = 1; i < NUM_OF_OBJECT; i++)
		{
			pNewBlock -> data[i - 1].pNext = &pNewBlock -> data[i];
		}
		pNewBlock -> data[NUM_OF_OBJECT - 1].pNext = nullptr;

		// �����µ��ڴ��
		pNewBlock -> pNext = pBlockHead;
		pBlockHead = pNewBlock;
	}

	// ����սڵ�
	Node *pNode = pFreeNodeHead;
	pFreeNodeHead = pFreeNodeHead -> pNext;
	return pNode -> data;
}

template<typename T, size_t NUM_OF_OBJECT>
void MemoryPool<T, NUM_OF_OBJECT>::free(void *p)
{
	Node *pNode = reinterpret_cast<Node *>(p);
	pNode -> pNext = pFreeNodeHead;
	pFreeNodeHead = pNode;
}
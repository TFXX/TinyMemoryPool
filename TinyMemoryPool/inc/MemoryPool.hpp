#pragma once

template<typename T, size_t NUM_OF_OBJECT = 32>
class MemoryPool
{
private:
	/**
		@brief 空节点
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
		// 在没有可用空节点的情况下申请内存块
		Block *pNewBlock = new Block;
		pBlockHead = pNewBlock;

		// 连接内存块中的节点
		pFreeNodeHead = &pNewBlock -> data[0];
		for(size_t i = 1; i < NUM_OF_OBJECT; i++)
		{
			pNewBlock -> data[i - 1].pNext = &pNewBlock -> data[i];
		}
		pNewBlock -> data[NUM_OF_OBJECT - 1].pNext = nullptr;

		// 插入新的内存块
		pNewBlock -> pNext = pBlockHead;
		pBlockHead = pNewBlock;
	}

	// 分配空节点
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
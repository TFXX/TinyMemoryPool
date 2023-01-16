#pragma once

#include <cstdint>
#include <iostream>

#include "MemoryPool.hpp"

class Dog
{
private:
	static MemoryPool<Dog, 8> memPool;
	static std::uint32_t count;

	std::uint32_t m_number = 0;

public:
	Dog();

	void *operator new(size_t size);
	void operator delete(void *p);

	void bark();
};
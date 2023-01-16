#include "../inc/Dog.hpp"

MemoryPool<Dog, 8> Dog::memPool;
std::uint32_t Dog::count = 0;

Dog::Dog()
{
	m_number = count++;
}

void *Dog::operator new(size_t size)
{
	return memPool.allocate();
}

void Dog::operator delete(void *p)
{
	memPool.free(p);
}

void Dog::bark()
{
	std::cout << this << " " << m_number << std::endl;
}
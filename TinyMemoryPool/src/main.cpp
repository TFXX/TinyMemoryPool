#include "..\inc\Dog.hpp"

int main(int argc, char **argv)
{
	constexpr size_t NUM  = 16;
	Dog *pA[NUM];

	for(size_t i = 0; i < NUM; i++)
	{
		pA[i] = new Dog;
	}

	for(size_t i = 0; i < NUM; i++)
	{
		pA[i] -> bark();
	}

	for(size_t i = 0; i < NUM; i++)
	{
		delete pA[i];
	}
	return 0;
}
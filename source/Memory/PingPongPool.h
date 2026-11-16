#ifndef PINGPONGPOOL_H
#define PINGPONGPOOL_H

#include <memory>
#include "Pool.h"
#include "Forward.h"


namespace Cosmo
{
	template <typename T>
	class PingPongPool
	{
	public:
		PingPongPool()
		{
			T pingT;
			T pongT;
			pingPool = new Pool<T, maxEntities>(pingT);
			pongPool = new Pool<T, maxEntities>(pongT);

			current = pingPool;
			notcurrent = pongPool;
		}

		~PingPongPool()
		{
			delete pingPool;
			delete pongPool;
		}

		Pool<T, maxEntities>* getCurrentPool()
		{
			return current;
		}

		std::size_t addObject()
		{
			notcurrent->createObject();
		}

	private:

		void swapBuffer()
		{
			Pool<T, maxEntities>* swap = current;
			current = notcurrent;
			notcurrent = swap;
		}


		Pool<T, maxEntities>* current;
		Pool<T, maxEntities>* notcurrent;

		Pool<T, maxEntities>* pingPool;
		Pool<T, maxEntities>* pongPool;

	};
}

#endif //PINGPONGPOOL_H
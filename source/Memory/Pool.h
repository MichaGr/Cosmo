#ifndef Cosmo_POOL_H
#define Cosmo_POOL_H

#include "../Forward.h"
#include "BasePool.h"
#include <stack>
#include <vector>
#include <memory>

#include <iostream>
#include <map>
#include <omp.h>
template<typename T, std::size_t maxObjects>
class Pool : public BasePool
{
public:
	~Pool()
	{
		delete[] m_data;
	}

	void operator=(const Pool& pool)
	{
		// deep copy
		m_default = pool.m_default;

        if (m_stack->size() != pool.m_stack->size())
		{
			std::cout << "stacks different" << std::endl;
                    m_lastObject = pool.m_lastObject;
            m_loadedObjects = pool.m_loadedObjects;
		}

		for (std::size_t i = 0; i < pool.m_lastObject; ++i)
		{
			m_data[i] = pool.m_data[i];
		}
	}

    Pool(T defaultValue)
    {
        m_default = defaultValue;
        m_data = nullptr;
        m_data = new T[maxObjects];

        for(std::size_t i = 0; i < maxObjects;++i)
        {
            m_data[i] = m_default;
        }

        m_lastID = 0;
        m_loadedObjects = 0;
		m_lastObject = 0;
        m_stack = std::make_shared<std::stack<std::size_t> >();
    }

    std::size_t createObject()
    {
        if(m_loadedObjects < maxObjects)
        {
            std::size_t res = 0;
            if(m_stack->empty())
            {
                res =  m_lastID++;
            }
            else
            {
                res = m_stack->top();
                m_stack->pop();
            }
            m_data[res] = T();
            ++m_loadedObjects;
			++m_lastObject;
            return res;
        }
        else
        {
            std::cout << "Pool full: " << m_loadedObjects << std::endl;
        }
        return size_t(-1);
    }

    void createObject(std::size_t id)
    {
        m_data[id] = m_default;
		if (id > m_lastObject)
		{
			m_lastObject = id;
		}
		++m_loadedObjects;
    }

    T& getObject(Cosmo::EntityID id)
    {
        return m_data[id];
    }

    void removeObject(std::size_t id)
    {
		std::cout << id << " " << m_lastObject << " " << m_loadedObjects << std::endl;
        m_data[id] = m_default;
		if ((id+1) != m_lastObject)
		{
			m_stack->push(id);
		}
		else
		{
			--m_lastObject;
		}
        --m_loadedObjects;
    }

    void restore(std::map<Cosmo::EntityID, Cosmo::EntityID>* map) override
	{
        std::map<Cosmo::EntityID, Cosmo::EntityID>::iterator map_it = map->begin();

		for (; map_it != map->end(); ++map_it)
		{
			m_data[map_it->second] = m_data[map_it->first];
			//m_data[map_it->first] = m_default;
		}
	}

    T& operator[](std::size_t id)
    {
        return m_data[id];
    }

	T* getDataPointer() const
	{
		return m_data;
	}

	std::size_t count() 
	{ 
		return m_lastObject; 
	}

protected:

    std::size_t m_loadedObjects;
	std::size_t m_lastObject;

    T m_default;
    T* m_data;

    std::size_t m_lastID;
    std::shared_ptr<std::stack<std::size_t> > m_stack;


};

#endif //Cosmo_POOL_H

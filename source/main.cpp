#include "Game.h"

#include "Forward.h"
#include "../glm-0.9.9.3/glm/gtc/matrix_transform.hpp"
#include <iostream>
#include "Memory/PoolManager.h"
#include <chrono>
#include "SFML/Graphics/RectangleShape.hpp"
#include "Memory/Pool.h"
#include <set>
#include <algorithm>

struct Pos
{
	Pos() : x(0), y(0), z(0) {}
	Pos(int x, int y, int z) : x(x), y(y), z(z) {}
	int x = 0;
	int y = 0;
	int z = 0;
};

struct Node
{
	std::string name;
	//boundaries
	Pos pos;
	int width = 1;
	int height = 1;
	//neighbors
	std::vector<Node*> northN;
	std::vector<Node*> eastN;
	std::vector<Node*> southN;
	std::vector<Node*> westN;

	bool operator ==(const Node& rhs) const
	{
		return pos.x == rhs.pos.x && pos.y == rhs.pos.y && pos.z == rhs.pos.z;
	}
};


struct NodeFunctor
{
	bool operator()(const Node* lhs,const Node* rhs) const
	{
		return lhs->pos.y <= rhs->pos.y && lhs->pos.x < rhs->pos.x;
	}
};

struct NodeFunctor2
{
	bool operator()(const Node* lhs,const Node* rhs) const
	{
		return lhs->pos.x <= rhs->pos.x && lhs->pos.y < rhs->pos.y;
	}
};


struct Graph
{
	std::vector<Node*> nodes;
	int width;
	int height;
	void connectNS(Node* north, Node* south)
	{
		north->southN.push_back(south);
		south->northN.push_back(north);
	}

	void connectWE(Node* west, Node* east)
	{
		west->eastN.push_back(east);
		east->westN.push_back(west);
	}

	bool sameWEBoundary(Node* west, Node* east)
	{
		if (west->height != east->height)
		{
			std::cout << "Fail because size" << std::endl;
			return false;
		}
		if (west->pos.y != east->pos.y)
		{
			return false;
		}
		return true;
	}

	bool sameNSBoundary(Node* north, Node* south)
	{
		if (north->width != south->width)
		{
			return false;
		}
		if (north->pos.x != south->pos.x)
		{
			return false;
		}
		return true;
	}

	bool mergeWEAll()
	{
		bool ret = false;
		for (int i = 0; i < nodes.size(); ++i)
		{
			for (int j = 0; j < nodes.at(i)->eastN.size(); ++j)
			{
				if (sameWEBoundary(nodes.at(i), nodes.at(i)->eastN.at(j)))
				{
					int k = 0;
					for (; k < nodes.size(); ++k)
					{
						if (nodes.at(k) == nodes.at(i)->eastN.at(j))
						{
							break;
						}
					}
					std::cout << "MERGE" << std::endl;
					mergeWE(nodes.at(i), nodes.at(i)->eastN.at(j));
					nodes.erase(nodes.begin() + k);
					ret = true;
					break;
				}
			}
		}
		return ret;
	}

	bool mergeNSAll()
	{
		bool ret = false;
		for (int i = 0; i < nodes.size(); ++i)
		{
			for (int j = 0; j < nodes.at(i)->southN.size(); ++j)
			{
				if (sameNSBoundary(nodes.at(i), nodes.at(i)->southN.at(j)))
				{
					int k = 0;
					for (; k < nodes.size(); ++k)
					{
						if (nodes.at(k) == nodes.at(i)->southN.at(j))
						{
							break;
						}
					}
					std::cout << "MERGE" << std::endl;
					mergeNS(nodes.at(i), nodes.at(i)->southN.at(j));
					nodes.erase(nodes.begin() + k);
					ret = true;
					break;
				}
			}
		}
		return ret;
	}

	void mergeWE(Node* west, Node* east)
	{
		//west->north.insert(west->north.end(), east->north.begin(), east->north.end());
		//west->south.insert(west->south.end(), east->south.begin(), east->south.end());

		west->northN.insert(west->northN.end(), east->northN.begin(), east->northN.end());
		west->southN.insert(west->southN.end(), east->southN.begin(), east->southN.end());

		//west->east = east->east;
		west->eastN = east->eastN;
		west->width += east->width;
		for (int i = 0; i < east->northN.size(); ++i)
		{
			for (int j = 0; j < east->northN.at(i)->southN.size(); ++j)
			{
				if (east->northN.at(i)->southN.at(j) == east)
				{
					east->northN.at(i)->southN.at(j) = west;
				}
			}
		}

		for (int i = 0; i < east->eastN.size(); ++i)
		{
			for (int j = 0; j < east->eastN.at(i)->westN.size(); ++j)
			{
				if (east->eastN.at(i)->westN.at(j) == east)
				{
					east->eastN.at(i)->westN.at(j) = west;
				}
			}
		}

		for (int i = 0; i < east->southN.size(); ++i)
		{
			for (int j = 0; j < east->southN.at(i)->northN.size(); ++j)
			{
				if (east->southN.at(i)->northN.at(j) == east)
				{
					east->southN.at(i)->northN.at(j) = west;
				}
			}
		}
	}

	void mergeNS(Node* north, Node* south)
	{
		//north->west.insert(north->west.end(), south->west.begin(), south->west.end());
		//north->east.insert(north->east.end(), south->east.begin(), south->east.end());

		north->westN.insert(north->westN.end(), south->westN.begin(), south->westN.end());
		north->eastN.insert(north->eastN.end(), south->eastN.begin(), south->eastN.end());

		//north->south = south->south;
		north->southN = south->southN;
		north->height += south->height;
		for (int i = 0; i < south->westN.size(); ++i)
		{
			for (int j = 0; j < south->westN.at(i)->eastN.size(); ++j)
			{
				if (south->westN.at(i)->eastN.at(j) == south)
				{
					south->westN.at(i)->eastN.at(j) = north;
				}
			}
		}

		for (int i = 0; i < south->eastN.size(); ++i)
		{
			for (int j = 0; j < south->eastN.at(i)->westN.size(); ++j)
			{
				if (south->eastN.at(i)->westN.at(j) == south)
				{
					south->eastN.at(i)->westN.at(j) = north;
				}
			}
		}

		for (int i = 0; i < south->southN.size(); ++i)
		{
			for (int j = 0; j < south->southN.at(i)->northN.size(); ++j)
			{
				if (south->southN.at(i)->northN.at(j) == south)
				{
					south->southN.at(i)->northN.at(j) = north;
				}
			}
		}
	}

	void print()
	{
		for (int i = 0; i < nodes.size(); ++i)
		{
			std::cout << nodes.at(i)->pos.x << " " << nodes.at(i)->pos.y << std::endl;
		}
	}

	void connectWEAll()
	{
		std::cout << "WE" << std::endl;
		print();
		for (int i = 0; i < nodes.size() - 1; ++i)
		{
			if (nodes.at(i)->pos.y == nodes.at(i + 1)->pos.y &&
				nodes.at(i)->pos.z == nodes.at(i + 1)->pos.z &&
				nodes.at(i)->pos.x + 1 == nodes.at(i + 1)->pos.x)
			{
				connectWE(nodes.at(i), nodes.at(i + 1));
			}
		}
	}

	void connectNSAll()
	{

		std::cout << "NS" << std::endl;
		print();
		for (int i = 0; i < nodes.size() - width; ++i)
		{
			if (nodes.at(i)->pos.x == nodes.at(i + width)->pos.x &&
				nodes.at(i)->pos.z == nodes.at(i + width)->pos.z &&
				nodes.at(i)->pos.y + 1 == nodes.at(i + width)->pos.y)
			{
				connectNS(nodes.at(i), nodes.at(i + width));
			}
		}
	}
};

struct GraphDrawer
{
	void draw(sf::RenderWindow& window, const std::vector<Node*>& nodes)
	{

		for (int i = 0; i < nodes.size(); ++i)
		{
			int width = nodes.at(i)->width;
			int height = nodes.at(i)->height;
			Pos pos = nodes.at(i)->pos;

			sf::RectangleShape rect(sf::Vector2f(50.0f*(float)width, 50.0f*(float)height));
			rect.setPosition(sf::Vector2f((float)pos.x * 50.0f, (float)pos.y * 50.0f));
			rect.setFillColor(sf::Color((pos.z + 1) * 60, (i + 1) * 20, 255));
			window.draw(rect);
		}
	}
};

int main()
{

	////Mesh Reducer Test

	//sf::RenderWindow window(sf::VideoMode(500, 500), "My window");

	//GraphDrawer drawer;

	//Graph graph;

	//graph.width = 6;
	//graph.height = 4;

	////----- TEST NODES -----

	//Node node00;
	//Node node01;
	//Node node02;
	//Node node03;

	//Node node10;
	//Node node11;
	//Node node12;
	//Node node13;

	//Node node20;
	//Node node21;
	//Node node22;
	//Node node23;

	//Node node30;
	//Node node31;
	//Node node32;
	//Node node33;

	//Node node40;
	//Node node41;
	//Node node42;
	//Node node43;

	//Node node50;
	//Node node51;
	//Node node52;
	//Node node53;

	////setup graph

	//node00.pos = Pos(0, 0, 0);
	//node01.pos = Pos(0, 1, 0);
	//node02.pos = Pos(0, 2, 0);
	//node03.pos = Pos(0, 3, 0);

	//node10.pos = Pos(1, 0, 1);
	//node11.pos = Pos(1, 1, 0);
	//node12.pos = Pos(1, 2, 0);
	//node13.pos = Pos(1, 3, 0);

	//node20.pos = Pos(2, 0, 1);
	//node21.pos = Pos(2, 1, 0);
	//node22.pos = Pos(2, 2, 0);
	//node23.pos = Pos(2, 3, 0);

	//node30.pos = Pos(3, 0, 1);
	//node31.pos = Pos(3, 1, 1);
	//node32.pos = Pos(3, 2, 0);
	//node33.pos = Pos(3, 3, 0);

	//node40.pos = Pos(4, 0, 2);
	//node41.pos = Pos(4, 1, 1);
	//node42.pos = Pos(4, 2, 1);
	//node43.pos = Pos(4, 3, 0);

	//node50.pos = Pos(5, 0, 2);
	//node51.pos = Pos(5, 1, 1);
	//node52.pos = Pos(5, 2, 1);
	//node53.pos = Pos(5, 3, 1);

	////connections

	////add to graph

	//graph.nodes.push_back(&node00);
	//graph.nodes.push_back(&node10);
	//graph.nodes.push_back(&node20);
	//graph.nodes.push_back(&node30);
	//graph.nodes.push_back(&node40);
	//graph.nodes.push_back(&node50);
	//graph.nodes.push_back(&node01);
	//graph.nodes.push_back(&node11);
	//graph.nodes.push_back(&node21);
	//graph.nodes.push_back(&node31);
	//graph.nodes.push_back(&node41);
	//graph.nodes.push_back(&node51);

	//graph.nodes.push_back(&node02);
	//graph.nodes.push_back(&node12);
	//graph.nodes.push_back(&node22);
	//graph.nodes.push_back(&node32);
	//graph.nodes.push_back(&node42);
	//graph.nodes.push_back(&node52);
	//graph.nodes.push_back(&node03);
	//graph.nodes.push_back(&node13);
	//graph.nodes.push_back(&node23);
	//graph.nodes.push_back(&node33);
	//graph.nodes.push_back(&node43);
	//graph.nodes.push_back(&node53);

	//graph.connectNSAll();
	//graph.connectWEAll();

	////----- TEST NODES END -----


	//// run the program as long as the window is open
	//while (window.isOpen())
	//{
	//	// check all the window's events that were triggered since the last iteration of the loop
	//	sf::Event event;
	//	while (window.pollEvent(event))
	//	{
	//		// "close requested" event: we close the window
	//		if (event.type == sf::Event::Closed)
	//			window.close();
	//		if (event.type == sf::Event::KeyPressed)
	//		{
	//			if (event.key.code == sf::Keyboard::A)
	//			{
	//				bool ret = true;
	//				while (ret)
	//				{
	//					ret = false;
	//					ret = graph.mergeWEAll();
	//					ret = graph.mergeNSAll() || ret;
	//				}
	//			}
	//		}
	//	}

	//	// clear the window with black color
	//	window.clear(sf::Color::Black);

	//	// draw everything here...
	//	// window.draw(...);

	//	drawer.draw(window, graph.nodes);
	//	// end the current frame
	//	window.display();
	//}

	//return 0;


	Cosmo::Game game;
	game.init();
	game.run();
}

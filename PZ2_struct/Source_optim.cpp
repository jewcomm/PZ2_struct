#include <cstdio>
#include <iostream>
#include <vector>
#include <stack>
#include <list>

const int size = 14;
// входящие ребра
int adjacency[size][size] = { { 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
						  { 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
						  { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
						  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
						  { 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0 },   // и
						  { 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },	  // с
						  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },   // х
						  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },   // о
						  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },   // д
						  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
						  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
						  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
						  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
						  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 } };

/*
adjacency[i][j] - путь из вершины i в j
*/

class node
{
private:

	int vertex; // номер вершины
	std::vector <int> inpVer; // входящие ребра из вершин
	int inpSum; // количество входящих ребер
	std::vector <int> outVer; // исходящие ребра из вершины
	int outSum; //  количество исхоядщих ребер

public:

	void set(int _vertex, int _adj[size][size], int);
	void print();
	
	int getInpSum()
	{
		return this->inpSum;
	}

	int getOutSum() 
	{
		return this->outSum;
	}

	std::vector <int> getInpVer()
	{
		return this->inpVer;
	}

	std::vector <int> getOutVer()
	{
		return this->outVer;
	}
};

void node::set(int _vertex, int _adj[size][size], int size)
{
	this->vertex = _vertex;
	int count = 0;
	this->inpVer.resize(count);
	for (int i = 0; i < size; i++)
	{
		if(_adj[i][_vertex] == 1)
		{
			count += 1;
			inpVer.resize(count);
			inpVer[count - 1] = i;
		}
	}
	this->inpSum = count;
	
	count = 0;
	this->outVer.resize(count);
	for (int i = 0; i < size; i++)
	{
		if (_adj[_vertex][i] == 1)
		{
			count += 1;
			outVer.resize(count);
			outVer[count - 1] = i;
		}
	}
	this->outSum = count;
}

void node::print()
{
	std::cout << "Вершина:" << this->vertex << std::endl;
	std::cout << "Количество входящих вершин = " << this->inpSum << std::endl;
	std::cout << "Входящие вершины: " << std::endl;
	for(int i = 0; i < this->inpSum; i++)
	{
		std::cout << this->inpVer[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Количество исходящих вершин = " << this->outSum << std::endl;
	std::cout << "Исходящие вершины: " << std::endl;
	for (int i = 0; i < this->outSum; i++)
	{
		std::cout << this->outVer[i] << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

int cort(std::vector <node> nodes);
void add(int arr[size], int val);
int check(std::vector <node> nodes, int vertex, int use[size]);
int check(std::vector <int> input, int use[size]);

int main()
{
	setlocale(LC_ALL, "Rus");
	int vert = 0;

	std::vector <node> nodes;
	nodes.resize(size);

	for(; vert < size; vert++)
	{
		nodes[vert].set(vert, adjacency, size);
		//nodes[vert].print();
	}
	
	cort(nodes);

	return 0;
}

int cort(std::vector <node> nodes)
{
	// непосещенная точка
	int use[size]; // 1 если посещена, 0 в отличном случае
	int lst[size];
	
	for (int i = 0; i < size; i++)
	{
		use[i] = 0;
		lst[i] = -1;
	}


	int add_count = 0;

	for (int i = 0; i < size; i++)
	{
		if (nodes[i].getInpSum() == 0)
		{
			use[i] = 1;
			add(lst, i);
			add_count += 1;
		}
	}
	
	while(add_count < size)
	{
		for (int i = 0; i < size; i++)
		{
			if (use[i] == 1) continue;
			int sze = nodes[i].getInpSum();
			int stat = check(nodes[i].getInpVer(), use);
			if (sze <= add_count && stat)
			{
				use[i] = 1;
				add(lst, i);
				add_count += 1;
			}
		}
	}

	
	for (int i = 0; i < size; i++)
	{
		std::cout << lst[i] << std::endl;
	}

	return 1;
}

void add(int arr[size], int val)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == -1) 
		{
			arr[i] = val;
			break;
		}
	}
}

int check(std::vector <node> nodes, int vertex, int use[size])
{
	std::vector <int> input = nodes[vertex].getInpVer();
	int size = nodes[vertex].getInpSum();
	for (int i = 0; i < size; i++)
	{
		if (use[input[i]] == 0) return 0;
	}
	return 1;
}

int check(std::vector <int> input, int use[size])
{
	int size = input.size();
	for (int i = 0; i < size; i++)
	{
		if (use[input[i]] == 0) return 0;
	}
	return 1;
}

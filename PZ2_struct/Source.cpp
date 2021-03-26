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

void node::set(int _vertex, int _adj[size][size], int size) // инициализация структуры 
{
	this->vertex = _vertex; // номер вершины
	int count = 0; // счетчик
	this->inpVer.resize(count); // выделяем память
	for (int i = 0; i < size; i++) // входящие ребра
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
	this->outVer.resize(count); // исходящие ребра
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

void node::print() // печать данных вершины
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

std::vector <int> sort(std::vector <node> nodes);
int check(std::vector <int> input, int use[size]);

int main()
{
	setlocale(LC_ALL, "Rus");
	int vert = 0;

	std::vector <node> nodes;
	nodes.resize(size);

	for(; vert < size; vert++) // заполняем структуру
	{
		nodes[vert].set(vert, adjacency, size);
		//nodes[vert].print();
	}
	
	std::vector <int> topSort; // вектор для хранения отсортированной последовательности

	topSort = sort(nodes); // вызов функции сортировки 


	std::cout << "Топологически отсортированные вершины:" << std::endl;
	for (int i = 0; i < size; i++)
	{
		std::cout << topSort[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}

std::vector <int> sort (std::vector <node> nodes)
{
	// непосещенная точка
	int use[size]; // 1 если посещена, 0 в отличном случае
	std::vector <int> lst; // выделяем вектор для хранения отсортированной вершины
	lst.resize(size); // выделяем память

	
	for (int i = 0; i < size; i++)
	{
		use[i] = 0; // если вершина не использована храним 0
		lst[i] = -1; // пишем -1 тк все положительные номера используются в качестве номеров вершин
	}


	int add_count = 0; // количество пройденных вершин
	
	while(add_count < size) // пока мы не добавили все вершины выполняем цикл
	{
		for (int i = 0; i < size; i++) // пока не прошли по всем вершинам выполняем цикл
		{
			if (use[i] == 1) continue; // если данная вершина обработана то переходим к следующей
			int sze = nodes[i].getInpSum(); // количество входящих вершин в этой точке
			int stat = check(nodes[i].getInpVer(), use); // проверяем подходит ли эта точка под условие
			if (sze <= add_count && stat) // проверяем условие и количество входящих вершин
			{
				use[i] = 1; // запоминаем что использовали эту вершину
				lst[add_count] = i; // добавляем эту вершину в список
				add_count += 1; // увеличиваем счетчик обработанных вершин
				i = 0; // закоментировать если не требуется порядок по возврастанию
			}
		}
	}

	return lst; // возврат списка
}


/*
функция используется для проверки входящих вершин 
если в вершину входят вершины, и все они уже в списке использованных, то значит она может быть добавлена  
*/
int check(std::vector <int> input, int use[size])
{
	int size = input.size(); // получим количество входящих ребер
	for (int i = 0; i < size; i++) 
	{
		if (use[input[i]] == 0) return 0; // если такая вершина не использовалась вернем 0
	}
	return 1;
}

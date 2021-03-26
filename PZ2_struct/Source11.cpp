#include <cstdio>
#include <iostream>

const int size = 14;
								// входящие ребра
int adjacency[size][size] = { { 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
						  { 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
						  { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
					      { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }, 
						  { 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0 },   // и
						  { 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },	  // с
					  	  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },   // х
						  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },   // о
						  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },   // д
						  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
						  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
						  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
						  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
						  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 } };

/*
adjacency[i][j] - путь из вершины i в j
*/

void found_zeroPoint(int adj[size][size], int used[size]);
int chUsed(int point, int arr[size]);
void addToUsed(int point, int arr[size]);


int main()
{
	int used[size];

	for (int i = 0; i < size; i++)
	{
		used[i] = -1;
	}

	/*for(int i = 0; i < size; i++)
	{
		std::cout << adjacency[i][0];
	}*/

	found_zeroPoint(adjacency, used);

	for (int i = 0; i < size; i++)
	{
		std::cout << used[i] << " ";
	}

	return 0;
}

void found_zeroPoint(int adj[size][size], int used[size])
{
	for(int column = 0; column < size; column++)
	{
		int stat = 0;
		for (int line = 0; line < size; line++)
		{
			if (adj[line][column])
			{
				stat = 1;
				break;
			}
		}
		if (stat == 0) addToUsed(column, used);
	}
}

int chUsed(int point, int arr[size])
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == point) return 1;
	}
	return 0;
}

void addToUsed(int point, int arr[size])
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == -1) 
		{
			arr[i] = point;
			break;
		}
	}
}
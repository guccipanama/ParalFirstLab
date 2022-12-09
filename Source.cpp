#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <conio.h>
#include <windows.h>

using matrix = std::vector<std::vector<int>>;
matrix operator* (const matrix& mat1, const matrix& mat2)
{
	const size_t n = mat1.size();
	const size_t m = mat1.begin()->size();
	const size_t p = mat2.begin()->size();

	matrix res(n, std::vector<int>(p, 0));
	for (size_t j = 0; j < p; ++j)
	{
		for (size_t k = 0; k < m; ++k)
		{
			for (size_t i = 0; i < n; ++i)
				res[i][j] += mat1[i][k] * mat2[k][j];
		}
	}
	return res;
}

int Menu1()
{
	system("cls");
	std::cout << "1. array multiplier" << std::endl;
	std::cout << "2. array generator" << std::endl;
	while (1)
	{
		int key = _getch();
		if ((key == 49) || (key == 50)) 
			return key;
	}
}

matrix ReadData(std::string filename)
{
	std::ifstream file;
	file.open(filename);

	matrix m;

	for (std::string buf; getline(file, buf); 1)
	{
		std::stringstream input(buf);
		int num;
		std::vector<int> temp;
		while (input >> num)
			temp.push_back(num);
		m.push_back(temp);
	}
	file.close();
	return m;
}

void WriteData(matrix& mat1, matrix& mat2, matrix& mat, double res, std::string filename)
{
	std::ofstream file;
	file.open(filename);

	file << "array:" << std::endl;
	for (auto elem : mat)
	{
		for (auto i : elem)
		{
			file << i;
			file << ' ';
		}
		file << std::endl;
	}
	file << "first arr: " << mat1.size() << "x" << mat1.begin()->size() << std::endl;
	file << "second arr size: " << mat2.size() << "x" << mat2.begin()->size() << std::endl;
	file << "res size: "<< mat.size() << "x" << mat.begin()->size() << std::endl;
	file << "time: " << res << std::endl;
	file.close();
}

void Generator(std::string filename1, std::string filename2)
{
	srand(time(NULL));
	int a = rand() % 1000;
	int b = rand() % 1000;
	int c = rand() % 1000;

	std::ofstream file;
	file.open(filename1);
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			file << rand() % 100;
			file << ' ';
		}
		file << std::endl;
	}
	file.close();
	file.open(filename2);
	for (int i = 0; i < b; i++)
	{
		for (int j = 0; j < c; j++)
		{
			file << rand() % 100;
			file << ' ';
		}
		file << std::endl;
	}
	file.close();
}

int main()
{
	while (true)
	{
		int m1 = Menu1();
		if (m1 == 49)
		{
			system("cls");
			matrix mat1;
			matrix mat2;
			std::string filename1;
			std::cout << "path to the first array: ";
			std::cin >> filename1;
			try
			{
				mat1 = ReadData(filename1);
			}
			catch (std::ios_base::failure ex)
			{
				std::cout << ex.what();
				int a = _getch();
				continue;
			}

			system("cls");
			std::string filename2;
			std::cout << "path to the second array: ";
			std::cin >> filename2;
			try
			{
				mat2 = ReadData(filename2);
			}
			catch (std::ios_base::failure ex)
			{
				std::cout << ex.what();
				int a = _getch();
				continue;
			}

			system("cls");
			std::cout << "processing...";
			matrix mat;
			auto begin = std::chrono::steady_clock::now();
			mat = mat1 * mat2;
			auto end = std::chrono::steady_clock::now();
			auto result = std::chrono::duration<double>(end - begin);

			system("cls");
			std::string filename3;
			std::cout << "path to the output file: ";
			std::cin >> filename3;
			try
			{
				WriteData(mat1, mat2, mat, result.count(), filename3);
			}
			catch (std::ios_base::failure ex)
			{
				std::cout << ex.what();
				int a = _getch();
				continue;
			}
			std::cout << "done";
			Sleep(50);
		}
		if (m1 == 50)
		{
			system("cls");
			std::string filename1;
			std::cout << "path to the first array: ";
			std::cin >> filename1;

			system("cls");
			std::string filename2;
			std::cout << "path to the second array: ";
			std::cin >> filename2;
			
			system("cls");
			std::cout << "program will generate two arrays that can be multiplied..." << std::endl;
			Generator(filename1, filename2);
			std::cout << "done";
			Sleep(50);
		}
	}
	return 0;
}

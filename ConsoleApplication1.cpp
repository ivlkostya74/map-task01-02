// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
//#include <windows.h>
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

// Функция для расчета суммы двух векторов
void vectorSum(const std::vector<int>& v1, const std::vector<int>& v2, std::vector<int>& result, int numThreads) {
	int size = v1.size();
	int chunkSize = std::ceil((double)size / numThreads);
	std::vector<std::thread> threads;

	for (int i = 0; i < numThreads; ++i) {
		threads.emplace_back([&, i]() {
			int start = i * chunkSize;
			int end = std::min((i + 1) * chunkSize, size);
			for (int j = start; j < end; ++j) {
				result[j] = v1[j] + v2[j];
			}
			});
	}

	for (auto& thread : threads) {
		thread.join();
	}
}


void printHardwareThreads() {
	std::cout << "Доступное количество аппаратных ядер: " << std::thread::hardware_concurrency() << std::endl;
}

int main() {

	setlocale(LC_ALL, "Russian");

	printHardwareThreads();

	std::vector<int> sizes = { 1000, 10000, 100000, 1000000 };
	std::vector<int> numThreadsList = { 1, 2,3, 4, 8, 16 };

	std::cout << "Количество потоков\tВремя выполнения для 1000\tВремя выполнения для 10000\tВремя выполнения для 100000\tВремя выполнения для 1000000" << std::endl;

	for (int numThreads : numThreadsList) {
		std::cout << numThreads;
		for (int size : sizes) {
			std::vector<int> v1(size, 1);
			std::vector<int> v2(size, 2);
			std::vector<int> result(size);
			auto start = std::chrono::steady_clock::now();
			vectorSum(v1, v2, result, numThreads);
			auto end = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
			std::cout << "\t\t\t\t" << duration;
		}
		std::cout << std::endl;
	}

	return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

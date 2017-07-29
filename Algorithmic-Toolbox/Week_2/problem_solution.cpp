/*The problem and the solution was made by me. It is not from the course assignment list*/

#include "stdafx.h" //Для Microsoft Visual Studio
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

//Медленный и неэффективный алгоритм.
int fibonacci_sum_naive(unsigned long long n) {
	if (n <= 1)
		return 0;

	unsigned long long previous = 0;
	unsigned long long current = 1;
	unsigned long long sum = 0;

	for (long long i = 0; i < n - 1; i++) {
		unsigned long long tmp_previous = previous;
		previous = current;
		current = tmp_previous + current;
		if (i%3 == 0)
			sum += current;
	}

	return sum % 10;
}

/* Функция для вычисления суммы остатков при делении на 10 каждого третьего
члена последовательности Фибоначчи. */
int fib_mods_sum_func(int& n) {
	if (n < 2)
		return 0;
	vector<int> fib_mod_vector = { 0,1 };
	int count(1), sum(0);
	//Заполняем вектор остатками от деления на 10 значений последовательности Фибоначчи.
	for (int i = 2; i <= n; i++)
		fib_mod_vector.push_back((fib_mod_vector[i - 2] + fib_mod_vector[i - 1] % 10) % 10);
	//Суммируем каждый третий элемент вектора.
	for (auto fib : fib_mod_vector) {
		if (count % 3 == 0)
			sum += fib;
		count++;
		}
	return sum;
}

//Быстрый и эффективный алгоритм.
int fibonacci_sum_fast(unsigned long long n) {
	if (n < 2)
		return 0;
	/* Длина периода последовательности Фибоначчи по модулю 10 равна 60 
	(подробнее смотрите Периоды Пизано). Для решения задачи достаточно просто
	вычислить сумму остатков при делении на 10 нужных нам значение последовательности Фибоначчи
	в одном периоде. Затем помножить результат на количество периодов и прибавить сумму
	неучтенных остатков в оставшемся неполном периоде (если такой есть).*/
	int pisano_period_10 = 60;
	//Вычисляем количество периодов.
	unsigned long long num_of_periods = n / 60;
	//Обрабатываем неучтенные значения в оставшемся неполном периоде (если такой есть).
	int new_n = n % pisano_period_10;
	//Вычисляем суммы отстатков
	int sum_in_period = fib_mods_sum_func(pisano_period_10);
	int sum_left = fib_mods_sum_func(new_n);

	return (num_of_periods*sum_in_period + sum_left) % 10;
}

void test() {
	//Проверяем на известных значениях
	assert(fibonacci_sum_naive(0) == 0);
	assert(fibonacci_sum_naive(12) == 6);
	assert(fibonacci_sum_naive(60) == 0);
	assert(fibonacci_sum_naive(70) == 7);
	//Сравниваем результаты простого и быстрого алгоритмов на небольших значениях
	for (unsigned long long i = 0; i < 94; i++) {
		cout << "i = " << i << ", summ_n = " << fibonacci_sum_naive(i) << ", summ_f = " << fibonacci_sum_fast(i) << endl;
		assert(fibonacci_sum_naive(i) == fibonacci_sum_fast(i));
	}
	//Проверяем скорость работы быстрого алгоритма на больших значениях
	for (unsigned long long i = 18446744073709551000; i < 18446744073709551615; i++)
		cout << "i = " << i << ", summ_f = " << fibonacci_sum_fast(i) << endl;
}

int main() {
	long long n = 0;
	cin >> n;
	//cout << fibonacci_sum_naive(n);
	//test();
	cout << fibonacci_sum_fast(n);
}



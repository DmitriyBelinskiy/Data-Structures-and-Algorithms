/* The problem and the solution was made by me. It is not from the course assignment list.

Task/������:
EN: Find out mod 20 of the sum of every third element of the Fibonacci sequence of n 
((F(m1) + F(m2) + � + F(m), 0 <= m <= n & m%3 = 0) mod 20).
RU: ����� � ������� �� ����� ������� �� ������� �� 20 ����� ������� �������� �������� 
������������������ ����� ��������� �� n ((F(m1) + F(m2) + � + F(m), 0 <= m <= n & m%3 = 0) mod 20).*/

#include "stdafx.h" //��� Microsoft Visual Studio
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

//�������, �� ��������� � ������������� ��������.
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

	return sum % 20;
}

/* ������� ��� ���������� ����� �������� ��� ������� �� 20 ������� ��������
����� ������������������ ���������. */
int fib_mods_sum_func(int& n) {
	if (n < 2)
		return 0;
	vector<int> fib_mod_vector = { 0,1 };
	int count(1), sum(0);
	//��������� ������ ��������� �� ������� �� 20 �������� ������������������ ���������.
	for (int i = 2; i <= n; i++)
		fib_mod_vector.push_back((fib_mod_vector[i - 2] + fib_mod_vector[i - 1] % 20) % 20);
	//��������� ������ ������ ������� �������.
	for (auto fib : fib_mod_vector) {
		if (count % 3 == 0)
			sum += fib;
		count++;
		}
	return sum;
}

//������� � ����������� ��������.
int fibonacci_sum_fast(unsigned long long n) {
	if (n < 2)
		return 0;
	/* ����� ������� ������������������ ��������� �� ������ 20 ����� 60 
	(��������� �������� ������� ������). ��� ������� ������ ���������� ������
	��������� ����� �������� ��� ������� �� 20 ������ ��� �������� ������������������ ���������
	� ����� �������. ����� ��������� ��������� �� ���������� �������� � ��������� �����
	���������� �������� � ���������� �������� ������� (���� ����� ����).*/
	int pisano_period_10 = 60;
	//��������� ���������� ��������.
	unsigned long long num_of_periods = n / 60;
	//������������ ���������� �������� � ���������� �������� ������� (���� ����� ����).
	int new_n = n % pisano_period_10;
	//��������� ����� ���������
	int sum_in_period = fib_mods_sum_func(pisano_period_10);
	int sum_left = fib_mods_sum_func(new_n);

	return (num_of_periods*sum_in_period + sum_left) % 20;
}

void test() {
	//��������� �� ��������� ���������
	assert(fibonacci_sum_fast(0) == 0);
	assert(fibonacci_sum_fast(12) == 16);
	assert(fibonacci_sum_fast(60) == 0);
	assert(fibonacci_sum_fast(70) == 7);
	//���������� ���������� �������� � �������� ���������� �� ��������� ���������
	for (unsigned long long i = 0; i < 94; i++) {
		cout << "i = " << i << ", summ_n = " << fibonacci_sum_naive(i) << ", summ_f = " << fibonacci_sum_fast(i) << endl;
		assert(fibonacci_sum_naive(i) == fibonacci_sum_fast(i));
	}
	//��������� �������� ������ �������� ��������� �� ������� ���������
	for (unsigned long long i = 18446744073709551000; i < 18446744073709551615; i++)
		cout << "i = " << i << ", summ_f = " << fibonacci_sum_fast(i) << endl;
}

int main() {
	unsigned long long n = 0;
	cin >> n;
	//cout << fibonacci_sum_naive(n);
	//test();
	cout << fibonacci_sum_fast(n);
}



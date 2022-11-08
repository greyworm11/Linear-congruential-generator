/*
* m - "modulus"
* a - "multiplier"
* c - "increment"
* X0 - "seed" or "start value"
* 
* Recurrence relation: X(n+1) = (a*X(n) + c) mod m.
* 
* In this case using: _srand and _rand, because original functions (srand and rand) reservated in C.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <locale.h>
#include <math.h>
#include <windows.h> // for sleeping


#define MACHINE_WORD_LENGTH 32


unsigned long long int next = 189231;

void _srand(unsigned int seed);
unsigned long long int _rand(unsigned long long int a, unsigned long long int c, unsigned long long int m);
unsigned long long int _exp(int base, int degree);


/*
* Fills intervals with numbers for Pearson's test
*/
void fill_intervals_xi(unsigned long long int* array)
{
	array[0] = 0;
	unsigned long long int Next = 477218588;
	for (int i = 1; i < 9; ++i)
	{
		array[i] = Next * i;
	}
}

/*
* Calculates the power of LCG
*/
short int _power(unsigned long long int a, unsigned long long int m)
{
	short int s = 1;
	unsigned long long int temp = (a - 1) % m;
	while (temp % m != 0)
	{
		s++;
		temp *= (a - 1);
		temp %= m;
	}
	return s;
}

/*
* Makes xi-2 test
*/
void xi2(unsigned long long int a, unsigned long long int c, unsigned long long int m)
{
	printf("Chi-square (Pearson) test is performing...\n\n");

	unsigned long long int* xi_intervals = (unsigned long long int*)malloc(sizeof(unsigned long long int) * 10);
	if (xi_intervals == NULL) exit(-1);

	fill_intervals_xi(xi_intervals);

	unsigned long long int* Allocation = (unsigned long long int*)malloc(sizeof(unsigned long long int) * 9);
	memset(Allocation, 0x00, sizeof(unsigned long long int) * 9);
	unsigned long long int Sat = 0;
	unsigned long long int UnSat = 0;
	for (int NumberOfExp = 0; NumberOfExp < 20; ++NumberOfExp)
	{
		for (unsigned long long i = 0; i < 100000000; ++i)
		{
			next = _rand(a, c, m);
			if (next > xi_intervals[0] && next < xi_intervals[1]) Allocation[0]++;
			if (next > xi_intervals[1] && next < xi_intervals[2]) Allocation[1]++;
			if (next > xi_intervals[2] && next < xi_intervals[3]) Allocation[2]++;
			if (next > xi_intervals[3] && next < xi_intervals[4]) Allocation[3]++;
			if (next > xi_intervals[4] && next < xi_intervals[5]) Allocation[4]++;
			if (next > xi_intervals[5] && next < xi_intervals[6]) Allocation[5]++;
			if (next > xi_intervals[6] && next < xi_intervals[7]) Allocation[6]++;
			if (next > xi_intervals[7] && next < xi_intervals[8]) Allocation[7]++;
			if (next >= xi_intervals[8]) Allocation[8]++;
		}
		double X = 0;
		for (int index = 0; index < 9; ++index)
		{
			X += (((double)Allocation[index] / (double)100000000) - (double)0.1111111111111111) * (((double)Allocation[index] / (double)100000000) - (double)0.1111111111111111) / (double)0.000000001;
		}
		if (X >= 3.940 && X <= 18.307)
		{
			Sat++;
		}
		else
		{
			UnSat++;
		}
	}
	int TotalResult = (int)((float)Sat / ((float)Sat + (float)UnSat) * 100);
	printf("Percentage of satisfactory ñhi-Square tests (Pearson) = %d %%\n\n", TotalResult);
	if (TotalResult > 70)
	{
		printf("Chi-square test successfully passed\n\n");
	}
	else
	{
		printf("Chi-square test was not passed\n\n");
	}
}



/*
* Number BASE erection to DEGREE
*/
unsigned long long int _exp(int base, int degree)
{
	if (base < 0 || degree < 0)
	{
		return 0;
	}

	unsigned long long int result = 1;

	for (int i = 0; i < degree; ++i)
	{
		result *= base;
	}

	return result;
}



/*
* Check randomness of the last bits
*/
void function_for_bin(unsigned long long int dec, int arr[4], double* one, double* Null)
{
	unsigned long long int v = 2147483648;
	int j = 0;

	for (int i = 1; i <= 32; i++)
	{
		if (dec >= v)
		{
			dec -= v;
			if (i >= 29)
			{
				arr[j] = 1;
				j++;
				(*one)++;
			}
		}
		else
		{
			if (i >= 29)
			{
				arr[j] = 0;
				j++;
				(*Null)++;
			}
		}
		v /= 2;
	}
}



/*
* Makes frequency bit test
*/
void frequency_bit_test(unsigned long long int integer, double* s)
{
	for (size_t i = 0; i < 15; i++)
	{
		if (((32 << 1) & integer) == 0)
		{
			(*s)--;
		}
		else
		{
			(*s)++;
		}
	}
}

/*
* Performs a frequency bit test
*/
void frequency_bit_test_check(unsigned long long int a, unsigned long long int c, unsigned long long int m)
{
	unsigned long long int counter = 1;
	unsigned long long int FirstElement;
	double FrequencyInteger = 0;
	int i = 0;

	printf("The frequency bit test is checking...\n\n");
	while (counter <= m)
	{
		if (counter % (m / 10) == 0)
		{
			printf("%llu\n", counter);
		}
		next = _rand(a, c, m);
		if (i == 0)
		{
			FirstElement = next;
			i++;
		}
		frequency_bit_test(next, &FrequencyInteger);
		if (next == FirstElement && i != 1)
		{
			break;
		}
		i = 2;
		counter++;
	}
	FrequencyInteger = (double)(fabs(FrequencyInteger) / (sqrt(2 * 16)));
	double P_value = erfc(FrequencyInteger); // 
	if (P_value > 0.01)
	{
		printf("Frequency bit test passed\n");
	}
	else
	{
		printf("The frequency bit test does not pass\n");

	}
	printf("\nThe resulting sequence period = %llu\n", counter - 1);
}


/*
* Performs a randomness of the last bits test
*/
void function_for_bin_check(unsigned long long int a, unsigned long long int c, unsigned long long int m)
{
	int arr[4] = { 0 };
	double One = 0;
	double Null = 0;
	unsigned long long int counter = 1;
	unsigned long long int FirstElement;
	int i = 0;

	printf("Randomness check of the last bits is performing...\n\n");
	while (counter <= m)
	{
		if (counter % (m / 10) == 0)
		{
			printf("%llu\n", counter);
		}
		next = _rand(a, c, m);
		if (i == 0)
		{
			FirstElement = next;
			i++;
		}
		function_for_bin(next, arr, &One, &Null);
		if (next == FirstElement && i != 1)
		{
			break;
		}
		i = 2;
		counter++;
	}
	printf("\nThe sequence of unit bits is %f\n", (float)(One) / (One + Null));
	printf("The sequence of zero bits is %f\n", (float)(Null) / (One + Null));
	if (fabs(One / (One + Null) - Null / (One + Null)) < 0.1)
	{
		printf("The sequence of the last bits is random\n");
	}
	else
	{
		printf("The sequence of the last bits is not random\n");
	}
}


/*
* Shows options of the program
*/
void choose_action_print(void)
{
	printf("\nSelect action:\n");
	printf("-> Enter 1 to check the frequency bit test \n");
	printf("-> Enter 2 to check the randomness of the last bits \n");
	printf("-> Enter 3 to test the Chi-square (Pearson) criterion \n");
	printf("-> Enter 4 to calculate the generator power\n");
	printf("-> Enter 5 to generate pseudo-random values\n");
	printf("-> ");
}

void generate_values(unsigned long long int a, unsigned long long int c, unsigned long long int m, time_t time_sleep)
{
	unsigned long long int first_element = next;

	next = _rand(a, c, m);
	printf("generated value: %llu\n", next);
	Sleep(time_sleep);
	while (next != first_element)
	{
		next = _rand(a, c, m);
		printf("generated value: %llu\n", next);
		Sleep(time_sleep);
	}
}


/*
* Main - entry point of the program
*/
int main(void)
{
	setlocale(LC_ALL, "");
	int ResultPrint;
	unsigned long long int m, x0;
	unsigned long long int a, c;
	
	srand((unsigned)time(NULL));

	m = _exp(2, MACHINE_WORD_LENGTH);
	x0 = rand();
	c = 1;
	a = 214013;

	unsigned long long int counter = 1;
	unsigned long long int FirstElement;

	int status;

	choose_action_print();

	int status_counter = scanf("%d", &status);

	if (status_counter == 1 && status >= 1 && status <= 5)
	{
		if (status == 1)
		{
			frequency_bit_test_check(a, c, m);
		}
		else if (status == 2)
		{
			function_for_bin_check(a, c, m);
		}
		else if (status == 3)
		{
			xi2(a, c, m);
		}
		else if (status == 4)
		{
			short int power = _power(a, m);
			printf("Power = %d\n", power);
		}
		else if (status == 5)
		{
			time_t time_delay = 100; // delay time for the next generated value	
									 // you can change it (time is in ms)
			generate_values(a, c, m, time_delay);
		}
	}
	else
	{
		printf("unknown command...");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void _srand(unsigned int seed)
{
	next = seed;
}

unsigned long long int _rand(unsigned long long int a, unsigned long long int c, unsigned long long int m)
{
	next = (a * next + c) % m;
	return next;
}
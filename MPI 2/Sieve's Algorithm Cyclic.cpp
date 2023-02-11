//#include <mpi.h>
//#include <cstdlib>
//#include <iostream>
//#include <time.h>
//#include<math.h>
//#include <chrono>
//#include<sstream>
//using namespace std;
//int* populate_array_with_numbers(int, int number_to_start_with = 2, int increment = true);
//void one_to_all_next_broadcast(int, int*, int, int);
//bool is_marked(int, int*);
//bool is_divisible_by(int, int);
//void mark_divident(int , int* , int*, int, int);
//int* merge_marked(int*, int*, int);
//int* get_odd(int*, int*, int&, int);
//void print_array(int*, int, string);
//int main() {
//	//Rank of current process
//	int my_rank;
//	MPI_Init(NULL, NULL);
//	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
//	//Array of numbers for each process and the array for marking as even
//	int* numbers_array = nullptr;
//	int* marked_array = nullptr;
//	int no_of_processes;
//	MPI_Comm_size(MPI_COMM_WORLD, &no_of_processes);
//	int length_of_array;
//	int break_loop = (int)false;
//	switch (my_rank)
//	{
//	case 0:
//	{
//		srand(time(NULL));
//		int range_of_numbers = 2+rand()%1000;
//		length_of_array = range_of_numbers - 1;
//		numbers_array = populate_array_with_numbers(range_of_numbers);
//		marked_array = populate_array_with_numbers(range_of_numbers, 0, false);
//		one_to_all_next_broadcast(my_rank, &length_of_array, no_of_processes, 1);
//		one_to_all_next_broadcast(my_rank, numbers_array, no_of_processes, length_of_array);
//		one_to_all_next_broadcast(my_rank, marked_array, no_of_processes, length_of_array);
//		auto t_start = std::chrono::high_resolution_clock::now();
//		for (int index = 0; index <= sqrt(length_of_array); index++) {
//			mark_divident(numbers_array[index], numbers_array, marked_array, length_of_array, index + no_of_processes);
//			for (int process = 1; process < no_of_processes; process++) {
//				int index_for_process = index + process;
//				MPI_Send(&break_loop, 1, MPI_INT, process, 0, MPI_COMM_WORLD);
//				MPI_Send(&index_for_process, 1, MPI_INT, process, 0, MPI_COMM_WORLD);
//			}
//		}
//		//Record the end time and calculate the total time
//		auto t_end = std::chrono::high_resolution_clock::now();
//		double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
//		break_loop = (int)true;
//		for (int process = 1; process < no_of_processes; process++) {
//			int* received_marked_array = new int[length_of_array];
//			MPI_Send(&break_loop, 1, MPI_INT, process, 0, MPI_COMM_WORLD);
//			MPI_Recv(received_marked_array, length_of_array, MPI_INT, process, process, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//			marked_array = merge_marked(marked_array, received_marked_array, length_of_array);
//		}
//		int length_of_odd = 0;
//		int* odd_values = get_odd(marked_array, numbers_array, length_of_odd, length_of_array);
//		//Print the array of odd numbers found
//		print_array(odd_values, length_of_odd, "\n\nODD NUMBERS BETWEEN 2 AND " + (std::stringstream() << range_of_numbers).str() + " is : \n\n");
//
//		//Print the total time to complete the processes
//		cout << "\n\nTOTAL TIME : " << elapsed_time_ms << " ms.\n\n";
//	}
//		break;
//	default:
//		MPI_Recv(&length_of_array, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//		numbers_array = new int[length_of_array];
//		marked_array = new int[length_of_array];
//		MPI_Recv(numbers_array, length_of_array, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//		MPI_Recv(marked_array, length_of_array, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//		while (true)
//		{
//			MPI_Recv(&break_loop, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//			if (break_loop)break;
//			int index_to_mark;
//			MPI_Recv(&index_to_mark, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//			if (!is_marked(index_to_mark, marked_array) && index_to_mark < length_of_array)
//				mark_divident(numbers_array[index_to_mark], numbers_array, marked_array, length_of_array, index_to_mark + no_of_processes);
//		}
//		MPI_Send(marked_array, length_of_array, MPI_INT, 0, my_rank, MPI_COMM_WORLD);
//		break;
//	}
//	MPI_Finalize();
//}
//int* populate_array_with_numbers(int end_range,int number_to_start_with, int increment) {
//	int total_length = end_range-1;
//	int* array = new int[total_length];
//	int number = number_to_start_with;
//	for (int index = 0; index < total_length; index++) {
//		array[index] = number;
//		if (increment)number++;
//	}
//	return array;
//}
//void one_to_all_next_broadcast(int my_rank, int* value_to_broadcast, int no_of_processes, int no_of_values) {
//	for (int process = my_rank + 1; process < no_of_processes; process++)
//		MPI_Send(value_to_broadcast, no_of_values, MPI_INT, process, my_rank, MPI_COMM_WORLD);
//}
////Check, if the value is already marked(0 for marked as odd and 1 for marked as even)
//bool is_marked(int index, int* marked_array) {
//	return marked_array[index] == 1;
//}
////Check if the value is fully divided by the divisor
//bool is_divisible_by(int divident, int divisor) {
//	return divident % divisor == 0;
//}
////Mark the divident of divisor whose remainder is 0 from start to end and check, if its not marked before
//void mark_divident(int divisor, int* numbers_array, int* marked_array,int length_of_array, int mark_from) {
//	for (int j = mark_from; j < length_of_array; j++) {
//		if (!is_marked(j, marked_array) && is_divisible_by(numbers_array[j], divisor))
//			marked_array[j] = 1;
//	}
//}
//int* merge_marked(int* marked_1, int* marked_2, int length) {
//	for (int i = 0; i < length; i++) {
//		if (marked_2[i] == 1)
//			marked_1[i] = 1;
//	}
//	return marked_1;
//}
//int* get_odd(int* marked_array, int* numbers_array, int&odd_length, int length_of_array) {
//	int* odd_array = new int[length_of_array];
//	odd_length = 0;
//	for (int i = 0; i < length_of_array; i++)
//		if (!is_marked(i, marked_array))
//			odd_array[odd_length++] = numbers_array[i];
//	int* odd_only = new int[odd_length];
//	for (int i = 0; i < odd_length; i++)
//		odd_only[i] = odd_array[i];
//	return odd_only;
//}
////Print the array passed
//void print_array(int* array, int length_of_array, string message) {
//	cout << message << "[";
//	for (int i = 0; i < length_of_array; i++) {
//		cout << array[i] << ", ";
//	}
//	cout << "]\n\n";
//}
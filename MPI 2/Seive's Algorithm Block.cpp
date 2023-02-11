//#include <mpi.h>
//#include <cstdlib>
//#include <iostream>
//#include <time.h>
//#include<math.h>
//#include <chrono>
//#include<sstream>
//using namespace std;
//int* populate_array_with_numbers(int, int);
//int* populate_array_with_0(int);
//void mark_divident(int, int*, int*, int, int mark_from = 0);
//void one_to_all_next_broadcast(int, int, int);
//bool is_marked(int, int*);
//bool is_divisible_by(int, int);
//void mark_and_broadcast(int, int*, int, int*, int, int);
//int* get_odd(int*, int*, int&, int);
//int* merge_arrays(int*, int, int*, int);
//void print_array(int*, int,string);
//int main() {
//	//Rank of current process
//	int my_rank;
//	MPI_Init(NULL, NULL);
//	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
//	//Array of numbers for each process and the array for marking as even
//	int* numbers_array = nullptr;
//	int* marked_array = nullptr;
//	//seed rand to time and generate a range of numbers between 2 and 1000
//	srand(time(NULL));
//	int numbers_range = 2+rand()%1000;
//	//Find the length of total numbers from 2 to end. (1 subtracted cuz to exclude 1 and start from 2)
//	int length_of_numbers = numbers_range - 1;
//	//No of processes
//	int no_of_processes;
//	MPI_Comm_size(MPI_COMM_WORLD, &no_of_processes);
//	//Length of numbers for each process
//	int numbers_for_each_process = length_of_numbers / no_of_processes;
//	//Calcualte start for each process. (2 is add because the start of numbers is always from 2)
//	int start = (my_rank * numbers_for_each_process)+2;
//	//Calcuate end length for each process (-1 so that the next process start and end dont match)
//	int end = (start + numbers_for_each_process)-1;
//	//If the range is greater then end becomes the range
//	end = end > numbers_range ? length_of_numbers : end;
//	//If its the last process then put all the remaining numbers to end
//	end = my_rank == (no_of_processes - 1) ? numbers_range : end;
//	//Calcuate length of array for each process(+1 to include the end in the length)
//	int length_of_array = (end - start) + 1;
//	//Populate the numbers array from start to end
//	numbers_array = populate_array_with_numbers(start, end);
//	//Populate marked array with 0
//	marked_array = populate_array_with_0(length_of_array);
//	//Set the broadcaster to be 0 for each process
//	int broadcaster = 0;
//	//Tell when to stop listening to the broadcaster
//	int stop_listening = false;
//	//The length of odd array
//	int odd_length;
//	//The number odd array
//	int* odd_array = nullptr;
//	switch (my_rank)
//	{
//	case 0:
//	{
//		//Record start time
//		auto t_start = chrono::high_resolution_clock::now();
//		//Mark as even and broadcast that number to underlying processes
//		mark_and_broadcast(length_of_array, marked_array, no_of_processes, numbers_array, my_rank, my_rank);
//		//Make the next process to be the broadcaster
//		one_to_all_next_broadcast(my_rank, my_rank + 1, no_of_processes);
//		//Filter the odd numbers into an array and calculate the length
//		odd_array = get_odd(marked_array, numbers_array, odd_length, length_of_array);
//		//Receive the results from all the processes
//		for (int i = 1; i < no_of_processes; i++) {
//			//Length of receiving numbers
//			int received_length_of_odd;
//			MPI_Recv(&received_length_of_odd, 1, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//			//Array of odd numbers
//			int* received_odd_numbers = new int[received_length_of_odd];
//			MPI_Recv(received_odd_numbers, received_length_of_odd, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//			//Merge previous and new received array into one array
//			odd_array = merge_arrays(odd_array, odd_length, received_odd_numbers, received_length_of_odd);
//			//Increase the odd numbers length
//			odd_length += received_length_of_odd;
//		}
//		//Record the end time and calculate the total time
//		auto t_end = std::chrono::high_resolution_clock::now();
//		double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
//		//Print the array of odd numbers found
//		print_array(odd_array, odd_length, "\n\nODD NUMBERS BETWEEN 2 AND " + (std::stringstream() << numbers_range).str() + " is : \n\n");
//		//Print the total time to complete the processes
//		cout << "\n\nTOTAL TIME : " << elapsed_time_ms << " ms.\n\n";
//		break;
//	}
//	default:
//		//Listen to the broadcaster till the broadcaster is not done sending
//		while (true)
//		{
//			//Receive the broadcaster rank
//			MPI_Recv(&broadcaster, 1, MPI_INT, broadcaster, broadcaster, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//			//If I am the broadcaster
//			if (broadcaster == my_rank) {
//				//Then mark my even and broadcast the number to underlying processes
//				mark_and_broadcast(length_of_array, marked_array, no_of_processes, numbers_array, my_rank, my_rank);
//				//Optimized: only visit the half of the processes then ask all underlying to stop listening
//				if (my_rank == sqrt(no_of_processes)) {
//					one_to_all_next_broadcast(my_rank, my_rank, no_of_processes);
//					one_to_all_next_broadcast(my_rank, (int)true, no_of_processes);
//				}
//				//Otherwise set next broadcaster
//				else
//					one_to_all_next_broadcast(my_rank, my_rank + 1, no_of_processes);
//				break;
//			}
//			//Receive the call, if to stop listening to the broadcaster
//			MPI_Recv(&stop_listening, 1, MPI_INT, broadcaster, broadcaster, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//			//If broadcaster says so, stop listening
//			if (stop_listening)
//				break;
//			//Get the divisor from the broadcaster
//			int divisor;
//			MPI_Recv(&divisor, 1, MPI_INT, broadcaster, broadcaster, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//			//Mark its divident
//			mark_divident(divisor, numbers_array, marked_array, length_of_array);
//		}
//		//Get the odd numbers, the process calculated and send the length and the array to process 0
//		odd_array = get_odd(marked_array, numbers_array, odd_length, length_of_array);
//		MPI_Send(&odd_length, 1, MPI_INT, 0, my_rank, MPI_COMM_WORLD);
//		MPI_Send(odd_array, odd_length, MPI_INT, 0, my_rank, MPI_COMM_WORLD);
//		break;
//	}
//	MPI_Finalize();
//}
////Populate array from start to end
//int* populate_array_with_numbers(int start_number, int end_number) {
//	int length = (end_number - start_number)+1;
//	int* array = new int[length];
//	int index = 0;
//	for (int number = start_number; number <= end_number; number++) {
//		array[index++] = number;
//	}
//	return array;
//}
////Populate array with 0
//int* populate_array_with_0(int length) {
//	int* array = new int[length];
//	for (int i = 0; i < length; i++) {
//		array[i] = 0;
//	}
//	return array;
//}
////Mark the divident of divisor whose remainder is 0 from start to end and check, if its not marked before
//void mark_divident(int divisor, int* numbers_array, int* marked_array,int length_of_array, int mark_from) {
//	for (int j = mark_from; j < length_of_array; j++) {
//		if (!is_marked(j, marked_array) && is_divisible_by(numbers_array[j], divisor))
//			marked_array[j] = 1;
//	}
//}
////Broadcast a value to all the underlying processes
//void one_to_all_next_broadcast(int my_rank, int value_to_broadcast, int no_of_processes) {
//	for (int process = my_rank+1; process < no_of_processes; process++)
//		MPI_Send(&value_to_broadcast, 1, MPI_INT, process, my_rank, MPI_COMM_WORLD);
//}
////Check, if the value is already marked(0 for marked as odd and 1 for marked as even)
//bool is_marked(int index, int* marked_array) {
//	return marked_array[index] == 1;
//}
////Check if the value is fully divided by the divisor
//bool is_divisible_by(int divident, int divisor) {
//	return divident % divisor == 0;
//}
////Mark self evens and broadcast the value to all the underlying process
//void mark_and_broadcast(int length_of_array, int* marked_array, int no_of_processes, int* numbers_array, int my_rank,int broadcaster) {
//	for (int i = 0; i < length_of_array; i++) {
//		if (!is_marked(i, marked_array)) {
//			//Tell which process is broadcaster
//			one_to_all_next_broadcast(my_rank, broadcaster, no_of_processes);
//			//Tell if to break the loop of listening
//			one_to_all_next_broadcast(my_rank, (int)false, no_of_processes);
//			//Send number to be marked as even
//			one_to_all_next_broadcast(my_rank, numbers_array[i], no_of_processes);
//			//Mark dividents in my array
//			mark_divident(numbers_array[i], numbers_array, marked_array, length_of_array, i + 1);
//		}
//	}
//}
////Get odd values from the array(odd values are one, whose index is marked as 0)
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
////Merge two arrays into single array
//int* merge_arrays(int* array1, int length_1,int* array2, int length_2) {
//	int* merged_array = new int[length_1 + length_2];
//
//	int index_of_merged_array = 0;
//	for (int i = 0; i < length_1; i++)
//		merged_array[index_of_merged_array++] = array1[i];
//	for (int i = 0; i < length_2; i++)
//		merged_array[index_of_merged_array++] = array2[i];
//	return merged_array;
//}
////Print the array passed
//void print_array(int* array, int length_of_array, string message) {
//	cout << message << "[";
//	for (int i = 0; i < length_of_array; i++) {
//		cout << array[i] << ", ";
//	}
//	cout << "]\n\n";
//}

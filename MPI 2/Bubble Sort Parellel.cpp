//#include <mpi.h>
//#include <cstdlib>
//#include <iostream>
//#include <time.h>
//#include<math.h>
//#include <chrono>
//using namespace std;
//int* randomize_array(int&);
//int* merge_arrays(int*, int, int*, int);
//void bubble_sort(int*, int);
//void swap(int*, int*);
//
//
//int main() {
//	//Rank of current process
//	int my_rank;
//	MPI_Init(NULL, NULL);
//	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
//	//No of processes
//	int no_of_processes;
//	MPI_Comm_size(MPI_COMM_WORLD, &no_of_processes);
//	//The array to be initialized
//	int* array = nullptr;
//
//	//Length of the array
//	int length_of_array;
//	//Check when to break subprocess loop
//	int break_sub_process_loop;
//	//Check for my rank
//	switch (my_rank) {
//	case 0:
//	{
//		//If its 0, randomize the array and print it
//		array = randomize_array(length_of_array);
//		cout << "*******************************\n";
//		cout << "* PROCESS " << my_rank << " INITIALIZED ARRAY*\n";
//		cout << "*******************************\n\n";
//		cout << "ARRAY IS : [";
//		for (int i = 0; i < length_of_array; i++) {
//			cout << array[i] << ", ";
//		}
//		cout << "]\n\n";
//		cout << "OF LENGTH : " << length_of_array << endl << endl;
//		//Calculate no of elements of array for each process
//		int no_of_elements = ceil(length_of_array / (float)(no_of_processes - 1));
//		//Ping if to break the sub process
//		break_sub_process_loop = (int)false;
//		//Record start time
//		auto t_start = chrono::high_resolution_clock::now();
//		//Tells, if this is even phase
//		bool even_phase = true;
//		//Run n times or till the length of the array
//		for (int j = 0; j < length_of_array; j++)
//		{
//			//Where to start and stop copying values from the returned array into the current array
//			int copy_start = 0;
//			int copy_end = length_of_array;
//			//Send divided array to all the remaining processes
//			for (int i = 1; i < no_of_processes; i++) {
//				//Calculate start and end index for process
//				int start = (i - 1) * no_of_elements;
//				start = even_phase ? start : start + 1;
//				start = start > length_of_array ? length_of_array : start;
//				int end = start + no_of_elements;
//				end = end > length_of_array ? length_of_array : end;
//				//Update the copy start and end
//				if (i == 1)
//					copy_start = start;
//				else if (i == (no_of_processes - 1))
//					copy_end = end;
//				//Calcuate the current length of the array
//				int curr_length = end - start;
//				//curr_length = curr_length < 0 ? 0 : curr_length;
//				//Inform if to break the loop
//				MPI_Send(&break_sub_process_loop, 1, MPI_INT, i, i, MPI_COMM_WORLD);
//				//Send the length for this process
//				MPI_Send(&curr_length, 1, MPI_INT, i, i, MPI_COMM_WORLD);
//				//Send array to this process
//				MPI_Send(&array[start], curr_length, MPI_INT, i, i, MPI_COMM_WORLD);
//			}
//			//Set the length of sorted array and initialize it
//			int sorted_length = 0;
//			int* sorted_array = new int[sorted_length];
//			//Get responses from all the processes
//			for (int i = 1; i < no_of_processes; i++) {
//				//Calculate start and end index for process
//				int start = (i - 1) * no_of_elements;
//				start = even_phase ? start : start + 1;
//				int end = start + no_of_elements;
//				end = end > length_of_array ? length_of_array : end;
//				//Calcuate the current length of the array
//				int curr_length = end - start;
//				//Initialize the buffer to get the array
//				int* array_received = new int[curr_length];
//				//Receiive the array
//				MPI_Recv(array_received, curr_length, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//				//merge the two arrays and update its new sorted length
//				sorted_array = merge_arrays(sorted_array, sorted_length, array_received, curr_length);
//				sorted_length = sorted_length + curr_length;
//
//			}
//			//Change the even phase
//			even_phase = !even_phase;
//			//Copy the sorted array to the original array
//			int index_of_copy = 0;
//			for (int index_to_copy = copy_start; index_to_copy < copy_end; index_to_copy++) {
//				array[index_to_copy] = sorted_array[index_of_copy++];
//			}
//		}
//		//Record the end time and calculate the sorting time
//		auto t_end = std::chrono::high_resolution_clock::now();
//		double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
//		//Stop listening from all the sub processes
//		break_sub_process_loop = (int)true;
//		for (int i = 1; i < no_of_processes; i++) {
//			MPI_Send(&break_sub_process_loop, 1, MPI_INT, i, i, MPI_COMM_WORLD);
//		}
//		//Print the array, sorted one
//		cout << "SORTED ARRAY IS : [";
//		for (int i = 0; i < length_of_array; i++) {
//			cout << array[i] << ", ";
//		}
//		cout << "]\n\n";
//		cout << "SORTED IN " << elapsed_time_ms << " ms";
//	}
//	break;
//	default:
//		//Listen to the process till the end
//		while (true)
//		{
//			//Receive the call to break the loop
//			MPI_Recv(&break_sub_process_loop, 1, MPI_INT, 0, my_rank, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//			if (break_sub_process_loop)
//				break;
//			//Receive the length of the array
//			MPI_Recv(&length_of_array, 1, MPI_INT, 0, my_rank, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//			array = new int[length_of_array];
//			//Receive the array
//			MPI_Recv(array, length_of_array, MPI_INT, 0, my_rank, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//			//Sort the array
//			bubble_sort(array, length_of_array);
//			//Return the array
//			MPI_Send(array, length_of_array, MPI_INT, 0, my_rank, MPI_COMM_WORLD);
//		}
//	}
//	MPI_Finalize();
//}
////Randomize the array to the size 10-20 and store any value between 1-100
////Seed the random for time 0
//int* randomize_array(int& length) {
//	srand(time(0));
//
//	length = 10 + (rand() % 20);
//	int* array = new int[length];
//	for (int i = 0; i < length; i++) {
//		int random_number = 1 + (rand() % 100);
//		array[i] = random_number;
//	}
//	return array;
//}
////Merge two arrays into 1
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
////Bubble sort the given array
//void bubble_sort(int* array, int length) {
//	for (int i = 0; i < length; i++) {
//		bool swapped = false;
//		for (int j = 0; j < length - 1 - i; j++) {
//			if (array[j] > array[j + 1]) {
//				swap(&array[j], &array[j + 1]);
//				swapped = true;
//			}
//		}
//		if (!swapped)
//			break;
//	}
//}
////swap the elements of the array
//void swap(int* value1, int* value2) {
//	int temp = *value1;
//	*value1 = *value2;
//	*value2 = temp;
//}

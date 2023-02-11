//#include <mpi.h>
//#include <cstdlib>
//#include <iostream>
//#include <time.h>
//#include <math.h>
//#include <chrono>
//#include <string>
//using namespace std;
//int* randomize_array(int&);
//int* get_sendcounts(int, int);
//int* get_disp(int*, int, int);
//void do_something(int*, int);
//void print_array(int*, int);
//int main() {
//	int my_rank, process_size;
//	MPI_Init(NULL, NULL);
//	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
//	MPI_Comm_size(MPI_COMM_WORLD, &process_size);
//	int size;
//	int* array = randomize_array(size);
//	int* send_counts = get_sendcounts(size, process_size);
//	int* send_disp = get_disp(send_counts, process_size, size);
//	int* recieve_my_val = new int[send_disp[my_rank]];
//	int* receieve_all = new int[size];
//	MPI_Alltoallv(array, send_counts, send_disp, MPI_INT, recieve_my_val, send_counts, send_disp, MPI_INT, MPI_COMM_WORLD);
//	do_something(recieve_my_val, send_counts[my_rank]);
//	MPI_Gatherv(recieve_my_val, send_counts[my_rank], MPI_INT, receieve_all, send_counts, send_disp, MPI_INT, 0, MPI_COMM_WORLD);
//	if (my_rank == 0) {
//		cout << "BEFORE : " << endl;
//		print_array(array,size);
//		cout << "AFTER : " << endl;
//		print_array(receieve_all, size);
//	}
//	MPI_Finalize();
//}
//int* randomize_array(int& size) {
//	size = 10;
//	int* array = new int[size];
//	for (int i = 0; i < size; i++)
//		array[i] = i;
//	return array;
//}
//int* get_sendcounts(int size, int process_size) {
//	int val_for_each_p = (size / process_size);
//	int* p = new int[process_size];
//	for (int i = 0; i < process_size; i++) {
//		p[i] = val_for_each_p; 
//	}
//	for (int i = 0; i < size % process_size; i++) {
//		p[i]++;
//	}
//	return p;
//}
//int* get_disp(int* values, int process_size, int array_size) {
//	int* disp = new int[process_size];
//	for (int i = 0; i < process_size; i++) {
//		disp[i] = values[i] * i;
//		if (disp[i] >= array_size)
//			disp[i] = array_size;
//	}
//	return disp;
//}
//void do_something(int* array, int size) {
//	srand(time(NULL));
//	for (int i = 0; i < size; i++)
//		array[i] += rand() % 100;
//}
//void print_array(int* array, int size) {
//	cout << "THE ARRAY IS : " << endl;
//	for (int i = 0; i < size; i++) {
//		cout << array[i] << "\t";
//	}
//	cout << endl;
//}
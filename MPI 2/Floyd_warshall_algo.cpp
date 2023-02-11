//#include <mpi.h>
//#include <cstdlib>
//#include <iostream>
//#include <time.h>
//#include <math.h>
//#include <chrono>
//#include <string>
//void find_distance(int, int, int*);
//int* initialize_matrix(int&);
//void print_array(int*,int);
//int validate_index(int, int);
//#define INFINITY 99999999
//using namespace std;
//int main() {
//	int my_rank, process_size;
//	MPI_Init(NULL, NULL);
//	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
//	MPI_Comm_size(MPI_COMM_WORLD, &process_size);
//	int k;
//	int* matrix = nullptr;
//	int size = 0;
//	matrix = initialize_matrix(size);
//	if (my_rank == 0) {
//		std::cout << std::endl << "BEFORE : " << std::endl;
//		print_array(matrix, size);
//	}
//	MPI_Bcast(matrix, size*size, MPI_INT, 0, MPI_COMM_WORLD);
//	int no_of_rows = ceil(size / (float)process_size);
//	int my_k_start = validate_index(my_rank*no_of_rows,size);
//	int my_k_end = validate_index(my_k_start + no_of_rows, size);
//	for (; my_k_start < my_k_end; my_k_start++) {
//		find_distance(my_k_start, size, matrix);
//	}
//	int* temp_buffer = new int[size * size];
//	MPI_Reduce(matrix, temp_buffer, size*size, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
//	switch (my_rank)
//	{
//	case 0:
//		std::cout << std::endl << "AFTER : " << std::endl;
//		print_array(temp_buffer, size);
//		break;
//	}
//	MPI_Finalize();
//}
//void find_distance(int k, int col_size, int* matrix) {
//	for (int i = 0; i < col_size; i++) {
//		for (int j = 0; j < col_size; j++) {
//			matrix[i * col_size + j] = fmin(matrix[i * col_size + k] + matrix[k * col_size + j], matrix[i * col_size + j]);
//		}
//	}
//}
//int* initialize_matrix(int& size) {
//	srand(time(NULL));
//	int distances[6] = { 1,2,3,4,5,INFINITY };
//	size = 5 + rand() % (4);
//	int * matrix = new int[(size * size)];
//	for (int i = 0; i < size; i++)
//		for (int j = 0; j < size; j++) {
//			int distance;
//			if (i == j)
//				distance = 0;
//			else
//				distance = distances[rand() % 6];
//			matrix[i * size + j] = distance;
//		}
//	return matrix;
//}
//void print_array(int* matrix, int size) {
//	std::cout << "  ";
//	int space = 10;
//	{
//	std::string output_value = "";
//	output_value = output_value.append(space - output_value.length(), ' ');
//	std::cout << output_value;
//	for (int i = 0; i < size; i++) {
//		std::string output_value = std::to_string(i);
//		output_value = output_value.append(space - output_value.length(), ' ');
//		std::cout << output_value;
//	}
//	std::cout << std::endl;
//	}
//	{
//		std::cout << "  ";
//		std::string output_value = "_";
//		output_value = output_value.append((space * (size+1)-1) - output_value.length(), ' ');
//		output_value = output_value.append("_");
//		std::cout << output_value << std::endl;
//	}
//	for (int i = 0; i < size; i++) {
//
//		for (int j = 0; j < size; j++) {
//			if (j == 0) {
//				std::cout << i << "|";
//				std::string output_value = "";
//				output_value = output_value.append(space - output_value.length(), ' ');
//				std::cout << output_value;
//			}
//
//			std::string value = std::to_string(matrix[i * size + j]);
//			if (value == std::to_string(INFINITY))
//				value = "INF";
//			std::string output_value = value;
//			output_value = output_value.append(space - output_value.length(), ' ');
//			std::cout << output_value;
//			if (j == size - 1)
//				std::cout << "|";
//		}
//		std::cout << std::endl;
//	}
//	{
//		std::cout << " |";
//		std::string output_value = "_";
//		output_value = output_value.append((space * (size + 1) - 1) - output_value.length(), ' ');
//		output_value = output_value.append("_|");
//		std::cout << output_value << std::endl;
//	}
//}
//int validate_index(int value, int size) {
//	return value > size ? size : value;
//}
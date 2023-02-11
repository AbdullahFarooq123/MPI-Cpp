//#include <iostream>
//#include <string>
//#include<stdlib.h>
//#include<vector>
//#include<mpi.h>
//#include<conio.h>
//#include<chrono>
//using namespace std;
//class static_class
//{
//public:
//	static bool draw(uint32_t game_board, int board_size) {
//		uint32_t draw_value = pow(2, board_size * board_size) - 1;
//		return (game_board & draw_value) == draw_value;
//	}
//	static string binary(uint32_t x) {
//		std::string binary = "";
//		for (int i = 0; i < 32; ++i) {
//			if (i % 4 == 0) binary = "" + binary;
//			binary = std::to_string(x % 2) + binary;
//			x = x / 2;
//		}
//		return binary;
//	}
//	static struct vector2 {
//		int i;
//		int j;
//		int score;
//	};
//	static enum player_category { HUMAN, BOT };
//};
//class Player
//{
//public:
//	uint32_t my_board;
//	uint32_t* game_board;
//	char my_character;
//	Player* opponent;
//	static_class::player_category my_category;
//	Player(uint32_t& board, int size, char my_character, static_class::player_category my_name, uint32_t my_board) {
//		this->my_board = my_board;
//		this->size = size;
//		this->game_board = &board;
//		this->col_win = generate_win_col();
//		this->diag_main_win = generate_win_main_diag();
//		this->diag_other_win = generate_win_other_diag();
//		this->previous_moves = new static_class::vector2[size * size];
//		this->my_character = my_character;
//		this->my_category = my_name;
//
//	}
//
//	virtual static_class::vector2 move() = 0;
//	void set_opponent(Player* opponent) {
//		this->opponent = opponent;
//	}
//	void set_my_board(uint32_t my_board) {
//		this->my_board = my_board;
//	}
//	void un_make_move() {
//		static_class::vector2 last_move = previous_moves[--move_index];
//		int index = last_move.i * size + last_move.j;
//		my_board &= ~(1UL << index);
//		*game_board &= ~(1UL << index);
//	}
//	bool won() {
//		static_class::vector2 last_move = previous_moves[move_index - 1];
//		if (check_win_for_row(last_move.i))
//			return true;
//		if (check_win_for_column(last_move.j))
//			return true;
//		if (last_move.i == last_move.j)
//			return check_win_for_main_diag();
//		if (check_win_for_other_diag())
//			return true;
//		return false;
//	}
//	void make_move(int i, int j) {
//		int index = i * size + j;
//		my_board |= 1UL << index;
//		*game_board |= 1UL << index;
//		previous_moves[move_index++] = static_class::vector2{ i,j };
//	}
//	static void print_board(uint32_t board, int size, Player * x_player, Player * o_player) {
//		string board_binary = static_class::binary(board);
//		string o_board_binary = static_class::binary(o_player->my_board);
//		string x_board_binary = static_class::binary(x_player->my_board);
//		for (int i = 0; i < size; i++) {
//			for (int j = 0; j < size; j++) {
//				int index = (board_binary.length() - 1) - (i * size + j);
//				char player_character = '-';
//				if (o_board_binary[index] == '1')
//					player_character = o_player->my_character;
//				else if (x_board_binary[index] == '1')
//					player_character = x_player->my_character;
//				cout << player_character << "\t";
//			}
//			cout << endl;
//		}
//	}
//
//protected:
//	uint32_t col_win;
//	uint32_t diag_main_win;
//	uint32_t diag_other_win;
//	static_class::vector2 * previous_moves;
//	int move_index = -1;
//	int size;
//
//	bool check_win_for_row(int row) {
//		int start_index = 32 - (row * size);
//		int end_index = (start_index - size);
//		return (my_board << end_index) >> 29 == (pow(2, size) - 1);
//	}
//	bool check_win_for_column(int col) {
//		uint32_t current_win_condition = col_win * pow(2, col);
//		return (my_board & current_win_condition) == current_win_condition;
//	}
//	bool check_win_for_main_diag() {
//		return (my_board & diag_main_win) == diag_main_win;
//	}
//	bool check_win_for_other_diag() {
//		return (my_board & diag_other_win) == diag_other_win;
//	}
//	int generate_win_col() {
//		uint64_t integer_value = 0;
//		for (int i = 0; i < size; i++)
//			integer_value += pow(2, i * size);
//		return integer_value;
//	}
//	int generate_win_main_diag() {
//		uint64_t integer_value = 0;
//		for (int i = 0; i < size; i++)
//			integer_value += pow(2, i * (size + 1));
//		return integer_value;
//	}
//	int generate_win_other_diag() {
//		uint64_t integer_value = 0;
//		for (int i = 0, bit_to_start = size - 1; i < size; i++, bit_to_start += size - 1)
//			integer_value += pow(2, bit_to_start);
//		return integer_value;
//	}
//
//};
//class Human : public Player
//{
//public:
//	Human(uint32_t& board, int size, char my_character, uint32_t my_board) :Player(board, size, my_character, static_class::player_category::HUMAN, my_board) {}
//
//	static_class::vector2 move() {
//		while (true) {
//			int i, j;
//			input(i, j);
//			if (!validate_input(i, j, size, *Player::game_board)) {
//				cout << "Please enter a valid row and col" << endl;
//				continue;
//			}
//			Player::make_move(i, j);
//			return static_class::vector2{ i,j };
//		}
//	}
//
//private:
//
//	void input(int& i, int& j) {
//		cout << endl << "Please enter row and col : ";
//		cin >> i >> j;
//	}
//
//	bool validate_input(int i, int j, int size, uint32_t board) {
//		int index = (i * size + j);
//		uint64_t after_shift = (board >> index);
//		bool is_marked = 1 & after_shift;
//		return index < size * size && !is_marked;
//	}
//};
//class Bot : public Player
//{
//public:
//	Bot(uint32_t& board, int size, char my_character, uint32_t my_board) :Player(board, size, my_character, static_class::player_category::BOT, my_board) {
//	}
//
//	static_class::vector2 move() {
//		static_class::vector2 best_move = get_best_move();
//		Player::make_move(best_move.i, best_move.j);
//		return best_move;
//	}
//
//public:
//	uint32_t generate_moves() {
//		return ~*this->game_board;
//	}
//	vector<static_class::vector2> get_moves() {
//		uint32_t binary_moves = generate_moves();
//		string string_moves = static_class::binary(binary_moves);
//		vector<static_class::vector2> player_moves = vector<static_class::vector2>();
//		for (int i = 0; i < size; i++)
//			for (int j = 0; j < size; j++)
//				if (string_moves[string_moves.length() - 1 - (i * size + j)] == '1')
//					player_moves.push_back(static_class::vector2{ i,j });
//		return player_moves;
//	}
//	static_class::vector2 get_best_move(vector<static_class::vector2> received_moves = vector<static_class::vector2>(), bool use_received_moves = false, bool print = false) {
//		vector<static_class::vector2>moves = use_received_moves ? received_moves : get_moves();
//		if (moves.size() == 0)
//			return static_class::vector2{ -1,-1 };
//		int max_score = INT_MIN;
//		static_class::vector2 best_move = moves[0];
//		for (static_class::vector2 move : moves) {
//			Player::make_move(move.i, move.j);
//			int score = min_max(INT_MIN, INT_MAX, false, opponent, this);
//			if (score > max_score) {
//				max_score = score;
//				best_move = move;
//				best_move.score = score;
//			}
//			Player::un_make_move();
//		}
//		return best_move;
//	}
//	int min_max(int alpha, int beta, bool maximizing, Player * current_player, Player * opponent_player) {
//		if (current_player->won())
//			return 10 * (maximizing ? 1 : -1);
//		else if (opponent_player->won())
//			return 10 * (maximizing ? -1 : 1);
//		else if (static_class::draw(*(current_player->game_board), size))
//			return 0;
//		vector<static_class::vector2>moves = get_moves();
//		if (maximizing) {
//			int max_score = INT_MIN;
//			for (static_class::vector2 move : moves) {
//				current_player->make_move(move.i, move.j);
//				int current_score = min_max(alpha, beta, false, opponent_player, current_player);
//				current_player->un_make_move();
//				max_score = fmax(max_score, current_score);
//				alpha = fmax(alpha, max_score);
//				if (beta <= alpha)
//					break;
//			}
//			return max_score;
//		}
//		else {
//			int min_score = INT_MAX;
//			for (static_class::vector2 move : moves) {
//				current_player->make_move(move.i, move.j);
//				int current_score = min_max(alpha, beta, true, opponent_player, current_player);
//				current_player->un_make_move();
//				min_score = fmin(min_score, current_score);
//				beta = fmin(beta, min_score);
//				if (beta <= alpha)
//					break;
//			}
//			return min_score;
//		}
//	}
//};
//
//
//class Engine {
//public:
//	Engine() {
//		board = initialize_board(game_size);
//	}
//	void run() {
//		bool game_over = false, player_1_turn = true;
//		Player* player_1 = &Bot(board, game_size, 'o', board);
//		Player* player_2 = &Bot(board, game_size, 'x', board);
//		player_1->set_opponent(player_2);
//		player_2->set_opponent(player_1);
//		while (!game_over) {
//			print_full_board(board, game_size, player_1_turn, player_1, player_2);
//			static_class::vector2 move = (player_1_turn ? player_1 : player_2)->move();
//			if ((player_1_turn ? player_1 : player_2)->won()) {
//				break;
//
//			}
//			else if (static_class::draw(board, game_size)) {
//				game_over = true;
//				break;
//			}
//			player_1_turn = !player_1_turn;
//		}
//		if (game_over)
//			cout << "DRAW";
//		else
//			cout << "PLAYER " << (player_1_turn ? 1 : 2) << " WON" << endl;
//		Player::print_board(board, game_size, player_1, player_2);
//	}
//protected:
//	int game_size;
//	uint32_t board;
//
//	void print_full_board(uint32_t board, int size, bool player_1_turn, Player * player1, Player * player2) {
//		cout << "Player " << (player_1_turn ? player1->my_character : player2->my_character) << "'s TURN\n\n";
//		Player::print_board(board, size, player1, player2);
//	}
//
//	uint32_t initialize_board(int& size) {
//		size = 3;
//		return 0;
//	}
//};
//class MPI :Engine {
//public:
//	MPI() {
//		MPI_Init(NULL, NULL);
//		MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
//		MPI_Comm_size(MPI_COMM_WORLD, &process_size);
//		MPI_Parallel();
//		MPI_Finalize();
//	}
//	void MPI_Parallel() {
//		if (my_rank == 0) {
//
//			int game_size;
//			uint32_t board = initialize_board(game_size);
//			bool game_over = false, player_1_turn = true;
//
//			Player* player_1 = new Bot(board, game_size, 'o', board);
//			Player* player_2 = new Bot(board, game_size, 'x', board);
//			Player* current_player = player_1;
//			Player* opponent_player = player_2;
//
//			player_1->set_opponent(player_2);
//			player_2->set_opponent(player_1);
//			auto t_start = chrono::high_resolution_clock::now();
//
//			while (!game_over) {
//
//				//print_full_board(board, game_size, player_1_turn, player_1, player_2);
//
//				if (current_player->my_category == static_class::player_category::BOT) {
//					static_class::vector2 best_move = get_best_move(current_player, opponent_player, board);
//					current_player->make_move(best_move.i, best_move.j);
//				}
//				else
//					static_class::vector2 move = current_player->move();
//
//				if (current_player->won())
//					break;
//				else if (static_class::draw(board, game_size)) {
//					game_over = true;
//					break;
//				}
//
//				player_1_turn = !player_1_turn;
//				current_player = player_1_turn ? player_1 : player_2;
//				opponent_player = player_1_turn ? player_2 : player_1;
//			}
//			auto t_end = chrono::high_resolution_clock::now();
//			double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
//			/*if (game_over)
//				cout << "DRAW" << endl;
//			else
//				cout << "PLAYER " << (player_1_turn ? 1 : 2) << " WON" << endl;
//			Player::print_board(board, game_size, player_1, player_2);*/
//			bool break_the_loop = true;
//			for (int i = 1; i < process_size; i++)
//				MPI_Send(&break_the_loop, 1, MPI_C_BOOL, i, 0, MPI_COMM_WORLD);
//			cout << "Total Execution Time : " << elapsed_time_ms;
//		}
//		else {
//			while (true)
//			{
//				bool stop_listening;
//				MPI_Recv(&stop_listening, 1, MPI_C_BOOL, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//				if (stop_listening)
//					break;
//
//				uint32_t game_board;
//				MPI_Recv(&game_board, 1, MPI_UINT32_T, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//				
//				uint32_t current_player_board;
//				MPI_Recv(&current_player_board, 1, MPI_UINT32_T, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//				Player* current_player = new Bot(game_board, Engine::game_size, 'o', current_player_board);
//
//				uint32_t opponent_player_board;
//				MPI_Recv(&opponent_player_board, 1, MPI_UINT32_T, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//				Player* opponent_player = new Bot(game_board, Engine::game_size, 'o', opponent_player_board);
//
//				int moves_count;
//				MPI_Recv(&moves_count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//
//				int* moves = new int[moves_count];
//				MPI_Recv(moves, moves_count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//
//				vector<static_class::vector2> my_moves = convert_to_vector(moves, moves_count);
//
//				current_player->set_opponent(opponent_player);
//				opponent_player->set_opponent(current_player);
//
//				static_class::vector2 best_move = dynamic_cast<Bot*>(current_player)->get_best_move(my_moves, true,true);
//
//				int move[3]{ best_move.i,best_move.j,best_move.score };
//				MPI_Send(move, 3, MPI_INT, 0, my_rank, MPI_COMM_WORLD);
//			}
//		}
//	}
//	~MPI() {
//	}
//private:
//	int process_size;
//	int my_rank;
//
//	static_class::vector2 get_best_move(Player * current_player, Player * opponent_player, uint32_t & board) {
//		Bot bot = Bot(board, Engine::game_size, current_player->my_character, current_player->my_board);
//		bot.set_opponent(opponent_player);
//
//		vector<static_class::vector2>moves = bot.get_moves();
//		int* moves_array = convert_to_array(moves);
//
//		bool break_the_loop = false;
//		int no_of_moves_for_each_process = ceil(moves.size() / (float)process_size);
//		int start, end;
//
//		static_class::vector2 * best_moves = new static_class::vector2[process_size];
//
//		for (int process = 1; process < process_size; process++) {
//
//			compute_my_start_and_end(start, end, process, no_of_moves_for_each_process, moves.size());
//			vector<static_class::vector2> moves_to_send = copy_vector(moves, start, end);
//			int length_of_moves_to_send = moves_to_send.size() * 3;
//			int* moves_array_to_send = convert_to_array(moves_to_send);
//
//			MPI_Send(&break_the_loop, 1, MPI_C_BOOL, process, 0, MPI_COMM_WORLD);
//			MPI_Send(&board, 1, MPI_UINT32_T, process, 0, MPI_COMM_WORLD);
//			MPI_Send(&(current_player->my_board), 1, MPI_UINT32_T, process, 0, MPI_COMM_WORLD);
//			MPI_Send(&(opponent_player->my_board), 1, MPI_UINT32_T, process, 0, MPI_COMM_WORLD);
//			MPI_Send(&length_of_moves_to_send, 1, MPI_INT, process, 0, MPI_COMM_WORLD);
//			MPI_Send(moves_array_to_send, length_of_moves_to_send, MPI_INT, process, 0, MPI_COMM_WORLD);
//
//		}
//
//		compute_my_start_and_end(start, end, 0, no_of_moves_for_each_process, moves.size());
//		vector<static_class::vector2> my_moves = copy_vector(moves, start, end);
//
//		best_moves[0] = dynamic_cast<Bot*>(current_player)->get_best_move(my_moves, true);
//
//		for (int process = 1; process < process_size; process++) {
//
//			int array[3];
//
//			MPI_Recv(array, 3, MPI_INT, process, process, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//
//			static_class::vector2 move{ array[0],array[1],array[2] };
//			best_moves[process] = move;
//
//		}
//
//		static_class::vector2 best_move = best_moves[0];
//
//		for (int i = 1; i < process_size; i++) 
//			if (best_move.score < best_moves[i].score)
//				best_move = best_moves[i];
//		
//		return best_move;
//	}
//
//	int* convert_to_array(vector<static_class::vector2>moves) {
//		int* moves_array = new int[moves.size() * 3];
//		int index = 0;
//		for (static_class::vector2 move : moves) {
//			moves_array[index++] = move.i;
//			moves_array[index++] = move.j;
//			moves_array[index++] = move.score;
//
//		}
//		return moves_array;
//	}
//
//	vector<static_class::vector2> convert_to_vector(int* array, int size) {
//		vector<static_class::vector2> moves = vector<static_class::vector2>();
//		for (int i = 0; i < size / 3; i++) {
//			static_class::vector2 move{ array[i * 3 + 0], array[i * 3 + 1], array[i * 3 + 2] };
//			moves.push_back(move);
//		}
//		return moves;
//	}
//
//	void compute_my_start_and_end(int& start, int& end, int process, int size_of_value_for_each_process, int array_size) {
//		start = process * size_of_value_for_each_process;
//		if (start > array_size)
//			start = array_size;
//		end = start + size_of_value_for_each_process;
//		if (end > array_size || process == process_size - 1)
//			end = array_size;
//	}
//
//	vector<static_class::vector2> copy_vector(vector<static_class::vector2> vector_array, int start, int end) {
//		vector<static_class::vector2> moves = vector<static_class::vector2>();
//		for (int i = start; i < end; i++) {
//			moves.push_back(vector_array[i]);
//		}
//		return moves;
//	}
//};
//int main() {
//	//Sequential Run
//	//Engine().run();
//	//Parallel Run
//	MPI();
//}
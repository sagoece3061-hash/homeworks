/** 
 * Title: Graphs 
 * Author: Sevval Ece Candogan 
 * ID: 22402843
 * Section: 1 
 * Homework: 4 
 * Description: Solves 4x4 and 3x3 puzzles
 */

#include <iostream>
#include <cmath>
#include "MyList.h"

using namespace std;

typedef unsigned long long ull;

struct dub{
    int nbhd[4] = {-1, -1, -1, -1}; // South, North, West, East
    int number_of_nhbrs = 0;
};

int factorial[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
const char move_chars[4] = {'D', 'U', 'L', 'R'};

char optimal_path[100];
int optimal_path_length = 0;
int target_positions[16];

int get_tile_at(ull state, int index) {
    return (state >> ((15 - index) * 4)) & 0xF;
}

void precompute_target(ull goal_state) {
    for (int i = 0; i < 16; i++) {
        int tile = get_tile_at(goal_state, i);
        target_positions[tile] = i;
    }
}

int get_manhattan_dist(ull current_state) {
    int total_distance = 0;
    for (int i = 0; i < 16; i++) {
        int tile = get_tile_at(current_state, i);
        if (tile != 0) {
            int current_row = i / 4;
            int current_col = i % 4;

            int target_idx = target_positions[tile];
            int target_row = target_idx / 4;
            int target_col = target_idx % 4;

            total_distance += std::abs(current_row - target_row) + std::abs(current_col - target_col);
        }
    }
    return total_distance;
}

ull convert_to_ull(){
    ull num = 0;
    ull input;

    for (int i = 0; i < 16; i++){
        cin >> input;
        num |= (input << ((15 - i) * 4));
    }
    return num;
}

int cantor_arr_to_idx(const int arr[9]){
    int num = 0;
    for(int i = 0; i < 9; i++){
        int count = 0;
        for(int j = i + 1; j < 9; j++)
            if(arr[i] > arr[j]) count++;
        num = num + factorial[8 - i] * count;
    }
    return num;
}

void cantor_idx_to_arr(int arr[9], int idx){
    int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8}; 
    int numbers_size = 9;
    int arr_idx = 0;

    for(int i = 8; i >= 0; i--){
        int factorial_i = factorial[i];
        int quotient = idx / factorial_i;
        int remainder = idx % factorial_i;

        arr[arr_idx++] = numbers[quotient];

        for(int j = quotient; j < numbers_size - 1; j++){
            numbers[j] = numbers[j + 1];
        }
        numbers_size--;
        idx = remainder;
    }
}

void init_nbhd(dub* node, int idx){
    int arr[9];
    cantor_idx_to_arr(arr, idx);
    int idx_of_zero = 0;

    for(int i = 0; i < 9; i++){
        if(arr[i] == 0){
            idx_of_zero = i;
            break;
        }
    }

    int north_of_zero = (idx_of_zero / 3 == 0) ? -1 : (idx_of_zero - 3);
    int south_of_zero = (idx_of_zero / 3 == 2) ? -1 : (idx_of_zero + 3);
    int west_of_zero = (idx_of_zero % 3 == 0) ? -1 : (idx_of_zero - 1);
    int east_of_zero = (idx_of_zero % 3 == 2) ? -1 : (idx_of_zero + 1);

    if(south_of_zero != -1){
        arr[idx_of_zero] = arr[south_of_zero];
        arr[south_of_zero] = 0;

        node->nbhd[0] = cantor_arr_to_idx(arr);

        arr[south_of_zero] = arr[idx_of_zero];
        arr[idx_of_zero] = 0;
        
        node->number_of_nhbrs++;
    } 
    else node->nbhd[0] = -1;

    if(north_of_zero != -1){
        arr[idx_of_zero] = arr[north_of_zero];
        arr[north_of_zero] = 0;
        node->nbhd[1] = cantor_arr_to_idx(arr);
        arr[north_of_zero] = arr[idx_of_zero];
        arr[idx_of_zero] = 0;
        node->number_of_nhbrs++;
    } 
    else node->nbhd[1] = -1;

    if(west_of_zero != -1){
        arr[idx_of_zero] = arr[west_of_zero];
        arr[west_of_zero] = 0;

        node->nbhd[2] = cantor_arr_to_idx(arr);

        arr[west_of_zero] = arr[idx_of_zero];
        arr[idx_of_zero] = 0;

        node->number_of_nhbrs++;
    } 
    else node->nbhd[2] = -1;

    if(east_of_zero != -1){
        arr[idx_of_zero] = arr[east_of_zero];
        arr[east_of_zero] = 0;

        node->nbhd[3] = cantor_arr_to_idx(arr);

        arr[east_of_zero] = arr[idx_of_zero];
        arr[idx_of_zero] = 0;

        node->number_of_nhbrs++;
    } 
    else node->nbhd[3] = -1;
}

void bfs_3(dub* graph, int initial_idx, int final_idx){
    if (initial_idx == final_idx) {
        std::cout << 0 << "\n\n";
        return;
    }

    int* queue = new int[362880];
    int queue_head = 0;
    int queue_tail = 0;

    int* visited_arr = new int[362880](); 

    visited_arr[initial_idx] = 1;   
    queue[queue_tail++] = initial_idx;

    bool reached = false;

    while (queue_head < queue_tail) {
        int w = queue[queue_head++];

        for (int i = 0; i < 4; i++) {
            int neighbor = graph[w].nbhd[i];

            if(neighbor != -1 && visited_arr[neighbor] == 0){
                visited_arr[neighbor] = visited_arr[w] + 1;
                
                if(neighbor == final_idx) {
                    reached = true;
                    break; 
                }
                
                queue[queue_tail++] = neighbor; 
            }
        }
        if (reached) break;
    }

    if (reached) {
        std::cout << visited_arr[final_idx] - 1 << "\n";
        
        char path[100];
        int path_len = 0;
        int curr = final_idx;

        while (curr != initial_idx) {
            for (int i = 0; i < 4; i++) {
                int prev = graph[curr].nbhd[i];
                if (prev != -1 && visited_arr[prev] == visited_arr[curr] - 1) {
                    for (int j = 0; j < 4; j++) {
                        if (graph[prev].nbhd[j] == curr) {
                            path[path_len++] = move_chars[j];
                            break;
                        }
                    }
                    curr = prev;
                    break;
                }
            }
        }

        for (int i = path_len - 1; i >= 0; i--) {
            std::cout << path[i];
        }
        std::cout << "\n";

    } else {
        std::cout << "UNREACHABLE\n";
    }

    delete[] queue;
    delete[] visited_arr;
}

bool is_solvable(ull start, ull goal) {
    int start_inv = 0, goal_inv = 0;
    int start_zero_row = 0, goal_zero_row = 0;
    int start_arr[16], goal_arr[16];

    for (int i = 0; i < 16; i++) {
        start_arr[i] = get_tile_at(start, i);
        goal_arr[i] = get_tile_at(goal, i);
        if (start_arr[i] == 0) start_zero_row = i / 4;
        if (goal_arr[i] == 0) goal_zero_row = i / 4;
    }

    for (int i = 0; i < 16; i++) {
        if (start_arr[i] != 0) {
            for (int j = i + 1; j < 16; j++) {
                if (start_arr[j] != 0 && start_arr[i] > start_arr[j]) start_inv++;
            }
        }
        if (goal_arr[i] != 0) {
            for (int j = i + 1; j < 16; j++) {
                if (goal_arr[j] != 0 && goal_arr[i] > goal_arr[j]) goal_inv++;
            }
        }
    }
    return ((start_inv + start_zero_row) % 2) == ((goal_inv + goal_zero_row) % 2);
}

int generate_neighbors_4x4(ull state, ull neighbors[], char moves[]) {
    int count = 0;
    int zero_idx = -1;
    for (int i = 0; i < 16; i++) {
        if (get_tile_at(state, i) == 0) {
            zero_idx = i;
            break;
        }
    }
    int r = zero_idx / 4;
    int c = zero_idx % 4;

    if (r < 3) { // South (Down)
        ull tile_val = get_tile_at(state, zero_idx + 4);
        ull new_state = state & ~(0xFULL << ((15 - (zero_idx + 4)) * 4));
        new_state |= (tile_val << ((15 - zero_idx) * 4));
        neighbors[count] = new_state; moves[count++] = 'D';
    }
    if (r > 0) { // North (Up)
        ull tile_val = get_tile_at(state, zero_idx - 4);
        ull new_state = state & ~(0xFULL << ((15 - (zero_idx - 4)) * 4));
        new_state |= (tile_val << ((15 - zero_idx) * 4));
        neighbors[count] = new_state; moves[count++] = 'U';
    }
    if (c > 0) { // West (Left)
        ull tile_val = get_tile_at(state, zero_idx - 1);
        ull new_state = state & ~(0xFULL << ((15 - (zero_idx - 1)) * 4));
        new_state |= (tile_val << ((15 - zero_idx) * 4));
        neighbors[count] = new_state; moves[count++] = 'L';
    }
    if (c < 3) { // East (Right)
        ull tile_val = get_tile_at(state, zero_idx + 1);
        ull new_state = state & ~(0xFULL << ((15 - (zero_idx + 1)) * 4));
        new_state |= (tile_val << ((15 - zero_idx) * 4));
        neighbors[count] = new_state; moves[count++] = 'R';
    }
    return count;
}

char get_opposite(char m) {
    if (m == 'U') return 'D';
    if (m == 'D') return 'U';
    if (m == 'L') return 'R';
    if (m == 'R') return 'L';
    return ' ';
}

int ida_search(ull current, ull goal, int g, int limit, char prev_move) {
    int h = get_manhattan_dist(current);
    int f = g + h;
    
    if (f > limit) return f;
    if (h == 0) { 
        optimal_path_length = g;
        return -1;
    }
    
    int min_limit = 999999;
    ull neighbors[4];
    char moves[4];
    int num_neighbors = generate_neighbors_4x4(current, neighbors, moves);
    
    for (int i = 0; i < num_neighbors; i++) {
        if (moves[i] == get_opposite(prev_move)) continue;
        
        int res = ida_search(neighbors[i], goal, g + 1, limit, moves[i]);
        if (res == -1) {
            optimal_path[g] = moves[i];
            return -1;
        }
        if (res < min_limit) min_limit = res;
    }
    return min_limit;
}

void ida_star(ull start, ull goal) {
    if (!is_solvable(start, goal)) {
        cout << "UNREACHABLE\n";
        return;
    }
    
    precompute_target(goal);
    int limit = get_manhattan_dist(start);
    
    while (true) {
        int res = ida_search(start, goal, 0, limit, ' ');
        if (res == -1) {
            cout << optimal_path_length << "\n";
            for (int i = 0; i < optimal_path_length; i++) cout << optimal_path[i];
            cout << "\n";
            return;
        }
        limit = res;
    }
}

int main(int argc, char const *argv[]){
    int dim;
    cin >> dim;

    if(dim == 3){
        dub* graph = new dub[362880];
    
        for(int i = 0; i < 362880; i++){
            init_nbhd(graph + i, i);
        }

        int start_arr[9];
        int finish_arr[9];

        for (int i = 0; i < 9; i++) cin >> start_arr[i];
        for (int i = 0; i < 9; i++) cin >> finish_arr[i];

        int start_idx = cantor_arr_to_idx(start_arr);
        int finish_idx = cantor_arr_to_idx(finish_arr);
        
        bfs_3(graph, start_idx, finish_idx);
    
        delete[] graph;
    }
    else if(dim == 4){
        ull start_state = convert_to_ull();
        ull goal_state = convert_to_ull();
        ida_star(start_state, goal_state);
    }

    return 0;
}
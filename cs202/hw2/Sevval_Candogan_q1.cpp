/** 
 * Title: AVL Trees and Heaps 
 * Author: Sevval Ece Candogan
 * ID: 22402843
 * Section: 1 
 * Homework: 2 
 * Description: processes tasks from given input file
 */
#include <fstream>
#include <iostream>
#include "Heap.h"
#include "Nodes.h"
#include <chrono>

int main(int argc, char const *argv[]){
    auto start = std::chrono::high_resolution_clock::now();
    if(argc < 2){
        std::cerr << "Error: NO INPUT\n";
        return 1;
    }
    std::string filename = argv[1];
    std::ifstream istrm(filename);

    Heap<TaskNode>* wait_queue = new Heap<TaskNode>();
    Heap<ProcessorNode>* processor_timeline = new Heap<ProcessorNode>();
    int current_time = 0;   // T

    if (!istrm.is_open())
        std::cout << "failed to open " << filename << '\n';
    else{
        int number_of_tasks;
        int number_of_processors;

        int number_of_avaliable_processors;

        istrm >> number_of_tasks;
        istrm >> number_of_processors;

        number_of_avaliable_processors = number_of_processors;

        for(int i = 0; i < number_of_tasks; i++){
            int arrival_time;
            int priority;
            int duration;

            istrm >> arrival_time;
            istrm >> duration;
            istrm >> priority;

            current_time = arrival_time;

            while(processor_timeline->items_size > 0 && processor_timeline->items[0].end_time < arrival_time){

                int event_time = processor_timeline->items[0].end_time;
                
                while(processor_timeline->items_size > 0 && processor_timeline->items[0].end_time == event_time){
                    ProcessorNode finished = processor_timeline->items[0];
                    processor_timeline->heapDeleteFirst();
                    number_of_avaliable_processors++;
                    std::cout << "Process " << finished.number << ": Start=" << finished.start_time << ", Finish=" << finished.end_time << "\n";
                }
                
                current_time = event_time;

                while(number_of_avaliable_processors > 0 && wait_queue->items_size > 0){
                    TaskNode next_task = wait_queue->items[0];
                    wait_queue->heapDeleteFirst();
                    
                    ProcessorNode new_process(next_task.number, current_time, current_time + next_task.duration);
                    processor_timeline->heapInsert(new_process);
                    number_of_avaliable_processors--;
                }
            }

            current_time = arrival_time;
            TaskNode new_task(i, arrival_time, duration, priority);
            wait_queue->heapInsert(new_task);

            while(processor_timeline->items_size > 0 && processor_timeline->items[0].end_time == current_time){
                ProcessorNode finished = processor_timeline->items[0];
                processor_timeline->heapDeleteFirst();
                number_of_avaliable_processors++;
                std::cout << "Process " << finished.number << ": Start=" << finished.start_time << ", Finish=" << finished.end_time << "\n";
            }

            while(number_of_avaliable_processors > 0 && wait_queue->items_size > 0){
                TaskNode next_task = wait_queue->items[0];
                wait_queue->heapDeleteFirst();
                
                ProcessorNode new_process(next_task.number, current_time, current_time + next_task.duration);
                processor_timeline->heapInsert(new_process);
                number_of_avaliable_processors--;
            }
        }
    
        while(processor_timeline->items_size > 0){
            ProcessorNode finished = processor_timeline->items[0];
            processor_timeline->heapDeleteFirst();
            number_of_avaliable_processors++;

            current_time = finished.end_time;
            std::cout << "Process " << finished.number << ": Start=" << finished.start_time << ", Finish=" << finished.end_time << "\n";

            if(wait_queue->items_size > 0){
                TaskNode next_task = wait_queue->items[0];
                wait_queue->heapDeleteFirst();

                ProcessorNode new_process(next_task.number, current_time, current_time + next_task.duration);
                processor_timeline->heapInsert(new_process);
                number_of_avaliable_processors--;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Total program execution time: " << elapsed.count() << " ms\n";
    }

    return 0;
}
 
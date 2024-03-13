#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <cstdlib> // for std::atoi
#include <chrono>
#include <functional>
#include <algorithm>

const int TIME_TO_REACH_TOOLS = 1;
const int TIME_TO_COMPLETE_TASK = 5;

std::mutex Tool0;
std::mutex Tool1;
std::mutex Tool2;
std::mutex Tool3;
std::mutex Tool4;

std::mutex coutMutex; //double check if this is okay!!!

void completeTask(int id, std::mutex& left, std::mutex& right)
{
    while (true) 
    {
        if (left.try_lock()) {
            if (right.try_lock()) 
            {
                {
                    std::lock_guard<std::mutex> lock(coutMutex); // Lock coutMutex for safe printing
                    std::cout << "Robot " << id << " is collecting data.\n";
                }

                // Simulate time to reach for tools
                std::this_thread::sleep_for(std::chrono::seconds(TIME_TO_REACH_TOOLS));

                {
                    std::lock_guard<std::mutex> lock(coutMutex); // Lock coutMutex for safe printing
                    std::cout << "Robot " << id << " acquired tools and starts performing a task.\n";
                }

                // Simulate completing task and returning tools
                std::this_thread::sleep_for(std::chrono::seconds(TIME_TO_COMPLETE_TASK));

                {
                    std::lock_guard<std::mutex> lock(coutMutex); // Lock coutMutex for safe printing
                    std::cout << "Robot " << id << " finished the task and returning the tools.\n";
                }

                // Unlock tools
                right.unlock();
                left.unlock();

                break; // Exit the loop once the task is completed
            }
            else 
            {
                left.unlock(); // Release the left tool lock if the right tool is not available
            }
        }
  
    }
}

int main()
{
	//duration counter begin
	auto startTime = std::chrono::high_resolution_clock::now();
		
	// Create threads for each robot and assign tasks
	std::thread Task1(completeTask, 0, std::ref(Tool0), std::ref(Tool4)); //robot 0
	std::thread Task2(completeTask, 1, std::ref(Tool1), std::ref(Tool0)); //robot 1
	std::thread Task3(completeTask, 2, std::ref(Tool2), std::ref(Tool1)); //robot 2
	std::thread Task4(completeTask, 3, std::ref(Tool3), std::ref(Tool2)); //robot 3
	std::thread Task5(completeTask, 4, std::ref(Tool4), std::ref(Tool3)); //robot 4

	// Join the threads with the main thread
	Task1.join();
	Task2.join();
	Task3.join();
	Task4.join();
	Task5.join();

	//duration counter end
	auto stopTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds > (stopTime - startTime);
	std::cout << "Duration: " << duration.count() << " seconds.\n";

	return 0;
}


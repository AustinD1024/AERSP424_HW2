#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <cstdlib> // for std::atoi
#include <chrono>
#include <functional>
#include <algorithm>

const int NUM_ROBOTS = 5;
const int NUM_TOOLS = 5;
const int TIME_TO_REACH_TOOLS = 1;
const int TIME_TO_COMPLETE_TASK = 5;

std::mutex toolMutex[NUM_TOOLS];

void completeTask(int id)
{


	//int left_tool = id;		 //index of left tool
	//int right_tool = NUM_TOOLS - 1 - id; //index of right tool


	std::lock(toolMutex[id], toolMutex[NUM_TOOLS - 1 - id]);

	
	int left_tool = id;		 //index of left tool
	int right_tool = NUM_TOOLS - 1 - id; //index of right tool

	std::cout << "Robot " << id << " is collecting data.\n";

	//simulate time to reach for tools
	std::this_thread::sleep_for(std::chrono::seconds(TIME_TO_REACH_TOOLS));
	std::cout << "Robot " << id << " acquired tools and starts performing a task.\n";

	//simulate completing task and returning tools
	std::this_thread::sleep_for(std::chrono::seconds(TIME_TO_COMPLETE_TASK));
	
	std::cout << "Robot " << id << " finished the task and returning the tools.\n";

	//unlock tools
	toolMutex[left_tool].unlock();
	toolMutex[right_tool].unlock();

}


int main()
{
	//duration counter begin
	auto startTime = std::chrono::high_resolution_clock::now();

	const int numTasks = NUM_ROBOTS; //number of tasks to be completed
	
	std::vector<std::thread> TasksToComplete(numTasks);
	
	// Create threads for each robot and assign tasks
	for (int i = 0; i < numTasks; i++) 
	{
		TasksToComplete[i] = std::thread(completeTask, i);
	}
	
	for (int i = 0; i < numTasks; i++) 
	{
        TasksToComplete[i].join();
    }

	//duration counter end
	auto stopTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds > (stopTime - startTime);
	std::cout << "Duration: " << duration.count() << " seconds.\n";

	return 0;
}

////////////////////////////////////////////////////////Good stuff from CHAT GPT////////////////////////////////////////////////////////////////
//#include <iostream>
//#include <thread>
//#include <vector>
//#include <mutex>
//#include <cstdlib> // for std::atoi
//
//const int NUM_ROBOTS = 5;
//const int NUM_TOOLS = 5;
//const int TIME_TO_REACH_TOOLS = 1;
//const int TIME_TO_COMPLETE_TASK = 5;
//
//std::mutex toolMutex[NUM_TOOLS];
//std::mutex coutMutex;
//
//void robotTask(int robotId, int taskId) {
//    int tool1 = robotId % NUM_TOOLS;
//    int tool2 = (robotId + 1) % NUM_TOOLS;
//
//    // Collect task
//    {
//        std::lock_guard<std::mutex> coutLock(coutMutex);
//    }
//
//    // Reach and grab tools
//    std::this_thread::sleep_for(std::chrono::seconds(TIME_TO_REACH_TOOLS));
//
//    // Acquire the tools
//    std::unique_lock<std::mutex> lock1(toolMutex[tool1]);
//    std::unique_lock<std::mutex> lock2(toolMutex[tool2]);
//
//    // Begin performing the task
//    {
//        std::lock_guard<std::mutex> coutLock(coutMutex);
//        std::cout << "Robot " << robotId << " aquired tools and starts performing a task. " << std::endl;
//    }
//
//    // Perform the task
//    std::this_thread::sleep_for(std::chrono::seconds(TIME_TO_COMPLETE_TASK));
//
//    // Return the tools to their original location
//    lock1.unlock();
//    lock2.unlock();
//
//    // Finish the task
//    {
//        std::lock_guard<std::mutex> coutLock(coutMutex);
//        std::cout << "Robot " << robotId << " finished the task and returning the tools." << std::endl;
//    }
//}
//
//int main() {
//    int numTasks;
//    std::cout << "Enter the total number of tasks to be completed: ";
//    std::cin >> numTasks;
//
//
//
//    std::vector<std::thread> threads;
//
//    // Create threads for each robot and assign tasks
//    for (int i = 0; i < numTasks; ++i) {
//        int robotId = i % NUM_ROBOTS; // Assign tasks in a circular manner to robots
//        threads.emplace_back(robotTask, robotId, i + 1); // i + 1 to start tasks from 1
//    }
//
//    // Join threads
//    for (auto& thread : threads) {
//        thread.join();
//    }
//
//    return 0;
//}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
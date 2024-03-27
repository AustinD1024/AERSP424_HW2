#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <queue>

// Number of aircrafts and maximum size of the traffic pattern and queue
int numAircrafts = 10;
int maxTrafficPattern = 3;
int currentTrafficPattern = 0;
bool firstAircraft = true;

// Mutexes and condition variables for synchronization
std::mutex coutMutex;             // Mutex for cout
std::mutex trafficPatternMutex;   // Mutex for accessing the traffic pattern
std::mutex ATCMutex;              // Mutex for ATC communication
std::mutex runwayMutex;           // Mutex for runway access
std::condition_variable cv;       // For signaling ATC status change
bool ATCSleeping = true;          // Initially ATC is sleeping
int aircraftTalkingToATC = 0;     // Count of aircraft talking to ATC
std::condition_variable runwayCV; // For signaling runway status change
bool runwayClear = true;          // Runway status

// Queue to hold aircraft waiting to enter the traffic pattern
std::queue<int> trafficPatternQueue;

// Function to handle aircraft arrivals
void aircraftArrival(int id)
{
    bool isDiverted = false;

    // Check if the traffic pattern is full
    {
        std::lock_guard<std::mutex> lock(trafficPatternMutex);
        if (runwayClear && firstAircraft)
        {
            firstAircraft = false;
        }
        else if (currentTrafficPattern + trafficPatternQueue.size() >= maxTrafficPattern)
        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "Aircraft #" << id << " requesting landing.\n";
            std::cout << "Approach pattern full. Aircraft #" << id << " redirected to another airport.\n";
            std::cout << "Aircraft #" << id << " flying to another airport.\n";
            isDiverted = true;
        }
        else if (currentTrafficPattern >= maxTrafficPattern)
        {
            // If traffic pattern is full, enqueue the aircraft
            trafficPatternQueue.push(id);
            return; // Aircraft added to the queue
        }
        else
        {
            currentTrafficPattern++;
        }
    }

    // If diverted, skip the rest of the logic
    if (isDiverted) {
        return;
    }

    bool needsDiversion = false;

    // Check with ATC
    {
        std::unique_lock<std::mutex> lock(ATCMutex);
        // Wait until ATC is not sleeping or no aircraft is talking to ATC
        cv.wait(lock, [] { return !ATCSleeping || aircraftTalkingToATC == 0; });
        if (!ATCSleeping && currentTrafficPattern > maxTrafficPattern)
        {
            needsDiversion = true; // Traffic pattern is full, need diversion
        }
        else
        {
            aircraftTalkingToATC++; // Increment the count of aircraft talking to ATC
            ATCSleeping = false; // ATC is now awake
        }
    }

    // If diversion needed, divert the aircraft
    if (needsDiversion)
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "Aircraft #" << id << " requesting landing.\n";
        std::cout << "Approach pattern full. Aircraft #" << id << " redirected to another airport.\n";
        std::cout << "Aircraft #" << id << " flying to another airport.\n";
    }
    else
    {
        // Otherwise, proceed with landing

        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "Aircraft #" << id << " requesting landing.\n";
        }

        // Land the aircraft
        {
            std::unique_lock<std::mutex> lock(runwayMutex);
            runwayCV.wait(lock, [] { return runwayClear; });
            runwayClear = false;
            std::cout << "Aircraft #" << id << " is cleared to land.\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "Runway is now free.\n";
        }
        {
            std::lock_guard<std::mutex> lock(runwayMutex);
            runwayClear = true;
            runwayCV.notify_one(); // Notify that runway status changed
        }

        // Release ATC
        {
            std::lock_guard<std::mutex> lock(ATCMutex);
            aircraftTalkingToATC--; // Decrement the count of aircraft talking to ATC
            if (aircraftTalkingToATC == 0)
            {
                ATCSleeping = true; // ATC goes to sleep if no aircraft is talking
                cv.notify_one(); // Notify that ATC status changed
            }
        }
    }

    {
        std::lock_guard<std::mutex> lock(trafficPatternMutex);
        currentTrafficPattern--; // Decrease the count of aircraft in traffic pattern
        // If queue is not empty, allow the next aircraft to enter the traffic pattern
        if (!trafficPatternQueue.empty())
        {
            int nextAircraftId = trafficPatternQueue.front();
            trafficPatternQueue.pop();
            currentTrafficPattern++;
            cv.notify_one(); // Notify that an aircraft can proceed
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "Aircraft #" << nextAircraftId << " enters the traffic pattern from the queue.\n";
        }
    }
}

int main()
{
    auto startTime = std::chrono::high_resolution_clock::now();

    // Create threads for each aircraft arrival
    std::thread Aircraft1(aircraftArrival, 1);
    std::thread Aircraft2(aircraftArrival, 2);
    std::thread Aircraft3(aircraftArrival, 3);
    std::thread Aircraft4(aircraftArrival, 4);
    std::thread Aircraft5(aircraftArrival, 5);
    std::thread Aircraft6(aircraftArrival, 6);
    std::thread Aircraft7(aircraftArrival, 7);
    std::thread Aircraft8(aircraftArrival, 8);
    std::thread Aircraft9(aircraftArrival, 9);
    std::thread Aircraft10(aircraftArrival, 10);

    // Join all aircraft threads
    Aircraft1.join();
    Aircraft2.join();
    Aircraft3.join();
    Aircraft4.join();
    Aircraft5.join();
    Aircraft6.join();
    Aircraft7.join();
    Aircraft8.join();
    Aircraft9.join();
    Aircraft10.join();

    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stopTime - startTime);
    std::cout << "Duration: " << duration.count() << " seconds.\n";

    return 0;
}

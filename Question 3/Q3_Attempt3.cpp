#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

int numAircrafts = 10;
int maxTrafficPattern = 3;
int currentTrafficPattern = 0;
bool runwayClear = true;
bool firstAircraft = true;
std::mutex runway;
std::mutex coutMutex;
std::mutex trafficPatternMutex;
std::mutex ATCMutex;
std::condition_variable cv; // For signaling ATC status change
bool ATCSleeping = true; // Initially ATC is sleeping
int aircraftTalkingToATC = 0;

void aircraftArrival(int id)
{
    {
        std::lock_guard<std::mutex> lock(trafficPatternMutex);
        if (runwayClear && firstAircraft)
        {
            firstAircraft = false;
        }
        else
        {
            currentTrafficPattern++;
        }
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

    if (needsDiversion)
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "Aircraft #" << id << " requesting landing.\n";
        std::cout << "Approach pattern full. Aircraft #" << id << " redirected to another airport.\n";
        std::cout << "Aircraft #" << id << " flying to another airport.\n";
    }
    else
    {
        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "Aircraft #" << id << " requesting landing.\n";
        }

        // Land the aircraft
        runway.lock();
        runwayClear = false;
        std::cout << "Aircraft #" << id << " is cleared to land.\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "Runway is now free.\n";
        }
        runwayClear = true;
        runway.unlock();

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

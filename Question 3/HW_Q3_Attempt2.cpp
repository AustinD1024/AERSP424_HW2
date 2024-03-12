#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

const int MAX_TRAFFIC = 3;
const int NUM_AIRCRAFT = 10;
int Aircraft_in_traffic = 0; //initial value
int duration = 0; //initial value
bool isATC_busy = false; //initial value
bool runway_free = true;
std::mutex mtx; // Mutex for thread synchronization

void pilot(int id) 
{
    std::cout << "Aircraft #" << id << " requesting landing.\n";

    if (Aircraft_in_traffic < MAX_TRAFFIC)
    {
        Aircraft_in_traffic++;
        if (runway_free == true)
        {
            mtx.lock();
            std::cout << "Aircraft #" << id << " is cleared to land.\n";

        }
    }
    if (Aircraft_in_traffic == MAX_TRAFFIC)
    {
        std::cout << "Approach pattern full. Aircraft #" << id << " redirected to another airport.\n";
        mtx.unlock();

    }
    mtx.unlock();

    


    if (Aircraft_in_traffic <= MAX_TRAFFIC && runway_free == true)
    {
        mtx.lock();
        std::cout << "Aircraft #" << id << " is cleared to land.\n";
        runway_free = false;
        duration++;
        std::cout << "Runway is now free.\n";
        runway_free = true;
        mtx.unlock();
        Aircraft_in_traffic--;
    }
    if (Aircraft_in_traffic > MAX_TRAFFIC)
    {
        std::cout << "Approach pattern full. Aircraft #" << id << " redirected to another airport.\n";
    }


}

int traffic_check()
{

}

int main()
{
    std::thread pilots[NUM_AIRCRAFT];
        for (int i = 0; i < NUM_AIRCRAFT; i++) 
        {
            pilots[i] = std::thread(pilot, i + 1);
        }

}
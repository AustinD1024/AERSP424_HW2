//#include <iostream>
//#include <thread>
//#include <mutex>
//#include <chrono>
//
//int numAircrafts = 10;
//int maxTrafficPattern = 3;
//int currentTrafficPattern = 0;
//bool ATCSleeping = true;
//bool runwayClear = true;
//bool firstAircraft = true;
//std::mutex runway;
//std::mutex coutMutex;
//std::mutex trafficPatternMutex;
//
//
//void aircraftArrival(int id) 
//{
//
//    //Check if first aircraft. Will be free to land.
//    {
//        std::lock_guard<std::mutex> lock(trafficPatternMutex);
//        if (runwayClear && firstAircraft)
//        {
//            firstAircraft = false;
//        }
//        else 
//        {
//            currentTrafficPattern++;
//        }
//    }
//
//
//    //Actions aircraft can take if free to land.
//    if (currentTrafficPattern <= maxTrafficPattern)
//    {
//        {
//            std::lock_guard<std::mutex> lock(coutMutex); // Lock coutMutex for safe printing
//            std::cout << "Aircraft #" << id << " requesting landing.\n";
//        }
//
//        runway.lock();
//        runwayClear = false;
//        {
//            std::lock_guard<std::mutex> lock(coutMutex);
//            std::cout << "Aircraft #" << id << " is cleared to land.\n";
//        }
//        //runwayClear = false; // Set runwayClear flag
//        std::this_thread::sleep_for(std::chrono::seconds(1));
//        {
//            std::lock_guard<std::mutex> lock(coutMutex);
//            std::cout << "Runway is now free.\n";
//        }
//        runwayClear = true; // Reset runwayClear flag
//        runway.unlock(); // Unlock runway
//    }
//    
//    //Diverted if traffic pattern is full.
//    else //(currentTrafficPattern > maxTrafficPattern)
//    {
//        {
//            std::lock_guard<std::mutex> lock(coutMutex); // Lock coutMutex for safe printing
//            std::cout << "Aircraft #" << id << " requesting landing.\n";
//            std::cout << "Approach pattern full. Aircraft #" << id << " redirected to another airport.\n";
//            std::cout << "Aircraft #" << id << " flying to another airport.\n";
//        }
//
//        { 
//            std::lock_guard<std::mutex> lock(trafficPatternMutex);
//            currentTrafficPattern--;
//        }
//        return;
//    }
//
//
//}
//
//void ATC() 
//{
//    
//}
//
//int main() 
//{
//
//    //duration counter begin
//    auto startTime = std::chrono::high_resolution_clock::now();
//
//
//    std::thread Aircraft1(aircraftArrival, 1);
//    std::thread Aircraft2(aircraftArrival, 2);
//    std::thread Aircraft3(aircraftArrival, 3);
//    std::thread Aircraft4(aircraftArrival, 4);
//    std::thread Aircraft5(aircraftArrival, 5);
//    std::thread Aircraft6(aircraftArrival, 6);
//    std::thread Aircraft7(aircraftArrival, 7);
//    std::thread Aircraft8(aircraftArrival, 8);
//    std::thread Aircraft9(aircraftArrival, 9);
//    std::thread Aircraft10(aircraftArrival, 10);
//
//
//    Aircraft1.join();
//    Aircraft2.join();
//    Aircraft3.join();
//    Aircraft4.join();
//    Aircraft5.join();
//    Aircraft6.join();
//    Aircraft7.join();
//    Aircraft8.join();
//    Aircraft9.join();
//    Aircraft10.join();
//
//
//    //duration counter end
//    auto stopTime = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::seconds> (stopTime - startTime);
//    std::cout << "Duration: " << duration.count() << " seconds.\n";
//
//    return 0;
//}
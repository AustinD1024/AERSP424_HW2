//#include <iostream>
//#include <thread>
//#include <mutex>
//#include <chrono>
//
//const int MAX_TRAFFIC = 3;
//const int NUM_AIRCRAFT = 10;
//int Aircraft_in_traffic = 0; //initial value
//int duration = 0; //initial value
//bool isATC_busy = false; //initial value
//std::mutex mtx; // Mutex for thread synchronization
//
//void pilot(int id) {
//    std::cout << "Aircraft #" << id << "requesting landing.\n";
//    while (true) {
//        mtx.lock();
//        Aircraft_in_traffic++;
//        // Check if traffic pattern is full
//        if (Aircraft_in_traffic == MAX_TRAFFIC) 
//        {
//            std::cout << "Approach pattern full. Aircraft #" << id << " redirected to another airport\n";
//            mtx.unlock();
//            break;
//            
//        }
//        isATC_busy = true;
//        mtx.unlock();
//    }
//    //mtx.unlock();
//    // Simulate landing
//    //std::this_thread::sleep_for(std::chrono::seconds(1));
//    mtx.lock();
//    std::cout << "Runway is now free.\n";
//    Aircraft_in_traffic--;
//    isATC_busy = false;
//    mtx.unlock();
//}
//
//int main() {
//    // Spawn 10 pilot threads
//    std::thread pilots[NUM_AIRCRAFT];
//    for (int i = 0; i < NUM_AIRCRAFT; i++) {
//        pilots[i] = std::thread(pilot, i + 1);
//    }
//
//    // Wait for all threads to finish
//    for (int i = 0; i < 10; i++) {
//        pilots[i].join();
//    }
//
//    return 0;
//}

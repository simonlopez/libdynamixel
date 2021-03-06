/*
 * Demo 5 : discrete static walk  
 */
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <math.h>
#include <string.h>
#include <sys/time.h>

#include <dynamixel/dynamixel.hpp>

#include "actuator.hpp"
#include "monitor.hpp"

#define SAMPLING_FREQUENCY 20
#define SPEED 150
#define READ_DURATION 0.02f
#define VERBOSE 0

using namespace dynamixel;
    
void usage(char * prog);

int main(int argc, char **argv) {

    // Getopt ///////////////////////////////////
    char controllerDevice[256] = "/dev/ttyUSB0";
    int c;
     
    opterr = 0;

    while ((c = getopt (argc, argv, "d:")) != -1) {
        switch (c) {
            case 'd':
                strcpy(controllerDevice, optarg);
                break;
            case '?':
                usage(argv[0]);
                return 1;
        }
    }

    // Dynamixel //////////////////////////////////////////////////////////////////////////////////
        
    // Init ///////////////////////////////////////////////////////////////
   
    // Set device file
    Usb2Dynamixel controller(controllerDevice);

    // Scan actuators IDs
    controller.scan_ax12s();
    const std::vector<byte_t>& ax12_ids = controller.ax12_ids();
    if (!ax12_ids.size()) {
        std::cerr << "no ax12 detected, exit" << std::endl;
        return 0;
    }

    if(argc < 3)
      exit(0);

    float GEN_0 = atof(argv[1]);
    float GEN_1 = atof(argv[2]);

    std::cout << "Transfer of the controller: " << GEN_0 << " " << GEN_1 << std::endl;

    // Config actuators //////////////////////////////////////////////////////
    std::vector<Actuator *> actuators;        // AX-12+ IDs
    
    actuators.push_back(new Actuator( 1, 512 - GEN_0 * 512,   GEN_1 * 512.0, 1.00,  0.00, SAMPLING_FREQUENCY, clockwise));
    actuators.push_back(new Actuator( 2, 512 - GEN_0 * 512,  -GEN_1 * 512.0, 1.00, -M_PI / 2.0f, SAMPLING_FREQUENCY, counterclockwise));

    actuators.push_back(new Actuator( 5, 512 + GEN_0 * 512,  -GEN_1 * 512.0, 1.00,  0.00, SAMPLING_FREQUENCY, counterclockwise));
    actuators.push_back(new Actuator( 6, 512 + GEN_0 * 512,   GEN_1 * 512.0, 1.00, -M_PI / 2.0f, SAMPLING_FREQUENCY, clockwise));

    actuators.push_back(new Actuator( 9, 512 - GEN_0 * 512,   GEN_1 * 512.0, 1.00,  0.00, SAMPLING_FREQUENCY, clockwise));
    actuators.push_back(new Actuator(10, 512 - GEN_0 * 512,  -GEN_1 * 512.0, 1.00,  M_PI / 2.0f, SAMPLING_FREQUENCY, counterclockwise));

    actuators.push_back(new Actuator(13, 512 + GEN_0 * 512,  -GEN_1 * 512.0, 1.00,  0.00, SAMPLING_FREQUENCY, counterclockwise));
    actuators.push_back(new Actuator(14, 512 + GEN_0 * 512,   GEN_1 * 512.0, 1.00,  M_PI / 2.0f, SAMPLING_FREQUENCY, clockwise));

    for(unsigned int i=0 ; i < actuators.size() ; i++) actuators[i]->printFunction();
    if(VERBOSE) for(unsigned int i=0 ; i < actuators.size() ; i++) actuators[i]->printDiscretePositions();
    if(VERBOSE) for(unsigned int i=0 ; i < actuators.size() ; i++) actuators[i]->printArrayDefinition();

    // Init timers //////////////////////////
    struct timeval timev_init;  // Initial absolute time (static)
    struct timeval timev_prev;  // Previous tick absolute time
    struct timeval timev_cur;   // Current absolute time
    struct timeval timev_diff;  // Current tick position (curent absolute time - previous tick time)
   
    timerclear(&timev_init);
    gettimeofday(&timev_init, NULL);

    // Init monitor /////////////////////////
    std::vector<byte_t> idMonitored;
    idMonitored.push_back(1);
    idMonitored.push_back(2);
    idMonitored.push_back(5);
    idMonitored.push_back(6);
    idMonitored.push_back(9);
    idMonitored.push_back(10);
    idMonitored.push_back(13);
    idMonitored.push_back(14);

    int items = Monitor::PRESENT_POSITION | Monitor::PRESENT_LOAD | Monitor::PRESENT_VOLTAGE | Monitor::PRESENT_TEMPERATURE;

    Monitor monitor(controller, idMonitored, items, READ_DURATION, timev_init);

    // Set speed ////////////////////////////
    for (size_t id_index = 0 ; id_index < actuators.size() ; ++id_index)
    {
        Status status;
        byte_t id = actuators[id_index]->getId();

        int moving_speed = SPEED;
        byte_t moving_speed_L = moving_speed & 0x00FF;
        byte_t moving_speed_H = (moving_speed & 0xFF00) >> 8;

        try {
            controller.send(ax12::WriteData(id, 0x20, moving_speed_L, moving_speed_H));
            controller.recv(READ_DURATION, status);
        } catch (Error& e) {
            std::cerr << "error : " << e.msg() << std::endl;
        }
    }

    timev_prev = timev_init;
    unsigned int sampling_interval_us = 1.0 / (double) SAMPLING_FREQUENCY * 1000000.0;

    std::cout << "Requested sampling interval : " << sampling_interval_us << " µs" << std::endl;

    if(VERBOSE) monitor.measure();

    // Ticks loop ///////////////////////////
    while(true) {
        gettimeofday(&timev_cur, NULL);
        timersub(&timev_cur, &timev_prev, &timev_diff);

        // On fait un step de sampling_interval_us (on suppose qu'une step ne dépasse pas 1 sec)
        if(timev_diff.tv_usec > sampling_interval_us || timev_diff.tv_sec > 0) {

            // Move robot ///////////////////////////////////////
            std::vector<byte_t> params;
            params.push_back(0x1e);
            params.push_back(0x02);

            for (size_t id_index = 0 ; id_index < actuators.size() ; ++id_index)
            {
                //Status status;
                byte_t id = actuators[id_index]->getId();

                // Calculate new positions
                unsigned int goal_position = actuators[id_index]->nextPosition();
                byte_t goal_position_L = goal_position & 0x00FF;
                byte_t goal_position_H = (goal_position & 0xFF00) >> 8;

                params.push_back(id);
                params.push_back(goal_position_L);
                params.push_back(goal_position_H);
            }

            // Move actuator
            Status status;
            try {
                controller.send(ax12::SyncWrite(0xfe, params));
                //controller.recv(READ_DURATION, status);
            } catch (Error& e) {
                std::cerr << "error : " << e.msg() << std::endl;
            }

            if(VERBOSE) monitor.measure();

            // Update vars //////////////////////////////////////
            timev_prev = timev_cur;
        }
    }

    return 0;
}

void usage(char * prog) {
    fprintf(stderr, "usage: %s [-d controller_device]\n", prog);
}


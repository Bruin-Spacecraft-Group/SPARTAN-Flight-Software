#include <array>
#include <iostream>
#include <fstream>

#include <data/datapacket.h>
#include <sensors/ads1115.h>
#include <sensors/lsm6ds33.h>

int main() {
    std::array<spartan::DataPacket*, 2> dataPackets;
    std::array<spartan::Sensor*, 1> sensors;

    // TODO: Initialize Sensors
    sensors[0] = new spartan::LSM6DS33(1, 0);

    // TODO: Initialize DataPackets
    // spartan::DataPacket masterPacket;
    // dataPackets[0] = new spartan::IMUDataPacket;

    // To debug lsm6
    /*
    spartan::LSM6DS33 * l6 = dynamic_cast<spartan::LSM6DS33 *>(sensors[0]);
    l6->powerOn();
    l6->poll();
    l6->printValues();
    spartan::DataPacket * dp;
    std::cout << l6->pollData(dp) << std::endl;
    std::cout << * dp << std::endl;
    std::cout << "DIVIDER" << std::endl; */
/*
    sensors[0]->powerOn();
    sensors[0]->poll();
    sensors[0]->printValues();
    std::cout << sensors[0]->pollData(dp) << std::endl;
    std::cout << * dp << std::endl;
*/
    bool debug = true;
    // Initialization of sensors
    for (int i = 0; i < sensors.size(); i++) {
	    sensors[i]->powerOn();
    }

    // TODO: flight loop
    int count = 0;

    std::ofstream fout;
    fout.open("data.txt");

    spartan::MasterDataPacket mdp;

    while (count < 100) {
        for (int i = 0; i < sensors.size(); i++) {
            // Polls data from sensor #i
            if (!(sensors[i]->pollData(mdp))) {
                std::cerr << "Sensor name: " << sensors[i]->name() << " instance; " << sensors[i]->getInstance()
                    << " poll data error!" << std::endl;
            }
            dataPackets[i]->populate(mdp);
            if (debug) {
                std::cout << "Packet size " << dataPackets[i]->getSize() << std::endl;
                std::cout << *dataPackets[i] << std::endl;
            }
            fout << *dataPackets[i];
        }
        count++;
    }
    fout.close();
    /*
    for (int i = 0; i < dataPackets.size(); i++) {
        dataPackets[i]->populate(masterPacket);
    }
    */

    // TODO: Send to comms (write to SD card and send to radio)
    /*
    std::cout << "Read from file" << std::endl;
    std::ifstream in;
    in.open("data.txt");
    for (int i=0; i<100; i++) {
        spartan::DataPacket * dp;
        in >> dp;
        std::cout << "Read: " << std::endl;
        std::cout << dp;
    } */
}

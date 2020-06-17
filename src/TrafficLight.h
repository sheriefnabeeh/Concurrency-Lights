#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <iostream>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;

// FP.3 Define a class âMessageQueueâ which has the public methods send and receive.
// Send should take an rvalue reference of type TrafficLightPhase whereas receive should return this type.
// Also, the class should define an std::dequeue called _queue, which stores objects of type TrafficLightPhase.
// Also, there should be an std::condition_variable as well as an std::mutex as private members.

template <class T>
class MessageQueue
{
public:
void send(T &&TrafficLightPhase);
T receive();
private:
std::condition_variable _condVariable;
std::deque<T> _queue;
std::mutex _mutex;
};

// FP.1 : Define a class âTrafficLightâ which is a child class of TrafficObject.
// The class shall have the public methods âvoid waitForGreen()â and âvoid simulate()â
// as well as âTrafficLightPhase getCurrentPhase()â, where TrafficLightPhase is an enum that
// can be either âredâ or âgreenâ. Also, add the private method âvoid cycleThroughPhases()â.
// Furthermore, there shall be the private member _currentPhase which can take âredâ or âgreenâ as its value.

class TrafficLight : TrafficObject
{
public:
    TrafficLight();
    ~TrafficLight();

    // getters / setters
    enum TrafficLightPhase
{
    red,
    green
};
    // typical behaviour methods
    void waitForGreen();
    void simulate();
    TrafficLightPhase getCurrentPhase();
    void setCurrentPhase(TrafficLightPhase l){ _currentPhase = l;}
    
private:
    // typical behaviour methods
    void cycleThroughPhases();

    // FP.4b : create a private member of type MessageQueue for messages of type TrafficLightPhase
    // and use it within the infinite loop to push each new TrafficLightPhase into it by calling
    // send in conjunction with move semantics.
    TrafficLightPhase _currentPhase;
    std::mutex _mutex;
    MessageQueue<TrafficLightPhase> _messageQueue;
};


#endif
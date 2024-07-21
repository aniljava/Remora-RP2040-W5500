#ifndef STEPGEN_H
#define STEPGEN_H

#include <cstdint>
#include <string>

#include "../extern.h"
#include "../module.h"
#include "../../drivers/pin/pin.h"



void createStepgen(void);
void loadStaticStepgen(void);

class Stepgen : public Module
{
  private:

    int jointNumber;              	// LinuxCNC joint number
    int mask;

    std::string step, direction;	  // physical pins connections

    bool isEnabled;        	        // flag to enable the step generator
    bool isForward;        	        // current direction
    bool isStepping;

    int32_t frequencyCommand;     	// the joint frequency command generated by LinuxCNC
    int32_t rawCount;             	// current position raw count - not currently used - mirrors original stepgen.c
    int32_t DDSaccumulator;       	// Direct Digital Synthesis (DDS) accumulator
    float   frequencyScale;		  	  // frequency scale
  	int32_t	DDSaddValue;		  	    // DDS accumulator add vdd value
    int32_t stepBit;                // position in the DDS accumulator that triggers a step pulse

    rxData_t* rxData;               // pointer to ping-pong buffer
	  txData_t* txData;               // pointer to ping-pong buffer

  public:

    Stepgen(int32_t, int, std::string, std::string, int);  // constructor

    Pin *stepPin, *directionPin;		// class object members - Pin objects

    virtual void update(void);           // Module default interface
    virtual void updatePost(void);
    virtual void slowUpdate(void);
    void makePulses();
    void stopPulses();
    void setEnabled(bool);
};


#endif

/*
 *  Trailer_Light_Controller
 * WLED usermod for controlling scenes based on tail light condition.
 */

#pragma once
#include <wled.h>

#ifndef LEFT_PIN
    #define LEFT_PIN 14
#endif

#ifndef RIGHT_PIN
    #define RIGHT_PIN 12
#endif

class UsermodTrailerLight : public Usermod {
private:
    unsigned long lastTime = 0;
    int delayMs = 100;
    bool braking = false;
    bool left = false;
    bool right = false;

public:
    enum LightState {
        IDLE        = 1,
        LEFT_TURN,  // 2
        RIGHT_TURN, // 3
        BRAKE,      // 4
        LEFT_BRAKE, // 5
        RIGHT_BRAKE,// 6
    };

    void setup()
    {
        pinMode(LEFT_PIN, INPUT);
        pinMode(RIGHT_PIN, INPUT);
    }

    void loop()
    {
        if(lastTime > millis()){
            return;
        }

        left = digitalRead(LEFT_PIN);
        right = digitalRead(RIGHT_PIN);
        
        if(braking){
            if ((left == LOW) && (right == LOW)){
                braking = false; // this only resets after the brakes are released
                applyPreset(LightState::IDLE);
            } 
        }
        else if ((left == HIGH) && (right == HIGH)){
            braking = true; // this only resets after the brakes are released
            applyPreset(LightState::BRAKE);
        }
        else if ((left == HIGH) && (right == LOW)){
            braking ? applyPreset(LightState::LEFT_BRAKE) : applyPreset(LightState::LEFT_TURN);
        }
        else if ((left == LOW) && (right == HIGH)){
            braking ? applyPreset(LightState::RIGHT_BRAKE) : applyPreset(LightState::RIGHT_TURN);
        }
        lastTime = delayMs + millis();
    }

    // Allows you to optionally give your V2 usermod an unique ID.
    // ------------------------------------------------------------
    uint16_t getId() {
        return USERMOD_ID_TRAILER_LIGHT;
    }
};
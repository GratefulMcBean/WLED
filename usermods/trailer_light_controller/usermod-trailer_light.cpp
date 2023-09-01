/*
 *  Trailer_Light_Controller
 * WLED usermod for controlling scenes based on tail light condition.
 */

#include <arduino.h>
#include <wled.h>

#define LEFT_PIN 14
#define RIGHT_PIN 12
#define LATCHCOUNT 5
#define TRUE 1
#define FALSE 0

void userSetup()
{
    //start the inputs
    pinMode(LEFT_PIN, INPUT);
    pinMode(RIGHT_PIN, INPUT);
}

void userConnected()
{

}

long lastTime = 0;
int delayMs = 100;
bool braking = FALSE;
bool left = FALSE;
bool right = FALSE;

void userLoop()
{
    if (millis()-lastTime > delayMs)
    {
        //check inputs
        left = digitalRead(LEFT_PIN);
        right = digitalRead(RIGHT_PIN);
        uint8_t showScene = NULL;

        if (braking)
        {
           if ((left == LOW) && (right == LOW))
            {
                braking = FALSE; // this only resets after the brakes are released
                showScene = 'i';  // switch to idle
            } 
        }
        else if ((left == HIGH) && (right == HIGH))
        {
            braking = TRUE; // this only resets after the brakes are released
            showScene = 'B';
        }
        else if ((left == HIGH) && (right == LOW))
        {
            showScene = 'l';
            if (braking)
            {
                showScene = 'L';
            }
        }
        else if ((left == LOW) && (right == HIGH))
        {
            showScene = 'r';
            if (braking)
            {
                showScene = 'R';
            }
        }


        //This is where the logic of selecting the correct preset for one of the 6 operating conditions
        if (showScene != NULL) {
            switch (showScene) {
                case 'i':
                    applyPreset(1); //idle
                    break;
                case 'l':
                    applyPreset(2); //left turn
                    break;
                case 'r':
                    applyPreset(3); //right turn
                    break;
                case 'B':
                    applyPreset(4); //brake only
                    break;
                case 'L':
                    applyPreset(5); //left turn + brake
                    break;
                case 'R':
                    applyPreset(6); //right turn + brake
                    break;
            }
        }
        lastTime = millis();
    }
}
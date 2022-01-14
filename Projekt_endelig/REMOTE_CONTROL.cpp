#include "REMOTE_CONTROL.h"

REMOTE_CONTROL::REMOTE_CONTROL()
{ 
    speedForward_ = 0;
    speedBackward_ = 0;
    speedValue_ = 0;
    for (int i = 0; i < 4; i++)
    {
        buttons_[i] = 0;
    }
    rfDriver_.init();
}

void REMOTE_CONTROL::setSpeedForward()
{
    speedForward_ = speedValue_ - 200;
}

void REMOTE_CONTROL::setSpeedBackward()
{
    speedBackward_ = 200 - speedValue_;
}

void REMOTE_CONTROL::setButton(uint8_t *buf)
{
    buttons_[0] = (buf[3] == '1' ? true : false);
    buttons_[1] = (buf[4] == '1' ? true : false);
    buttons_[2] = (buf[5] == '1' ? true : false);
    buttons_[3] = (buf[6] == '1' ? true : false);

    for (int i = 0; i < 4; i++)
      {
         buttonArray[i] = buttons_[i];
      }
    
    
}

void REMOTE_CONTROL::setSpeedValue(uint8_t * buf, uint8_t buflen)
{

    if (rfDriver_.recv(buf, &buflen))
    {
        const char speed[3] = { buf[0],buf[1],buf[2]};
        speedValue_ = atoi(speed);
    }
    //else
    //{
    //    speedValue_ = 0;
    //}
}

int REMOTE_CONTROL::getSpeedForward()
{
    return speedForward_;
}

int REMOTE_CONTROL::getSpeedBackward()
{
    return speedBackward_;
}


int REMOTE_CONTROL::getSpeedValue()
{
    return speedValue_;
}

void REMOTE_CONTROL::init()
{
    rfDriver_.init();
}

void REMOTE_CONTROL::drive()
{
    setSpeedBackward();
    setSpeedForward();

    if (speedValue_ > 210)
    {
        forward(speedForward_, 0, 0);
    }
    else if (speedValue_ < 203 && 195 < speedValue_)
    {
        stop();
    }
    else if (speedValue_ < 190)
    {
        backward(speedBackward_, 0, 0);
    }
}

void REMOTE_CONTROL::print()
{
    Serial.print("\nForward Value: ");
    Serial.print(speedForward_);

    Serial.print("\nBackward Value: ");
    Serial.print(speedBackward_);

    Serial.print("\n Speed Value: ");
    Serial.print(speedValue_);

    for (int i = 0; i < 4; i++)
    {
        Serial.print("\nButton number: ");
        Serial.print(i + 1);
        Serial.print(" state: ");
        Serial.print(buttonArray[i]);
    }

}

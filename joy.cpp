#include 'WPILib.h'

class Robot: public Robot
{
  Joystick = new stick;
public:
  Robot()
    stick(0) //use station port 0.
    {
      
    }

    void operatorControl()
    whilte(IsOperatorControl()){
      //controller class

      //left side y-axis
      if(stick.getRawAxis(1) > .2){
        
      }

      //left side x-axis
      if (stick.getRawAxis(2) > .2){
        
      }

      //X Button
      if(stick.getRawButton(1) == 1){
        
      }

      //A Button
      if(stick.getRawButton(2) == 1){
        
      }
      //B Button
      if(stick.getRawButton(3) == 1){
        
      }

      //Y Button
      if(stick.getRawButton(4) == 1){
        
      }
            
    }
}

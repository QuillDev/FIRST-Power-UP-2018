//main.cpp
#include <WPILib.h>

class Robot: public IterativeRobot{

private:
    RobotDrive *myDrive;
    Joystick *left, *right;

    void TeleopInit() {
      myDrive = new RobotDrive(1,2,3,4);
      joycon = new Joystick(1);
      double value;
      value = joycon->GetRawAxis(1)

    }

    void OperatorControl() override {
      while (IsOperatorControl() && isEnabled()){
          myDrive->ArcadeDrive(joycon);
          wait(0.01);
      }
    }
    void TeleopPeriodic() override {

    }

    void AutonomousInit() override {

    }

    void AutonomousPeriodic() override {
      
    }

    void Test {

    }

};

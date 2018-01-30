#include <Drive/DifferentialDrive.h>
#include <IterativeRobot.h>
#include <Joystick.h>
#include <LiveWindow/LiveWindow.h>
#include <Spark.h>
#include <Timer.h>
#include <WPILib.h>


using namespace frc;

class Robot: public IterativeRobot
{
    RobotDrive *difDrive;
    Joystick *logiCon; //controller
    LiveWindow *lw;
    Gyro *gyro;
    int autoLoopCounter;

public:
    Robot() :
        difDrive(0,1), //these must be initialized in the same order
        logiCon(1),      //as they are declared above.
        lw(NULL),
        autoLoopCounter(0){

          difDrive.SetExpiration(0.1);

        }

        void RobotStart(){
          lw = LiveWindow::GetInstance();

          difDrive = new RobotDrive(1, 2, 3, 4);
          gyro = new AnalogGyro(1);
        }

        void AutoStart(){
          autoLoopCounter = 0;
        }

        void AutoPeriod(){
          while(IsAutonomous() && IsEnabled()){
            float angle = gyro->GetAngle();
            float kp = 0.03
            myDrive->ArcadeDrive(-1.0, -angle*Kp);
            wait(0.01)
          }
        }

        void PilotStart(){
          difDrive = new RobotDrive(1, 2, 3, 4);

          logiCon = new Joystick(1);
          double value;
          value = logiCon-> GetRawAxis(1); .//left X
          value = logiCon-> GetRawAxis(2); //left Y
          value = logiCon-> getRawAxis(4); //right X
          value = logiCon-> getRawAxis(5); //right Y

          boolean buttonValue;
          buttonValue = logiCon.getRawButton(1);//A
          buttonValue = logiCon.getRawButton(2);//B
          buttonValue = logiCon.getRawButton(3);//X
          buttonValue = logiCon.getRawButton(4);//Y

          /**
          NOTE Add microsoft Xbox controller bindings
          NOTE Add way to determine which controller is plugged in for easier bindings
          **/

        }

        void PilotControl(){
          //SingleStick "Arcade Drive"
          while (IsOperatorControl() && IsEnabled()){
            difDrive->ArcadeDrive(logiCon);
            wait(0.1);
          }
        }

        void PilotPeriod(){
          //difdrive
        }

        void TestPeriod(){
          lw -> Run();
        }

};

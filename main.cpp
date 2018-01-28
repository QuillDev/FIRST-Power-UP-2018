#include <Drive/DifferentialDrive.h>
#include <IterativeRobot.h>
#include <Joystick.h>
#include <LiveWindow/LiveWindow.h>
#include <Spark.h>
#include <Timer.h>
#include <WPILib.h>
#include <XboxController.h>


using namespace frc;

class Robot: public IterativeRobot
{
    RobotDrive myRobot;
    Joystick *logiCon; //controller
    LiveWindow *lw;
    int autoLoopCounter;

public:
    Robot() :
        myRobot(0,1), //these must be initialized in the same order
        logiCon(1),      //as they are declared above.
        lw(NULL),
        autoLoopCounter(0){

          myRobot.SetExpiration(0.1);

        }

        void RobotStart(){
          lw = LiveWindow::GetInstance();

          //controller???
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
          
        }

        void AutoStart(){
          autoLoopCounter = 0;
        }

        void AutoPeriod(){
          if(autoLoopCounter < 100){
            myRobot.Drive(-0.5, 0);

            autoLoopCounter++;
          } else{
            myRobot.Drive(0.0, 0.0);
          }
        }

        void PilotStart(){
          //to be continued
        }

        void PilotPeriod(){
          //difdrive
        }

        void TestPeriod(){
          lw -> Run();
        }
                  
};

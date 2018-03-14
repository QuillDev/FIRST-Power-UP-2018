/**robot.cpp
TODO:
- Test Reset Function.
- Test Arms and Swing.
- Do wait and Autonomous during 6hr period.

**/

#include <boltbeard.h>
#include <iostream>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

//Include Spark.h
#include <Spark.h>
#include <Joystick.h>
#include <Math.h>
#include "WPILib.h"

//custom headers
#include "boltbeard.h" //I hope you're satisfied @StripedMonkey

using namespace std;
using namespace frc;

class Robot : public IterativeRobot {
public:
	void RobotInit() {
		m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
		m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
		SmartDashboard::PutData("Auto Modes", &m_chooser);

		//Create Sparks
		left = new Spark(0);
		right = new Spark(1);
		intake = new Spark(2);
		intake2 = new Spark(3);
		swing = new Spark(4);

		//Timer
		timer = new Timer();

	}
	//Pointers for Sparks
	Spark *left;
	Spark *right;
	Spark *intake;
	Spark *intake2;
	Spark *swing;
	Joystick *stick;
	Timer *timer;

	//declare doubles
	double ly, ls,lbs, ry, rs, rbs = 0;
	const double dz = .1;
	//declare ints
	int i, h, m, n = 0;

	//declare booleans
	bool lb, rb, aButton;

	void AutonomousInit() override {
		m_autoSelected = m_chooser.GetSelected();
		// m_autoSelected = SmartDashboard::GetString(
		// 		"Auto Selector", kAutoNameDefault);
		std::cout << "Auto selected: " << m_autoSelected << std::endl;
		timer->Reset();
		timer->Start();

		if (m_autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void AutonomousPeriodic() {
		if (m_autoSelected == kAutoNameCustom) {

		} else {
			if(timer->Get() < 2){
				left->Set(.5);
				right->Set(.5);
			} else{
				left->Set(0);
				right->Set(0);
			}
		}
	}

	void TeleopInit() {
		stick = new Joystick(0);
	}

	void TeleopPeriodic() {
		//sticks
		ly = stick->GetRawAxis(1);
		ry = stick->GetRawAxis(5);
		ls = spd(i);
		rs = spd(h);

		//bumpers
		lb = stick->GetRawButton(5);
		rb = stick->GetRawButton(6);
		lbs = spd(m);
		rbs = spd(n);

		// intake test
		aButton = stick->GetRawButton(1);


		//Left Logic
		//IF IT IS LESS THAN ONE
		if(abs(ly) > dz && ls < 1){
			if(ly > 0){
				left->Set(ls);
				i++;
			}
			else{
				left->Set(-ls);
				i++;
			}
		}
		// MAKES IT SO IT NEVER GOES OVER 1
		else if(ls >=1){
			if(ls > 0){
				left->Set(-1);
		}
			else{
				left->Set(1);
			}
		}
		else{
			left->Set(0);
			i = 0;
		}

		//Right Logic
		//IF RIGHT STICK IS LESS THAN ONE & GREATER THAN dz
		if(abs(ry) > dz && rs < 1){
			if(ry > 0){
				right->Set(rs);
				h++;
			}
			else{
				right->Set(-rs);
				h++;
			}
		}
		else if(rs >= 1){
				if(rs > 0){
					right->Set(1);
				}
				else{
					right->Set(-1);
				}
			}
		else {
			right->Set(0);
			h = 0;
		}
	//IF LEFT BUMPER IS DOWN AND RIGHT/LEFT STICK ARE NOT ACTIVE AND IF LESS THAN 1
	if(lb == true && abs(ly) < dz && abs(ry) < dz){
		left->Set(-lbs);
		right->Set(lbs);
		m++;
	}
	//IF
	else if(lb == true && lbs >= 1 && abs(ly) < dz && abs(ry) < dz){
		left->Set(-1);
		right->Set(1);
	}
	//IF LEFT BUMPER IS NOT DOWN OR IF RIGHT/LEFT STICK ARE ACTIVE
	else if(lb == false || abs(ly) > dz || abs(ry) > dz){
		left->Set(0);
		right->Set(0);
		m = 0;

	}
	//IF RIGHT BUMPER IS DOWN
	if(rb == true && abs(ly) < dz && abs(ry) < dz){
		left->Set(lbs);
		right->Set(-lbs);
		n++;
	}
	//IF RIGHT BUMPER IS AT MAX SPEED AND LEFT/RIGHT GREATER THAN DEADZONE
	else if(lb == true && rbs >= 1 && abs(ly) < dz && abs(ry) < dz){
		left->Set(1);
		right->Set(-1);
	}
	//IF RIGHT BUMPER IS NOT DOWN OR IF RIGHT/LEFT STICK ARE ACTIVE
	else if(rb == false || abs(ly) > dz || abs(ry) > dz){
		left->Set(0);
		right->Set(0);
		n = 0;
	}

	if(aButton == true ){
		if(timer <= 2){
		}
		intake->Set(1);
		intake2->Set(-.5);
	} else {
		
	}

}


	void TestPeriodic() {

	}

private:
	LiveWindow& m_lw = *LiveWindow::GetInstance();
	SendableChooser<string> m_chooser;
	const string kAutoNameDefault = "Default";
	const string kAutoNameCustom = "My Auto";
	string m_autoSelected;
};

START_ROBOT_CLASS(Robot)

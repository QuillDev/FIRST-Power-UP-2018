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
		swing = new Spark(3);

	}
	//Pointers for Sparks
	Spark *left;
	Spark *right;
	Spark *intake;
	Spark *swing;
	Joystick *stick;

	//declare doubles
	double ly, ls,lbs, ry, rs, rbs = 0;
	const double deadzone = .1;

	//declare ints
	int i, h, m, n = 0;

	//declare booleans
	bool lb, rb, a;

	void AutonomousInit() override {
		m_autoSelected = m_chooser.GetSelected();
		// m_autoSelected = SmartDashboard::GetString(
		// 		"Auto Selector", kAutoNameDefault);
		std::cout << "Auto selected: " << m_autoSelected << std::endl;

		if (m_autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void AutonomousPeriodic() {
		if (m_autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void TeleopInit() {
		stick = new Joystick(0);
	}

	void TeleopPeriodic() {
		//sticks
		ly = stick->GetRawAxis(1);
		ry = stick->GetRawAxis(5);
		ls = spd(i, -1);
		rs = spd(h, 1);

		//bumpers
		lb = stick->GetRawButton(5);
		rb = stick->GetRawButton(6);
		lbs = spd(m, 1);
		rbs = spd(n, 1);

		// intake test
		a = stick->GetRawButton(1);


		//stick logic
		if(abs(ly) > deadzone && abs(ls) < 1){
			left ->Set(ls);
			i++;
		} else if(abs(ls) >= 1){
			if(abs(ls) > 0){left->Set(-1);

			} else{left->Set(1);}
		}

			else{left->Set(0);i=0;}

		if(ry > deadzone && abs(rs) < 1){
			right->Set(rs);
			h++;
		}

		else if(abs(rs) >= 1){if(abs(rs) > 0){
			right->Set(1);
		}

		else{right->Set(-1);}

		}

		else{
			right->Set(0);h=0;
		}

		//Left Bumper
		if(lb == true && abs(lbs) < 1 && abs(ly) < deadzone){
			left->Set(-lbs);
			right->Set(lbs);
			m++;

		} else if(abs(lbs) >= 1 && abs(ly) < deadzone){
			left->Set(-1); right->Set(1);
		}

		else if(abs(lbs) < deadzone){
			left->Set(0); right->Set(0);m=0;
		}

		//Right Bumper
		if(rb == true && abs(ry) < deadzone && abs(ry) < 1){
			left->Set(rbs);
			right->Set(-rbs);
		} else if(abs(ry) > deadzone && rbs >= 1){
			left->Set(1);
			right->Set(-1);
		} else if(ry < deadzone) {
			left->Set(0); right->Set(0);
		}

	// INTAKE TESTING
		if(a == true){
			intake->Set(.7);
		}else{intake->Set(0);}
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

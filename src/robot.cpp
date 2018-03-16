/**robot.cpp
TODO:
- TEST TEST TEST!
- Pray
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
#include <Timer.h>
#include <Joystick.h>
#include <Math.h>

//custom headers
#include "boltbeard.h"

using namespace std;
using namespace frc;

class Robot : public IterativeRobot {
public:
	void RobotInit() {
		m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
		m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
		SmartDashboard::PutData("Auto Modes", &m_chooser);

		//Create Sparks
		right = new Spark(0);
		left = new Spark(1);
		intake = new Spark(2);
		intake2 = new Spark(3);
		swing = new Spark(4);

		//Timer
		autoTimer = new Timer();

	}
	//Pointers for Sparks
	Spark *left;
	Spark *right;
	Spark *intake;
	Spark *intake2;
	Spark *swing;
	Joystick *stick;
	Timer *autoTimer;

	//declare doubles
	double ly, ls,lbs, ry, rs, rbs = 0;
	const double dz = .2;

	//Declare Loops
	int i, h, m, n = 0;

	//declare booleans
	bool lb, rb, aButton, bButton, xButton, yButton;

	void AutonomousInit() override {
		m_autoSelected = m_chooser.GetSelected();
		/* m_autoSelected = SmartDashboard::GetString(
			"Auto Selector", kAutoNameDefault);*/
		std::cout << "Auto selected: " << m_autoSelected << std::endl;
		autoTimer->Reset();
		autoTimer->Start();

		if (m_autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void AutonomousPeriodic() {
		if (m_autoSelected == kAutoNameCustom) {

		} else {
			if(autoTimer->Get() < 5){
				left->Set(.4);
				right->Set(-.4);
			} else{
				left->Set(0);
				right->Set(0);
			}
		}
	}

	void TeleopInit() {
		stick = new Joystick(0);
		right->SetInverted(true);
	}

	void TeleopPeriodic() {
		//sticks
		ly = stick->GetRawAxis(1);
		ry = stick->GetRawAxis(5);

		//bumpers
		lb = stick->GetRawButton(5);
		rb = stick->GetRawButton(6);
		lbs = spd(m);
		rbs = spd(n);

		// intake test
		aButton = stick->GetRawButton(1);
		bButton = stick->GetRawButton(2);
		xButton = stick->GetRawButton(3);
		yButton = stick->GetRawButton(4);


		//Stick Logic
		//IF IT IS LESS THAN ONE

		if(abs(ly) > dz){
			left->Set(-ly);
		}
		else{
			left->Set(0);
		}

		if(abs(ry) > dz){
			right->Set(-ry);
		}
		else{
			right->Set(0);
		}
		/*
	//IF LEFT BUMPER IS DOWN AND RIGHT/LEFT STICK ARE NOT ACTIVE AND IF LESS THAN 1
	if(lb == true && abs(ly) <= dz && abs(ry) <= dz){
		left->Set(-lbs);
		right->Set(-lbs);
		m++;
	}
	//IF
	else if(lb == true && lbs >= 1 && abs(ly) < dz && abs(ry) < dz){
		left->Set(-1);
		right->Set(-1);
	}
	//IF LEFT BUMPER IS NOT DOWN OR IF RIGHT/LEFT STICK ARE ACTIVE
	else if(lb == false || abs(ly) > dz || abs(ry) > dz){
		left->Set(0);
		right->Set(0);
		m = 0;

	}
	//IF RIGHT BUMPER IS DOWN
	if(rb == true && abs(ly) < dz && abs(ry) < dz && ry < 1){
		left->Set(rbs);
		right->Set(rbs);
		n++;
	}
	//IF RIGHT BUMPER IS AT MAX SPEED AND LEFT/RIGHT GREATER THAN DEADZONE
	else if(lb == true && rbs >= 1 && abs(ly) < dz && abs(ry) < dz){
		left->Set(1);
		right->Set(1);
	}
	//IF RIGHT BUMPER IS NOT DOWN OR IF RIGHT/LEFT STICK ARE ACTIVE
	else if(rb == false || abs(ly) > dz || abs(ry) > dz){
		left->Set(0);
		right->Set(0);
		n = 0;
	}
	/*
	if(aButton == true ){
		intake->Set(1);
		intake2->Set(-.5);

	} else if(bButton == true){
		intake->Set(-1);
		intake2->Set(.5);
	}
	else{
		intake->Set(0);
		intake2->Set(0);
	}

	if(xButton == true){
		swing->Set(.2);
	} else if(yButton == true){
		swing->Set(-.2);
	}
	else{
		swing->Set(0);
	}
	*/
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

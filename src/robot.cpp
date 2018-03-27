/**robot.cpp
 TODO:
 - Test Reset Function.
 - Test Arms and Swing.
 - Set Flag for the Swing.
 - Beef out autonomous

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
#include "DriverStation.h"

using namespace std;
using namespace frc;

class Robot: public IterativeRobot {
public:
	void RobotInit() {
		m_chooser.AddDefault(startSwitchLeft, startSwitchLeft);
		m_chooser.AddObject(startSwitchRight, startSwitchRight);
		m_chooser.AddObject(startOffSwitch, startOffSwitch);
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
	double ly, ls, lbs, ry, rs, rbs, rt, lt = 0;
	const double dz = .2;

	//Declare Loops
	int i, h, m, n = 0;

	//declare booleans
	bool lb, rb, aButton, bButton, xButton, yButton;

	void AutonomousInit() override {
		left->SetSafetyEnabled(false);
		right->SetSafetyEnabled(false);
		swing->SetSafetyEnabled(false);

		m_autoSelected = m_chooser.GetSelected();
		std::cout << "Auto selected: " << m_autoSelected << std::endl;
		string gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

		if (((m_autoSelected == startSwitchLeft) && (gameData[0] == 'L')) ||
				((m_autoSelected == startSwitchRight) && (gameData[0] == 'R'))){
			left->Set(0.3);
			right->Set(0.3);

			Wait(5);
			cout << "Moving" << endl;

			left->Set(0);
			right->Set(0);

			Wait(1);

			swing->Set(.5);
			Wait(4);
			swing->Set(-.5);
			Wait(4);
			swing->Set(0);
			cout << "Swinging" << endl;
		}
		else if(m_autoSelected == startOffSwitch){
			left->Set(0.3);
			right->Set(0.3);

			Wait(5);
			cout << "Moving" << endl;

			left->Set(0);
			right->Set(0);
		}
	}


	void AutonomousPeriodic() {
		}

	void TeleopInit() {
		stick = new Joystick(0);
		left->SetSafetyEnabled(true);
		right->SetSafetyEnabled(true);
		swing->SetSafetyEnabled(true);

	}

	void TeleopPeriodic() {
		lt = stick->GetRawAxis(2);
		rt = stick->GetRawAxis(3);
		right->SetInverted(true);
		right->Set(0);
		left->Set(0);
		//sticks
		ly = stick->GetRawAxis(1);
		ry = stick->GetRawAxis(5);

		//bumpers
		lb = stick->GetRawButton(5);
		rb = stick->GetRawButton(6);


		// intake test
		aButton = stick->GetRawButton(1);
		bButton = stick->GetRawButton(2);
		xButton = stick->GetRawButton(3);
		yButton = stick->GetRawButton(4);


		//Stick Logic
		if (aButton == true) {
			left->Set(0);
			right->Set(0);
		}

		if (abs(ly) > dz) {
			left->Set(-ly);
			stick->SetRumble(frc::GenericHID::kLeftRumble, abs(ly));
		} else {
			left->Set(0);
			stick->SetRumble(frc::GenericHID::kLeftRumble, 0);
		}

		if (abs(ry) > dz) {
			right->Set(-ry);
			stick->SetRumble(frc::GenericHID::kRightRumble, abs(ry));
		} else {

			right->Set(0);
			stick->SetRumble(frc::GenericHID::kRightRumble, 0);
		}

		//INTAKE
		if (lb == true) {
			intake->Set(1);
			intake2->Set(-1);
		} else if (rb == true) {
			intake->Set(-1);
			intake2->Set(1);
		} else {
			intake->Set(0);
			intake2->Set(0);
		}

		//SWING
		if(xButton == true){
			swing->Set(.5);
		} else if(yButton == true){
			swing->Set(-.5);
		} else{
			swing->Set(0);
		}


	}

	void TestPeriodic() {

	}

private:
	LiveWindow& m_lw = *LiveWindow::GetInstance();
	SendableChooser<string> m_chooser;
	const string startSwitchLeft = "Starting on Switch Left";
	const string startSwitchRight = "Starting on Switch Right";
	const string startOffSwitch = "Starting Off Switch";
	string m_autoSelected;
};

START_ROBOT_CLASS(Robot)

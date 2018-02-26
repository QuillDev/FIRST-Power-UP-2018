//Robot.cpp
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
#include <WPILib.h>

class Robot : public frc::IterativeRobot {
public:
	void RobotInit() {
		m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
		m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
		left = new frc::Spark(0);
		right = new frc::Spark(1);
		intake = new frc::Spark(2);
		swing = new frc::Spark(3);
	}
//Create pointers (*) for left and right
	frc::Spark *left;
	frc::Spark *right;
	frc::Spark *intake;
	frc::Spark *swing;
	frc::Joystick *stick;
	double ly, ry, deadzone, i, h, val1, val2, rbump, lbump, lbumpx, lbumpy, intakey, arm1, arm2 = 0;
	double inc = .005;

	void AutonomousInit() override {
		m_autoSelected = m_chooser.GetSelected();

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
		stick = new frc::Joystick(0);
	}

	void TeleopPeriodic() {
		ly = stick->GetRawAxis(1);
		ry = stick->GetRawAxis(5);
		rbump = stick->GetRawButton(6);
		lbump = stick->GetRawButton(5);
		intakey = stick->GetRawAxis(3);
		arm1 = stick->GetRawButton(1);
		arm2 = stick->GetRawButton(2);

		deadzone = .2;

		if(std::abs(ly) > deadzone){
			val1 = .5 + (inc * i);
			if(ly > 0){left->Set(-val1);}
			else{left->Set(val1+.05);}
			i++;
			}

		else{
			left->Set(0);
			ly1 = 0.0;
			i = 0;
		}

		if(std::abs(ry) > deadzone){
			val2 = .5 + (inc * h);
			if(ry > 0){right->Set(val2);}
			else{right->Set(-val2);}
			h++;
			}

		else{
			right->Set(0);
			h = 0;
		}

		if(lbump == true){
			left->Set(-(.5 + (lbumpx * inc)));
			right->Set(.55 + (lbumpx * inc));
			lbumpx++;
		} else {lbumpx = 0;}

		if(rbump == true){
			left->Set(.5 + (lbumpy * inc));
			right->Set(-(.5 + (lbumpy * inc)));
			lbumpy++;
		} else{lbumpy = 0;}

		if(std::abs(intakey) > 0){
			intake->Set(-1);
		}

		if(arm1 == true){
			swing->Set(.3);
		}

		if(arm2 == true){
			swing ->Set(-.5);
		}

	void TestPeriodic() {}

private:
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	frc::SendableChooser<std::string> m_chooser;
	const std::string kAutoNameDefault = "Default";
	const std::string kAutoNameCustom = "My Auto";
	std::string m_autoSelected;
};

START_ROBOT_CLASS(Robot)

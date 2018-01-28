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

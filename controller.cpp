// Joystick Object

Joystick *xboxCon
    
    public:
        Robot(){
        }
            void RobotInit(){
                xboxCon = new Joystick(1);
                double value; int logic;
                logic = xboxCon.getAButton(); //checks state of buttons (UP/DOWN)
                logic = xboxCon.getBButton();
                logic = xboxCon.getYButton();
                logic = xboxCon.getXButton();
                value = xboxCon.getX(); //retrieves how far the X of the stick is
                value = xboxCon.getY(); //retrieves how far the Y of the stick is
            }

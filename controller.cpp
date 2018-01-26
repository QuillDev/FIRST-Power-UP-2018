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
                /**please note that the ()'s are for inserting robot functions when we get to that point
                
                //Note, these are temporary labels and WILL MOST LIEKLY CHANGE when we
                Find the libraries of the controller we're using.**/
            }

class KeyboardEventHandler : public osgGA::GUIEventHandler
{
public:

    KeyboardEventHandler()
    {}

    virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&)
    {    
        int input1=10;
        int input2=10;
        int input3=10;
        int input4=10;
        int input5=10;


        switch (ea.getEventType())
        {
        case(osgGA::GUIEventAdapter::KEYDOWN):
            {
                switch (ea.getKey())
                {
                case(osgGA::GUIEventAdapter::KEY_Return):
		running=!running;
                    return true;
		#ifdef INPUTS
                case 'q':
			inputs[0]=+1*input1;
                    return true;
                case 'a':
			inputs[0]=-1*input1;
                    return true;
                case 'w':
			inputs[1]=+1*input2;
                    return true;
                case 's':
			inputs[1]=-1*input2;
                    return true;
                case 'e':
			inputs[2]=+1*input3;
                    return true;
                case 'd':
			inputs[2]=-1*input3;
                    return true;
                case 'r':
			inputs[3]=+1*input4;
                    return true;
                case 'f':
			inputs[3]=-1*input4;
                    return true;
                case 't':
			inputs[4]=+1*input5;
                    return true;
                case 'g':
			inputs[4]=-1*input5;
                    return true;
		#endif
                }
            }
        case(osgGA::GUIEventAdapter::KEYUP):
            {
                switch (ea.getKey())
                {
		#ifdef INPUTS	
                case 'q':
			inputs[0]=0;
                    return true;
                case 'a':
			inputs[0]=0;
                    return true;
                case 'w':
			inputs[1]=0;
                    return true;
                case 's':
			inputs[1]=0;
                    return true;
                case 'e':
			inputs[2]=0;
                    return true;
                case 'd':
			inputs[2]=0;
                    return true;
                case 'r':
			inputs[3]=0;
                    return true;
                case 'f':
			inputs[3]=0;
                    return true;
                case 't':
			inputs[4]=0;
                    return true;
                case 'g':
			inputs[4]=0;
                    return true;
		#endif
                }
            }


        default:
            break;

        }	
        return false;
    }
};


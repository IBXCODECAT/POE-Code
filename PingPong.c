#pragma config(Sensor, dgtl1,  bump,           sensorTouch)
#pragma config(Sensor, dgtl2,  bump,           sensorTouch)
#pragma config(Sensor, dgtl3,  bump,           sensorTouch)
#pragma config(Motor,  port1,           angle,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port10,          launcharm,     tmotorVex393_HBridge, openLoop)

void Init(); void DoStuff();
struct BumpBois { bool bumpUp; bool bumpDown; bool bumpActivate; }
struct BumpBois bumpBoi;
task main() { Init(); }

task Input()
{
	while(true)
	{


		if(SensorValue[dgtl1] == 1 && SensorValue[dgtl2] == 1)
		{
			bumpBoi.bumpUp = false; bumpBoi.bumpDown = false;
			continue;
		}
		else
		{
			if(SensorValue[dgtl1] == 1) { bumpBoi.bumpUp = true; } else { bumpBoi.bumpUp = false; }
			if(SensorValue[dgtl2] == 1) { bumpBoi.bumpDown = true; } else { bumpBoi.bumpDown = false; }
			if(SensorValue[dgtl3] == 1) { bumpBoi.bumpActivate = true; } else { bumpBoi.bumpActivate = false; }
		}
	}
}

void Init()
{
	bumpBoi.bumpUp = false;
	bumpBoi.bumpDown = false;
	bumpBoi.bumpActivate = false;

	startTask(Input);

	DoStuff();
}

void DoStuff()
{
	while(true)
	{
		if(bumpBoi.bumpUp) { startMotor(port1, 127); }
		if(bumpBoi.bumpDown) { startMotor(port1, -127); }
		if(bumpBoi.bumpActivate) { startMotor(port10, 127); } else { stopMotor(port10); }
		if(!bumpBoi.bumpUp && !bumpBoi.bumpDown) { stopMotor(port1); }
	}
}

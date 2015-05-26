#include "behavior.h"
#include "motorcontrol.h"
#include "buzzer.h"
#include "button.h"
#include "robot.h"
#include "modelrc.h"



StandbyBehavior::StandbyBehavior() : Behavior() {
  name = "StandbyBehavior";
}

bool StandbyBehavior::takeControl(){
  return  true;
}

void StandbyBehavior::action(){  
  suppressed = false;
  MotorCtrl.stopImmediately();
  while ( !suppressed ) {    
    Robot.run();   
  }  
}

// ----------------------------------------------------------

ModelRCBehavior::ModelRCBehavior() : Behavior() {
  name = "ModelRCBehavior";
}

bool ModelRCBehavior::takeControl(){
  return (Button.beepCounter == 3);
}

void ModelRCBehavior::action(){  
  suppressed = false;
  MotorCtrl.stopImmediately();
  Button.resetBeepCounter();    
  while ( (!suppressed) && (!Button.pressed) )  {    
    ModelRC.run();
    Robot.run();   
  }  
}


// ----------------------------------------------------------

UserStopBehavior::UserStopBehavior() : Behavior() {
  name = "UserStopBehavior";
}

bool UserStopBehavior::takeControl(){
  return ( (Button.beepCounter == 1) && (MotorCtrl.motion != MOTION_STOP) );
}

void UserStopBehavior::action(){  
  suppressed = false;
  MotorCtrl.stopImmediately();  
  Button.resetBeepCounter();  
  while ( (!suppressed) && (MotorCtrl.motion != MOTION_STOP) ){
    Robot.run();   
  }
}

// ----------------------------------------------------------

DriveForwardBehavior::DriveForwardBehavior() : Behavior() {
  name = "DriveForwardBehavior";
}

bool DriveForwardBehavior::takeControl(){
  return (Button.beepCounter == 1);
}

void DriveForwardBehavior::action(){  
  suppressed = false;
  Button.resetBeepCounter();

  // forward
  MotorCtrl.setSpeedRpm(+10, +10); 

  while ( (!suppressed) && (MotorCtrl.motion != MOTION_STOP) ){
    Robot.run();   
  }
}

// ----------------------------------------------------------

HitObstacleBehavior::HitObstacleBehavior()  : Behavior(){
  name = "HitObstacleBehavior";
}

bool HitObstacleBehavior::takeControl(){
  return ( (MotorCtrl.motion != MOTION_STOP) && (MotorCtrl.motorRightStalled) || (MotorCtrl.motorLeftStalled) || (Sonar.triggeredLeft()) );
}

void HitObstacleBehavior::action(){  
  suppressed = false;    
  MotorCtrl.resetStalled();
  bool rotateRight = MotorCtrl.motorLeftStalled;
  if (!Buzzer.isPlaying()) Buzzer.play(BC_LONG_SHORT_SHORT);                  
  
  // reverse
  MotorCtrl.travelLineDistance(-30, 10);             
  while ( (!suppressed) && (MotorCtrl.motion != MOTION_STOP) ) {
    Robot.run();   
  }
  
  // rotate
  if (rotateRight){
    MotorCtrl.rotate(-PI/2, 10);               
  } else {
    MotorCtrl.rotate(+PI/2, 10);                   
  } 
  // wait until motion stop
  while ( (!suppressed) && (MotorCtrl.motion != MOTION_STOP) ){
    Robot.run();   
  }
}

// ----------------------------------------------------------

ChargerConnectedBehavior::ChargerConnectedBehavior() : Behavior() {
  name = "ChargerConnectedBehavior";
}

bool ChargerConnectedBehavior::takeControl(){
  return Battery.chargerConnected();
}

void ChargerConnectedBehavior::action(){  
  suppressed = false;
  
  MotorCtrl.stopImmediately();
  Buzzer.play(BC_SHORT_SHORT_SHORT);                  

  // wait until some other behavior was activated
  while ( !suppressed ){
    Robot.run();       
  }
}


// ----------------------------------------------------------

FatalErrorBehavior::FatalErrorBehavior() : Behavior() {
  name = "FatalErrorBehavior";
}

bool FatalErrorBehavior::takeControl(){
  return (MotorCtrl.motorLeftError || MotorCtrl.motorRightError || MotorMow.motorError);
}

void FatalErrorBehavior::action(){  
  suppressed = false;
  
  MotorCtrl.stopImmediately();
  Buzzer.play(BC_SHORT_SHORT_SHORT);                  

  // wait until some other behavior was activated
  while ( (!suppressed )&& (!Button.pressed) ) {
    Robot.run();       
  }
  
  MotorCtrl.resetFault();
  MotorMow.resetFault();  
}



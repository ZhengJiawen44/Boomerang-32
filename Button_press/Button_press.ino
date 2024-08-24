
// this will assign the name PushButton to pin numer 15
const int PushButtonUp =12;
const int PushButtonDown =13;
// This Setup function is used to initialize everything 
void setup()
{
// This statement will declare pin 15 as digital input 
Serial.begin(115200);
pinMode(PushButtonUp, INPUT);
pinMode(PushButtonDown, INPUT);

}

void loop()

{
// digitalRead function stores the Push button state 
// in variable push_button_state
int Push_button_state_up = digitalRead(PushButtonUp);
int Push_button_state_down = digitalRead(PushButtonDown);

// if condition checks if push button is pressed
// if pressed LED will turn on otherwise remain off 
if ( Push_button_state_up == HIGH )
{ 
Serial.println("up pressed!");
}
else 
{
Serial.println("no press");
}



if ( Push_button_state_down == HIGH )
{ 
Serial.println("down pressed!");
}
else 
{
Serial.println("no press");
}
delay(200);
}
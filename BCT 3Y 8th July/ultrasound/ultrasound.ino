float duration_us, distance_cm;
void setup() {
  Serial.begin (9600);      
  pinMode(5, OUTPUT); //trigger
  pinMode(18, INPUT);  //echo
  
}
void loop() {
  digitalWrite(5, LOW);    
  delayMicroseconds(10);
  digitalWrite(5, HIGH); 
  delayMicroseconds(10);
  digitalWrite(5, LOW);
  duration_us = pulseIn(18, HIGH); //from echo pin
 distance_cm
		= duration_us * 0.0344 / 2;
  Serial.print("distance: ");
  
  Serial.print(distance_cm);
  Serial.println(" cm");
  
delay(1000);
}
int ldr=A0;
int value=0;
void setup() {
Serial.begin(9600);
pinMode(3,OUTPUT);
}

void loop() {
value=analogRead(ldr);//Reads the Value of LDR(light).
Serial.println("LDR value is :");//Prints the value of LDR to Serial Monitor.
Serial.println(value);
delay(3000);
}

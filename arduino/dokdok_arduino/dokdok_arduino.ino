#define TRIG 9 // TRIG 핀 설정(초음파를 보내는 핀)
#define ECHO 8 // ECHO 핀 설정(초음파를 받는 핀)

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH); // 물체에 반사되어 돌아온 초음파의 시간을 변수에 저장한다.

  // 34000 * 초음파가 물체로 부터 반사되어 돌아오는 시간 / 1000000 / 2 (왕복값이 아니라 편도값으로 나누기 2를 해준다.)
  // 초음파 센서의 가리값이 위 계산값과 동일하게 Cm로 환산되는 계산공식. 수식이 간단해지도록 적용.
  distance = duration * 17 / 1000;

  Serial.println(distance); // 측정된 물체로부터 거리값(cm값)을 보여준다.
  delay(1000); // 1초마다 측정값을 보여준다.
}

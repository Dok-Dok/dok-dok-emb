import serial

port = "/dev/ttyACM0"
isOpen = 0;
serialFromArduino = serial.Serial(port, 9600)
serialFromArduino.flushInput()

while True:
	input_s = serialFromArduino.readline()
	input = int(input_s)
	if input > 15:
		print(str(input) + " open")
		if isOpen == 0:
			isOpen = 1
			# 안드에 신호 보내기 (열림)
	else:
		print(str(input) + " close")
		if isOpen == 1:
			isOpen = 0
			# 안드에 신호 보내기 (닫힘)

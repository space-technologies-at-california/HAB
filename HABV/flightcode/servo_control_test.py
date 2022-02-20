from servo_control import HabServo


# TEST CODE BELOW
def test1():
    test_servo = HabServo(1.5, 50, 0)  # position (0 to 8 rev), frequency, channel
    test_servo.run(1)  # direction

test1()

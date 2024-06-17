import cv2
import cvlearn.HandTrackingModule as htm
import cvlearn.FingerCounter as fc
import serial

# Initialize serial connection
ser = serial.Serial('COM8', 9600)  # Replace 'COMX' with your Arduino's COM port

cap = cv2.VideoCapture(0)
det = htm.handDetector()
counter = fc.FingerCounter()

# Variable to store the counted finger value
num_fingers = 0

while True:
    # Capture frame-by-frame
    ret, frame = cap.read()
    det.findHands(frame)
    lmlist, bbox = det.findPosition(frame)

    if lmlist != 0:
        num_fingers = counter.countFingers(lmlist)  # Count fingers and store the value

        # Draw counted fingers on the frame
        counter.drawCountedFingers(frame, lmlist, bbox)

        # Print the number of fingers
        print("Number of fingers:", num_fingers)

        # Send commands over serial based on finger count
        if num_fingers == 1:
            ser.write(b'a')  # Send 'a' command to increase angle
        elif num_fingers == 2:
            ser.write(b'b')  # Send 'd' command to decrease angle
        elif num_fingers == 3:
            ser.write(b'c')  # Send 'd' command to decrease angle
        elif num_fingers == 4:
            ser.write(b'd')  # Send 'd' command to decrease angle

    # Check if the frame was successfully captured
    if not ret:
        print("Error: Could not capture frame.")
        break

    # Display the frame
    cv2.imshow('Live Feed', frame)

    # Break the loop if 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the capture object and close all windows
cap.release()
cv2.destroyAllWindows()
# Homework 12 - Arduino Password Machine with Potentiometer and LEDs

## Project Description
This project creates a **password machine** using an Arduino Uno. It utilizes:
- A potentiometer (analog input) and two push buttons (digital input).
- Three LEDs (green, red, and blue) as output indicators.

The user must follow a specific sequence of inputs to complete the password successfully. The **blue LED** provides feedback when the potentiometer is at specific positions, while the **green LED** indicates success, and the **red LED** signals failure.

---

## **Password Sequence**
To complete the password successfully:
1. Turn the potentiometer to the **middle position** (value between 400 and 500) → **Blue LED blinks once**.
2. Press **Button 1**.
3. Press **Button 2**.
4. Turn the potentiometer to the **right-most position** (value > 850) → **Blue LED blinks once**.
5. Press **Button 1** again.

If all steps are followed correctly:
- The **green LED blinks 3 times** to indicate success.

If the user makes a mistake at any step:
- The **red LED blinks 3 times**, and the sequence resets.

---

## **Circuit Connections**



---

## **How It Works**

1. **Blue LED Notification**:
   - Blinks once when the potentiometer is at:
     - **Middle position** (400 to 500).
     - **Right-most position** (> 850).

2. **Password Sequence**:
   - The user must follow the exact sequence of steps:
     1. Potentiometer to middle → Blue LED blinks.
     2. Press **Button 1**.
     3. Press **Button 2**.
     4. Potentiometer to right-most → Blue LED blinks.
     5. Press **Button 1**.

3. **Success**:
   - Green LED blinks **3 times**.

4. **Failure**:
   - Red LED blinks **3 times**, and the sequence resets.

---

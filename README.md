# Pressure Control Software

## Hardware

This Arduino software was developed by Denk Development in Mar 2019 for the microcontroller Atmega 328P.

### Wiring

_as-is_ + the following
* Connect a second Arduino to the motor through a motor shield (shield pins 1 and 2, as well as GND and VCC).
* Connect the Main-Arduino to the Motor-Arduino by hooking up the digital pins 6 <--> 6 and 7 <--> 7, as well as GND <--> GND.

## Software Architecture

The software is split into the following sub-parts:

* **Main program**. Controls the program flow and contains the main event loop.
* **Pressure delta**. Two things: (1) Reads the analog input from a potentiometer which is set by the user to control the target pressure difference. Its output is a pressure difference in PSI (float). (2) Reads the analog input from a pressure sensor. The values correspond to the difference between cabin pressure and external pressure. Yields values in PSI (float).
* **Display controller**. Shows four things on the display: (1) selected target pressure, (2) measured pressure, (3) motor position, (4) target motor position.
* **Valve control**. Takes actual and target pressure values and adjusts a valve accordingly.

### Upload to the Arduinos

There are two `.ino` file, one for the Motor-Arduino, one for the Main-Arduino.

1. Open the file at `PressureControlSoftware/MotorController/MotorController.ino` and upload it to the Motor-Arduino (the one with the motor shield).
2. Open the file at `PressureControlSoftware/PressureControlSoftware.ino` and upload it to the Main-Arduino (the one that is connected to display, potentiometers, ...).

### Parameters

Parameters can be adjusted in the header file `Parameters.h`. Not that instead of using a comma `,`, a dot `.` must be used for decimals. Lines are terminated with a semicolon `;`. 

* **Opening tolerance** `openingTolerance`, _Motor-Positions-Toleranz_, permitted value range [0,1]. Controls which deviation of target motor position and actual motor position is still tolerated until a motion is being triggered. If the motor target is e.g. `0.2`, and the measured position is `0.25`, nothing will happen with an `openingTolerance` greater than or equal to `0.05`. The tolerance for motion is derived from this value through division by 2. So while adjusting the motor position, movement will not stop unless half of the `openingTolerance` is reached.
* **Tolerated PSI delta** `toleratedPsiDelta`, _akzeptierte Differenz von Soll- und Ist-PSI_, permitted value range [0,maxPSI]. After which difference in preassure levels (target vs. actual) a motion is being triggered. Note that there is no tolerance for motion because this is already caught by the motor positioning tolerance.
* **Minimum valve opening**, `minOpening`, _geringste Öffnung des Ventils_, permitted value range [0,1]. Once a deviation from the target PSI is exceeding `toleratedPsiDelta` the valve will be opened to `minOpening` the least. May be set to `0` when in doubt.
* **Max opening at PSI delta** `maxOpeningAtPsiDelta`, _Differeny von Soll- und Ist-PSI, bei der das Ventil komplett offen steht_, permitted value range [0,maxPSI). At what PSI difference the valve is openend entirely.

## Warranty

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

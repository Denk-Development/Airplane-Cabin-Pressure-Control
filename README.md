# Pressure Control Software

## Hardware

This Arduino software was developed for the microcontroller Atmega 328P.

## Software Architecture

The software is split into the following modules:

 * **Main program**. Controls the program flow and contains the main event loop.
 * **Target pressure delta**. Reads the analog input from a potentiometer which is set by the user to control the target pressure difference. Its output is a pressure difference in PSI (float).
 * **Display controller**. Initially only one feature: Shows the selected target pressure on a display. Takes PSI values; outputs nothing.
 * **Actual pressure delta**. Reads the analog input from a pressure sensor. The values correspond to the difference between cabin pressure and external pressure. Yields values in PSI (float).
 * **Valve control**. Takes actual and target pressure values and adjusts a valve accordingly.

### Parameters

Parameters can be adjusted in the header files `Parameters.h`.

 * **Opening tolerance** `openingTolerance`, range [0,1]. Controls which deviation of target motor position and actual motor position is still tolerated until a motion is being triggered. If the motor target is e.g. `0.2`, and the measured position is `0.25`, nothing will happen with an `openingTolerance` greater than or equal to `0.05`. The tolerance for motion is derived from this value through division by 2. So while adjusting the motor position, movement will not stop unless half o the `openingTolerance` is reached.
 * **Tolerated PSI delta** `toleratedPsiDelta`, range [0,maxPSI]. After which difference in preassure levels (target vs. actual) a motion is being triggered. Not that there is no tolerance for motion because this is already caught by the motor positioning tolerance.
 * **Minimum valve opening** `minOpening`, range [0,1]. Once a deviation from the target PSI is exceeding `toleratedPsiDelta` the valve will be opened to `minOpening` the least. May be set to `0` when in doubt.
 * **Max opening at PSI delta** `maxOpeningAtPsiDelta`, range [0,maxPSI). At what PSI difference the valve is openend entirely.

## Warranty

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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

## Warranty

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

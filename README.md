# Arduino-Unity-AudioVisualization
Simple **code only** example how to make an audio visualizer with Arduino and the Unity game engine

# What you need
* An Arduino Uno, Nano, Mega...
* Ws2812b LED strip, each can be controlled individually and it only needs one pin
* 15-20W power supply (for 60 LEDs, each 5V and up to 50mA)

# Software
* Just unzip the folder and click on Arduino_Unity.exe to start the program
* It listens to the desktop audio and sends the data to the Arduino. I did not figure out how to select a single audio source yet so it mixes all sounds together
* You can also start multiple instances to control different ports
* Also note that this is a side project so I didn't put to much effort into it

# Basic software and script explanation
* Unity sends 36 Bytes to the Arduino as string
* First 6 Bytes contain the Amplitude
* Last 30 Bytes contain different audio bands the spectrum has been divided into
* The arduino then splits the string into char arrays and converts it into integer

# Code information
* The AudioData component in my Unity-Script is a custom script which gives me the amplitude of a song as a float and divides the audio spectrum into 64 different audio bands.
* These 64 audio bands are stored in an array and I'm using 30 of them to control my LED strip
* I can't give you the code for my script but if you need something like this take a look at this function https://docs.unity3d.com/ScriptReference/AudioSource.GetSpectrumData.html
* Also there is this great tutorial on what my script is based on https://www.youtube.com/watch?v=5pmoP1ZOoNs&list=PL3POsQzaCw53p2tA6AWf7_AWgplskR0Vo

# Contact
If you have any questions, hit me up on Twitter https://twitter.com/_Buttermilch or Reddit https://www.reddit.com/user/MangoButtermilch

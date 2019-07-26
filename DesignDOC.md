
# <center>Vex EDR 2019</center><center>5868C Program Design Document</center>
---
## Index
<a href="#game-rules" style="font-size: 18px;">1. GameRules</a></br></br>
<a href="#program-structure-and-goals" style="font-size: 18px;">2. Program structure and goals</a></br>
<div style="transform: translate(20px);">
<a href="#program-platform-and-language">1. Program platform and language</a></br></br>
<a href="#program-structure">2. Program structure</a>
<br/></br>
<a href="#program-thoughts">3. Program thoughts</a>
</div><br/>
<a href="#features-and-progress" style="font-size:18px;">3. Features and Progress</a><br/><div></div>

-------
## <div id="game-rules">Game Rules</div>
### <center><span style="color:yellow"><b>Tower TakeOver</b></span></center>
<div style="font-size: 19px;">
<ul>
<li> Game analyze: More on engineering notebook </li>
<li> Official site: *https://www.vexrobotics.com/vexedr/competition/vrc-current-game* </li>
</ul>
</div>

---
<div style="font-size: 16px;">

## <div id="program-structure-and-goals">Program structure and goals</div>
### <div id="program-platform-and-language">1. Program platform and language</div>
<ul>
<li>Language: C++</li>
<li>Develop Platform: PROS</li>
<li>Version Control: git</li>

<br/>
PROS develop steps:
<ol>
<li>Install <b>visual studio code</b></li>
<li>Install <b>C/C++ Support</b></li>
<li>Install <b>PROS CLI</b> (PROS command-line-interface)</li>
</ol>
</br>

### <div id="program-structure">2. Program Struture</div>
The project structure is like the following:

|-> include
<div style="transform: translate(20px);">
|-> Config.h: Containing constants used throughout the whole program </br>
|-> Robot.h : Containing instance for sensors, motors, etc. </br>
|-> RobotAuto.h : Containing the RobotAuto class, which is a class that provide more features using the foundation of Robot.h</br>
|-> vector2d.h : Containing the class of vector2d </br>
|-> typedefs.h : All typedefs that will be used throughout the program (including vector2d) </br>
|-> Debug.h : Header that provide extensive feature for debugging output (output can be viewed using the terminal) </br>
|-> gui.h : Containing function headers that do stuff related to the gui on V5 (using LVGL)
</div>

|-> src
<div style="transform: translate(20px);">
|-> initilize.cpp : Containing code that would be executed before Autonomous</br>
|-> autonomous.cpp : Containing code for Autonomous</br>
|-> opcontrol.cpp : Containing code for Driver-Control Period</br>
|-> RobotAuto.cpp : Containing function implementations of class RobotAuto </br>
|-> Debug.cpp : Containing function implementations for Debug.h </br>
|-> gui.cpp : Containing code that will produce the gui on V5 </br>
</div>

### <div id="program-thoughts">3. Program thoughts</div>
<div style="font-size: 16px;">
<strong><center>Use Object-Oriented-Programming</center></strong>
Here are the classes we plan to use:
<br/>
<ol>
<li>Robot</li>
<div style="transform: translate(20px);">
containing all motors and sensors on the robot (excluding the instance of the joystick)<br/>
Might contain some function for specific job like moving claws
</div>
<li>RobotAuto</li>
<div style="transform: translate(20px);">
<strong>inherit from the <i>Robot</i> class</strong></br>
More functions for autonomous movement like:
<ul>
<li>MoveDistance(): call the robot to move a specific distance</li>
<li>Turn(): call the robot to turn a specific angle</li>
</ul>
</div>
</ol>

</br>
<center>Some structures and objects are used in the program:</center>
<ol>
<li>vector2d</li>
<div style="transform: translate(20px);">
A class that can store a 2D Vector, it stores the x, y value of that vector.
</div>
<li>AutonPos_t</li>
<div style="transform: translate(20px);">
A enum type that stores the desire autonomous starting position of the robot.
</div>
</ol>
</div>
</div>

----
<div style="font-size: 16px;">

## <div id="features-and-progress">Features and Progress</div>
### OpControl
Operator Control's code is now fully operating, with all desire features enabled. The following features are included:
* Free Movement
* Side Sliding Movement
* Intake Control
* Intake-Lifter Control
* Lifter Control
### Autonomous

### Hot/Cold Linking
Hot/Cold Linking, a feature provided by PROS, is enabled, so library code is compiled into cold code, user code is compiled into hot code.

Each time, the robot will detect the library's status on the robot, and if the library is fine, it will only upload hot code.

Thus, upload time(especially wireless), will be shorten significantly.
For more info, go to https://pros.cs.purdue.edu/v5/tutorials/topical/wireless-upload.html

</div>

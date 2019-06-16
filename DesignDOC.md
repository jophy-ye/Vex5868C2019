# <center>Vex EDR 2019</center><center>5868C Program Design Document</center>
---
## Index
<a href="#game-rules" style="font-size: 18px;">1. GameRules</a></br></br>
<a href="#program-structure-and-goals" style="font-size: 18px;">2. Program structure and goals</a></br>
<div style="transform: translate(20px);">
<a href="#program-platform-and-language">1. Program platform and language</a></br>
<a href="#program-thoughts">2. Program thoughts</a>
</div><br/>
<a href="#program-api" style="font-size:18px;">3. Program API</a><br/><div></div>

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
## <div id="program-structure-and-goals">Program structure and goals</div>
### <div id="program-platform-and-language">1. Program platform and language</div>
<div style="font-size: 19px;">
<ul>
<li>Language: C++</li>
<li>Develop Platform: PROS</li>
<li>Version Control: git</li>

<br/>
PROS develop steps:
<ol>
<li>Install *atom*</li>
<li>Install *cquery* and set its path in atom</li>
<li>Install *PROS CLI* (PROS command-line-interface)</li>
<li>Install *bootstrap of PROS* in atom
</ol>
</div>

### <div id="program-thoughts">2. Program thoughts</div>
<div style="font-size: 19px;">
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
<strong>inherit from the *Robot* class</strong></br>
More functions for autonomous movement like:
<ul>
<li>MoveDistance(): call the robot to move a specific distance</li>
<li>Turn(): call the robot to turn a specific angle</li>
</ul>
</div>
</ol>
</div>

---
## Program API
<div id="program-api">

</div>

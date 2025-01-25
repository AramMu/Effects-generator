# Effects-generator

This is early program, or rather framework, I created for generating various cellular effects and simulations, similar to Game of Life, Forest fire and so on.\
I usually focused on making flame-like and lightning-like effects, and also implementations of algorithms such as Minimum Spanning Tree (MST), such that gradually connections between dots are made with lines.\
The description of this program is not well done yet, please provide me feedback and suggestions for improving it!

# Demonstration
![Alt text](/screenshots/DLA.PNG?raw=true "DLA")
![Alt text](/screenshots/forest-fire.PNG?raw=true "forest-fire")
![Alt text](/screenshots/main-window.PNG?raw=true "main-window")
![Alt text](/screenshots/flame-candle.PNG?raw=true "Flame candle")
![Alt text](/screenshots/flame-candle-colorful.PNG?raw=true "flame-candle-colorful")
![Alt text](/screenshots/flame-tongue.PNG?raw=true "flame-tongue")

# Getting started
This project depends on OpenCV 3.x.x, currently using 3.4.8 but anything else works, previously was 3.1.0\
Normally building all with MinGW x64, also works with MinGW x86, VS probably works don't remember if I tried or not.\
You can get prebuilt OpenCV libraries with MinGW here:\
https://github.com/huihut/OpenCV-MinGW-Build?tab=readme-ov-file\
Steps to do:\
-Download/clone OpenCV and put some place\
-Begin building "Generator" subproject\
  -On Generator.pro put the correct include/libs, in my case I didn't put include/lib paths since I had set system-wide variables of MinGW for include/libs, CPLUS_INCLUDE_PATH     and LIBRARY_PATH\
  -Put the OpenCV dlls on program folder after building or put the path into PATH
# Documentation/Wiki
TODO: put external links to algorithms and strategies used for implementation, and my own tricks too!


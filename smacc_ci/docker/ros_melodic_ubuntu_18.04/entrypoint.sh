#!/bin/bash
source /opt/ros/melodic/setup.bash; 
roscore&  
echo "DISPLAY:" $DISPLAY; 
rosrun smacc_viewer smacc_viewer_node.py
Before the code in MCP3008.h is used, the gpio.sh script must be run
	
To make gpio.sh run on startup always: 
- open terminal
- type "sudo nano /etc/rc.local"
- add the line "sudo bash <pathToThisFolder>/gpio.sh &"
- save and then run "sudo reboot"

Use testMCP.cpp to test if it worked.

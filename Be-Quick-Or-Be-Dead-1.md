# Be Quick Or Be Dead 1

	This is a basic challenge from picoCTF 2018

# Category: Reversing

  You find this when searching for some music, which leads you to be-quick-or-be-dead-1. Can you run it fast enough? 
  You can also find the executable in /problems/be-quick-or-be-dead-1_3_aeb48854203a88fb1da963f41ae06a1c. 

# Points: 200

	./be-quick-or-be-dead-1 
  	Be Quick Or Be Dead 1
  	=====================

  	Calculating key...
  	You need a faster machine. Bye bye

# What You Need To Follow

Binary Ninja or IDA Freeware

# Write Up:

To start. We open up the binary in either IDA or Binary Ninja. 

![image](https://user-images.githubusercontent.com/31195314/52672656-5628c380-2ed3-11e9-8940-0285a5589f8b.png)

After observing the "start" instructions, I moved to "main"

![image 1](https://user-images.githubusercontent.com/31195314/52672836-ce8f8480-2ed3-11e9-8736-790ae9e730c5.png)

Next, I say there was a call to "Set_Timer" which seemed interesting.

![image 3](https://user-images.githubusercontent.com/31195314/52672889-f2eb6100-2ed3-11e9-87a4-7e88ccf71f3c.png)

Based on what I saw in Set_Timer, I decided change the binary in order to prevent "alarm" from being called.

Right click alarm, select "Patch", and select "Convert to NOP"

![image 2](https://user-images.githubusercontent.com/31195314/52672863-e2d38180-2ed3-11e9-89c6-f34c00649410.png)

I saved the binary and re-ran the code.

  	./be-quick-or-be-dead-1\ \(1\) 
  	Be Quick Or Be Dead 1
  	=====================

  	Calculating key...
  	Done calculating key
  	Printing flag:
  	picoCTF{why_bother_doing_unnecessary_computation_27f28e71}


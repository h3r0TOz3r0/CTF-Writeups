# Quackme

	This is a basic challenge from picoCTF 2018

# Category: Reversing

  Can you deal with the Duck Web? 
  Get us the flag from this program. You can also find the program in /problems/quackme_2_45804bbb593f90c3b4cefabe60c1c4e2.  

# Points: 200

    ./main 
    You have now entered the Duck Web, and you're in for a honkin' good time.
    Can you figure out my trick?
    no
    That's all folks.
    
# What You Need To Follow Along

IDA Freeware

# Write Up:

So I open the binary in IDA Freeware (if you would like to follow along, this code can be found in the "Code" directory)

I scroll down to an interesting statement, "You are a winner!" Figuring this is what I want to accomplish. 

![image](https://user-images.githubusercontent.com/31195314/52674918-12de4d00-2ef3-11e9-8d00-7ef849ac284c.png)

In order to go to the winner block, [ebp+var_1c] must equal 19h (25 in decimal).

So let's write some sudo code of what is occuring...

	greetingMSG = "You have now entered the Duck Web, and you're in for a honkin' good time. Can you figure out my trick?"
	eax = len(password)
	eax++
	var_C = malloc(eax)

	eax = password_length
	eax++
	memset(var_C,0,eax) //push in reverse order; we are overwriting var_C (mem_ptr) with 0s; eax is the amount of 0s we are putting in it
	var_1C = 0
	var_18 = 0

	for(i=0;i++;i<password_length){
		array = [29h, 6, 16h,4Fh,2Bh,35h,30h,1Eh,51h,1Bh,5Bh,14h,4Bh,8,5Dh,2Bh,56h,47h,57h,50h, 16h,4Dh,51h,51h,5Dh,0]
		var_1D = password[i] ^ array[i]
	
		eax = greetingMSG[i]
		
		if(eax == var_1D){
			var_1C++
			}
		if(var_1C==19h){
			printf "winner"
			break
			}
		}

Before we go too far, let's revisit where I found array. 

![capture1](https://user-images.githubusercontent.com/31195314/52680818-e7199200-2f07-11e9-95a5-82c5bf937ec0.PNG)

So this is interesting. Big hex number.... But, it's not being fed as a hex value in and of itself! So lets double click it.

![capture1](https://user-images.githubusercontent.com/31195314/52680992-5c856280-2f08-11e9-8bae-1e79220a5af8.PNG)

It's actually a location of a buffer with values. This is where I got the array from.

So now lets decrypt the encryption. To do this, I wrote the following python script:

	password = []
	greetingMSG = "You have now entered the Duck Web, and you're in for a honkin' good time. Can you figure out my trick?"
	array = "\x29\x06\x16\x4F\x2B\x35\x30\x1E\x51\x1B\x5B\x14\x4B\x08\x5D\x2B\x56\x47\x57\x50\x16\x4D\x51\x51\x5D\x00"
	var = 0
	i = 0
	while(var < 25):
		pw = ord(greetingMSG[i])^ord(array[i])
		i+=1
		var+=1
		password.append(chr(pw))

	passd = ''.join(password)	
	print passd
	
Finally, when ran...

	python quackmedecode.py
	picoCTF{qu4ckm3_35246994}

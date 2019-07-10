import os
from subprocess import PIPE,Popen

# Gets the name of the host (the computer you are ssh'ing to)
proc = Popen(['hostname'], stdout=PIPE)
host_full = proc.communicate()[0].split()[0]
host = host_full.split(".")[0]
print("Getting data from computer: %s..."%host)

if host == "higgs":
	MC_path = "/higgs-data3/sam/forTomRyunAliceLuca/v03/mc"
elif host == "pc2014":
	MC_path = "/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc"
elif host == "pc2012":
	MC_path = "/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc"
	
found_dir = False	# Used to check whether a directory was found or not	

while found_dir == False:
	choice = raw_input("Enter which process you want to analyse: ")

	# Searches the MC directory for sub-directories containing strings of what the user entered
	# Then prints out the paths to all files within the found directory
	for dirnames in os.walk(MC_path):
		for dirname in dirnames:
			if choice in dirname:	
				print("Here's what I found:")
				#print(dirname)					# Gives the path of the chosen MC directory
				found_dir = True
				for filenames in os.walk(dirname):
					filename = filenames[2][0]
					#print(filename)			# Gives the name of the files within the chosen MC directory
					print("\n"+dirname+"/"+filename)	# Writes out the full file path
	if found_dir == False:
		print("I'm sorry, I couldn't find a matching simulation!")


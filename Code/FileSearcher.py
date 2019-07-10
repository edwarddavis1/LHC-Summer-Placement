import ROOT as r
import os
from subprocess import PIPE,Popen

# Gets the name of the host (the computer you are ssh'ing to)
proc = Popen(['hostname'], stdout=PIPE)
host_full = proc.communicate()[0].split()[0]
host = host_full.split(".")[0]
print("Getting data from computer: %s..."%host)

if host == "higgs":
	MC_path = "/higgs-data3/sam/forTomRyunAliceLuca/v03/mc"
	specifics_start = 6	# specifics_start refers to the amount of "."'s before the substring telling you the specifics of the dataset
elif host == "pc2014":
	MC_path = "/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc"
	specifics_start = 7
elif host == "pc2012":
	MC_path = "/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc"
	specifics_start = 7
	
found_dir = False	# Used to check whether a directory was found or not
file_paths = []	
file_specifics = []

while found_dir == False:
	choice = raw_input("Enter which specific process you want to analyse (if multiple words, separate with _): ")
	#choice = "Zee2jets"
	print("Here's what I found:")

	# Searches the MC directory for sub-directories containing strings of what the user entered
	# Then prints out the paths to all files within the found directory
	for dirnames in os.walk(MC_path):
		for dirname in dirnames:
			if choice in dirname:	
				found_dir = True
				for filenames in os.walk(dirname):
										
					# Writes out the full file path
					filename = filenames[2][0]
					file_path = dirname+"/"+filename
					
					# Finds out the specifics of the process e.g. Zee_MV0_70_CVetBVet
					file_specific = "_".join(file_path.split(".")[specifics_start].split("_")[2:]) 
					print(file_specific)
					#print(file_path)	
					file_paths.append(file_path)
					file_specifics.append(file_specific)	
										
	if found_dir == False:
		print("I'm sorry, I couldn't find a matching simulation!")

print("Are you sure you want to analyse all %i of these simulations?\n"%len(file_paths))
confirm_run = raw_input("y/n: ")

if confirm_run == "y":

	# Analysis 
	print("\nBegining analysis...")
	for i in range(len(file_paths)):
		print("Analysing %s, %i/%i"%(file_specifics[i],i+1,len(file_paths)))
		with open(os.path.join("Headers","ChosenFile.h"), "w") as text_file:
			text_file.write("decay_chain_file = "+'"%s";\nchoice = "%s";'%(file_paths[i],file_specifics[i]))

		r.gROOT.Reset()
		r.gROOT.ProcessLine(".L MC_Analysis.C")
		r.gROOT.ProcessLine("MC_Analysis t")
		r.gROOT.ProcessLine("t.Loop();")
	
		if i != len(file_paths)-1:
			r.gROOT.ProcessLine(".q")
		else:
			r.gROOT.ProcessLine("new TBrowser")
			os.system("root -l")

else:
	print("Analysis aborted...Restarting...")
	os.system("python FileSearcher.py")








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
	
found_dir = None	# Used to check whether a directory was found or not
file_paths = []	
chain_names = []

while found_dir == None:
	user_input = raw_input("Enter which specific process you want to analyse (if multiple words, separate with _): ")
	#user_input = "Zee2jets"
	user_input = user_input.replace(" ","")	# remove spaces
	chains = user_input.split(",")	# get list of chains from input
	print("Here's what I found:")

	# Searches the MC directory for sub-directories containing strings of what the user entered
	# Then prints out the paths to all files within the found directory
	for i in range(len(chains)):
		if found_dir == None:
			found_dir = None
		else:
			found_dir = False
		for dirnames in os.walk(MC_path):
			for dirname in dirnames:
				if chains[i] in dirname:	
					found_dir = True
					for filenames in os.walk(dirname):
										
						# Writes out the full file path
						filename = filenames[2][0]
						file_path = dirname+"/"+filename
					
						# Finds out the specifics of the process e.g. Zee_MV0_70_CVetBVet
						file_specific = "_".join(file_path.split(".")[specifics_start].split("_")[2:])
						
						# Remove duplicate processes found in higgs
						if file_specific not in chain_names:
							print(file_specific)
							file_paths.append(file_path)
							chain_names.append(file_specific)
										
		if found_dir == False or found_dir == None:
			print("I'm sorry, I couldn't find a matching simulation to %s!"%chains[i])

print("Are you sure you want to analyse all %i of these simulations?\n"%len(file_paths))
confirm_run = raw_input("y/n: ")

if confirm_run == "y":

	# ------ ANALYSIS ------ #
	print("\nBegining analysis...")
	
	for i in range(len(file_paths)):
		print(i)
		print("Analysing %s, %i/%i"%(chain_names[i],i+1,len(file_paths)))

		r.gROOT.Reset()
		r.gROOT.ProcessLine(".L MC_Analysis.C")
		#r.gROOT.ProcessLine("MC_Analysis t")
		#r.gROOT.ProcessLine("t.Loop()")
		r.gROOT.ProcessLine('TFile *file_%s = new TFile("%s")'%(chain_names[i],file_paths[i]))
		r.gROOT.ProcessLine("TTree *tree_%s = new TTree"%chain_names[i])
		r.gROOT.ProcessLine('file_%s->GetObject("NOMINAL",tree_%s)'%(chain_names[i],chain_names[i]))

		# create new instance of MC_Analysis and loop over events
		r.gROOT.ProcessLine("MC_Analysis* t_%s = new MC_Analysis(tree_%s)"%(chain_names[i],chain_names[i]))
		r.gROOT.ProcessLine("t_%s->Loop()"%chain_names[i])

		os.system("mv outfile.root OutputFiles/" + chain_names[i] + ".root")
	
		if i != len(file_paths)-1:
			r.gROOT.ProcessLine(".q")
		else:
			r.gROOT.ProcessLine("new TBrowser")
			os.system("root -l")
	
else:
	print("Analysis aborted...Restarting...")
	os.system("python FileSearcher.py")








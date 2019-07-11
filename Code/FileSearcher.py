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
	user_input = raw_input("Enter which specific process(es) you want to analyse: ")
	#user_input = "Zee2jets"
	user_input = user_input.replace(" ","")	# remove spaces
	chains = user_input.split(",")	# get list of chains from input
	print("Here's what I found:\n")

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
					
						# Finds out the name of the chain e.g. Zee_MV0_70_CVetBVet
						chain_name = "_".join(file_path.split(".")[specifics_start].split("_")[2:])
						
						# Remove duplicate processes found in higgs
						if chain_name not in chain_names:
							print(chain_name)
							file_paths.append(file_path)
							chain_names.append(chain_name)
										
		if found_dir == False or found_dir == None:
			print("I'm sorry, I couldn't find a matching simulation to %s!"%chains[i])

print("\nI found %i simulations\n"%len(file_paths))
run_analysis = False
run_chain = False
run_restart = False
while run_analysis == False and run_chain == False and run_restart == False:
	print("Would you like to (a): Analyse these files, (b): Chain these files, (c): Analyse, then chain these files, or (d): Restart?")
	run_choice = raw_input("Input: ").lower()
	
	if run_choice == 'a':
		run_analysis = True
	elif run_choice == 'b':
		run_chain = True
	elif run_choice == 'c':
		run_analysis = True
		run_chain = True
	elif run_choice == 'd':
		run_restart = True
	else:
		print("Error: please type either a, b, c or d")

if run_analysis == True:

	# ------ ANALYSIS ------ #
	print("\nBegining analysis...")
	
	for i in range(len(file_paths)):
		print(i)
		print("Analysing %s, %i/%i"%(chain_names[i],i+1,len(file_paths)))

		# Reset environment
		r.gROOT.Reset()
		
		# Load in macro
		r.gROOT.ProcessLine(".L MC_Analysis.C")
		
		# Load in tree from file
		r.gROOT.ProcessLine('TFile *file_%s = new TFile("%s")'%(chain_names[i],file_paths[i]))
		r.gROOT.ProcessLine("TTree *tree_%s = new TTree"%chain_names[i])
		r.gROOT.ProcessLine('file_%s->GetObject("NOMINAL",tree_%s)'%(chain_names[i],chain_names[i]))	# "NOMINAL" is the object got by the new tree from the file

		# Create new instance of MC_Analysis and loop over events
		r.gROOT.ProcessLine("MC_Analysis* t_%s = new MC_Analysis(tree_%s)"%(chain_names[i],chain_names[i]))
		r.gROOT.ProcessLine("t_%s->Loop()"%chain_names[i])

		# Rename output file as the chain name and put into OutputFiles
		os.system("mv outfile.root OutputFiles/%s.root"%chain_names[i])
	
		if i != len(file_paths)-1:
			r.gROOT.ProcessLine(".q")
		else: 
			r.gROOT.ProcessLine("new TBrowser")
			os.system("root -l")
			
if run_chain == True:
	print("\nMaking chain...")
	
	# Store the histograms from the first seciton of data in a list
	totHist = []
	sec0 = r.TFile("OutputFiles/%s.root"%chain_names[0])	# first file
	key0 = sec0.GetListOfKeys()				# first list of keys
	for j in range(len(key0)):
		totHist.append(sec0.Get(key0[j].GetName()))

	# Loop over other output files
	for i in range(1, len(chain_names)):

		# Read in the output file fofr this seciton of data
		secFile = r.TFile("OutputFiles/%s.root"%chain_names[i])

		# Get histogram keys
		keys = secFile.GetListOfKeys()

		# Loop over histograms in the file and add them cumulatively
		for j in range(len(keys)):
			totHist[j].Add(secFile.Get(keys[j].GetName()))
	
		# Save the combined histograms to a file
		totFile = r.TFile("OutputFiles/%s.root"%chains[0],"RECREATE")
		for hist in totHist:
			hist.Write()
		totFile.Close()
	print("Chain %s Complete!"%chains[0])
	r.gROOT.ProcessLine("new TBrowser")
	os.system("root -l")

if run_restart == True:
	print("\nAnalysis aborted...Restarting...\n")
	os.system("python FileSearcher.py")








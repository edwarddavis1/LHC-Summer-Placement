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
	chain_start = 6	# chain_start refers to the amount of "."'s before the substring telling you the specifics of the dataset
elif host == "pc2014":
	MC_path = "/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc"
	chain_start = 7
elif host == "pc2012":
	MC_path = "/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc"
	chain_start = 7
	
found_dir = None	# Used to check whether a directory was found or not
file_paths = []		# List of chosen file paths
chain_names = []	# List of chosen file chain names
file_sizes = []		# List of file sizes
files_analysed = []	# List of whether files have been previously analysed or not

while found_dir == None:
	user_input = raw_input("Enter which specific process(es) you want to analyse: ")
	#user_input = "Zee2jets"
	user_input = user_input.replace(" ","")	# remove spaces	
	chains = user_input.split(",")	# get list of chains from input
	
	# Prevent bug where by typing "Ztt" all the files get chose (/mc directory contains the sub-string "Ztt")
	for i in range(len(chains)):
		if chains[i] == "Ztt":
			chains[i] = "Ztt_"
	
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
				if chains[i] in dirname and dirname != MC_path:	# prevents the program grabbing the /mc directory
					found_dir = True
					for filenames in os.walk(dirname):
						# Writes out the full file path
						filename = filenames[2][0]
						file_path = dirname+"/"+filename
											
						# Finds out the name of the chain e.g. Zee_MV0_70_CVetBVet
						chain_name = "_".join(file_path.split(".")[chain_start].split("_")[2:])
						
						# Remove duplicate processes found in higgs
						if chain_name not in chain_names:
							file_size = os.path.getsize(file_path)/1e9	# Gets the size of file in GB
							file_exist = os.path.exists("OutputFiles/"+chain_name+".root")
							if file_exist == True:
								file_analysed = "Analysed"
							else:
								file_analysed = "Not Analysed"
								
							# Bodge to get nice columns (yeah ik it's dumb but it works)
							if len(chain_name) < 8:
								print("%s				%.2f GB		%s"%(chain_name,file_size,file_analysed))
							elif len(chain_name)>=8 and len(chain_name) < 16:
								print("%s			%.2f GB		%s"%(chain_name,file_size,file_analysed))
							elif len(chain_name)>=16 and len(chain_name)<24:
								print("%s		%.2f GB		%s"%(chain_name,file_size,file_analysed))
							else:
								print("%s	%.2f GB		%s"%(chain_name,file_size,file_analysed))
							file_paths.append(file_path)
							chain_names.append(chain_name)
							file_sizes.append(file_size)
							files_analysed.append(file_exist)
										
		if found_dir == False or found_dir == None:
			print("I'm sorry, I couldn't find a matching simulation to %s!"%chains[i])

print("\nI found %i simulations\n"%len(file_paths))
run_analysis = False
run_sum = False
run_stack = False
run_new = False
run_restart = False
while run_analysis == False and run_sum == False and run_stack == False and run_restart == False and run_new == False:
	print("Would you like to\n (a): Analyse these files\n (b): Sum these files       (c): Analyse, then sum these files\n (d): Stack these files     (e): Analyse, then stack these files\n (f): Analyse files not previously analysed\n (g): Restart?")
	run_choice = raw_input("Input: ").lower()
	
	if run_choice in ['a','c','e']:
		run_analysis = True
	if run_choice in ['b', 'c']:
		run_sum = True
		sum_name = raw_input("Name your summed data: ")
	if run_choice in ['d', 'e']:
		run_stack = True
		#stack_hist = raw_input("Which histogram would you like to stack?: ")
		#stack_name = stack_hist+'_stack'
		#stack_title = raw_input("Title your stack: ")
	if run_choice == 'f':
		run_new = True
	if run_choice == 'g':
		run_restart = True
	if run_choice not in ['a', 'b', 'c', 'd', 'e', 'f', 'g']:
		print("Error: please type either option a, b, c, d, e, f or g")

if run_new == True:
	popped=0
	for i in range(len(files_analysed)):
		if files_analysed[i]==True:	# If the file previously existed
			file_paths.pop(i-popped)
			chain_names.pop(i-popped)
			file_sizes.pop(i-popped)
			popped+=1
	print("Comfirm analysis of these %i simulations: "%len(chain_names))
	for i in range(len(chain_names)):
	
	# Bodge again
		if len(chain_names[i]) < 8:
			print("%s				%.2f GB"%(chain_names[i],file_sizes[i]))
		elif len(chain_names[i])>=8 and len(chain_names[i]) < 16:
			print("%s			%.2f GB"%(chain_names[i],file_sizes[i]))
		elif len(chain_names[i])>=16 and len(chain_names[i])<24:
			print("%s		%.2f GB"%(chain_names[i],file_sizes[i]))
		else:
			print("%s	%.2f GB	"%(chain_names[i],file_sizes[i]))
	confirm_run = False
	while confirm_run != True:
		confirm_run = raw_input("y/n: ")
		if confirm_run == 'y':
			confirm_run = True
			run_analysis=True
		elif confirm_run == 'n':
			confirm_run = True
			run_analysis=False
			run_restart=True
		
if run_analysis == True:

	# ------ ANALYSIS ------ #
	print("\nBegining analysis...")
	print("Updating Histogram booking...")
	os.system("python Auto_Histogram_Book.py")
	
	
	
	for i in range(len(file_paths)):
		print("Analysing %s	%.2f GB, (%i/%i)"%(chain_names[i],file_sizes[i],i+1,len(file_paths)))
	
		with open("Headers/ChosenFile.h",'w') as ChoiceFile:
			if run_sum == False:
				ChoiceFile.write('choice = "%s";'%chain_names[i])
			else:
				ChoiceFile.write('choice = "%s";'%sum_name)
		ChoiceFile.close()

		# Reset environment
		r.gROOT.Reset()
	
		# Load in macro
		r.gROOT.SetBatch(True)	# Turn on batch mode so that any graphics are blocked from opening
		r.gROOT.ProcessLine(".L MC_Analysis.C")
	
		# Load in tree from file
		r.gROOT.ProcessLine('TFile *file_%s = new TFile("%s")'%(chain_names[i],file_paths[i]))
		r.gROOT.ProcessLine("TTree *tree_%s = new TTree"%chain_names[i])
		r.gROOT.ProcessLine('file_%s->GetObject("NOMINAL",tree_%s)'%(chain_names[i],chain_names[i]))	# "NOMINAL" is the object got by the new tree from 																the file
		if run_stack == True:
			print("This has not been programmed yet!")


		# Create new instance of MC_Analysis and loop over events
		r.gROOT.ProcessLine("MC_Analysis* t_%s = new MC_Analysis(tree_%s)"%(chain_names[i],chain_names[i]))
		r.gROOT.ProcessLine("t_%s->Loop()"%chain_names[i])

		# Rename output file as the chain name and put into OutputFiles
		if run_sum == True:
			os.system("mv outfile.root OutputFiles/%s.root"%chain_names[i])
		if run_sum == False:
			os.system("mv outfile.root OutputFiles/%s.root"%chain_names[i])

		if i != len(file_paths)-1:
			r.gROOT.ProcessLine(".q")
		if i == len(file_paths)-1 and run_sum == False: 
			r.gROOT.SetBatch(False)	# Turn batch mode off so that TBrowser can start after analysis
			r.gROOT.ProcessLine("new TBrowser")
			os.system("root -l")
			
if run_sum == True:
	print("\nSumming Histograms...")
	
	# Store the histograms from the first seciton of data in a list
	totHist = []
	sec0 = r.TFile("OutputFiles/%s.root"%chain_names[0])	# first file
	key0 = sec0.GetListOfKeys()				# first list of keys
	for j in range(len(key0)):
		totHist.append(sec0.Get(key0[j].GetName()))

	# Loop over other output files
	for i in range(1, len(chain_names)):

		# Read in the output file for this seciton of data
		secFile = r.TFile("OutputFiles/%s.root"%chain_names[i])

		# Get histogram keys
		keys = secFile.GetListOfKeys()

		# Loop over histograms in the file and add them cumulatively
		for j in range(len(keys)):
			totHist[j].Add(secFile.Get(keys[j].GetName()))
	
		# Save the combined histograms to a file
		totFile = r.TFile("OutputFiles/%s.root"%sum_name,"RECREATE")
		for hist in totHist:
			hist.Write()
		totFile.Close()
		
	print("Sum %s Complete!"%chains[0])
	r.gROOT.ProcessLine("new TBrowser")
	os.system("root -l")

if run_restart == True:
	print("\nAnalysis aborted...Restarting...\n")
	os.system("python FileSearcher.py")








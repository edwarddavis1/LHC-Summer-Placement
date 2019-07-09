import ROOT as r
import os



processes = ["zee2jets", "zmumu2jets", "ztt2jets"] 

year = 2012	# Used to change between the pc2012 and pc2014 datasets
if year == 2014:
	data_paths = {"zee2jets":"/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308092.Sh221_PDF30_Zee2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14357856._000001.hist-output.root", 
	       
		"zmumu2jets":"/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308093.Sh221_PDF30_Zmm2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14357860._000001.hist-output.root", 
	       
		"ztt2jets":"/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308094.Sh221_PDF30_Ztt2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14361308._000001.hist-output.root",
		
		} 
elif year == 2012: # Just change "/pc2014-data4" to "/pc2012-data1"
	data_paths = {"zee2jets":"/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308092.Sh221_PDF30_Zee2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14357856._000001.hist-output.root", 
	       
		"zmumu2jets":"/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308093.Sh221_PDF30_Zmm2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14357860._000001.hist-output.root", 
	       
		"ztt2jets":"/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308094.Sh221_PDF30_Ztt2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14361308._000001.hist-output.root" 
		}

choice = raw_input("Enter Decay Chains, Separated by Commas: ").lower()	# remove case sensitivity

#choice = "ztt2jets, ztt2jets"
choice = choice.replace(" ","") 	# remove spaces
chains = choice.split(",")		# get list of series of chains from string

for i in range(len(chains)):
	if chains[i] in processes: 
		print("Now analysing %s..."%chains[i])      
		i+=1
	else: 
		print("Decay chain %s not recognised...please retype all chains entered. Choose from: "%(chains[i],chains[i]),processes) 
		choice= raw_input("Input: ")
		choice = choice.replace(" ","")
		chains = choice.split(",")
	
	chosen_file = data_paths[chains[i-1]] 

	with open(os.path.join("Headers","ChosenFile.h"), "w") as text_file:
		text_file.write("decay_chain_files = "+'"%s";\nchoice = "%s";'%(chosen_file,chains[i-1]))

	r.gROOT.Reset()
	r.gROOT.ProcessLine(".L MC_Analysis.C")
	r.gROOT.ProcessLine("MC_Analysis t")
	r.gROOT.ProcessLine("t.Loop();")
	
	if i != len(chains):
		r.gROOT.ProcessLine(".q")
	else:
		r.gROOT.ProcessLine("new TBrowser")
		os.system("root -l")


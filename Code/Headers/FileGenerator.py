import ROOT as r
import os



processes = ["zee2jets", "zmumu2jets", "ztt2jets", "zqqzll","zqqzll_2",
		"zmumu_mv0_70_cvetbvet","zmumu_mv0_70_cfilbvet"] 

year = 2012	# Used to change between the pc2012 and pc2014 datasets
if year == 2014:
	data_paths = {"zee2jets":"/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308092.Sh221_PDF30_Zee2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14357856._000001.hist-output.root", 
	       
		"zmumu2jets":"/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308093.Sh221_PDF30_Zmm2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14357860._000001.hist-output.root", 
	       
		"ztt2jets":"/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308094.Sh221_PDF30_Ztt2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14361308._000001.hist-output.root",
		
		"zqqzll":"/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.363356.Sh221_PDF30_ZqqZll.D1.e5525_s3126_r9364_r9315_p3371.sv1_hist/user.sdysch.14362495._000001.hist-output.root",
		
		"zqqzll_2":"/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.363356.Sh221_PDF30_ZqqZll.D1.e5525_s3126_r9364_r9315_p3371.sv1_hist/user.sdysch.14362495._000002.hist-output.root",
		
		"zmumu_mv0_70_cvetbvet":"/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.364100.Sh221_PDF30_Zmumu_MV0_70_CVetBVet.D1.e5271_s3126_r9364_r9315_p3371.sv1_hist/user.sdysch.14362886._000001.hist-output.root",

		"zmumu_mv0_70_cfilbvet":"/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.364101.Sh221_PDF30_Zmumu_MV0_70_CFilBVet.D1.e5271_s3126_r9364_r9315_p3371.sv1_hist/user.sdysch.14362915._000001.hist-output.root"
		}

		
elif year == 2012: # Just change "/pc2014-data4" to "/pc2012-data1"
	data_paths = {"zee2jets":"/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308092.Sh221_PDF30_Zee2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14357856._000001.hist-output.root", 
	       
		"zmumu2jets":"/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308093.Sh221_PDF30_Zmm2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14357860._000001.hist-output.root", 
	       
		"ztt2jets":"/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308094.Sh221_PDF30_Ztt2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14361308._000001.hist-output.root",
		
		"zqqzll":"/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.363356.Sh221_PDF30_ZqqZll.D1.e5525_s3126_r9364_r9315_p3371.sv1_hist/user.sdysch.14362495._000001.hist-output.root",
		
		"zqqzll_2":"/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.363356.Sh221_PDF30_ZqqZll.D1.e5525_s3126_r9364_r9315_p3371.sv1_hist/user.sdysch.14362495._000002.hist-output.root",
		
		"zmumu_mv0_70_cvetbvet":"/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.364100.Sh221_PDF30_Zmumu_MV0_70_CVetBVet.D1.e5271_s3126_r9364_r9315_p3371.sv1_hist/user.sdysch.14362886._000001.hist-output.root",

		"zmumu_mv0_70_cfilbvet":"/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.364101.Sh221_PDF30_Zmumu_MV0_70_CFilBVet.D1.e5271_s3126_r9364_r9315_p3371.sv1_hist/user.sdysch.14362915._000001.hist-output.root" 
		}

choice = raw_input("Enter Decay Chains, Separated by Commas or type all: ")
#choice = "ztt2jets, ztt2jets"

choice = choice.lower()			# remove case sensitivity
choice = choice.replace(" ","") 	# remove spaces
chains = choice.split(",")		# get list of series of chains from string
print(chains)
if chains[0] == "all":
	print("here")
	chains = []
	chains = processes

accepted = False
for i in range(len(chains)):
	while accepted == False:
		if chains[i] in processes: 
			print("Now analysing %s..."%chains[i])      
			accepted = True
		else: 
			print(chains[i])
			print("Decay chain %s not recognised...please retype all chains entered. Choose from: "%chains[i],processes) 
			choice= raw_input("Input: ")
			choice = choice.replace(" ","")
			chains = choice.split(",")
			accepted = False
	
	chosen_file = data_paths[chains[i-1]] 

	with open(os.path.join("Headers","ChosenFile.h"), "w") as text_file:
		text_file.write("decay_chain_files = "+'"%s";\nchoice = "%s";'%(chosen_file,chains[i]))

	r.gROOT.Reset()
	r.gROOT.ProcessLine(".L MC_Analysis.C")
	r.gROOT.ProcessLine("MC_Analysis t")
	r.gROOT.ProcessLine("t.Loop();")
	
	if i != len(chains)-1:
		r.gROOT.ProcessLine(".q")
	else:
		r.gROOT.ProcessLine("new TBrowser")
		os.system("root -l")


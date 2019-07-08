import ROOT as r
import os



processes = ["Zee2jets", "Zmumu2jets", "Ztt2jets"] 

choice= raw_input("Enter a Decay Chain: ") 
#choice = "Zee2jets"  

accept = False     # will become true when an accepted analysis type is entered  
while accept == False: 
    if choice in processes: 
        print("Now analysing %s..."%choice) 
        accept = True        

    else: 
        print("Decay chain not recognised... Choose one of: ",processes) 
        choice= raw_input("Input: ") 
        

data_paths = {"Zee2jets":"/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308092.Sh221_PDF30_Zee2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14357856._000001.hist-output.root", 
       
        "Zmumu2jets":"/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308093.Sh221_PDF30_Zmm2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14357860._000001.hist-output.root", 
       
        "Ztt2jets":"/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308094.Sh221_PDF30_Ztt2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14361308._000001.hist-output.root" 
        } 

chosen_file = data_paths[choice] 
print(chosen_file) 

with open(os.path.join("Headers","ChosenFile.h"), "w") as text_file:
	text_file.write("decay_chain_file = "+'"%s";'%chosen_file)





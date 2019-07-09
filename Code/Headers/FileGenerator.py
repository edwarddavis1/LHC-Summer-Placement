import ROOT as r 

import os 

  

  

  

processes = ["zee2jets", "zmumu2jets", "ztt2jets"]  

  

year = 2012    # Used to change between the pc2012 and pc2014 datasets 

  

choice = raw_input("Enter a Decay Chain: ").lower()    # remove case sensitivity 

choice = choice.replace(" ","")             # remove any spaces from list 

  

  

#choice = "zee2jets"   

  

accept = False     # will become true when an accepted analysis type is entered   

while accept == False:  

    if choice in processes:  

        print("Now analysing %s..."%choice)  

        accept = True         

  

    else:  

        print("Decay chain not recognised... Choose one of: ",processes)  

        choice= raw_input("Input: ")  

         

if year == 2014: 

    data_paths = {"Zee2jets":"/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308092.Sh221_PDF30_Zee2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14357856._000001.hist-output.root",  

            

        "Zmumu2jets":"/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308093.Sh221_PDF30_Zmm2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14357860._000001.hist-output.root",  

            

        "Ztt2jets":"/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308094.Sh221_PDF30_Ztt2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14361308._000001.hist-output.root"  

        }  

elif year == 2012: # Just change "/pc2014-data4" to "/pc2012-data1" 

    data_paths = {"Zee2jets":"/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308092.Sh221_PDF30_Zee2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14357856._000001.hist-output.root",  

            

        "Zmumu2jets":"/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308093.Sh221_PDF30_Zmm2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14357860._000001.hist-output.root",  

            

        "Ztt2jets":"/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc/user.sdysch.v5.0.mc16_13TeV.308094.Sh221_PDF30_Ztt2jets_Min_N_TChannel.D1.e5767_e5984_s3126_r9364_r9315_p3563.sv1_hist/user.sdysch.14361308._000001.hist-output.root"  

        }  

chosen_file = data_paths[choice]  

print(chosen_file)  

  

with open(os.path.join("Headers","ChosenFile.h"), "w") as text_file: 

    text_file.write("decay_chain_file = "+'"%s";\nchoice = "%s";'%(chosen_file,choice)) 

  

r.gROOT.Reset() 

r.gROOT.ProcessLine(".L MC_Analysis.C") 

r.gROOT.ProcessLine("MC_Analysis t") 

r.gROOT.ProcessLine("t.Loop();") 

  

os.system("root -l") 

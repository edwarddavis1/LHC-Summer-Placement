import ROOT as r
import os
from subprocess import PIPE, Popen
import datetime


def SumHistograms(chain_names, sum_name, single_sim):
    print("\nSumming Histograms...")

    # store the histograms from the first seciton of data in a list
    totHist = []
    if single_sim is False:
        sec0 = r.TFile("OutputFiles/%s.root" % chain_names[0])
    else:
        sec0 = r.TFile("OutputFiles/IndividualHistograms/%s" %
                       chain_names[0])
    key0 = sec0.GetListOfKeys()
    for j in range(len(key0)):
        totHist.append(sec0.Get(key0[j].GetName()))

    for i in range(1, len(chain_names)):
        if single_sim is False:
            secFile = r.TFile("OutputFiles/%s.root" % chain_names[i])
        else:
            secFile = r.TFile("OutputFiles/IndividualHistograms/%s" %
                              chain_names[i])
        keys = secFile.GetListOfKeys()

        # loop over histograms in the file and add them cumulatively
        for j in range(len(keys)):
            totHist[j].Add(secFile.Get(keys[j].GetName()))
        if single_sim is False:
            totFile = r.TFile("OutputFiles/%s.root" % sum_name, "RECREATE")
        else:
            totFile = r.TFile("OutputFiles/%s.root" %
                              sum_name, "RECREATE")
        for hist in totHist:
            hist.Write()
        totFile.Close()

    print("Sum %s Complete!" % sum_name)

# --------------------------- PRE-SEARCH STUFF ------------------------------ #


# Gets the name of the host (the computer you are ssh'ing to)
proc = Popen(['hostname'], stdout=PIPE)
host_full = proc.communicate()[0].split()[0]
host = host_full.split(".")[0]
print("Getting data from computer: %s..." % host)

if host == "higgs":
    MC_path = "/higgs-data3/sam/forTomRyunAliceLuca/v03/mc"
    data_path = "/higgs-data3/sam/forTomRyunAliceLuca/v03/data"
    # amount of '.' before chain name
    chain_start = 6
elif host == "pc2014":
    MC_path = "/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc"
    data_path = "/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/data"
    chain_start = 7
elif host == "pc2012":
    MC_path = "/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc"
    data_path = "/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/data"
    chain_start = 7

found_dir = None
subchains = []              # List of input strings that are separeted by '&'
hist_paths = []             # Contains all histograms for a given chain
file_paths = []
chain_names = []
higgs_lums = []
file_sizes = []
files_analysed = []
file_times = []
files_last_run = []
second_substring = []
file_time_total_s = 0

# Formats the Process times correctly
new_lines = []
with open("ProcessTimes.txt", "r") as f:
    lines = f.readlines()
    for line in lines:

        # skips lines with no time info
        if line.split(':')[0] == '':
            continue
        try:
            line.split(':')[3]
        except:
            continue

        chain_name = line.split(':')[-3]
        time_info = line.split(':')[0:-3]
        last_run = ':'.join(line.split(':')[-2:])
        time_info = [int(i) for i in time_info]

        hist_num = len(time_info) / 2

        min_all = time_info[::2]
        sec_all = time_info[1::2]

        total_in_sec = sum(min_all) * 60 + sum(sec_all)
        min_total = int(total_in_sec / 60)
        sec_total = total_in_sec - min_total * 60

        new_lines.append("%s:%s:%s:%s" % (min_total, sec_total,
                                          chain_name, last_run))
f.close()

with open("ProcessTimes.txt", "w") as f:
    for new_line in new_lines:
        f.write(new_line)
f.close()

# ---------------------------- SEARCH FILES ----------------------------------#

while found_dir is None:
    subchains[:] = []
    user_input = raw_input("Enter which specific process(es) you want "
                           "to analyse: ")
    user_input = user_input.replace(" ", "")
    chains = user_input.split(",")

    # Prevent bug where by typing "Ztt" all the files get chosen
    # (/mc directory contains the sub-string "Ztt")
    for i in range(len(chains)):
        if chains[i] == "Ztt":
            chains[i] = "Ztt_"

    # Allow for multiple substrings to search for a single chain name if
    # separated by &
    for i in range(len(chains)):
        subchain = chains[i].split("&")
        subchains.append(subchain)

    print("Here's what I found:\n")

    # Searches the MC directory for sub-directories containing strings of
    # what the user entered
    for i in range(len(chains)):
        if found_dir is None:
            found_dir = None
        else:
            found_dir = False

        for dirnames in os.walk(MC_path):
            for dirname in dirnames:
                # prevents the program grabbing the /mc directory
                if subchains[i][0] not in dirname or dirname == MC_path:
                    break
                # if all the strings separated by '&' are present in a single
                # directoy name
                if all(substr in dirname for substr in subchains[i]):
                    found_dir = True
                    for filenames in os.walk(dirname):

                        dir_path = filenames[0]         # Path to MC directory

                        # list of histograms within the MC directory
                        hist_files = filenames[2]

                        # get all the paths to all the histograms
                        # file sizes = sum of histogram sizes
                        file_size = 0
                        del hist_paths[:]
                        for hist_file in hist_files:
                            hist_path = dir_path + "/" + hist_file
                            hist_paths.append(hist_path)
                            # get size of the file (file = all the hists)
                            file_size += os.path.getsize(hist_path) / 1e9

                        # file_paths didn't append the hist_paths array
                        # properly so done this as a bodge
                        hists_str = ','.join(hist_paths)

                        chain_name = "_".join(dir_path.split(
                            ".")[chain_start].split("_")[2:])

                        # Fixes bug where some chains were missed
                        if chain_name == "":
                            chain_name = "_".join(dir_path.split(
                                ".")[chain_start].split("_")[1:])

                        if host == 'higgs':
                            higgs_lum_line = dir_path.split(".")[8]
                            higgs_lum = higgs_lum_line.split("_")[2]
                            chain_name = "_".join([chain_name, higgs_lum])

                        file_exist = os.path.exists(
                            "OutputFiles/" + chain_name + ".root")
                        if file_exist is True:
                            file_analysed = "Analysed"
                        else:
                            file_analysed = "Not Analysed"

                        # reads previous simulation times
                        file_time = ""
                        file_last_run = ""
                        for line in reversed(list(open("ProcessTimes.txt"))):
                            start_is_time = str.isdigit(line.split(':')[0])
                            if chain_name in line and start_is_time:
                                file_time_m = line.split(':')[0]
                                file_time_s = line.split(':')[1]
                                file_time_total_s += int(file_time_s) + \
                                    int(file_time_m) * 60
                                if file_time_m == '0':
                                    file_time = "%s sec" % file_time_s
                                else:
                                    file_time = "%s min %s sec" % (
                                        file_time_m, file_time_s)

                                file_last_run = str(line.split(':')[3]) + \
                                    ':' + str(line.split(':')[4].rstrip())
                                break
                        print('{:35s} {:.2f} GB	{:16} {}'.format(
                            chain_name, file_size, file_time,
                            file_last_run))
                        file_paths.append(hists_str)
                        chain_names.append(chain_name)
                        file_sizes.append(file_size)
                        files_analysed.append(file_exist)
                        file_times.append(file_time)

        if found_dir is False or found_dir is None:
            print("I'm sorry, I couldn't find a matching simulation to %s!" %
                  chains[i])

file_time_total_h = int(round(file_time_total_s / 3600))
file_time_total_m = int(round(file_time_total_s / 60)) - file_time_total_h * 60
file_time_total_s = (file_time_total_s - file_time_total_m * 60
                     - file_time_total_h * 3600)
print("\nI found %i simulations, total time: %i h %i min %i sec\n" %
      (len(chain_names), file_time_total_h, file_time_total_m,
       file_time_total_s))
run_analysis = False
run_sum = False
run_stack = False
run_new = False
run_restart = False
while (run_analysis is False and run_sum is False and run_stack is False and
        run_restart is False and run_new is False):
    print("Would you like to\n (a): Analyse these files\n "
          "(b): Sum these files       (c): Analyse, then sum these files\n"
          " (d): Analyse files not previously analysed\n (e): Restart?")
    run_choice = raw_input("Input: ").lower()

    if run_choice in ['a', 'c']:
        run_analysis = True
    if run_choice in ['b', 'c']:
        run_sum = True
        sum_name = raw_input("Name your summed data: ")
    if run_choice == 'd':
        run_new = True
    if run_choice == 'e':
        run_restart = True
    if run_choice not in ['a', 'b', 'c', 'd', 'e']:
        print("Error: please type either option a, b, c, d or e")

if run_new is True:
    popped = 0
    for i in range(len(files_analysed)):
        # if the file previously existed
        if files_analysed[i] is True:
            file_paths.pop(i - popped)
            chain_names.pop(i - popped)
            file_sizes.pop(i - popped)
            file_times.pop(i - popped)
            popped += 1

    print("Comfirm analysis of these %i simulations: " % len(chain_names))
    for i in range(len(chain_names)):
        print('{:27s} {:.2f} GB	{:6}'.format(
            chain_names[i], file_sizes[i], file_times[i]))
    confirm_run = False

    while confirm_run is not True:
        confirm_run = raw_input("y/n: ")

        if confirm_run == 'y':
            confirm_run = True
            run_analysis = True

        elif confirm_run == 'n':
            confirm_run = True
            run_analysis = False
            run_restart = True

if run_analysis is True:

    # ------ ANALYSIS ------ #
    print("\nBegining analysis...")
    print("Updating Histogram booking...")
    os.system("python Auto_Histogram_Book.py")

    for i in range(len(file_paths)):
        print("Analysing {}	{}, ({}/{})".format(chain_names[i], file_times[i],
                                                i + 1, len(file_paths)))

        file_last_run = str(
            datetime.datetime.now().strftime("%m-%d %H:%M"))
        files_last_run.append(file_last_run)

        hists_analysed = 0
        hist_paths = file_paths[i].split(',')

        hist_storenames = []
        for hist_path in hist_paths:
            # file name in the MC directory
            hist_filename = hist_path.split('/')[-1]
            # file name to be stored as
            hist_storename = chain_names[i] + '_' + hist_filename
            hist_storenames.append(hist_storename)

            hists_analysed += 1
            total_hists = len(hist_paths)
            print("    Analysing histogram %s/%s" % (hists_analysed,
                                                     total_hists))

            r.gROOT.Reset()
            r.gROOT.SetBatch(True)
            r.gROOT.ProcessLine(".L MC_Analysis.C")
            r.gROOT.ProcessLine('TFile *file_%s = new TFile("%s")' %
                                (chain_names[i], hist_path))
            r.gROOT.ProcessLine("TTree *tree_%s = new TTree" % chain_names[i])
            # "NOMINAL" is the object got by the new tree from the file
            r.gROOT.ProcessLine('file_%s->GetObject("NOMINAL",tree_%s)' %
                                (chain_names[i], chain_names[i]))
            r.gROOT.ProcessLine(
                "MC_Analysis* t_%s = new MC_Analysis(tree_%s)" % (chain_names[i],
                                                                  chain_names[i]))
            r.gROOT.ProcessLine("t_%s->Loop()" % chain_names[i])

            os.system("mv outfile.root OutputFiles/IndividualHistograms"
                      "/%s" % hist_storename)

            if hist_path == hist_paths[-1]:
                SumHistograms(hist_storenames, chain_names[i], single_sim=True)

        # records the process time if the process was not interruped
        with open("ProcessTimes.txt", "r") as f:
            lines = f.readlines()
        with open("ProcessTimes.txt", "a") as f:
            for line in lines:
                failed_run = False
                try:
                    line.split(':')[1]
                except:
                    failed_run = True
            if failed_run is False:
                print("Writing process times")
                f.write(chain_names[i])
                f.write(':' + files_last_run[i] + "\n")
        f.close()

        if i != len(file_paths) - 1:
            r.gROOT.ProcessLine(".q")
        if i == len(file_paths) - 1 and run_sum is False:
            r.gROOT.SetBatch(False)
            # r.gROOT.ProcessLine("new TBrowser")
            # os.system("root -l")

if run_sum is True:
    SumHistograms(chain_names, sum_name, single_sim=False)

if run_restart is True:
    print("\nAnalysis aborted...Restarting...\n")
    os.system("python FileSearcher.py")

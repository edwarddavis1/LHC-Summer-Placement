# Lifted from FileSearcher.property
import os
from subprocess import PIPE, Popen

# Gets the name of the host (the computer you are ssh'ing to)
proc = Popen(['hostname'], stdout=PIPE)
host_full = proc.communicate()[0].split()[0]
host = host_full.split(".")[0]
print("Getting data from computer: %s..." % host)

if host == "higgs":
    MC_path = "/higgs-data3/sam/forTomRyunAliceLuca/v03/mc"
    # amount of '.' before chain name
    chain_start = 6
elif host == "pc2014":
    MC_path = "/pc2014-data4/sam/VBF_Ztt/HIGG8D1/v5.0/mc"
    chain_start = 7
elif host == "pc2012":
    MC_path = "/pc2012-data1/sam/VBF_Ztt/HIGG8D1/v5.0/mc"
    chain_start = 7

found_dir = None
file_paths = []
chain_names = []
higgs_lums = []
file_sizes = []
files_analysed = []
file_times = []
files_last_run = []
second_substring = []
file_time_total_s = 0

while found_dir is None:
    user_input = ""
    user_input = user_input.replace(" ", "")
    chains = user_input.split(",")

    # Prevent bug where by typing "Ztt" all the files get chosen
    # (/mc directory contains the sub-string "Ztt")
    for i in range(len(chains)):
        if chains[i] == "Ztt":
            chains[i] = "Ztt_"

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
                if chains[i] in dirname and dirname != MC_path:
                    found_dir = True
                    for filenames in os.walk(dirname):

                        filename = filenames[2][0]
                        file_path = dirname + "/" + filename

                        chain_name = "_".join(file_path.split(
                            ".")[chain_start].split("_")[2:])

                        # Fixes bug where some chains were missed
                        if chain_name == "":
                            chain_name = "_".join(file_path.split(
                                ".")[chain_start].split("_")[1:])

                        if host == 'higgs':
                            higgs_lum_line = file_path.split(".")[8]
                            higgs_lum = higgs_lum_line.split("_")[2]
                            chain_name = "_".join([chain_name, higgs_lum])

                        file_size = os.path.getsize(file_path) / 1e9
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
                        file_paths.append(file_path)
                        chain_names.append(chain_name)
                        file_sizes.append(file_size)
                        files_analysed.append(file_exist)
                        file_times.append(file_time)


# Write a .C file that writes all the N value to a text file based on header
# files created by Alice and Luca (Get_N.h)
# -------------------------------- PC2014 ----------------------------------- #
if host == 'pc2014':
    func_names = []
    with open("Headers/Get_N_pc2014.h", "r") as fread:
        lines = fread.readlines()
        for line in lines:
            if line[0] == 'L':
                func_names.append(line.split(' ')[1])
    fread.close()

    # Erase contents of the text file
    f_txt = open('N_values.txt', 'r+')
    f_txt.truncate(0)

    i = 0
    with open("Write_All_N.C", "w") as f:
        print("Writing...")
        for line in lines:
            if line[0] == 'L':
                f.write('void %s {' % func_names[i])
            elif line[1] == 'r':
                f.write('    ofstream N_file;\n'
                        + '    N_file.open'
                        + '("N_values_pc2014.txt",ios_base::app);\n'
                        + '    N_file << "%s"' % chain_names[i]
                        + ' << ":" << N << endl;\n'
                        + '    N_file.close();\n')
                i += 1
            elif line[0] == '/' or line[0] == '#':
                f.write('')
            else:
                f.write(line)

        f.write("void Write_All_N() {\n")
        for i in range(len(func_names)):
            f.write('    ' + func_names[i] + ';\n')
        f.write('}\n')
    f.close()

# -------------------------------- PC2012 ----------------------------------- #
elif host == 'pc2012':
    func_names = []
    with open("Headers/Get_N_pc2012.h", "r") as fread:
        lines = fread.readlines()
        for line in lines:
            if line[0] == 'L':
                func_names.append(line.split(' ')[1])
    fread.close()

    # Erase contents of the text file
    f_txt = open('N_values.txt', 'r+')
    f_txt.truncate(0)

    i = 0
    with open("Write_All_N.C", "w") as f:
        print("Writing...")
        for line in lines:
            if line[0] == 'L':
                f.write('void %s {' % func_names[i])
            elif line[1] == 'r':
                f.write('    ofstream N_file;\n'
                        + '    N_file.open'
                        + '("N_values_pc2012.txt",ios_base::app);\n'
                        + '    N_file << "%s"' % chain_names[i]
                        + ' << ":" << N << endl;\n'
                        + '    N_file.close();\n')
                i += 1
            elif line[0] == '/' or line[0] == '#':
                f.write('')
            else:
                f.write(line)

        f.write("void Write_All_N() {\n")
        for i in range(len(func_names)):
            f.write('    ' + func_names[i] + ';\n')
        f.write('}\n')
    f.close()

# -------------------------------- HIGGS ------------------------------------ #
elif host == 'higgs':
    func_names = []
    with open("Headers/Get_N_higgs.h", "r") as fread:
        lines = fread.readlines()
        for line in lines:
            if line[0] == 'L':
                func_names.append(line.split(' ')[1])
    fread.close()

    # Erase contents of the text file
    f_txt = open('N_values_higgs.txt', 'r+')
    f_txt.truncate(0)

    i = 0
    with open("Write_All_N.C", "w") as f:
        print("Writing...")
        for line in lines:
            if line[0] == 'L':
                f.write('void %s {' % func_names[i])
            elif line[1] == 'r':
                f.write('    ofstream N_file;\n'
                        + '    N_file.open'
                        + '("N_values_higgs.txt",ios_base::app);\n'
                        + '    N_file << "%s"' % chain_names[i]
                        + ' << ":" << N << endl;\n'
                        + '    N_file.close();\n')
                i += 1
            elif line[0] == '/' or line[0] == '#':
                f.write('')
            else:
                f.write(line)

        f.write("void Write_All_N() {\n")
        for i in range(len(func_names)):
            f.write('    ' + func_names[i] + ';\n')
        f.write('}\n')
    f.close()

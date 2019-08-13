def RemoveFromString(string, substring, delimeter):
    if ',' in string:
        strings = string.split(',')
    else:
        strings = [string]

    new_strings = []
    for str in strings:
        str = str.strip()
        if substring in str:
            split_str = str.split(delimeter)
            counts = str.count(substring)
            for i in range(counts):
                split_str.remove(substring)
                new_strings.append(delimeter.join(split_str))

        else:
            new_strings.append(str)

    new_string = ', '.join(new_strings)

    return new_string


def UpdateWrite():
    """Writes all the histograms that are booked
    Colours all the histograms
    """
    Hist_book = []
    hist_names = []

    # Read in all the histogram names, checking that they aren't commented
    BookFile = open("Headers/BookHistos.h", "r")
    Hist_book.append(BookFile.read().split("\n"))
    void = False
    for i in range(len(Hist_book[0])):
        line = Hist_book[0][i]
        if '/*' in line:
            void = True
        if '*/' in line:
            void = False
        if 'h_' in line and '//' not in line and void is False:
            hist_names.append(Hist_book[0][i].split(" ")[1])
    BookFile.close()

    # Write them into WriteHistos.h
    with open("Headers/WriteHistos.h", "w") as WriteFile:
        for i in range(len(hist_names)):
            WriteFile.write('%s->Write();\n' % hist_names[i])
    WriteFile.close()

    # Colour the histograms
    with open("Headers/ColourHistos.h", "w") as ColourFile:
        for i in range(len(hist_names)):
            ColourFile.write('%s->SetFillColor(colour);\n' % hist_names[i])
            ColourFile.write('%s->SetLineColor(kBlack);\n' % hist_names[i])
            ColourFile.write('%s->SetFillStyle(1001);\n' % hist_names[i])
    ColourFile.close()

    # Fill all the histograms
    info = []
    with open("Headers/PreSelectionHistos.h", "w") as preselect, \
            open("Headers/BaselineHistos.h", "w") as baseline, \
            open("Headers/SearchHistos.h", "w") as search, \
            open("Headers/ControlHistos.h", "w") as control, \
            open("Headers/HighMassHistos.h", "w") as highmass:
        files = [preselect, baseline, search, control, highmass]

        # sort arrays into lep, elec, muon, tau, ljet, bjet, Z
        for i in range(len(hist_names)):
            particle = hist_names[i].split('_')[1]
            variable = '_'.join(hist_names[i].split('_')[1:-1])
            region = hist_names[i].split('_')[-1]

            if particle == 'lep':
                info.append([particle, variable, region, 1])
            elif particle == 'elec':
                info.append([particle, variable, region, 2])
            elif particle == 'muon':
                info.append([particle, variable, region, 3])
            elif particle == 'tau':
                info.append([particle, variable, region, 4])
            elif particle == 'ljet':
                info.append([particle, variable, region, 5])
            elif particle == 'bjet':
                info.append([particle, variable, region, 6])
            elif particle == 'Z':
                info.append([particle, variable, region, 7])
            else:
                info.append([particle, variable, region, 8])

        info.sort(key=lambda x: x[3])
        particles = [row[0] for row in info]
        variables = [row[1] for row in info]
        regions = [row[2] for row in info]

        filled = 0      # Keeps track of particles that have been filled

        # ------------------------- FILL LEPTONS ---------------------------- #

        for file in files:
            file.write('// general leptons\n')
        for i in range(particles.count('lep')):

            if 'L_SL' in variables[i]:
                split_variable = variables[i].split('_')
                split_variable.remove('L')
                split_variable.remove('SL')
                split_variable.remove(particles[i])
                new_variable = '_'.join(split_variable)
                fill1 = (particles[i] + "_0_" + new_variable).strip('_')
                fill2 = (particles[i] + "_1_" + new_variable).strip('_')
                fill = (fill1 + ', ' + fill2)
            else:
                fill = variables[i]

            if regions[i] == 'preselect':
                preselect.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                            regions[i],
                                                            fill))
            if regions[i] == 'baseline':
                baseline.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                           regions[i],
                                                           fill))
            if regions[i] == 'search':
                search.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                         regions[i],
                                                         fill))
            if regions[i] == 'control':
                control.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                          regions[i],
                                                          fill))
            if regions[i] == 'highmass':
                highmass.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                           regions[i],
                                                           fill))
        filled = i + 1
        # ----------------------- FILL ELECTRONS ---------------------------- #
        for file in files:
            file.write('\n// electrons\n')
            file.write('if (lep_type == "Electron") {\n')
        for i in range(filled, filled + particles.count('elec')):

            if 'L_SL' in variables[i]:
                split_variable = variables[i].split('_')
                split_variable.remove('L')
                split_variable.remove('SL')
                split_variable.remove(particles[i])
                new_variable = '_'.join(split_variable)
                fill1 = (particles[i] + "_0_" + new_variable).strip('_')
                fill2 = (particles[i] + "_1_" + new_variable).strip('_')
                fill = (fill1 + ', ' + fill2)
            else:
                fill = variables[i]

            if 'cone' not in fill:
                fill = fill.replace('elec', 'lep')

            if regions[i] == 'preselect':
                preselect.write('    h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                                regions[i],
                                                                fill))
            if regions[i] == 'baseline':
                baseline.write('    h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                               regions[i],
                                                               fill))
            if regions[i] == 'search':
                search.write('    h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                             regions[i],
                                                             fill))
            if regions[i] == 'control':
                control.write('    h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                              regions[i],
                                                              fill))
            if regions[i] == 'highmass':
                highmass.write('    h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                               regions[i],
                                                               fill))
        for file in files:
            file.write('}\n')

        filled = i + 1

        # ------------------------- FILL MUONS ------------------------------ #
        for file in files:
            file.write('\n// muons\n')
            file.write('if (lep_type == "Muon") {\n')
        for i in range(filled, filled + particles.count('muon')):

            if 'L_SL' in variables[i]:
                split_variable = variables[i].split('_')
                split_variable.remove('L')
                split_variable.remove('SL')
                split_variable.remove(particles[i])
                new_variable = '_'.join(split_variable)
                fill1 = (particles[i] + "_0_" + new_variable).strip('_')
                fill2 = (particles[i] + "_1_" + new_variable).strip('_')
                fill = (fill1 + ', ' + fill2)
            else:
                fill = variables[i]

            if 'cone' not in fill:
                fill = fill.replace('muon', 'lep')

            if regions[i] == 'preselect':
                preselect.write('    h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                                regions[i],
                                                                fill))
            if regions[i] == 'baseline':
                baseline.write('    h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                               regions[i],
                                                               fill))
            if regions[i] == 'search':
                search.write('    h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                             regions[i],
                                                             fill))
            if regions[i] == 'control':
                control.write('    h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                              regions[i],
                                                              fill))
            if regions[i] == 'highmass':
                highmass.write('    h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                               regions[i],
                                                               fill))
        for file in files:
            file.write('}\n')

        filled = i
        # -------------------------- FILL TAUS ------------------------------ #
        for file in files:
            file.write('\n// taus\n')
            file.write('if (lep_type == "ElectronTau" or lep_type == "MuonTau"\n'
                       + '    or lep_type == "ElectronMuon") {\n')
        for i in range(filled + 1, filled + particles.count('tau')):

            if 'L_SL' in variables[i]:
                split_variable = variables[i].split('_')
                split_variable.remove('L')
                split_variable.remove('SL')
                split_variable.remove(particles[i])
                new_variable = '_'.join(split_variable)
                fill1 = (particles[i] + "_0_" + new_variable).strip('_')
                fill2 = (particles[i] + "_1_" + new_variable).strip('_')
                fill = (fill1 + ', ' + fill2)
            else:
                fill = variables[i]

            fill = fill.replace('tau', 'lep')

            if regions[i] == 'preselect':
                preselect.write('    h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                                regions[i],
                                                                fill))
            if regions[i] == 'baseline':
                baseline.write('    h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                               regions[i],
                                                               fill))
            if regions[i] == 'search':
                search.write('    h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                             regions[i],
                                                             fill))
            if regions[i] == 'control':
                control.write('    h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                              regions[i],
                                                              fill))
            if regions[i] == 'highmass':
                highmass.write('    h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                               regions[i],
                                                               fill))
        for file in files:
            file.write('}\n')

        filled = i + 1

        # -------------------------- FILL LJETS ----------------------------- #
        # Requires condition for amount of jets for some histos
        for file in files:
            file.write('\n// ljets\n')
        for i in range(filled + 1, filled + particles.count('ljet')):

            if 'L_SL' in variables[i]:
                split_variable = variables[i].split('_')
                split_variable.remove('L')
                split_variable.remove('SL')
                split_variable.remove(particles[i])
                new_variable = '_'.join(split_variable)
                fill1 = (particles[i] + "_0_" + new_variable).strip('_')
                fill2 = (particles[i] + "_1_" + new_variable).strip('_')
                fill = (fill1 + ', ' + fill2)
            else:
                fill = variables[i]

            if '2jets' in variables[i]:
                condition = 'n_jets == 2'
                fill = RemoveFromString(fill, '2jets', '_')
            elif '3jets' in variables[i]:
                condition = 'n_jets == 3'
                fill = RemoveFromString(fill, '3jets', '_')
            elif '4jets' in variables[i]:
                condition = 'n_jets == 4'
                fill = RemoveFromString(fill, '4jets', '_')
            elif '5jets' in variables[i]:
                condition = 'n_jets == 5'
                fill = RemoveFromString(fill, '5jets', '_')
            elif 'ljet_3' in variables[i]:
                condition = 'ljet_3'
            elif 'ljet_2' in variables[i]:
                condition = 'ljet_2'
            else:
                condition = None

            if regions[i] == 'preselect':
                if condition is not None:
                    preselect.write('if (%s) ' % condition)
                preselect.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                            regions[i],
                                                            fill))
            if regions[i] == 'baseline':
                if condition is not None:
                    baseline.write('if (%s) ' % condition)
                baseline.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                           regions[i],
                                                           fill))
            if regions[i] == 'search':
                if condition is not None:
                    search.write('if (%s) ' % condition)
                search.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                         regions[i],
                                                         fill))
            if regions[i] == 'control':
                if condition is not None:
                    control.write('if (%s) ' % condition)
                control.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                          regions[i],
                                                          fill))
            if regions[i] == 'highmass':
                if condition is not None:
                    highmass.write('if (%s) ' % condition)
                highmass.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                           regions[i],
                                                           fill))

        filled = i + 1

        # -------------------------- FILL BJETS ----------------------------- #
        for file in files:
            file.write('\n// bjets\n')
        for i in range(filled + 1, filled + particles.count('bjet')):
            if regions[i] == 'preselect':
                preselect.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                            regions[i],
                                                            variables[i]))
            if regions[i] == 'baseline':
                baseline.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                           regions[i],
                                                           variables[i]))
            if regions[i] == 'search':
                search.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                         regions[i],
                                                         variables[i]))
            if regions[i] == 'control':
                control.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                          regions[i],
                                                          variables[i]))
            if regions[i] == 'highmass':
                highmass.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                           regions[i],
                                                           variables[i]))

        filled = i + 1

        # ---------------------------- FILL Z ------------------------------- #
        for file in files:
            file.write('\n// Z\n')
        for i in range(filled + 1, filled + particles.count('Z')):
            if regions[i] == 'preselect':
                preselect.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                            regions[i],
                                                            variables[i]))
            if regions[i] == 'baseline':
                baseline.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                           regions[i],
                                                           variables[i]))
            if regions[i] == 'search':
                search.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                         regions[i],
                                                         variables[i]))
            if regions[i] == 'control':
                control.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                          regions[i],
                                                          variables[i]))
            if regions[i] == 'highmass':
                highmass.write('h_%s_%s -> Fill(%s);\n' % (variables[i],
                                                           regions[i],
                                                           variables[i]))

        filled = i + 1


UpdateWrite()

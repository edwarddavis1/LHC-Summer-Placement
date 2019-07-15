def UpdateWrite():
	"""
	Writes all the histograms that are booked
	"""
	Hist_book = []
	Hist_names = []
	
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
		if 'h_' in line and '//' not in line and void == False:
			Hist_names.append(Hist_book[0][i].split(" ")[1])
	BookFile.close()
			
	# Write them into WriteHistos.h
	with open("Headers/WriteHistos.h", "w") as WriteFile:
		for i in range(len(Hist_names)):
			WriteFile.write('%s->Write();\n'%Hist_names[i])
	WriteFile.close()

def AutoHistoBook(quantity_name, quantity_title, bins, h_min, h_max, *args, **kwargs): 
	"""
	Automatically adds histogram bookings to the end of the "Headers/BookHistos.h" file
	"""
	
	# List of all particles that you want to be generated for each histogram 
	particles = ['Electron', 'Muon', 'Tau']
	
	# Can override the default option of booking for the three ll pair events
	# Can write 'full' to get all six ll events or write out a specific array of your choosing
	particles = kwargs.get('particles', particles)
	if particles == 'full':
		particles = ['Electron', 'Muon', 'Tau', 'ElectronMuon', 'ElectronTau', 'MuonTau']
	elif particles == 'lep':
		particles = ['Leptons']
	
	particles_name = particles
	particles_name = [lep.replace('Electron', 'elec_') for lep in particles_name]
	particles_name = [lep.replace('Muon', 'muon_') for lep in particles_name]
	particles_name = [lep.replace('Tau', 'tau_') for lep in particles_name]
	particles_name = [lep.replace('Leptons', 'lep_') for lep in particles_name]
	
	# In case not running an MC simulation
	sim = 'MC'
	sim = kwargs.get('sim', sim)	
	
	# Modify booking header
	with open("Headers/BookHistos.h", "a") as BookFile:
		for i in range(len(particles)):
			Histo_name = particles_name[i]+quantity_name
		
			Histo_book = 'TH1F* h_%s = new TH1F("%s", TString::Format("%s from %s in %s %%s",choice.c_str()), %i, %i, %i);\n'%(Histo_name,Histo_name,quantity_title, 
																particles[i], sim, bins, h_min, h_max)
			BookFile.write(Histo_book)
	BookFile.close()
#AutoHistoBook("pt", "Transverse Momenta", 500, 0, 1000, particles=['Electron'])
#AutoHistoBook("eta", "Pseudorapidity", 500, -5, 5, particles=['Electron'])
#AutoHistoBook("phi", "Phi", 500, -4, 4, particles=['Electron'])
UpdateWrite()	

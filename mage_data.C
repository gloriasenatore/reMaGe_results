#include <fstream>
#include <iostream>
#include <cmath>

{
	std::set<std::string> excluded_det = {"ch1108804", "ch1110405", "ch1115200", "ch1115201", "ch1115202", "ch1080002", "ch1080003", "ch1083200", "ch1088000", "ch1088004", "ch1089602", "ch1089604"};

	filename = "/global/cfs/projectdirs/m2676/users/tdixon/legend-prodenv/calibration_simulations/generated/tier/pdf/l200-cal-source-sis-2-source-3-8300-mm-offset-0-mm-Ra224-to-Pb208/l200-cal-source-sis-2-source-3-8300-mm-offset-0-mm-Ra224-to-Pb208-tier_pdf.root";
	ofstream file_out("MaGe_data/l200-cal-source-sis-2-source-3-8300-mm-offset-0-mm-Ra224-to-Pb208.txt");
	int n = 0;
	TFile *f = TFile::Open(filename);
	TDirectory* dir = f->GetDirectory("hit");
	int bin_num_general = 0;
        double bin_width_general = 0.;
	std::vector<double> vec_energies(6000, 0.);

	for (auto&& keyAsObj : *dir->GetListOfKeys()) {
	auto key = (TKey*) keyAsObj;
	string det_name = key->GetName();

	if(det_name.at(0)=='c' and det_name.at(1)=='h' and excluded_det.find(det_name) == excluded_det.end()){
	     	++n;	
		cout << "Processing detector n. " << n << " " << det_name << endl;
			
		TH1F* energies = (TH1F*)dir->Get(key->GetName());
		int bin_num = energies->GetNbinsX();
		//cout << energies->GetBinLowEdge(1) << endl;

		for (int i = 0; i < bin_num; ++i){
			vec_energies[i] += energies->GetBinContent(i+1);
		}	
		if(det_name=="ch1113601") bin_width_general = energies->GetBinWidth(1);
		bin_num_general = bin_num;
		}	
	}
		
	for (int i = 0; i < bin_num_general; ++i){
		file_out << vec_energies[i] << endl;
	}
	
	file_out.close();
	cout << "Number of bins = " << bin_num_general << ". Bin width = " << bin_width_general << endl;

}

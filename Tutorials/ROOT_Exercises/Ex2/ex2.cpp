void ex2() {
	TFile *infile("TTree_example.root","READ");
	TFile *outfile("ex2.root","RECREATE");

	TTree *tree = (TTree*) infile->Get("myTree");
	// tree->Print();
	cout << "Nº of tree entries: " << tree->GetEntries() << endl;

	// Canvas
    TCanvas* c1 = new TCanvas("c1", "TTree_example", 0, 0, 700, 500);
    c1->SetFillColor(kWhite);
    c1->SetGrid();
    c1->GetFrame()->SetFillColor(21);
    c1->GetFrame()->SetBorderSize(12);

    // Pad
    TPad* p1 = new TPad("p1", "Pad1", 0, 0, 1, 1, kWhite);
	p1->SetLogy();
    p1->Draw();
    p1->cd();

	// TH1Fs	
	tree->Draw("mu_pt>>hist_mu_pt","","goff");
	TH1F *hist_mu_pt = (TH1F*) gDirectory->Get("hist_mu_pt");
	hist_mu_pt->SetLineColor(kRed);
	hist_mu_pt->SetLineWidth(2);

	tree->Draw("el_pt>>hist_el_pt","","goff");
	TH1F *hist_el_pt = (TH1F*) gDirectory->Get("hist_el_pt");
	hist_el_pt->SetLineColor(kBlue);
	hist_el_pt->SetLineWidth(2);

	tree->Draw("met_phi>>hist_met_phi","","goff");
	TH1F *hist_met_phi = (TH1F*) gDirectory->Get("hist_met_phi");
	cout << "Nº of met_phi entries: " << hist_met_phi->GetEntries() << endl << endl;

	tree->Draw("mTV>>hist_mTV","","goff");
	TH1F *hist_mTV = (TH1F*) gDirectory->Get("hist_mTV");
	
	// Draw
	hist_mu_pt->Draw();
	hist_el_pt->Draw("same");
	// hist_met_phi->Draw();
	// hist_mTV->Draw();
    
    c1->Modified();
    c1->Update();
    while(c1->WaitPrimitive()) gSystem->ProcessEvents();
    c1->Print("mu_pt_el_pt.png");

    outfile->Write();
    outfile->ls();
    infile->Close();
    outfile->Close();

    delete p1;
    delete c1;
}
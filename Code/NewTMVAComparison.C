#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "TROOT.h"
#include "TSystem.h"
#include "TFile.h"
#include "TString.h"
#include "TMath.h"
#include "TStopwatch.h"

#include "TStyle.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TLine.h"
#include "TGraph.h"
#include "TH1F.h"

using namespace std;


void NewTMVAComparison() {

	cout << "===> Start NewTMVAComparison\n" << endl;

//----SET INPUT--------------------------------------------------

	// Open files

	// training: pp,   application: pp
	TFile *input_bdt_atlas        = new TFile( "rootfiles/pp_pp/bdt_atlas/TMVAanalysis.root",        "READ" );
	TFile *input_bdt_atlas_jfllr  = new TFile( "rootfiles/pp_pp/bdt_atlas+jfllr/TMVAanalysis.root",  "READ" );
	TFile *input_bdt_all          = new TFile( "rootfiles/pp_pp/bdt_all/TMVAanalysis.root",          "READ" );
	TFile *input_bdt_25separation = new TFile( "rootfiles/pp_pp/bdt_25separation/TMVAanalysis.root", "READ" );
	TFile *input_bdt_25important  = new TFile( "rootfiles/pp_pp/bdt_25important/TMVAanalysis.root",  "READ" );
	TFile *input_bdt_tbrowser     = new TFile( "rootfiles/pp_pp/bdt_tbrowser/TMVAanalysis.root",     "READ" );

	// training: pp,   application: PbPb
	TFile *input_bdt_atlas_jfllr_p_pb_jz2_w1 = new TFile(
		"rootfiles/pp_pbpb/bdt_atlas+jfllr_jz2_w1/TMVAanalysis.root",   "READ" );
	TFile *input_bdt_atlas_jfllr_p_pb_jz2 = new TFile(
		"rootfiles/pp_pbpb/bdt_atlas+jfllr_jz2/TMVAanalysis.root",      "READ" );

	// training: PbPb, application: PbPb
	TFile *input_bdt_atlas_jfllr_pb_pb_jz2_w1 = new TFile(
		"rootfiles/pbpb_pbpb/bdt_atlas+jfllr_jz2_w1/TMVAanalysis.root", "READ" );
	TFile *input_bdt_atlas_jfllr_pb_pb_jz2 = new TFile(
		"rootfiles/pbpb_pbpb/bdt_atlas+jfllr_jz2/TMVAanalysis.root",    "READ" );
	TFile *input_bdt_atlas_jfllr_pb_pb_all = new TFile(
		"rootfiles/pbpb_pbpb/bdt_atlas+jfllr_all/TMVAanalysis.root",    "READ" );

	TFile *outputFile = new TFile( "rootfiles/TMVAcomparison.root", "RECREATE" );

	// Start stopwatch
	TStopwatch sw;
	sw.Start();

	// Remove stats box
	gStyle->SetOptStat(0);

	// Canvas
	TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 1005, 670);
	c1->SetFillColor(kWhite);
	c1->SetGrid();
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	c1->cd();

	// Legend
    TLegend *leg = new TLegend(0.54,0.61,0.9,0.89); // (x1,y1,x2,y2)
    leg->SetFillColor(0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.03);

	TH1::SetDefaultSumw2(); // store sum of squares of weights

//----EFFICIENCY COMPARISON--------------------------------------

	// IP2D, IP3D, JF
	TGraph *IP2D_pp_eff       = (TGraph*) input_bdt_atlas_jfllr->Get( "IP2D_Efficiency" );
	TGraph *IP3D_pp_eff       = (TGraph*) input_bdt_atlas_jfllr->Get( "IP3D_Efficiency" );
	TGraph *JF_pp_eff         = (TGraph*) input_bdt_atlas_jfllr->Get( "JF_Efficiency"   );
	TGraph *IP2D_pbpb_jz2_eff = (TGraph*) input_bdt_atlas_jfllr_pb_pb_jz2->Get( "IP2D_Efficiency" );
	TGraph *IP3D_pbpb_jz2_eff = (TGraph*) input_bdt_atlas_jfllr_pb_pb_jz2->Get( "IP3D_Efficiency" );
	TGraph *JF_pbpb_jz2_eff   = (TGraph*) input_bdt_atlas_jfllr_pb_pb_jz2->Get( "JF_Efficiency"   );
	TGraph *IP2D_pbpb_all_eff = (TGraph*) input_bdt_atlas_jfllr_pb_pb_all->Get( "IP2D_Efficiency" );
	TGraph *IP3D_pbpb_all_eff = (TGraph*) input_bdt_atlas_jfllr_pb_pb_all->Get( "IP3D_Efficiency" );
	TGraph *JF_pbpb_all_eff   = (TGraph*) input_bdt_atlas_jfllr_pb_pb_all->Get( "JF_Efficiency"   );

	// training: pp,   application: pp
	TGraph *BDT_atlas_eff        = (TGraph*) input_bdt_atlas       ->Get( "BDT_Efficiency" );
	TGraph *BDT_atlas_jfllr_eff  = (TGraph*) input_bdt_atlas_jfllr ->Get( "BDT_Efficiency" );
	TGraph *BDT_all_eff          = (TGraph*) input_bdt_all         ->Get( "BDT_Efficiency" );
	TGraph *BDT_25separation_eff = (TGraph*) input_bdt_25separation->Get( "BDT_Efficiency" );
	TGraph *BDT_25important_eff  = (TGraph*) input_bdt_25important ->Get( "BDT_Efficiency" );
	TGraph *BDT_tbrowser_eff     = (TGraph*) input_bdt_tbrowser    ->Get( "BDT_Efficiency" );

	// training: pp,   application: PbPb
	TGraph *BDT_atlas_jfllr_p_pb_jz2_w1_eff = (TGraph*) input_bdt_atlas_jfllr_p_pb_jz2_w1->Get("BDT_Efficiency");
	TGraph *BDT_atlas_jfllr_p_pb_jz2_eff    = (TGraph*) input_bdt_atlas_jfllr_p_pb_jz2   ->Get("BDT_Efficiency");

	// training: PbPb, application: PbPb
	TGraph *BDT_atlas_jfllr_pb_pb_jz2_w1_eff = (TGraph*) input_bdt_atlas_jfllr_pb_pb_jz2_w1->Get("BDT_Efficiency");
	TGraph *BDT_atlas_jfllr_pb_pb_jz2_eff    = (TGraph*) input_bdt_atlas_jfllr_pb_pb_jz2   ->Get("BDT_Efficiency");
	TGraph *BDT_atlas_jfllr_pb_pb_all_eff    = (TGraph*) input_bdt_atlas_jfllr_pb_pb_all   ->Get("BDT_Efficiency");

	// Good: kBlack, kRed, kBlue, kGreen, kCyan, kMagenta, kOrange, kGray
	// Too similar: kWhite, kYellow, kSpring, kTeal, kAzure, kViolet, kPink

// training: pp, application: pp


	// Title, Style
	BDT_atlas_jfllr_eff ->SetTitle("p+p => p+p BDT Efficiency");
	BDT_atlas_jfllr_eff ->GetXaxis()->SetRangeUser(0.15,1.);
	BDT_atlas_jfllr_eff ->SetLineColor(kBlack);
	BDT_atlas_eff 		->SetLineColor(kRed);
	BDT_all_eff         ->SetLineColor(kBlue);
	BDT_25separation_eff->SetLineColor(kGreen);
	BDT_25important_eff ->SetLineColor(kGreen+2);
	BDT_tbrowser_eff    ->SetLineColor(kGray+1);
	IP2D_pp_eff         ->SetLineColor(kCyan+1);
	IP3D_pp_eff         ->SetLineColor(kMagenta);
	JF_pp_eff           ->SetLineColor(kOrange);

	// Draw
	BDT_atlas_jfllr_eff ->Draw("AL");
	BDT_atlas_eff       ->Draw("same");
	BDT_all_eff         ->Draw("same");
	BDT_25separation_eff->Draw("same");
	BDT_25important_eff ->Draw("same");
	BDT_tbrowser_eff    ->Draw("same");
	IP2D_pp_eff         ->Draw("same");
	IP3D_pp_eff         ->Draw("same");
	JF_pp_eff           ->Draw("same");

	leg->Clear();
	leg->SetHeader("Inputs:");
	leg->AddEntry(BDT_atlas_eff,        "ATLAS ",                             "l");
	leg->AddEntry(BDT_atlas_jfllr_eff,  "ATLAS + JF llr",                     "l");
	leg->AddEntry(BDT_all_eff,          "All",                                "l");
	leg->AddEntry(BDT_25separation_eff, "25 w/ most TMVA separation",         "l");
	leg->AddEntry(BDT_25important_eff,  "25 w/ most BDT importance",          "l");
	leg->AddEntry(BDT_tbrowser_eff,     "Visually different between sig/bkg", "l");
	leg->AddEntry((TObject*) 0, "-------", ""); // new line
	leg->AddEntry(IP2D_pp_eff,          "IP2D",                               "l");
	leg->AddEntry(IP3D_pp_eff,          "IP3D",                               "l");
	leg->AddEntry(JF_pp_eff,            "JetFitter",                          "l");
	leg->Draw();

	c1->SetLogy(1);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/bdt_effcomp_pp_pp.png");

// training: pp,   application: PbPb (JZ2)

	// // Title, Style
	// BDT_atlas_jfllr_p_pb_jz2_w1_eff->SetTitle("p+p => Pb+Pb (JZ2) BDT Efficiency");
	// BDT_atlas_jfllr_p_pb_jz2_w1_eff->GetXaxis()->SetRangeUser(0.15,1.);
	// BDT_atlas_jfllr_p_pb_jz2_w1_eff->SetLineColor(kRed);
	// BDT_atlas_jfllr_p_pb_jz2_eff   ->SetLineColor(kBlue);
	// IP2D_pbpb_jz2_eff              ->SetLineColor(kCyan);
	// IP3D_pbpb_jz2_eff              ->SetLineColor(kGreen);
	// JF_pbpb_jz2_eff                ->SetLineColor(kOrange);

	// // Draw
	// BDT_atlas_jfllr_p_pb_jz2_w1_eff->Draw("AL");
	// BDT_atlas_jfllr_p_pb_jz2_eff   ->Draw("same");
	// IP2D_pbpb_jz2_eff              ->Draw("same");
	// IP3D_pbpb_jz2_eff              ->Draw("same");
	// JF_pbpb_jz2_eff                ->Draw("same");

	// leg->Clear();
	// leg->SetTextSize(0.04);
	// leg->SetX1NDC(0.6);
	// leg->SetY1NDC(0.69);
	// leg->AddEntry(BDT_atlas_jfllr_p_pb_jz2_w1_eff, "ATLAS + JF llr (w=1)", "l");
	// leg->AddEntry(BDT_atlas_jfllr_p_pb_jz2_eff,    "ATLAS + JF llr",       "l");
	// leg->AddEntry(IP2D_pbpb_jz2_eff,               "IP2D",                 "l");
	// leg->AddEntry(IP3D_pbpb_jz2_eff,               "IP3D",                 "l");
	// leg->AddEntry(JF_pbpb_jz2_eff,                 "JetFitter",            "l");
	// leg->Draw();

	// c1->SetLogy(1);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/bdt_effcomp_pp_pbpb_jz2.png");

// training: PbPb, application: PbPb (JZ2)

	// // Title, Style
	// BDT_atlas_jfllr_pb_pb_jz2_w1_eff->SetTitle("Pb+Pb => Pb+Pb (JZ2) BDT Efficiency");
	// BDT_atlas_jfllr_pb_pb_jz2_w1_eff->GetXaxis()->SetRangeUser(0.15,1.);
	// BDT_atlas_jfllr_pb_pb_jz2_w1_eff->SetLineColor(kRed);
	// BDT_atlas_jfllr_pb_pb_jz2_eff   ->SetLineColor(kBlue);
	// IP2D_pbpb_jz2_eff               ->SetLineColor(kCyan);
	// IP3D_pbpb_jz2_eff               ->SetLineColor(kGreen);
	// JF_pbpb_jz2_eff                 ->SetLineColor(kOrange);

	// // Draw
	// BDT_atlas_jfllr_pb_pb_jz2_w1_eff->Draw("AL");
	// BDT_atlas_jfllr_pb_pb_jz2_eff   ->Draw("same");
	// IP2D_pbpb_jz2_eff               ->Draw("same");
	// IP3D_pbpb_jz2_eff               ->Draw("same");
	// JF_pbpb_jz2_eff                 ->Draw("same");

	// leg->Clear();
	// leg->AddEntry(BDT_atlas_jfllr_p_pb_jz2_w1_eff, "ATLAS + JF llr (w=1)", "l");
	// leg->AddEntry(BDT_atlas_jfllr_p_pb_jz2_eff,    "ATLAS + JF llr",       "l");
	// leg->AddEntry(IP2D_pbpb_jz2_eff,               "IP2D",                 "l");
	// leg->AddEntry(IP3D_pbpb_jz2_eff,               "IP3D",                 "l");
	// leg->AddEntry(JF_pbpb_jz2_eff,                 "JetFitter",            "l");
	// leg->Draw();

	// c1->SetLogy(1);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/bdt_effcomp_pbpb_pbpb_jz2.png");

// training: PbPb, application: PbPb

	// Title, Style
	BDT_atlas_jfllr_pb_pb_all_eff->SetTitle("Pb+Pb => Pb+Pb BDT Efficiency");
	BDT_atlas_jfllr_pb_pb_all_eff->GetXaxis()->SetRangeUser(0.15, 1.);
	BDT_atlas_jfllr_pb_pb_all_eff->SetLineColor(kRed);
	IP2D_pbpb_all_eff            ->SetLineColor(kBlue);
	IP3D_pbpb_all_eff            ->SetLineColor(kGreen);
	JF_pbpb_all_eff              ->SetLineColor(kOrange);

	// Draw
	BDT_atlas_jfllr_pb_pb_all_eff->Draw("AL");
	IP2D_pbpb_all_eff            ->Draw("same");
	IP3D_pbpb_all_eff            ->Draw("same");
	JF_pbpb_all_eff              ->Draw("same");

	leg->Clear();
	leg->SetTextSize(0.04);
	leg->SetX1NDC(0.68);
	leg->SetY1NDC(0.73);
	leg->AddEntry(BDT_atlas_jfllr_pb_pb_all_eff, "ATLAS + JF llr", "l");
	leg->AddEntry(IP2D_pbpb_all_eff,             "IP2D",           "l");
	leg->AddEntry(IP3D_pbpb_all_eff,             "IP3D",           "l");
	leg->AddEntry(JF_pbpb_all_eff,               "JetFitter",      "l");
	leg->Draw();

	c1->SetLogy(1);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/bdt_effcomp_pbpb_pbpb.png");

// IP2D pp vs IP2D PbPb

	// Title, Style
	IP2D_pp_eff      ->SetTitle("IP2D Efficiency");
	IP2D_pp_eff      ->GetXaxis()->SetRangeUser(0.15, 1.);
	IP2D_pp_eff      ->SetLineColor(kRed);
	// IP2D_pbpb_jz2_eff->SetLineColor(kGreen);
	IP2D_pbpb_all_eff->SetLineColor(kBlue);

	// Draw
	IP2D_pp_eff      ->Draw("AL");
	// IP2D_pbpb_jz2_eff->Draw("same");
	IP2D_pbpb_all_eff->Draw("same");

	leg->Clear();
	leg->SetTextSize(0.06);
	leg->SetX1NDC(0.74);
	leg->SetY1NDC(0.75);
	leg->AddEntry(IP2D_pp_eff,       "p+p",   "l");
	// leg->AddEntry(IP2D_pbpb_jz2_eff, "Pb+Pb (JZ2)", "l");
	leg->AddEntry(IP2D_pbpb_all_eff, "Pb+Pb", "l");
	leg->Draw();

	c1->SetLogy(1);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/ip2d_effcomp.png");

// IP3D pp vs IP3D PbPb

	// Title, Style
	IP3D_pp_eff      ->SetTitle("IP3D Efficiency");
	IP3D_pp_eff      ->GetXaxis()->SetRangeUser(0.15, 1.);
	IP3D_pp_eff      ->SetLineColor(kRed);
	// IP3D_pbpb_jz2_eff->SetLineColor(kGreen);
	IP3D_pbpb_all_eff->SetLineColor(kBlue);

	// Draw
	IP3D_pp_eff      ->Draw("AL");
	// IP3D_pbpb_jz2_eff->Draw("same");
	IP3D_pbpb_all_eff->Draw("same");

	leg->Draw();

	c1->SetLogy(1);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/ip3d_effcomp.png");

// JF pp vs JF PbPb

	// Title, Style
	JF_pp_eff      ->SetTitle("JetFitter Efficiency");
	JF_pp_eff      ->GetXaxis()->SetRangeUser(0.15, 1.);
	JF_pp_eff      ->SetLineColor(kRed);
	// JF_pbpb_jz2_eff->SetLineColor(kGreen);
	JF_pbpb_all_eff->SetLineColor(kBlue);

	// Draw
	JF_pp_eff      ->Draw("AL");
	// JF_pbpb_jz2_eff->Draw("same");
	JF_pbpb_all_eff->Draw("same");

	leg->Draw();

	c1->SetLogy(1);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/jf_effcomp.png");

// BDT: pp vs PbPb

	// Title, Style
	BDT_atlas_jfllr_eff             ->SetTitle("BDT Efficiency");
	BDT_atlas_jfllr_eff             ->GetXaxis()->SetRangeUser(0.15, 1.);
	BDT_atlas_jfllr_eff             ->SetLineColor(kRed);
	// BDT_atlas_jfllr_p_pb_jz2_w1_eff ->SetLineColor(kOrange);
	// BDT_atlas_jfllr_p_pb_jz2_eff    ->SetLineColor(kGreen);
	// BDT_atlas_jfllr_pb_pb_jz2_w1_eff->SetLineColor(kCyan);
	// BDT_atlas_jfllr_pb_pb_jz2_eff   ->SetLineColor(kBlack);
	BDT_atlas_jfllr_pb_pb_all_eff   ->SetLineColor(kBlue);

	// Draw
	BDT_atlas_jfllr_eff             ->Draw("AL");
	// BDT_atlas_jfllr_p_pb_jz2_w1_eff ->Draw("same");
	// BDT_atlas_jfllr_p_pb_jz2_eff    ->Draw("same");
	// BDT_atlas_jfllr_pb_pb_jz2_w1_eff->Draw("same");
	// BDT_atlas_jfllr_pb_pb_jz2_eff   ->Draw("same");
	BDT_atlas_jfllr_pb_pb_all_eff   ->Draw("same");

	leg->Clear();
	leg->SetTextSize(0.05);
	leg->SetX1NDC(0.58);
	leg->SetY1NDC(0.78);
	leg->AddEntry(BDT_atlas_jfllr_eff,              "p+p      => p+p",                "l");
	// leg->AddEntry(BDT_atlas_jfllr_p_pb_jz2_w1_eff,  "p+p      => Pb+Pb (JZ2, w=1)",   "l");
	// leg->AddEntry(BDT_atlas_jfllr_p_pb_jz2_eff,     "p+p      => Pb+Pb (JZ2)",        "l");
	// leg->AddEntry(BDT_atlas_jfllr_pb_pb_jz2_w1_eff, "Pb+Pb => Pb+Pb (JZ2, w=1)", "l");
	// leg->AddEntry(BDT_atlas_jfllr_pb_pb_jz2_eff,    "Pb+Pb => Pb+Pb (JZ2)",      "l");
	leg->AddEntry(BDT_atlas_jfllr_pb_pb_all_eff,    "Pb+Pb => Pb+Pb",            "l");
	leg->Draw();

	c1->SetLogy(1);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/bdt_effcomp_pp_pbpb.png");

	// Write to output file
	IP2D_pp_eff      ->Write();
	IP3D_pp_eff      ->Write();
	JF_pp_eff        ->Write();
	
	IP2D_pbpb_jz2_eff->Write();
	IP3D_pbpb_jz2_eff->Write();
	JF_pbpb_jz2_eff  ->Write();
	
	IP2D_pbpb_all_eff->Write();
	IP3D_pbpb_all_eff->Write();
	JF_pbpb_all_eff  ->Write();

	BDT_atlas_eff       ->Write();
	BDT_atlas_jfllr_eff ->Write();
	BDT_all_eff         ->Write();
	BDT_25separation_eff->Write();
	BDT_25important_eff ->Write();
	BDT_tbrowser_eff    ->Write();

	// BDT_atlas_jfllr_p_pb_jz2_w1_eff->Write();
	// BDT_atlas_jfllr_p_pb_jz2_eff   ->Write();

	// BDT_atlas_jfllr_pb_pb_jz2_w1_eff->Write();
	// BDT_atlas_jfllr_pb_pb_jz2_eff   ->Write();
	BDT_atlas_jfllr_pb_pb_all_eff   ->Write();

//----END--------------------------------------------------------

	// Get elapsed time
	sw.Stop();
	cout << "\n---- End of comparison: "; sw.Print();

	outputFile->Close();

	cout << "===> Wrote root file: " << outputFile->GetName() << endl;
	cout << "===> NewTMVAComparison is done!\n" << endl;	

	delete c1;
	delete outputFile;
}

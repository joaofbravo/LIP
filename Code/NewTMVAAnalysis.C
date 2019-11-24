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
#include "TH2F.h"

using namespace std;


void NewTMVAAnalysis() {

	cout << "===> Start NewTMVAAnalysis\n" << endl;

//----SET INPUT--------------------------------------------------

	const int pp_flag = 0; // p-p=1, Pb-Pb=0

	// Open files
	TFile *inputFile    = new TFile( "rootfiles/TMVAapplied.root",                        "READ"     );   
	TFile *inputFile_pp = new TFile( "rootfiles/pp_pp/bdt_atlas+jfllr/TMVAanalysis.root", "READ"     );
	TFile *outputFile   = new TFile( "rootfiles/TMVAanalysis.root",                       "RECREATE" );

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
    TLegend *leg = new TLegend(0.72,0.75,0.9,0.89); // (x1,y1,x2,y2)
    leg->SetFillColor(0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);

	TH1::SetDefaultSumw2(); // store sum of squares of weights

//----SAMPLE-----------------------------------------------------

	// Get sample histograms
	TH1F *histSampleSig_pt         = (TH1F*) inputFile->Get("MVA_SIGNAL_pt");
	TH1F *histSampleBkg_pt         = (TH1F*) inputFile->Get("MVA_Background_pt");
	TH1F *histSampleOther_pt       = (TH1F*) inputFile->Get("MVA_Other_pt");
	TH1F *histSampleSig_eta        = (TH1F*) inputFile->Get("MVA_SIGNAL_eta");
	TH1F *histSampleBkg_eta        = (TH1F*) inputFile->Get("MVA_Background_eta");
	TH1F *histSampleOther_eta      = (TH1F*) inputFile->Get("MVA_Other_eta");
	TH1F *histSampleSig_abseta     = (TH1F*) inputFile->Get("MVA_SIGNAL_abseta");
	TH1F *histSampleBkg_abseta     = (TH1F*) inputFile->Get("MVA_Background_abseta");
	TH1F *histSampleOther_abseta   = (TH1F*) inputFile->Get("MVA_Other_abseta");
	TH1F *histSampleSig_phi        = (TH1F*) inputFile->Get("MVA_SIGNAL_phi");
	TH1F *histSampleBkg_phi        = (TH1F*) inputFile->Get("MVA_Background_phi");
	TH1F *histSampleOther_phi      = (TH1F*) inputFile->Get("MVA_Other_phi");
	TH1F *histSampleSig_centzone   = (TH1F*) inputFile->Get("MVA_SIGNAL_centzone");
	TH1F *histSampleBkg_centzone   = (TH1F*) inputFile->Get("MVA_Background_centzone");
	TH1F *histSampleOther_centzone = (TH1F*) inputFile->Get("MVA_Other_centzone");

	TH2F *pt_vs_eta             = (TH2F*) inputFile->Get("pt_vs_eta");
	TH2F *Sig_pt_vs_eta         = (TH2F*) inputFile->Get("Sig_pt_vs_eta");
	TH2F *Bkg_pt_vs_eta         = (TH2F*) inputFile->Get("Bkg_pt_vs_eta");
	TH2F *Other_pt_vs_eta       = (TH2F*) inputFile->Get("Other_pt_vs_eta");
	TH2F *pt_vs_phi             = (TH2F*) inputFile->Get("pt_vs_eta");
	TH2F *Sig_pt_vs_phi         = (TH2F*) inputFile->Get("Sig_pt_vs_phi");
	TH2F *Bkg_pt_vs_phi         = (TH2F*) inputFile->Get("Bkg_pt_vs_phi");
	TH2F *Other_pt_vs_phi       = (TH2F*) inputFile->Get("Other_pt_vs_phi");
	TH2F *pt_vs_centzone        = (TH2F*) inputFile->Get("pt_vs_centzone");
	TH2F *Sig_pt_vs_centzone    = (TH2F*) inputFile->Get("Sig_pt_vs_centzone");
	TH2F *Bkg_pt_vs_centzone    = (TH2F*) inputFile->Get("Bkg_pt_vs_centzone");
	TH2F *Other_pt_vs_centzone  = (TH2F*) inputFile->Get("Other_pt_vs_centzone");
	TH2F *phi_vs_eta            = (TH2F*) inputFile->Get("phi_vs_eta");
	TH2F *Sig_phi_vs_eta        = (TH2F*) inputFile->Get("Sig_phi_vs_eta");
	TH2F *Bkg_phi_vs_eta        = (TH2F*) inputFile->Get("Bkg_phi_vs_eta");
	TH2F *Other_phi_vs_eta      = (TH2F*) inputFile->Get("Other_phi_vs_eta");
	TH2F *phi_vs_centzone       = (TH2F*) inputFile->Get("phi_vs_centzone");
	TH2F *Sig_phi_vs_centzone   = (TH2F*) inputFile->Get("Sig_phi_vs_centzone");
	TH2F *Bkg_phi_vs_centzone   = (TH2F*) inputFile->Get("Bkg_phi_vs_centzone");
	TH2F *Other_phi_vs_centzone = (TH2F*) inputFile->Get("Other_phi_vs_centzone");
	TH2F *centzone_vs_eta       = (TH2F*) inputFile->Get("centzone_vs_eta");
	TH2F *Sig_centzone_vs_eta   = (TH2F*) inputFile->Get("Sig_centzone_vs_eta");
	TH2F *Bkg_centzone_vs_eta   = (TH2F*) inputFile->Get("Bkg_centzone_vs_eta");
	TH2F *Other_centzone_vs_eta = (TH2F*) inputFile->Get("Other_centzone_vs_eta");

// TH2F variable projections

	TH1D *Sig_pt_vs_centzone_Yproj_1 = Sig_pt_vs_centzone->ProjectionY("Sig_pt_vs_centzone_Yproj_1", 3, 4);
	TH1D *Sig_pt_vs_centzone_Yproj_2 = Sig_pt_vs_centzone->ProjectionY("Sig_pt_vs_centzone_Yproj_2", 5, 6);
	TH1D *Sig_pt_vs_centzone_Yproj_3 = Sig_pt_vs_centzone->ProjectionY("Sig_pt_vs_centzone_Yproj_3", 7, 8);
	TH1D *Sig_pt_vs_centzone_Yproj_4 = Sig_pt_vs_centzone->ProjectionY("Sig_pt_vs_centzone_Yproj_4", 9, 10);
	TH1D *Sig_pt_vs_centzone_Yproj_5 = Sig_pt_vs_centzone->ProjectionY("Sig_pt_vs_centzone_Yproj_5", 11, 12);
	TH1D *Sig_pt_vs_centzone_Yproj_6 = Sig_pt_vs_centzone->ProjectionY("Sig_pt_vs_centzone_Yproj_6", 7, 10);
	TH1D *Sig_pt_vs_centzone_Yproj_7 = Sig_pt_vs_centzone->ProjectionY("Sig_pt_vs_centzone_Yproj_7", 3, 6);
	TH1D *Bkg_pt_vs_centzone_Yproj_1 = Bkg_pt_vs_centzone->ProjectionY("Bkg_pt_vs_centzone_Yproj_1", 3, 4);
	TH1D *Bkg_pt_vs_centzone_Yproj_2 = Bkg_pt_vs_centzone->ProjectionY("Bkg_pt_vs_centzone_Yproj_2", 5, 6);
	TH1D *Bkg_pt_vs_centzone_Yproj_3 = Bkg_pt_vs_centzone->ProjectionY("Bkg_pt_vs_centzone_Yproj_3", 7, 8);
	TH1D *Bkg_pt_vs_centzone_Yproj_4 = Bkg_pt_vs_centzone->ProjectionY("Bkg_pt_vs_centzone_Yproj_4", 9, 10);
	TH1D *Bkg_pt_vs_centzone_Yproj_5 = Bkg_pt_vs_centzone->ProjectionY("Bkg_pt_vs_centzone_Yproj_5", 11, 12);
	TH1D *Bkg_pt_vs_centzone_Yproj_6 = Bkg_pt_vs_centzone->ProjectionY("Bkg_pt_vs_centzone_Yproj_6", 7, 10);
	TH1D *Bkg_pt_vs_centzone_Yproj_7 = Bkg_pt_vs_centzone->ProjectionY("Bkg_pt_vs_centzone_Yproj_7", 3, 6);
	TH1D *Other_pt_vs_centzone_Yproj_1 = Other_pt_vs_centzone->ProjectionY("Other_pt_vs_centzone_Yproj_1", 3, 4);
	TH1D *Other_pt_vs_centzone_Yproj_2 = Other_pt_vs_centzone->ProjectionY("Other_pt_vs_centzone_Yproj_2", 5, 6);
	TH1D *Other_pt_vs_centzone_Yproj_3 = Other_pt_vs_centzone->ProjectionY("Other_pt_vs_centzone_Yproj_3", 7, 8);
	TH1D *Other_pt_vs_centzone_Yproj_4 = Other_pt_vs_centzone->ProjectionY("Other_pt_vs_centzone_Yproj_4", 9, 10);
	TH1D *Other_pt_vs_centzone_Yproj_5 = Other_pt_vs_centzone->ProjectionY("Other_pt_vs_centzone_Yproj_5", 11, 12);
	TH1D *Other_pt_vs_centzone_Yproj_6 = Other_pt_vs_centzone->ProjectionY("Other_pt_vs_centzone_Yproj_6", 7, 10);
	TH1D *Other_pt_vs_centzone_Yproj_7 = Other_pt_vs_centzone->ProjectionY("Other_pt_vs_centzone_Yproj_7", 3, 6);

	TH1D *Sig_phi_vs_centzone_Yproj_1 = Sig_phi_vs_centzone->ProjectionY("Sig_phi_vs_centzone_Yproj_1", 3, 4);
	TH1D *Sig_phi_vs_centzone_Yproj_2 = Sig_phi_vs_centzone->ProjectionY("Sig_phi_vs_centzone_Yproj_2", 5, 6);
	TH1D *Sig_phi_vs_centzone_Yproj_3 = Sig_phi_vs_centzone->ProjectionY("Sig_phi_vs_centzone_Yproj_3", 7, 8);
	TH1D *Sig_phi_vs_centzone_Yproj_4 = Sig_phi_vs_centzone->ProjectionY("Sig_phi_vs_centzone_Yproj_4", 9, 10);
	TH1D *Sig_phi_vs_centzone_Yproj_5 = Sig_phi_vs_centzone->ProjectionY("Sig_phi_vs_centzone_Yproj_5", 11, 12);
	TH1D *Bkg_phi_vs_centzone_Yproj_1 = Bkg_phi_vs_centzone->ProjectionY("Bkg_phi_vs_centzone_Yproj_1", 3, 4);
	TH1D *Bkg_phi_vs_centzone_Yproj_2 = Bkg_phi_vs_centzone->ProjectionY("Bkg_phi_vs_centzone_Yproj_2", 5, 6);
	TH1D *Bkg_phi_vs_centzone_Yproj_3 = Bkg_phi_vs_centzone->ProjectionY("Bkg_phi_vs_centzone_Yproj_3", 7, 8);
	TH1D *Bkg_phi_vs_centzone_Yproj_4 = Bkg_phi_vs_centzone->ProjectionY("Bkg_phi_vs_centzone_Yproj_4", 9, 10);
	TH1D *Bkg_phi_vs_centzone_Yproj_5 = Bkg_phi_vs_centzone->ProjectionY("Bkg_phi_vs_centzone_Yproj_5", 11, 12);
	TH1D *Other_phi_vs_centzone_Yproj_1 = Other_phi_vs_centzone->ProjectionY("Other_phi_vs_centzone_Yproj_1", 3, 4);
	TH1D *Other_phi_vs_centzone_Yproj_2 = Other_phi_vs_centzone->ProjectionY("Other_phi_vs_centzone_Yproj_2", 5, 6);
	TH1D *Other_phi_vs_centzone_Yproj_3 = Other_phi_vs_centzone->ProjectionY("Other_phi_vs_centzone_Yproj_3", 7, 8);
	TH1D *Other_phi_vs_centzone_Yproj_4 = Other_phi_vs_centzone->ProjectionY("Other_phi_vs_centzone_Yproj_4", 9, 10);
	TH1D *Other_phi_vs_centzone_Yproj_5 = Other_phi_vs_centzone->ProjectionY("Other_phi_vs_centzone_Yproj_5", 11, 12);

	TH1D *Sig_centzone_vs_eta_Xproj_1 = Sig_centzone_vs_eta->ProjectionX("Sig_centzone_vs_eta_Xproj_1", 3, 4);
	TH1D *Sig_centzone_vs_eta_Xproj_2 = Sig_centzone_vs_eta->ProjectionX("Sig_centzone_vs_eta_Xproj_2", 5, 6);
	TH1D *Sig_centzone_vs_eta_Xproj_3 = Sig_centzone_vs_eta->ProjectionX("Sig_centzone_vs_eta_Xproj_3", 7, 8);
	TH1D *Sig_centzone_vs_eta_Xproj_4 = Sig_centzone_vs_eta->ProjectionX("Sig_centzone_vs_eta_Xproj_4", 9, 10);
	TH1D *Sig_centzone_vs_eta_Xproj_5 = Sig_centzone_vs_eta->ProjectionX("Sig_centzone_vs_eta_Xproj_5", 11, 12);
	TH1D *Bkg_centzone_vs_eta_Xproj_1 = Bkg_centzone_vs_eta->ProjectionX("Bkg_centzone_vs_eta_Xproj_1", 3, 4);
	TH1D *Bkg_centzone_vs_eta_Xproj_2 = Bkg_centzone_vs_eta->ProjectionX("Bkg_centzone_vs_eta_Xproj_2", 5, 6);
	TH1D *Bkg_centzone_vs_eta_Xproj_3 = Bkg_centzone_vs_eta->ProjectionX("Bkg_centzone_vs_eta_Xproj_3", 7, 8);
	TH1D *Bkg_centzone_vs_eta_Xproj_4 = Bkg_centzone_vs_eta->ProjectionX("Bkg_centzone_vs_eta_Xproj_4", 9, 10);
	TH1D *Bkg_centzone_vs_eta_Xproj_5 = Bkg_centzone_vs_eta->ProjectionX("Bkg_centzone_vs_eta_Xproj_5", 11, 12);
	TH1D *Other_centzone_vs_eta_Xproj_1 = Other_centzone_vs_eta->ProjectionX("Other_centzone_vs_eta_Xproj_1", 3, 4);
	TH1D *Other_centzone_vs_eta_Xproj_2 = Other_centzone_vs_eta->ProjectionX("Other_centzone_vs_eta_Xproj_2", 5, 6);
	TH1D *Other_centzone_vs_eta_Xproj_3 = Other_centzone_vs_eta->ProjectionX("Other_centzone_vs_eta_Xproj_3", 7, 8);
	TH1D *Other_centzone_vs_eta_Xproj_4 = Other_centzone_vs_eta->ProjectionX("Other_centzone_vs_eta_Xproj_4", 9, 10);
	TH1D *Other_centzone_vs_eta_Xproj_5 = Other_centzone_vs_eta->ProjectionX("Other_centzone_vs_eta_Xproj_5", 11, 12);

	TH1D *Sig_pt_vs_eta_Yproj_1 = Sig_pt_vs_eta->ProjectionY("Sig_pt_vs_eta_Yproj_1", 0, 5);
	TH1D *Sig_pt_vs_eta_Yproj_2 = Sig_pt_vs_eta->ProjectionY("Sig_pt_vs_eta_Yproj_2", 6, 10);
	TH1D *Sig_pt_vs_eta_Yproj_3 = Sig_pt_vs_eta->ProjectionY("Sig_pt_vs_eta_Yproj_3", 11, 15);
	TH1D *Sig_pt_vs_eta_Yproj_4 = Sig_pt_vs_eta->ProjectionY("Sig_pt_vs_eta_Yproj_4", 16, 20);
	TH1D *Sig_pt_vs_eta_Yproj_5 = Sig_pt_vs_eta->ProjectionY("Sig_pt_vs_eta_Yproj_5", 21, 25);
	TH1D *Sig_pt_vs_eta_Yproj_6 = Sig_pt_vs_eta->ProjectionY("Sig_pt_vs_eta_Yproj_6", 26, Sig_pt_vs_eta->GetNbinsX()+1);
	TH1D *Bkg_pt_vs_eta_Yproj_1 = Bkg_pt_vs_eta->ProjectionY("Bkg_pt_vs_eta_Yproj_1", 0, 5);
	TH1D *Bkg_pt_vs_eta_Yproj_2 = Bkg_pt_vs_eta->ProjectionY("Bkg_pt_vs_eta_Yproj_2", 6, 10);
	TH1D *Bkg_pt_vs_eta_Yproj_3 = Bkg_pt_vs_eta->ProjectionY("Bkg_pt_vs_eta_Yproj_3", 11, 15);
	TH1D *Bkg_pt_vs_eta_Yproj_4 = Bkg_pt_vs_eta->ProjectionY("Bkg_pt_vs_eta_Yproj_4", 16, 20);
	TH1D *Bkg_pt_vs_eta_Yproj_5 = Bkg_pt_vs_eta->ProjectionY("Bkg_pt_vs_eta_Yproj_5", 21, 25);
	TH1D *Bkg_pt_vs_eta_Yproj_6 = Bkg_pt_vs_eta->ProjectionY("Bkg_pt_vs_eta_Yproj_6", 26, Bkg_pt_vs_eta->GetNbinsX()+1);
	TH1D *Other_pt_vs_eta_Yproj_1 = Other_pt_vs_eta->ProjectionY("Other_pt_vs_eta_Yproj_1", 0, 5);
	TH1D *Other_pt_vs_eta_Yproj_2 = Other_pt_vs_eta->ProjectionY("Other_pt_vs_eta_Yproj_2", 6, 10);
	TH1D *Other_pt_vs_eta_Yproj_3 = Other_pt_vs_eta->ProjectionY("Other_pt_vs_eta_Yproj_3", 11, 15);
	TH1D *Other_pt_vs_eta_Yproj_4 = Other_pt_vs_eta->ProjectionY("Other_pt_vs_eta_Yproj_4", 16, 20);
	TH1D *Other_pt_vs_eta_Yproj_5 = Other_pt_vs_eta->ProjectionY("Other_pt_vs_eta_Yproj_5", 21, 25);
	TH1D *Other_pt_vs_eta_Yproj_6 = Other_pt_vs_eta->ProjectionY("Other_pt_vs_eta_Yproj_6", 26, Other_pt_vs_eta->GetNbinsX()+1);

	TH1D *Sig_pt_vs_phi_Yproj_1 = Sig_pt_vs_phi->ProjectionY("Sig_pt_vs_phi_Yproj_1", 0, 5);
	TH1D *Sig_pt_vs_phi_Yproj_2 = Sig_pt_vs_phi->ProjectionY("Sig_pt_vs_phi_Yproj_2", 6, 10);
	TH1D *Sig_pt_vs_phi_Yproj_3 = Sig_pt_vs_phi->ProjectionY("Sig_pt_vs_phi_Yproj_3", 11, 15);
	TH1D *Sig_pt_vs_phi_Yproj_4 = Sig_pt_vs_phi->ProjectionY("Sig_pt_vs_phi_Yproj_4", 16, 20);
	TH1D *Sig_pt_vs_phi_Yproj_5 = Sig_pt_vs_phi->ProjectionY("Sig_pt_vs_phi_Yproj_5", 21, 25);
	TH1D *Sig_pt_vs_phi_Yproj_6 = Sig_pt_vs_phi->ProjectionY("Sig_pt_vs_phi_Yproj_6", 26, Sig_pt_vs_eta->GetNbinsX()+1);
	TH1D *Bkg_pt_vs_phi_Yproj_1 = Bkg_pt_vs_phi->ProjectionY("Bkg_pt_vs_phi_Yproj_1", 0, 5);
	TH1D *Bkg_pt_vs_phi_Yproj_2 = Bkg_pt_vs_phi->ProjectionY("Bkg_pt_vs_phi_Yproj_2", 6, 10);
	TH1D *Bkg_pt_vs_phi_Yproj_3 = Bkg_pt_vs_phi->ProjectionY("Bkg_pt_vs_phi_Yproj_3", 11, 15);
	TH1D *Bkg_pt_vs_phi_Yproj_4 = Bkg_pt_vs_phi->ProjectionY("Bkg_pt_vs_phi_Yproj_4", 16, 20);
	TH1D *Bkg_pt_vs_phi_Yproj_5 = Bkg_pt_vs_phi->ProjectionY("Bkg_pt_vs_phi_Yproj_5", 21, 25);
	TH1D *Bkg_pt_vs_phi_Yproj_6 = Bkg_pt_vs_phi->ProjectionY("Bkg_pt_vs_phi_Yproj_6", 26, Bkg_pt_vs_eta->GetNbinsX()+1);
	TH1D *Other_pt_vs_phi_Yproj_1 = Other_pt_vs_phi->ProjectionY("Other_pt_vs_phi_Yproj_1", 0, 5);
	TH1D *Other_pt_vs_phi_Yproj_2 = Other_pt_vs_phi->ProjectionY("Other_pt_vs_phi_Yproj_2", 6, 10);
	TH1D *Other_pt_vs_phi_Yproj_3 = Other_pt_vs_phi->ProjectionY("Other_pt_vs_phi_Yproj_3", 11, 15);
	TH1D *Other_pt_vs_phi_Yproj_4 = Other_pt_vs_phi->ProjectionY("Other_pt_vs_phi_Yproj_4", 16, 20);
	TH1D *Other_pt_vs_phi_Yproj_5 = Other_pt_vs_phi->ProjectionY("Other_pt_vs_phi_Yproj_5", 21, 25);
	TH1D *Other_pt_vs_phi_Yproj_6 = Other_pt_vs_phi->ProjectionY("Other_pt_vs_phi_Yproj_6", 26, Other_pt_vs_eta->GetNbinsX()+1);

// Title, Axis, Style

	histSampleBkg_pt->SetTitle("Sample p_{T}");
	histSampleBkg_pt->GetXaxis()->SetTitle("p_{T} (MeV)");
	histSampleBkg_pt->GetYaxis()->SetTitle("N/N_{Total}");
	histSampleBkg_pt->GetXaxis()->SetRange(histSampleBkg_pt->GetXaxis()->FindBin(100000),histSampleBkg_pt->GetXaxis()->GetLast());
	histSampleBkg_pt->SetLineColor(kRed);
	histSampleBkg_pt->SetLineWidth(2);
	histSampleSig_pt->SetLineColor(kBlue);
	histSampleSig_pt->SetLineWidth(2);
	histSampleOther_pt->SetLineColor(kCyan);
	histSampleOther_pt->SetLineWidth(2);

	histSampleSig_eta->SetTitle("Sample #eta");
	histSampleSig_eta->GetXaxis()->SetTitle("#eta");
	histSampleSig_eta->GetYaxis()->SetTitle("N/N_{Total}");
	histSampleSig_eta->GetXaxis()->SetRangeUser(-2.5, 2.5);
	histSampleSig_eta->SetMinimum(0.);
	histSampleBkg_eta->SetLineColor(kRed);
	histSampleBkg_eta->SetLineWidth(2);
	histSampleSig_eta->SetLineColor(kBlue);
	histSampleSig_eta->SetLineWidth(2);
	histSampleOther_eta->SetLineColor(kCyan);
	histSampleOther_eta->SetLineWidth(2);

	histSampleSig_abseta->SetTitle("Sample |#eta|");
	histSampleSig_abseta->GetXaxis()->SetTitle("|#eta|");
	histSampleSig_abseta->GetYaxis()->SetTitle("N/N_{Total}");
	histSampleSig_abseta->GetXaxis()->SetRangeUser(0, 2.5);
	histSampleSig_abseta->SetMinimum(0.);
	histSampleBkg_abseta->SetLineColor(kRed);
	histSampleBkg_abseta->SetLineWidth(2);
	histSampleSig_abseta->SetLineColor(kBlue);
	histSampleSig_abseta->SetLineWidth(2);
	histSampleOther_abseta->SetLineColor(kCyan);
	histSampleOther_abseta->SetLineWidth(2);

	histSampleOther_phi->SetTitle("Sample #phi");
	histSampleOther_phi->GetXaxis()->SetTitle("#phi (rad)");
	histSampleOther_phi->GetYaxis()->SetTitle("N/N_{Total}");
	histSampleOther_phi->SetMinimum(0.);
	histSampleBkg_phi->SetLineColor(kRed);
	histSampleBkg_phi->SetLineWidth(2);
	histSampleSig_phi->SetLineColor(kBlue);
	histSampleSig_phi->SetLineWidth(2);
	histSampleOther_phi->SetLineColor(kCyan);
	histSampleOther_phi->SetLineWidth(2);

	histSampleBkg_centzone->SetTitle("Sample Centrality");
	histSampleBkg_centzone->GetXaxis()->SetTitle("Centrality");
	histSampleBkg_centzone->GetYaxis()->SetTitle("N/N_{Total}");
	histSampleBkg_centzone->SetMinimum(0.);
	histSampleBkg_centzone->SetLineColor(kRed);
	histSampleBkg_centzone->SetLineWidth(2);
	histSampleSig_centzone->SetLineColor(kBlue);
	histSampleSig_centzone->SetLineWidth(2);
	histSampleOther_centzone->SetLineColor(kCyan);
	histSampleOther_centzone->SetLineWidth(2);

	// variable vs. variable
	Bkg_pt_vs_centzone_Yproj_1->SetTitle("p_{T} with centrality #in [0, 20] %");
	Bkg_pt_vs_centzone_Yproj_1->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_centzone_Yproj_1->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_centzone_Yproj_1->GetXaxis()->SetRange(Bkg_pt_vs_centzone_Yproj_1->GetXaxis()->FindBin(100000),Bkg_pt_vs_centzone_Yproj_1->GetXaxis()->GetLast());
	Sig_pt_vs_centzone_Yproj_1->SetLineColor(kBlue);
	Sig_pt_vs_centzone_Yproj_1->SetLineWidth(2);
	Bkg_pt_vs_centzone_Yproj_1->SetLineColor(kRed);
	Bkg_pt_vs_centzone_Yproj_1->SetLineWidth(2);
	Other_pt_vs_centzone_Yproj_1->SetLineColor(kCyan);
	Other_pt_vs_centzone_Yproj_1->SetLineWidth(2);
	Bkg_pt_vs_centzone_Yproj_2->SetTitle("p_{T} with centrality #in ]20, 40] %");
	Bkg_pt_vs_centzone_Yproj_2->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_centzone_Yproj_2->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_centzone_Yproj_2->GetXaxis()->SetRange(Bkg_pt_vs_centzone_Yproj_2->GetXaxis()->FindBin(100000),Bkg_pt_vs_centzone_Yproj_2->GetXaxis()->GetLast());
	Sig_pt_vs_centzone_Yproj_2->SetLineColor(kBlue);
	Sig_pt_vs_centzone_Yproj_2->SetLineWidth(2);
	Bkg_pt_vs_centzone_Yproj_2->SetLineColor(kRed);
	Bkg_pt_vs_centzone_Yproj_2->SetLineWidth(2);
	Other_pt_vs_centzone_Yproj_2->SetLineColor(kCyan);
	Other_pt_vs_centzone_Yproj_2->SetLineWidth(2);
	Bkg_pt_vs_centzone_Yproj_3->SetTitle("p_{T} with centrality #in ]40, 60] %");
	Bkg_pt_vs_centzone_Yproj_3->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_centzone_Yproj_3->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_centzone_Yproj_3->GetXaxis()->SetRange(Bkg_pt_vs_centzone_Yproj_3->GetXaxis()->FindBin(100000),Bkg_pt_vs_centzone_Yproj_3->GetXaxis()->GetLast());
	Sig_pt_vs_centzone_Yproj_3->SetLineColor(kBlue);
	Sig_pt_vs_centzone_Yproj_3->SetLineWidth(2);
	Bkg_pt_vs_centzone_Yproj_3->SetLineColor(kRed);
	Bkg_pt_vs_centzone_Yproj_3->SetLineWidth(2);
	Other_pt_vs_centzone_Yproj_3->SetLineColor(kCyan);
	Other_pt_vs_centzone_Yproj_3->SetLineWidth(2);
	Bkg_pt_vs_centzone_Yproj_4->SetTitle("p_{T} with centrality #in ]60, 80] %");
	Bkg_pt_vs_centzone_Yproj_4->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_centzone_Yproj_4->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_centzone_Yproj_4->GetXaxis()->SetRange(Bkg_pt_vs_centzone_Yproj_4->GetXaxis()->FindBin(100000),Bkg_pt_vs_centzone_Yproj_4->GetXaxis()->GetLast());
	Sig_pt_vs_centzone_Yproj_4->SetLineColor(kBlue);
	Sig_pt_vs_centzone_Yproj_4->SetLineWidth(2);
	Bkg_pt_vs_centzone_Yproj_4->SetLineColor(kRed);
	Bkg_pt_vs_centzone_Yproj_4->SetLineWidth(2);
	Other_pt_vs_centzone_Yproj_4->SetLineColor(kCyan);
	Other_pt_vs_centzone_Yproj_4->SetLineWidth(2);
	Bkg_pt_vs_centzone_Yproj_5->SetTitle("p_{T} with centrality #in ]80, 90] %  ");
	Bkg_pt_vs_centzone_Yproj_5->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_centzone_Yproj_5->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_centzone_Yproj_5->GetXaxis()->SetRange(Bkg_pt_vs_centzone_Yproj_5->GetXaxis()->FindBin(100000),Bkg_pt_vs_centzone_Yproj_5->GetXaxis()->GetLast());
	Sig_pt_vs_centzone_Yproj_5->SetLineColor(kBlue);
	Sig_pt_vs_centzone_Yproj_5->SetLineWidth(2);
	Bkg_pt_vs_centzone_Yproj_5->SetLineColor(kRed);
	Bkg_pt_vs_centzone_Yproj_5->SetLineWidth(2);
	Other_pt_vs_centzone_Yproj_5->SetLineColor(kCyan);
	Other_pt_vs_centzone_Yproj_5->SetLineWidth(2);
	Bkg_pt_vs_centzone_Yproj_6->SetTitle("p_{T} with centrality #in ]40, 80] % ");
	Bkg_pt_vs_centzone_Yproj_6->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_centzone_Yproj_6->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_centzone_Yproj_6->GetXaxis()->SetRange(Bkg_pt_vs_centzone_Yproj_6->GetXaxis()->FindBin(100000),Bkg_pt_vs_centzone_Yproj_6->GetXaxis()->GetLast());
	Sig_pt_vs_centzone_Yproj_6->SetLineColor(kBlue);
	Sig_pt_vs_centzone_Yproj_6->SetLineWidth(2);
	Bkg_pt_vs_centzone_Yproj_6->SetLineColor(kRed);
	Bkg_pt_vs_centzone_Yproj_6->SetLineWidth(2);
	Other_pt_vs_centzone_Yproj_6->SetLineColor(kCyan);
	Other_pt_vs_centzone_Yproj_6->SetLineWidth(2);
	Bkg_pt_vs_centzone_Yproj_7->SetTitle("p_{T} with centrality #in [0, 40] % ");
	Bkg_pt_vs_centzone_Yproj_7->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_centzone_Yproj_7->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_centzone_Yproj_7->GetXaxis()->SetRange(Bkg_pt_vs_centzone_Yproj_7->GetXaxis()->FindBin(100000),Bkg_pt_vs_centzone_Yproj_7->GetXaxis()->GetLast());
	Sig_pt_vs_centzone_Yproj_7->SetLineColor(kBlue);
	Sig_pt_vs_centzone_Yproj_7->SetLineWidth(2);
	Bkg_pt_vs_centzone_Yproj_7->SetLineColor(kRed);
	Bkg_pt_vs_centzone_Yproj_7->SetLineWidth(2);
	Other_pt_vs_centzone_Yproj_7->SetLineColor(kCyan);
	Other_pt_vs_centzone_Yproj_7->SetLineWidth(2);

	Bkg_pt_vs_eta_Yproj_1->SetTitle("p_{T} with #eta #in [-2.5,-2]");
	Bkg_pt_vs_eta_Yproj_1->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_eta_Yproj_1->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_eta_Yproj_1->GetXaxis()->SetRange(Bkg_pt_vs_eta_Yproj_1->GetXaxis()->FindBin(100000),Bkg_pt_vs_eta_Yproj_1->GetXaxis()->GetLast());
	Sig_pt_vs_eta_Yproj_1->SetLineColor(kBlue);
	Sig_pt_vs_eta_Yproj_1->SetLineWidth(2);
	Bkg_pt_vs_eta_Yproj_1->SetLineColor(kRed);
	Bkg_pt_vs_eta_Yproj_1->SetLineWidth(2);
	Other_pt_vs_eta_Yproj_1->SetLineColor(kCyan);
	Other_pt_vs_eta_Yproj_1->SetLineWidth(2);
	Bkg_pt_vs_eta_Yproj_2->SetTitle("p_{T} with #eta #in ]-2,-1]");
	Bkg_pt_vs_eta_Yproj_2->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_eta_Yproj_2->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_eta_Yproj_2->GetXaxis()->SetRange(Bkg_pt_vs_eta_Yproj_2->GetXaxis()->FindBin(100000),Bkg_pt_vs_eta_Yproj_2->GetXaxis()->GetLast());
	Sig_pt_vs_eta_Yproj_2->SetLineColor(kBlue);
	Sig_pt_vs_eta_Yproj_2->SetLineWidth(2);
	Bkg_pt_vs_eta_Yproj_2->SetLineColor(kRed);
	Bkg_pt_vs_eta_Yproj_2->SetLineWidth(2);
	Other_pt_vs_eta_Yproj_2->SetLineColor(kCyan);
	Other_pt_vs_eta_Yproj_2->SetLineWidth(2);
	Bkg_pt_vs_eta_Yproj_3->SetTitle("p_{T} with #eta #in ]-1, 0]");
	Bkg_pt_vs_eta_Yproj_3->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_eta_Yproj_3->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_eta_Yproj_3->GetXaxis()->SetRange(Bkg_pt_vs_eta_Yproj_3->GetXaxis()->FindBin(100000),Bkg_pt_vs_eta_Yproj_3->GetXaxis()->GetLast());
	Sig_pt_vs_eta_Yproj_3->SetLineColor(kBlue);
	Sig_pt_vs_eta_Yproj_3->SetLineWidth(2);
	Bkg_pt_vs_eta_Yproj_3->SetLineColor(kRed);
	Bkg_pt_vs_eta_Yproj_3->SetLineWidth(2);
	Other_pt_vs_eta_Yproj_3->SetLineColor(kCyan);
	Other_pt_vs_eta_Yproj_3->SetLineWidth(2);
	Bkg_pt_vs_eta_Yproj_4->SetTitle("p_{T} with #eta #in ]0, 1]");
	Bkg_pt_vs_eta_Yproj_4->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_eta_Yproj_4->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_eta_Yproj_4->GetXaxis()->SetRange(Bkg_pt_vs_eta_Yproj_4->GetXaxis()->FindBin(100000),Bkg_pt_vs_eta_Yproj_4->GetXaxis()->GetLast());
	Sig_pt_vs_eta_Yproj_4->SetLineColor(kBlue);
	Sig_pt_vs_eta_Yproj_4->SetLineWidth(2);
	Bkg_pt_vs_eta_Yproj_4->SetLineColor(kRed);
	Bkg_pt_vs_eta_Yproj_4->SetLineWidth(2);
	Other_pt_vs_eta_Yproj_4->SetLineColor(kCyan);
	Other_pt_vs_eta_Yproj_4->SetLineWidth(2);
	Bkg_pt_vs_eta_Yproj_5->SetTitle("p_{T} with #eta #in ]1, 2]");
	Bkg_pt_vs_eta_Yproj_5->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_eta_Yproj_5->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_eta_Yproj_5->GetXaxis()->SetRange(Bkg_pt_vs_eta_Yproj_5->GetXaxis()->FindBin(100000),Bkg_pt_vs_eta_Yproj_5->GetXaxis()->GetLast());
	Sig_pt_vs_eta_Yproj_5->SetLineColor(kBlue);
	Sig_pt_vs_eta_Yproj_5->SetLineWidth(2);
	Bkg_pt_vs_eta_Yproj_5->SetLineColor(kRed);
	Bkg_pt_vs_eta_Yproj_5->SetLineWidth(2);
	Other_pt_vs_eta_Yproj_5->SetLineColor(kCyan);
	Other_pt_vs_eta_Yproj_5->SetLineWidth(2);
	Bkg_pt_vs_eta_Yproj_6->SetTitle("p_{T} with #eta #in ]2, 2.5]");
	Bkg_pt_vs_eta_Yproj_6->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_eta_Yproj_6->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_eta_Yproj_6->GetXaxis()->SetRange(Bkg_pt_vs_eta_Yproj_6->GetXaxis()->FindBin(100000),Bkg_pt_vs_eta_Yproj_6->GetXaxis()->GetLast());
	Sig_pt_vs_eta_Yproj_6->SetLineColor(kBlue);
	Sig_pt_vs_eta_Yproj_6->SetLineWidth(2);
	Bkg_pt_vs_eta_Yproj_6->SetLineColor(kRed);
	Bkg_pt_vs_eta_Yproj_6->SetLineWidth(2);
	Other_pt_vs_eta_Yproj_6->SetLineColor(kCyan);
	Other_pt_vs_eta_Yproj_6->SetLineWidth(2);

	Bkg_pt_vs_phi_Yproj_1->SetTitle("p_{T} with #phi #in [-#pi, -2#pi/3] rad");
	Bkg_pt_vs_phi_Yproj_1->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_phi_Yproj_1->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_phi_Yproj_1->GetXaxis()->SetRange(Bkg_pt_vs_phi_Yproj_1->GetXaxis()->FindBin(100000),Bkg_pt_vs_phi_Yproj_1->GetXaxis()->GetLast());
	Sig_pt_vs_phi_Yproj_1->SetLineColor(kBlue);
	Sig_pt_vs_phi_Yproj_1->SetLineWidth(2);
	Bkg_pt_vs_phi_Yproj_1->SetLineColor(kRed);
	Bkg_pt_vs_phi_Yproj_1->SetLineWidth(2);
	Other_pt_vs_phi_Yproj_1->SetLineColor(kCyan);
	Other_pt_vs_phi_Yproj_1->SetLineWidth(2);
	Bkg_pt_vs_phi_Yproj_2->SetTitle("p_{T} with #phi #in ]-2#pi/3, - #pi/3] rad");
	Bkg_pt_vs_phi_Yproj_2->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_phi_Yproj_2->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_phi_Yproj_2->GetXaxis()->SetRange(Bkg_pt_vs_phi_Yproj_2->GetXaxis()->FindBin(100000),Bkg_pt_vs_phi_Yproj_2->GetXaxis()->GetLast());
	Sig_pt_vs_phi_Yproj_2->SetLineColor(kBlue);
	Sig_pt_vs_phi_Yproj_2->SetLineWidth(2);
	Bkg_pt_vs_phi_Yproj_2->SetLineColor(kRed);
	Bkg_pt_vs_phi_Yproj_2->SetLineWidth(2);
	Other_pt_vs_phi_Yproj_2->SetLineColor(kCyan);
	Other_pt_vs_phi_Yproj_2->SetLineWidth(2);
	Bkg_pt_vs_phi_Yproj_3->SetTitle("p_{T} with #phi #in ]-#pi/3 , 0] rad");
	Bkg_pt_vs_phi_Yproj_3->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_phi_Yproj_3->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_phi_Yproj_3->GetXaxis()->SetRange(Bkg_pt_vs_phi_Yproj_3->GetXaxis()->FindBin(100000),Bkg_pt_vs_phi_Yproj_3->GetXaxis()->GetLast());
	Sig_pt_vs_phi_Yproj_3->SetLineColor(kBlue);
	Sig_pt_vs_phi_Yproj_3->SetLineWidth(2);
	Bkg_pt_vs_phi_Yproj_3->SetLineColor(kRed);
	Bkg_pt_vs_phi_Yproj_3->SetLineWidth(2);
	Other_pt_vs_phi_Yproj_3->SetLineColor(kCyan);
	Other_pt_vs_phi_Yproj_3->SetLineWidth(2);
	Bkg_pt_vs_phi_Yproj_4->SetTitle("p_{T} with #phi #in ]0 , #pi/3] rad");
	Bkg_pt_vs_phi_Yproj_4->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_phi_Yproj_4->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_phi_Yproj_4->GetXaxis()->SetRange(Bkg_pt_vs_phi_Yproj_4->GetXaxis()->FindBin(100000),Bkg_pt_vs_phi_Yproj_4->GetXaxis()->GetLast());
	Sig_pt_vs_phi_Yproj_4->SetLineColor(kBlue);
	Sig_pt_vs_phi_Yproj_4->SetLineWidth(2);
	Bkg_pt_vs_phi_Yproj_4->SetLineColor(kRed);
	Bkg_pt_vs_phi_Yproj_4->SetLineWidth(2);
	Other_pt_vs_phi_Yproj_4->SetLineColor(kCyan);
	Other_pt_vs_phi_Yproj_4->SetLineWidth(2);
	Bkg_pt_vs_phi_Yproj_5->SetTitle("p_{T} with #phi #in ]#pi/3, 2#pi/3] rad");
	Bkg_pt_vs_phi_Yproj_5->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_phi_Yproj_5->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_phi_Yproj_5->GetXaxis()->SetRange(Bkg_pt_vs_phi_Yproj_5->GetXaxis()->FindBin(100000),Bkg_pt_vs_phi_Yproj_5->GetXaxis()->GetLast());
	Sig_pt_vs_phi_Yproj_5->SetLineColor(kBlue);
	Sig_pt_vs_phi_Yproj_5->SetLineWidth(2);
	Bkg_pt_vs_phi_Yproj_5->SetLineColor(kRed);
	Bkg_pt_vs_phi_Yproj_5->SetLineWidth(2);
	Other_pt_vs_phi_Yproj_5->SetLineColor(kCyan);
	Other_pt_vs_phi_Yproj_5->SetLineWidth(2);
	Bkg_pt_vs_phi_Yproj_6->SetTitle("p_{T} with #phi #in ]2#pi/3, #pi] rad");
	Bkg_pt_vs_phi_Yproj_6->GetXaxis()->SetTitle("p_{T} (MeV)");
	Bkg_pt_vs_phi_Yproj_6->GetYaxis()->SetTitle("N/N_{Total}");
	Bkg_pt_vs_phi_Yproj_6->GetXaxis()->SetRange(Bkg_pt_vs_phi_Yproj_6->GetXaxis()->FindBin(100000),Bkg_pt_vs_phi_Yproj_6->GetXaxis()->GetLast());
	Sig_pt_vs_phi_Yproj_6->SetLineColor(kBlue);
	Sig_pt_vs_phi_Yproj_6->SetLineWidth(2);
	Bkg_pt_vs_phi_Yproj_6->SetLineColor(kRed);
	Bkg_pt_vs_phi_Yproj_6->SetLineWidth(2);
	Other_pt_vs_phi_Yproj_6->SetLineColor(kCyan);
	Other_pt_vs_phi_Yproj_6->SetLineWidth(2);

	Sig_phi_vs_centzone_Yproj_1->SetTitle("#phi with centrality #in [0, 20] %");
	Sig_phi_vs_centzone_Yproj_1->GetXaxis()->SetTitle("#phi (rad)");
	Sig_phi_vs_centzone_Yproj_1->GetYaxis()->SetTitle("N/N_{Total}");
	Sig_phi_vs_centzone_Yproj_1->SetLineColor(kBlue);
	Sig_phi_vs_centzone_Yproj_1->SetLineWidth(2);
	Bkg_phi_vs_centzone_Yproj_1->SetLineColor(kRed);
	Bkg_phi_vs_centzone_Yproj_1->SetLineWidth(2);
	Other_phi_vs_centzone_Yproj_1->SetLineColor(kCyan);
	Other_phi_vs_centzone_Yproj_1->SetLineWidth(2);
	Sig_phi_vs_centzone_Yproj_2->SetTitle("#phi with centrality #in ]20, 40] %");
	Sig_phi_vs_centzone_Yproj_2->GetXaxis()->SetTitle("#phi (rad)");
	Sig_phi_vs_centzone_Yproj_2->GetYaxis()->SetTitle("N/N_{Total}");
	Sig_phi_vs_centzone_Yproj_2->SetLineColor(kBlue);
	Sig_phi_vs_centzone_Yproj_2->SetLineWidth(2);
	Bkg_phi_vs_centzone_Yproj_2->SetLineColor(kRed);
	Bkg_phi_vs_centzone_Yproj_2->SetLineWidth(2);
	Other_phi_vs_centzone_Yproj_2->SetLineColor(kCyan);
	Other_phi_vs_centzone_Yproj_2->SetLineWidth(2);
	Sig_phi_vs_centzone_Yproj_3->SetTitle("#phi with centrality #in ]40, 60] %");
	Sig_phi_vs_centzone_Yproj_3->GetXaxis()->SetTitle("#phi (rad)");
	Sig_phi_vs_centzone_Yproj_3->GetYaxis()->SetTitle("N/N_{Total}");
	Sig_phi_vs_centzone_Yproj_3->SetLineColor(kBlue);
	Sig_phi_vs_centzone_Yproj_3->SetLineWidth(2);
	Bkg_phi_vs_centzone_Yproj_3->SetLineColor(kRed);
	Bkg_phi_vs_centzone_Yproj_3->SetLineWidth(2);
	Other_phi_vs_centzone_Yproj_3->SetLineColor(kCyan);
	Other_phi_vs_centzone_Yproj_3->SetLineWidth(2);
	Sig_phi_vs_centzone_Yproj_4->SetTitle("#phi with centrality #in ]60, 80] %");
	Sig_phi_vs_centzone_Yproj_4->GetXaxis()->SetTitle("#phi (rad)");
	Sig_phi_vs_centzone_Yproj_4->GetYaxis()->SetTitle("N/N_{Total}");
	Sig_phi_vs_centzone_Yproj_4->SetLineColor(kBlue);
	Sig_phi_vs_centzone_Yproj_4->SetLineWidth(2);
	Bkg_phi_vs_centzone_Yproj_4->SetLineColor(kRed);
	Bkg_phi_vs_centzone_Yproj_4->SetLineWidth(2);
	Other_phi_vs_centzone_Yproj_4->SetLineColor(kCyan);
	Other_phi_vs_centzone_Yproj_4->SetLineWidth(2); 
	Sig_phi_vs_centzone_Yproj_5->SetTitle("#phi with centrality #in ]80, 90] ");
	Sig_phi_vs_centzone_Yproj_5->GetXaxis()->SetTitle("#phi (rad)");
	Sig_phi_vs_centzone_Yproj_5->GetYaxis()->SetTitle("N/N_{Total}");
	Sig_phi_vs_centzone_Yproj_5->SetLineColor(kBlue);
	Sig_phi_vs_centzone_Yproj_5->SetLineWidth(2);
	Bkg_phi_vs_centzone_Yproj_5->SetLineColor(kRed);
	Bkg_phi_vs_centzone_Yproj_5->SetLineWidth(2);
	Other_phi_vs_centzone_Yproj_5->SetLineColor(kCyan);
	Other_phi_vs_centzone_Yproj_5->SetLineWidth(2);

	Sig_centzone_vs_eta_Xproj_1->SetTitle("#eta with centrality #in [0, 20] %");
	Sig_centzone_vs_eta_Xproj_1->GetXaxis()->SetTitle("#eta");
	Sig_centzone_vs_eta_Xproj_1->GetYaxis()->SetTitle("N/N_{Total}");
	Sig_centzone_vs_eta_Xproj_1->SetLineColor(kBlue);
	Sig_centzone_vs_eta_Xproj_1->SetLineWidth(2);
	Bkg_centzone_vs_eta_Xproj_1->SetLineColor(kRed);
	Bkg_centzone_vs_eta_Xproj_1->SetLineWidth(2);
	Other_centzone_vs_eta_Xproj_1->SetLineColor(kCyan);
	Other_centzone_vs_eta_Xproj_1->SetLineWidth(2);
	Sig_centzone_vs_eta_Xproj_2->SetTitle("#eta with centrality #in ]20, 40] %");
	Sig_centzone_vs_eta_Xproj_2->GetXaxis()->SetTitle("#eta");
	Sig_centzone_vs_eta_Xproj_2->GetYaxis()->SetTitle("N/N_{Total}");
	Sig_centzone_vs_eta_Xproj_2->SetLineColor(kBlue);
	Sig_centzone_vs_eta_Xproj_2->SetLineWidth(2);
	Bkg_centzone_vs_eta_Xproj_2->SetLineColor(kRed);
	Bkg_centzone_vs_eta_Xproj_2->SetLineWidth(2);
	Other_centzone_vs_eta_Xproj_2->SetLineColor(kCyan);
	Other_centzone_vs_eta_Xproj_2->SetLineWidth(2);
	Sig_centzone_vs_eta_Xproj_3->SetTitle("#eta with centrality #in ]40, 60] %");
	Sig_centzone_vs_eta_Xproj_3->GetXaxis()->SetTitle("#eta");
	Sig_centzone_vs_eta_Xproj_3->GetYaxis()->SetTitle("N/N_{Total}");
	Sig_centzone_vs_eta_Xproj_3->SetLineColor(kBlue);
	Sig_centzone_vs_eta_Xproj_3->SetLineWidth(2);
	Bkg_centzone_vs_eta_Xproj_3->SetLineColor(kRed);
	Bkg_centzone_vs_eta_Xproj_3->SetLineWidth(2);
	Other_centzone_vs_eta_Xproj_3->SetLineColor(kCyan);
	Other_centzone_vs_eta_Xproj_3->SetLineWidth(2);
	Sig_centzone_vs_eta_Xproj_4->SetTitle("#eta with centrality #in ]60, 80] %");
	Sig_centzone_vs_eta_Xproj_4->GetXaxis()->SetTitle("#eta");
	Sig_centzone_vs_eta_Xproj_4->GetYaxis()->SetTitle("N/N_{Total}");
	Sig_centzone_vs_eta_Xproj_4->SetLineColor(kBlue);
	Sig_centzone_vs_eta_Xproj_4->SetLineWidth(2);
	Bkg_centzone_vs_eta_Xproj_4->SetLineColor(kRed);
	Bkg_centzone_vs_eta_Xproj_4->SetLineWidth(2);
	Other_centzone_vs_eta_Xproj_4->SetLineColor(kCyan);
	Other_centzone_vs_eta_Xproj_4->SetLineWidth(2);
	Sig_centzone_vs_eta_Xproj_5->SetTitle("#eta with centrality #in ]80, 90] ");
	Sig_centzone_vs_eta_Xproj_5->GetXaxis()->SetTitle("#eta");
	Sig_centzone_vs_eta_Xproj_5->GetYaxis()->SetTitle("N/N_{Total}");
	Sig_centzone_vs_eta_Xproj_5->SetLineColor(kBlue);
	Sig_centzone_vs_eta_Xproj_5->SetLineWidth(2);
	Bkg_centzone_vs_eta_Xproj_5->SetLineColor(kRed);
	Bkg_centzone_vs_eta_Xproj_5->SetLineWidth(2);
	Other_centzone_vs_eta_Xproj_5->SetLineColor(kCyan);
	Other_centzone_vs_eta_Xproj_5->SetLineWidth(2);

// Write to output file

	histSampleSig_pt->Write();
	histSampleOther_pt->Write();
	histSampleBkg_pt->Write();
	histSampleSig_eta->Write();
	histSampleOther_eta->Write();
	histSampleBkg_eta->Write();
	histSampleSig_abseta->Write();
	histSampleOther_abseta->Write();
	histSampleBkg_abseta->Write();
	histSampleSig_phi->Write();
	histSampleOther_phi->Write();
	histSampleBkg_phi->Write();
	histSampleSig_centzone->Write();
	histSampleOther_centzone->Write();
	histSampleBkg_centzone->Write();

	Sig_pt_vs_centzone_Yproj_1->Write();
	Sig_pt_vs_centzone_Yproj_2->Write();
	Sig_pt_vs_centzone_Yproj_3->Write();
	Sig_pt_vs_centzone_Yproj_4->Write();
	Sig_pt_vs_centzone_Yproj_5->Write();
	Sig_pt_vs_centzone_Yproj_6->Write();
	Sig_pt_vs_centzone_Yproj_7->Write();
	Bkg_pt_vs_centzone_Yproj_1->Write();
	Bkg_pt_vs_centzone_Yproj_2->Write();
	Bkg_pt_vs_centzone_Yproj_3->Write();
	Bkg_pt_vs_centzone_Yproj_4->Write();
	Bkg_pt_vs_centzone_Yproj_5->Write();
	Bkg_pt_vs_centzone_Yproj_6->Write();
	Bkg_pt_vs_centzone_Yproj_7->Write();
	Other_pt_vs_centzone_Yproj_1->Write();
	Other_pt_vs_centzone_Yproj_2->Write();
	Other_pt_vs_centzone_Yproj_3->Write();
	Other_pt_vs_centzone_Yproj_4->Write();
	Other_pt_vs_centzone_Yproj_5->Write();
	Other_pt_vs_centzone_Yproj_6->Write();
	Other_pt_vs_centzone_Yproj_7->Write();

	Sig_pt_vs_eta_Yproj_1->Write();
	Sig_pt_vs_eta_Yproj_2->Write();
	Sig_pt_vs_eta_Yproj_3->Write();
	Sig_pt_vs_eta_Yproj_4->Write();
	Sig_pt_vs_eta_Yproj_5->Write();
	Sig_pt_vs_eta_Yproj_6->Write();
	Bkg_pt_vs_eta_Yproj_1->Write();
	Bkg_pt_vs_eta_Yproj_2->Write();
	Bkg_pt_vs_eta_Yproj_3->Write();
	Bkg_pt_vs_eta_Yproj_4->Write();
	Bkg_pt_vs_eta_Yproj_5->Write();
	Bkg_pt_vs_eta_Yproj_6->Write();
	Other_pt_vs_eta_Yproj_1->Write();
	Other_pt_vs_eta_Yproj_2->Write();
	Other_pt_vs_eta_Yproj_3->Write();
	Other_pt_vs_eta_Yproj_4->Write();
	Other_pt_vs_eta_Yproj_5->Write();
	Other_pt_vs_eta_Yproj_6->Write();

	Sig_pt_vs_phi_Yproj_1->Write();
	Sig_pt_vs_phi_Yproj_2->Write();
	Sig_pt_vs_phi_Yproj_3->Write();
	Sig_pt_vs_phi_Yproj_4->Write();
	Sig_pt_vs_phi_Yproj_5->Write();
	Sig_pt_vs_phi_Yproj_6->Write();
	Bkg_pt_vs_phi_Yproj_1->Write();
	Bkg_pt_vs_phi_Yproj_2->Write();
	Bkg_pt_vs_phi_Yproj_3->Write();
	Bkg_pt_vs_phi_Yproj_4->Write();
	Bkg_pt_vs_phi_Yproj_5->Write();
	Bkg_pt_vs_phi_Yproj_6->Write();
	Other_pt_vs_phi_Yproj_1->Write();
	Other_pt_vs_phi_Yproj_2->Write();
	Other_pt_vs_phi_Yproj_3->Write();
	Other_pt_vs_phi_Yproj_4->Write();
	Other_pt_vs_phi_Yproj_5->Write();
	Other_pt_vs_phi_Yproj_6->Write();

	Sig_phi_vs_centzone_Yproj_1->Write();
	Sig_phi_vs_centzone_Yproj_2->Write();
	Sig_phi_vs_centzone_Yproj_3->Write();
	Sig_phi_vs_centzone_Yproj_4->Write();
	Sig_phi_vs_centzone_Yproj_5->Write();
	Bkg_phi_vs_centzone_Yproj_1->Write();
	Bkg_phi_vs_centzone_Yproj_2->Write();
	Bkg_phi_vs_centzone_Yproj_3->Write();
	Bkg_phi_vs_centzone_Yproj_4->Write();
	Bkg_phi_vs_centzone_Yproj_5->Write();
	Other_phi_vs_centzone_Yproj_1->Write();
	Other_phi_vs_centzone_Yproj_2->Write();
	Other_phi_vs_centzone_Yproj_3->Write();
	Other_phi_vs_centzone_Yproj_4->Write();
	Other_phi_vs_centzone_Yproj_5->Write();

	Sig_centzone_vs_eta_Xproj_1->Write();
	Sig_centzone_vs_eta_Xproj_2->Write();
	Sig_centzone_vs_eta_Xproj_3->Write();
	Sig_centzone_vs_eta_Xproj_4->Write();
	Sig_centzone_vs_eta_Xproj_5->Write();
	Bkg_centzone_vs_eta_Xproj_1->Write();
	Bkg_centzone_vs_eta_Xproj_2->Write();
	Bkg_centzone_vs_eta_Xproj_3->Write();
	Bkg_centzone_vs_eta_Xproj_4->Write();
	Bkg_centzone_vs_eta_Xproj_5->Write();
	Other_centzone_vs_eta_Xproj_1->Write();
	Other_centzone_vs_eta_Xproj_2->Write();
	Other_centzone_vs_eta_Xproj_3->Write();
	Other_centzone_vs_eta_Xproj_4->Write();
	Other_centzone_vs_eta_Xproj_5->Write();

// Normalization to 1

	histSampleBkg_pt->Scale(1./histSampleBkg_pt->Integral());
	histSampleSig_pt->Scale(1./histSampleSig_pt->Integral());
	histSampleOther_pt->Scale(1./histSampleOther_pt->Integral());
	histSampleBkg_eta->Scale(1./histSampleBkg_eta->Integral());
	histSampleSig_eta->Scale(1./histSampleSig_eta->Integral());
	histSampleOther_eta->Scale(1./histSampleOther_eta->Integral());
	histSampleBkg_abseta->Scale(1./histSampleBkg_abseta->Integral());
	histSampleSig_abseta->Scale(1./histSampleSig_abseta->Integral());
	histSampleOther_abseta->Scale(1./histSampleOther_abseta->Integral());
	histSampleBkg_phi->Scale(1./histSampleBkg_phi->Integral());
	histSampleSig_phi->Scale(1./histSampleSig_phi->Integral());
	histSampleOther_phi->Scale(1./histSampleOther_phi->Integral());
	if (!pp_flag) {
		histSampleBkg_centzone->Scale(1./histSampleBkg_centzone->Integral());
		histSampleSig_centzone->Scale(1./histSampleSig_centzone->Integral());
		histSampleOther_centzone->Scale(1./histSampleOther_centzone->Integral());

		Bkg_pt_vs_centzone_Yproj_1->Scale(1./Bkg_pt_vs_centzone_Yproj_1->Integral());
		Sig_pt_vs_centzone_Yproj_1->Scale(1./Sig_pt_vs_centzone_Yproj_1->Integral());
		Other_pt_vs_centzone_Yproj_1->Scale(1./Other_pt_vs_centzone_Yproj_1->Integral());
		Bkg_pt_vs_centzone_Yproj_2->Scale(1./Bkg_pt_vs_centzone_Yproj_2->Integral());
		Sig_pt_vs_centzone_Yproj_2->Scale(1./Sig_pt_vs_centzone_Yproj_2->Integral());
		Other_pt_vs_centzone_Yproj_2->Scale(1./Other_pt_vs_centzone_Yproj_2->Integral());
		Bkg_pt_vs_centzone_Yproj_3->Scale(1./Bkg_pt_vs_centzone_Yproj_3->Integral());
		Sig_pt_vs_centzone_Yproj_3->Scale(1./Sig_pt_vs_centzone_Yproj_3->Integral());
		Other_pt_vs_centzone_Yproj_3->Scale(1./Other_pt_vs_centzone_Yproj_3->Integral());
		Bkg_pt_vs_centzone_Yproj_4->Scale(1./Bkg_pt_vs_centzone_Yproj_4->Integral());
		Sig_pt_vs_centzone_Yproj_4->Scale(1./Sig_pt_vs_centzone_Yproj_4->Integral());
		Other_pt_vs_centzone_Yproj_4->Scale(1./Other_pt_vs_centzone_Yproj_4->Integral());
		Bkg_pt_vs_centzone_Yproj_5->Scale(1./Bkg_pt_vs_centzone_Yproj_5->Integral());
		Sig_pt_vs_centzone_Yproj_5->Scale(1./Sig_pt_vs_centzone_Yproj_5->Integral());
		Other_pt_vs_centzone_Yproj_5->Scale(1./Other_pt_vs_centzone_Yproj_5->Integral());
		Bkg_pt_vs_centzone_Yproj_6->Scale(1./Bkg_pt_vs_centzone_Yproj_6->Integral());
		Sig_pt_vs_centzone_Yproj_6->Scale(1./Sig_pt_vs_centzone_Yproj_6->Integral());
		Other_pt_vs_centzone_Yproj_6->Scale(1./Other_pt_vs_centzone_Yproj_6->Integral());
		Bkg_pt_vs_centzone_Yproj_7->Scale(1./Bkg_pt_vs_centzone_Yproj_7->Integral());
		Sig_pt_vs_centzone_Yproj_7->Scale(1./Sig_pt_vs_centzone_Yproj_7->Integral());
		Other_pt_vs_centzone_Yproj_7->Scale(1./Other_pt_vs_centzone_Yproj_7->Integral());
	}

	Bkg_pt_vs_eta_Yproj_1->Scale(1./Bkg_pt_vs_eta_Yproj_1->Integral());
	Sig_pt_vs_eta_Yproj_1->Scale(1./Sig_pt_vs_eta_Yproj_1->Integral());
	Other_pt_vs_eta_Yproj_1->Scale(1./Other_pt_vs_eta_Yproj_1->Integral());
	Bkg_pt_vs_eta_Yproj_2->Scale(1./Bkg_pt_vs_eta_Yproj_2->Integral());
	Sig_pt_vs_eta_Yproj_2->Scale(1./Sig_pt_vs_eta_Yproj_2->Integral());
	Other_pt_vs_eta_Yproj_2->Scale(1./Other_pt_vs_eta_Yproj_2->Integral());
	Bkg_pt_vs_eta_Yproj_3->Scale(1./Bkg_pt_vs_eta_Yproj_3->Integral());
	Sig_pt_vs_eta_Yproj_3->Scale(1./Sig_pt_vs_eta_Yproj_3->Integral());
	Other_pt_vs_eta_Yproj_3->Scale(1./Other_pt_vs_eta_Yproj_3->Integral());
	Bkg_pt_vs_eta_Yproj_4->Scale(1./Bkg_pt_vs_eta_Yproj_4->Integral());
	Sig_pt_vs_eta_Yproj_4->Scale(1./Sig_pt_vs_eta_Yproj_4->Integral());
	Other_pt_vs_eta_Yproj_4->Scale(1./Other_pt_vs_eta_Yproj_4->Integral());
	Bkg_pt_vs_eta_Yproj_5->Scale(1./Bkg_pt_vs_eta_Yproj_5->Integral());
	Sig_pt_vs_eta_Yproj_5->Scale(1./Sig_pt_vs_eta_Yproj_5->Integral());
	Other_pt_vs_eta_Yproj_5->Scale(1./Other_pt_vs_eta_Yproj_5->Integral());
	Bkg_pt_vs_eta_Yproj_6->Scale(1./Bkg_pt_vs_eta_Yproj_6->Integral());
	Sig_pt_vs_eta_Yproj_6->Scale(1./Sig_pt_vs_eta_Yproj_6->Integral());
	Other_pt_vs_eta_Yproj_6->Scale(1./Other_pt_vs_eta_Yproj_6->Integral());

	Bkg_pt_vs_phi_Yproj_1->Scale(1./Bkg_pt_vs_phi_Yproj_1->Integral());
	Sig_pt_vs_phi_Yproj_1->Scale(1./Sig_pt_vs_phi_Yproj_1->Integral());
	Other_pt_vs_phi_Yproj_1->Scale(1./Other_pt_vs_phi_Yproj_1->Integral());
	Bkg_pt_vs_phi_Yproj_2->Scale(1./Bkg_pt_vs_phi_Yproj_2->Integral());
	Sig_pt_vs_phi_Yproj_2->Scale(1./Sig_pt_vs_phi_Yproj_2->Integral());
	Other_pt_vs_phi_Yproj_2->Scale(1./Other_pt_vs_phi_Yproj_2->Integral());
	Bkg_pt_vs_phi_Yproj_3->Scale(1./Bkg_pt_vs_phi_Yproj_3->Integral());
	Sig_pt_vs_phi_Yproj_3->Scale(1./Sig_pt_vs_phi_Yproj_3->Integral());
	Other_pt_vs_phi_Yproj_3->Scale(1./Other_pt_vs_phi_Yproj_3->Integral());
	Bkg_pt_vs_phi_Yproj_4->Scale(1./Bkg_pt_vs_phi_Yproj_4->Integral());
	Sig_pt_vs_phi_Yproj_4->Scale(1./Sig_pt_vs_phi_Yproj_4->Integral());
	Other_pt_vs_phi_Yproj_4->Scale(1./Other_pt_vs_phi_Yproj_4->Integral());
	Bkg_pt_vs_phi_Yproj_5->Scale(1./Bkg_pt_vs_phi_Yproj_5->Integral());
	Sig_pt_vs_phi_Yproj_5->Scale(1./Sig_pt_vs_phi_Yproj_5->Integral());
	Other_pt_vs_phi_Yproj_5->Scale(1./Other_pt_vs_phi_Yproj_5->Integral());
	Bkg_pt_vs_phi_Yproj_6->Scale(1./Bkg_pt_vs_phi_Yproj_6->Integral());
	Sig_pt_vs_phi_Yproj_6->Scale(1./Sig_pt_vs_phi_Yproj_6->Integral());
	Other_pt_vs_phi_Yproj_6->Scale(1./Other_pt_vs_phi_Yproj_6->Integral());

	if (!pp_flag) {
		Bkg_phi_vs_centzone_Yproj_1->Scale(1./Bkg_phi_vs_centzone_Yproj_1->Integral());
		Sig_phi_vs_centzone_Yproj_1->Scale(1./Sig_phi_vs_centzone_Yproj_1->Integral());
		Other_phi_vs_centzone_Yproj_1->Scale(1./Other_phi_vs_centzone_Yproj_1->Integral());
		Bkg_phi_vs_centzone_Yproj_2->Scale(1./Bkg_phi_vs_centzone_Yproj_2->Integral());
		Sig_phi_vs_centzone_Yproj_2->Scale(1./Sig_phi_vs_centzone_Yproj_2->Integral());
		Other_phi_vs_centzone_Yproj_2->Scale(1./Other_phi_vs_centzone_Yproj_2->Integral());
		Bkg_phi_vs_centzone_Yproj_3->Scale(1./Bkg_phi_vs_centzone_Yproj_3->Integral());
		Sig_phi_vs_centzone_Yproj_3->Scale(1./Sig_phi_vs_centzone_Yproj_3->Integral());
		Other_phi_vs_centzone_Yproj_3->Scale(1./Other_phi_vs_centzone_Yproj_3->Integral());
		Bkg_phi_vs_centzone_Yproj_4->Scale(1./Bkg_phi_vs_centzone_Yproj_4->Integral());
		Sig_phi_vs_centzone_Yproj_4->Scale(1./Sig_phi_vs_centzone_Yproj_4->Integral());
		Other_phi_vs_centzone_Yproj_4->Scale(1./Other_phi_vs_centzone_Yproj_4->Integral());
		Bkg_phi_vs_centzone_Yproj_5->Scale(1./Bkg_phi_vs_centzone_Yproj_5->Integral());
		Sig_phi_vs_centzone_Yproj_5->Scale(1./Sig_phi_vs_centzone_Yproj_5->Integral());
		Other_phi_vs_centzone_Yproj_5->Scale(1./Other_phi_vs_centzone_Yproj_5->Integral());

		Bkg_centzone_vs_eta_Xproj_1->Scale(1./Bkg_centzone_vs_eta_Xproj_1->Integral());
		Sig_centzone_vs_eta_Xproj_1->Scale(1./Sig_centzone_vs_eta_Xproj_1->Integral());
		Other_centzone_vs_eta_Xproj_1->Scale(1./Other_centzone_vs_eta_Xproj_1->Integral());
		Bkg_centzone_vs_eta_Xproj_2->Scale(1./Bkg_centzone_vs_eta_Xproj_2->Integral());
		Sig_centzone_vs_eta_Xproj_2->Scale(1./Sig_centzone_vs_eta_Xproj_2->Integral());
		Other_centzone_vs_eta_Xproj_2->Scale(1./Other_centzone_vs_eta_Xproj_2->Integral());
		Bkg_centzone_vs_eta_Xproj_3->Scale(1./Bkg_centzone_vs_eta_Xproj_3->Integral());
		Sig_centzone_vs_eta_Xproj_3->Scale(1./Sig_centzone_vs_eta_Xproj_3->Integral());
		Other_centzone_vs_eta_Xproj_3->Scale(1./Other_centzone_vs_eta_Xproj_3->Integral());
		Bkg_centzone_vs_eta_Xproj_4->Scale(1./Bkg_centzone_vs_eta_Xproj_4->Integral());
		Sig_centzone_vs_eta_Xproj_4->Scale(1./Sig_centzone_vs_eta_Xproj_4->Integral());
		Other_centzone_vs_eta_Xproj_4->Scale(1./Other_centzone_vs_eta_Xproj_4->Integral());
		Bkg_centzone_vs_eta_Xproj_5->Scale(1./Bkg_centzone_vs_eta_Xproj_5->Integral());
		Sig_centzone_vs_eta_Xproj_5->Scale(1./Sig_centzone_vs_eta_Xproj_5->Integral());
		Other_centzone_vs_eta_Xproj_5->Scale(1./Other_centzone_vs_eta_Xproj_5->Integral());
	}

// Draw, Legend

	histSampleBkg_pt->Draw();
	histSampleOther_pt->Draw("same");
	histSampleSig_pt->Draw("same");

	leg->Clear();
	leg->AddEntry(histSampleSig_pt,   "Bottom Jets", "l");
	leg->AddEntry(histSampleBkg_pt,   "Light Jets",  "l");
	leg->AddEntry(histSampleOther_pt, "Charm Jets",  "l");
	leg->Draw();
	
	c1->SetLogy(1);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/sample_pt.png");

	histSampleSig_eta->Draw();
	histSampleOther_eta->Draw("same");
	histSampleBkg_eta->Draw("same");

	leg->Draw();

	c1->SetLogy(0);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/sample_eta.png");

	histSampleSig_abseta->Draw();
	histSampleOther_abseta->Draw("same");
	histSampleBkg_abseta->Draw("same");

	leg->Draw();

	c1->SetLogy(0);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/sample_abseta.png");

	histSampleOther_phi->Draw();
	histSampleBkg_phi->Draw("same");
	histSampleSig_phi->Draw("same");

	leg->Draw();

	c1->SetLogy(0);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/sample_phi.png");

	if (!pp_flag) {
		histSampleBkg_centzone->Draw();
		histSampleOther_centzone->Draw("same");
		histSampleSig_centzone->Draw("same");

		leg->Draw();

		c1->SetLogy(0);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/sample_centzone.png");
	}

	// variable vs. variable
	if (!pp_flag) {
		Bkg_pt_vs_centzone_Yproj_1->Draw();
		Sig_pt_vs_centzone_Yproj_1->Draw("same");
		Other_pt_vs_centzone_Yproj_1->Draw("same");

		leg->Draw();

		c1->SetLogy(1);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/pt_vs_centzone_y1.png");

		Bkg_pt_vs_centzone_Yproj_2->Draw();
		Sig_pt_vs_centzone_Yproj_2->Draw("same");
		Other_pt_vs_centzone_Yproj_2->Draw("same");

		leg->Draw();

		c1->SetLogy(1);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/pt_vs_centzone_y2.png");

		Bkg_pt_vs_centzone_Yproj_3->Draw();
		Sig_pt_vs_centzone_Yproj_3->Draw("same");
		Other_pt_vs_centzone_Yproj_3->Draw("same");

		leg->Draw();

		c1->SetLogy(1);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/pt_vs_centzone_y3.png");

		Bkg_pt_vs_centzone_Yproj_4->Draw();
		Sig_pt_vs_centzone_Yproj_4->Draw("same");
		Other_pt_vs_centzone_Yproj_4->Draw("same");

		leg->Draw();

		c1->SetLogy(1);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/pt_vs_centzone_y4.png");

		Bkg_pt_vs_centzone_Yproj_5->Draw();
		Sig_pt_vs_centzone_Yproj_5->Draw("same");
		Other_pt_vs_centzone_Yproj_5->Draw("same");

		leg->Draw();

		c1->SetLogy(1);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/pt_vs_centzone_y5.png");

		Bkg_pt_vs_centzone_Yproj_6->Draw();
		Sig_pt_vs_centzone_Yproj_6->Draw("same");
		Other_pt_vs_centzone_Yproj_6->Draw("same");

		leg->Draw();

		c1->SetLogy(1);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/pt_vs_centzone_y6.png");

		Bkg_pt_vs_centzone_Yproj_7->Draw();
		Sig_pt_vs_centzone_Yproj_7->Draw("same");
		Other_pt_vs_centzone_Yproj_7->Draw("same");

		leg->Draw();

		c1->SetLogy(1);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/pt_vs_centzone_y7.png");
	}

	Bkg_pt_vs_eta_Yproj_1->Draw();
	Sig_pt_vs_eta_Yproj_1->Draw("same");
	Other_pt_vs_eta_Yproj_1->Draw("same");

	leg->Draw();

	c1->SetLogy(1);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/pt_vs_eta_y1.png");

	Bkg_pt_vs_eta_Yproj_2->Draw();
	Sig_pt_vs_eta_Yproj_2->Draw("same");
	Other_pt_vs_eta_Yproj_2->Draw("same");

	leg->Draw();

	c1->SetLogy(1);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/pt_vs_eta_y2.png");

	Bkg_pt_vs_eta_Yproj_3->Draw();
	Sig_pt_vs_eta_Yproj_3->Draw("same");
	Other_pt_vs_eta_Yproj_3->Draw("same");

	leg->Draw();

	c1->SetLogy(1);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/pt_vs_eta_y3.png");

	Bkg_pt_vs_eta_Yproj_4->Draw();
	Sig_pt_vs_eta_Yproj_4->Draw("same");
	Other_pt_vs_eta_Yproj_4->Draw("same");

	leg->Draw();

	c1->SetLogy(1);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/pt_vs_eta_y4.png");

	Bkg_pt_vs_eta_Yproj_5->Draw();
	Sig_pt_vs_eta_Yproj_5->Draw("same");
	Other_pt_vs_eta_Yproj_5->Draw("same");

	leg->Draw();

	c1->SetLogy(1);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/pt_vs_eta_y5.png");

	Bkg_pt_vs_eta_Yproj_6->Draw();
	Sig_pt_vs_eta_Yproj_6->Draw("same");
	Other_pt_vs_eta_Yproj_6->Draw("same");

	leg->Draw();

	c1->SetLogy(1);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/pt_vs_eta_y6.png");

	// Bkg_pt_vs_phi_Yproj_1->Draw();
	// Sig_pt_vs_phi_Yproj_1->Draw("same");
	// Other_pt_vs_phi_Yproj_1->Draw("same");

	// leg->Draw();

	// c1->SetLogy(1);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/pt_vs_phi_y1.png");

	// Bkg_pt_vs_phi_Yproj_2->Draw();
	// Sig_pt_vs_phi_Yproj_2->Draw("same");
	// Other_pt_vs_phi_Yproj_2->Draw("same");

	// leg->Draw();

	// c1->SetLogy(1);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/pt_vs_phi_y2.png");

	// Bkg_pt_vs_phi_Yproj_3->Draw();
	// Sig_pt_vs_phi_Yproj_3->Draw("same");
	// Other_pt_vs_phi_Yproj_3->Draw("same");

	// leg->Draw();

	// c1->SetLogy(1);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/pt_vs_phi_y3.png");

	// Bkg_pt_vs_phi_Yproj_4->Draw();
	// Sig_pt_vs_phi_Yproj_4->Draw("same");
	// Other_pt_vs_phi_Yproj_4->Draw("same");

	// leg->Draw();

	// c1->SetLogy(1);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/pt_vs_phi_y4.png");

	// Bkg_pt_vs_phi_Yproj_5->Draw();
	// Sig_pt_vs_phi_Yproj_5->Draw("same");
	// Other_pt_vs_phi_Yproj_5->Draw("same");

	// leg->Draw();

	// c1->SetLogy(1);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/pt_vs_phi_y5.png");

	// Bkg_pt_vs_phi_Yproj_6->Draw();
	// Sig_pt_vs_phi_Yproj_6->Draw("same");
	// Other_pt_vs_phi_Yproj_6->Draw("same");

	// leg->Draw();

	// c1->SetLogy(1);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/pt_vs_phi_y6.png");

	// if (!pp_flag) {
	// 	Sig_phi_vs_centzone_Yproj_1->Draw();
	// 	Bkg_phi_vs_centzone_Yproj_1->Draw("same");
	// 	Other_phi_vs_centzone_Yproj_1->Draw("same");

	// 	leg->Draw();

	// 	c1->SetLogy(0);
	// 	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// 	c1->Print("plots/phi_vs_centzone_y1.png");

	// 	Sig_phi_vs_centzone_Yproj_2->Draw();
	// 	Bkg_phi_vs_centzone_Yproj_2->Draw("same");
	// 	Other_phi_vs_centzone_Yproj_2->Draw("same");

	// 	leg->Draw();

	// 	c1->SetLogy(0);
	// 	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// 	c1->Print("plots/phi_vs_centzone_y2.png");

	// 	Sig_phi_vs_centzone_Yproj_3->Draw();
	// 	Bkg_phi_vs_centzone_Yproj_3->Draw("same");
	// 	Other_phi_vs_centzone_Yproj_3->Draw("same");

	// 	leg->Draw();

	// 	c1->SetLogy(0);
	// 	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// 	c1->Print("plots/phi_vs_centzone_y3.png");

	// 	Sig_phi_vs_centzone_Yproj_4->Draw();
	// 	Bkg_phi_vs_centzone_Yproj_4->Draw("same");
	// 	Other_phi_vs_centzone_Yproj_4->Draw("same");

	// 	leg->Draw();

	// 	c1->SetLogy(0);
	// 	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// 	c1->Print("plots/phi_vs_centzone_y4.png");

	// 	Sig_phi_vs_centzone_Yproj_5->Draw();
	// 	Bkg_phi_vs_centzone_Yproj_5->Draw("same");
	// 	Other_phi_vs_centzone_Yproj_5->Draw("same");

	// 	leg->Draw();

	// 	c1->SetLogy(0);
	// 	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// 	c1->Print("plots/phi_vs_centzone_y5.png");
	// }

	if (!pp_flag) {
		Sig_centzone_vs_eta_Xproj_1->Draw();
		Bkg_centzone_vs_eta_Xproj_1->Draw("same");
		Other_centzone_vs_eta_Xproj_1->Draw("same");

		leg->Draw();

		c1->SetLogy(0);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/centzone_vs_eta_x1.png");

		Sig_centzone_vs_eta_Xproj_2->Draw();
		Bkg_centzone_vs_eta_Xproj_2->Draw("same");
		Other_centzone_vs_eta_Xproj_2->Draw("same");

		leg->Draw();

		c1->SetLogy(0);
		Sig_centzone_vs_eta_Xproj_2->SetMinimum(0.);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/centzone_vs_eta_x2.png");

		Sig_centzone_vs_eta_Xproj_3->Draw();
		Bkg_centzone_vs_eta_Xproj_3->Draw("same");
		Other_centzone_vs_eta_Xproj_3->Draw("same");

		leg->Draw();

		c1->SetLogy(0);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/centzone_vs_eta_x3.png");

		Sig_centzone_vs_eta_Xproj_4->Draw();
		Bkg_centzone_vs_eta_Xproj_4->Draw("same");
		Other_centzone_vs_eta_Xproj_4->Draw("same");

		leg->Draw();

		c1->SetLogy(0);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/centzone_vs_eta_x4.png");

		Sig_centzone_vs_eta_Xproj_5->Draw();
		Bkg_centzone_vs_eta_Xproj_5->Draw("same");
		Other_centzone_vs_eta_Xproj_5->Draw("same");

		leg->Draw();

		c1->SetLogy(0);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/centzone_vs_eta_x5.png");
	}

//----RESULT-----------------------------------------------------

	// Get result histograms
	TH1F *MVA_IP2D            = (TH1F*) inputFile->Get("MVA_IP2D");
	TH1F *MVA_IP2D_SIGNAL     = (TH1F*) inputFile->Get("MVA_IP2D_SIGNAL");
	TH1F *MVA_IP2D_Background = (TH1F*) inputFile->Get("MVA_IP2D_Background");
	TH1F *MVA_IP2D_Other      = (TH1F*) inputFile->Get("MVA_IP2D_Other");
	TH1F *MVA_IP3D            = (TH1F*) inputFile->Get("MVA_IP3D");
	TH1F *MVA_IP3D_SIGNAL     = (TH1F*) inputFile->Get("MVA_IP3D_SIGNAL");
	TH1F *MVA_IP3D_Background = (TH1F*) inputFile->Get("MVA_IP3D_Background");
	TH1F *MVA_IP3D_Other      = (TH1F*) inputFile->Get("MVA_IP3D_Other");
	TH1F *MVA_JF              = (TH1F*) inputFile->Get("MVA_JF");
	TH1F *MVA_JF_SIGNAL       = (TH1F*) inputFile->Get("MVA_JF_SIGNAL");
	TH1F *MVA_JF_Background   = (TH1F*) inputFile->Get("MVA_JF_Background");
	TH1F *MVA_JF_Other        = (TH1F*) inputFile->Get("MVA_JF_Other");

	TH1F *MVA_BDT                       = (TH1F*) inputFile->Get("MVA_BDT");
	TH1F *MVA_BDT_SIGNAL                = (TH1F*) inputFile->Get("MVA_BDT_SIGNAL");
	TH1F *MVA_BDT_Background            = (TH1F*) inputFile->Get("MVA_BDT_Background");
	TH1F *MVA_BDT_Other                 = (TH1F*) inputFile->Get("MVA_BDT_Other");
	TH2F *MVA_BDT_pt_vs_eval            = (TH2F*) inputFile->Get("MVA_BDT_pt_vs_eval");
	TH2F *MVA_BDT_abseta_vs_eval        = (TH2F*) inputFile->Get("MVA_BDT_abseta_vs_eval");
	TH2F *MVA_BDT_phi_vs_eval           = (TH2F*) inputFile->Get("MVA_BDT_phi_vs_eval");
	TH2F *MVA_BDTSig_pt_vs_eval         = (TH2F*) inputFile->Get("MVA_BDTSig_pt_vs_eval");
	TH2F *MVA_BDTSig_abseta_vs_eval     = (TH2F*) inputFile->Get("MVA_BDTSig_abseta_vs_eval");
	TH2F *MVA_BDTSig_phi_vs_eval        = (TH2F*) inputFile->Get("MVA_BDTSig_phi_vs_eval");
	TH2F *MVA_BDTBkg_pt_vs_eval         = (TH2F*) inputFile->Get("MVA_BDTBkg_pt_vs_eval");
	TH2F *MVA_BDTBkg_abseta_vs_eval     = (TH2F*) inputFile->Get("MVA_BDTBkg_abseta_vs_eval");
	TH2F *MVA_BDTBkg_phi_vs_eval        = (TH2F*) inputFile->Get("MVA_BDTBkg_phi_vs_eval");
	TH2F *MVA_BDTOther_pt_vs_eval       = (TH2F*) inputFile->Get("MVA_BDTOther_pt_vs_eval");
	TH2F *MVA_BDTOther_abseta_vs_eval   = (TH2F*) inputFile->Get("MVA_BDTOther_abseta_vs_eval");
	TH2F *MVA_BDTOther_phi_vs_eval      = (TH2F*) inputFile->Get("MVA_BDTOther_phi_vs_eval");
	TH2F *MVA_BDT_centzone_vs_eval      = (TH2F*) inputFile->Get("MVA_BDT_centzone_vs_eval");
	TH2F *MVA_BDTSig_centzone_vs_eval   = (TH2F*) inputFile->Get("MVA_BDTSig_centzone_vs_eval");
	TH2F *MVA_BDTBkg_centzone_vs_eval   = (TH2F*) inputFile->Get("MVA_BDTBkg_centzone_vs_eval");
	TH2F *MVA_BDTOther_centzone_vs_eval = (TH2F*) inputFile->Get("MVA_BDTOther_centzone_vs_eval");
	TH2F *MVA_IP2D_pt_vs_eval                  = (TH2F*) inputFile->Get("MVA_IP2D_pt_vs_eval");
	TH2F *MVA_IP2D_abseta_vs_eval              = (TH2F*) inputFile->Get("MVA_IP2D_abseta_vs_eval");
	TH2F *MVA_IP2D_phi_vs_eval                 = (TH2F*) inputFile->Get("MVA_IP2D_phi_vs_eval");
	TH2F *MVA_IP2D_SIGNAL_pt_vs_eval           = (TH2F*) inputFile->Get("MVA_IP2D_SIGNAL_pt_vs_eval");
	TH2F *MVA_IP2D_SIGNAL_abseta_vs_eval       = (TH2F*) inputFile->Get("MVA_IP2D_SIGNAL_abseta_vs_eval");
	TH2F *MVA_IP2D_SIGNAL_phi_vs_eval          = (TH2F*) inputFile->Get("MVA_IP2D_SIGNAL_phi_vs_eval");
	TH2F *MVA_IP2D_Background_pt_vs_eval       = (TH2F*) inputFile->Get("MVA_IP2D_Background_pt_vs_eval");
	TH2F *MVA_IP2D_Background_abseta_vs_eval   = (TH2F*) inputFile->Get("MVA_IP2D_Background_abseta_vs_eval");
	TH2F *MVA_IP2D_Background_phi_vs_eval      = (TH2F*) inputFile->Get("MVA_IP2D_Background_phi_vs_eval");
	TH2F *MVA_IP2D_Other_pt_vs_eval            = (TH2F*) inputFile->Get("MVA_IP2D_Other_pt_vs_eval");
	TH2F *MVA_IP2D_Other_abseta_vs_eval        = (TH2F*) inputFile->Get("MVA_IP2D_Other_abseta_vs_eval");
	TH2F *MVA_IP2D_Other_phi_vs_eval           = (TH2F*) inputFile->Get("MVA_IP2D_Other_phi_vs_eval");
	TH2F *MVA_IP2D_centzone_vs_eval            = (TH2F*) inputFile->Get("MVA_IP2D_centzone_vs_eval");
	TH2F *MVA_IP2D_SIGNAL_centzone_vs_eval     = (TH2F*) inputFile->Get("MVA_IP2D_SIGNAL_centzone_vs_eval");
	TH2F *MVA_IP2D_Background_centzone_vs_eval = (TH2F*) inputFile->Get("MVA_IP2D_Background_centzone_vs_eval");
	TH2F *MVA_IP2D_Other_centzone_vs_eval      = (TH2F*) inputFile->Get("MVA_IP2D_Other_centzone_vs_eval");
	TH2F *MVA_IP3D_pt_vs_eval                  = (TH2F*) inputFile->Get("MVA_IP3D_pt_vs_eval");
	TH2F *MVA_IP3D_abseta_vs_eval              = (TH2F*) inputFile->Get("MVA_IP3D_abseta_vs_eval");
	TH2F *MVA_IP3D_phi_vs_eval                 = (TH2F*) inputFile->Get("MVA_IP3D_phi_vs_eval");
	TH2F *MVA_IP3D_SIGNAL_pt_vs_eval           = (TH2F*) inputFile->Get("MVA_IP3D_SIGNAL_pt_vs_eval");
	TH2F *MVA_IP3D_SIGNAL_abseta_vs_eval       = (TH2F*) inputFile->Get("MVA_IP3D_SIGNAL_abseta_vs_eval");
	TH2F *MVA_IP3D_SIGNAL_phi_vs_eval          = (TH2F*) inputFile->Get("MVA_IP3D_SIGNAL_phi_vs_eval");
	TH2F *MVA_IP3D_Background_pt_vs_eval       = (TH2F*) inputFile->Get("MVA_IP3D_Background_pt_vs_eval");
	TH2F *MVA_IP3D_Background_abseta_vs_eval   = (TH2F*) inputFile->Get("MVA_IP3D_Background_abseta_vs_eval");
	TH2F *MVA_IP3D_Background_phi_vs_eval      = (TH2F*) inputFile->Get("MVA_IP3D_Background_phi_vs_eval");
	TH2F *MVA_IP3D_Other_pt_vs_eval            = (TH2F*) inputFile->Get("MVA_IP3D_Other_pt_vs_eval");
	TH2F *MVA_IP3D_Other_abseta_vs_eval        = (TH2F*) inputFile->Get("MVA_IP3D_Other_abseta_vs_eval");
	TH2F *MVA_IP3D_Other_phi_vs_eval           = (TH2F*) inputFile->Get("MVA_IP3D_Other_phi_vs_eval");
	TH2F *MVA_IP3D_centzone_vs_eval            = (TH2F*) inputFile->Get("MVA_IP3D_centzone_vs_eval");
	TH2F *MVA_IP3D_SIGNAL_centzone_vs_eval     = (TH2F*) inputFile->Get("MVA_IP3D_SIGNAL_centzone_vs_eval");
	TH2F *MVA_IP3D_Background_centzone_vs_eval = (TH2F*) inputFile->Get("MVA_IP3D_Background_centzone_vs_eval");
	TH2F *MVA_IP3D_Other_centzone_vs_eval      = (TH2F*) inputFile->Get("MVA_IP3D_Other_centzone_vs_eval");
	TH2F *MVA_JF_pt_vs_eval                  = (TH2F*) inputFile->Get("MVA_JF_pt_vs_eval");
	TH2F *MVA_JF_abseta_vs_eval              = (TH2F*) inputFile->Get("MVA_JF_abseta_vs_eval");
	TH2F *MVA_JF_phi_vs_eval                 = (TH2F*) inputFile->Get("MVA_JF_phi_vs_eval");
	TH2F *MVA_JF_SIGNAL_pt_vs_eval           = (TH2F*) inputFile->Get("MVA_JF_SIGNAL_pt_vs_eval");
	TH2F *MVA_JF_SIGNAL_abseta_vs_eval       = (TH2F*) inputFile->Get("MVA_JF_SIGNAL_abseta_vs_eval");
	TH2F *MVA_JF_SIGNAL_phi_vs_eval          = (TH2F*) inputFile->Get("MVA_JF_SIGNAL_phi_vs_eval");
	TH2F *MVA_JF_Background_pt_vs_eval       = (TH2F*) inputFile->Get("MVA_JF_Background_pt_vs_eval");
	TH2F *MVA_JF_Background_abseta_vs_eval   = (TH2F*) inputFile->Get("MVA_JF_Background_abseta_vs_eval");
	TH2F *MVA_JF_Background_phi_vs_eval      = (TH2F*) inputFile->Get("MVA_JF_Background_phi_vs_eval");
	TH2F *MVA_JF_Other_pt_vs_eval            = (TH2F*) inputFile->Get("MVA_JF_Other_pt_vs_eval");
	TH2F *MVA_JF_Other_abseta_vs_eval        = (TH2F*) inputFile->Get("MVA_JF_Other_abseta_vs_eval");
	TH2F *MVA_JF_Other_phi_vs_eval           = (TH2F*) inputFile->Get("MVA_JF_Other_phi_vs_eval");
	TH2F *MVA_JF_centzone_vs_eval            = (TH2F*) inputFile->Get("MVA_JF_centzone_vs_eval");
	TH2F *MVA_JF_SIGNAL_centzone_vs_eval     = (TH2F*) inputFile->Get("MVA_JF_SIGNAL_centzone_vs_eval");
	TH2F *MVA_JF_Background_centzone_vs_eval = (TH2F*) inputFile->Get("MVA_JF_Background_centzone_vs_eval");
	TH2F *MVA_JF_Other_centzone_vs_eval      = (TH2F*) inputFile->Get("MVA_JF_Other_centzone_vs_eval");

	TH1F *chosen_pt                      = (TH1F*) inputFile->Get("chosen_pt");
	TH1F *notchosen_pt                   = (TH1F*) inputFile->Get("notchosen_pt");
	TH1F *chosen_pt_vs_centzone_0_20     = (TH1F*) inputFile->Get("chosen_pt_vs_centzone_0_20");
	TH1F *notchosen_pt_vs_centzone_0_20  = (TH1F*) inputFile->Get("notchosen_pt_vs_centzone_0_20");
	TH1F *chosen_pt_vs_centzone_20_40    = (TH1F*) inputFile->Get("chosen_pt_vs_centzone_20_40");
	TH1F *notchosen_pt_vs_centzone_20_40 = (TH1F*) inputFile->Get("notchosen_pt_vs_centzone_20_40");
	TH1F *chosen_pt_vs_centzone_40_80    = (TH1F*) inputFile->Get("chosen_pt_vs_centzone_40_80");
	TH1F *notchosen_pt_vs_centzone_40_80 = (TH1F*) inputFile->Get("notchosen_pt_vs_centzone_40_80");

// TH2F BDT projections

	Int_t lim_pt100, lim_pt120, lim_pt140, lim_pt160, lim_pt180, lim_pt200, lim_pt300, lim_pt400, lim_pt500;
	if (pp_flag) {
		lim_pt100 = 3;
		lim_pt120 = 6;
		lim_pt140 = 10;
		lim_pt160 = 13;
		lim_pt180 = 16;
		lim_pt200 = 19;
		lim_pt300 = 35;
		lim_pt400 = 52;
		lim_pt500 = 68;
	} else {
		lim_pt100 = 16;
		lim_pt120 = 33;
		lim_pt140 = 50;
		lim_pt160 = 67;
		lim_pt180 = 83;
		lim_pt200 = MVA_BDT_pt_vs_eval->GetNbinsX()+1;
		lim_pt300 = lim_pt200;
		lim_pt400 = lim_pt200;
		lim_pt500 = lim_pt200;
	}

	TH1D *MVA_BDT_pt_eval_Xproj_0 = MVA_BDT_pt_vs_eval->ProjectionX("MVA_BDT_pt_eval_Xproj_0");
	TH1D *MVA_BDT_pt_eval_Xproj_1 = MVA_BDT_pt_vs_eval->ProjectionX("MVA_BDT_pt_eval_Xproj_1", lim_pt100, lim_pt120);
	TH1D *MVA_BDT_pt_eval_Xproj_2 = MVA_BDT_pt_vs_eval->ProjectionX("MVA_BDT_pt_eval_Xproj_2", lim_pt120, lim_pt140);
	TH1D *MVA_BDT_pt_eval_Xproj_3 = MVA_BDT_pt_vs_eval->ProjectionX("MVA_BDT_pt_eval_Xproj_3", lim_pt140, lim_pt160);
	TH1D *MVA_BDT_pt_eval_Xproj_4 = MVA_BDT_pt_vs_eval->ProjectionX("MVA_BDT_pt_eval_Xproj_4", lim_pt160, lim_pt180);
	TH1D *MVA_BDT_pt_eval_Xproj_5 = MVA_BDT_pt_vs_eval->ProjectionX("MVA_BDT_pt_eval_Xproj_5", lim_pt180, lim_pt200);
	TH1D *MVA_BDT_pt_eval_Xproj_6 = MVA_BDT_pt_vs_eval->ProjectionX("MVA_BDT_pt_eval_Xproj_6", lim_pt200, lim_pt300);
	TH1D *MVA_BDT_pt_eval_Xproj_7 = MVA_BDT_pt_vs_eval->ProjectionX("MVA_BDT_pt_eval_Xproj_7", lim_pt300, lim_pt400);
	TH1D *MVA_BDT_pt_eval_Xproj_8 = MVA_BDT_pt_vs_eval->ProjectionX("MVA_BDT_pt_eval_Xproj_8", lim_pt400, lim_pt500);
	TH1D *MVA_BDTSig_pt_eval_Xproj_0 = MVA_BDTSig_pt_vs_eval->ProjectionX("MVA_BDTSig_pt_eval_Xproj_0");
	TH1D *MVA_BDTSig_pt_eval_Xproj_1 = MVA_BDTSig_pt_vs_eval->ProjectionX("MVA_BDTSig_pt_eval_Xproj_1", lim_pt100, lim_pt120);
	TH1D *MVA_BDTSig_pt_eval_Xproj_2 = MVA_BDTSig_pt_vs_eval->ProjectionX("MVA_BDTSig_pt_eval_Xproj_2", lim_pt120, lim_pt140);
	TH1D *MVA_BDTSig_pt_eval_Xproj_3 = MVA_BDTSig_pt_vs_eval->ProjectionX("MVA_BDTSig_pt_eval_Xproj_3", lim_pt140, lim_pt160);
	TH1D *MVA_BDTSig_pt_eval_Xproj_4 = MVA_BDTSig_pt_vs_eval->ProjectionX("MVA_BDTSig_pt_eval_Xproj_4", lim_pt160, lim_pt180);
	TH1D *MVA_BDTSig_pt_eval_Xproj_5 = MVA_BDTSig_pt_vs_eval->ProjectionX("MVA_BDTSig_pt_eval_Xproj_5", lim_pt180, lim_pt200);
	TH1D *MVA_BDTSig_pt_eval_Xproj_6 = MVA_BDTSig_pt_vs_eval->ProjectionX("MVA_BDTSig_pt_eval_Xproj_6", lim_pt200, lim_pt300);
	TH1D *MVA_BDTSig_pt_eval_Xproj_7 = MVA_BDTSig_pt_vs_eval->ProjectionX("MVA_BDTSig_pt_eval_Xproj_7", lim_pt300, lim_pt400);
	TH1D *MVA_BDTSig_pt_eval_Xproj_8 = MVA_BDTSig_pt_vs_eval->ProjectionX("MVA_BDTSig_pt_eval_Xproj_8", lim_pt400, lim_pt500);
	TH1D *MVA_BDTBkg_pt_eval_Xproj_0 = MVA_BDTBkg_pt_vs_eval->ProjectionX("MVA_BDTBkg_pt_eval_Xproj_0");
	TH1D *MVA_BDTBkg_pt_eval_Xproj_1 = MVA_BDTBkg_pt_vs_eval->ProjectionX("MVA_BDTBkg_pt_eval_Xproj_1", lim_pt100, lim_pt120);
	TH1D *MVA_BDTBkg_pt_eval_Xproj_2 = MVA_BDTBkg_pt_vs_eval->ProjectionX("MVA_BDTBkg_pt_eval_Xproj_2", lim_pt120, lim_pt140);
	TH1D *MVA_BDTBkg_pt_eval_Xproj_3 = MVA_BDTBkg_pt_vs_eval->ProjectionX("MVA_BDTBkg_pt_eval_Xproj_3", lim_pt140, lim_pt160);
	TH1D *MVA_BDTBkg_pt_eval_Xproj_4 = MVA_BDTBkg_pt_vs_eval->ProjectionX("MVA_BDTBkg_pt_eval_Xproj_4", lim_pt160, lim_pt180);
	TH1D *MVA_BDTBkg_pt_eval_Xproj_5 = MVA_BDTBkg_pt_vs_eval->ProjectionX("MVA_BDTBkg_pt_eval_Xproj_5", lim_pt180, lim_pt200);
	TH1D *MVA_BDTBkg_pt_eval_Xproj_6 = MVA_BDTBkg_pt_vs_eval->ProjectionX("MVA_BDTBkg_pt_eval_Xproj_6", lim_pt200, lim_pt300);
	TH1D *MVA_BDTBkg_pt_eval_Xproj_7 = MVA_BDTBkg_pt_vs_eval->ProjectionX("MVA_BDTBkg_pt_eval_Xproj_7", lim_pt300, lim_pt400);
	TH1D *MVA_BDTBkg_pt_eval_Xproj_8 = MVA_BDTBkg_pt_vs_eval->ProjectionX("MVA_BDTBkg_pt_eval_Xproj_8", lim_pt400, lim_pt500);
	TH1D *MVA_BDTOther_pt_eval_Xproj_0 = MVA_BDTOther_pt_vs_eval->ProjectionX("MVA_BDTOther_pt_eval_Xproj_0");
	TH1D *MVA_BDTOther_pt_eval_Xproj_1 = MVA_BDTOther_pt_vs_eval->ProjectionX("MVA_BDTOther_pt_eval_Xproj_1", lim_pt100, lim_pt120);
	TH1D *MVA_BDTOther_pt_eval_Xproj_2 = MVA_BDTOther_pt_vs_eval->ProjectionX("MVA_BDTOther_pt_eval_Xproj_2", lim_pt120, lim_pt140);
	TH1D *MVA_BDTOther_pt_eval_Xproj_3 = MVA_BDTOther_pt_vs_eval->ProjectionX("MVA_BDTOther_pt_eval_Xproj_3", lim_pt140, lim_pt160);
	TH1D *MVA_BDTOther_pt_eval_Xproj_4 = MVA_BDTOther_pt_vs_eval->ProjectionX("MVA_BDTOther_pt_eval_Xproj_4", lim_pt160, lim_pt180);
	TH1D *MVA_BDTOther_pt_eval_Xproj_5 = MVA_BDTOther_pt_vs_eval->ProjectionX("MVA_BDTOther_pt_eval_Xproj_5", lim_pt180, lim_pt200);
	TH1D *MVA_BDTOther_pt_eval_Xproj_6 = MVA_BDTOther_pt_vs_eval->ProjectionX("MVA_BDTOther_pt_eval_Xproj_6", lim_pt200, lim_pt300);
	TH1D *MVA_BDTOther_pt_eval_Xproj_7 = MVA_BDTOther_pt_vs_eval->ProjectionX("MVA_BDTOther_pt_eval_Xproj_7", lim_pt300, lim_pt400);
	TH1D *MVA_BDTOther_pt_eval_Xproj_8 = MVA_BDTOther_pt_vs_eval->ProjectionX("MVA_BDTOther_pt_eval_Xproj_8", lim_pt400, lim_pt500);

	TH1D *MVA_BDT_abseta_eval_Xproj_0 = MVA_BDT_abseta_vs_eval->ProjectionX("MVA_BDT_abseta_eval_Xproj_0");
	TH1D *MVA_BDT_abseta_eval_Xproj_1 = MVA_BDT_abseta_vs_eval->ProjectionX("MVA_BDT_abseta_eval_Xproj_1", 0, 10);
	TH1D *MVA_BDT_abseta_eval_Xproj_2 = MVA_BDT_abseta_vs_eval->ProjectionX("MVA_BDT_abseta_eval_Xproj_2", 11, 20);
	TH1D *MVA_BDT_abseta_eval_Xproj_3 = MVA_BDT_abseta_vs_eval->ProjectionX("MVA_BDT_abseta_eval_Xproj_3", 21, MVA_BDT_abseta_vs_eval->GetNbinsX()+1);
	TH1D *MVA_BDTSig_abseta_eval_Xproj_0 = MVA_BDTSig_abseta_vs_eval->ProjectionX("MVA_BDTSig_abseta_eval_Xproj_0");
	TH1D *MVA_BDTSig_abseta_eval_Xproj_1 = MVA_BDTSig_abseta_vs_eval->ProjectionX("MVA_BDTSig_abseta_eval_Xproj_1", 0, 10);
	TH1D *MVA_BDTSig_abseta_eval_Xproj_2 = MVA_BDTSig_abseta_vs_eval->ProjectionX("MVA_BDTSig_abseta_eval_Xproj_2", 11, 20);
	TH1D *MVA_BDTSig_abseta_eval_Xproj_3 = MVA_BDTSig_abseta_vs_eval->ProjectionX("MVA_BDTSig_abseta_eval_Xproj_3", 21, MVA_BDTSig_abseta_vs_eval->GetNbinsX()+1);
	TH1D *MVA_BDTBkg_abseta_eval_Xproj_0 = MVA_BDTBkg_abseta_vs_eval->ProjectionX("MVA_BDTBkg_abseta_eval_Xproj_0");
	TH1D *MVA_BDTBkg_abseta_eval_Xproj_1 = MVA_BDTBkg_abseta_vs_eval->ProjectionX("MVA_BDTBkg_abseta_eval_Xproj_1", 0, 10);
	TH1D *MVA_BDTBkg_abseta_eval_Xproj_2 = MVA_BDTBkg_abseta_vs_eval->ProjectionX("MVA_BDTBkg_abseta_eval_Xproj_2", 11, 20);
	TH1D *MVA_BDTBkg_abseta_eval_Xproj_3 = MVA_BDTBkg_abseta_vs_eval->ProjectionX("MVA_BDTBkg_abseta_eval_Xproj_3", 21, MVA_BDTBkg_abseta_vs_eval->GetNbinsX()+1);
	TH1D *MVA_BDTOther_abseta_eval_Xproj_0 = MVA_BDTOther_abseta_vs_eval->ProjectionX("MVA_BDTOther_abseta_eval_Xproj_0");
	TH1D *MVA_BDTOther_abseta_eval_Xproj_1 = MVA_BDTOther_abseta_vs_eval->ProjectionX("MVA_BDTOther_abseta_eval_Xproj_1", 0, 10);
	TH1D *MVA_BDTOther_abseta_eval_Xproj_2 = MVA_BDTOther_abseta_vs_eval->ProjectionX("MVA_BDTOther_abseta_eval_Xproj_2", 11, 20);
	TH1D *MVA_BDTOther_abseta_eval_Xproj_3 = MVA_BDTOther_abseta_vs_eval->ProjectionX("MVA_BDTOther_abseta_eval_Xproj_3", 21, MVA_BDTSig_abseta_vs_eval->GetNbinsX()+1);

	TH1D *MVA_BDT_phi_eval_Xproj_0 = MVA_BDT_phi_vs_eval->ProjectionX("MVA_BDT_phi_eval_Xproj_0");
	TH1D *MVA_BDT_phi_eval_Xproj_1 = MVA_BDT_phi_vs_eval->ProjectionX("MVA_BDT_phi_eval_Xproj_1", 0, 5);
	TH1D *MVA_BDT_phi_eval_Xproj_2 = MVA_BDT_phi_vs_eval->ProjectionX("MVA_BDT_phi_eval_Xproj_2", 6, 10);
	TH1D *MVA_BDT_phi_eval_Xproj_3 = MVA_BDT_phi_vs_eval->ProjectionX("MVA_BDT_phi_eval_Xproj_3", 11, 15);
	TH1D *MVA_BDT_phi_eval_Xproj_4 = MVA_BDT_phi_vs_eval->ProjectionX("MVA_BDT_phi_eval_Xproj_4", 16, 20);
	TH1D *MVA_BDT_phi_eval_Xproj_5 = MVA_BDT_phi_vs_eval->ProjectionX("MVA_BDT_phi_eval_Xproj_5", 21, 25);
	TH1D *MVA_BDT_phi_eval_Xproj_6 = MVA_BDT_phi_vs_eval->ProjectionX("MVA_BDT_phi_eval_Xproj_6", 26, MVA_BDT_phi_vs_eval->GetNbinsX()+1);
	TH1D *MVA_BDTSig_phi_eval_Xproj_0 = MVA_BDTSig_phi_vs_eval->ProjectionX("MVA_BDTSig_phi_eval_Xproj_0");
	TH1D *MVA_BDTSig_phi_eval_Xproj_1 = MVA_BDTSig_phi_vs_eval->ProjectionX("MVA_BDTSig_phi_eval_Xproj_1", 0, 5);
	TH1D *MVA_BDTSig_phi_eval_Xproj_2 = MVA_BDTSig_phi_vs_eval->ProjectionX("MVA_BDTSig_phi_eval_Xproj_2", 6, 10);
	TH1D *MVA_BDTSig_phi_eval_Xproj_3 = MVA_BDTSig_phi_vs_eval->ProjectionX("MVA_BDTSig_phi_eval_Xproj_3", 11, 15);
	TH1D *MVA_BDTSig_phi_eval_Xproj_4 = MVA_BDTSig_phi_vs_eval->ProjectionX("MVA_BDTSig_phi_eval_Xproj_4", 16, 20);
	TH1D *MVA_BDTSig_phi_eval_Xproj_5 = MVA_BDTSig_phi_vs_eval->ProjectionX("MVA_BDTSig_phi_eval_Xproj_5", 21, 25);
	TH1D *MVA_BDTSig_phi_eval_Xproj_6 = MVA_BDTSig_phi_vs_eval->ProjectionX("MVA_BDTSig_phi_eval_Xproj_6", 26, MVA_BDT_phi_vs_eval->GetNbinsX()+1);
	TH1D *MVA_BDTBkg_phi_eval_Xproj_0 = MVA_BDTBkg_phi_vs_eval->ProjectionX("MVA_BDTBkg_phi_eval_Xproj_0");
	TH1D *MVA_BDTBkg_phi_eval_Xproj_1 = MVA_BDTBkg_phi_vs_eval->ProjectionX("MVA_BDTBkg_phi_eval_Xproj_1", 0, 5);
	TH1D *MVA_BDTBkg_phi_eval_Xproj_2 = MVA_BDTBkg_phi_vs_eval->ProjectionX("MVA_BDTBkg_phi_eval_Xproj_2", 6, 10);
	TH1D *MVA_BDTBkg_phi_eval_Xproj_3 = MVA_BDTBkg_phi_vs_eval->ProjectionX("MVA_BDTBkg_phi_eval_Xproj_3", 11, 15);
	TH1D *MVA_BDTBkg_phi_eval_Xproj_4 = MVA_BDTBkg_phi_vs_eval->ProjectionX("MVA_BDTBkg_phi_eval_Xproj_4", 16, 20);
	TH1D *MVA_BDTBkg_phi_eval_Xproj_5 = MVA_BDTBkg_phi_vs_eval->ProjectionX("MVA_BDTBkg_phi_eval_Xproj_5", 21, 25);
	TH1D *MVA_BDTBkg_phi_eval_Xproj_6 = MVA_BDTBkg_phi_vs_eval->ProjectionX("MVA_BDTBkg_phi_eval_Xproj_6", 26, MVA_BDT_phi_vs_eval->GetNbinsX()+1);
	TH1D *MVA_BDTOther_phi_eval_Xproj_0 = MVA_BDTOther_phi_vs_eval->ProjectionX("MVA_BDTOther_phi_eval_Xproj_0");
	TH1D *MVA_BDTOther_phi_eval_Xproj_1 = MVA_BDTOther_phi_vs_eval->ProjectionX("MVA_BDTOther_phi_eval_Xproj_1", 0, 5);
	TH1D *MVA_BDTOther_phi_eval_Xproj_2 = MVA_BDTOther_phi_vs_eval->ProjectionX("MVA_BDTOther_phi_eval_Xproj_2", 6, 10);
	TH1D *MVA_BDTOther_phi_eval_Xproj_3 = MVA_BDTOther_phi_vs_eval->ProjectionX("MVA_BDTOther_phi_eval_Xproj_3", 11, 15);
	TH1D *MVA_BDTOther_phi_eval_Xproj_4 = MVA_BDTOther_phi_vs_eval->ProjectionX("MVA_BDTOther_phi_eval_Xproj_4", 16, 20);
	TH1D *MVA_BDTOther_phi_eval_Xproj_5 = MVA_BDTOther_phi_vs_eval->ProjectionX("MVA_BDTOther_phi_eval_Xproj_5", 21, 25);
	TH1D *MVA_BDTOther_phi_eval_Xproj_6 = MVA_BDTOther_phi_vs_eval->ProjectionX("MVA_BDTOther_phi_eval_Xproj_6", 26, MVA_BDT_phi_vs_eval->GetNbinsX()+1);

	TH1D *MVA_BDT_centzone_eval_Xproj_0 = MVA_BDT_centzone_vs_eval->ProjectionX("MVA_BDT_centzone_eval_Xproj_0");
	TH1D *MVA_BDT_centzone_eval_Xproj_1 = MVA_BDT_centzone_vs_eval->ProjectionX("MVA_BDT_centzone_eval_Xproj_1", 3, 4);
	TH1D *MVA_BDT_centzone_eval_Xproj_2 = MVA_BDT_centzone_vs_eval->ProjectionX("MVA_BDT_centzone_eval_Xproj_2", 5, 6);
	TH1D *MVA_BDT_centzone_eval_Xproj_3 = MVA_BDT_centzone_vs_eval->ProjectionX("MVA_BDT_centzone_eval_Xproj_3", 7, 8);
	TH1D *MVA_BDT_centzone_eval_Xproj_4 = MVA_BDT_centzone_vs_eval->ProjectionX("MVA_BDT_centzone_eval_Xproj_4", 9, 10);
	TH1D *MVA_BDT_centzone_eval_Xproj_5 = MVA_BDT_centzone_vs_eval->ProjectionX("MVA_BDT_centzone_eval_Xproj_5", 11, 12);
	TH1D *MVA_BDT_centzone_eval_Xproj_6 = MVA_BDT_centzone_vs_eval->ProjectionX("MVA_BDT_centzone_eval_Xproj_6", 7, 10);
	TH1D *MVA_BDTSig_centzone_eval_Xproj_0 = MVA_BDTSig_centzone_vs_eval->ProjectionX("MVA_BDTSig_centzone_eval_Xproj_0");
	TH1D *MVA_BDTSig_centzone_eval_Xproj_1 = MVA_BDTSig_centzone_vs_eval->ProjectionX("MVA_BDTSig_centzone_eval_Xproj_1", 3, 4);
	TH1D *MVA_BDTSig_centzone_eval_Xproj_2 = MVA_BDTSig_centzone_vs_eval->ProjectionX("MVA_BDTSig_centzone_eval_Xproj_2", 5, 6);
	TH1D *MVA_BDTSig_centzone_eval_Xproj_3 = MVA_BDTSig_centzone_vs_eval->ProjectionX("MVA_BDTSig_centzone_eval_Xproj_3", 7, 8);
	TH1D *MVA_BDTSig_centzone_eval_Xproj_4 = MVA_BDTSig_centzone_vs_eval->ProjectionX("MVA_BDTSig_centzone_eval_Xproj_4", 9, 10);
	TH1D *MVA_BDTSig_centzone_eval_Xproj_5 = MVA_BDTSig_centzone_vs_eval->ProjectionX("MVA_BDTSig_centzone_eval_Xproj_5", 11, 12);
	TH1D *MVA_BDTSig_centzone_eval_Xproj_6 = MVA_BDTSig_centzone_vs_eval->ProjectionX("MVA_BDTSig_centzone_eval_Xproj_6", 7, 10);
	TH1D *MVA_BDTBkg_centzone_eval_Xproj_0 = MVA_BDTBkg_centzone_vs_eval->ProjectionX("MVA_BDTBkg_centzone_eval_Xproj_0");
	TH1D *MVA_BDTBkg_centzone_eval_Xproj_1 = MVA_BDTBkg_centzone_vs_eval->ProjectionX("MVA_BDTBkg_centzone_eval_Xproj_1", 3, 4);
	TH1D *MVA_BDTBkg_centzone_eval_Xproj_2 = MVA_BDTBkg_centzone_vs_eval->ProjectionX("MVA_BDTBkg_centzone_eval_Xproj_2", 5, 6);
	TH1D *MVA_BDTBkg_centzone_eval_Xproj_3 = MVA_BDTBkg_centzone_vs_eval->ProjectionX("MVA_BDTBkg_centzone_eval_Xproj_3", 7, 8);
	TH1D *MVA_BDTBkg_centzone_eval_Xproj_4 = MVA_BDTBkg_centzone_vs_eval->ProjectionX("MVA_BDTBkg_centzone_eval_Xproj_4", 9, 10);
	TH1D *MVA_BDTBkg_centzone_eval_Xproj_5 = MVA_BDTBkg_centzone_vs_eval->ProjectionX("MVA_BDTBkg_centzone_eval_Xproj_5", 11, 12);
	TH1D *MVA_BDTBkg_centzone_eval_Xproj_6 = MVA_BDTBkg_centzone_vs_eval->ProjectionX("MVA_BDTBkg_centzone_eval_Xproj_6", 7, 10);
	TH1D *MVA_BDTOther_centzone_eval_Xproj_0 = MVA_BDTOther_centzone_vs_eval->ProjectionX("MVA_BDTOther_centzone_eval_Xproj_0");
	TH1D *MVA_BDTOther_centzone_eval_Xproj_1 = MVA_BDTOther_centzone_vs_eval->ProjectionX("MVA_BDTOther_centzone_eval_Xproj_1", 3, 4);
	TH1D *MVA_BDTOther_centzone_eval_Xproj_2 = MVA_BDTOther_centzone_vs_eval->ProjectionX("MVA_BDTOther_centzone_eval_Xproj_2", 5, 6);
	TH1D *MVA_BDTOther_centzone_eval_Xproj_3 = MVA_BDTOther_centzone_vs_eval->ProjectionX("MVA_BDTOther_centzone_eval_Xproj_3", 7, 8);
	TH1D *MVA_BDTOther_centzone_eval_Xproj_4 = MVA_BDTOther_centzone_vs_eval->ProjectionX("MVA_BDTOther_centzone_eval_Xproj_4", 9, 10);
	TH1D *MVA_BDTOther_centzone_eval_Xproj_5 = MVA_BDTOther_centzone_vs_eval->ProjectionX("MVA_BDTOther_centzone_eval_Xproj_5", 11, 12);
	TH1D *MVA_BDTOther_centzone_eval_Xproj_6 = MVA_BDTOther_centzone_vs_eval->ProjectionX("MVA_BDTOther_centzone_eval_Xproj_6", 7, 10);

// TH2F IP2D projections

	TH1D *MVA_IP2D_pt_eval_Xproj_0 = MVA_IP2D_pt_vs_eval->ProjectionX("MVA_IP2D_pt_eval_Xproj_0");
	TH1D *MVA_IP2D_pt_eval_Xproj_1 = MVA_IP2D_pt_vs_eval->ProjectionX("MVA_IP2D_pt_eval_Xproj_1", lim_pt100, lim_pt120);
	TH1D *MVA_IP2D_pt_eval_Xproj_2 = MVA_IP2D_pt_vs_eval->ProjectionX("MVA_IP2D_pt_eval_Xproj_2", lim_pt120, lim_pt140);
	TH1D *MVA_IP2D_pt_eval_Xproj_3 = MVA_IP2D_pt_vs_eval->ProjectionX("MVA_IP2D_pt_eval_Xproj_3", lim_pt140, lim_pt160);
	TH1D *MVA_IP2D_pt_eval_Xproj_4 = MVA_IP2D_pt_vs_eval->ProjectionX("MVA_IP2D_pt_eval_Xproj_4", lim_pt160, lim_pt180);
	TH1D *MVA_IP2D_pt_eval_Xproj_5 = MVA_IP2D_pt_vs_eval->ProjectionX("MVA_IP2D_pt_eval_Xproj_5", lim_pt180, lim_pt200);
	TH1D *MVA_IP2D_pt_eval_Xproj_6 = MVA_IP2D_pt_vs_eval->ProjectionX("MVA_IP2D_pt_eval_Xproj_6", lim_pt200, lim_pt300);
	TH1D *MVA_IP2D_pt_eval_Xproj_7 = MVA_IP2D_pt_vs_eval->ProjectionX("MVA_IP2D_pt_eval_Xproj_7", lim_pt300, lim_pt400);
	TH1D *MVA_IP2D_pt_eval_Xproj_8 = MVA_IP2D_pt_vs_eval->ProjectionX("MVA_IP2D_pt_eval_Xproj_8", lim_pt400, lim_pt500);
	TH1D *MVA_IP2D_SIGNAL_pt_eval_Xproj_0 = MVA_IP2D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_pt_eval_Xproj_0");
	TH1D *MVA_IP2D_SIGNAL_pt_eval_Xproj_1 = MVA_IP2D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_pt_eval_Xproj_1", lim_pt100, lim_pt120);
	TH1D *MVA_IP2D_SIGNAL_pt_eval_Xproj_2 = MVA_IP2D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_pt_eval_Xproj_2", lim_pt120, lim_pt140);
	TH1D *MVA_IP2D_SIGNAL_pt_eval_Xproj_3 = MVA_IP2D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_pt_eval_Xproj_3", lim_pt140, lim_pt160);
	TH1D *MVA_IP2D_SIGNAL_pt_eval_Xproj_4 = MVA_IP2D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_pt_eval_Xproj_4", lim_pt160, lim_pt180);
	TH1D *MVA_IP2D_SIGNAL_pt_eval_Xproj_5 = MVA_IP2D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_pt_eval_Xproj_5", lim_pt180, lim_pt200);
	TH1D *MVA_IP2D_SIGNAL_pt_eval_Xproj_6 = MVA_IP2D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_pt_eval_Xproj_6", lim_pt200, lim_pt300);
	TH1D *MVA_IP2D_SIGNAL_pt_eval_Xproj_7 = MVA_IP2D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_pt_eval_Xproj_7", lim_pt300, lim_pt400);
	TH1D *MVA_IP2D_SIGNAL_pt_eval_Xproj_8 = MVA_IP2D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_pt_eval_Xproj_8", lim_pt400, lim_pt500);
	TH1D *MVA_IP2D_Background_pt_eval_Xproj_0 = MVA_IP2D_Background_pt_vs_eval->ProjectionX("MVA_IP2D_Background_pt_eval_Xproj_0");
	TH1D *MVA_IP2D_Background_pt_eval_Xproj_1 = MVA_IP2D_Background_pt_vs_eval->ProjectionX("MVA_IP2D_Background_pt_eval_Xproj_1", lim_pt100, lim_pt120);
	TH1D *MVA_IP2D_Background_pt_eval_Xproj_2 = MVA_IP2D_Background_pt_vs_eval->ProjectionX("MVA_IP2D_Background_pt_eval_Xproj_2", lim_pt120, lim_pt140);
	TH1D *MVA_IP2D_Background_pt_eval_Xproj_3 = MVA_IP2D_Background_pt_vs_eval->ProjectionX("MVA_IP2D_Background_pt_eval_Xproj_3", lim_pt140, lim_pt160);
	TH1D *MVA_IP2D_Background_pt_eval_Xproj_4 = MVA_IP2D_Background_pt_vs_eval->ProjectionX("MVA_IP2D_Background_pt_eval_Xproj_4", lim_pt160, lim_pt180);
	TH1D *MVA_IP2D_Background_pt_eval_Xproj_5 = MVA_IP2D_Background_pt_vs_eval->ProjectionX("MVA_IP2D_Background_pt_eval_Xproj_5", lim_pt180, lim_pt200);
	TH1D *MVA_IP2D_Background_pt_eval_Xproj_6 = MVA_IP2D_Background_pt_vs_eval->ProjectionX("MVA_IP2D_Background_pt_eval_Xproj_6", lim_pt200, lim_pt300);
	TH1D *MVA_IP2D_Background_pt_eval_Xproj_7 = MVA_IP2D_Background_pt_vs_eval->ProjectionX("MVA_IP2D_Background_pt_eval_Xproj_7", lim_pt300, lim_pt400);
	TH1D *MVA_IP2D_Background_pt_eval_Xproj_8 = MVA_IP2D_Background_pt_vs_eval->ProjectionX("MVA_IP2D_Background_pt_eval_Xproj_8", lim_pt400, lim_pt500);
	TH1D *MVA_IP2D_Other_pt_eval_Xproj_0 = MVA_IP2D_Other_pt_vs_eval->ProjectionX("MVA_IP2D_Other_pt_eval_Xproj_0");
	TH1D *MVA_IP2D_Other_pt_eval_Xproj_1 = MVA_IP2D_Other_pt_vs_eval->ProjectionX("MVA_IP2D_Other_pt_eval_Xproj_1", lim_pt100, lim_pt120);
	TH1D *MVA_IP2D_Other_pt_eval_Xproj_2 = MVA_IP2D_Other_pt_vs_eval->ProjectionX("MVA_IP2D_Other_pt_eval_Xproj_2", lim_pt120, lim_pt140);
	TH1D *MVA_IP2D_Other_pt_eval_Xproj_3 = MVA_IP2D_Other_pt_vs_eval->ProjectionX("MVA_IP2D_Other_pt_eval_Xproj_3", lim_pt140, lim_pt160);
	TH1D *MVA_IP2D_Other_pt_eval_Xproj_4 = MVA_IP2D_Other_pt_vs_eval->ProjectionX("MVA_IP2D_Other_pt_eval_Xproj_4", lim_pt160, lim_pt180);
	TH1D *MVA_IP2D_Other_pt_eval_Xproj_5 = MVA_IP2D_Other_pt_vs_eval->ProjectionX("MVA_IP2D_Other_pt_eval_Xproj_5", lim_pt180, lim_pt200);
	TH1D *MVA_IP2D_Other_pt_eval_Xproj_6 = MVA_IP2D_Other_pt_vs_eval->ProjectionX("MVA_IP2D_Other_pt_eval_Xproj_6", lim_pt200, lim_pt300);
	TH1D *MVA_IP2D_Other_pt_eval_Xproj_7 = MVA_IP2D_Other_pt_vs_eval->ProjectionX("MVA_IP2D_Other_pt_eval_Xproj_7", lim_pt300, lim_pt400);
	TH1D *MVA_IP2D_Other_pt_eval_Xproj_8 = MVA_IP2D_Other_pt_vs_eval->ProjectionX("MVA_IP2D_Other_pt_eval_Xproj_8", lim_pt400, lim_pt500);

	TH1D *MVA_IP2D_abseta_eval_Xproj_0 = MVA_IP2D_abseta_vs_eval->ProjectionX("MVA_IP2D_abseta_eval_Xproj_0");
	TH1D *MVA_IP2D_abseta_eval_Xproj_1 = MVA_IP2D_abseta_vs_eval->ProjectionX("MVA_IP2D_abseta_eval_Xproj_1", 0, 10);
	TH1D *MVA_IP2D_abseta_eval_Xproj_2 = MVA_IP2D_abseta_vs_eval->ProjectionX("MVA_IP2D_abseta_eval_Xproj_2", 11, 20);
	TH1D *MVA_IP2D_abseta_eval_Xproj_3 = MVA_IP2D_abseta_vs_eval->ProjectionX("MVA_IP2D_abseta_eval_Xproj_3", 21, MVA_IP2D_abseta_vs_eval->GetNbinsX()+1);
	TH1D *MVA_IP2D_SIGNAL_abseta_eval_Xproj_0 = MVA_IP2D_SIGNAL_abseta_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_abseta_eval_Xproj_0");
	TH1D *MVA_IP2D_SIGNAL_abseta_eval_Xproj_1 = MVA_IP2D_SIGNAL_abseta_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_abseta_eval_Xproj_1", 0, 10);
	TH1D *MVA_IP2D_SIGNAL_abseta_eval_Xproj_2 = MVA_IP2D_SIGNAL_abseta_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_abseta_eval_Xproj_2", 11, 20);
	TH1D *MVA_IP2D_SIGNAL_abseta_eval_Xproj_3 = MVA_IP2D_SIGNAL_abseta_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_abseta_eval_Xproj_3", 21, MVA_IP2D_SIGNAL_abseta_vs_eval->GetNbinsX()+1);
	TH1D *MVA_IP2D_Background_abseta_eval_Xproj_0 = MVA_IP2D_Background_abseta_vs_eval->ProjectionX("MVA_IP2D_Background_abseta_eval_Xproj_0");
	TH1D *MVA_IP2D_Background_abseta_eval_Xproj_1 = MVA_IP2D_Background_abseta_vs_eval->ProjectionX("MVA_IP2D_Background_abseta_eval_Xproj_1", 0, 10);
	TH1D *MVA_IP2D_Background_abseta_eval_Xproj_2 = MVA_IP2D_Background_abseta_vs_eval->ProjectionX("MVA_IP2D_Background_abseta_eval_Xproj_2", 11, 20);
	TH1D *MVA_IP2D_Background_abseta_eval_Xproj_3 = MVA_IP2D_Background_abseta_vs_eval->ProjectionX("MVA_IP2D_Background_abseta_eval_Xproj_3", 21, MVA_IP2D_Background_abseta_vs_eval->GetNbinsX()+1);
	TH1D *MVA_IP2D_Other_abseta_eval_Xproj_0 = MVA_IP2D_Other_abseta_vs_eval->ProjectionX("MVA_IP2D_Other_abseta_eval_Xproj_0");
	TH1D *MVA_IP2D_Other_abseta_eval_Xproj_1 = MVA_IP2D_Other_abseta_vs_eval->ProjectionX("MVA_IP2D_Other_abseta_eval_Xproj_1", 0, 10);
	TH1D *MVA_IP2D_Other_abseta_eval_Xproj_2 = MVA_IP2D_Other_abseta_vs_eval->ProjectionX("MVA_IP2D_Other_abseta_eval_Xproj_2", 11, 20);
	TH1D *MVA_IP2D_Other_abseta_eval_Xproj_3 = MVA_IP2D_Other_abseta_vs_eval->ProjectionX("MVA_IP2D_Other_abseta_eval_Xproj_3", 21, MVA_IP2D_SIGNAL_abseta_vs_eval->GetNbinsX()+1);

	TH1D *MVA_IP2D_phi_eval_Xproj_0 = MVA_IP2D_phi_vs_eval->ProjectionX("MVA_IP2D_phi_eval_Xproj_0");
	TH1D *MVA_IP2D_phi_eval_Xproj_1 = MVA_IP2D_phi_vs_eval->ProjectionX("MVA_IP2D_phi_eval_Xproj_1", 0, 5);
	TH1D *MVA_IP2D_phi_eval_Xproj_2 = MVA_IP2D_phi_vs_eval->ProjectionX("MVA_IP2D_phi_eval_Xproj_2", 6, 10);
	TH1D *MVA_IP2D_phi_eval_Xproj_3 = MVA_IP2D_phi_vs_eval->ProjectionX("MVA_IP2D_phi_eval_Xproj_3", 11, 15);
	TH1D *MVA_IP2D_phi_eval_Xproj_4 = MVA_IP2D_phi_vs_eval->ProjectionX("MVA_IP2D_phi_eval_Xproj_4", 16, 20);
	TH1D *MVA_IP2D_phi_eval_Xproj_5 = MVA_IP2D_phi_vs_eval->ProjectionX("MVA_IP2D_phi_eval_Xproj_5", 21, 25);
	TH1D *MVA_IP2D_phi_eval_Xproj_6 = MVA_IP2D_phi_vs_eval->ProjectionX("MVA_IP2D_phi_eval_Xproj_6", 26, MVA_IP2D_phi_vs_eval->GetNbinsX()+1);
	TH1D *MVA_IP2D_SIGNAL_phi_eval_Xproj_0 = MVA_IP2D_SIGNAL_phi_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_phi_eval_Xproj_0");
	TH1D *MVA_IP2D_SIGNAL_phi_eval_Xproj_1 = MVA_IP2D_SIGNAL_phi_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_phi_eval_Xproj_1", 0, 5);
	TH1D *MVA_IP2D_SIGNAL_phi_eval_Xproj_2 = MVA_IP2D_SIGNAL_phi_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_phi_eval_Xproj_2", 6, 10);
	TH1D *MVA_IP2D_SIGNAL_phi_eval_Xproj_3 = MVA_IP2D_SIGNAL_phi_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_phi_eval_Xproj_3", 11, 15);
	TH1D *MVA_IP2D_SIGNAL_phi_eval_Xproj_4 = MVA_IP2D_SIGNAL_phi_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_phi_eval_Xproj_4", 16, 20);
	TH1D *MVA_IP2D_SIGNAL_phi_eval_Xproj_5 = MVA_IP2D_SIGNAL_phi_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_phi_eval_Xproj_5", 21, 25);
	TH1D *MVA_IP2D_SIGNAL_phi_eval_Xproj_6 = MVA_IP2D_SIGNAL_phi_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_phi_eval_Xproj_6", 26, MVA_IP2D_phi_vs_eval->GetNbinsX()+1);
	TH1D *MVA_IP2D_Background_phi_eval_Xproj_0 = MVA_IP2D_Background_phi_vs_eval->ProjectionX("MVA_IP2D_Background_phi_eval_Xproj_0");
	TH1D *MVA_IP2D_Background_phi_eval_Xproj_1 = MVA_IP2D_Background_phi_vs_eval->ProjectionX("MVA_IP2D_Background_phi_eval_Xproj_1", 0, 5);
	TH1D *MVA_IP2D_Background_phi_eval_Xproj_2 = MVA_IP2D_Background_phi_vs_eval->ProjectionX("MVA_IP2D_Background_phi_eval_Xproj_2", 6, 10);
	TH1D *MVA_IP2D_Background_phi_eval_Xproj_3 = MVA_IP2D_Background_phi_vs_eval->ProjectionX("MVA_IP2D_Background_phi_eval_Xproj_3", 11, 15);
	TH1D *MVA_IP2D_Background_phi_eval_Xproj_4 = MVA_IP2D_Background_phi_vs_eval->ProjectionX("MVA_IP2D_Background_phi_eval_Xproj_4", 16, 20);
	TH1D *MVA_IP2D_Background_phi_eval_Xproj_5 = MVA_IP2D_Background_phi_vs_eval->ProjectionX("MVA_IP2D_Background_phi_eval_Xproj_5", 21, 25);
	TH1D *MVA_IP2D_Background_phi_eval_Xproj_6 = MVA_IP2D_Background_phi_vs_eval->ProjectionX("MVA_IP2D_Background_phi_eval_Xproj_6", 26, MVA_IP2D_phi_vs_eval->GetNbinsX()+1);
	TH1D *MVA_IP2D_Other_phi_eval_Xproj_0 = MVA_IP2D_Other_phi_vs_eval->ProjectionX("MVA_IP2D_Other_phi_eval_Xproj_0");
	TH1D *MVA_IP2D_Other_phi_eval_Xproj_1 = MVA_IP2D_Other_phi_vs_eval->ProjectionX("MVA_IP2D_Other_phi_eval_Xproj_1", 0, 5);
	TH1D *MVA_IP2D_Other_phi_eval_Xproj_2 = MVA_IP2D_Other_phi_vs_eval->ProjectionX("MVA_IP2D_Other_phi_eval_Xproj_2", 6, 10);
	TH1D *MVA_IP2D_Other_phi_eval_Xproj_3 = MVA_IP2D_Other_phi_vs_eval->ProjectionX("MVA_IP2D_Other_phi_eval_Xproj_3", 11, 15);
	TH1D *MVA_IP2D_Other_phi_eval_Xproj_4 = MVA_IP2D_Other_phi_vs_eval->ProjectionX("MVA_IP2D_Other_phi_eval_Xproj_4", 16, 20);
	TH1D *MVA_IP2D_Other_phi_eval_Xproj_5 = MVA_IP2D_Other_phi_vs_eval->ProjectionX("MVA_IP2D_Other_phi_eval_Xproj_5", 21, 25);
	TH1D *MVA_IP2D_Other_phi_eval_Xproj_6 = MVA_IP2D_Other_phi_vs_eval->ProjectionX("MVA_IP2D_Other_phi_eval_Xproj_6", 26, MVA_IP2D_phi_vs_eval->GetNbinsX()+1);

	TH1D *MVA_IP2D_centzone_eval_Xproj_0 = MVA_IP2D_centzone_vs_eval->ProjectionX("MVA_IP2D_centzone_eval_Xproj_0");
	TH1D *MVA_IP2D_centzone_eval_Xproj_1 = MVA_IP2D_centzone_vs_eval->ProjectionX("MVA_IP2D_centzone_eval_Xproj_1", 3, 4);
	TH1D *MVA_IP2D_centzone_eval_Xproj_2 = MVA_IP2D_centzone_vs_eval->ProjectionX("MVA_IP2D_centzone_eval_Xproj_2", 5, 6);
	TH1D *MVA_IP2D_centzone_eval_Xproj_3 = MVA_IP2D_centzone_vs_eval->ProjectionX("MVA_IP2D_centzone_eval_Xproj_3", 7, 8);
	TH1D *MVA_IP2D_centzone_eval_Xproj_4 = MVA_IP2D_centzone_vs_eval->ProjectionX("MVA_IP2D_centzone_eval_Xproj_4", 9, 10);
	TH1D *MVA_IP2D_centzone_eval_Xproj_5 = MVA_IP2D_centzone_vs_eval->ProjectionX("MVA_IP2D_centzone_eval_Xproj_5", 11, 12);
	TH1D *MVA_IP2D_SIGNAL_centzone_eval_Xproj_0 = MVA_IP2D_SIGNAL_centzone_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_centzone_eval_Xproj_0");
	TH1D *MVA_IP2D_SIGNAL_centzone_eval_Xproj_1 = MVA_IP2D_SIGNAL_centzone_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_centzone_eval_Xproj_1", 3, 4);
	TH1D *MVA_IP2D_SIGNAL_centzone_eval_Xproj_2 = MVA_IP2D_SIGNAL_centzone_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_centzone_eval_Xproj_2", 5, 6);
	TH1D *MVA_IP2D_SIGNAL_centzone_eval_Xproj_3 = MVA_IP2D_SIGNAL_centzone_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_centzone_eval_Xproj_3", 7, 8);
	TH1D *MVA_IP2D_SIGNAL_centzone_eval_Xproj_4 = MVA_IP2D_SIGNAL_centzone_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_centzone_eval_Xproj_4", 9, 10);
	TH1D *MVA_IP2D_SIGNAL_centzone_eval_Xproj_5 = MVA_IP2D_SIGNAL_centzone_vs_eval->ProjectionX("MVA_IP2D_SIGNAL_centzone_eval_Xproj_5", 11, 12);
	TH1D *MVA_IP2D_Background_centzone_eval_Xproj_0 = MVA_IP2D_Background_centzone_vs_eval->ProjectionX("MVA_IP2D_Background_centzone_eval_Xproj_0");
	TH1D *MVA_IP2D_Background_centzone_eval_Xproj_1 = MVA_IP2D_Background_centzone_vs_eval->ProjectionX("MVA_IP2D_Background_centzone_eval_Xproj_1", 3, 4);
	TH1D *MVA_IP2D_Background_centzone_eval_Xproj_2 = MVA_IP2D_Background_centzone_vs_eval->ProjectionX("MVA_IP2D_Background_centzone_eval_Xproj_2", 5, 6);
	TH1D *MVA_IP2D_Background_centzone_eval_Xproj_3 = MVA_IP2D_Background_centzone_vs_eval->ProjectionX("MVA_IP2D_Background_centzone_eval_Xproj_3", 7, 8);
	TH1D *MVA_IP2D_Background_centzone_eval_Xproj_4 = MVA_IP2D_Background_centzone_vs_eval->ProjectionX("MVA_IP2D_Background_centzone_eval_Xproj_4", 9, 10);
	TH1D *MVA_IP2D_Background_centzone_eval_Xproj_5 = MVA_IP2D_Background_centzone_vs_eval->ProjectionX("MVA_IP2D_Background_centzone_eval_Xproj_5", 11, 12);
	TH1D *MVA_IP2D_Other_centzone_eval_Xproj_0 = MVA_IP2D_Other_centzone_vs_eval->ProjectionX("MVA_IP2D_Other_centzone_eval_Xproj_0");
	TH1D *MVA_IP2D_Other_centzone_eval_Xproj_1 = MVA_IP2D_Other_centzone_vs_eval->ProjectionX("MVA_IP2D_Other_centzone_eval_Xproj_1", 3, 4);
	TH1D *MVA_IP2D_Other_centzone_eval_Xproj_2 = MVA_IP2D_Other_centzone_vs_eval->ProjectionX("MVA_IP2D_Other_centzone_eval_Xproj_2", 5, 6);
	TH1D *MVA_IP2D_Other_centzone_eval_Xproj_3 = MVA_IP2D_Other_centzone_vs_eval->ProjectionX("MVA_IP2D_Other_centzone_eval_Xproj_3", 7, 8);
	TH1D *MVA_IP2D_Other_centzone_eval_Xproj_4 = MVA_IP2D_Other_centzone_vs_eval->ProjectionX("MVA_IP2D_Other_centzone_eval_Xproj_4", 9, 10);
	TH1D *MVA_IP2D_Other_centzone_eval_Xproj_5 = MVA_IP2D_Other_centzone_vs_eval->ProjectionX("MVA_IP2D_Other_centzone_eval_Xproj_5", 11, 12);

// TH2F IP3D projections

	TH1D *MVA_IP3D_pt_eval_Xproj_0 = MVA_IP3D_pt_vs_eval->ProjectionX("MVA_IP3D_pt_eval_Xproj_0");
	TH1D *MVA_IP3D_pt_eval_Xproj_1 = MVA_IP3D_pt_vs_eval->ProjectionX("MVA_IP3D_pt_eval_Xproj_1", lim_pt100, lim_pt120);
	TH1D *MVA_IP3D_pt_eval_Xproj_2 = MVA_IP3D_pt_vs_eval->ProjectionX("MVA_IP3D_pt_eval_Xproj_2", lim_pt120, lim_pt140);
	TH1D *MVA_IP3D_pt_eval_Xproj_3 = MVA_IP3D_pt_vs_eval->ProjectionX("MVA_IP3D_pt_eval_Xproj_3", lim_pt140, lim_pt160);
	TH1D *MVA_IP3D_pt_eval_Xproj_4 = MVA_IP3D_pt_vs_eval->ProjectionX("MVA_IP3D_pt_eval_Xproj_4", lim_pt160, lim_pt180);
	TH1D *MVA_IP3D_pt_eval_Xproj_5 = MVA_IP3D_pt_vs_eval->ProjectionX("MVA_IP3D_pt_eval_Xproj_5", lim_pt180, lim_pt200);
	TH1D *MVA_IP3D_pt_eval_Xproj_6 = MVA_IP3D_pt_vs_eval->ProjectionX("MVA_IP3D_pt_eval_Xproj_6", lim_pt200, lim_pt300);
	TH1D *MVA_IP3D_pt_eval_Xproj_7 = MVA_IP3D_pt_vs_eval->ProjectionX("MVA_IP3D_pt_eval_Xproj_7", lim_pt300, lim_pt400);
	TH1D *MVA_IP3D_pt_eval_Xproj_8 = MVA_IP3D_pt_vs_eval->ProjectionX("MVA_IP3D_pt_eval_Xproj_8", lim_pt400, lim_pt500);
	TH1D *MVA_IP3D_SIGNAL_pt_eval_Xproj_0 = MVA_IP3D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_pt_eval_Xproj_0");
	TH1D *MVA_IP3D_SIGNAL_pt_eval_Xproj_1 = MVA_IP3D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_pt_eval_Xproj_1", lim_pt100, lim_pt120);
	TH1D *MVA_IP3D_SIGNAL_pt_eval_Xproj_2 = MVA_IP3D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_pt_eval_Xproj_2", lim_pt120, lim_pt140);
	TH1D *MVA_IP3D_SIGNAL_pt_eval_Xproj_3 = MVA_IP3D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_pt_eval_Xproj_3", lim_pt140, lim_pt160);
	TH1D *MVA_IP3D_SIGNAL_pt_eval_Xproj_4 = MVA_IP3D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_pt_eval_Xproj_4", lim_pt160, lim_pt180);
	TH1D *MVA_IP3D_SIGNAL_pt_eval_Xproj_5 = MVA_IP3D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_pt_eval_Xproj_5", lim_pt180, lim_pt200);
	TH1D *MVA_IP3D_SIGNAL_pt_eval_Xproj_6 = MVA_IP3D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_pt_eval_Xproj_6", lim_pt200, lim_pt300);
	TH1D *MVA_IP3D_SIGNAL_pt_eval_Xproj_7 = MVA_IP3D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_pt_eval_Xproj_7", lim_pt300, lim_pt400);
	TH1D *MVA_IP3D_SIGNAL_pt_eval_Xproj_8 = MVA_IP3D_SIGNAL_pt_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_pt_eval_Xproj_8", lim_pt400, lim_pt500);
	TH1D *MVA_IP3D_Background_pt_eval_Xproj_0 = MVA_IP3D_Background_pt_vs_eval->ProjectionX("MVA_IP3D_Background_pt_eval_Xproj_0");
	TH1D *MVA_IP3D_Background_pt_eval_Xproj_1 = MVA_IP3D_Background_pt_vs_eval->ProjectionX("MVA_IP3D_Background_pt_eval_Xproj_1", lim_pt100, lim_pt120);
	TH1D *MVA_IP3D_Background_pt_eval_Xproj_2 = MVA_IP3D_Background_pt_vs_eval->ProjectionX("MVA_IP3D_Background_pt_eval_Xproj_2", lim_pt120, lim_pt140);
	TH1D *MVA_IP3D_Background_pt_eval_Xproj_3 = MVA_IP3D_Background_pt_vs_eval->ProjectionX("MVA_IP3D_Background_pt_eval_Xproj_3", lim_pt140, lim_pt160);
	TH1D *MVA_IP3D_Background_pt_eval_Xproj_4 = MVA_IP3D_Background_pt_vs_eval->ProjectionX("MVA_IP3D_Background_pt_eval_Xproj_4", lim_pt160, lim_pt180);
	TH1D *MVA_IP3D_Background_pt_eval_Xproj_5 = MVA_IP3D_Background_pt_vs_eval->ProjectionX("MVA_IP3D_Background_pt_eval_Xproj_5", lim_pt180, lim_pt200);
	TH1D *MVA_IP3D_Background_pt_eval_Xproj_6 = MVA_IP3D_Background_pt_vs_eval->ProjectionX("MVA_IP3D_Background_pt_eval_Xproj_6", lim_pt200, lim_pt300);
	TH1D *MVA_IP3D_Background_pt_eval_Xproj_7 = MVA_IP3D_Background_pt_vs_eval->ProjectionX("MVA_IP3D_Background_pt_eval_Xproj_7", lim_pt300, lim_pt400);
	TH1D *MVA_IP3D_Background_pt_eval_Xproj_8 = MVA_IP3D_Background_pt_vs_eval->ProjectionX("MVA_IP3D_Background_pt_eval_Xproj_8", lim_pt400, lim_pt500);
	TH1D *MVA_IP3D_Other_pt_eval_Xproj_0 = MVA_IP3D_Other_pt_vs_eval->ProjectionX("MVA_IP3D_Other_pt_eval_Xproj_0");
	TH1D *MVA_IP3D_Other_pt_eval_Xproj_1 = MVA_IP3D_Other_pt_vs_eval->ProjectionX("MVA_IP3D_Other_pt_eval_Xproj_1", lim_pt100, lim_pt120);
	TH1D *MVA_IP3D_Other_pt_eval_Xproj_2 = MVA_IP3D_Other_pt_vs_eval->ProjectionX("MVA_IP3D_Other_pt_eval_Xproj_2", lim_pt120, lim_pt140);
	TH1D *MVA_IP3D_Other_pt_eval_Xproj_3 = MVA_IP3D_Other_pt_vs_eval->ProjectionX("MVA_IP3D_Other_pt_eval_Xproj_3", lim_pt140, lim_pt160);
	TH1D *MVA_IP3D_Other_pt_eval_Xproj_4 = MVA_IP3D_Other_pt_vs_eval->ProjectionX("MVA_IP3D_Other_pt_eval_Xproj_4", lim_pt160, lim_pt180);
	TH1D *MVA_IP3D_Other_pt_eval_Xproj_5 = MVA_IP3D_Other_pt_vs_eval->ProjectionX("MVA_IP3D_Other_pt_eval_Xproj_5", lim_pt180, lim_pt200);
	TH1D *MVA_IP3D_Other_pt_eval_Xproj_6 = MVA_IP3D_Other_pt_vs_eval->ProjectionX("MVA_IP3D_Other_pt_eval_Xproj_6", lim_pt200, lim_pt300);
	TH1D *MVA_IP3D_Other_pt_eval_Xproj_7 = MVA_IP3D_Other_pt_vs_eval->ProjectionX("MVA_IP3D_Other_pt_eval_Xproj_7", lim_pt300, lim_pt400);
	TH1D *MVA_IP3D_Other_pt_eval_Xproj_8 = MVA_IP3D_Other_pt_vs_eval->ProjectionX("MVA_IP3D_Other_pt_eval_Xproj_8", lim_pt400, lim_pt500);

	TH1D *MVA_IP3D_abseta_eval_Xproj_0 = MVA_IP3D_abseta_vs_eval->ProjectionX("MVA_IP3D_abseta_eval_Xproj_0");
	TH1D *MVA_IP3D_abseta_eval_Xproj_1 = MVA_IP3D_abseta_vs_eval->ProjectionX("MVA_IP3D_abseta_eval_Xproj_1", 0, 10);
	TH1D *MVA_IP3D_abseta_eval_Xproj_2 = MVA_IP3D_abseta_vs_eval->ProjectionX("MVA_IP3D_abseta_eval_Xproj_2", 11, 20);
	TH1D *MVA_IP3D_abseta_eval_Xproj_3 = MVA_IP3D_abseta_vs_eval->ProjectionX("MVA_IP3D_abseta_eval_Xproj_3", 21, MVA_IP3D_abseta_vs_eval->GetNbinsX()+1);
	TH1D *MVA_IP3D_SIGNAL_abseta_eval_Xproj_0 = MVA_IP3D_SIGNAL_abseta_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_abseta_eval_Xproj_0");
	TH1D *MVA_IP3D_SIGNAL_abseta_eval_Xproj_1 = MVA_IP3D_SIGNAL_abseta_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_abseta_eval_Xproj_1", 0, 10);
	TH1D *MVA_IP3D_SIGNAL_abseta_eval_Xproj_2 = MVA_IP3D_SIGNAL_abseta_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_abseta_eval_Xproj_2", 11, 20);
	TH1D *MVA_IP3D_SIGNAL_abseta_eval_Xproj_3 = MVA_IP3D_SIGNAL_abseta_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_abseta_eval_Xproj_3", 21, MVA_IP3D_SIGNAL_abseta_vs_eval->GetNbinsX()+1);
	TH1D *MVA_IP3D_Background_abseta_eval_Xproj_0 = MVA_IP3D_Background_abseta_vs_eval->ProjectionX("MVA_IP3D_Background_abseta_eval_Xproj_0");
	TH1D *MVA_IP3D_Background_abseta_eval_Xproj_1 = MVA_IP3D_Background_abseta_vs_eval->ProjectionX("MVA_IP3D_Background_abseta_eval_Xproj_1", 0, 10);
	TH1D *MVA_IP3D_Background_abseta_eval_Xproj_2 = MVA_IP3D_Background_abseta_vs_eval->ProjectionX("MVA_IP3D_Background_abseta_eval_Xproj_2", 11, 20);
	TH1D *MVA_IP3D_Background_abseta_eval_Xproj_3 = MVA_IP3D_Background_abseta_vs_eval->ProjectionX("MVA_IP3D_Background_abseta_eval_Xproj_3", 21, MVA_IP3D_Background_abseta_vs_eval->GetNbinsX()+1);
	TH1D *MVA_IP3D_Other_abseta_eval_Xproj_0 = MVA_IP3D_Other_abseta_vs_eval->ProjectionX("MVA_IP3D_Other_abseta_eval_Xproj_0");
	TH1D *MVA_IP3D_Other_abseta_eval_Xproj_1 = MVA_IP3D_Other_abseta_vs_eval->ProjectionX("MVA_IP3D_Other_abseta_eval_Xproj_1", 0, 10);
	TH1D *MVA_IP3D_Other_abseta_eval_Xproj_2 = MVA_IP3D_Other_abseta_vs_eval->ProjectionX("MVA_IP3D_Other_abseta_eval_Xproj_2", 11, 20);
	TH1D *MVA_IP3D_Other_abseta_eval_Xproj_3 = MVA_IP3D_Other_abseta_vs_eval->ProjectionX("MVA_IP3D_Other_abseta_eval_Xproj_3", 21, MVA_IP3D_SIGNAL_abseta_vs_eval->GetNbinsX()+1);

	TH1D *MVA_IP3D_phi_eval_Xproj_0 = MVA_IP3D_phi_vs_eval->ProjectionX("MVA_IP3D_phi_eval_Xproj_0");
	TH1D *MVA_IP3D_phi_eval_Xproj_1 = MVA_IP3D_phi_vs_eval->ProjectionX("MVA_IP3D_phi_eval_Xproj_1", 0, 5);
	TH1D *MVA_IP3D_phi_eval_Xproj_2 = MVA_IP3D_phi_vs_eval->ProjectionX("MVA_IP3D_phi_eval_Xproj_2", 6, 10);
	TH1D *MVA_IP3D_phi_eval_Xproj_3 = MVA_IP3D_phi_vs_eval->ProjectionX("MVA_IP3D_phi_eval_Xproj_3", 11, 15);
	TH1D *MVA_IP3D_phi_eval_Xproj_4 = MVA_IP3D_phi_vs_eval->ProjectionX("MVA_IP3D_phi_eval_Xproj_4", 16, 20);
	TH1D *MVA_IP3D_phi_eval_Xproj_5 = MVA_IP3D_phi_vs_eval->ProjectionX("MVA_IP3D_phi_eval_Xproj_5", 21, 25);
	TH1D *MVA_IP3D_phi_eval_Xproj_6 = MVA_IP3D_phi_vs_eval->ProjectionX("MVA_IP3D_phi_eval_Xproj_6", 26, MVA_IP3D_phi_vs_eval->GetNbinsX()+1);
	TH1D *MVA_IP3D_SIGNAL_phi_eval_Xproj_0 = MVA_IP3D_SIGNAL_phi_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_phi_eval_Xproj_0");
	TH1D *MVA_IP3D_SIGNAL_phi_eval_Xproj_1 = MVA_IP3D_SIGNAL_phi_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_phi_eval_Xproj_1", 0, 5);
	TH1D *MVA_IP3D_SIGNAL_phi_eval_Xproj_2 = MVA_IP3D_SIGNAL_phi_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_phi_eval_Xproj_2", 6, 10);
	TH1D *MVA_IP3D_SIGNAL_phi_eval_Xproj_3 = MVA_IP3D_SIGNAL_phi_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_phi_eval_Xproj_3", 11, 15);
	TH1D *MVA_IP3D_SIGNAL_phi_eval_Xproj_4 = MVA_IP3D_SIGNAL_phi_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_phi_eval_Xproj_4", 16, 20);
	TH1D *MVA_IP3D_SIGNAL_phi_eval_Xproj_5 = MVA_IP3D_SIGNAL_phi_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_phi_eval_Xproj_5", 21, 25);
	TH1D *MVA_IP3D_SIGNAL_phi_eval_Xproj_6 = MVA_IP3D_SIGNAL_phi_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_phi_eval_Xproj_6", 26, MVA_IP3D_phi_vs_eval->GetNbinsX()+1);
	TH1D *MVA_IP3D_Background_phi_eval_Xproj_0 = MVA_IP3D_Background_phi_vs_eval->ProjectionX("MVA_IP3D_Background_phi_eval_Xproj_0");
	TH1D *MVA_IP3D_Background_phi_eval_Xproj_1 = MVA_IP3D_Background_phi_vs_eval->ProjectionX("MVA_IP3D_Background_phi_eval_Xproj_1", 0, 5);
	TH1D *MVA_IP3D_Background_phi_eval_Xproj_2 = MVA_IP3D_Background_phi_vs_eval->ProjectionX("MVA_IP3D_Background_phi_eval_Xproj_2", 6, 10);
	TH1D *MVA_IP3D_Background_phi_eval_Xproj_3 = MVA_IP3D_Background_phi_vs_eval->ProjectionX("MVA_IP3D_Background_phi_eval_Xproj_3", 11, 15);
	TH1D *MVA_IP3D_Background_phi_eval_Xproj_4 = MVA_IP3D_Background_phi_vs_eval->ProjectionX("MVA_IP3D_Background_phi_eval_Xproj_4", 16, 20);
	TH1D *MVA_IP3D_Background_phi_eval_Xproj_5 = MVA_IP3D_Background_phi_vs_eval->ProjectionX("MVA_IP3D_Background_phi_eval_Xproj_5", 21, 25);
	TH1D *MVA_IP3D_Background_phi_eval_Xproj_6 = MVA_IP3D_Background_phi_vs_eval->ProjectionX("MVA_IP3D_Background_phi_eval_Xproj_6", 26, MVA_IP3D_phi_vs_eval->GetNbinsX()+1);
	TH1D *MVA_IP3D_Other_phi_eval_Xproj_0 = MVA_IP3D_Other_phi_vs_eval->ProjectionX("MVA_IP3D_Other_phi_eval_Xproj_0");
	TH1D *MVA_IP3D_Other_phi_eval_Xproj_1 = MVA_IP3D_Other_phi_vs_eval->ProjectionX("MVA_IP3D_Other_phi_eval_Xproj_1", 0, 5);
	TH1D *MVA_IP3D_Other_phi_eval_Xproj_2 = MVA_IP3D_Other_phi_vs_eval->ProjectionX("MVA_IP3D_Other_phi_eval_Xproj_2", 6, 10);
	TH1D *MVA_IP3D_Other_phi_eval_Xproj_3 = MVA_IP3D_Other_phi_vs_eval->ProjectionX("MVA_IP3D_Other_phi_eval_Xproj_3", 11, 15);
	TH1D *MVA_IP3D_Other_phi_eval_Xproj_4 = MVA_IP3D_Other_phi_vs_eval->ProjectionX("MVA_IP3D_Other_phi_eval_Xproj_4", 16, 20);
	TH1D *MVA_IP3D_Other_phi_eval_Xproj_5 = MVA_IP3D_Other_phi_vs_eval->ProjectionX("MVA_IP3D_Other_phi_eval_Xproj_5", 21, 25);
	TH1D *MVA_IP3D_Other_phi_eval_Xproj_6 = MVA_IP3D_Other_phi_vs_eval->ProjectionX("MVA_IP3D_Other_phi_eval_Xproj_6", 26, MVA_IP3D_phi_vs_eval->GetNbinsX()+1);

	TH1D *MVA_IP3D_centzone_eval_Xproj_0 = MVA_IP3D_centzone_vs_eval->ProjectionX("MVA_IP3D_centzone_eval_Xproj_0");
	TH1D *MVA_IP3D_centzone_eval_Xproj_1 = MVA_IP3D_centzone_vs_eval->ProjectionX("MVA_IP3D_centzone_eval_Xproj_1", 3, 4);
	TH1D *MVA_IP3D_centzone_eval_Xproj_2 = MVA_IP3D_centzone_vs_eval->ProjectionX("MVA_IP3D_centzone_eval_Xproj_2", 5, 6);
	TH1D *MVA_IP3D_centzone_eval_Xproj_3 = MVA_IP3D_centzone_vs_eval->ProjectionX("MVA_IP3D_centzone_eval_Xproj_3", 7, 8);
	TH1D *MVA_IP3D_centzone_eval_Xproj_4 = MVA_IP3D_centzone_vs_eval->ProjectionX("MVA_IP3D_centzone_eval_Xproj_4", 9, 10);
	TH1D *MVA_IP3D_centzone_eval_Xproj_5 = MVA_IP3D_centzone_vs_eval->ProjectionX("MVA_IP3D_centzone_eval_Xproj_5", 11, 12);
	TH1D *MVA_IP3D_SIGNAL_centzone_eval_Xproj_0 = MVA_IP3D_SIGNAL_centzone_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_centzone_eval_Xproj_0");
	TH1D *MVA_IP3D_SIGNAL_centzone_eval_Xproj_1 = MVA_IP3D_SIGNAL_centzone_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_centzone_eval_Xproj_1", 3, 4);
	TH1D *MVA_IP3D_SIGNAL_centzone_eval_Xproj_2 = MVA_IP3D_SIGNAL_centzone_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_centzone_eval_Xproj_2", 5, 6);
	TH1D *MVA_IP3D_SIGNAL_centzone_eval_Xproj_3 = MVA_IP3D_SIGNAL_centzone_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_centzone_eval_Xproj_3", 7, 8);
	TH1D *MVA_IP3D_SIGNAL_centzone_eval_Xproj_4 = MVA_IP3D_SIGNAL_centzone_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_centzone_eval_Xproj_4", 9, 10);
	TH1D *MVA_IP3D_SIGNAL_centzone_eval_Xproj_5 = MVA_IP3D_SIGNAL_centzone_vs_eval->ProjectionX("MVA_IP3D_SIGNAL_centzone_eval_Xproj_5", 11, 12);
	TH1D *MVA_IP3D_Background_centzone_eval_Xproj_0 = MVA_IP3D_Background_centzone_vs_eval->ProjectionX("MVA_IP3D_Background_centzone_eval_Xproj_0");
	TH1D *MVA_IP3D_Background_centzone_eval_Xproj_1 = MVA_IP3D_Background_centzone_vs_eval->ProjectionX("MVA_IP3D_Background_centzone_eval_Xproj_1", 3, 4);
	TH1D *MVA_IP3D_Background_centzone_eval_Xproj_2 = MVA_IP3D_Background_centzone_vs_eval->ProjectionX("MVA_IP3D_Background_centzone_eval_Xproj_2", 5, 6);
	TH1D *MVA_IP3D_Background_centzone_eval_Xproj_3 = MVA_IP3D_Background_centzone_vs_eval->ProjectionX("MVA_IP3D_Background_centzone_eval_Xproj_3", 7, 8);
	TH1D *MVA_IP3D_Background_centzone_eval_Xproj_4 = MVA_IP3D_Background_centzone_vs_eval->ProjectionX("MVA_IP3D_Background_centzone_eval_Xproj_4", 9, 10);
	TH1D *MVA_IP3D_Background_centzone_eval_Xproj_5 = MVA_IP3D_Background_centzone_vs_eval->ProjectionX("MVA_IP3D_Background_centzone_eval_Xproj_5", 11, 12);
	TH1D *MVA_IP3D_Other_centzone_eval_Xproj_0 = MVA_IP3D_Other_centzone_vs_eval->ProjectionX("MVA_IP3D_Other_centzone_eval_Xproj_0");
	TH1D *MVA_IP3D_Other_centzone_eval_Xproj_1 = MVA_IP3D_Other_centzone_vs_eval->ProjectionX("MVA_IP3D_Other_centzone_eval_Xproj_1", 3, 4);
	TH1D *MVA_IP3D_Other_centzone_eval_Xproj_2 = MVA_IP3D_Other_centzone_vs_eval->ProjectionX("MVA_IP3D_Other_centzone_eval_Xproj_2", 5, 6);
	TH1D *MVA_IP3D_Other_centzone_eval_Xproj_3 = MVA_IP3D_Other_centzone_vs_eval->ProjectionX("MVA_IP3D_Other_centzone_eval_Xproj_3", 7, 8);
	TH1D *MVA_IP3D_Other_centzone_eval_Xproj_4 = MVA_IP3D_Other_centzone_vs_eval->ProjectionX("MVA_IP3D_Other_centzone_eval_Xproj_4", 9, 10);
	TH1D *MVA_IP3D_Other_centzone_eval_Xproj_5 = MVA_IP3D_Other_centzone_vs_eval->ProjectionX("MVA_IP3D_Other_centzone_eval_Xproj_5", 11, 52);

// TH2F JF projection

	TH1D *MVA_JF_pt_eval_Xproj_0 = MVA_JF_pt_vs_eval->ProjectionX("MVA_JF_pt_eval_Xproj_0");
	TH1D *MVA_JF_pt_eval_Xproj_1 = MVA_JF_pt_vs_eval->ProjectionX("MVA_JF_pt_eval_Xproj_1", lim_pt100, lim_pt120);
	TH1D *MVA_JF_pt_eval_Xproj_2 = MVA_JF_pt_vs_eval->ProjectionX("MVA_JF_pt_eval_Xproj_2", lim_pt120, lim_pt140);
	TH1D *MVA_JF_pt_eval_Xproj_3 = MVA_JF_pt_vs_eval->ProjectionX("MVA_JF_pt_eval_Xproj_3", lim_pt140, lim_pt160);
	TH1D *MVA_JF_pt_eval_Xproj_4 = MVA_JF_pt_vs_eval->ProjectionX("MVA_JF_pt_eval_Xproj_4", lim_pt160, lim_pt180);
	TH1D *MVA_JF_pt_eval_Xproj_5 = MVA_JF_pt_vs_eval->ProjectionX("MVA_JF_pt_eval_Xproj_5", lim_pt180, lim_pt200);
	TH1D *MVA_JF_pt_eval_Xproj_6 = MVA_JF_pt_vs_eval->ProjectionX("MVA_JF_pt_eval_Xproj_6", lim_pt200, lim_pt300);
	TH1D *MVA_JF_pt_eval_Xproj_7 = MVA_JF_pt_vs_eval->ProjectionX("MVA_JF_pt_eval_Xproj_7", lim_pt300, lim_pt400);
	TH1D *MVA_JF_pt_eval_Xproj_8 = MVA_JF_pt_vs_eval->ProjectionX("MVA_JF_pt_eval_Xproj_8", lim_pt400, lim_pt500);
	TH1D *MVA_JF_SIGNAL_pt_eval_Xproj_0 = MVA_JF_SIGNAL_pt_vs_eval->ProjectionX("MVA_JF_SIGNAL_pt_eval_Xproj_0");
	TH1D *MVA_JF_SIGNAL_pt_eval_Xproj_1 = MVA_JF_SIGNAL_pt_vs_eval->ProjectionX("MVA_JF_SIGNAL_pt_eval_Xproj_1", lim_pt100, lim_pt120);
	TH1D *MVA_JF_SIGNAL_pt_eval_Xproj_2 = MVA_JF_SIGNAL_pt_vs_eval->ProjectionX("MVA_JF_SIGNAL_pt_eval_Xproj_2", lim_pt120, lim_pt140);
	TH1D *MVA_JF_SIGNAL_pt_eval_Xproj_3 = MVA_JF_SIGNAL_pt_vs_eval->ProjectionX("MVA_JF_SIGNAL_pt_eval_Xproj_3", lim_pt140, lim_pt160);
	TH1D *MVA_JF_SIGNAL_pt_eval_Xproj_4 = MVA_JF_SIGNAL_pt_vs_eval->ProjectionX("MVA_JF_SIGNAL_pt_eval_Xproj_4", lim_pt160, lim_pt180);
	TH1D *MVA_JF_SIGNAL_pt_eval_Xproj_5 = MVA_JF_SIGNAL_pt_vs_eval->ProjectionX("MVA_JF_SIGNAL_pt_eval_Xproj_5", lim_pt180, lim_pt200);
	TH1D *MVA_JF_SIGNAL_pt_eval_Xproj_6 = MVA_JF_SIGNAL_pt_vs_eval->ProjectionX("MVA_JF_SIGNAL_pt_eval_Xproj_6", lim_pt200, lim_pt300);
	TH1D *MVA_JF_SIGNAL_pt_eval_Xproj_7 = MVA_JF_SIGNAL_pt_vs_eval->ProjectionX("MVA_JF_SIGNAL_pt_eval_Xproj_7", lim_pt300, lim_pt400);
	TH1D *MVA_JF_SIGNAL_pt_eval_Xproj_8 = MVA_JF_SIGNAL_pt_vs_eval->ProjectionX("MVA_JF_SIGNAL_pt_eval_Xproj_8", lim_pt400, lim_pt500);
	TH1D *MVA_JF_Background_pt_eval_Xproj_0 = MVA_JF_Background_pt_vs_eval->ProjectionX("MVA_JF_Background_pt_eval_Xproj_0");
	TH1D *MVA_JF_Background_pt_eval_Xproj_1 = MVA_JF_Background_pt_vs_eval->ProjectionX("MVA_JF_Background_pt_eval_Xproj_1", lim_pt100, lim_pt120);
	TH1D *MVA_JF_Background_pt_eval_Xproj_2 = MVA_JF_Background_pt_vs_eval->ProjectionX("MVA_JF_Background_pt_eval_Xproj_2", lim_pt120, lim_pt140);
	TH1D *MVA_JF_Background_pt_eval_Xproj_3 = MVA_JF_Background_pt_vs_eval->ProjectionX("MVA_JF_Background_pt_eval_Xproj_3", lim_pt140, lim_pt160);
	TH1D *MVA_JF_Background_pt_eval_Xproj_4 = MVA_JF_Background_pt_vs_eval->ProjectionX("MVA_JF_Background_pt_eval_Xproj_4", lim_pt160, lim_pt180);
	TH1D *MVA_JF_Background_pt_eval_Xproj_5 = MVA_JF_Background_pt_vs_eval->ProjectionX("MVA_JF_Background_pt_eval_Xproj_5", lim_pt180, lim_pt200);
	TH1D *MVA_JF_Background_pt_eval_Xproj_6 = MVA_JF_Background_pt_vs_eval->ProjectionX("MVA_JF_Background_pt_eval_Xproj_6", lim_pt200, lim_pt300);
	TH1D *MVA_JF_Background_pt_eval_Xproj_7 = MVA_JF_Background_pt_vs_eval->ProjectionX("MVA_JF_Background_pt_eval_Xproj_7", lim_pt300, lim_pt400);
	TH1D *MVA_JF_Background_pt_eval_Xproj_8 = MVA_JF_Background_pt_vs_eval->ProjectionX("MVA_JF_Background_pt_eval_Xproj_8", lim_pt400, lim_pt500);
	TH1D *MVA_JF_Other_pt_eval_Xproj_0 = MVA_JF_Other_pt_vs_eval->ProjectionX("MVA_JF_Other_pt_eval_Xproj_0");
	TH1D *MVA_JF_Other_pt_eval_Xproj_1 = MVA_JF_Other_pt_vs_eval->ProjectionX("MVA_JF_Other_pt_eval_Xproj_1", lim_pt100, lim_pt120);
	TH1D *MVA_JF_Other_pt_eval_Xproj_2 = MVA_JF_Other_pt_vs_eval->ProjectionX("MVA_JF_Other_pt_eval_Xproj_2", lim_pt120, lim_pt140);
	TH1D *MVA_JF_Other_pt_eval_Xproj_3 = MVA_JF_Other_pt_vs_eval->ProjectionX("MVA_JF_Other_pt_eval_Xproj_3", lim_pt140, lim_pt160);
	TH1D *MVA_JF_Other_pt_eval_Xproj_4 = MVA_JF_Other_pt_vs_eval->ProjectionX("MVA_JF_Other_pt_eval_Xproj_4", lim_pt160, lim_pt180);
	TH1D *MVA_JF_Other_pt_eval_Xproj_5 = MVA_JF_Other_pt_vs_eval->ProjectionX("MVA_JF_Other_pt_eval_Xproj_5", lim_pt180, lim_pt200);
	TH1D *MVA_JF_Other_pt_eval_Xproj_6 = MVA_JF_Other_pt_vs_eval->ProjectionX("MVA_JF_Other_pt_eval_Xproj_6", lim_pt200, lim_pt300);
	TH1D *MVA_JF_Other_pt_eval_Xproj_7 = MVA_JF_Other_pt_vs_eval->ProjectionX("MVA_JF_Other_pt_eval_Xproj_7", lim_pt300, lim_pt400);
	TH1D *MVA_JF_Other_pt_eval_Xproj_8 = MVA_JF_Other_pt_vs_eval->ProjectionX("MVA_JF_Other_pt_eval_Xproj_8", lim_pt400, lim_pt500);

	TH1D *MVA_JF_abseta_eval_Xproj_0 = MVA_JF_abseta_vs_eval->ProjectionX("MVA_JF_abseta_eval_Xproj_0");
	TH1D *MVA_JF_abseta_eval_Xproj_1 = MVA_JF_abseta_vs_eval->ProjectionX("MVA_JF_abseta_eval_Xproj_1", 0, 10);
	TH1D *MVA_JF_abseta_eval_Xproj_2 = MVA_JF_abseta_vs_eval->ProjectionX("MVA_JF_abseta_eval_Xproj_2", 11, 20);
	TH1D *MVA_JF_abseta_eval_Xproj_3 = MVA_JF_abseta_vs_eval->ProjectionX("MVA_JF_abseta_eval_Xproj_3", 21, MVA_JF_abseta_vs_eval->GetNbinsX()+1);
	TH1D *MVA_JF_SIGNAL_abseta_eval_Xproj_0 = MVA_JF_SIGNAL_abseta_vs_eval->ProjectionX("MVA_JF_SIGNAL_abseta_eval_Xproj_0");
	TH1D *MVA_JF_SIGNAL_abseta_eval_Xproj_1 = MVA_JF_SIGNAL_abseta_vs_eval->ProjectionX("MVA_JF_SIGNAL_abseta_eval_Xproj_1", 0, 10);
	TH1D *MVA_JF_SIGNAL_abseta_eval_Xproj_2 = MVA_JF_SIGNAL_abseta_vs_eval->ProjectionX("MVA_JF_SIGNAL_abseta_eval_Xproj_2", 11, 20);
	TH1D *MVA_JF_SIGNAL_abseta_eval_Xproj_3 = MVA_JF_SIGNAL_abseta_vs_eval->ProjectionX("MVA_JF_SIGNAL_abseta_eval_Xproj_3", 21, MVA_JF_SIGNAL_abseta_vs_eval->GetNbinsX()+1);
	TH1D *MVA_JF_Background_abseta_eval_Xproj_0 = MVA_JF_Background_abseta_vs_eval->ProjectionX("MVA_JF_Background_abseta_eval_Xproj_0");
	TH1D *MVA_JF_Background_abseta_eval_Xproj_1 = MVA_JF_Background_abseta_vs_eval->ProjectionX("MVA_JF_Background_abseta_eval_Xproj_1", 0, 10);
	TH1D *MVA_JF_Background_abseta_eval_Xproj_2 = MVA_JF_Background_abseta_vs_eval->ProjectionX("MVA_JF_Background_abseta_eval_Xproj_2", 11, 20);
	TH1D *MVA_JF_Background_abseta_eval_Xproj_3 = MVA_JF_Background_abseta_vs_eval->ProjectionX("MVA_JF_Background_abseta_eval_Xproj_3", 21, MVA_JF_Background_abseta_vs_eval->GetNbinsX()+1);
	TH1D *MVA_JF_Other_abseta_eval_Xproj_0 = MVA_JF_Other_abseta_vs_eval->ProjectionX("MVA_JF_Other_abseta_eval_Xproj_0");
	TH1D *MVA_JF_Other_abseta_eval_Xproj_1 = MVA_JF_Other_abseta_vs_eval->ProjectionX("MVA_JF_Other_abseta_eval_Xproj_1", 0, 10);
	TH1D *MVA_JF_Other_abseta_eval_Xproj_2 = MVA_JF_Other_abseta_vs_eval->ProjectionX("MVA_JF_Other_abseta_eval_Xproj_2", 11, 20);
	TH1D *MVA_JF_Other_abseta_eval_Xproj_3 = MVA_JF_Other_abseta_vs_eval->ProjectionX("MVA_JF_Other_abseta_eval_Xproj_3", 21, MVA_JF_SIGNAL_abseta_vs_eval->GetNbinsX()+1);

	TH1D *MVA_JF_phi_eval_Xproj_0 = MVA_JF_phi_vs_eval->ProjectionX("MVA_JF_phi_eval_Xproj_0");
	TH1D *MVA_JF_phi_eval_Xproj_1 = MVA_JF_phi_vs_eval->ProjectionX("MVA_JF_phi_eval_Xproj_1", 0, 5);
	TH1D *MVA_JF_phi_eval_Xproj_2 = MVA_JF_phi_vs_eval->ProjectionX("MVA_JF_phi_eval_Xproj_2", 6, 10);
	TH1D *MVA_JF_phi_eval_Xproj_3 = MVA_JF_phi_vs_eval->ProjectionX("MVA_JF_phi_eval_Xproj_3", 11, 15);
	TH1D *MVA_JF_phi_eval_Xproj_4 = MVA_JF_phi_vs_eval->ProjectionX("MVA_JF_phi_eval_Xproj_4", 16, 20);
	TH1D *MVA_JF_phi_eval_Xproj_5 = MVA_JF_phi_vs_eval->ProjectionX("MVA_JF_phi_eval_Xproj_5", 21, 25);
	TH1D *MVA_JF_phi_eval_Xproj_6 = MVA_JF_phi_vs_eval->ProjectionX("MVA_JF_phi_eval_Xproj_6", 26, MVA_JF_phi_vs_eval->GetNbinsX()+1);
	TH1D *MVA_JF_SIGNAL_phi_eval_Xproj_0 = MVA_JF_SIGNAL_phi_vs_eval->ProjectionX("MVA_JF_SIGNAL_phi_eval_Xproj_0");
	TH1D *MVA_JF_SIGNAL_phi_eval_Xproj_1 = MVA_JF_SIGNAL_phi_vs_eval->ProjectionX("MVA_JF_SIGNAL_phi_eval_Xproj_1", 0, 5);
	TH1D *MVA_JF_SIGNAL_phi_eval_Xproj_2 = MVA_JF_SIGNAL_phi_vs_eval->ProjectionX("MVA_JF_SIGNAL_phi_eval_Xproj_2", 6, 10);
	TH1D *MVA_JF_SIGNAL_phi_eval_Xproj_3 = MVA_JF_SIGNAL_phi_vs_eval->ProjectionX("MVA_JF_SIGNAL_phi_eval_Xproj_3", 11, 15);
	TH1D *MVA_JF_SIGNAL_phi_eval_Xproj_4 = MVA_JF_SIGNAL_phi_vs_eval->ProjectionX("MVA_JF_SIGNAL_phi_eval_Xproj_4", 16, 20);
	TH1D *MVA_JF_SIGNAL_phi_eval_Xproj_5 = MVA_JF_SIGNAL_phi_vs_eval->ProjectionX("MVA_JF_SIGNAL_phi_eval_Xproj_5", 21, 25);
	TH1D *MVA_JF_SIGNAL_phi_eval_Xproj_6 = MVA_JF_SIGNAL_phi_vs_eval->ProjectionX("MVA_JF_SIGNAL_phi_eval_Xproj_6", 26, MVA_JF_phi_vs_eval->GetNbinsX()+1);
	TH1D *MVA_JF_Background_phi_eval_Xproj_0 = MVA_JF_Background_phi_vs_eval->ProjectionX("MVA_JF_Background_phi_eval_Xproj_0");
	TH1D *MVA_JF_Background_phi_eval_Xproj_1 = MVA_JF_Background_phi_vs_eval->ProjectionX("MVA_JF_Background_phi_eval_Xproj_1", 0, 5);
	TH1D *MVA_JF_Background_phi_eval_Xproj_2 = MVA_JF_Background_phi_vs_eval->ProjectionX("MVA_JF_Background_phi_eval_Xproj_2", 6, 10);
	TH1D *MVA_JF_Background_phi_eval_Xproj_3 = MVA_JF_Background_phi_vs_eval->ProjectionX("MVA_JF_Background_phi_eval_Xproj_3", 11, 15);
	TH1D *MVA_JF_Background_phi_eval_Xproj_4 = MVA_JF_Background_phi_vs_eval->ProjectionX("MVA_JF_Background_phi_eval_Xproj_4", 16, 20);
	TH1D *MVA_JF_Background_phi_eval_Xproj_5 = MVA_JF_Background_phi_vs_eval->ProjectionX("MVA_JF_Background_phi_eval_Xproj_5", 21, 25);
	TH1D *MVA_JF_Background_phi_eval_Xproj_6 = MVA_JF_Background_phi_vs_eval->ProjectionX("MVA_JF_Background_phi_eval_Xproj_6", 26, MVA_JF_phi_vs_eval->GetNbinsX()+1);
	TH1D *MVA_JF_Other_phi_eval_Xproj_0 = MVA_JF_Other_phi_vs_eval->ProjectionX("MVA_JF_Other_phi_eval_Xproj_0");
	TH1D *MVA_JF_Other_phi_eval_Xproj_1 = MVA_JF_Other_phi_vs_eval->ProjectionX("MVA_JF_Other_phi_eval_Xproj_1", 0, 5);
	TH1D *MVA_JF_Other_phi_eval_Xproj_2 = MVA_JF_Other_phi_vs_eval->ProjectionX("MVA_JF_Other_phi_eval_Xproj_2", 6, 10);
	TH1D *MVA_JF_Other_phi_eval_Xproj_3 = MVA_JF_Other_phi_vs_eval->ProjectionX("MVA_JF_Other_phi_eval_Xproj_3", 11, 15);
	TH1D *MVA_JF_Other_phi_eval_Xproj_4 = MVA_JF_Other_phi_vs_eval->ProjectionX("MVA_JF_Other_phi_eval_Xproj_4", 16, 20);
	TH1D *MVA_JF_Other_phi_eval_Xproj_5 = MVA_JF_Other_phi_vs_eval->ProjectionX("MVA_JF_Other_phi_eval_Xproj_5", 21, 25);
	TH1D *MVA_JF_Other_phi_eval_Xproj_6 = MVA_JF_Other_phi_vs_eval->ProjectionX("MVA_JF_Other_phi_eval_Xproj_6", 26, MVA_JF_phi_vs_eval->GetNbinsX()+1);

	TH1D *MVA_JF_centzone_eval_Xproj_0 = MVA_JF_centzone_vs_eval->ProjectionX("MVA_JF_centzone_eval_Xproj_0");
	TH1D *MVA_JF_centzone_eval_Xproj_1 = MVA_JF_centzone_vs_eval->ProjectionX("MVA_JF_centzone_eval_Xproj_1", 3, 4);
	TH1D *MVA_JF_centzone_eval_Xproj_2 = MVA_JF_centzone_vs_eval->ProjectionX("MVA_JF_centzone_eval_Xproj_2", 5, 6);
	TH1D *MVA_JF_centzone_eval_Xproj_3 = MVA_JF_centzone_vs_eval->ProjectionX("MVA_JF_centzone_eval_Xproj_3", 7, 8);
	TH1D *MVA_JF_centzone_eval_Xproj_4 = MVA_JF_centzone_vs_eval->ProjectionX("MVA_JF_centzone_eval_Xproj_4", 9, 10);
	TH1D *MVA_JF_centzone_eval_Xproj_5 = MVA_JF_centzone_vs_eval->ProjectionX("MVA_JF_centzone_eval_Xproj_5", 11, 12);
	TH1D *MVA_JF_SIGNAL_centzone_eval_Xproj_0 = MVA_JF_SIGNAL_centzone_vs_eval->ProjectionX("MVA_JF_SIGNAL_centzone_eval_Xproj_0");
	TH1D *MVA_JF_SIGNAL_centzone_eval_Xproj_1 = MVA_JF_SIGNAL_centzone_vs_eval->ProjectionX("MVA_JF_SIGNAL_centzone_eval_Xproj_1", 3, 4);
	TH1D *MVA_JF_SIGNAL_centzone_eval_Xproj_2 = MVA_JF_SIGNAL_centzone_vs_eval->ProjectionX("MVA_JF_SIGNAL_centzone_eval_Xproj_2", 5, 6);
	TH1D *MVA_JF_SIGNAL_centzone_eval_Xproj_3 = MVA_JF_SIGNAL_centzone_vs_eval->ProjectionX("MVA_JF_SIGNAL_centzone_eval_Xproj_3", 7, 8);
	TH1D *MVA_JF_SIGNAL_centzone_eval_Xproj_4 = MVA_JF_SIGNAL_centzone_vs_eval->ProjectionX("MVA_JF_SIGNAL_centzone_eval_Xproj_4", 9, 10);
	TH1D *MVA_JF_SIGNAL_centzone_eval_Xproj_5 = MVA_JF_SIGNAL_centzone_vs_eval->ProjectionX("MVA_JF_SIGNAL_centzone_eval_Xproj_5", 11, 12);
	TH1D *MVA_JF_Background_centzone_eval_Xproj_0 = MVA_JF_Background_centzone_vs_eval->ProjectionX("MVA_JF_Background_centzone_eval_Xproj_0");
	TH1D *MVA_JF_Background_centzone_eval_Xproj_1 = MVA_JF_Background_centzone_vs_eval->ProjectionX("MVA_JF_Background_centzone_eval_Xproj_1", 3, 4);
	TH1D *MVA_JF_Background_centzone_eval_Xproj_2 = MVA_JF_Background_centzone_vs_eval->ProjectionX("MVA_JF_Background_centzone_eval_Xproj_2", 5, 6);
	TH1D *MVA_JF_Background_centzone_eval_Xproj_3 = MVA_JF_Background_centzone_vs_eval->ProjectionX("MVA_JF_Background_centzone_eval_Xproj_3", 7, 8);
	TH1D *MVA_JF_Background_centzone_eval_Xproj_4 = MVA_JF_Background_centzone_vs_eval->ProjectionX("MVA_JF_Background_centzone_eval_Xproj_4", 9, 10);
	TH1D *MVA_JF_Background_centzone_eval_Xproj_5 = MVA_JF_Background_centzone_vs_eval->ProjectionX("MVA_JF_Background_centzone_eval_Xproj_5", 11, 12);
	TH1D *MVA_JF_Other_centzone_eval_Xproj_0 = MVA_JF_Other_centzone_vs_eval->ProjectionX("MVA_JF_Other_centzone_eval_Xproj_0");
	TH1D *MVA_JF_Other_centzone_eval_Xproj_1 = MVA_JF_Other_centzone_vs_eval->ProjectionX("MVA_JF_Other_centzone_eval_Xproj_1", 3, 4);
	TH1D *MVA_JF_Other_centzone_eval_Xproj_2 = MVA_JF_Other_centzone_vs_eval->ProjectionX("MVA_JF_Other_centzone_eval_Xproj_2", 5, 6);
	TH1D *MVA_JF_Other_centzone_eval_Xproj_3 = MVA_JF_Other_centzone_vs_eval->ProjectionX("MVA_JF_Other_centzone_eval_Xproj_3", 7, 8);
	TH1D *MVA_JF_Other_centzone_eval_Xproj_4 = MVA_JF_Other_centzone_vs_eval->ProjectionX("MVA_JF_Other_centzone_eval_Xproj_4", 9, 10);
	TH1D *MVA_JF_Other_centzone_eval_Xproj_5 = MVA_JF_Other_centzone_vs_eval->ProjectionX("MVA_JF_Other_centzone_eval_Xproj_5", 11, 12);

// Title, Axis, Style

	MVA_IP2D_Background->SetTitle("IP2D Output");
	MVA_IP2D_Background->GetXaxis()->SetTitle("IP2D");
	MVA_IP2D_Background->GetYaxis()->SetTitle("N/N_{Total}");
	// MVA_IP2D->SetLineColor(kBlack);
	// MVA_IP2D->SetLineWidth(2);
	MVA_IP2D_SIGNAL->SetLineColor(kBlue);
	MVA_IP2D_SIGNAL->SetLineWidth(2);
	MVA_IP2D_Background->SetLineColor(kRed);
	MVA_IP2D_Background->SetLineWidth(2);
	MVA_IP2D_Other->SetLineColor(kCyan);
	MVA_IP2D_Other->SetLineWidth(2);

	MVA_IP3D_Background->SetTitle("IP3D Output");
	MVA_IP3D_Background->GetXaxis()->SetTitle("IP3D");
	MVA_IP3D_Background->GetYaxis()->SetTitle("N/N_{Total}");
	// MVA_IP3D->SetLineColor(kBlack);
	// MVA_IP3D->SetLineWidth(2);
	MVA_IP3D_SIGNAL->SetLineColor(kBlue);
	MVA_IP3D_SIGNAL->SetLineWidth(2);
	MVA_IP3D_Background->SetLineColor(kRed);
	MVA_IP3D_Background->SetLineWidth(2);
	MVA_IP3D_Other->SetLineColor(kCyan);
	MVA_IP3D_Other->SetLineWidth(2);

	MVA_JF_Background->SetTitle("JetFitter Output");
	MVA_JF_Background->GetXaxis()->SetTitle("JF");
	MVA_JF_Background->GetYaxis()->SetTitle("N/N_{Total}");
	// MVA_JF->SetLineColor(kBlack);
	// MVA_JF->SetLineWidth(2);
	MVA_JF_SIGNAL->SetLineColor(kBlue);
	MVA_JF_SIGNAL->SetLineWidth(2);
	MVA_JF_Background->SetLineColor(kRed);
	MVA_JF_Background->SetLineWidth(2);
	MVA_JF_Other->SetLineColor(kCyan);
	MVA_JF_Other->SetLineWidth(2);

	MVA_BDT_Background->SetTitle("BDT Output");
	MVA_BDT_Background->GetXaxis()->SetTitle("BDT");
	MVA_BDT_Background->GetYaxis()->SetTitle("N/N_{Total}");
	// MVA_BDT->SetLineColor(kBlack);
	// MVA_BDT->SetLineWidth(2);
	MVA_BDT_SIGNAL->SetLineColor(kBlue);
	MVA_BDT_SIGNAL->SetLineWidth(2);
	MVA_BDT_Background->SetLineColor(kRed);
	MVA_BDT_Background->SetLineWidth(2);
	MVA_BDT_Other->SetLineColor(kCyan);
	MVA_BDT_Other->SetLineWidth(2);

	// pT
	MVA_BDT_pt_eval_Xproj_0->SetTitle("BDT: Different p_{T} cuts");
	MVA_BDT_pt_eval_Xproj_0->GetXaxis()->SetTitle("BDT");
	MVA_BDT_pt_eval_Xproj_0->GetYaxis()->SetTitle("N");
	MVA_BDT_pt_eval_Xproj_0->SetLineColor(kRed);
	MVA_BDT_pt_eval_Xproj_0->SetLineWidth(2);
	MVA_BDT_pt_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDT_pt_eval_Xproj_1->SetLineWidth(2);
	MVA_BDT_pt_eval_Xproj_2->SetLineColor(kBlack);
	MVA_BDT_pt_eval_Xproj_2->SetLineWidth(2);
	MVA_BDT_pt_eval_Xproj_3->SetLineColor(kGreen);
	MVA_BDT_pt_eval_Xproj_3->SetLineWidth(2);
	MVA_BDT_pt_eval_Xproj_4->SetLineColor(kOrange);
	MVA_BDT_pt_eval_Xproj_4->SetLineWidth(2);
	MVA_BDT_pt_eval_Xproj_5->SetLineColor(kViolet);
	MVA_BDT_pt_eval_Xproj_5->SetLineWidth(2);
	MVA_BDT_pt_eval_Xproj_6->SetLineStyle(6);
	MVA_BDT_pt_eval_Xproj_6->SetLineColor(kCyan);
	MVA_BDT_pt_eval_Xproj_6->SetLineWidth(2);
	MVA_BDT_pt_eval_Xproj_7->SetLineStyle(6);
	MVA_BDT_pt_eval_Xproj_7->SetLineColor(kMagenta-9);
	MVA_BDT_pt_eval_Xproj_7->SetLineWidth(2);
	MVA_BDT_pt_eval_Xproj_8->SetLineStyle(6);
	MVA_BDT_pt_eval_Xproj_8->SetLineColor(kYellow+2);
	MVA_BDT_pt_eval_Xproj_8->SetLineWidth(2);

	MVA_BDTSig_pt_eval_Xproj_0->SetTitle("BDT (Bottom): Different p_{T} cuts");
	MVA_BDTSig_pt_eval_Xproj_0->GetXaxis()->SetTitle("BDT");
	MVA_BDTSig_pt_eval_Xproj_0->GetYaxis()->SetTitle("N");
	MVA_BDTSig_pt_eval_Xproj_0->SetLineColor(kRed);
	MVA_BDTSig_pt_eval_Xproj_0->SetLineWidth(2);
	MVA_BDTSig_pt_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDTSig_pt_eval_Xproj_1->SetLineWidth(2);
	MVA_BDTSig_pt_eval_Xproj_2->SetLineColor(kBlack);
	MVA_BDTSig_pt_eval_Xproj_2->SetLineWidth(2);
	MVA_BDTSig_pt_eval_Xproj_3->SetLineColor(kGreen);
	MVA_BDTSig_pt_eval_Xproj_3->SetLineWidth(2);
	MVA_BDTSig_pt_eval_Xproj_4->SetLineColor(kOrange);
	MVA_BDTSig_pt_eval_Xproj_4->SetLineWidth(2);
	MVA_BDTSig_pt_eval_Xproj_5->SetLineColor(kViolet);
	MVA_BDTSig_pt_eval_Xproj_5->SetLineWidth(2);
	MVA_BDTSig_pt_eval_Xproj_6->SetLineStyle(6);
	MVA_BDTSig_pt_eval_Xproj_6->SetLineColor(kCyan);
	MVA_BDTSig_pt_eval_Xproj_6->SetLineWidth(2);
	MVA_BDTSig_pt_eval_Xproj_7->SetLineStyle(6);
	MVA_BDTSig_pt_eval_Xproj_7->SetLineColor(kMagenta-9);
	MVA_BDTSig_pt_eval_Xproj_7->SetLineWidth(2);
	MVA_BDTSig_pt_eval_Xproj_8->SetLineStyle(6);
	MVA_BDTSig_pt_eval_Xproj_8->SetLineColor(kYellow+2);
	MVA_BDTSig_pt_eval_Xproj_8->SetLineWidth(2);

	MVA_BDTBkg_pt_eval_Xproj_0->SetTitle("BDT (Light): Different p_{T} cuts");
	MVA_BDTBkg_pt_eval_Xproj_1->SetTitle("BDT: p_{T} #in [100, 120] GeV");
	MVA_BDTBkg_pt_eval_Xproj_2->SetTitle("BDT: p_{T} #in ]120, 140] GeV");
	MVA_BDTBkg_pt_eval_Xproj_3->SetTitle("BDT: p_{T} #in ]140, 160] GeV");
	MVA_BDTBkg_pt_eval_Xproj_4->SetTitle("BDT: p_{T} #in ]160, 180] GeV");
	MVA_BDTBkg_pt_eval_Xproj_5->SetTitle("BDT: p_{T} #in ]180, 200] GeV");
	MVA_BDTBkg_pt_eval_Xproj_0->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_pt_eval_Xproj_0->GetYaxis()->SetTitle("N");
	MVA_BDTBkg_pt_eval_Xproj_1->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_pt_eval_Xproj_1->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_pt_eval_Xproj_2->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_pt_eval_Xproj_2->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_pt_eval_Xproj_3->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_pt_eval_Xproj_3->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_pt_eval_Xproj_4->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_pt_eval_Xproj_4->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_pt_eval_Xproj_5->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_pt_eval_Xproj_5->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_pt_eval_Xproj_0->SetLineColor(kRed);
	MVA_BDTBkg_pt_eval_Xproj_0->SetLineWidth(2);
	MVA_BDTBkg_pt_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDTBkg_pt_eval_Xproj_1->SetLineWidth(2);
	MVA_BDTBkg_pt_eval_Xproj_2->SetLineColor(kBlack);
	MVA_BDTBkg_pt_eval_Xproj_2->SetLineWidth(2);
	MVA_BDTBkg_pt_eval_Xproj_3->SetLineColor(kGreen);
	MVA_BDTBkg_pt_eval_Xproj_3->SetLineWidth(2);
	MVA_BDTBkg_pt_eval_Xproj_4->SetLineColor(kOrange);
	MVA_BDTBkg_pt_eval_Xproj_4->SetLineWidth(2);
	MVA_BDTBkg_pt_eval_Xproj_5->SetLineColor(kViolet);
	MVA_BDTBkg_pt_eval_Xproj_5->SetLineWidth(2);
	MVA_BDTBkg_pt_eval_Xproj_6->SetLineStyle(6);
	MVA_BDTBkg_pt_eval_Xproj_6->SetLineColor(kCyan);
	MVA_BDTBkg_pt_eval_Xproj_6->SetLineWidth(2);
	MVA_BDTBkg_pt_eval_Xproj_7->SetLineStyle(6);
	MVA_BDTBkg_pt_eval_Xproj_7->SetLineColor(kMagenta-9);
	MVA_BDTBkg_pt_eval_Xproj_7->SetLineWidth(2);
	MVA_BDTBkg_pt_eval_Xproj_8->SetLineStyle(6);
	MVA_BDTBkg_pt_eval_Xproj_8->SetLineColor(kYellow+2);
	MVA_BDTBkg_pt_eval_Xproj_8->SetLineWidth(2);

	MVA_BDTOther_pt_eval_Xproj_0->SetTitle("BDT (Charm): Different p_{T} cuts");
	MVA_BDTOther_pt_eval_Xproj_0->GetXaxis()->SetTitle("BDT");
	MVA_BDTOther_pt_eval_Xproj_0->GetYaxis()->SetTitle("N");
	MVA_BDTOther_pt_eval_Xproj_0->SetLineColor(kRed);
	MVA_BDTOther_pt_eval_Xproj_0->SetLineWidth(2);
	MVA_BDTOther_pt_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDTOther_pt_eval_Xproj_1->SetLineWidth(2);
	MVA_BDTOther_pt_eval_Xproj_2->SetLineColor(kBlack);
	MVA_BDTOther_pt_eval_Xproj_2->SetLineWidth(2);
	MVA_BDTOther_pt_eval_Xproj_3->SetLineColor(kGreen);
	MVA_BDTOther_pt_eval_Xproj_3->SetLineWidth(2);
	MVA_BDTOther_pt_eval_Xproj_4->SetLineColor(kOrange);
	MVA_BDTOther_pt_eval_Xproj_4->SetLineWidth(2);
	MVA_BDTOther_pt_eval_Xproj_5->SetLineColor(kViolet);
	MVA_BDTOther_pt_eval_Xproj_5->SetLineWidth(2);
	MVA_BDTOther_pt_eval_Xproj_6->SetLineStyle(6);
	MVA_BDTOther_pt_eval_Xproj_6->SetLineColor(kCyan);
	MVA_BDTOther_pt_eval_Xproj_6->SetLineWidth(2);
	MVA_BDTOther_pt_eval_Xproj_7->SetLineStyle(6);
	MVA_BDTOther_pt_eval_Xproj_7->SetLineColor(kMagenta-9);
	MVA_BDTOther_pt_eval_Xproj_7->SetLineWidth(2);
	MVA_BDTOther_pt_eval_Xproj_8->SetLineStyle(6);
	MVA_BDTOther_pt_eval_Xproj_8->SetLineColor(kYellow+2);
	MVA_BDTOther_pt_eval_Xproj_8->SetLineWidth(2);

	// abseta
	MVA_BDT_abseta_eval_Xproj_0->SetTitle("BDT: Different |#eta| cuts");
	MVA_BDT_abseta_eval_Xproj_0->GetXaxis()->SetTitle("BDT");
	MVA_BDT_abseta_eval_Xproj_0->GetYaxis()->SetTitle("N");
	MVA_BDT_abseta_eval_Xproj_0->SetLineColor(kRed);
	MVA_BDT_abseta_eval_Xproj_0->SetLineWidth(2);
	MVA_BDT_abseta_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDT_abseta_eval_Xproj_1->SetLineWidth(2);
	MVA_BDT_abseta_eval_Xproj_2->SetLineColor(kBlack);
	MVA_BDT_abseta_eval_Xproj_2->SetLineWidth(2);
	MVA_BDT_abseta_eval_Xproj_3->SetLineColor(kGreen);
	MVA_BDT_abseta_eval_Xproj_3->SetLineWidth(2);

	MVA_BDTSig_abseta_eval_Xproj_0->SetTitle("BDT (Bottom): Different |#eta| cuts");
	MVA_BDTSig_abseta_eval_Xproj_0->GetXaxis()->SetTitle("BDT");
	MVA_BDTSig_abseta_eval_Xproj_0->GetYaxis()->SetTitle("N");
	MVA_BDTSig_abseta_eval_Xproj_0->SetLineColor(kRed);
	MVA_BDTSig_abseta_eval_Xproj_0->SetLineWidth(2);
	MVA_BDTSig_abseta_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDTSig_abseta_eval_Xproj_1->SetLineWidth(2);
	MVA_BDTSig_abseta_eval_Xproj_2->SetLineColor(kBlack);
	MVA_BDTSig_abseta_eval_Xproj_2->SetLineWidth(2);
	MVA_BDTSig_abseta_eval_Xproj_3->SetLineColor(kGreen);
	MVA_BDTSig_abseta_eval_Xproj_3->SetLineWidth(2);

	MVA_BDTBkg_abseta_eval_Xproj_0->SetTitle("BDT (Light): Different |#eta| cuts");
	MVA_BDTBkg_abseta_eval_Xproj_1->SetTitle("BDT: |#eta| #in [0, 1] ");
	MVA_BDTBkg_abseta_eval_Xproj_2->SetTitle("BDT: |#eta| #in ]1, 2] ");
	MVA_BDTBkg_abseta_eval_Xproj_3->SetTitle("BDT: |#eta| #in ]2, 2.5] ");
	MVA_BDTBkg_abseta_eval_Xproj_0->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_abseta_eval_Xproj_0->GetYaxis()->SetTitle("N");
	MVA_BDTBkg_abseta_eval_Xproj_1->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_abseta_eval_Xproj_1->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_abseta_eval_Xproj_2->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_abseta_eval_Xproj_2->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_abseta_eval_Xproj_3->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_abseta_eval_Xproj_3->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_abseta_eval_Xproj_0->SetLineColor(kRed);
	MVA_BDTBkg_abseta_eval_Xproj_0->SetLineWidth(2);
	MVA_BDTBkg_abseta_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDTBkg_abseta_eval_Xproj_1->SetLineWidth(2);
	MVA_BDTBkg_abseta_eval_Xproj_2->SetLineColor(kBlack);
	MVA_BDTBkg_abseta_eval_Xproj_2->SetLineWidth(2);
	MVA_BDTBkg_abseta_eval_Xproj_3->SetLineColor(kGreen);
	MVA_BDTBkg_abseta_eval_Xproj_3->SetLineWidth(2);

	MVA_BDTOther_abseta_eval_Xproj_0->SetTitle("BDT (Charm): Different |#eta| cuts");
	MVA_BDTOther_abseta_eval_Xproj_0->GetXaxis()->SetTitle("BDT");
	MVA_BDTOther_abseta_eval_Xproj_0->GetYaxis()->SetTitle("N");
	MVA_BDTOther_abseta_eval_Xproj_0->SetLineColor(kRed);
	MVA_BDTOther_abseta_eval_Xproj_0->SetLineWidth(2);
	MVA_BDTOther_abseta_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDTOther_abseta_eval_Xproj_1->SetLineWidth(2);
	MVA_BDTOther_abseta_eval_Xproj_2->SetLineColor(kBlack);
	MVA_BDTOther_abseta_eval_Xproj_2->SetLineWidth(2);
	MVA_BDTOther_abseta_eval_Xproj_3->SetLineColor(kGreen);
	MVA_BDTOther_abseta_eval_Xproj_3->SetLineWidth(2);

	// phi
	MVA_BDT_phi_eval_Xproj_0->SetTitle("BDT: Different #phi cuts");
	MVA_BDT_phi_eval_Xproj_0->GetXaxis()->SetTitle("BDT");
	MVA_BDT_phi_eval_Xproj_0->GetYaxis()->SetTitle("N");
	MVA_BDT_phi_eval_Xproj_0->SetLineColor(kRed);
	MVA_BDT_phi_eval_Xproj_0->SetLineWidth(2);
	MVA_BDT_phi_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDT_phi_eval_Xproj_1->SetLineWidth(2);
	MVA_BDT_phi_eval_Xproj_2->SetLineColor(kBlack);
	MVA_BDT_phi_eval_Xproj_2->SetLineWidth(2);
	MVA_BDT_phi_eval_Xproj_3->SetLineColor(kGreen);
	MVA_BDT_phi_eval_Xproj_3->SetLineWidth(2);
	MVA_BDT_phi_eval_Xproj_4->SetLineColor(kOrange);
	MVA_BDT_phi_eval_Xproj_4->SetLineWidth(2);
	MVA_BDT_phi_eval_Xproj_5->SetLineColor(kViolet);
	MVA_BDT_phi_eval_Xproj_5->SetLineWidth(2);
	MVA_BDT_phi_eval_Xproj_6->SetLineColor(kCyan);
	MVA_BDT_phi_eval_Xproj_6->SetLineWidth(2);

	MVA_BDTSig_phi_eval_Xproj_0->SetTitle("BDT (Bottom): Different #phi cuts");
	MVA_BDTSig_phi_eval_Xproj_0->GetXaxis()->SetTitle("BDT");
	MVA_BDTSig_phi_eval_Xproj_0->GetYaxis()->SetTitle("N");
	MVA_BDTSig_phi_eval_Xproj_0->SetLineColor(kRed);
	MVA_BDTSig_phi_eval_Xproj_0->SetLineWidth(2);
	MVA_BDTSig_phi_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDTSig_phi_eval_Xproj_1->SetLineWidth(2);
	MVA_BDTSig_phi_eval_Xproj_2->SetLineColor(kBlack);
	MVA_BDTSig_phi_eval_Xproj_2->SetLineWidth(2);
	MVA_BDTSig_phi_eval_Xproj_3->SetLineColor(kGreen);
	MVA_BDTSig_phi_eval_Xproj_3->SetLineWidth(2);
	MVA_BDTSig_phi_eval_Xproj_4->SetLineColor(kOrange);
	MVA_BDTSig_phi_eval_Xproj_4->SetLineWidth(2);
	MVA_BDTSig_phi_eval_Xproj_5->SetLineColor(kViolet);
	MVA_BDTSig_phi_eval_Xproj_5->SetLineWidth(2);
	MVA_BDTSig_phi_eval_Xproj_6->SetLineColor(kCyan);
	MVA_BDTSig_phi_eval_Xproj_6->SetLineWidth(2);

	MVA_BDTBkg_phi_eval_Xproj_0->SetTitle("BDT (Light): Different #phi cuts");
	MVA_BDTBkg_phi_eval_Xproj_1->SetTitle("BDT: #phi #in [- #pi, - 2#pi/3]  rad");
	MVA_BDTBkg_phi_eval_Xproj_2->SetTitle("BDT: #phi #in ]- 2#pi/3, - #pi/3]  rad");
	MVA_BDTBkg_phi_eval_Xproj_3->SetTitle("BDT: #phi #in ]- #pi/3, 0]  rad");
	MVA_BDTBkg_phi_eval_Xproj_4->SetTitle("BDT: #phi #in ] 0, #pi/3]  rad");
	MVA_BDTBkg_phi_eval_Xproj_5->SetTitle("BDT: #phi #in ] #pi/3, 2#pi/3]  rad");
	MVA_BDTBkg_phi_eval_Xproj_6->SetTitle("BDT: #phi #in ] 2#pi/3, #pi]  rad");
	MVA_BDTBkg_phi_eval_Xproj_0->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_phi_eval_Xproj_0->GetYaxis()->SetTitle("N");
	MVA_BDTBkg_phi_eval_Xproj_1->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_phi_eval_Xproj_1->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_phi_eval_Xproj_2->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_phi_eval_Xproj_2->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_phi_eval_Xproj_3->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_phi_eval_Xproj_3->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_phi_eval_Xproj_4->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_phi_eval_Xproj_4->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_phi_eval_Xproj_5->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_phi_eval_Xproj_5->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_phi_eval_Xproj_6->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_phi_eval_Xproj_6->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_phi_eval_Xproj_0->SetLineColor(kRed);
	MVA_BDTBkg_phi_eval_Xproj_0->SetLineWidth(2);
	MVA_BDTBkg_phi_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDTBkg_phi_eval_Xproj_1->SetLineWidth(2);
	MVA_BDTBkg_phi_eval_Xproj_2->SetLineColor(kBlack);
	MVA_BDTBkg_phi_eval_Xproj_2->SetLineWidth(2);
	MVA_BDTBkg_phi_eval_Xproj_3->SetLineColor(kGreen);
	MVA_BDTBkg_phi_eval_Xproj_3->SetLineWidth(2);
	MVA_BDTBkg_phi_eval_Xproj_4->SetLineColor(kOrange);
	MVA_BDTBkg_phi_eval_Xproj_4->SetLineWidth(2);
	MVA_BDTBkg_phi_eval_Xproj_5->SetLineColor(kViolet);
	MVA_BDTBkg_phi_eval_Xproj_5->SetLineWidth(2);
	MVA_BDTBkg_phi_eval_Xproj_6->SetLineColor(kCyan);
	MVA_BDTBkg_phi_eval_Xproj_6->SetLineWidth(2);

	MVA_BDTOther_phi_eval_Xproj_0->SetTitle("BDT (Charm): Different #phi cuts");
	MVA_BDTOther_phi_eval_Xproj_0->GetXaxis()->SetTitle("BDT");
	MVA_BDTOther_phi_eval_Xproj_0->GetYaxis()->SetTitle("N");
	MVA_BDTOther_phi_eval_Xproj_0->SetLineColor(kRed);
	MVA_BDTOther_phi_eval_Xproj_0->SetLineWidth(2);
	MVA_BDTOther_phi_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDTOther_phi_eval_Xproj_1->SetLineWidth(2);
	MVA_BDTOther_phi_eval_Xproj_2->SetLineColor(kBlack);
	MVA_BDTOther_phi_eval_Xproj_2->SetLineWidth(2);
	MVA_BDTOther_phi_eval_Xproj_3->SetLineColor(kGreen);
	MVA_BDTOther_phi_eval_Xproj_3->SetLineWidth(2);
	MVA_BDTOther_phi_eval_Xproj_4->SetLineColor(kOrange);
	MVA_BDTOther_phi_eval_Xproj_4->SetLineWidth(2);
	MVA_BDTOther_phi_eval_Xproj_5->SetLineColor(kViolet);
	MVA_BDTOther_phi_eval_Xproj_5->SetLineWidth(2);
	MVA_BDTOther_phi_eval_Xproj_6->SetLineColor(kCyan);
	MVA_BDTOther_phi_eval_Xproj_6->SetLineWidth(2);

	// centzone
	MVA_BDT_centzone_eval_Xproj_0->SetTitle("BDT: Different centrality cuts");
	MVA_BDT_centzone_eval_Xproj_0->GetXaxis()->SetTitle("BDT");
	MVA_BDT_centzone_eval_Xproj_0->GetYaxis()->SetTitle("N");
	MVA_BDT_centzone_eval_Xproj_0->SetLineColor(kRed);
	MVA_BDT_centzone_eval_Xproj_0->SetLineWidth(2);
	MVA_BDT_centzone_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDT_centzone_eval_Xproj_1->SetLineWidth(2);
	MVA_BDT_centzone_eval_Xproj_2->SetLineColor(kGreen);
	MVA_BDT_centzone_eval_Xproj_2->SetLineWidth(2);
	MVA_BDT_centzone_eval_Xproj_3->SetLineColor(kCyan);
	MVA_BDT_centzone_eval_Xproj_3->SetLineWidth(2);
	MVA_BDT_centzone_eval_Xproj_4->SetLineColor(kOrange);
	MVA_BDT_centzone_eval_Xproj_4->SetLineWidth(2);
	MVA_BDT_centzone_eval_Xproj_5->SetLineColor(kViolet);
	MVA_BDT_centzone_eval_Xproj_5->SetLineWidth(2);
	MVA_BDT_centzone_eval_Xproj_6->SetLineColor(kBlack);
	MVA_BDT_centzone_eval_Xproj_6->SetLineWidth(2);

	MVA_BDTSig_centzone_eval_Xproj_0->SetTitle("BDT (Bottom): Different centrality cuts");
	MVA_BDTSig_centzone_eval_Xproj_0->GetXaxis()->SetTitle("BDT");
	MVA_BDTSig_centzone_eval_Xproj_0->GetYaxis()->SetTitle("N");
	MVA_BDTSig_centzone_eval_Xproj_0->SetLineColor(kRed);
	MVA_BDTSig_centzone_eval_Xproj_0->SetLineWidth(2);
	MVA_BDTSig_centzone_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDTSig_centzone_eval_Xproj_1->SetLineWidth(2);
	MVA_BDTSig_centzone_eval_Xproj_2->SetLineColor(kGreen);
	MVA_BDTSig_centzone_eval_Xproj_2->SetLineWidth(2);
	MVA_BDTSig_centzone_eval_Xproj_3->SetLineColor(kCyan);
	MVA_BDTSig_centzone_eval_Xproj_3->SetLineWidth(2);
	MVA_BDTSig_centzone_eval_Xproj_4->SetLineColor(kOrange);
	MVA_BDTSig_centzone_eval_Xproj_4->SetLineWidth(2);
	MVA_BDTSig_centzone_eval_Xproj_5->SetLineColor(kViolet);
	MVA_BDTSig_centzone_eval_Xproj_5->SetLineWidth(2);
	MVA_BDTSig_centzone_eval_Xproj_6->SetLineColor(kBlack);
	MVA_BDTSig_centzone_eval_Xproj_6->SetLineWidth(2);

	MVA_BDTBkg_centzone_eval_Xproj_0->SetTitle("BDT (Light): Different centrality cuts");
	MVA_BDTBkg_centzone_eval_Xproj_1->SetTitle("BDT: centrality #in [0, 20] %");
	MVA_BDTBkg_centzone_eval_Xproj_2->SetTitle("BDT: centrality #in ]20, 40] %");
	MVA_BDTBkg_centzone_eval_Xproj_3->SetTitle("BDT: centrality #in ]40, 60] %");
	MVA_BDTBkg_centzone_eval_Xproj_4->SetTitle("BDT: centrality #in ]60, 80] %");
	MVA_BDTBkg_centzone_eval_Xproj_5->SetTitle("BDT: centrality #in ]80, 100] %");
	MVA_BDTBkg_centzone_eval_Xproj_6->SetTitle("BDT: centrality #in ]40, 80] %");
	MVA_BDTBkg_centzone_eval_Xproj_0->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_centzone_eval_Xproj_0->GetYaxis()->SetTitle("N");
	MVA_BDTBkg_centzone_eval_Xproj_1->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_centzone_eval_Xproj_1->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_centzone_eval_Xproj_2->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_centzone_eval_Xproj_2->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_centzone_eval_Xproj_3->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_centzone_eval_Xproj_3->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_centzone_eval_Xproj_4->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_centzone_eval_Xproj_4->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_centzone_eval_Xproj_5->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_centzone_eval_Xproj_5->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_centzone_eval_Xproj_6->GetXaxis()->SetTitle("BDT");
	MVA_BDTBkg_centzone_eval_Xproj_6->GetYaxis()->SetTitle("N/N_{Total}");
	MVA_BDTBkg_centzone_eval_Xproj_0->SetLineColor(kRed);
	MVA_BDTBkg_centzone_eval_Xproj_0->SetLineWidth(2);
	MVA_BDTBkg_centzone_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDTBkg_centzone_eval_Xproj_1->SetLineWidth(2);
	MVA_BDTBkg_centzone_eval_Xproj_2->SetLineColor(kGreen);
	MVA_BDTBkg_centzone_eval_Xproj_2->SetLineWidth(2);
	MVA_BDTBkg_centzone_eval_Xproj_3->SetLineColor(kCyan);
	MVA_BDTBkg_centzone_eval_Xproj_3->SetLineWidth(2);
	MVA_BDTBkg_centzone_eval_Xproj_4->SetLineColor(kOrange);
	MVA_BDTBkg_centzone_eval_Xproj_4->SetLineWidth(2);
	MVA_BDTBkg_centzone_eval_Xproj_5->SetLineColor(kViolet);
	MVA_BDTBkg_centzone_eval_Xproj_5->SetLineWidth(2);
	MVA_BDTBkg_centzone_eval_Xproj_6->SetLineColor(kBlack);
	MVA_BDTBkg_centzone_eval_Xproj_6->SetLineWidth(2);

	MVA_BDTOther_centzone_eval_Xproj_0->SetTitle("BDT (Charm): Different centrality cuts");
	MVA_BDTOther_centzone_eval_Xproj_0->GetXaxis()->SetTitle("BDT");
	MVA_BDTOther_centzone_eval_Xproj_0->GetYaxis()->SetTitle("N");
	MVA_BDTOther_centzone_eval_Xproj_0->SetLineColor(kRed);
	MVA_BDTOther_centzone_eval_Xproj_0->SetLineWidth(2);
	MVA_BDTOther_centzone_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDTOther_centzone_eval_Xproj_1->SetLineWidth(2);
	MVA_BDTOther_centzone_eval_Xproj_2->SetLineColor(kGreen);
	MVA_BDTOther_centzone_eval_Xproj_2->SetLineWidth(2);
	MVA_BDTOther_centzone_eval_Xproj_3->SetLineColor(kCyan);
	MVA_BDTOther_centzone_eval_Xproj_3->SetLineWidth(2);
	MVA_BDTOther_centzone_eval_Xproj_4->SetLineColor(kOrange);
	MVA_BDTOther_centzone_eval_Xproj_4->SetLineWidth(2);
	MVA_BDTOther_centzone_eval_Xproj_5->SetLineColor(kViolet);
	MVA_BDTOther_centzone_eval_Xproj_5->SetLineWidth(2);
	MVA_BDTOther_centzone_eval_Xproj_6->SetLineColor(kBlack);
	MVA_BDTOther_centzone_eval_Xproj_6->SetLineWidth(2);

	// BDT Chosen
	notchosen_pt->SetTitle("BDT Result: p_{T}");
	notchosen_pt->GetXaxis()->SetTitle("p_{T} (MeV)"); 
	notchosen_pt->GetYaxis()->SetTitle("N/N_{Total}");
	notchosen_pt->GetXaxis()->SetRange(notchosen_pt->GetXaxis()->FindBin(100000),notchosen_pt->GetXaxis()->FindBin(200000));
	chosen_pt->SetLineColor(kBlue);
	chosen_pt->SetLineWidth(2);
	notchosen_pt->SetLineColor(kRed);
	notchosen_pt->SetLineWidth(2);
	notchosen_pt_vs_centzone_0_20->SetTitle("BDT Result: p_{T} with centrality #in [0, 20] %");
	notchosen_pt_vs_centzone_0_20->GetXaxis()->SetTitle("p_{T} (MeV)"); 
	notchosen_pt_vs_centzone_0_20->GetYaxis()->SetTitle("N/N_{Total}");
	notchosen_pt_vs_centzone_0_20->GetXaxis()->SetRange(notchosen_pt_vs_centzone_0_20->GetXaxis()->FindBin(100000),notchosen_pt_vs_centzone_0_20->GetXaxis()->GetLast());
	chosen_pt_vs_centzone_0_20->SetLineColor(kBlue);
	chosen_pt_vs_centzone_0_20->SetLineWidth(2);
	notchosen_pt_vs_centzone_0_20->SetLineColor(kRed);
	notchosen_pt_vs_centzone_0_20->SetLineWidth(2);
	notchosen_pt_vs_centzone_20_40->SetTitle("BDT Result: p_{T} with centrality #in ]20, 40] %");
	notchosen_pt_vs_centzone_20_40->GetXaxis()->SetTitle("p_{T} (MeV)"); 
	notchosen_pt_vs_centzone_20_40->GetYaxis()->SetTitle("N/N_{Total}");
	notchosen_pt_vs_centzone_20_40->GetXaxis()->SetRange(notchosen_pt_vs_centzone_20_40->GetXaxis()->FindBin(100000),notchosen_pt_vs_centzone_20_40->GetXaxis()->GetLast());
	chosen_pt_vs_centzone_20_40->SetLineColor(kBlue);
	chosen_pt_vs_centzone_20_40->SetLineWidth(2);
	notchosen_pt_vs_centzone_20_40->SetLineColor(kRed);
	notchosen_pt_vs_centzone_20_40->SetLineWidth(2);
	notchosen_pt_vs_centzone_40_80->SetTitle("BDT Result: p_{T} with centrality #in ]40, 80] %");
	notchosen_pt_vs_centzone_40_80->GetXaxis()->SetTitle("p_{T} (MeV)"); 
	notchosen_pt_vs_centzone_40_80->GetYaxis()->SetTitle("N/N_{Total}");
	notchosen_pt_vs_centzone_40_80->GetXaxis()->SetRange(notchosen_pt_vs_centzone_40_80->GetXaxis()->FindBin(100000),notchosen_pt_vs_centzone_40_80->GetXaxis()->GetLast());
	chosen_pt_vs_centzone_40_80->SetLineColor(kBlue);
	chosen_pt_vs_centzone_40_80->SetLineWidth(2);
	notchosen_pt_vs_centzone_40_80->SetLineColor(kRed);
	notchosen_pt_vs_centzone_40_80->SetLineWidth(2);

// Write to output file

	MVA_IP2D->Write();
	MVA_IP2D_SIGNAL->Write();
	MVA_IP2D_Background->Write();
	MVA_IP2D_Other->Write();

	MVA_IP3D->Write();
	MVA_IP3D_SIGNAL->Write();
	MVA_IP3D_Background->Write();
	MVA_IP3D_Other->Write();

	MVA_JF->Write();
	MVA_JF_SIGNAL->Write();
	MVA_JF_Background->Write();
	MVA_JF_Other->Write();

	MVA_BDT->Write();
	MVA_BDT_SIGNAL->Write();
	MVA_BDT_Background->Write();
	MVA_BDT_Other->Write();

	MVA_BDT_pt_eval_Xproj_0->Write();
	MVA_BDT_pt_eval_Xproj_1->Write();
	MVA_BDT_pt_eval_Xproj_2->Write();
	MVA_BDT_pt_eval_Xproj_3->Write();
	MVA_BDT_pt_eval_Xproj_4->Write();
	MVA_BDT_pt_eval_Xproj_5->Write();
	MVA_BDT_pt_eval_Xproj_6->Write();
	MVA_BDT_pt_eval_Xproj_7->Write();
	MVA_BDT_pt_eval_Xproj_8->Write();

	MVA_BDTSig_pt_eval_Xproj_0->Write();
	MVA_BDTSig_pt_eval_Xproj_1->Write();
	MVA_BDTSig_pt_eval_Xproj_2->Write();
	MVA_BDTSig_pt_eval_Xproj_3->Write();
	MVA_BDTSig_pt_eval_Xproj_4->Write();
	MVA_BDTSig_pt_eval_Xproj_5->Write();
	MVA_BDTSig_pt_eval_Xproj_6->Write();
	MVA_BDTSig_pt_eval_Xproj_7->Write();
	MVA_BDTSig_pt_eval_Xproj_8->Write();
	MVA_BDTBkg_pt_eval_Xproj_0->Write();
	MVA_BDTBkg_pt_eval_Xproj_1->Write();
	MVA_BDTBkg_pt_eval_Xproj_2->Write();
	MVA_BDTBkg_pt_eval_Xproj_3->Write();
	MVA_BDTBkg_pt_eval_Xproj_4->Write();
	MVA_BDTBkg_pt_eval_Xproj_5->Write();
	MVA_BDTBkg_pt_eval_Xproj_6->Write();
	MVA_BDTBkg_pt_eval_Xproj_7->Write();
	MVA_BDTBkg_pt_eval_Xproj_8->Write();
	MVA_BDTOther_pt_eval_Xproj_0->Write();
	MVA_BDTOther_pt_eval_Xproj_1->Write();
	MVA_BDTOther_pt_eval_Xproj_2->Write();
	MVA_BDTOther_pt_eval_Xproj_3->Write();
	MVA_BDTOther_pt_eval_Xproj_4->Write();
	MVA_BDTOther_pt_eval_Xproj_5->Write();
	MVA_BDTOther_pt_eval_Xproj_6->Write();
	MVA_BDTOther_pt_eval_Xproj_7->Write();
	MVA_BDTOther_pt_eval_Xproj_8->Write();
	
	MVA_BDT_abseta_eval_Xproj_0->Write();
	MVA_BDT_abseta_eval_Xproj_1->Write();
	MVA_BDT_abseta_eval_Xproj_2->Write();
	MVA_BDT_abseta_eval_Xproj_3->Write();
	MVA_BDTSig_abseta_eval_Xproj_0->Write();
	MVA_BDTSig_abseta_eval_Xproj_1->Write();
	MVA_BDTSig_abseta_eval_Xproj_2->Write();
	MVA_BDTSig_abseta_eval_Xproj_3->Write();
	MVA_BDTBkg_abseta_eval_Xproj_0->Write();
	MVA_BDTBkg_abseta_eval_Xproj_1->Write();
	MVA_BDTBkg_abseta_eval_Xproj_2->Write();
	MVA_BDTBkg_abseta_eval_Xproj_3->Write();
	MVA_BDTOther_abseta_eval_Xproj_0->Write();
	MVA_BDTOther_abseta_eval_Xproj_1->Write();
	MVA_BDTOther_abseta_eval_Xproj_2->Write();
	MVA_BDTOther_abseta_eval_Xproj_3->Write();

	MVA_BDT_phi_eval_Xproj_0->Write();
	MVA_BDT_phi_eval_Xproj_1->Write();
	MVA_BDT_phi_eval_Xproj_2->Write();
	MVA_BDT_phi_eval_Xproj_3->Write();
	MVA_BDT_phi_eval_Xproj_4->Write();
	MVA_BDT_phi_eval_Xproj_5->Write();
	MVA_BDT_phi_eval_Xproj_6->Write();
	MVA_BDTSig_phi_eval_Xproj_0->Write();
	MVA_BDTSig_phi_eval_Xproj_1->Write();
	MVA_BDTSig_phi_eval_Xproj_2->Write();
	MVA_BDTSig_phi_eval_Xproj_3->Write();
	MVA_BDTSig_phi_eval_Xproj_4->Write();
	MVA_BDTSig_phi_eval_Xproj_5->Write();
	MVA_BDTSig_phi_eval_Xproj_6->Write();
	MVA_BDTBkg_phi_eval_Xproj_0->Write();
	MVA_BDTBkg_phi_eval_Xproj_1->Write();
	MVA_BDTBkg_phi_eval_Xproj_2->Write();
	MVA_BDTBkg_phi_eval_Xproj_3->Write();
	MVA_BDTBkg_phi_eval_Xproj_4->Write();
	MVA_BDTBkg_phi_eval_Xproj_5->Write();
	MVA_BDTBkg_phi_eval_Xproj_6->Write();
	MVA_BDTOther_phi_eval_Xproj_0->Write();
	MVA_BDTOther_phi_eval_Xproj_1->Write();
	MVA_BDTOther_phi_eval_Xproj_2->Write();
	MVA_BDTOther_phi_eval_Xproj_3->Write();
	MVA_BDTOther_phi_eval_Xproj_4->Write();
	MVA_BDTOther_phi_eval_Xproj_5->Write();
	MVA_BDTOther_phi_eval_Xproj_6->Write();

	MVA_BDT_centzone_eval_Xproj_0->Write();
	MVA_BDT_centzone_eval_Xproj_1->Write();
	MVA_BDT_centzone_eval_Xproj_2->Write();
	MVA_BDT_centzone_eval_Xproj_3->Write();
	MVA_BDT_centzone_eval_Xproj_4->Write();
	MVA_BDT_centzone_eval_Xproj_5->Write();
	MVA_BDT_centzone_eval_Xproj_6->Write();
	MVA_BDTSig_centzone_eval_Xproj_0->Write();
	MVA_BDTSig_centzone_eval_Xproj_1->Write();
	MVA_BDTSig_centzone_eval_Xproj_2->Write();
	MVA_BDTSig_centzone_eval_Xproj_3->Write();
	MVA_BDTSig_centzone_eval_Xproj_4->Write();
	MVA_BDTSig_centzone_eval_Xproj_5->Write();
	MVA_BDTSig_centzone_eval_Xproj_6->Write();
	MVA_BDTBkg_centzone_eval_Xproj_0->Write();
	MVA_BDTBkg_centzone_eval_Xproj_1->Write();
	MVA_BDTBkg_centzone_eval_Xproj_2->Write();
	MVA_BDTBkg_centzone_eval_Xproj_3->Write();
	MVA_BDTBkg_centzone_eval_Xproj_4->Write();
	MVA_BDTBkg_centzone_eval_Xproj_5->Write();
	MVA_BDTBkg_centzone_eval_Xproj_6->Write();
	MVA_BDTOther_centzone_eval_Xproj_0->Write();
	MVA_BDTOther_centzone_eval_Xproj_1->Write();
	MVA_BDTOther_centzone_eval_Xproj_2->Write();
	MVA_BDTOther_centzone_eval_Xproj_3->Write();
	MVA_BDTOther_centzone_eval_Xproj_4->Write();
	MVA_BDTOther_centzone_eval_Xproj_5->Write();
	MVA_BDTOther_centzone_eval_Xproj_6->Write();

	MVA_IP2D_pt_eval_Xproj_0->Write();
	MVA_IP2D_pt_eval_Xproj_1->Write();
	MVA_IP2D_pt_eval_Xproj_2->Write();
	MVA_IP2D_pt_eval_Xproj_3->Write();
	MVA_IP2D_pt_eval_Xproj_4->Write();
	MVA_IP2D_pt_eval_Xproj_5->Write();
	MVA_IP2D_pt_eval_Xproj_6->Write();
	MVA_IP2D_pt_eval_Xproj_7->Write();
	MVA_IP2D_pt_eval_Xproj_8->Write();

	MVA_IP2D_SIGNAL_pt_eval_Xproj_0->Write();
	MVA_IP2D_SIGNAL_pt_eval_Xproj_1->Write();
	MVA_IP2D_SIGNAL_pt_eval_Xproj_2->Write();
	MVA_IP2D_SIGNAL_pt_eval_Xproj_3->Write();
	MVA_IP2D_SIGNAL_pt_eval_Xproj_4->Write();
	MVA_IP2D_SIGNAL_pt_eval_Xproj_5->Write();
	MVA_IP2D_SIGNAL_pt_eval_Xproj_6->Write();
	MVA_IP2D_SIGNAL_pt_eval_Xproj_7->Write();
	MVA_IP2D_SIGNAL_pt_eval_Xproj_8->Write();
	MVA_IP2D_Background_pt_eval_Xproj_0->Write();
	MVA_IP2D_Background_pt_eval_Xproj_1->Write();
	MVA_IP2D_Background_pt_eval_Xproj_2->Write();
	MVA_IP2D_Background_pt_eval_Xproj_3->Write();
	MVA_IP2D_Background_pt_eval_Xproj_4->Write();
	MVA_IP2D_Background_pt_eval_Xproj_5->Write();
	MVA_IP2D_Background_pt_eval_Xproj_6->Write();
	MVA_IP2D_Background_pt_eval_Xproj_7->Write();
	MVA_IP2D_Background_pt_eval_Xproj_8->Write();
	MVA_IP2D_Other_pt_eval_Xproj_0->Write();
	MVA_IP2D_Other_pt_eval_Xproj_1->Write();
	MVA_IP2D_Other_pt_eval_Xproj_2->Write();
	MVA_IP2D_Other_pt_eval_Xproj_3->Write();
	MVA_IP2D_Other_pt_eval_Xproj_4->Write();
	MVA_IP2D_Other_pt_eval_Xproj_5->Write();
	MVA_IP2D_Other_pt_eval_Xproj_6->Write();
	MVA_IP2D_Other_pt_eval_Xproj_7->Write();
	MVA_IP2D_Other_pt_eval_Xproj_8->Write();
	
	MVA_IP2D_abseta_eval_Xproj_0->Write();
	MVA_IP2D_abseta_eval_Xproj_1->Write();
	MVA_IP2D_abseta_eval_Xproj_2->Write();
	MVA_IP2D_abseta_eval_Xproj_3->Write();
	MVA_IP2D_SIGNAL_abseta_eval_Xproj_0->Write();
	MVA_IP2D_SIGNAL_abseta_eval_Xproj_1->Write();
	MVA_IP2D_SIGNAL_abseta_eval_Xproj_2->Write();
	MVA_IP2D_SIGNAL_abseta_eval_Xproj_3->Write();
	MVA_IP2D_Background_abseta_eval_Xproj_0->Write();
	MVA_IP2D_Background_abseta_eval_Xproj_1->Write();
	MVA_IP2D_Background_abseta_eval_Xproj_2->Write();
	MVA_IP2D_Background_abseta_eval_Xproj_3->Write();
	MVA_IP2D_Other_abseta_eval_Xproj_0->Write();
	MVA_IP2D_Other_abseta_eval_Xproj_1->Write();
	MVA_IP2D_Other_abseta_eval_Xproj_2->Write();
	MVA_IP2D_Other_abseta_eval_Xproj_3->Write();

	MVA_IP2D_phi_eval_Xproj_0->Write();
	MVA_IP2D_phi_eval_Xproj_1->Write();
	MVA_IP2D_phi_eval_Xproj_2->Write();
	MVA_IP2D_phi_eval_Xproj_3->Write();
	MVA_IP2D_phi_eval_Xproj_4->Write();
	MVA_IP2D_phi_eval_Xproj_5->Write();
	MVA_IP2D_phi_eval_Xproj_6->Write();
	MVA_IP2D_SIGNAL_phi_eval_Xproj_0->Write();
	MVA_IP2D_SIGNAL_phi_eval_Xproj_1->Write();
	MVA_IP2D_SIGNAL_phi_eval_Xproj_2->Write();
	MVA_IP2D_SIGNAL_phi_eval_Xproj_3->Write();
	MVA_IP2D_SIGNAL_phi_eval_Xproj_4->Write();
	MVA_IP2D_SIGNAL_phi_eval_Xproj_5->Write();
	MVA_IP2D_SIGNAL_phi_eval_Xproj_6->Write();
	MVA_IP2D_Background_phi_eval_Xproj_0->Write();
	MVA_IP2D_Background_phi_eval_Xproj_1->Write();
	MVA_IP2D_Background_phi_eval_Xproj_2->Write();
	MVA_IP2D_Background_phi_eval_Xproj_3->Write();
	MVA_IP2D_Background_phi_eval_Xproj_4->Write();
	MVA_IP2D_Background_phi_eval_Xproj_5->Write();
	MVA_IP2D_Background_phi_eval_Xproj_6->Write();
	MVA_IP2D_Other_phi_eval_Xproj_0->Write();
	MVA_IP2D_Other_phi_eval_Xproj_1->Write();
	MVA_IP2D_Other_phi_eval_Xproj_2->Write();
	MVA_IP2D_Other_phi_eval_Xproj_3->Write();
	MVA_IP2D_Other_phi_eval_Xproj_4->Write();
	MVA_IP2D_Other_phi_eval_Xproj_5->Write();
	MVA_IP2D_Other_phi_eval_Xproj_6->Write();

	MVA_IP2D_centzone_eval_Xproj_0->Write();
	MVA_IP2D_centzone_eval_Xproj_1->Write();
	MVA_IP2D_centzone_eval_Xproj_2->Write();
	MVA_IP2D_centzone_eval_Xproj_3->Write();
	MVA_IP2D_centzone_eval_Xproj_4->Write();
	MVA_IP2D_centzone_eval_Xproj_5->Write();
	MVA_IP2D_SIGNAL_centzone_eval_Xproj_0->Write();
	MVA_IP2D_SIGNAL_centzone_eval_Xproj_1->Write();
	MVA_IP2D_SIGNAL_centzone_eval_Xproj_2->Write();
	MVA_IP2D_SIGNAL_centzone_eval_Xproj_3->Write();
	MVA_IP2D_SIGNAL_centzone_eval_Xproj_4->Write();
	MVA_IP2D_SIGNAL_centzone_eval_Xproj_5->Write();
	MVA_IP2D_Background_centzone_eval_Xproj_0->Write();
	MVA_IP2D_Background_centzone_eval_Xproj_1->Write();
	MVA_IP2D_Background_centzone_eval_Xproj_2->Write();
	MVA_IP2D_Background_centzone_eval_Xproj_3->Write();
	MVA_IP2D_Background_centzone_eval_Xproj_4->Write();
	MVA_IP2D_Background_centzone_eval_Xproj_5->Write();
	MVA_IP2D_Other_centzone_eval_Xproj_0->Write();
	MVA_IP2D_Other_centzone_eval_Xproj_1->Write();
	MVA_IP2D_Other_centzone_eval_Xproj_2->Write();
	MVA_IP2D_Other_centzone_eval_Xproj_3->Write();
	MVA_IP2D_Other_centzone_eval_Xproj_4->Write();
	MVA_IP2D_Other_centzone_eval_Xproj_5->Write();

	MVA_IP3D_pt_eval_Xproj_0->Write();
	MVA_IP3D_pt_eval_Xproj_1->Write();
	MVA_IP3D_pt_eval_Xproj_2->Write();
	MVA_IP3D_pt_eval_Xproj_3->Write();
	MVA_IP3D_pt_eval_Xproj_4->Write();
	MVA_IP3D_pt_eval_Xproj_5->Write();
	MVA_IP3D_pt_eval_Xproj_6->Write();
	MVA_IP3D_pt_eval_Xproj_7->Write();
	MVA_IP3D_pt_eval_Xproj_8->Write();

	MVA_IP3D_SIGNAL_pt_eval_Xproj_0->Write();
	MVA_IP3D_SIGNAL_pt_eval_Xproj_1->Write();
	MVA_IP3D_SIGNAL_pt_eval_Xproj_2->Write();
	MVA_IP3D_SIGNAL_pt_eval_Xproj_3->Write();
	MVA_IP3D_SIGNAL_pt_eval_Xproj_4->Write();
	MVA_IP3D_SIGNAL_pt_eval_Xproj_5->Write();
	MVA_IP3D_SIGNAL_pt_eval_Xproj_6->Write();
	MVA_IP3D_SIGNAL_pt_eval_Xproj_7->Write();
	MVA_IP3D_SIGNAL_pt_eval_Xproj_8->Write();
	MVA_IP3D_Background_pt_eval_Xproj_0->Write();
	MVA_IP3D_Background_pt_eval_Xproj_1->Write();
	MVA_IP3D_Background_pt_eval_Xproj_2->Write();
	MVA_IP3D_Background_pt_eval_Xproj_3->Write();
	MVA_IP3D_Background_pt_eval_Xproj_4->Write();
	MVA_IP3D_Background_pt_eval_Xproj_5->Write();
	MVA_IP3D_Background_pt_eval_Xproj_6->Write();
	MVA_IP3D_Background_pt_eval_Xproj_7->Write();
	MVA_IP3D_Background_pt_eval_Xproj_8->Write();
	MVA_IP3D_Other_pt_eval_Xproj_0->Write();
	MVA_IP3D_Other_pt_eval_Xproj_1->Write();
	MVA_IP3D_Other_pt_eval_Xproj_2->Write();
	MVA_IP3D_Other_pt_eval_Xproj_3->Write();
	MVA_IP3D_Other_pt_eval_Xproj_4->Write();
	MVA_IP3D_Other_pt_eval_Xproj_5->Write();
	MVA_IP3D_Other_pt_eval_Xproj_6->Write();
	MVA_IP3D_Other_pt_eval_Xproj_7->Write();
	MVA_IP3D_Other_pt_eval_Xproj_8->Write();
	
	MVA_IP3D_abseta_eval_Xproj_0->Write();
	MVA_IP3D_abseta_eval_Xproj_1->Write();
	MVA_IP3D_abseta_eval_Xproj_2->Write();
	MVA_IP3D_abseta_eval_Xproj_3->Write();
	MVA_IP3D_SIGNAL_abseta_eval_Xproj_0->Write();
	MVA_IP3D_SIGNAL_abseta_eval_Xproj_1->Write();
	MVA_IP3D_SIGNAL_abseta_eval_Xproj_2->Write();
	MVA_IP3D_SIGNAL_abseta_eval_Xproj_3->Write();
	MVA_IP3D_Background_abseta_eval_Xproj_0->Write();
	MVA_IP3D_Background_abseta_eval_Xproj_1->Write();
	MVA_IP3D_Background_abseta_eval_Xproj_2->Write();
	MVA_IP3D_Background_abseta_eval_Xproj_3->Write();
	MVA_IP3D_Other_abseta_eval_Xproj_0->Write();
	MVA_IP3D_Other_abseta_eval_Xproj_1->Write();
	MVA_IP3D_Other_abseta_eval_Xproj_2->Write();
	MVA_IP3D_Other_abseta_eval_Xproj_3->Write();

	MVA_IP3D_phi_eval_Xproj_0->Write();
	MVA_IP3D_phi_eval_Xproj_1->Write();
	MVA_IP3D_phi_eval_Xproj_2->Write();
	MVA_IP3D_phi_eval_Xproj_3->Write();
	MVA_IP3D_phi_eval_Xproj_4->Write();
	MVA_IP3D_phi_eval_Xproj_5->Write();
	MVA_IP3D_phi_eval_Xproj_6->Write();
	MVA_IP3D_SIGNAL_phi_eval_Xproj_0->Write();
	MVA_IP3D_SIGNAL_phi_eval_Xproj_1->Write();
	MVA_IP3D_SIGNAL_phi_eval_Xproj_2->Write();
	MVA_IP3D_SIGNAL_phi_eval_Xproj_3->Write();
	MVA_IP3D_SIGNAL_phi_eval_Xproj_4->Write();
	MVA_IP3D_SIGNAL_phi_eval_Xproj_5->Write();
	MVA_IP3D_SIGNAL_phi_eval_Xproj_6->Write();
	MVA_IP3D_Background_phi_eval_Xproj_0->Write();
	MVA_IP3D_Background_phi_eval_Xproj_1->Write();
	MVA_IP3D_Background_phi_eval_Xproj_2->Write();
	MVA_IP3D_Background_phi_eval_Xproj_3->Write();
	MVA_IP3D_Background_phi_eval_Xproj_4->Write();
	MVA_IP3D_Background_phi_eval_Xproj_5->Write();
	MVA_IP3D_Background_phi_eval_Xproj_6->Write();
	MVA_IP3D_Other_phi_eval_Xproj_0->Write();
	MVA_IP3D_Other_phi_eval_Xproj_1->Write();
	MVA_IP3D_Other_phi_eval_Xproj_2->Write();
	MVA_IP3D_Other_phi_eval_Xproj_3->Write();
	MVA_IP3D_Other_phi_eval_Xproj_4->Write();
	MVA_IP3D_Other_phi_eval_Xproj_5->Write();
	MVA_IP3D_Other_phi_eval_Xproj_6->Write();

	MVA_IP3D_centzone_eval_Xproj_0->Write();
	MVA_IP3D_centzone_eval_Xproj_1->Write();
	MVA_IP3D_centzone_eval_Xproj_2->Write();
	MVA_IP3D_centzone_eval_Xproj_3->Write();
	MVA_IP3D_centzone_eval_Xproj_4->Write();
	MVA_IP3D_centzone_eval_Xproj_5->Write();
	MVA_IP3D_SIGNAL_centzone_eval_Xproj_0->Write();
	MVA_IP3D_SIGNAL_centzone_eval_Xproj_1->Write();
	MVA_IP3D_SIGNAL_centzone_eval_Xproj_2->Write();
	MVA_IP3D_SIGNAL_centzone_eval_Xproj_3->Write();
	MVA_IP3D_SIGNAL_centzone_eval_Xproj_4->Write();
	MVA_IP3D_SIGNAL_centzone_eval_Xproj_5->Write();
	MVA_IP3D_Background_centzone_eval_Xproj_0->Write();
	MVA_IP3D_Background_centzone_eval_Xproj_1->Write();
	MVA_IP3D_Background_centzone_eval_Xproj_2->Write();
	MVA_IP3D_Background_centzone_eval_Xproj_3->Write();
	MVA_IP3D_Background_centzone_eval_Xproj_4->Write();
	MVA_IP3D_Background_centzone_eval_Xproj_5->Write();
	MVA_IP3D_Other_centzone_eval_Xproj_0->Write();
	MVA_IP3D_Other_centzone_eval_Xproj_1->Write();
	MVA_IP3D_Other_centzone_eval_Xproj_2->Write();
	MVA_IP3D_Other_centzone_eval_Xproj_3->Write();
	MVA_IP3D_Other_centzone_eval_Xproj_4->Write();
	MVA_IP3D_Other_centzone_eval_Xproj_5->Write();

	MVA_JF_pt_eval_Xproj_0->Write();
	MVA_JF_pt_eval_Xproj_1->Write();
	MVA_JF_pt_eval_Xproj_2->Write();
	MVA_JF_pt_eval_Xproj_3->Write();
	MVA_JF_pt_eval_Xproj_4->Write();
	MVA_JF_pt_eval_Xproj_5->Write();
	MVA_JF_pt_eval_Xproj_6->Write();
	MVA_JF_pt_eval_Xproj_7->Write();
	MVA_JF_pt_eval_Xproj_8->Write();

	MVA_JF_SIGNAL_pt_eval_Xproj_0->Write();
	MVA_JF_SIGNAL_pt_eval_Xproj_1->Write();
	MVA_JF_SIGNAL_pt_eval_Xproj_2->Write();
	MVA_JF_SIGNAL_pt_eval_Xproj_3->Write();
	MVA_JF_SIGNAL_pt_eval_Xproj_4->Write();
	MVA_JF_SIGNAL_pt_eval_Xproj_5->Write();
	MVA_JF_SIGNAL_pt_eval_Xproj_6->Write();
	MVA_JF_SIGNAL_pt_eval_Xproj_7->Write();
	MVA_JF_SIGNAL_pt_eval_Xproj_8->Write();
	MVA_JF_Background_pt_eval_Xproj_0->Write();
	MVA_JF_Background_pt_eval_Xproj_1->Write();
	MVA_JF_Background_pt_eval_Xproj_2->Write();
	MVA_JF_Background_pt_eval_Xproj_3->Write();
	MVA_JF_Background_pt_eval_Xproj_4->Write();
	MVA_JF_Background_pt_eval_Xproj_5->Write();
	MVA_JF_Background_pt_eval_Xproj_6->Write();
	MVA_JF_Background_pt_eval_Xproj_7->Write();
	MVA_JF_Background_pt_eval_Xproj_8->Write();
	MVA_JF_Other_pt_eval_Xproj_0->Write();
	MVA_JF_Other_pt_eval_Xproj_1->Write();
	MVA_JF_Other_pt_eval_Xproj_2->Write();
	MVA_JF_Other_pt_eval_Xproj_3->Write();
	MVA_JF_Other_pt_eval_Xproj_4->Write();
	MVA_JF_Other_pt_eval_Xproj_5->Write();
	MVA_JF_Other_pt_eval_Xproj_6->Write();
	MVA_JF_Other_pt_eval_Xproj_7->Write();
	MVA_JF_Other_pt_eval_Xproj_8->Write();
	
	MVA_JF_abseta_eval_Xproj_0->Write();
	MVA_JF_abseta_eval_Xproj_1->Write();
	MVA_JF_abseta_eval_Xproj_2->Write();
	MVA_JF_abseta_eval_Xproj_3->Write();
	MVA_JF_SIGNAL_abseta_eval_Xproj_0->Write();
	MVA_JF_SIGNAL_abseta_eval_Xproj_1->Write();
	MVA_JF_SIGNAL_abseta_eval_Xproj_2->Write();
	MVA_JF_SIGNAL_abseta_eval_Xproj_3->Write();
	MVA_JF_Background_abseta_eval_Xproj_0->Write();
	MVA_JF_Background_abseta_eval_Xproj_1->Write();
	MVA_JF_Background_abseta_eval_Xproj_2->Write();
	MVA_JF_Background_abseta_eval_Xproj_3->Write();
	MVA_JF_Other_abseta_eval_Xproj_0->Write();
	MVA_JF_Other_abseta_eval_Xproj_1->Write();
	MVA_JF_Other_abseta_eval_Xproj_2->Write();
	MVA_JF_Other_abseta_eval_Xproj_3->Write();

	MVA_JF_phi_eval_Xproj_0->Write();
	MVA_JF_phi_eval_Xproj_1->Write();
	MVA_JF_phi_eval_Xproj_2->Write();
	MVA_JF_phi_eval_Xproj_3->Write();
	MVA_JF_phi_eval_Xproj_4->Write();
	MVA_JF_phi_eval_Xproj_5->Write();
	MVA_JF_phi_eval_Xproj_6->Write();
	MVA_JF_SIGNAL_phi_eval_Xproj_0->Write();
	MVA_JF_SIGNAL_phi_eval_Xproj_1->Write();
	MVA_JF_SIGNAL_phi_eval_Xproj_2->Write();
	MVA_JF_SIGNAL_phi_eval_Xproj_3->Write();
	MVA_JF_SIGNAL_phi_eval_Xproj_4->Write();
	MVA_JF_SIGNAL_phi_eval_Xproj_5->Write();
	MVA_JF_SIGNAL_phi_eval_Xproj_6->Write();
	MVA_JF_Background_phi_eval_Xproj_0->Write();
	MVA_JF_Background_phi_eval_Xproj_1->Write();
	MVA_JF_Background_phi_eval_Xproj_2->Write();
	MVA_JF_Background_phi_eval_Xproj_3->Write();
	MVA_JF_Background_phi_eval_Xproj_4->Write();
	MVA_JF_Background_phi_eval_Xproj_5->Write();
	MVA_JF_Background_phi_eval_Xproj_6->Write();
	MVA_JF_Other_phi_eval_Xproj_0->Write();
	MVA_JF_Other_phi_eval_Xproj_1->Write();
	MVA_JF_Other_phi_eval_Xproj_2->Write();
	MVA_JF_Other_phi_eval_Xproj_3->Write();
	MVA_JF_Other_phi_eval_Xproj_4->Write();
	MVA_JF_Other_phi_eval_Xproj_5->Write();
	MVA_JF_Other_phi_eval_Xproj_6->Write();

	MVA_JF_centzone_eval_Xproj_0->Write();
	MVA_JF_centzone_eval_Xproj_1->Write();
	MVA_JF_centzone_eval_Xproj_2->Write();
	MVA_JF_centzone_eval_Xproj_3->Write();
	MVA_JF_centzone_eval_Xproj_4->Write();
	MVA_JF_centzone_eval_Xproj_5->Write();
	MVA_JF_SIGNAL_centzone_eval_Xproj_0->Write();
	MVA_JF_SIGNAL_centzone_eval_Xproj_1->Write();
	MVA_JF_SIGNAL_centzone_eval_Xproj_2->Write();
	MVA_JF_SIGNAL_centzone_eval_Xproj_3->Write();
	MVA_JF_SIGNAL_centzone_eval_Xproj_4->Write();
	MVA_JF_SIGNAL_centzone_eval_Xproj_5->Write();
	MVA_JF_Background_centzone_eval_Xproj_0->Write();
	MVA_JF_Background_centzone_eval_Xproj_1->Write();
	MVA_JF_Background_centzone_eval_Xproj_2->Write();
	MVA_JF_Background_centzone_eval_Xproj_3->Write();
	MVA_JF_Background_centzone_eval_Xproj_4->Write();
	MVA_JF_Background_centzone_eval_Xproj_5->Write();
	MVA_JF_Other_centzone_eval_Xproj_0->Write();
	MVA_JF_Other_centzone_eval_Xproj_1->Write();
	MVA_JF_Other_centzone_eval_Xproj_2->Write();
	MVA_JF_Other_centzone_eval_Xproj_3->Write();
	MVA_JF_Other_centzone_eval_Xproj_4->Write();
	MVA_JF_Other_centzone_eval_Xproj_5->Write();

	chosen_pt->Write();
	notchosen_pt->Write();
	chosen_pt_vs_centzone_0_20->Write();
	notchosen_pt_vs_centzone_0_20->Write();
	chosen_pt_vs_centzone_20_40->Write();
	notchosen_pt_vs_centzone_20_40->Write();
	chosen_pt_vs_centzone_40_80->Write();
	notchosen_pt_vs_centzone_40_80->Write();

// Normalization to 1

	chosen_pt->Scale(1./chosen_pt->Integral());
	notchosen_pt->Scale(1./notchosen_pt->Integral());
	if (!pp_flag) {
		chosen_pt_vs_centzone_0_20->Scale(1./chosen_pt_vs_centzone_0_20->Integral());
		notchosen_pt_vs_centzone_0_20->Scale(1./notchosen_pt_vs_centzone_0_20->Integral());
		chosen_pt_vs_centzone_20_40->Scale(1./chosen_pt_vs_centzone_20_40->Integral());
		notchosen_pt_vs_centzone_20_40->Scale(1./notchosen_pt_vs_centzone_20_40->Integral());
		chosen_pt_vs_centzone_40_80->Scale(1./chosen_pt_vs_centzone_40_80->Integral());
		notchosen_pt_vs_centzone_40_80->Scale(1./notchosen_pt_vs_centzone_40_80->Integral());
	}

// Draw, Legend

	MVA_IP2D_Background->Scale(1./MVA_IP2D_Background->Integral());
	MVA_IP2D_Other->Scale(1./MVA_IP2D_Other->Integral());
	MVA_IP2D_SIGNAL->Scale(1./MVA_IP2D_SIGNAL->Integral());

	MVA_IP2D_Background->Draw();
	MVA_IP2D_Other->Draw("same");
	MVA_IP2D_SIGNAL->Draw("same");

	leg->Draw();

	c1->SetLogy(0);
	MVA_IP2D_Background->SetMinimum(0.);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/mva_ip2d_sig_bkg.png");

	MVA_IP3D_Background->Scale(1./MVA_IP3D_Background->Integral());
	MVA_IP3D_Other->Scale(1./MVA_IP3D_Other->Integral());
	MVA_IP3D_SIGNAL->Scale(1./MVA_IP3D_SIGNAL->Integral());

	MVA_IP3D_Background->Draw();
	MVA_IP3D_Other->Draw("same");
	MVA_IP3D_SIGNAL->Draw("same");
	
	leg->Draw();

	c1->SetLogy(0);
	MVA_IP3D_Background->SetMinimum(0.);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/mva_ip3d_sig_bkg.png");

	MVA_JF_Background->Scale(1./MVA_JF_Background->Integral());
	MVA_JF_Other->Scale(1./MVA_JF_Other->Integral());
	MVA_JF_SIGNAL->Scale(1./MVA_JF_SIGNAL->Integral());

	MVA_JF_Background->Draw();
	MVA_JF_Other->Draw("same");
	MVA_JF_SIGNAL->Draw("same");
	
	leg->Draw();

	c1->SetLogy(0);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/mva_jf_sig_bkg.png");

	MVA_BDT_Background->Scale(1./MVA_BDT_Background->Integral());
	MVA_BDT_Other->Scale(1./MVA_BDT_Other->Integral());
	MVA_BDT_SIGNAL->Scale(1./MVA_BDT_SIGNAL->Integral());
	
	MVA_BDT_Background->Draw();
	MVA_BDT_Other->Draw("same");
	MVA_BDT_SIGNAL->Draw("same");
	
	leg->Draw();

	c1->SetLogy(0);
	MVA_BDT_Background->SetMinimum(0.);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/mva_bdt_sig_bkg.png");
	
    // pT
	// MVA_BDT_pt_eval_Xproj_0->Draw();
	// MVA_BDT_pt_eval_Xproj_1->Draw("same");
	// MVA_BDT_pt_eval_Xproj_2->Draw("same");
	// MVA_BDT_pt_eval_Xproj_3->Draw("same");
	// MVA_BDT_pt_eval_Xproj_4->Draw("same");
	// MVA_BDT_pt_eval_Xproj_5->Draw("same");
	// if (pp_flag) {
	// 	MVA_BDT_pt_eval_Xproj_6->Draw("same");
	// 	MVA_BDT_pt_eval_Xproj_7->Draw("same");
	// 	MVA_BDT_pt_eval_Xproj_8->Draw("same");
	// }
	// MVA_BDT_pt_eval_Xproj_0->Draw("same");

	// leg->Clear();
	// leg->SetX1NDC(0.61);
	// leg->SetY1NDC(0.66);
	// leg->AddEntry(MVA_BDT_pt_eval_Xproj_0, "All",                   "l");
	// leg->AddEntry(MVA_BDT_pt_eval_Xproj_1, "100 < p_{T} < 120 GeV", "l");
	// leg->AddEntry(MVA_BDT_pt_eval_Xproj_2, "120 < p_{T} < 140 GeV", "l");
	// leg->AddEntry(MVA_BDT_pt_eval_Xproj_3, "140 < p_{T} < 160 GeV", "l");
	// leg->AddEntry(MVA_BDT_pt_eval_Xproj_4, "160 < p_{T} < 180 GeV", "l");
	// leg->AddEntry(MVA_BDT_pt_eval_Xproj_5, "180 < p_{T} < 200 GeV", "l");
	// if (pp_flag) {
	// 	leg->AddEntry(MVA_BDT_pt_eval_Xproj_6, "200 < p_{T} < 300 GeV", "l");
	// 	leg->AddEntry(MVA_BDT_pt_eval_Xproj_7, "300 < p_{T} < 400 GeV", "l");
	// 	leg->AddEntry(MVA_BDT_pt_eval_Xproj_8, "400 < p_{T} < 500 GeV", "l");
	// }

	// leg->Draw();

	// c1->SetLogy(0);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdt_pt_eval_x.png");

	// MVA_BDTSig_pt_eval_Xproj_0->Draw();
	// MVA_BDTSig_pt_eval_Xproj_1->Draw("same");
	// MVA_BDTSig_pt_eval_Xproj_2->Draw("same");
	// MVA_BDTSig_pt_eval_Xproj_3->Draw("same");
	// MVA_BDTSig_pt_eval_Xproj_4->Draw("same");
	// MVA_BDTSig_pt_eval_Xproj_5->Draw("same");
	// if (pp_flag) {
	// 	MVA_BDTSig_pt_eval_Xproj_6->Draw("same");
	// 	MVA_BDTSig_pt_eval_Xproj_7->Draw("same");
	// 	MVA_BDTSig_pt_eval_Xproj_8->Draw("same");
	// }
	// MVA_BDTSig_pt_eval_Xproj_0->Draw("same");
	
	// leg->Draw();

	// c1->SetLogy(0);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdtsig_pt_eval_x.png");

	// MVA_BDTBkg_pt_eval_Xproj_0->Draw();
	// MVA_BDTBkg_pt_eval_Xproj_1->Draw("same");
	// MVA_BDTBkg_pt_eval_Xproj_2->Draw("same");
	// MVA_BDTBkg_pt_eval_Xproj_3->Draw("same");
	// MVA_BDTBkg_pt_eval_Xproj_4->Draw("same");
	// MVA_BDTBkg_pt_eval_Xproj_5->Draw("same");
	// if (pp_flag) {
	// 	MVA_BDTBkg_pt_eval_Xproj_6->Draw("same");
	// 	MVA_BDTBkg_pt_eval_Xproj_7->Draw("same");
	// 	MVA_BDTBkg_pt_eval_Xproj_8->Draw("same");
	// }
	// MVA_BDTBkg_pt_eval_Xproj_0->Draw("same");

	// leg->Draw();

	// c1->SetLogy(0);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdtbkg_pt_eval_x.png");

	// MVA_BDTOther_pt_eval_Xproj_0->Draw();
	// MVA_BDTOther_pt_eval_Xproj_1->Draw("same");
	// MVA_BDTOther_pt_eval_Xproj_2->Draw("same");
	// MVA_BDTOther_pt_eval_Xproj_3->Draw("same");
	// MVA_BDTOther_pt_eval_Xproj_4->Draw("same");
	// MVA_BDTOther_pt_eval_Xproj_5->Draw("same");
	// if (pp_flag) {
	// 	MVA_BDTOther_pt_eval_Xproj_6->Draw("same");
	// 	MVA_BDTOther_pt_eval_Xproj_7->Draw("same");
	// 	MVA_BDTOther_pt_eval_Xproj_8->Draw("same");
	// }
	// MVA_BDTOther_pt_eval_Xproj_0->Draw("same");

	// leg->Draw();

	// c1->SetLogy(0);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdtother_pt_eval_x.png");

    // pT cuts
	MVA_BDTSig_pt_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDTBkg_pt_eval_Xproj_1->SetLineColor(kRed);
	MVA_BDTOther_pt_eval_Xproj_1->SetLineColor(kCyan);
	
	MVA_BDTSig_pt_eval_Xproj_1->Scale(1/MVA_BDTSig_pt_eval_Xproj_1->Integral());
	MVA_BDTBkg_pt_eval_Xproj_1->Scale(1/MVA_BDTBkg_pt_eval_Xproj_1->Integral());
	MVA_BDTOther_pt_eval_Xproj_1->Scale(1/MVA_BDTOther_pt_eval_Xproj_1->Integral());
	
	MVA_BDTBkg_pt_eval_Xproj_1->Draw();
	MVA_BDTSig_pt_eval_Xproj_1->Draw("same");
	MVA_BDTOther_pt_eval_Xproj_1->Draw("same"); 

	leg->Clear();
	leg->SetX1NDC(0.72);
	leg->SetY1NDC(0.75);
	leg->AddEntry(MVA_BDTSig_pt_eval_Xproj_1,   "Bottom Jets", "l");
	leg->AddEntry(MVA_BDTBkg_pt_eval_Xproj_1,   "Light Jets",  "l");
	leg->AddEntry(MVA_BDTOther_pt_eval_Xproj_1, "Charm Jets",  "l");
	leg->Draw();

	c1->SetLogy(0);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/mva_bdt_pt1_eval_x.png");

	MVA_BDTSig_pt_eval_Xproj_2->SetLineColor(kBlue);
	MVA_BDTBkg_pt_eval_Xproj_2->SetLineColor(kRed);
	MVA_BDTOther_pt_eval_Xproj_2->SetLineColor(kCyan);

	MVA_BDTSig_pt_eval_Xproj_2->Scale(1/MVA_BDTSig_pt_eval_Xproj_2->Integral());
	MVA_BDTBkg_pt_eval_Xproj_2->Scale(1/MVA_BDTBkg_pt_eval_Xproj_2->Integral());
	MVA_BDTOther_pt_eval_Xproj_2->Scale(1/MVA_BDTOther_pt_eval_Xproj_2->Integral());

	MVA_BDTBkg_pt_eval_Xproj_2->Draw();
	MVA_BDTSig_pt_eval_Xproj_2->Draw("same");
	MVA_BDTOther_pt_eval_Xproj_2->Draw("same"); 

	leg->Draw();

	c1->SetLogy(0);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/mva_bdt_pt2_eval_x.png");

	MVA_BDTSig_pt_eval_Xproj_3->SetLineColor(kBlue);
	MVA_BDTBkg_pt_eval_Xproj_3->SetLineColor(kRed);
	MVA_BDTOther_pt_eval_Xproj_3->SetLineColor(kCyan);

	MVA_BDTSig_pt_eval_Xproj_3->Scale(1/MVA_BDTSig_pt_eval_Xproj_3->Integral());
	MVA_BDTBkg_pt_eval_Xproj_3->Scale(1/MVA_BDTBkg_pt_eval_Xproj_3->Integral());
	MVA_BDTOther_pt_eval_Xproj_3->Scale(1/MVA_BDTOther_pt_eval_Xproj_3->Integral());

	MVA_BDTBkg_pt_eval_Xproj_3->Draw();
	MVA_BDTSig_pt_eval_Xproj_3->Draw("same");
	MVA_BDTOther_pt_eval_Xproj_3->Draw("same"); 

	leg->Draw();

	c1->SetLogy(0);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/mva_bdt_pt3_eval_x.png");

	MVA_BDTSig_pt_eval_Xproj_4->SetLineColor(kBlue);
	MVA_BDTBkg_pt_eval_Xproj_4->SetLineColor(kRed);
	MVA_BDTOther_pt_eval_Xproj_4->SetLineColor(kCyan);

	MVA_BDTSig_pt_eval_Xproj_4->Scale(1/MVA_BDTSig_pt_eval_Xproj_4->Integral());
	MVA_BDTBkg_pt_eval_Xproj_4->Scale(1/MVA_BDTBkg_pt_eval_Xproj_4->Integral());
	MVA_BDTOther_pt_eval_Xproj_4->Scale(1/MVA_BDTOther_pt_eval_Xproj_4->Integral());
	
	MVA_BDTBkg_pt_eval_Xproj_4->Draw();
	MVA_BDTSig_pt_eval_Xproj_4->Draw("same");
	MVA_BDTOther_pt_eval_Xproj_4->Draw("same"); 

	leg->Draw();

	c1->SetLogy(0);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/mva_bdt_pt4_eval_x.png");

	MVA_BDTSig_pt_eval_Xproj_5->SetLineColor(kBlue);
	MVA_BDTBkg_pt_eval_Xproj_5->SetLineColor(kRed);
	MVA_BDTOther_pt_eval_Xproj_5->SetLineColor(kCyan);

	MVA_BDTSig_pt_eval_Xproj_5->Scale(1/MVA_BDTSig_pt_eval_Xproj_5->Integral());
	MVA_BDTBkg_pt_eval_Xproj_5->Scale(1/MVA_BDTBkg_pt_eval_Xproj_5->Integral());
	MVA_BDTOther_pt_eval_Xproj_5->Scale(1/MVA_BDTOther_pt_eval_Xproj_5->Integral());
	
	MVA_BDTBkg_pt_eval_Xproj_5->Draw();
	MVA_BDTSig_pt_eval_Xproj_5->Draw("same");
	MVA_BDTOther_pt_eval_Xproj_5->Draw("same"); 
	
	leg->Draw();

	c1->SetLogy(0);
	MVA_BDTBkg_pt_eval_Xproj_5->SetMinimum(0.);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/mva_bdt_pt5_eval_x.png");       

	// abseta
	// MVA_BDT_abseta_eval_Xproj_0->Draw();
	// MVA_BDT_abseta_eval_Xproj_1->Draw("same");
	// MVA_BDT_abseta_eval_Xproj_2->Draw("same");
	// MVA_BDT_abseta_eval_Xproj_3->Draw("same");
	// MVA_BDT_abseta_eval_Xproj_0->Draw("same");

	// leg->Clear();
	// leg->SetX1NDC(0.7);
	// leg->SetY1NDC(0.72);
	// leg->AddEntry(MVA_BDT_abseta_eval_Xproj_0, "All",                "l");
	// leg->AddEntry(MVA_BDT_abseta_eval_Xproj_1, "0 < |#eta| < 1 rad", "l");
	// leg->AddEntry(MVA_BDT_abseta_eval_Xproj_2, "1 < |#eta| < 2 rad", "l");
	// leg->AddEntry(MVA_BDT_abseta_eval_Xproj_3, "2 < |#eta| < 3 rad", "l");
	// leg->Draw();

	// c1->SetLogy(0);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdt_abseta_eval_x.png");

	// MVA_BDTSig_abseta_eval_Xproj_0->Draw();
	// MVA_BDTSig_abseta_eval_Xproj_1->Draw("same");
	// MVA_BDTSig_abseta_eval_Xproj_2->Draw("same");
	// MVA_BDTSig_abseta_eval_Xproj_3->Draw("same");
	// MVA_BDTSig_abseta_eval_Xproj_0->Draw("same");

	// leg->Draw();

	// c1->SetLogy(0);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdtsig_abseta_eval_x.png");

	// MVA_BDTBkg_abseta_eval_Xproj_0->Draw();
	// MVA_BDTBkg_abseta_eval_Xproj_1->Draw("same");
	// MVA_BDTBkg_abseta_eval_Xproj_2->Draw("same");
	// MVA_BDTBkg_abseta_eval_Xproj_3->Draw("same");
	// MVA_BDTBkg_abseta_eval_Xproj_0->Draw("same");

	// leg->Draw();

	// c1->SetLogy(0);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdtbkg_abseta_eval_x.png");

	// MVA_BDTOther_abseta_eval_Xproj_0->Draw();
	// MVA_BDTOther_abseta_eval_Xproj_1->Draw("same");
	// MVA_BDTOther_abseta_eval_Xproj_2->Draw("same");
	// MVA_BDTOther_abseta_eval_Xproj_3->Draw("same");
	// MVA_BDTOther_abseta_eval_Xproj_0->Draw("same");

	// leg->Draw();

	// c1->SetLogy(0);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdtother_abseta_eval_x.png");

	// abseta cuts
	MVA_BDTSig_abseta_eval_Xproj_1->SetLineColor(kBlue);
	MVA_BDTBkg_abseta_eval_Xproj_1->SetLineColor(kRed);
	MVA_BDTOther_abseta_eval_Xproj_1->SetLineColor(kCyan);

	MVA_BDTSig_abseta_eval_Xproj_1->Scale(1/MVA_BDTSig_abseta_eval_Xproj_1->Integral());
	MVA_BDTBkg_abseta_eval_Xproj_1->Scale(1/MVA_BDTBkg_abseta_eval_Xproj_1->Integral());
	MVA_BDTOther_abseta_eval_Xproj_1->Scale(1/MVA_BDTOther_abseta_eval_Xproj_1->Integral());

	MVA_BDTBkg_abseta_eval_Xproj_1->Draw();
	MVA_BDTSig_abseta_eval_Xproj_1->Draw("same");
	MVA_BDTOther_abseta_eval_Xproj_1->Draw("same"); 

	leg->Clear();
	leg->SetX1NDC(0.72);
	leg->SetY1NDC(0.75);
	leg->AddEntry(MVA_BDTSig_abseta_eval_Xproj_1,   "Bottom Jets", "l");
	leg->AddEntry(MVA_BDTBkg_abseta_eval_Xproj_1,   "Light Jets",  "l");
	leg->AddEntry(MVA_BDTOther_abseta_eval_Xproj_1, "Charm Jets",  "l");
	leg->Draw();

	c1->SetLogy(0);
	MVA_BDTBkg_abseta_eval_Xproj_1->SetMinimum(0.);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/mva_bdt_abseta1_eval_x.png");

	MVA_BDTSig_abseta_eval_Xproj_2->SetLineColor(kBlue);
	MVA_BDTBkg_abseta_eval_Xproj_2->SetLineColor(kRed);
	MVA_BDTOther_abseta_eval_Xproj_2->SetLineColor(kCyan);

	MVA_BDTSig_abseta_eval_Xproj_2->Scale(1/MVA_BDTSig_abseta_eval_Xproj_2->Integral());
	MVA_BDTBkg_abseta_eval_Xproj_2->Scale(1/MVA_BDTBkg_abseta_eval_Xproj_2->Integral());
	MVA_BDTOther_abseta_eval_Xproj_2->Scale(1/MVA_BDTOther_abseta_eval_Xproj_2->Integral());
	
	MVA_BDTBkg_abseta_eval_Xproj_2->Draw();
	MVA_BDTSig_abseta_eval_Xproj_2->Draw("same");
	MVA_BDTOther_abseta_eval_Xproj_2->Draw("same"); 

	leg->Draw();

	c1->SetLogy(0);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/mva_bdt_abseta2_eval_x.png");

	MVA_BDTSig_abseta_eval_Xproj_3->SetLineColor(kBlue);
	MVA_BDTBkg_abseta_eval_Xproj_3->SetLineColor(kRed);
	MVA_BDTOther_abseta_eval_Xproj_3->SetLineColor(kCyan);

	MVA_BDTSig_abseta_eval_Xproj_3->Scale(1/MVA_BDTSig_abseta_eval_Xproj_3->Integral());
	MVA_BDTBkg_abseta_eval_Xproj_3->Scale(1/MVA_BDTBkg_abseta_eval_Xproj_3->Integral());
	MVA_BDTOther_abseta_eval_Xproj_3->Scale(1/MVA_BDTOther_abseta_eval_Xproj_3->Integral());

	MVA_BDTBkg_abseta_eval_Xproj_3->Draw();
	MVA_BDTSig_abseta_eval_Xproj_3->Draw("same");
	MVA_BDTOther_abseta_eval_Xproj_3->Draw("same"); 
	
	leg->Draw();

	c1->SetLogy(0);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/mva_bdt_abseta3_eval_x.png");  

	// phi
	// MVA_BDT_phi_eval_Xproj_0->Draw();
	// MVA_BDT_phi_eval_Xproj_1->Draw("same");
	// MVA_BDT_phi_eval_Xproj_2->Draw("same");
	// MVA_BDT_phi_eval_Xproj_3->Draw("same");
	// MVA_BDT_phi_eval_Xproj_4->Draw("same");
	// MVA_BDT_phi_eval_Xproj_5->Draw("same");
	// MVA_BDT_phi_eval_Xproj_6->Draw("same");
	// MVA_BDT_phi_eval_Xproj_0->Draw("same");

	// leg->Clear();
	// leg->SetX1NDC(0.69);
	// leg->SetY1NDC(0.63);
	// leg->AddEntry(MVA_BDT_phi_eval_Xproj_0, "All",                "l");
	// leg->AddEntry(MVA_BDT_phi_eval_Xproj_1, "-3 < #phi < -2 rad", "l");
	// leg->AddEntry(MVA_BDT_phi_eval_Xproj_2, "-2 < #phi < -1 rad", "l");
	// leg->AddEntry(MVA_BDT_phi_eval_Xproj_3, "-1 < #phi <  0 rad", "l");
	// leg->AddEntry(MVA_BDT_phi_eval_Xproj_4, " 0 < #phi <  1 rad", "l");
	// leg->AddEntry(MVA_BDT_phi_eval_Xproj_5, " 1 < #phi <  2 rad", "l");
	// leg->AddEntry(MVA_BDT_phi_eval_Xproj_6, " 2 < #phi <  3 rad", "l");
	// leg->Draw();

	// c1->SetLogy(0);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdt_phi_eval_x.png");

	// MVA_BDTSig_phi_eval_Xproj_0->Draw();
	// MVA_BDTSig_phi_eval_Xproj_1->Draw("same");
	// MVA_BDTSig_phi_eval_Xproj_2->Draw("same");
	// MVA_BDTSig_phi_eval_Xproj_3->Draw("same");
	// MVA_BDTSig_phi_eval_Xproj_4->Draw("same");
	// MVA_BDTSig_phi_eval_Xproj_5->Draw("same");
	// MVA_BDTSig_phi_eval_Xproj_6->Draw("same");
	// MVA_BDTSig_phi_eval_Xproj_0->Draw("same");

	// leg->Draw();

	// c1->SetLogy(0);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdtsig_phi_eval_x.png");

	// MVA_BDTBkg_phi_eval_Xproj_0->Draw();
	// MVA_BDTBkg_phi_eval_Xproj_1->Draw("same");
	// MVA_BDTBkg_phi_eval_Xproj_2->Draw("same");
	// MVA_BDTBkg_phi_eval_Xproj_3->Draw("same");
	// MVA_BDTBkg_phi_eval_Xproj_4->Draw("same");
	// MVA_BDTBkg_phi_eval_Xproj_5->Draw("same");
	// MVA_BDTBkg_phi_eval_Xproj_6->Draw("same");
	// MVA_BDTBkg_phi_eval_Xproj_0->Draw("same");

	// leg->Draw();

	// c1->SetLogy(0);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdtbkg_phi_eval_x.png");

	// MVA_BDTOther_phi_eval_Xproj_0->Draw();
	// MVA_BDTOther_phi_eval_Xproj_1->Draw("same");
	// MVA_BDTOther_phi_eval_Xproj_2->Draw("same");
	// MVA_BDTOther_phi_eval_Xproj_3->Draw("same");
	// MVA_BDTOther_phi_eval_Xproj_4->Draw("same");
	// MVA_BDTOther_phi_eval_Xproj_5->Draw("same");
	// MVA_BDTOther_phi_eval_Xproj_6->Draw("same");
	// MVA_BDTOther_phi_eval_Xproj_0->Draw("same");

	// leg->Draw();

	// c1->SetLogy(0);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdtother_phi_eval_x.png");

    // phi cuts
	// MVA_BDTSig_phi_eval_Xproj_1->SetLineColor(kBlue);
	// MVA_BDTBkg_phi_eval_Xproj_1->SetLineColor(kRed);
	// MVA_BDTOther_phi_eval_Xproj_1->SetLineColor(kCyan);

	// MVA_BDTSig_phi_eval_Xproj_1->Scale(1/MVA_BDTSig_phi_eval_Xproj_1->Integral());
	// MVA_BDTBkg_phi_eval_Xproj_1->Scale(1/MVA_BDTBkg_phi_eval_Xproj_1->Integral());
	// MVA_BDTOther_phi_eval_Xproj_1->Scale(1/MVA_BDTOther_phi_eval_Xproj_1->Integral());

	// MVA_BDTBkg_phi_eval_Xproj_1->Draw();
	// MVA_BDTSig_phi_eval_Xproj_1->Draw("same");
	// MVA_BDTOther_phi_eval_Xproj_1->Draw("same"); 

	// leg->Clear();
	// leg->SetX1NDC(0.72);
	// leg->SetY1NDC(0.75);
	// leg->AddEntry(MVA_BDTSig_phi_eval_Xproj_1,   "Bottom Jets", "l");
	// leg->AddEntry(MVA_BDTBkg_phi_eval_Xproj_1,   "Light Jets",  "l");
	// leg->AddEntry(MVA_BDTOther_phi_eval_Xproj_1, "Charm Jets",  "l");
	// leg->Draw();

	// c1->SetLogy(0);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdt_phi1_eval_x.png");

	// MVA_BDTSig_phi_eval_Xproj_2->SetLineColor(kBlue);
	// MVA_BDTBkg_phi_eval_Xproj_2->SetLineColor(kRed);
	// MVA_BDTOther_phi_eval_Xproj_2->SetLineColor(kCyan);

	// MVA_BDTSig_phi_eval_Xproj_2->Scale(1/MVA_BDTSig_phi_eval_Xproj_2->Integral());
	// MVA_BDTBkg_phi_eval_Xproj_2->Scale(1/MVA_BDTBkg_phi_eval_Xproj_2->Integral());
	// MVA_BDTOther_phi_eval_Xproj_2->Scale(1/MVA_BDTOther_phi_eval_Xproj_2->Integral());

	// MVA_BDTBkg_phi_eval_Xproj_2->Draw();
	// MVA_BDTSig_phi_eval_Xproj_2->Draw("same");
	// MVA_BDTOther_phi_eval_Xproj_2->Draw("same"); 

	// leg->Draw();

	// c1->SetLogy(0);
	// MVA_BDTBkg_phi_eval_Xproj_2->SetMinimum(0.);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdt_phi2_eval_x.png");

	// MVA_BDTSig_phi_eval_Xproj_3->SetLineColor(kBlue);
	// MVA_BDTBkg_phi_eval_Xproj_3->SetLineColor(kRed);
	// MVA_BDTOther_phi_eval_Xproj_3->SetLineColor(kCyan);

	// MVA_BDTSig_phi_eval_Xproj_3->Scale(1/MVA_BDTSig_phi_eval_Xproj_3->Integral());
	// MVA_BDTBkg_phi_eval_Xproj_3->Scale(1/MVA_BDTBkg_phi_eval_Xproj_3->Integral());
	// MVA_BDTOther_phi_eval_Xproj_3->Scale(1/MVA_BDTOther_phi_eval_Xproj_3->Integral());

	// MVA_BDTBkg_phi_eval_Xproj_3->Draw();
	// MVA_BDTSig_phi_eval_Xproj_3->Draw("same");
	// MVA_BDTOther_phi_eval_Xproj_3->Draw("same"); 

	// leg->Draw();

	// c1->SetLogy(0);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdt_phi3_eval_x.png");

	// MVA_BDTSig_phi_eval_Xproj_4->SetLineColor(kBlue);
	// MVA_BDTBkg_phi_eval_Xproj_4->SetLineColor(kRed);
	// MVA_BDTOther_phi_eval_Xproj_4->SetLineColor(kCyan);

	// MVA_BDTSig_phi_eval_Xproj_4->Scale(1/MVA_BDTSig_phi_eval_Xproj_4->Integral());
	// MVA_BDTBkg_phi_eval_Xproj_4->Scale(1/MVA_BDTBkg_phi_eval_Xproj_4->Integral());
	// MVA_BDTOther_phi_eval_Xproj_4->Scale(1/MVA_BDTOther_phi_eval_Xproj_4->Integral());

	// MVA_BDTBkg_phi_eval_Xproj_4->Draw();
	// MVA_BDTSig_phi_eval_Xproj_4->Draw("same");
	// MVA_BDTOther_phi_eval_Xproj_4->Draw("same"); 

	// leg->Draw();

	// c1->SetLogy(0);
	// MVA_BDTBkg_phi_eval_Xproj_4->SetMinimum(0.);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdt_phi4_eval_x.png");

	// MVA_BDTSig_phi_eval_Xproj_5->SetLineColor(kBlue);
	// MVA_BDTBkg_phi_eval_Xproj_5->SetLineColor(kRed);
	// MVA_BDTOther_phi_eval_Xproj_5->SetLineColor(kCyan);

	// MVA_BDTSig_phi_eval_Xproj_5->Scale(1/MVA_BDTSig_phi_eval_Xproj_5->Integral());
	// MVA_BDTBkg_phi_eval_Xproj_5->Scale(1/MVA_BDTBkg_phi_eval_Xproj_5->Integral());
	// MVA_BDTOther_phi_eval_Xproj_5->Scale(1/MVA_BDTOther_phi_eval_Xproj_5->Integral());

	// MVA_BDTBkg_phi_eval_Xproj_5->Draw();
	// MVA_BDTSig_phi_eval_Xproj_5->Draw("same");
	// MVA_BDTOther_phi_eval_Xproj_5->Draw("same"); 

	// leg->Draw();

	// c1->SetLogy(0);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdt_phi5_eval_x.png"); 

	// MVA_BDTSig_phi_eval_Xproj_6->SetLineColor(kBlue);
	// MVA_BDTBkg_phi_eval_Xproj_6->SetLineColor(kRed);
	// MVA_BDTOther_phi_eval_Xproj_6->SetLineColor(kCyan);

	// MVA_BDTSig_phi_eval_Xproj_6->Scale(1/MVA_BDTSig_phi_eval_Xproj_6->Integral());
	// MVA_BDTBkg_phi_eval_Xproj_6->Scale(1/MVA_BDTBkg_phi_eval_Xproj_6->Integral());
	// MVA_BDTOther_phi_eval_Xproj_6->Scale(1/MVA_BDTOther_phi_eval_Xproj_6->Integral());

	// MVA_BDTBkg_phi_eval_Xproj_6->Draw();
	// MVA_BDTSig_phi_eval_Xproj_6->Draw("same");
	// MVA_BDTOther_phi_eval_Xproj_6->Draw("same"); 

	// leg->Draw();

	// c1->SetLogy(0);
	// MVA_BDTBkg_phi_eval_Xproj_6->SetMinimum(0.);
	// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// c1->Print("plots/mva_bdt_phi6_eval_x.png");

    // centzone
	// if (!pp_flag) {
	// 	MVA_BDT_centzone_eval_Xproj_0->Draw();
	// 	MVA_BDT_centzone_eval_Xproj_1->Draw("same");
	// 	MVA_BDT_centzone_eval_Xproj_2->Draw("same");
	// 	// MVA_BDT_centzone_eval_Xproj_3->Draw("same");
	// 	// MVA_BDT_centzone_eval_Xproj_4->Draw("same");
	// 	// MVA_BDT_centzone_eval_Xproj_5->Draw("same");
	// 	MVA_BDT_centzone_eval_Xproj_6->Draw("same");
	// 	MVA_BDT_centzone_eval_Xproj_0->Draw("same");

	// 	leg->Clear();
	// 	leg->SetX1NDC(0.68);
	// 	leg->SetY1NDC(0.66);
	// 	leg->AddEntry(MVA_BDT_centzone_eval_Xproj_0, "All",             "l");
	// 	leg->AddEntry(MVA_BDT_centzone_eval_Xproj_1, "centzone 1 or 2", "l");
	// 	leg->AddEntry(MVA_BDT_centzone_eval_Xproj_2, "centzone 3 or 4", "l");
	// 	// leg->AddEntry(MVA_BDT_centzone_eval_Xproj_3, "centzone 5 or 6", "l");
	// 	// leg->AddEntry(MVA_BDT_centzone_eval_Xproj_4, "centzone 7 or 8", "l");
	// 	// leg->AddEntry(MVA_BDT_centzone_eval_Xproj_5, "centzone 9",      "l");
	// 	leg->AddEntry(MVA_BDT_centzone_eval_Xproj_6, "centzone 5 to 8", "l");
	// 	leg->Draw();

	// 	c1->SetLogy(0);
	// 	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// 	c1->Print("plots/mva_bdt_centzone_eval_x.png");

	// 	MVA_BDTSig_centzone_eval_Xproj_0->Draw();
	// 	MVA_BDTSig_centzone_eval_Xproj_1->Draw("same");
	// 	MVA_BDTSig_centzone_eval_Xproj_2->Draw("same");
	// 	// MVA_BDTSig_centzone_eval_Xproj_3->Draw("same");
	// 	// MVA_BDTSig_centzone_eval_Xproj_4->Draw("same");
	// 	// MVA_BDTSig_centzone_eval_Xproj_5->Draw("same");
	// 	MVA_BDTSig_centzone_eval_Xproj_6->Draw("same");
	// 	MVA_BDTSig_centzone_eval_Xproj_0->Draw("same");

	// 	leg->Draw();

	// 	c1->SetLogy(0);
	// 	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// 	c1->Print("plots/mva_bdtsig_centzone_eval_x.png");

	// 	MVA_BDTBkg_centzone_eval_Xproj_0->Draw();
	// 	MVA_BDTBkg_centzone_eval_Xproj_1->Draw("same");
	// 	MVA_BDTBkg_centzone_eval_Xproj_2->Draw("same");
	// 	// MVA_BDTBkg_centzone_eval_Xproj_3->Draw("same");
	// 	// MVA_BDTBkg_centzone_eval_Xproj_4->Draw("same");
	// 	// MVA_BDTBkg_centzone_eval_Xproj_5->Draw("same");
	// 	MVA_BDTBkg_centzone_eval_Xproj_6->Draw("same");
	// 	MVA_BDTBkg_centzone_eval_Xproj_0->Draw("same");

	// 	leg->Draw();

	// 	c1->SetLogy(0);
	// 	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// 	c1->Print("plots/mva_bdtbkg_centzone_eval_x.png");

	// 	MVA_BDTOther_centzone_eval_Xproj_0->Draw();
	// 	MVA_BDTOther_centzone_eval_Xproj_1->Draw("same");
	// 	MVA_BDTOther_centzone_eval_Xproj_2->Draw("same");
	// 	// MVA_BDTOther_centzone_eval_Xproj_3->Draw("same");
	// 	// MVA_BDTOther_centzone_eval_Xproj_4->Draw("same");
	// 	// MVA_BDTOther_centzone_eval_Xproj_5->Draw("same");
	// 	MVA_BDTOther_centzone_eval_Xproj_6->Draw("same");
	// 	MVA_BDTOther_centzone_eval_Xproj_0->Draw("same");

	// 	leg->Draw();

	// 	c1->SetLogy(0);
	// 	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	// 	c1->Print("plots/mva_bdtother_centzone_eval_x.png");
	// }

	// centzone cuts
	if (!pp_flag) {
		MVA_BDTSig_centzone_eval_Xproj_1->SetLineColor(kBlue);
		MVA_BDTBkg_centzone_eval_Xproj_1->SetLineColor(kRed);
		MVA_BDTOther_centzone_eval_Xproj_1->SetLineColor(kCyan);

		MVA_BDTSig_centzone_eval_Xproj_1->Scale(1/MVA_BDTSig_centzone_eval_Xproj_1->Integral());
		MVA_BDTBkg_centzone_eval_Xproj_1->Scale(1/MVA_BDTBkg_centzone_eval_Xproj_1->Integral());
		MVA_BDTOther_centzone_eval_Xproj_1->Scale(1/MVA_BDTOther_centzone_eval_Xproj_1->Integral());

		MVA_BDTBkg_centzone_eval_Xproj_1->Draw();
		MVA_BDTSig_centzone_eval_Xproj_1->Draw("same");
		MVA_BDTOther_centzone_eval_Xproj_1->Draw("same"); 

		leg->Clear();
		leg->SetX1NDC(0.72);
		leg->SetY1NDC(0.75);
		leg->AddEntry(MVA_BDTSig_centzone_eval_Xproj_1,   "Bottom Jets", "l");
		leg->AddEntry(MVA_BDTBkg_centzone_eval_Xproj_1,   "Light Jets",  "l");
		leg->AddEntry(MVA_BDTOther_centzone_eval_Xproj_1, "Charm Jets",  "l");
		leg->Draw();

		c1->SetLogy(0);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/mva_bdt_centzone1_eval_x.png");

		MVA_BDTSig_centzone_eval_Xproj_2->SetLineColor(kBlue);
		MVA_BDTBkg_centzone_eval_Xproj_2->SetLineColor(kRed);
		MVA_BDTOther_centzone_eval_Xproj_2->SetLineColor(kCyan);

		MVA_BDTSig_centzone_eval_Xproj_2->Scale(1/MVA_BDTSig_centzone_eval_Xproj_2->Integral());
		MVA_BDTBkg_centzone_eval_Xproj_2->Scale(1/MVA_BDTBkg_centzone_eval_Xproj_2->Integral());
		MVA_BDTOther_centzone_eval_Xproj_2->Scale(1/MVA_BDTOther_centzone_eval_Xproj_2->Integral());

		MVA_BDTBkg_centzone_eval_Xproj_2->Draw();
		MVA_BDTSig_centzone_eval_Xproj_2->Draw("same");
		MVA_BDTOther_centzone_eval_Xproj_2->Draw("same"); 

		leg->Draw();

		c1->SetLogy(0);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/mva_bdt_centzone2_eval_x.png");

		// MVA_BDTSig_centzone_eval_Xproj_3->SetLineColor(kBlue);
		// MVA_BDTBkg_centzone_eval_Xproj_3->SetLineColor(kRed);
		// MVA_BDTOther_centzone_eval_Xproj_3->SetLineColor(kCyan);

		// MVA_BDTSig_centzone_eval_Xproj_3->Scale(1/MVA_BDTSig_centzone_eval_Xproj_3->Integral());
		// MVA_BDTBkg_centzone_eval_Xproj_3->Scale(1/MVA_BDTBkg_centzone_eval_Xproj_3->Integral());
		// MVA_BDTOther_centzone_eval_Xproj_3->Scale(1/MVA_BDTOther_centzone_eval_Xproj_3->Integral());

		// MVA_BDTBkg_centzone_eval_Xproj_3->Draw();
		// MVA_BDTSig_centzone_eval_Xproj_3->Draw("same");
		// MVA_BDTOther_centzone_eval_Xproj_3->Draw("same"); 

		// leg->Draw();

		// c1->SetLogy(0);
		// MVA_BDTBkg_centzone_eval_Xproj_3->SetMinimum(0.);
		// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		// c1->Print("plots/mva_bdt_centzone3_eval_x.png");

		// MVA_BDTSig_centzone_eval_Xproj_4->SetLineColor(kBlue);
		// MVA_BDTBkg_centzone_eval_Xproj_4->SetLineColor(kRed);
		// MVA_BDTOther_centzone_eval_Xproj_4->SetLineColor(kCyan);

		// MVA_BDTSig_centzone_eval_Xproj_4->Scale(1/MVA_BDTSig_centzone_eval_Xproj_4->Integral());
		// MVA_BDTBkg_centzone_eval_Xproj_4->Scale(1/MVA_BDTBkg_centzone_eval_Xproj_4->Integral());
		// MVA_BDTOther_centzone_eval_Xproj_4->Scale(1/MVA_BDTOther_centzone_eval_Xproj_4->Integral());

		// MVA_BDTBkg_centzone_eval_Xproj_4->Draw();
		// MVA_BDTSig_centzone_eval_Xproj_4->Draw("same");
		// MVA_BDTOther_centzone_eval_Xproj_4->Draw("same"); 

		// leg->Draw();

		// c1->SetLogy(0);
		// MVA_BDTBkg_centzone_eval_Xproj_4->SetMinimum(0.);
		// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		// c1->Print("plots/mva_bdt_centzone4_eval_x.png");

		// MVA_BDTSig_centzone_eval_Xproj_5->SetLineColor(kBlue);
		// MVA_BDTBkg_centzone_eval_Xproj_5->SetLineColor(kRed);
		// MVA_BDTOther_centzone_eval_Xproj_5->SetLineColor(kCyan);

		// MVA_BDTSig_centzone_eval_Xproj_5->Scale(1/MVA_BDTSig_centzone_eval_Xproj_5->Integral());
		// MVA_BDTBkg_centzone_eval_Xproj_5->Scale(1/MVA_BDTBkg_centzone_eval_Xproj_5->Integral());
		// MVA_BDTOther_centzone_eval_Xproj_5->Scale(1/MVA_BDTOther_centzone_eval_Xproj_5->Integral());

		// MVA_BDTBkg_centzone_eval_Xproj_5->Draw();
		// MVA_BDTSig_centzone_eval_Xproj_5->Draw("same");
		// MVA_BDTOther_centzone_eval_Xproj_5->Draw("same"); 

		// leg->Draw();

		// c1->SetLogy(0);
		// MVA_BDTBkg_centzone_eval_Xproj_5->SetMinimum(0.);
		// c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		// c1->Print("plots/mva_bdt_centzone5_eval_x.png");

		MVA_BDTSig_centzone_eval_Xproj_6->SetLineColor(kBlue);
		MVA_BDTBkg_centzone_eval_Xproj_6->SetLineColor(kRed);
		MVA_BDTOther_centzone_eval_Xproj_6->SetLineColor(kCyan);

		MVA_BDTSig_centzone_eval_Xproj_6->Scale(1/MVA_BDTSig_centzone_eval_Xproj_6->Integral());
		MVA_BDTBkg_centzone_eval_Xproj_6->Scale(1/MVA_BDTBkg_centzone_eval_Xproj_6->Integral());
		MVA_BDTOther_centzone_eval_Xproj_6->Scale(1/MVA_BDTOther_centzone_eval_Xproj_6->Integral());

		MVA_BDTBkg_centzone_eval_Xproj_6->Draw();
		MVA_BDTSig_centzone_eval_Xproj_6->Draw("same");
		MVA_BDTOther_centzone_eval_Xproj_6->Draw("same"); 

		leg->Draw();

		c1->SetLogy(0);
		MVA_BDTBkg_centzone_eval_Xproj_6->SetMinimum(0.);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/mva_bdt_centzone6_eval_x.png");
	}

	//BDT Chosen
	notchosen_pt->Draw();
	chosen_pt->Draw("same");

	leg->Clear();
	leg->SetX1NDC(0.55);
	leg->SetY1NDC(0.8);
	leg->AddEntry(chosen_pt,    "Classified as Bottom",     "l");
	leg->AddEntry(notchosen_pt, "Not classified as Bottom", "l");
	leg->Draw();

	c1->SetLogy(1);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/chosen_pt.png");

	if (!pp_flag) {
		notchosen_pt_vs_centzone_0_20->Draw();
		chosen_pt_vs_centzone_0_20->Draw("same");

		leg->Draw();

		c1->SetLogy(1);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/chosen_pt_0_20.png");

		notchosen_pt_vs_centzone_20_40->Draw();
		chosen_pt_vs_centzone_20_40->Draw("same");

		leg->Draw();

		c1->SetLogy(1);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/chosen_pt_20_40.png");

		notchosen_pt_vs_centzone_40_80->Draw();
		chosen_pt_vs_centzone_40_80->Draw("same");

		leg->Draw();

		c1->SetLogy(1);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/chosen_pt_40_80.png");
	}

//----EFFICIENCY-------------------------------------------------

	const Int_t NbinMax = 300;

	// IP2D Efficiency
	Int_t   IP2D_nbins        = MVA_IP2D->GetNbinsX();
	Float_t IP2D_Sig_Integral = MVA_IP2D_SIGNAL->Integral(0, IP2D_nbins+1);
	Float_t IP2D_Bkg_Integral = MVA_IP2D_Background->Integral(0, IP2D_nbins+1);

	Float_t IP2DSig_accept[NbinMax]    = {};
	Float_t IP2DBkg_invreject[NbinMax] = {};
	Float_t IP2DBkg_reject[NbinMax]    = {};

	for (int i=0; i<=IP2D_nbins+1; i++) {
		// Signal Acceptance Integral Ratio
		IP2DSig_accept[i] = MVA_IP2D_SIGNAL->Integral(i,IP2D_nbins+1)/IP2D_Sig_Integral;
		IP2DBkg_reject[i] = (IP2D_Bkg_Integral - MVA_IP2D_Background->Integral(i,IP2D_nbins+1))/IP2D_Bkg_Integral;

		// Inverse Background Rejection Integral Ratio
		if (IP2DSig_accept[i] > 0.15)
			IP2DBkg_invreject[i] = IP2D_Bkg_Integral/MVA_IP2D_Background->Integral(i,IP2D_nbins+1);
		else
			IP2DBkg_invreject[i] = IP2DBkg_invreject[i-1];

		// cout << "sig  : " << IP2DSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << IP2DBkg_invreject[i-1] << endl;
	}

	// IP3D Efficiency
	Int_t   IP3D_nbins        = MVA_IP3D->GetNbinsX();
	Float_t IP3D_Sig_Integral = MVA_IP3D_SIGNAL->Integral(0, IP3D_nbins+1);
	Float_t IP3D_Bkg_Integral = MVA_IP3D_Background->Integral(0, IP3D_nbins+1);

	Float_t IP3DSig_accept[NbinMax]    = {};
	Float_t IP3DBkg_invreject[NbinMax] = {};
	Float_t IP3DBkg_reject[NbinMax]    = {};

	for (int i=0; i<=IP3D_nbins+1; i++) {
		// Signal Acceptance Integral Ratio
		IP3DSig_accept[i] = MVA_IP3D_SIGNAL->Integral(i,IP3D_nbins+1)/IP3D_Sig_Integral;
		IP3DBkg_reject[i] = (IP3D_Bkg_Integral - MVA_IP3D_Background->Integral(i,IP3D_nbins+1))/IP3D_Bkg_Integral;

		// Inverse Background Rejection Integral Ratio
		if (IP3DSig_accept[i] > 0.15)
			IP3DBkg_invreject[i] = IP3D_Bkg_Integral/MVA_IP3D_Background->Integral(i,IP3D_nbins+1);
		else
			IP3DBkg_invreject[i] = IP3DBkg_invreject[i-1];

		// cout << "sig  : " << IP3DSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << IP3DBkg_invreject[i-1] << endl;
	}

	// JF Efficiency
	Int_t   JF_nbins        = MVA_JF->GetNbinsX();
	Float_t JF_Sig_Integral = MVA_JF_SIGNAL->Integral(0, JF_nbins+1);
	Float_t JF_Bkg_Integral = MVA_JF_Background->Integral(0, JF_nbins+1);

	Float_t JFSig_accept[NbinMax]    = {};
	Float_t JFBkg_invreject[NbinMax] = {};
	Float_t JFBkg_reject[NbinMax]    = {};

	for (int i=0; i<=JF_nbins+1; i++) {
		// Signal Acceptance Integral Ratio
		JFSig_accept[i] = MVA_JF_SIGNAL->Integral(i,JF_nbins+1)/JF_Sig_Integral;
		JFBkg_reject[i] = (JF_Bkg_Integral - MVA_JF_Background->Integral(i,JF_nbins+1))/JF_Bkg_Integral;

		// Inverse Background Rejection Integral Ratio
		if (JFSig_accept[i] > 0.15)
			JFBkg_invreject[i] = JF_Bkg_Integral/MVA_JF_Background->Integral(i,JF_nbins+1);
		else
			JFBkg_invreject[i] = JFBkg_invreject[i-1];

		// cout << "sig  : " << JFSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << JFBkg_invreject[i-1] << endl;
	}

	// BDT Efficiency
	Int_t   BDT_nbins        = MVA_BDT->GetNbinsX();
	Float_t BDT_Sig_Integral = MVA_BDT_SIGNAL->Integral(0, BDT_nbins+1);
	Float_t BDT_Bkg_Integral = MVA_BDT_Background->Integral(0, BDT_nbins+1);

	Float_t BDTSig_accept[NbinMax]    = {};
	Float_t BDTBkg_invreject[NbinMax] = {};
	Float_t BDTBkg_reject[NbinMax]    = {};

	for (int i=0; i<=BDT_nbins+1; i++) {
		// Signal Acceptance Integral Ratio
		BDTSig_accept[i] = MVA_BDT_SIGNAL->Integral(i,BDT_nbins+1)/BDT_Sig_Integral;
		BDTBkg_reject[i] = (BDT_Bkg_Integral - MVA_BDT_Background->Integral(i,BDT_nbins+1))/BDT_Bkg_Integral;

		// Inverse Background Rejection Integral Ratio
		if (BDTSig_accept[i] > 0.15)
			BDTBkg_invreject[i] = BDT_Bkg_Integral/MVA_BDT_Background->Integral(i,BDT_nbins+1);
		else
			BDTBkg_invreject[i] = BDTBkg_invreject[i-1];

		// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
	}

	// BDT Efficiency for different pT cuts
	Int_t   BDT_nbins_pt1        = MVA_BDT_pt_eval_Xproj_1->GetNbinsX();
	Float_t BDT_Sig_Integral_pt1 = MVA_BDTSig_pt_eval_Xproj_1->Integral(0, BDT_nbins_pt1+1);
	Float_t BDT_Bkg_Integral_pt1 = MVA_BDTBkg_pt_eval_Xproj_1->Integral(0, BDT_nbins_pt1+1);

	Float_t BDTSig_accept_pt1[NbinMax]    = {};
	Float_t BDTBkg_invreject_pt1[NbinMax] = {};
	Float_t BDTBkg_reject_pt1[NbinMax]    = {};

	for (int i=0; i<=BDT_nbins_pt1+1; i++) {
		// Signal Acceptance Integral Ratio
		BDTSig_accept_pt1[i] = MVA_BDTSig_pt_eval_Xproj_1->Integral(i,BDT_nbins_pt1+1)/BDT_Sig_Integral_pt1;
		BDTBkg_reject_pt1[i] = (BDT_Bkg_Integral_pt1 - MVA_BDTBkg_pt_eval_Xproj_1->Integral(i,BDT_nbins_pt1+1))/BDT_Bkg_Integral_pt1;

		// Inverse Background Rejection Integral Ratio
		if (BDTSig_accept_pt1[i] > 0.15)
			BDTBkg_invreject_pt1[i] = BDT_Bkg_Integral_pt1/MVA_BDTBkg_pt_eval_Xproj_1->Integral(i,BDT_nbins_pt1+1);
		else
			BDTBkg_invreject_pt1[i] = BDTBkg_invreject_pt1[i-1];

		// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
	}

	Int_t   BDT_nbins_pt2        = MVA_BDT_pt_eval_Xproj_2->GetNbinsX();
	Float_t BDT_Sig_Integral_pt2 = MVA_BDTSig_pt_eval_Xproj_2->Integral(0, BDT_nbins_pt2+1);
	Float_t BDT_Bkg_Integral_pt2 = MVA_BDTBkg_pt_eval_Xproj_2->Integral(0, BDT_nbins_pt2+1);

	Float_t BDTSig_accept_pt2[NbinMax]    = {};
	Float_t BDTBkg_invreject_pt2[NbinMax] = {};
	Float_t BDTBkg_reject_pt2[NbinMax]    = {};

	for (int i=0; i<=BDT_nbins_pt2+1; i++) {
		// Signal Acceptance Integral Ratio
		BDTSig_accept_pt2[i] = MVA_BDTSig_pt_eval_Xproj_2->Integral(i,BDT_nbins_pt2+1)/BDT_Sig_Integral_pt2;
		BDTBkg_reject_pt2[i] = (BDT_Bkg_Integral_pt2 - MVA_BDTBkg_pt_eval_Xproj_2->Integral(i,BDT_nbins_pt2+1))/BDT_Bkg_Integral_pt2;

		// Inverse Background Rejection Integral Ratio
		if (BDTSig_accept_pt2[i] > 0.15)
			BDTBkg_invreject_pt2[i] = BDT_Bkg_Integral_pt2/MVA_BDTBkg_pt_eval_Xproj_2->Integral(i,BDT_nbins_pt2+1);
		else
			BDTBkg_invreject_pt2[i] = BDTBkg_invreject_pt2[i-1];

		// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
	}

	Int_t   BDT_nbins_pt3        = MVA_BDT_pt_eval_Xproj_3->GetNbinsX();
	Float_t BDT_Sig_Integral_pt3 = MVA_BDTSig_pt_eval_Xproj_3->Integral(0, BDT_nbins_pt3+1);
	Float_t BDT_Bkg_Integral_pt3 = MVA_BDTBkg_pt_eval_Xproj_3->Integral(0, BDT_nbins_pt3+1);

	Float_t BDTSig_accept_pt3[NbinMax]    = {};
	Float_t BDTBkg_invreject_pt3[NbinMax] = {};
	Float_t BDTBkg_reject_pt3[NbinMax]    = {};

	for (int i=0; i<=BDT_nbins_pt3+1; i++) {
		// Signal Acceptance Integral Ratio
		BDTSig_accept_pt3[i] = MVA_BDTSig_pt_eval_Xproj_3->Integral(i,BDT_nbins_pt3+1)/BDT_Sig_Integral_pt3;
		BDTBkg_reject_pt3[i] = (BDT_Bkg_Integral_pt3 - MVA_BDTBkg_pt_eval_Xproj_3->Integral(i,BDT_nbins_pt3+1))/BDT_Bkg_Integral_pt3;

		// Inverse Background Rejection Integral Ratio
		if (BDTSig_accept_pt3[i] > 0.15)
			BDTBkg_invreject_pt3[i] = BDT_Bkg_Integral_pt3/MVA_BDTBkg_pt_eval_Xproj_3->Integral(i,BDT_nbins_pt3+1);
		else
			BDTBkg_invreject_pt3[i] = BDTBkg_invreject_pt3[i-1];

		// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
	}

	Int_t   BDT_nbins_pt4        = MVA_BDT_pt_eval_Xproj_4->GetNbinsX();
	Float_t BDT_Sig_Integral_pt4 = MVA_BDTSig_pt_eval_Xproj_4->Integral(0, BDT_nbins_pt4+1);
	Float_t BDT_Bkg_Integral_pt4 = MVA_BDTBkg_pt_eval_Xproj_4->Integral(0, BDT_nbins_pt4+1);

	Float_t BDTSig_accept_pt4[NbinMax]    = {};
	Float_t BDTBkg_invreject_pt4[NbinMax] = {};
	Float_t BDTBkg_reject_pt4[NbinMax]    = {};

	for (int i=0; i<=BDT_nbins_pt4+1; i++) {
		// Signal Acceptance Integral Ratio
		BDTSig_accept_pt4[i] = MVA_BDTSig_pt_eval_Xproj_4->Integral(i,BDT_nbins_pt4+1)/BDT_Sig_Integral_pt4;
		BDTBkg_reject_pt4[i] = (BDT_Bkg_Integral_pt4 - MVA_BDTBkg_pt_eval_Xproj_4->Integral(i,BDT_nbins_pt4+1))/BDT_Bkg_Integral_pt4;

		// Inverse Background Rejection Integral Ratio
		if (BDTSig_accept_pt4[i] > 0.15)
			BDTBkg_invreject_pt4[i] = BDT_Bkg_Integral_pt4/MVA_BDTBkg_pt_eval_Xproj_4->Integral(i,BDT_nbins_pt4+1);
		else
			BDTBkg_invreject_pt4[i] = BDTBkg_invreject_pt4[i-1];

		// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
	}

	Int_t   BDT_nbins_pt5        = MVA_BDT_pt_eval_Xproj_5->GetNbinsX();
	Float_t BDT_Sig_Integral_pt5 = MVA_BDTSig_pt_eval_Xproj_5->Integral(0, BDT_nbins_pt5+1);
	Float_t BDT_Bkg_Integral_pt5 = MVA_BDTBkg_pt_eval_Xproj_5->Integral(0, BDT_nbins_pt5+1);

	Float_t BDTSig_accept_pt5[NbinMax]    = {};
	Float_t BDTBkg_invreject_pt5[NbinMax] = {};
	Float_t BDTBkg_reject_pt5[NbinMax]    = {};

	for (int i=0; i<=BDT_nbins_pt5+1; i++) {
		// Signal Acceptance Integral Ratio
		BDTSig_accept_pt5[i] = MVA_BDTSig_pt_eval_Xproj_5->Integral(i,BDT_nbins_pt5+1)/BDT_Sig_Integral_pt5;
		BDTBkg_reject_pt5[i] = (BDT_Bkg_Integral_pt5 - MVA_BDTBkg_pt_eval_Xproj_5->Integral(i,BDT_nbins_pt5+1))/BDT_Bkg_Integral_pt5;

		// Inverse Background Rejection Integral Ratio
		if (BDTSig_accept_pt5[i] > 0.15)
			BDTBkg_invreject_pt5[i] = BDT_Bkg_Integral_pt5/MVA_BDTBkg_pt_eval_Xproj_5->Integral(i,BDT_nbins_pt5+1);
		else
			BDTBkg_invreject_pt5[i] = BDTBkg_invreject_pt5[i-1];

		// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
	}

	Int_t   BDT_nbins_pt6        = MVA_BDT_pt_eval_Xproj_6->GetNbinsX();
	Float_t BDT_Sig_Integral_pt6 = MVA_BDTSig_pt_eval_Xproj_6->Integral(0, BDT_nbins_pt6+1);
	Float_t BDT_Bkg_Integral_pt6 = MVA_BDTBkg_pt_eval_Xproj_6->Integral(0, BDT_nbins_pt6+1);

	Float_t BDTSig_accept_pt6[NbinMax]    = {};
	Float_t BDTBkg_invreject_pt6[NbinMax] = {};
	Float_t BDTBkg_reject_pt6[NbinMax]    = {};

	if (pp_flag) {
		for (int i=0; i<=BDT_nbins_pt6+1; i++) {
			// Signal Acceptance Integral Ratio
			BDTSig_accept_pt6[i] = MVA_BDTSig_pt_eval_Xproj_6->Integral(i,BDT_nbins_pt6+1)/BDT_Sig_Integral_pt6;
			BDTBkg_reject_pt6[i] = (BDT_Bkg_Integral_pt6 - MVA_BDTBkg_pt_eval_Xproj_6->Integral(i,BDT_nbins_pt6+1))/BDT_Bkg_Integral_pt6;

			// Inverse Background Rejection Integral Ratio
			if (BDTSig_accept_pt6[i] > 0.15)
				BDTBkg_invreject_pt6[i] = BDT_Bkg_Integral_pt6/MVA_BDTBkg_pt_eval_Xproj_6->Integral(i,BDT_nbins_pt6+1);
			else
				BDTBkg_invreject_pt6[i] = BDTBkg_invreject_pt6[i-1];

			// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
			// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
		}
	}

	Int_t   BDT_nbins_pt7        = MVA_BDT_pt_eval_Xproj_7->GetNbinsX();
	Float_t BDT_Sig_Integral_pt7 = MVA_BDTSig_pt_eval_Xproj_7->Integral(0, BDT_nbins_pt7+1);
	Float_t BDT_Bkg_Integral_pt7 = MVA_BDTBkg_pt_eval_Xproj_7->Integral(0, BDT_nbins_pt7+1);

	Float_t BDTSig_accept_pt7[NbinMax]    = {};
	Float_t BDTBkg_invreject_pt7[NbinMax] = {};
	Float_t BDTBkg_reject_pt7[NbinMax]    = {};

	if (pp_flag) {
		for (int i=0; i<=BDT_nbins_pt7+1; i++) {
			// Signal Acceptance Integral Ratio
			BDTSig_accept_pt7[i] = MVA_BDTSig_pt_eval_Xproj_7->Integral(i,BDT_nbins_pt7+1)/BDT_Sig_Integral_pt7;
			BDTBkg_reject_pt7[i] = (BDT_Bkg_Integral_pt7 - MVA_BDTBkg_pt_eval_Xproj_7->Integral(i,BDT_nbins_pt7+1))/BDT_Bkg_Integral_pt7;

			// Inverse Background Rejection Integral Ratio
			if (BDTSig_accept_pt7[i] > 0.15)
				BDTBkg_invreject_pt7[i] = BDT_Bkg_Integral_pt7/MVA_BDTBkg_pt_eval_Xproj_7->Integral(i,BDT_nbins_pt7+1);
			else
				BDTBkg_invreject_pt7[i] = BDTBkg_invreject_pt7[i-1];

			// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
			// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
		}
	}

	Int_t   BDT_nbins_pt8        = MVA_BDT_pt_eval_Xproj_8->GetNbinsX();
	Float_t BDT_Sig_Integral_pt8 = MVA_BDTSig_pt_eval_Xproj_8->Integral(0, BDT_nbins_pt8+1);
	Float_t BDT_Bkg_Integral_pt8 = MVA_BDTBkg_pt_eval_Xproj_8->Integral(0, BDT_nbins_pt8+1);

	Float_t BDTSig_accept_pt8[NbinMax]    = {};
	Float_t BDTBkg_invreject_pt8[NbinMax] = {};
	Float_t BDTBkg_reject_pt8[NbinMax]    = {};

	if (pp_flag) {
		for (int i=0; i<=BDT_nbins_pt8+1; i++) {
			// Signal Acceptance Integral Ratio
			BDTSig_accept_pt8[i] = MVA_BDTSig_pt_eval_Xproj_8->Integral(i,BDT_nbins_pt8+1)/BDT_Sig_Integral_pt8;
			BDTBkg_reject_pt8[i] = (BDT_Bkg_Integral_pt8 - MVA_BDTBkg_pt_eval_Xproj_8->Integral(i,BDT_nbins_pt8+1))/BDT_Bkg_Integral_pt8;

			// Inverse Background Rejection Integral Ratio
			if (BDTSig_accept_pt8[i] > 0.15)
				BDTBkg_invreject_pt8[i] = BDT_Bkg_Integral_pt8/MVA_BDTBkg_pt_eval_Xproj_8->Integral(i,BDT_nbins_pt8+1);
			else
				BDTBkg_invreject_pt8[i] = BDTBkg_invreject_pt8[i-1];

			// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
			// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
		}
	}

	// BDT Efficiency for different abseta cuts
	Int_t   BDT_nbins_abseta1        = MVA_BDT_abseta_eval_Xproj_1->GetNbinsX();
	Float_t BDT_Sig_Integral_abseta1 = MVA_BDTSig_abseta_eval_Xproj_1->Integral(0, BDT_nbins_abseta1+1);
	Float_t BDT_Bkg_Integral_abseta1 = MVA_BDTBkg_abseta_eval_Xproj_1->Integral(0, BDT_nbins_abseta1+1);

	Float_t BDTSig_accept_abseta1[NbinMax]    = {};
	Float_t BDTBkg_invreject_abseta1[NbinMax] = {};
	Float_t BDTBkg_reject_abseta1[NbinMax]    = {};

	for (int i=0; i<=BDT_nbins_abseta1+1; i++) {
		// Signal Acceptance Integral Ratio
		BDTSig_accept_abseta1[i] = MVA_BDTSig_abseta_eval_Xproj_1->Integral(i,BDT_nbins_abseta1+1)/BDT_Sig_Integral_abseta1;
		BDTBkg_reject_abseta1[i] = (BDT_Bkg_Integral_abseta1 - MVA_BDTBkg_abseta_eval_Xproj_1->Integral(i,BDT_nbins_abseta1+1))/BDT_Bkg_Integral_abseta1;

		// Inverse Background Rejection Integral Ratio
		if (BDTSig_accept_abseta1[i] > 0.15)
			BDTBkg_invreject_abseta1[i] = BDT_Bkg_Integral_abseta1/MVA_BDTBkg_abseta_eval_Xproj_1->Integral(i,BDT_nbins_abseta1+1);
		else
			BDTBkg_invreject_abseta1[i] = BDTBkg_invreject_abseta1[i-1];

		// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
	}

	Int_t   BDT_nbins_abseta2        = MVA_BDT_abseta_eval_Xproj_2->GetNbinsX();
	Float_t BDT_Sig_Integral_abseta2 = MVA_BDTSig_abseta_eval_Xproj_2->Integral(0, BDT_nbins_abseta2+1);
	Float_t BDT_Bkg_Integral_abseta2 = MVA_BDTBkg_abseta_eval_Xproj_2->Integral(0, BDT_nbins_abseta2+1);

	Float_t BDTSig_accept_abseta2[NbinMax]    = {};
	Float_t BDTBkg_invreject_abseta2[NbinMax] = {};
	Float_t BDTBkg_reject_abseta2[NbinMax]    = {};

	for (int i=0; i<=BDT_nbins_abseta2+1; i++) {
		// Signal Acceptance Integral Ratio
		BDTSig_accept_abseta2[i] = MVA_BDTSig_abseta_eval_Xproj_2->Integral(i,BDT_nbins_abseta2+1)/BDT_Sig_Integral_abseta2;
		BDTBkg_reject_abseta2[i] = (BDT_Bkg_Integral_abseta2 - MVA_BDTBkg_abseta_eval_Xproj_2->Integral(i,BDT_nbins_abseta2+1))/BDT_Bkg_Integral_abseta2;

		// Inverse Background Rejection Integral Ratio
		if (BDTSig_accept_abseta2[i] > 0.15)
			BDTBkg_invreject_abseta2[i] = BDT_Bkg_Integral_abseta2/MVA_BDTBkg_abseta_eval_Xproj_2->Integral(i,BDT_nbins_abseta2+1);
		else
			BDTBkg_invreject_abseta2[i] = BDTBkg_invreject_abseta2[i-1];

		// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
	}

	Int_t   BDT_nbins_abseta3        = MVA_BDT_abseta_eval_Xproj_3->GetNbinsX();
	Float_t BDT_Sig_Integral_abseta3 = MVA_BDTSig_abseta_eval_Xproj_3->Integral(0, BDT_nbins_abseta3+1);
	Float_t BDT_Bkg_Integral_abseta3 = MVA_BDTBkg_abseta_eval_Xproj_3->Integral(0, BDT_nbins_abseta3+1);

	Float_t BDTSig_accept_abseta3[NbinMax]    = {};
	Float_t BDTBkg_invreject_abseta3[NbinMax] = {};
	Float_t BDTBkg_reject_abseta3[NbinMax]    = {};

	for (int i=0; i<=BDT_nbins_abseta3+1; i++) {
		// Signal Acceptance Integral Ratio
		BDTSig_accept_abseta3[i] = MVA_BDTSig_abseta_eval_Xproj_3->Integral(i,BDT_nbins_abseta3+1)/BDT_Sig_Integral_abseta3;
		BDTBkg_reject_abseta3[i] = (BDT_Bkg_Integral_abseta3 - MVA_BDTBkg_abseta_eval_Xproj_3->Integral(i,BDT_nbins_abseta3+1))/BDT_Bkg_Integral_abseta3;

		// Inverse Background Rejection Integral Ratio
		if (BDTSig_accept_abseta3[i] > 0.15)
			BDTBkg_invreject_abseta3[i] = BDT_Bkg_Integral_abseta3/MVA_BDTBkg_abseta_eval_Xproj_3->Integral(i,BDT_nbins_abseta3+1);
		else
			BDTBkg_invreject_abseta3[i] = BDTBkg_invreject_abseta3[i-1];

		// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
	}

	// BDT Efficiency for different phi cuts
	Int_t   BDT_nbins_phi1        = MVA_BDT_phi_eval_Xproj_1->GetNbinsX();
	Float_t BDT_Sig_Integral_phi1 = MVA_BDTSig_phi_eval_Xproj_1->Integral(0, BDT_nbins_phi1+1);
	Float_t BDT_Bkg_Integral_phi1 = MVA_BDTBkg_phi_eval_Xproj_1->Integral(0, BDT_nbins_phi1+1);

	Float_t BDTSig_accept_phi1[NbinMax]    = {};
	Float_t BDTBkg_invreject_phi1[NbinMax] = {};
	Float_t BDTBkg_reject_phi1[NbinMax]    = {};

	for (int i=0; i<=BDT_nbins_phi1+1; i++) {
		// Signal Acceptance Integral Ratio
		BDTSig_accept_phi1[i] = MVA_BDTSig_phi_eval_Xproj_1->Integral(i,BDT_nbins_phi1+1)/BDT_Sig_Integral_phi1;
		BDTBkg_reject_phi1[i] = (BDT_Bkg_Integral_phi1 - MVA_BDTBkg_phi_eval_Xproj_1->Integral(i,BDT_nbins_phi1+1))/BDT_Bkg_Integral_phi1;

		// Inverse Background Rejection Integral Ratio
		if (BDTSig_accept_phi1[i] > 0.15)
			BDTBkg_invreject_phi1[i] = BDT_Bkg_Integral_phi1/MVA_BDTBkg_phi_eval_Xproj_1->Integral(i,BDT_nbins_phi1+1);
		else
			BDTBkg_invreject_phi1[i] = BDTBkg_invreject_phi1[i-1];

		// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
	}

	Int_t   BDT_nbins_phi2        = MVA_BDT_phi_eval_Xproj_2->GetNbinsX();
	Float_t BDT_Sig_Integral_phi2 = MVA_BDTSig_phi_eval_Xproj_2->Integral(0, BDT_nbins_phi2+1);
	Float_t BDT_Bkg_Integral_phi2 = MVA_BDTBkg_phi_eval_Xproj_2->Integral(0, BDT_nbins_phi2+1);

	Float_t BDTSig_accept_phi2[NbinMax]    = {};
	Float_t BDTBkg_invreject_phi2[NbinMax] = {};
	Float_t BDTBkg_reject_phi2[NbinMax]    = {};

	for (int i=0; i<=BDT_nbins_phi2+1; i++) {
		// Signal Acceptance Integral Ratio
		BDTSig_accept_phi2[i] = MVA_BDTSig_phi_eval_Xproj_2->Integral(i,BDT_nbins_phi2+1)/BDT_Sig_Integral_phi2;
		BDTBkg_reject_phi2[i] = (BDT_Bkg_Integral_phi2 - MVA_BDTBkg_phi_eval_Xproj_2->Integral(i,BDT_nbins_phi2+1))/BDT_Bkg_Integral_phi2;

		// Inverse Background Rejection Integral Ratio
		if (BDTSig_accept_phi2[i] > 0.15)
			BDTBkg_invreject_phi2[i] = BDT_Bkg_Integral_phi2/MVA_BDTBkg_phi_eval_Xproj_2->Integral(i,BDT_nbins_phi2+1);
		else
			BDTBkg_invreject_phi2[i] = BDTBkg_invreject_phi2[i-1];

		// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
	}

	Int_t   BDT_nbins_phi3        = MVA_BDT_phi_eval_Xproj_3->GetNbinsX();
	Float_t BDT_Sig_Integral_phi3 = MVA_BDTSig_phi_eval_Xproj_3->Integral(0, BDT_nbins_phi3+1);
	Float_t BDT_Bkg_Integral_phi3 = MVA_BDTBkg_phi_eval_Xproj_3->Integral(0, BDT_nbins_phi3+1);

	Float_t BDTSig_accept_phi3[NbinMax]    = {};
	Float_t BDTBkg_invreject_phi3[NbinMax] = {};
	Float_t BDTBkg_reject_phi3[NbinMax]    = {};

	for (int i=0; i<=BDT_nbins_phi3+1; i++) {
		// Signal Acceptance Integral Ratio
		BDTSig_accept_phi3[i] = MVA_BDTSig_phi_eval_Xproj_3->Integral(i,BDT_nbins_phi3+1)/BDT_Sig_Integral_phi3;
		BDTBkg_reject_phi3[i] = (BDT_Bkg_Integral_phi3 - MVA_BDTBkg_phi_eval_Xproj_3->Integral(i,BDT_nbins_phi3+1))/BDT_Bkg_Integral_phi3;

		// Inverse Background Rejection Integral Ratio
		if (BDTSig_accept_phi3[i] > 0.15)
			BDTBkg_invreject_phi3[i] = BDT_Bkg_Integral_phi3/MVA_BDTBkg_phi_eval_Xproj_3->Integral(i,BDT_nbins_phi3+1);
		else
			BDTBkg_invreject_phi3[i] = BDTBkg_invreject_phi3[i-1];

		// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
	}   

	Int_t   BDT_nbins_phi4        = MVA_BDT_phi_eval_Xproj_4->GetNbinsX();
	Float_t BDT_Sig_Integral_phi4 = MVA_BDTSig_phi_eval_Xproj_4->Integral(0, BDT_nbins_phi4+1);
	Float_t BDT_Bkg_Integral_phi4 = MVA_BDTBkg_phi_eval_Xproj_4->Integral(0, BDT_nbins_phi4+1);

	Float_t BDTSig_accept_phi4[NbinMax]    = {};
	Float_t BDTBkg_invreject_phi4[NbinMax] = {};
	Float_t BDTBkg_reject_phi4[NbinMax]    = {};

	for (int i=0; i<=BDT_nbins_phi4+1; i++) {
		// Signal Acceptance Integral Ratio
		BDTSig_accept_phi4[i] = MVA_BDTSig_phi_eval_Xproj_4->Integral(i,BDT_nbins_phi4+1)/BDT_Sig_Integral_phi4;
		BDTBkg_reject_phi4[i] = (BDT_Bkg_Integral_phi4 - MVA_BDTBkg_phi_eval_Xproj_4->Integral(i,BDT_nbins_phi4+1))/BDT_Bkg_Integral_phi4;

		// Inverse Background Rejection Integral Ratio
		if (BDTSig_accept_phi4[i] > 0.15)
			BDTBkg_invreject_phi4[i] = BDT_Bkg_Integral_phi4/MVA_BDTBkg_phi_eval_Xproj_4->Integral(i,BDT_nbins_phi4+1);
		else
			BDTBkg_invreject_phi4[i] = BDTBkg_invreject_phi4[i-1];

		// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
	}

	Int_t   BDT_nbins_phi5        = MVA_BDT_phi_eval_Xproj_5->GetNbinsX();
	Float_t BDT_Sig_Integral_phi5 = MVA_BDTSig_phi_eval_Xproj_5->Integral(0, BDT_nbins_phi5+1);
	Float_t BDT_Bkg_Integral_phi5 = MVA_BDTBkg_phi_eval_Xproj_5->Integral(0, BDT_nbins_phi5+1);

	Float_t BDTSig_accept_phi5[NbinMax]    = {};
	Float_t BDTBkg_invreject_phi5[NbinMax] = {};
	Float_t BDTBkg_reject_phi5[NbinMax]    = {};

	for (int i=0; i<=BDT_nbins_phi5+1; i++) {
		// Signal Acceptance Integral Ratio
		BDTSig_accept_phi5[i] = MVA_BDTSig_phi_eval_Xproj_5->Integral(i,BDT_nbins_phi5+1)/BDT_Sig_Integral_phi5;
		BDTBkg_reject_phi5[i] = (BDT_Bkg_Integral_phi5 - MVA_BDTBkg_phi_eval_Xproj_5->Integral(i,BDT_nbins_phi5+1))/BDT_Bkg_Integral_phi5;

		// Inverse Background Rejection Integral Ratio
		if (BDTSig_accept_phi5[i] > 0.15)
			BDTBkg_invreject_phi5[i] = BDT_Bkg_Integral_phi5/MVA_BDTBkg_phi_eval_Xproj_5->Integral(i,BDT_nbins_phi5+1);
		else
			BDTBkg_invreject_phi5[i] = BDTBkg_invreject_phi5[i-1];

		// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
	}

	Int_t   BDT_nbins_phi6        = MVA_BDT_phi_eval_Xproj_6->GetNbinsX();
	Float_t BDT_Sig_Integral_phi6 = MVA_BDTSig_phi_eval_Xproj_6->Integral(0, BDT_nbins_phi6+1);
	Float_t BDT_Bkg_Integral_phi6 = MVA_BDTBkg_phi_eval_Xproj_6->Integral(0, BDT_nbins_phi6+1);

	Float_t BDTSig_accept_phi6[NbinMax]    = {};
	Float_t BDTBkg_invreject_phi6[NbinMax] = {};
	Float_t BDTBkg_reject_phi6[NbinMax]    = {};

	for (int i=0; i<=BDT_nbins_phi6+1; i++) {
		// Signal Acceptance Integral Ratio
		BDTSig_accept_phi6[i] = MVA_BDTSig_phi_eval_Xproj_6->Integral(i,BDT_nbins_phi6+1)/BDT_Sig_Integral_phi6;
		BDTBkg_reject_phi6[i] = (BDT_Bkg_Integral_phi6 - MVA_BDTBkg_phi_eval_Xproj_6->Integral(i,BDT_nbins_phi6+1))/BDT_Bkg_Integral_phi6;

		// Inverse Background Rejection Integral Ratio
		if (BDTSig_accept_phi6[i] > 0.15)
			BDTBkg_invreject_phi6[i] = BDT_Bkg_Integral_phi6/MVA_BDTBkg_phi_eval_Xproj_6->Integral(i,BDT_nbins_phi6+1);
		else
			BDTBkg_invreject_phi6[i] = BDTBkg_invreject_phi6[i-1];

		// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
		// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
	}

    // BDT Efficiency for different centzone cuts
	Int_t   BDT_nbins_centzone1        = MVA_BDT_centzone_eval_Xproj_1->GetNbinsX();
	Float_t BDT_Sig_Integral_centzone1 = MVA_BDTSig_centzone_eval_Xproj_1->Integral(0, BDT_nbins_centzone1+1);
	Float_t BDT_Bkg_Integral_centzone1 = MVA_BDTBkg_centzone_eval_Xproj_1->Integral(0, BDT_nbins_centzone1+1);

	Float_t BDTSig_accept_centzone1[NbinMax]    = {};
	Float_t BDTBkg_invreject_centzone1[NbinMax] = {};
	Float_t BDTBkg_reject_centzone1[NbinMax]    = {};

	if (!pp_flag) {
		for (int i=0; i<=BDT_nbins_centzone1+1; i++) {
			// Signal Acceptance Integral Ratio
			BDTSig_accept_centzone1[i] = MVA_BDTSig_centzone_eval_Xproj_1->Integral(i,BDT_nbins_centzone1+1)/BDT_Sig_Integral_centzone1;
			BDTBkg_reject_centzone1[i] = (BDT_Bkg_Integral_centzone1 - MVA_BDTBkg_centzone_eval_Xproj_1->Integral(i,BDT_nbins_centzone1+1))/BDT_Bkg_Integral_centzone1;

			// Inverse Background Rejection Integral Ratio
			if (BDTSig_accept_centzone1[i] > 0.15)
				BDTBkg_invreject_centzone1[i] = BDT_Bkg_Integral_centzone1/MVA_BDTBkg_centzone_eval_Xproj_1->Integral(i,BDT_nbins_centzone1+1);
			else
				BDTBkg_invreject_centzone1[i] = BDTBkg_invreject_centzone1[i-1];

			// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
			// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
		}
	}

	Int_t   BDT_nbins_centzone2        = MVA_BDT_centzone_eval_Xproj_2->GetNbinsX();
	Float_t BDT_Sig_Integral_centzone2 = MVA_BDTSig_centzone_eval_Xproj_2->Integral(0, BDT_nbins_centzone2+1);
	Float_t BDT_Bkg_Integral_centzone2 = MVA_BDTBkg_centzone_eval_Xproj_2->Integral(0, BDT_nbins_centzone2+1);

	Float_t BDTSig_accept_centzone2[NbinMax] = {};
	Float_t BDTBkg_invreject_centzone2[NbinMax] = {};
	Float_t BDTBkg_reject_centzone2[NbinMax] = {};

	if (!pp_flag) {
		for (int i=0; i<=BDT_nbins_centzone2+1; i++) {
			// Signal Acceptance Integral Ratio
			BDTSig_accept_centzone2[i] = MVA_BDTSig_centzone_eval_Xproj_2->Integral(i,BDT_nbins_centzone2+1)/BDT_Sig_Integral_centzone2;
			BDTBkg_reject_centzone2[i] = (BDT_Bkg_Integral_centzone2 - MVA_BDTBkg_centzone_eval_Xproj_2->Integral(i,BDT_nbins_centzone2+1))/BDT_Bkg_Integral_centzone2;

			// Inverse Background Rejection Integral Ratio
			if (BDTSig_accept_centzone2[i] > 0.15)
				BDTBkg_invreject_centzone2[i] = BDT_Bkg_Integral_centzone2/MVA_BDTBkg_centzone_eval_Xproj_2->Integral(i,BDT_nbins_centzone2+1);
			else
				BDTBkg_invreject_centzone2[i] = BDTBkg_invreject_centzone2[i-1];

			// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
			// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
		}
	}

	Int_t   BDT_nbins_centzone3        = MVA_BDT_centzone_eval_Xproj_3->GetNbinsX();
	Float_t BDT_Sig_Integral_centzone3 = MVA_BDTSig_centzone_eval_Xproj_3->Integral(0, BDT_nbins_centzone3+1);
	Float_t BDT_Bkg_Integral_centzone3 = MVA_BDTBkg_centzone_eval_Xproj_3->Integral(0, BDT_nbins_centzone3+1);

	Float_t BDTSig_accept_centzone3[NbinMax]    = {};
	Float_t BDTBkg_invreject_centzone3[NbinMax] = {};
	Float_t BDTBkg_reject_centzone3[NbinMax]    = {};

	if (!pp_flag) {
		for (int i=0; i<=BDT_nbins_centzone3+1; i++) {
			// Signal Acceptance Integral Ratio
			BDTSig_accept_centzone3[i] = MVA_BDTSig_centzone_eval_Xproj_3->Integral(i,BDT_nbins_centzone3+1)/BDT_Sig_Integral_centzone3;
			BDTBkg_reject_centzone3[i] = (BDT_Bkg_Integral_centzone3 - MVA_BDTBkg_centzone_eval_Xproj_3->Integral(i,BDT_nbins_centzone3+1))/BDT_Bkg_Integral_centzone3;

			// Inverse Background Rejection Integral Ratio
			if (BDTSig_accept_centzone3[i] > 0.15)
				BDTBkg_invreject_centzone3[i] = BDT_Bkg_Integral_centzone3/MVA_BDTBkg_centzone_eval_Xproj_3->Integral(i,BDT_nbins_centzone3+1);
			else
				BDTBkg_invreject_centzone3[i] = BDTBkg_invreject_centzone3[i-1];

			// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
			// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
		}
	}

	Int_t   BDT_nbins_centzone4        = MVA_BDT_centzone_eval_Xproj_4->GetNbinsX();
	Float_t BDT_Sig_Integral_centzone4 = MVA_BDTSig_centzone_eval_Xproj_4->Integral(0, BDT_nbins_centzone4+1);
	Float_t BDT_Bkg_Integral_centzone4 = MVA_BDTBkg_centzone_eval_Xproj_4->Integral(0, BDT_nbins_centzone4+1);

	Float_t BDTSig_accept_centzone4[NbinMax]    = {};
	Float_t BDTBkg_invreject_centzone4[NbinMax] = {};
	Float_t BDTBkg_reject_centzone4[NbinMax]    = {};

	if (!pp_flag) {
		for (int i=0; i<=BDT_nbins_centzone4+1; i++) {
			// Signal Acceptance Integral Ratio
			BDTSig_accept_centzone4[i] = MVA_BDTSig_centzone_eval_Xproj_4->Integral(i,BDT_nbins_centzone4+1)/BDT_Sig_Integral_centzone4;
			BDTBkg_reject_centzone4[i] = (BDT_Bkg_Integral_centzone4 - MVA_BDTBkg_centzone_eval_Xproj_4->Integral(i,BDT_nbins_centzone4+1))/BDT_Bkg_Integral_centzone4;

			// Inverse Background Rejection Integral Ratio
			if (BDTSig_accept_centzone4[i] > 0.15)
				BDTBkg_invreject_centzone4[i] = BDT_Bkg_Integral_centzone4/MVA_BDTBkg_centzone_eval_Xproj_4->Integral(i,BDT_nbins_centzone4+1);
			else
				BDTBkg_invreject_centzone4[i] = BDTBkg_invreject_centzone4[i-1];

			// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
			// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
		}
	}

	Int_t   BDT_nbins_centzone5        = MVA_BDT_centzone_eval_Xproj_5->GetNbinsX();
	Float_t BDT_Sig_Integral_centzone5 = MVA_BDTSig_centzone_eval_Xproj_5->Integral(0, BDT_nbins_centzone5+1);
	Float_t BDT_Bkg_Integral_centzone5 = MVA_BDTBkg_centzone_eval_Xproj_5->Integral(0, BDT_nbins_centzone5+1);

	Float_t BDTSig_accept_centzone5[NbinMax]    = {};
	Float_t BDTBkg_invreject_centzone5[NbinMax] = {};
	Float_t BDTBkg_reject_centzone5[NbinMax]    = {};

	if (!pp_flag) {
		for (int i=0; i<=BDT_nbins_centzone5+1; i++) {
			// Signal Acceptance Integral Ratio
			BDTSig_accept_centzone5[i] = MVA_BDTSig_centzone_eval_Xproj_5->Integral(i,BDT_nbins_centzone5+1)/BDT_Sig_Integral_centzone5;
			BDTBkg_reject_centzone5[i] = (BDT_Bkg_Integral_centzone5 - MVA_BDTBkg_centzone_eval_Xproj_5->Integral(i,BDT_nbins_centzone5+1))/BDT_Bkg_Integral_centzone5;

			// Inverse Background Rejection Integral Ratio
			if (BDTSig_accept_centzone5[i] > 0.15)
				BDTBkg_invreject_centzone5[i] = BDT_Bkg_Integral_centzone5/MVA_BDTBkg_centzone_eval_Xproj_5->Integral(i,BDT_nbins_centzone5+1);
			else
				BDTBkg_invreject_centzone5[i] = BDTBkg_invreject_centzone5[i-1];

			// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
			// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
		}
	}

	Int_t   BDT_nbins_centzone6        = MVA_BDT_centzone_eval_Xproj_6->GetNbinsX();
	Float_t BDT_Sig_Integral_centzone6 = MVA_BDTSig_centzone_eval_Xproj_6->Integral(0, BDT_nbins_centzone6+1);
	Float_t BDT_Bkg_Integral_centzone6 = MVA_BDTBkg_centzone_eval_Xproj_6->Integral(0, BDT_nbins_centzone6+1);

	Float_t BDTSig_accept_centzone6[NbinMax]    = {};
	Float_t BDTBkg_invreject_centzone6[NbinMax] = {};
	Float_t BDTBkg_reject_centzone6[NbinMax]    = {};

	if (!pp_flag) {
		for (int i=0; i<=BDT_nbins_centzone6+1; i++) {
			// Signal Acceptance Integral Ratio
			BDTSig_accept_centzone6[i] = MVA_BDTSig_centzone_eval_Xproj_6->Integral(i,BDT_nbins_centzone6+1)/BDT_Sig_Integral_centzone6;
			BDTBkg_reject_centzone6[i] = (BDT_Bkg_Integral_centzone6 - MVA_BDTBkg_centzone_eval_Xproj_6->Integral(i,BDT_nbins_centzone6+1))/BDT_Bkg_Integral_centzone6;

			// Inverse Background Rejection Integral Ratio
			if (BDTSig_accept_centzone6[i] > 0.16)
				BDTBkg_invreject_centzone6[i] = BDT_Bkg_Integral_centzone6/MVA_BDTBkg_centzone_eval_Xproj_6->Integral(i,BDT_nbins_centzone6+1);
			else
				BDTBkg_invreject_centzone6[i] = BDTBkg_invreject_centzone6[i-1];

			// cout << "sig  : " << BDTSig_accept[i-1]    << endl;
			// cout << "1/bkg: " << BDTBkg_invreject[i-1] << endl;
		}
	}

	TGraph *IP2D_Efficiency        = new TGraph(IP2D_nbins+2,    IP2DSig_accept,    IP2DBkg_invreject);
	TGraph *IP2D_Efficiency2       = new TGraph(IP2D_nbins+2,    IP2DSig_accept,    IP2DBkg_reject);
	TGraph *IP3D_Efficiency        = new TGraph(IP3D_nbins+2,    IP3DSig_accept,    IP3DBkg_invreject);
	TGraph *IP3D_Efficiency2       = new TGraph(IP3D_nbins+2,    IP3DSig_accept,    IP3DBkg_reject);
	TGraph *JF_Efficiency          = new TGraph(JF_nbins+2,      JFSig_accept,      JFBkg_invreject  );
	TGraph *JF_Efficiency2         = new TGraph(JF_nbins+2,      JFSig_accept,      JFBkg_reject);
	TGraph *BDT_Efficiency         = new TGraph(BDT_nbins+2,     BDTSig_accept,     BDTBkg_invreject );
	TGraph *BDT_Efficiency2        = new TGraph(BDT_nbins+2,     BDTSig_accept,     BDTBkg_reject );
	TGraph *BDT_Efficiency_pt1     = new TGraph(BDT_nbins_pt1+2, BDTSig_accept_pt1, BDTBkg_invreject_pt1 );
	TGraph *BDT_Efficiency2_pt1    = new TGraph(BDT_nbins_pt1+2, BDTSig_accept_pt1, BDTBkg_reject_pt1 );
	TGraph *BDT_Efficiency_pt2     = new TGraph(BDT_nbins_pt2+2, BDTSig_accept_pt2, BDTBkg_invreject_pt2 );
	TGraph *BDT_Efficiency2_pt2    = new TGraph(BDT_nbins_pt2+2, BDTSig_accept_pt2, BDTBkg_reject_pt2 );
	TGraph *BDT_Efficiency_pt3     = new TGraph(BDT_nbins_pt3+2, BDTSig_accept_pt3, BDTBkg_invreject_pt3 );
	TGraph *BDT_Efficiency2_pt3    = new TGraph(BDT_nbins_pt3+2, BDTSig_accept_pt3, BDTBkg_reject_pt3 );
	TGraph *BDT_Efficiency_pt4     = new TGraph(BDT_nbins_pt4+2, BDTSig_accept_pt4, BDTBkg_invreject_pt4 );
	TGraph *BDT_Efficiency2_pt4    = new TGraph(BDT_nbins_pt4+2, BDTSig_accept_pt4, BDTBkg_reject_pt4 );
	TGraph *BDT_Efficiency_pt5     = new TGraph(BDT_nbins_pt5+2, BDTSig_accept_pt5, BDTBkg_invreject_pt5 );
	TGraph *BDT_Efficiency2_pt5    = new TGraph(BDT_nbins_pt5+2, BDTSig_accept_pt5, BDTBkg_reject_pt5 );
	TGraph *BDT_Efficiency_pt6     = new TGraph(BDT_nbins_pt6+2, BDTSig_accept_pt6, BDTBkg_invreject_pt6 );
	TGraph *BDT_Efficiency2_pt6    = new TGraph(BDT_nbins_pt6+2, BDTSig_accept_pt6, BDTBkg_reject_pt6 );
	TGraph *BDT_Efficiency_pt7     = new TGraph(BDT_nbins_pt7+2, BDTSig_accept_pt7, BDTBkg_invreject_pt7 );
	TGraph *BDT_Efficiency2_pt7    = new TGraph(BDT_nbins_pt7+2, BDTSig_accept_pt7, BDTBkg_reject_pt7 );
	TGraph *BDT_Efficiency_pt8     = new TGraph(BDT_nbins_pt8+2, BDTSig_accept_pt8, BDTBkg_invreject_pt8 );
	TGraph *BDT_Efficiency2_pt8    = new TGraph(BDT_nbins_pt8+2, BDTSig_accept_pt8, BDTBkg_reject_pt8 );
	TGraph *BDT_Efficiency_abseta1  = new TGraph(BDT_nbins_abseta1+2, BDTSig_accept_abseta1, BDTBkg_invreject_abseta1 );
	TGraph *BDT_Efficiency2_abseta1 = new TGraph(BDT_nbins_abseta1+2, BDTSig_accept_abseta1, BDTBkg_reject_abseta1 );
	TGraph *BDT_Efficiency_abseta2  = new TGraph(BDT_nbins_abseta2+2, BDTSig_accept_abseta2, BDTBkg_invreject_abseta2 );
	TGraph *BDT_Efficiency2_abseta2 = new TGraph(BDT_nbins_abseta2+2, BDTSig_accept_abseta2, BDTBkg_reject_abseta2 );
	TGraph *BDT_Efficiency_abseta3  = new TGraph(BDT_nbins_abseta3+2, BDTSig_accept_abseta3, BDTBkg_invreject_abseta3 );
	TGraph *BDT_Efficiency2_abseta3 = new TGraph(BDT_nbins_abseta3+2, BDTSig_accept_abseta3, BDTBkg_reject_abseta3 );
	TGraph *BDT_Efficiency_phi1       = new TGraph(BDT_nbins_phi1+2, BDTSig_accept_phi1, BDTBkg_invreject_phi1 );
	TGraph *BDT_Efficiency2_phi1      = new TGraph(BDT_nbins_phi1+2, BDTSig_accept_phi1, BDTBkg_reject_phi1 );
	TGraph *BDT_Efficiency_phi2       = new TGraph(BDT_nbins_phi2+2, BDTSig_accept_phi2, BDTBkg_invreject_phi2 );
	TGraph *BDT_Efficiency2_phi2      = new TGraph(BDT_nbins_phi2+2, BDTSig_accept_phi2, BDTBkg_reject_phi2 );
	TGraph *BDT_Efficiency_phi3       = new TGraph(BDT_nbins_phi3+2, BDTSig_accept_phi3, BDTBkg_invreject_phi3 );
	TGraph *BDT_Efficiency2_phi3      = new TGraph(BDT_nbins_phi3+2, BDTSig_accept_phi3, BDTBkg_reject_phi3 );
	TGraph *BDT_Efficiency_phi4       = new TGraph(BDT_nbins_phi4+2, BDTSig_accept_phi4, BDTBkg_invreject_phi4 );
	TGraph *BDT_Efficiency2_phi4      = new TGraph(BDT_nbins_phi4+2, BDTSig_accept_phi4, BDTBkg_reject_phi4 );
	TGraph *BDT_Efficiency_phi5       = new TGraph(BDT_nbins_phi5+2, BDTSig_accept_phi5, BDTBkg_invreject_phi5 );
	TGraph *BDT_Efficiency2_phi5      = new TGraph(BDT_nbins_phi5+2, BDTSig_accept_phi5, BDTBkg_reject_phi5 );
	TGraph *BDT_Efficiency_phi6       = new TGraph(BDT_nbins_phi6+2, BDTSig_accept_phi6, BDTBkg_invreject_phi6 );
	TGraph *BDT_Efficiency2_phi6      = new TGraph(BDT_nbins_phi6+2, BDTSig_accept_phi6, BDTBkg_reject_phi6 );
	TGraph *BDT_Efficiency_centzone1  = new TGraph(BDT_nbins_centzone1+2, BDTSig_accept_centzone1, BDTBkg_invreject_centzone1 );
	TGraph *BDT_Efficiency2_centzone1 = new TGraph(BDT_nbins_centzone1+2, BDTSig_accept_centzone1, BDTBkg_reject_centzone1 );
	TGraph *BDT_Efficiency_centzone2  = new TGraph(BDT_nbins_centzone2+2, BDTSig_accept_centzone2, BDTBkg_invreject_centzone2 );
	TGraph *BDT_Efficiency2_centzone2 = new TGraph(BDT_nbins_centzone2+2, BDTSig_accept_centzone2, BDTBkg_reject_centzone2 );
	TGraph *BDT_Efficiency_centzone3  = new TGraph(BDT_nbins_centzone3+2, BDTSig_accept_centzone3, BDTBkg_invreject_centzone3 );
	TGraph *BDT_Efficiency2_centzone3 = new TGraph(BDT_nbins_centzone3+2, BDTSig_accept_centzone3, BDTBkg_reject_centzone3 );
	TGraph *BDT_Efficiency_centzone4  = new TGraph(BDT_nbins_centzone4+2, BDTSig_accept_centzone4, BDTBkg_invreject_centzone4 );
	TGraph *BDT_Efficiency2_centzone4 = new TGraph(BDT_nbins_centzone4+2, BDTSig_accept_centzone4, BDTBkg_reject_centzone4 );
	TGraph *BDT_Efficiency_centzone5  = new TGraph(BDT_nbins_centzone5+2, BDTSig_accept_centzone5, BDTBkg_invreject_centzone5 );
	TGraph *BDT_Efficiency2_centzone5 = new TGraph(BDT_nbins_centzone5+2, BDTSig_accept_centzone5, BDTBkg_reject_centzone5 );
	TGraph *BDT_Efficiency_centzone6  = new TGraph(BDT_nbins_centzone6+2, BDTSig_accept_centzone6, BDTBkg_invreject_centzone6 );
	TGraph *BDT_Efficiency2_centzone6 = new TGraph(BDT_nbins_centzone6+2, BDTSig_accept_centzone6, BDTBkg_reject_centzone6 );
	TGraph *BDT_Efficiency_pp         = (TGraph*) inputFile_pp->Get( "BDT_Efficiency"  );
	TGraph *BDT_Efficiency2_pp        = (TGraph*) inputFile_pp->Get( "BDT_Efficiency2" );

// Title, Axis, Style

	IP2D_Efficiency->SetNameTitle("IP2D_Efficiency", "IP2D Efficiency");
	IP2D_Efficiency->GetXaxis()->SetTitle("Signal Acceptance");
	IP2D_Efficiency->GetYaxis()->SetTitle("1/Bkg Rejection");
	IP2D_Efficiency->SetLineColor(kBlack);
	IP2D_Efficiency->SetLineWidth(2);
	IP2D_Efficiency->SetMarkerStyle(8);
	IP2D_Efficiency->SetMarkerColor(kRed);
	IP2D_Efficiency->SetMarkerSize(1);

	IP2D_Efficiency2->SetNameTitle("IP2D_Efficiency2", "IP2D Efficiency");
	IP2D_Efficiency2->GetXaxis()->SetTitle("Signal Acceptance");
	IP2D_Efficiency2->GetYaxis()->SetTitle("Bkg Rejection");
	IP2D_Efficiency2->SetLineColor(kBlack);
	IP2D_Efficiency2->SetLineWidth(2);
	IP2D_Efficiency2->SetMarkerStyle(8);
	IP2D_Efficiency2->SetMarkerColor(kRed);
	IP2D_Efficiency2->SetMarkerSize(1);

	IP3D_Efficiency->SetNameTitle("IP3D_Efficiency", "IP3D Efficiency");
	IP3D_Efficiency->GetXaxis()->SetTitle("Signal Acceptance");
	IP3D_Efficiency->GetYaxis()->SetTitle("1/Bkg Rejection");
	IP3D_Efficiency->SetLineColor(kBlack);
	IP3D_Efficiency->SetLineWidth(2);
	IP3D_Efficiency->SetMarkerStyle(8);
	IP3D_Efficiency->SetMarkerColor(kRed);
	IP3D_Efficiency->SetMarkerSize(1);

	IP3D_Efficiency2->SetNameTitle("IP3D_Efficiency2", "IP3D Efficiency");
	IP3D_Efficiency2->GetXaxis()->SetTitle("Signal Acceptance");
	IP3D_Efficiency2->GetYaxis()->SetTitle("Bkg Rejection");
	IP3D_Efficiency2->SetLineColor(kBlack);
	IP3D_Efficiency2->SetLineWidth(2);
	IP3D_Efficiency2->SetMarkerStyle(8);
	IP3D_Efficiency2->SetMarkerColor(kRed);
	IP3D_Efficiency2->SetMarkerSize(1);

	JF_Efficiency->SetNameTitle("JF_Efficiency", "JetFitter Efficiency");
	JF_Efficiency->GetXaxis()->SetTitle("Signal Acceptance");
	JF_Efficiency->GetYaxis()->SetTitle("1/Bkg Rejection");
	JF_Efficiency->SetLineColor(kBlack);
	JF_Efficiency->SetLineWidth(2);
	JF_Efficiency->SetMarkerStyle(8);
	JF_Efficiency->SetMarkerColor(kRed);
	JF_Efficiency->SetMarkerSize(1);

	JF_Efficiency2->SetNameTitle("JF_Efficiency2", "JetFitter Efficiency");
	JF_Efficiency2->GetXaxis()->SetTitle("Signal Acceptance");
	JF_Efficiency2->GetYaxis()->SetTitle("Bkg Rejection");
	JF_Efficiency2->SetLineColor(kBlack);
	JF_Efficiency2->SetLineWidth(2);
	JF_Efficiency2->SetMarkerStyle(8);
	JF_Efficiency2->SetMarkerColor(kRed);
	JF_Efficiency2->SetMarkerSize(1);

	BDT_Efficiency->SetNameTitle("BDT_Efficiency", "BDT Efficiency");
	BDT_Efficiency->GetXaxis()->SetTitle("Signal Acceptance");
	BDT_Efficiency->GetYaxis()->SetTitle("1/Bkg Rejection");
	BDT_Efficiency->SetLineColor(kBlack);
	BDT_Efficiency->SetLineWidth(2);
	BDT_Efficiency->SetMarkerStyle(8);
	BDT_Efficiency->SetMarkerColor(kRed);
	BDT_Efficiency->SetMarkerSize(1);

	BDT_Efficiency2->SetNameTitle("BDT_Efficiency2", "BDT Efficiency");
	BDT_Efficiency2->GetXaxis()->SetTitle("Signal Acceptance");
	BDT_Efficiency2->GetYaxis()->SetTitle("Bkg Rejection");
	BDT_Efficiency2->SetLineColor(kBlack);
	BDT_Efficiency2->SetLineWidth(2);
	BDT_Efficiency2->SetMarkerStyle(8);
	BDT_Efficiency2->SetMarkerColor(kRed);
	BDT_Efficiency2->SetMarkerSize(1);

	BDT_Efficiency_pt1->SetNameTitle("BDT_Efficiency_pt1", "BDT Efficiency by p_{T}");
	BDT_Efficiency_pt1->GetXaxis()->SetTitle("Signal Acceptance");
	BDT_Efficiency_pt1->GetYaxis()->SetTitle("1/Bkg Rejection");
	BDT_Efficiency_pt1->SetLineColor(kBlue);
	BDT_Efficiency_pt1->SetLineWidth(2);
	BDT_Efficiency_pt2->SetLineColor(kBlack);
	BDT_Efficiency_pt2->SetLineWidth(2);
	BDT_Efficiency_pt3->SetLineColor(kGreen);
	BDT_Efficiency_pt3->SetLineWidth(2);
	BDT_Efficiency_pt4->SetLineColor(kOrange);
	BDT_Efficiency_pt4->SetLineWidth(2);
	BDT_Efficiency_pt5->SetLineColor(kViolet);
	BDT_Efficiency_pt5->SetLineWidth(2);
	BDT_Efficiency_pt6->SetLineStyle(6);
	BDT_Efficiency_pt6->SetLineColor(kCyan);
	BDT_Efficiency_pt6->SetLineWidth(2);
	BDT_Efficiency_pt7->SetLineStyle(6);
	BDT_Efficiency_pt7->SetLineColor(kMagenta-9);
	BDT_Efficiency_pt7->SetLineWidth(2);
	BDT_Efficiency_pt8->SetLineStyle(6);
	BDT_Efficiency_pt8->SetLineColor(kYellow+2);
	BDT_Efficiency_pt8->SetLineWidth(2);

	BDT_Efficiency2_pt3->SetNameTitle("BDT_Efficiency2_pt3", "BDT Efficiency by p_{T}");
	BDT_Efficiency2_pt3->GetXaxis()->SetTitle("Signal Acceptance");
	BDT_Efficiency2_pt3->GetYaxis()->SetTitle("Bkg Rejection");
	BDT_Efficiency2_pt1->SetLineColor(kBlue);
	BDT_Efficiency2_pt1->SetLineWidth(2);
	BDT_Efficiency2_pt2->SetLineColor(kBlack);
	BDT_Efficiency2_pt2->SetLineWidth(2);
	BDT_Efficiency2_pt3->SetLineColor(kGreen);
	BDT_Efficiency2_pt3->SetLineWidth(2);
	BDT_Efficiency2_pt4->SetLineColor(kOrange);
	BDT_Efficiency2_pt4->SetLineWidth(2);
	BDT_Efficiency2_pt5->SetLineColor(kViolet);
	BDT_Efficiency2_pt5->SetLineWidth(2);
	BDT_Efficiency2_pt6->SetLineStyle(6);
	BDT_Efficiency2_pt6->SetLineColor(kCyan);
	BDT_Efficiency2_pt6->SetLineWidth(2);
	BDT_Efficiency2_pt7->SetLineStyle(6);
	BDT_Efficiency2_pt7->SetLineColor(kMagenta-9);
	BDT_Efficiency2_pt7->SetLineWidth(2);
	BDT_Efficiency2_pt8->SetLineStyle(6);
	BDT_Efficiency2_pt8->SetLineColor(kYellow+2);
	BDT_Efficiency2_pt8->SetLineWidth(2);

	BDT_Efficiency_abseta3->SetNameTitle("BDT_Efficiency_abseta3", "BDT Efficiency by |#eta|");
	BDT_Efficiency_abseta3->GetXaxis()->SetTitle("Signal Acceptance");
	BDT_Efficiency_abseta3->GetYaxis()->SetTitle("1/Bkg Rejection");
	BDT_Efficiency_abseta1->SetLineColor(kBlue);
	BDT_Efficiency_abseta1->SetLineWidth(2);
	BDT_Efficiency_abseta2->SetLineColor(kBlack);
	BDT_Efficiency_abseta2->SetLineWidth(2);
	BDT_Efficiency_abseta3->SetLineColor(kGreen);
	BDT_Efficiency_abseta3->SetLineWidth(2);

	BDT_Efficiency2_abseta3->SetNameTitle("BDT_Efficiency2_abseta3", "BDT Efficiency by |#eta|");
	BDT_Efficiency2_abseta3->GetXaxis()->SetTitle("Signal Acceptance");
	BDT_Efficiency2_abseta3->GetYaxis()->SetTitle("Bkg Rejection");
	BDT_Efficiency2_abseta1->SetLineColor(kBlue);
	BDT_Efficiency2_abseta1->SetLineWidth(2);
	BDT_Efficiency2_abseta2->SetLineColor(kBlack);
	BDT_Efficiency2_abseta2->SetLineWidth(2);
	BDT_Efficiency2_abseta3->SetLineColor(kGreen);
	BDT_Efficiency2_abseta3->SetLineWidth(2);

	BDT_Efficiency_phi6->SetNameTitle("BDT_Efficiency_phi6", "BDT Efficiency by #phi");
	BDT_Efficiency_phi6->GetXaxis()->SetTitle("Signal Acceptance");
	BDT_Efficiency_phi6->GetYaxis()->SetTitle("1/Bkg Rejection");
	BDT_Efficiency_phi1->SetLineColor(kBlue);
	BDT_Efficiency_phi1->SetLineWidth(2);
	BDT_Efficiency_phi2->SetLineColor(kBlack);
	BDT_Efficiency_phi2->SetLineWidth(2);
	BDT_Efficiency_phi3->SetLineColor(kGreen);
	BDT_Efficiency_phi3->SetLineWidth(2);
	BDT_Efficiency_phi4->SetLineColor(kOrange);
	BDT_Efficiency_phi4->SetLineWidth(2);
	BDT_Efficiency_phi5->SetLineColor(kViolet);
	BDT_Efficiency_phi5->SetLineWidth(2);
	BDT_Efficiency_phi6->SetLineColor(kCyan);
	BDT_Efficiency_phi6->SetLineWidth(2);

	BDT_Efficiency2_phi6->SetNameTitle("BDT_Efficiency2_phi6", "BDT Efficiency by #phi");
	BDT_Efficiency2_phi6->GetXaxis()->SetTitle("Signal Acceptance");
	BDT_Efficiency2_phi6->GetYaxis()->SetTitle("Bkg Rejection");
	BDT_Efficiency2_phi1->SetLineColor(kBlue);
	BDT_Efficiency2_phi1->SetLineWidth(2);
	BDT_Efficiency2_phi2->SetLineColor(kBlack);
	BDT_Efficiency2_phi2->SetLineWidth(2);
	BDT_Efficiency2_phi3->SetLineColor(kGreen);
	BDT_Efficiency2_phi3->SetLineWidth(2);
	BDT_Efficiency2_phi4->SetLineColor(kOrange);
	BDT_Efficiency2_phi4->SetLineWidth(2);
	BDT_Efficiency2_phi5->SetLineColor(kViolet);
	BDT_Efficiency2_phi5->SetLineWidth(2);
	BDT_Efficiency2_phi6->SetLineColor(kCyan);
	BDT_Efficiency2_phi6->SetLineWidth(2);

	BDT_Efficiency_pp       ->SetNameTitle("BDT_Efficiency_pp", "BDT Efficiency by centrality");
	BDT_Efficiency_pp       ->GetXaxis()->SetTitle("Signal Acceptance");
	BDT_Efficiency_pp       ->GetYaxis()->SetTitle("1/Bkg Rejection");
	BDT_Efficiency_centzone1->SetLineColor(kBlue);
	BDT_Efficiency_centzone1->SetLineWidth(2);
	BDT_Efficiency_centzone2->SetLineColor(kBlack);
	BDT_Efficiency_centzone2->SetLineWidth(2);
	BDT_Efficiency_centzone3->SetLineColor(kGreen);
	BDT_Efficiency_centzone3->SetLineWidth(2);
	BDT_Efficiency_centzone4->SetLineColor(kOrange);
	BDT_Efficiency_centzone4->SetLineWidth(2);
	BDT_Efficiency_centzone5->SetLineColor(kViolet);
	BDT_Efficiency_centzone5->SetLineWidth(2);
	BDT_Efficiency_centzone6->SetLineColor(kGreen);
	BDT_Efficiency_centzone6->SetLineWidth(2);
	BDT_Efficiency_pp       ->SetLineColor(kOrange);
	BDT_Efficiency_pp       ->SetLineWidth(2);

	BDT_Efficiency2_pp       ->SetNameTitle("BDT_Efficiency2_pp", "BDT Efficiency by centrality");
	BDT_Efficiency2_pp       ->GetXaxis()->SetTitle("Signal Acceptance");
	BDT_Efficiency2_pp       ->GetYaxis()->SetTitle("Bkg Rejection");
	BDT_Efficiency2_centzone1->SetLineColor(kBlue);
	BDT_Efficiency2_centzone1->SetLineWidth(2);
	BDT_Efficiency2_centzone2->SetLineColor(kBlack);
	BDT_Efficiency2_centzone2->SetLineWidth(2);
	BDT_Efficiency2_centzone3->SetLineColor(kGreen);
	BDT_Efficiency2_centzone3->SetLineWidth(2);
	BDT_Efficiency2_centzone4->SetLineColor(kOrange);
	BDT_Efficiency2_centzone4->SetLineWidth(2);
	BDT_Efficiency2_centzone5->SetLineColor(kViolet);
	BDT_Efficiency2_centzone5->SetLineWidth(2);
	BDT_Efficiency2_centzone6->SetLineColor(kGreen);
	BDT_Efficiency2_centzone6->SetLineWidth(2);
	BDT_Efficiency2_pp       ->SetLineColor(kOrange);
	BDT_Efficiency2_pp       ->SetLineWidth(2);

// Write to output file

	IP2D_Efficiency->Write();
	IP2D_Efficiency2->Write();
	IP3D_Efficiency->Write();
	IP3D_Efficiency2->Write();
	JF_Efficiency->Write();
	JF_Efficiency2->Write();
	BDT_Efficiency->Write();
	BDT_Efficiency2->Write();
	BDT_Efficiency_pt1->Write();
	BDT_Efficiency_pt2->Write();
	BDT_Efficiency_pt3->Write();
	BDT_Efficiency_pt4->Write();
	BDT_Efficiency_pt5->Write();
	BDT_Efficiency2_pt1->Write();
	BDT_Efficiency2_pt2->Write();
	BDT_Efficiency2_pt3->Write();
	BDT_Efficiency2_pt4->Write();
	BDT_Efficiency2_pt5->Write();
	BDT_Efficiency_abseta1->Write();
	BDT_Efficiency_abseta2->Write();
	BDT_Efficiency_abseta3->Write();
	BDT_Efficiency2_abseta1->Write();
	BDT_Efficiency2_abseta2->Write();
	BDT_Efficiency2_abseta3->Write();
	BDT_Efficiency_phi1->Write();
	BDT_Efficiency_phi2->Write();
	BDT_Efficiency_phi3->Write();
	BDT_Efficiency_phi4->Write();
	BDT_Efficiency_phi5->Write();
	BDT_Efficiency_phi6->Write();
	BDT_Efficiency2_phi1->Write();
	BDT_Efficiency2_phi2->Write();
	BDT_Efficiency2_phi3->Write();
	BDT_Efficiency2_phi4->Write();
	BDT_Efficiency2_phi5->Write();
	BDT_Efficiency2_phi6->Write();
	BDT_Efficiency_centzone1->Write();
	BDT_Efficiency_centzone2->Write();
	BDT_Efficiency_centzone3->Write();
	BDT_Efficiency_centzone4->Write();
	BDT_Efficiency_centzone5->Write();
	BDT_Efficiency_centzone6->Write();
	BDT_Efficiency2_centzone1->Write();
	BDT_Efficiency2_centzone2->Write();
	BDT_Efficiency2_centzone3->Write();
	BDT_Efficiency2_centzone4->Write();
	BDT_Efficiency2_centzone5->Write();
	BDT_Efficiency2_centzone6->Write();

// Draw, Legend

	IP2D_Efficiency->Draw("ALP");
	c1->SetLogy(1);
	IP2D_Efficiency->GetXaxis()->SetRangeUser(0.15, 1.);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/ip2d_efficiency.png");

	IP2D_Efficiency2->Draw("ALP");
	c1->SetLogy(0);
	IP2D_Efficiency2->GetXaxis()->SetRangeUser(0.15, 1.);
	IP2D_Efficiency2->GetYaxis()->SetRangeUser(0., 1.05);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/ip2d_efficiency2.png");

	IP3D_Efficiency->Draw("ALP");
	c1->SetLogy(1);
	IP3D_Efficiency->GetXaxis()->SetRangeUser(0.15, 1.);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/ip3d_efficiency.png");

	IP3D_Efficiency2->Draw("ALP");
	c1->SetLogy(0);
	IP3D_Efficiency2->GetXaxis()->SetRangeUser(0.15, 1.);
	IP3D_Efficiency2->GetYaxis()->SetRangeUser(0., 1.05);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/ip3d_efficiency2.png");

	JF_Efficiency->Draw("ALP");
	c1->SetLogy(1);
	JF_Efficiency->GetXaxis()->SetRangeUser(0.15, 1.);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/jf_efficiency.png");

	JF_Efficiency2->Draw("ALP");
	c1->SetLogy(0);
	JF_Efficiency2->GetXaxis()->SetRangeUser(0.15, 1.);
	JF_Efficiency2->GetYaxis()->SetRangeUser(0., 1.05);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/jf_efficiency2.png");

	BDT_Efficiency->Draw("ALP");
	c1->SetLogy(1);
	BDT_Efficiency->GetXaxis()->SetRangeUser(0.15, 1.);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/bdt_efficiency.png");

	BDT_Efficiency2->Draw("ALP");
	c1->SetLogy(0);
	BDT_Efficiency2->GetXaxis()->SetRangeUser(0.15, 1.);
	BDT_Efficiency2->GetYaxis()->SetRangeUser(0., 1.05);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/bdt_efficiency2.png");

	BDT_Efficiency->SetLineColor(kRed);

	BDT_Efficiency_pt1->Draw("AL");
	BDT_Efficiency_pt3->Draw("same");
	BDT_Efficiency->Draw("same");
	BDT_Efficiency_pt2->Draw("same");
	BDT_Efficiency_pt4->Draw("same");
	BDT_Efficiency_pt5->Draw("same");
	if (pp_flag) {
		BDT_Efficiency_pt6->Draw("same");
		BDT_Efficiency_pt7->Draw("same");
		BDT_Efficiency_pt8->Draw("same");		
	}

	leg->Clear();
	leg->SetX1NDC(0.61);
	leg->SetY1NDC(0.66);
	leg->AddEntry(BDT_Efficiency,     "All",                       "l");
	leg->AddEntry(BDT_Efficiency_pt1, "p_{T} #in [100, 120] GeV ", "l");
	leg->AddEntry(BDT_Efficiency_pt2, "p_{T} #in ]120, 140] GeV ", "l");
	leg->AddEntry(BDT_Efficiency_pt3, "p_{T} #in ]140, 160] GeV ", "l");
	leg->AddEntry(BDT_Efficiency_pt4, "p_{T} #in ]160, 180] GeV ", "l");
	leg->AddEntry(BDT_Efficiency_pt5, "p_{T} #in ]180, 200] GeV ", "l");
	if (pp_flag) {
		leg->SetY1NDC(0.55);
		leg->AddEntry(BDT_Efficiency_pt6, "p_{T} #in ]200, 300] GeV ", "l");
		leg->AddEntry(BDT_Efficiency_pt7, "p_{T} #in ]300, 400] GeV ", "l");
		leg->AddEntry(BDT_Efficiency_pt8, "p_{T} #in ]400, 500] GeV ", "l");
	}
	leg->Draw();

	c1->SetLogy(1);
	BDT_Efficiency_pt1->GetXaxis()->SetRangeUser(0.15, 1.);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/bdt_efficiency_pt.png");

	BDT_Efficiency2->SetLineColor(kRed);

	BDT_Efficiency2_pt3->Draw("AL");
	BDT_Efficiency2->Draw("same");
	BDT_Efficiency2_pt1->Draw("same");
	BDT_Efficiency2_pt2->Draw("same");
	BDT_Efficiency2_pt4->Draw("same");
	BDT_Efficiency2_pt5->Draw("same");
	if (pp_flag) {
		BDT_Efficiency2_pt6->Draw("same");
		BDT_Efficiency2_pt7->Draw("same");
		BDT_Efficiency2_pt8->Draw("same");		
	}

	leg->Draw();

	c1->SetLogy(0);
	BDT_Efficiency2_pt3->GetXaxis()->SetLimits(0.15, 1.4);
	BDT_Efficiency2_pt3->GetYaxis()->SetRangeUser(0., 1.2);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/bdt_efficiency2_pt.png");

	BDT_Efficiency_abseta3->Draw("AL");
	BDT_Efficiency->Draw("same");
	BDT_Efficiency_abseta1->Draw("same");
	BDT_Efficiency_abseta2->Draw("same");

	leg->Clear();
	leg->SetX1NDC(0.73);
	leg->SetY1NDC(0.72);
	leg->AddEntry(BDT_Efficiency,         "All",               "l");
	leg->AddEntry(BDT_Efficiency_abseta1, "|#eta| #in [0, 1]", "l");
	leg->AddEntry(BDT_Efficiency_abseta2, "|#eta| #in ]1, 2]", "l");
	leg->AddEntry(BDT_Efficiency_abseta3, "|#eta| #in ]2, 2.5]", "l");
	leg->Draw();

	c1->SetLogy(1);
	BDT_Efficiency_abseta3->GetXaxis()->SetRangeUser(0.15, 1.);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/bdt_efficiency_abseta.png");

	BDT_Efficiency2->SetLineColor(kRed);

	BDT_Efficiency2_abseta3->Draw("AL");
	BDT_Efficiency2->Draw("same");
	BDT_Efficiency2_abseta1->Draw("same");
	BDT_Efficiency2_abseta2->Draw("same");

	leg->Draw();

	c1->SetLogy(0);
	BDT_Efficiency2_abseta3->GetXaxis()->SetLimits(0.15, 1.1);
	BDT_Efficiency2_abseta3->GetYaxis()->SetRangeUser(0., 1.2);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/bdt_efficiency2_abseta.png");

	BDT_Efficiency_phi6->Draw("AL");
	BDT_Efficiency->Draw("same");
	BDT_Efficiency_phi1->Draw("same");
	BDT_Efficiency_phi2->Draw("same");
	BDT_Efficiency_phi3->Draw("same");
	BDT_Efficiency_phi4->Draw("same");
	BDT_Efficiency_phi5->Draw("same");

	leg->Clear();
	leg->SetX1NDC(0.62);
	leg->SetY1NDC(0.63);
	leg->AddEntry(BDT_Efficiency,      "All",                            "l");
	leg->AddEntry(BDT_Efficiency_phi1, "#phi #in [-#pi, -2#pi/3] rad",   "l");
	leg->AddEntry(BDT_Efficiency_phi2, "#phi #in ]-2#pi/3, -#pi/3] rad", "l");
	leg->AddEntry(BDT_Efficiency_phi3, "#phi #in ]-#pi/3, 0] rad",       "l");
	leg->AddEntry(BDT_Efficiency_phi4, "#phi #in ]0, #pi/3] rad",        "l");
	leg->AddEntry(BDT_Efficiency_phi5, "#phi #in ]#pi/3, 2#pi/3] rad",   "l");
	leg->AddEntry(BDT_Efficiency_phi6, "#phi #in ]2#pi/3, #pi] rad",     "l");
	leg->Draw();

	c1->SetLogy(1);
	BDT_Efficiency_phi6->GetXaxis()->SetRangeUser(0.15, 1.);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/bdt_efficiency_phi.png");

	BDT_Efficiency2->SetLineColor(kRed);

	BDT_Efficiency2_phi6->Draw("AL");
	BDT_Efficiency2->Draw("same");
	BDT_Efficiency2_phi1->Draw("same");
	BDT_Efficiency2_phi2->Draw("same");
	BDT_Efficiency2_phi3->Draw("same");
	BDT_Efficiency2_phi4->Draw("same");
	BDT_Efficiency2_phi5->Draw("same");

	leg->Draw();

	c1->SetLogy(0);
	BDT_Efficiency2_phi6->GetXaxis()->SetLimits(0.15, 1.4);
	BDT_Efficiency2_phi6->GetYaxis()->SetRangeUser(0., 1.2);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/bdt_efficiency2_phi.png");

	if (!pp_flag) {
		BDT_Efficiency_pp->Draw("AL");
		BDT_Efficiency->Draw("same");
		BDT_Efficiency_centzone1->Draw("same");
		BDT_Efficiency_centzone2->Draw("same");
		// BDT_Efficiency_centzone3->Draw("same");
		// BDT_Efficiency_centzone4->Draw("same");
		// BDT_Efficiency_centzone5->Draw("same");
		BDT_Efficiency_centzone6->Draw("same");

		leg->Clear();
		leg->SetX1NDC(0.58);
		leg->SetY1NDC(0.69);
		leg->AddEntry(BDT_Efficiency,           "All",                       "l");
		leg->AddEntry(BDT_Efficiency_centzone1, "Centrality #in [0, 20] %",  "l");
		leg->AddEntry(BDT_Efficiency_centzone2, "Centrality #in ]20, 40] %", "l");
		// leg->AddEntry(BDT_Efficiency_centzone3, "Centrality #in ]40, 60] %", "l");
		// leg->AddEntry(BDT_Efficiency_centzone4, "Centrality #in ]60, 80] %", "l");
	    // leg->AddEntry(BDT_Efficiency_centzone5, "Centrality #in ]80, 100] %", "l");
	    leg->AddEntry(BDT_Efficiency_centzone6, "Centrality #in ]40, 80] %", "l");
	    leg->AddEntry(BDT_Efficiency_pp,        "p+p MC Sample",             "l");
		leg->Draw();

		c1->SetLogy(1);
		BDT_Efficiency_pp->GetXaxis()->SetRangeUser(0.15, 1.);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/bdt_efficiency_centzone.png");

		BDT_Efficiency2->SetLineColor(kRed);

		BDT_Efficiency2_pp->Draw("AL");
		BDT_Efficiency2->Draw("same");
		BDT_Efficiency2_centzone1->Draw("same");
		BDT_Efficiency2_centzone2->Draw("same");
		// BDT_Efficiency2_centzone3->Draw("same");
		// BDT_Efficiency2_centzone4->Draw("same");
		// BDT_Efficiency2_centzone5->Draw("same");
		BDT_Efficiency2_centzone6->Draw("same");

		leg->Draw();

		c1->SetLogy(0);
		BDT_Efficiency2_pp->GetXaxis()->SetLimits(0.15, 1.4);
		BDT_Efficiency2_pp->GetYaxis()->SetRangeUser(0., 1.2);
		c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
		c1->Print("plots/bdt_efficiency2_centzone.png");
	}

	// Draw with input variables

	JF_Efficiency->SetTitle("Input vs Output Efficiencies");
	IP2D_Efficiency->SetLineColor(kRed);
	IP3D_Efficiency->SetLineColor(kBlue);
	JF_Efficiency->SetLineColor(kCyan);
	BDT_Efficiency->SetLineColor(kBlack);

	BDT_Efficiency->Draw("AL");
	JF_Efficiency->Draw("same");
	IP2D_Efficiency->Draw("same");
	IP3D_Efficiency->Draw("same");

	leg->Clear();
	leg->SetX1NDC(0.77);
	leg->SetY1NDC(0.72);
	leg->AddEntry(BDT_Efficiency,  "BDT",       "l");
	leg->AddEntry(IP2D_Efficiency, "IP2D",      "l");
	leg->AddEntry(IP3D_Efficiency, "IP3D",      "l");
	leg->AddEntry(JF_Efficiency,   "JetFitter", "l");
	leg->Draw();

	c1->SetLogy(1);
	BDT_Efficiency->GetXaxis()->SetRangeUser(0.15, 1.);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/in_vs_out_efficiency.png");

	BDT_Efficiency2->SetTitle("Input vs Output Efficiencies2");
	IP2D_Efficiency2->SetLineColor(kRed);
	IP3D_Efficiency2->SetLineColor(kBlue);
	JF_Efficiency2->SetLineColor(kCyan);
	BDT_Efficiency2->SetLineColor(kBlack);

	BDT_Efficiency2->Draw("AL");
	JF_Efficiency2->Draw("same");
	IP2D_Efficiency2->Draw("same");
	IP3D_Efficiency2->Draw("same");

	leg->Draw();

	c1->SetLogy(0);
	BDT_Efficiency2->GetXaxis()->SetLimits(0.15, 1.2);
	BDT_Efficiency2->GetYaxis()->SetRangeUser(0., 1.2);
	c1->Modified();	c1->Update(); while(c1->WaitPrimitive()) gSystem->ProcessEvents();
	c1->Print("plots/in_vs_out_efficiency2.png");

//----END--------------------------------------------------------

	// Get elapsed time
	sw.Stop();
	cout << "\n---- End of analysis: "; sw.Print();

	inputFile->Close();
	outputFile->Close();

	cout << "===> Wrote root file: " << outputFile->GetName() << endl;
	cout << "===> NewTMVAAnalysis is done!\n" << endl;	

	delete c1;
	delete outputFile;
	delete inputFile_pp;
	delete inputFile;
}

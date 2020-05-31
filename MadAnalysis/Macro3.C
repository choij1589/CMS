#include <string>

void Macro3() {
    vector<TFile*> files;
    for (unsigned int i = 0; i < 4; i++) {
        string mass;
        if (i == 0) mass = "200";
        else if (i == 1) mass = "500";
        else if (i == 2) mass = "900";
        else if (i == 3) mass = "1600";
        TString filename = "test_SR" + to_string(i+1) + "_go" + mass + ".root";
        TFile* f = new TFile(filename);

        files.push_back(f);
    }

    //===== Prepare Delta plots =====
    TH2D* Delta_before[4];
    TH2D* Delta_after[4];

    for (int i = 0; i < 4; i++) {
        TString histname_before = "Mass_HT_beforeDelta_" + to_string(i+1);
        TString histname_after = "Mass_HT_afterDelta_" + to_string(i+1);
        Delta_before[i] = (TH2D*)files.at(i)->Get(histname_before);
        Delta_after[i] = (TH2D*)files.at(i)->Get(histname_after);

        Delta_before[i]->SetStats(0);
        Delta_after[i]->SetStats(0);
        TString title = "SR" + to_string(i+1);
        Delta_before[i]->SetTitle(title);
        Delta_after[i]->SetTitle(title);

        Delta_before[i]->GetXaxis()->SetTitle("|P_{T}|_{ijk} [GeV]");
        Delta_before[i]->GetYaxis()->SetTitle("M_{ijk} [GeV]");
        Delta_after[i]->GetXaxis()->SetTitle("|P_{T}|_{ijk} [GeV]");
        Delta_after[i]->GetYaxis()->SetTitle("M_{ijk} [GeV]");

		Delta_before[i]->GetXaxis()->SetTitleOffset(1.2);
		Delta_before[i]->GetYaxis()->SetTitleOffset(1.2);
		Delta_after[i]->GetXaxis()->SetTitleOffset(1.2);
		Delta_after[i]->GetYaxis()->SetTitleOffset(1.2);
		
		Delta_before[i]->GetXaxis()->SetTitleSize(0.04);
		Delta_before[i]->GetYaxis()->SetTitleSize(0.04);
		Delta_after[i]->GetXaxis()->SetTitleSize(0.04);
		Delta_after[i]->GetYaxis()->SetTitleSize(0.04);

		Delta_before[i]->GetXaxis()->SetRangeUser(0, 2000);
		Delta_before[i]->GetYaxis()->SetRangeUser(0, 2000);
		Delta_after[i]->GetXaxis()->SetRangeUser(0, 2000);
		Delta_after[i]->GetYaxis()->SetRangeUser(0, 2000);
    }

    TCanvas* cvs_before = new TCanvas("cvs_before", "cvs_before", 1600, 900);
    TPad* pad_before1 = new TPad("pad_before1", "pad_before1", 0, 0.5, 0.5, 1);
    TPad* pad_before2 = new TPad("pad_before2", "pad_before2", 0.5, 0.5, 1, 1);
    TPad* pad_before3 = new TPad("pad_before3", "pad_before3", 0, 0, 0.5, 0.5);
    TPad* pad_before4 = new TPad("pad_before4", "pad_before4", 0.5, 0., 1, 0.5);

    pad_before1->cd(); Delta_before[0]->Draw("colz");
    pad_before2->cd(); Delta_before[1]->Draw("colz");
    pad_before3->cd(); Delta_before[2]->Draw("colz");
    pad_before4->cd(); Delta_before[3]->Draw("colz");

    TCanvas* cvs_after = new TCanvas("cvs_after", "cvs_after", 1600, 900);
    TPad* pad_after1 = new TPad("pad_after1", "pad_after1", 0, 0.5, 0.5, 1);
    TPad* pad_after2 = new TPad("pad_after2", "pad_after2", 0.5, 0.5, 1, 1);
    TPad* pad_after3 = new TPad("pad_after3", "pad_after3", 0, 0, 0.5, 0.5);
    TPad* pad_after4 = new TPad("pad_after4", "pad_after4", 0.5, 0., 1, 0.5);

    pad_after1->cd(); Delta_after[0]->Draw("colz");
    pad_after2->cd(); Delta_after[1]->Draw("colz");
    pad_after3->cd(); Delta_after[2]->Draw("colz");
    pad_after4->cd(); Delta_after[3]->Draw("colz");

    cvs_before->cd(); pad_before1->Draw(); pad_before2->Draw(); pad_before3->Draw(); pad_before4->Draw();
    cvs_after->cd(); pad_after1->Draw(); pad_after2->Draw(); pad_after3->Draw(); pad_after4->Draw();

    //cvs_before->Draw();
    cvs_before->SaveAs("Delta_before.pdf");
    //cvs_after->Draw();
    cvs_after->SaveAs("Delta_after.pdf");
}

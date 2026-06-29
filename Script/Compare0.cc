void Compare0()
{

    auto file = TFile::Open(Form("/Users/xiongzheng/software/Hadr03/Root/Proton_BGO_10TeV.root"));
    auto h1   = (TH1D*)file->Get("1");
    auto h2   = (TH1D*)file->Get("2");
    auto h3   = (TH1D*)file->Get("3");
    auto h4   = (TH1D*)file->Get("4");
    auto h5   = (TH1D*)file->Get("5");

    auto c1 = new TCanvas("c1","c1",1200,900);
    c1->cd();
    gPad->SetGrid(1,1);
    gStyle->SetOptStat(0);
    h2->SetLineColor(kBlue);h2->SetLineWidth(2);
    h3->SetLineColor(kRed);h3->SetLineWidth(2);
    h4->SetLineColor(kOrange-3);h4->SetLineWidth(2);
    h5->SetLineColor(kMagenta);h5->SetLineWidth(2);
    gPad->SetLogy(1); 

    h2->GetXaxis()->SetRangeUser(9.9,10);
    h2->Draw("hist");
    h3->Draw("histsame");
    h4->Draw("histsame");
    // h5->Draw("histsame");

    // gPad->Update();

    cout << "h4 " << h4->Integral() << endl;
    cout << "h3 " << h4->Integral() << endl;

    auto lg1 = new TLegend(0.38,0.68,0.78,0.88);
    lg1->AddEntry(h2,"most energetic secondary","l");
    lg1->AddEntry(h3,"most energetic secondary && ==primary","l");
    lg1->AddEntry(h4,"most energetic secondary && ==primary && QE","l");
    lg1->Draw();

    c1->SaveAs("/Users/xiongzheng/software/Hadr03/Script/Proton_BGO_10TeV.pdf");


}
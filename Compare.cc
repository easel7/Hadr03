void Compare()
{
    auto file = TFile::Open("/Users/xiongzheng/software/Hadr03/build/proton_BGO.root");
    auto h2   = (TH1D*)file->Get("2");
    auto h3   = (TH1D*)file->Get("3");

    auto c1 = new TCanvas("c1","c1",1200,900);
    c1->cd();
    h2->SetLineColor(kBlue);
    h3->SetLineColor(kRed);
    h2->Draw("hist");
    h3->Draw("histsame");
}
void Compare2()
{

    int energy[13] = {10,12,16,20,25,32,40,50,63,80,100,1000,10000};
    double  Energy[13] ={0};
    double Ratio[13] = {0};

    for (int ii = 0; ii <13 ; ii++)
    {
        auto file = TFile::Open(Form("/Users/xiongzheng/software/Hadr03/Root2/Proton_BGO_%dGeV.root",energy[ii]));
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
        // gPad->SetLogy(1); 
        // h2->GetXaxis()->SetLimits(    );
        h2->Draw("hist");
        h3->Draw("histsame");
        h4->Draw("histsame");
        // h5->Draw("histsame");
        // cout << "h4 " << h4->Integral() << endl;
        // cout << "h3 " << h4->Integral() << endl;
        cout << " h4 / h2 = "<<  1- h4->Integral() / h2->Integral() << endl;
        
        if(ii<11)        Energy[ii] = pow(10,0.1*ii+1);
        else if (ii ==11) {Energy[ii] =1e3; }
        else              {Energy[ii] =1e4; }

        cout << Energy[ii] << endl;
        Ratio[ii] = 1- h4->Integral() / h2->Integral();

        auto lg1 = new TLegend(0.38,0.68,0.78,0.88);
        lg1->AddEntry(h2,"most energetic secondary","l");
        lg1->AddEntry(h3,"most energetic secondary && ==primary","l");
        lg1->AddEntry(h4,"most energetic secondary && ==primary && QE","l");
        lg1->Draw();
        c1->SaveAs(Form("/Users/xiongzheng/software/Hadr03/Script/Proton2_BGO_%dGeV.pdf",energy[ii]));
    } 


    auto c2 = new TCanvas("c2","c2",1200,900);
    auto gr1 = new TGraph(13,Energy,Ratio);
    gPad->SetLogx(1);
    gPad->SetGrid(1,1);
    gr1->GetYaxis()->SetRangeUser(0.89,0.95);
    gr1->GetXaxis()->SetLimits(9e0,2e4);
    gr1->SetMarkerStyle(20);
    gr1->SetTitle("; Energy (GeV) ;Correction Factor ");
    gr1->Draw("ALP");
    c2->SaveAs("/Users/xiongzheng/software/Hadr03/Script/Proton2_Correction.pdf");
}
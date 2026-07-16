void Canvas_XS_Base()
{
    auto file1 = TFile::Open("/Users/xiongzheng/software/Hadr00/build/proton_BGO.root");
    auto hist6 = (TH1D*)file1->Get("h4");
    auto file2 = TFile::Open("/Users/xiongzheng/software/Hadr00/build/deuteron_BGO.root");
    auto hist7 = (TH1D*)file2->Get("h4");
    auto file3 = TFile::Open("/Users/xiongzheng/software/Hadr00/build/alpha_BGO.root");
    auto hist8 = (TH1D*)file3->Get("h4");

    auto fileXS = TFile::Open("/Users/xiongzheng/software/Hadr03/Script/Proton2_Correction.root");
    auto gre_QE  = (TGraph*)fileXS->Get("QE_Truth_G4_11");

    int Nbins = hist6->GetNbinsX();
    cout << "Nbins = " << Nbins << endl;
    double KN_Energy[60] = {0};       double KN_Deuteron[60] = {0}; double KN_Proton[60] = {0};double KN_Helium4[60] = {0}; 
    
    double KN_Dp_Ratio_1[60]={0};  
    double KN_Dp_Ratio_2[60]={0};
    double KN_Dp_Ratio_3[60]={0};

    double KN_Gamma_1[60]  = {0};
    double KN_Gamma_2[60]  = {0};
    double KN_Gamma_3[60]  = {0};

    double alpha[60]   = {0};
    
    double kappa[7] = {0};
    double kappa_EPOS[7] = {0};


    double XS_QE_E[41] = {0};
    double XS_QE_proton[41] = {0};
    double XS_QE[41] = {0.1047   , 0.097465 , 0.0903725, 0.0842575, 0.07878 , 0.07443  ,
           0.07056  , 0.0670775, 0.064135 , 0.06161  , 0.0595825, 0.05796  ,
           0.056615 , 0.055525 , 0.0546475, 0.0538575, 0.05335  , 0.0529325,
           0.052575 , 0.0523   , 0.052085 , 0.052015 , 0.0519725, 0.0520275,
           0.05197  , 0.0518925, 0.0523225, 0.052495 , 0.0525175, 0.052765 ,
           0.052995 , 0.0518925, 0.0515950, 0.0499500, 0.0488575, 0.0492875, 
           0.0466775, 0.0488775, 0.0465475, 0.0443225, 0.0426000};
    for (int i = 0 ; i< 41 ; i++) 
    {
        XS_QE_E[i] = pow(10,1+0.1*i);
        // XS_QE_proton[i] = 1 - XS_QE[i];
        gre_QE->GetPoint(i, XS_QE_E[i] ,XS_QE_proton[i]);
    }
    // auto gre_QE = new TGraph(41 , XS_QE_E, XS_QE_proton);
    double v_temp                  = 1.108/  gre_QE->Eval(1e3);

    for (int ii = 0 ; ii < Nbins ; ii++)
    {
        KN_Energy[ii]   = pow(10,hist6->GetBinCenter(ii+1)-3);
        file1->cd(); KN_Proton[ii]   = hist6->GetBinContent(ii+1)*1e3;
        file2->cd(); KN_Deuteron[ii] = hist7->GetBinContent(ii+1)*1e3;
        file3->cd(); KN_Helium4[ii]  = hist8->GetBinContent(ii+1)*1e3;
        KN_Dp_Ratio_1[ii]              = KN_Deuteron[ii] /  KN_Proton[ii] ;
        KN_Dp_Ratio_2[ii]              = KN_Dp_Ratio_1[ii] / gre_QE->Eval(KN_Energy[ii] );
        if(KN_Energy[ii] < 1e3) {KN_Dp_Ratio_3[ii]  = KN_Dp_Ratio_2[ii] ;                    }
        else                    {KN_Dp_Ratio_3[ii]  = KN_Dp_Ratio_1[ii] / gre_QE->Eval(1e3); }

        if(KN_Energy[ii] > 1.1e5)  KN_Dp_Ratio_2[ii] = 1e-9 ;
        alpha[ii]                      = gre_QE->Eval(1e3) / gre_QE->Eval(KN_Energy[ii] ) ; 
        KN_Gamma_1[ii]                 = 1 - ( KN_Dp_Ratio_1[ii]  - 1.108 )  / 1.108;
        KN_Gamma_2[ii]                 = 1 - ( KN_Dp_Ratio_1[ii] * alpha[ii] - 1.108  )  / 1.108;
        KN_Gamma_3[ii]                 = 1 - ( KN_Dp_Ratio_2[ii]  - v_temp )  / v_temp;

        cout << KN_Energy[ii] << " , " << alpha[ii] << " , " <<  gre_QE->Eval(KN_Energy[ii] ) << endl;

    }
    auto gre6 = new TGraph(Nbins,KN_Energy, KN_Proton);     gre6->SetLineColor(kRed);
    auto gre7 = new TGraph(Nbins,KN_Energy, KN_Deuteron);   gre7->SetLineColor(kBlue);
    auto gre8 = new TGraph(Nbins,KN_Energy, KN_Helium4);    gre8->SetLineColor(kGreen-3);
    auto gre9_1 = new TGraph(Nbins,KN_Energy, KN_Dp_Ratio_1);   gre9_1->SetLineColor(kBlack);
    auto gre9_2 = new TGraph(Nbins ,KN_Energy, KN_Dp_Ratio_2);  gre9_2->SetLineColor(kRed);
    auto gre9_3 = new TGraph(Nbins ,KN_Energy, KN_Dp_Ratio_3);  gre9_3->SetLineColor(kRed); gre9_3->SetLineStyle(9);
    auto gre10_1 = new TGraph(Nbins,KN_Energy, KN_Gamma_1);     gre10_1->SetLineColor(kBlack);
    auto gre10_2 = new TGraph(Nbins,KN_Energy, KN_Gamma_2);     gre10_2->SetLineColor(kRed);
    auto gre10_3 = new TGraph(Nbins,KN_Energy, KN_Gamma_3);     gre10_3->SetLineColor(kRed); gre10_3->SetLineStyle(9);

    auto gre_alpha = new TGraph(Nbins , KN_Energy, alpha);

    gre6->SetName("Geant4_P");
    gre7->SetName("Geant4_D");
    gre8->SetName("Geant4_H");
    gre9_1->SetName("Geant4_Ratio_Dp_OLD");
    gre9_2->SetName("Geant4_Ratio_Dp_Check");
    gre9_3->SetName("Geant4_Ratio_Dp_NEW");
    gre10_1->SetName("Geant4_Gamma_OLD");
    gre10_2->SetName("Geant4_Gamma_NEW");
    gre10_3->SetName("Geant4_Gamma_Check");

    gre9_2->SetTitle(";Ek (GeV);#sigma^{ine}_{D,G4} / (#sigma^{ine}_{P,G4} #upoint f_{QE}(E))");
    gre9_3->SetTitle(";Ek (GeV);#sigma^{ine}_{D,G4} / #sigma^{ine}_{P,G4} #upoint #alpha(E) ");

    gre10_2->SetTitle("(1+#kappa#upoint#gamma') #sigma_{D,G4} = #sigma_{D,exp}, (1+#kappa) #sigma_{p,G4} = #sigma_{p,exp};Ek (GeV);#gamma'");
    gre10_3->SetTitle("(1+#kappa#upoint#gamma') #sigma_{D,G4} = #sigma_{D,exp}, (1+#kappa) #sigma_{p,G4} = #sigma_{p,exp};Ek (GeV);#gamma'");

    double XS_P_Paul[7]         = {7.31E+02,6.80E+02,6.59E+02,6.45E+02,6.59E+02,6.77E+02,7.16E+02};
    double XS_P_Paul_Err[7]     = {2.02E+01,2.12E+01,2.96E+01,3.57E+01,5.54E+01,8.56E+01,1.56E+02};
    double Energy_P_Paul[7]     = {1.92E+01,4.20E+01,9.80E+01,2.40E+02,8.10E+02,2.70E+03,8.60E+03};
    double Energy_P_Paul_Err[7] = {5.90E+00,1.30E+01,3.10E+01,8.50E+01,3.30E+02,1.20E+03,3.80E+03};
    auto gre_P_Paul = new TGraphErrors(7,Energy_P_Paul,XS_P_Paul,Energy_P_Paul_Err,XS_P_Paul_Err);
    
    double XS_He_Paul[7]         = {1.08E+03,1.11E+03,1.10E+03,1.14E+03,1.17E+03,1.24E+03,1.32E+03};
    double XS_He_Paul_Err[7]     = {2.57E+01,3.42E+01,4.14E+01,5.10E+01,6.80E+01,1.06E+02,1.90E+02};
    double Energy_He_Paul[7]     = {2.00E+01,3.28E+01,8.72E+01,2.84E+02,9.60E+02,3.24E+03,1.12E+04};
    double Energy_He_Paul_Err[7] = {4.80E+00,1.12E+01,2.52E+01,8.40E+01,3.20E+02,1.12E+03,4.40E+03};
    auto gre_He_Paul = new TGraphErrors(7,Energy_He_Paul,XS_He_Paul,Energy_He_Paul_Err,XS_He_Paul_Err);

    // double EPOS_Energy[7]     = {2.00E+01,4.16E+01,9.86E+01,2.36E+02,8.10E+02,2.77E+03,8.96E+03};
    // double EPOS_XS[7]         = {6.53E+02,6.57E+02,6.63E+02,6.75E+02,6.95E+02,7.15E+02,7.36E+02};
    // for(int ii= 0; ii<7 ; ii++)
    // {   
    //     double x = Energy_P_Paul[ii];
    //     //
    //     kappa[ii]      = XS_P_Paul[ii]/ (gre6->Eval(x) * ( gre_QE->Eval(x))) -1;
    //     // Extract from Paul
    //     kappa_EPOS[ii] = XS_P_Paul[ii]/ EPOS_XS[ii] -1;
    // }
    // auto gr_kappa     = new TGraph(7, Energy_P_Paul, kappa);
    // auto gr_kappa_EPOS = new TGraph(7, Energy_P_Paul, kappa_EPOS);

    gre_P_Paul->SetName("gre_P_Paul");
    gre_P_Paul->SetMarkerStyle(22);
    gre_P_Paul->SetMarkerSize(2);
    gre_P_Paul->SetMarkerColor(kRed-3);
    gre_P_Paul->SetLineColor(kRed-3);
    gre_P_Paul->SetLineWidth(2);
    gre_P_Paul->SetTitle(";Ek (GeV);Hadronic Inelastic Interaction XS (mbarn)");

    gre_He_Paul->SetName("gre_He_Paul");
    gre_He_Paul->SetMarkerStyle(23);
    gre_He_Paul->SetMarkerSize(2);
    gre_He_Paul->SetMarkerColor(kGreen-6);
    gre_He_Paul->SetLineColor(kGreen-6);
    gre_He_Paul->SetLineWidth(2);

    auto C0 = new TCanvas("C0", "C0",0,0,1200,1000);
    C0->cd();
    gPad->SetLogx(1);
    gre_P_Paul->GetYaxis()->SetRangeUser(0,2e3);
    gre_P_Paul->GetXaxis()->SetLimits(8e0,2e4);
    gre_P_Paul->Draw("AP");
    gre_He_Paul->Draw("PSAME");
    gre6->Draw("LSAME");
    gre7->Draw("LSAME");
    gre8->Draw("LSAME");

    auto leg0 = new TLegend(0.12,0.15,0.88,0.25);
    leg0->SetNColumns(3);
    leg0->SetTextFont(72);
    leg0->SetTextSize(0.025);
    leg0->SetBorderSize(0);
    leg0->SetName("leg0");

    leg0->AddEntry(gre6,"GEANT4 Proton","L");
    leg0->AddEntry(gre8,"GEANT4 He4","L");
    leg0->AddEntry(gre7,"GEANT4 Deuteron","L");
    leg0->AddEntry(gre_P_Paul,"DAMPE Proton 2025","EP");
    leg0->AddEntry(gre_He_Paul,"DAMPE He4 2025","EP");
    leg0->Draw();
    C0->SaveAs("/Users/xiongzheng/software/Canvas_XS_Base.pdf");

    
    auto C1 = new TCanvas("C1","C1",0,0,1200,1000);
    gPad->SetGrid(1,1);
    gPad->SetLogx(1);
    
    gre9_1->GetYaxis()->SetRangeUser(1,1.4e0);
    gre9_1->GetXaxis()->SetLimits(8e0,2e7);
    gre9_1->SetTitle(";Ek (GeV);#sigma^{ine}_{D,G4} / #sigma^{ine}_{P,G4}");
    gre9_1->Draw("AL");
    gre9_2->GetXaxis()->SetLimits(1e2,1e5);
    gre9_2->Draw("LSAME");
    gre9_3->Draw("LSAME");

    auto line1 = new TLine(1e1,1.108,1e7,1.108);
    line1->SetLineStyle(9);
    line1->Draw();

    auto line2 = new TLine(1e1,1.108/gre_QE->Eval(1e3)  ,1e7,1.108/  gre_QE->Eval(1e3));
    line2->SetLineColor(kRed);
    line2->SetLineStyle(10);
    line2->Draw();

    auto leg1 = new TLegend(0.32,0.72,0.88,0.88);
    leg1->SetNColumns(2);
    leg1->AddEntry(gre9_1," #sigma^{ine}_{D,G4} / #sigma^{ine}_{P,G4}" ,"l");
    leg1->AddEntry(gre9_2," #sigma^{ine}_{D,G4} / (#sigma^{ine}_{P,G4} #upoint f_{QE}(E))" ,"l");
    leg1->AddEntry(gre9_3," #sigma^{ine}_{D,G4} / #sigma^{ine}_{P,G4} #upoint #alpha(E)" ,"l");
    leg1->AddEntry(line1, " Black Disk Limit" ,"l");
    leg1->AddEntry(line2, " Black Disk Limit / f_{QE}(1TeV)" ,"l");

    leg1->Draw();
    C1->SaveAs("/Users/xiongzheng/software/XS_Ratio.pdf");

    auto C2 = new TCanvas("C2","C2",0,0,1200,1000);
    gPad->SetGrid(1,1);
    gPad->SetLogx(1);
    // gre10_1->GetXaxis()->SetLimits(9e0,2e5);
    gre10_1->SetTitle("(1+#kappa#upoint#gamma) #sigma_{D,G4} = #sigma_{D,exp}, (1+#kappa) #sigma_{p,G4} = #sigma_{p,exp};Ek (GeV);#gamma ");
    gre10_1->Draw("AL");
    gre10_2->Draw("LSAME");
    gre10_3->Draw("LSAME");

    auto leg2 = new TLegend(0.22,0.12,0.68,0.22);
    leg2->AddEntry(gre10_1," Without considering QE process" ,"l");
    leg2->AddEntry(gre10_2," Considering QE process #alpha(E)" ,"l");
    leg2->AddEntry(gre10_3," Considering QE process #alpha(E), converge at 1.108/f(1TeV)" ,"l");

    leg2->Draw();
    C2->SaveAs("/Users/xiongzheng/software/XS_Ratio_Gamma.pdf");


    // auto C3 = new TCanvas("C3","C3",0,0,1200,1000);
    // gPad->SetLogx(1);
    // gPad->SetGrid(1,1);
    // gr_kappa->SetTitle("#kappa = FD / FTFP Curve - 1;Ek(GeV); #kappa ");
    // gr_kappa->SetLineColor(kRed);
    // gr_kappa->GetYaxis()->SetRangeUser(-0.2,0.2);
    // gr_kappa_EPOS->SetLineColor(kBlue);

    // gr_kappa->Draw("AL");
    // gr_kappa_EPOS->Draw("LSAME");

    // auto lg3 = new TLegend(0.72,0.78,0.88,0.88);
    // lg3->AddEntry(gr_kappa,"FTFP * (1 - P{QE} ) ","l");
    // lg3->AddEntry(gr_kappa_EPOS,"EPOS","l");
    // lg3->Draw();
    // C3->SaveAs("/Users/xiongzheng/software/XS_Ratio_Kappa.pdf");


    auto C4 = new TCanvas("C4","C4",0,0,1200,1000);
    auto tf1 = new TF1("f1","log(1+2*x)/log(1+x)",1e-1,1e10);
    gPad->SetLogx(1);
    tf1->Draw();
    C4->SaveAs("/Users/xiongzheng/software/GEO_converge.pdf");

    auto C5 = new TCanvas("C5","C5",0,0,1200,1000);
    gPad->SetLogx(1);
    gre_QE->SetTitle("gre_QE;Energy (GeV); #sigma_{Quasi-elastic} / #sigma_{inelastic}");
    gre_QE->SetName("gre_QE");
    gre_QE->Draw("ALP");
    C5->SaveAs("/Users/xiongzheng/software/QE.pdf");


    auto C6 = new TCanvas("C6","C6",0,0,1200,1000);
    gPad->SetLogx(1);
    gre_alpha->GetXaxis()->SetLimits(9e0,2e5);
    gre_alpha->SetTitle("#alpha = f_{QE}(E_{#infty}) / f_{QE}(E) ;Energy (GeV); Ratio");
    gre_alpha->SetName("alpha_Fraction_QE");
    gre_alpha->Draw("ALP");

    auto line_Ref = new TLine(1e3,1,1e5,1);
    line_Ref->SetLineColor(kRed);
    line_Ref->SetLineWidth(2);
    line_Ref->SetLineStyle(9);
    line_Ref->Draw("same");
    C6->SaveAs("/Users/xiongzheng/software/alpha_Fraction_QE.pdf");


    auto write_file = TFile::Open("/Users/xiongzheng/software/XS_Base_Figures.root","RECREATE");
    write_file->cd();
    C0->Write();
    C1->Write();
    C2->Write();
    // C3->Write();
    C4->Write();
    C5->Write();
    C6->Write();

    gre_P_Paul->Write();
    gre_He_Paul->Write();
    gre_alpha->Write();
    gre6->Write();
    gre7->Write();
    gre8->Write();
    gre9_1->Write();
    gre9_2->Write();
    gre9_3->Write();

    gre10_1->Write();
    gre10_2->Write();
    gre10_3->Write();

    leg1->Write();
    write_file->Close();
}
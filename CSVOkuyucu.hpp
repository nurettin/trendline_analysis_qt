#ifndef CSVOKUYUCU_HPP
#define CSVOKUYUCU_HPP

#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <stdexcept>
#include <locale>
#include <iomanip>

namespace onur{ namespace bilim{

struct CSVOkuyucuOzellikleri
{
    int SutunSayisi;
    char DoubleAyraci;
    char ElemanAyraci;
    bool Belirsiz;
};

struct CSVOkuyucu
{
    struct CSVData
    {
        std::vector<std::vector<double> > Data;
        int SutunSayisi() const { if(Data.empty()) return 0; return Data[0].size(); }
        double Min;
        double Max;
    };

    struct LocaleDoubleAyraci: std::numpunct<char>
    {
        char ayrac;
        LocaleDoubleAyraci(char ayrac): ayrac(ayrac){}
        char do_decimal_point() const { return ayrac; }
    };

    static CSVData Oku(std::string const &dosya_ismi)
    {
        std::ifstream dosya(dosya_ismi.c_str());
        if(!dosya.is_open()) throw std::runtime_error(dosya_ismi + " a\xc3\xa7\xc4\xb1l\xc4\xb1rken bir hata olu\xc5\x9ftu.");
        CSVOkuyucuOzellikleri ozellikler= OzellikleriBelirle(dosya_ismi);
        if(ozellikler.Belirsiz) throw std::runtime_error(dosya_ismi+ " format\xc4\xb1 belirsiz");
        dosya.imbue(std::locale(std::locale(), new LocaleDoubleAyraci(ozellikler.DoubleAyraci)));
        int sutunSayaci= 0;
        CSVData data;
        data.Min= std::numeric_limits<double>::max();
        data.Max= std::numeric_limits<double>::min();
        dosya>> std::noskipws;
        for(double token; (dosya>> token).ignore(1); ++ sutunSayaci)
        {
            sutunSayaci%= ozellikler.SutunSayisi;
            if(sutunSayaci== 0)
            {
                do{
                    char next= dosya.peek();
                    if(next== ' '|| next== '\r'|| next== '\n'|| next== '\t')
                        dosya.ignore();
                    else break;
                }while (true);

                data.Data.push_back(std::vector<double>(ozellikler.SutunSayisi));
            }
            if(token< data.Min) data.Min= token;
            if(token> data.Max) data.Max= token;
            data.Data[data.Data.size()- 1][sutunSayaci]= token;
        }
        return data;
    }

    static bool NumerikDegil(char c)
    {
        return (c> '9' || c< '0') && !(c== '+'|| c== '-');
    }

    static bool VirgulDegil(char c)
    {
        return c!= ',';
    }

    // ilk satirdan CSV dosyasinin ozelliklerini bulmaya calisir
    static CSVOkuyucuOzellikleri OzellikleriBelirle(std::string const &dosya_ismi)
    {
        CSVOkuyucuOzellikleri ozellikler;
        ozellikler.Belirsiz= true;
        std::ifstream dosya(dosya_ismi.c_str());
        if(!dosya.is_open()) return ozellikler;
        std::string satir;
        std::getline(dosya, satir);
        std::string::iterator ilkNumerikOlmayan= std::find_if(satir.begin(), satir.end(), NumerikDegil);
        if(ilkNumerikOlmayan== satir.end()) // tamsayi, tek sutun, diger satirlara bakilmali
        {
            ozellikler.SutunSayisi= 1;
            return ozellikler;
        }
        std::string::iterator sonrakiNumerikOlmayan= std::find_if(ilkNumerikOlmayan+ 1, satir.end(), NumerikDegil);
        ozellikler.Belirsiz= false;
        if(sonrakiNumerikOlmayan== satir.end()) // double, tek sutun. Yeterli bilgi var.
        {
            ozellikler.DoubleAyraci= *ilkNumerikOlmayan;
            ozellikler.SutunSayisi= 1;
            return ozellikler;
        }        
        if(*ilkNumerikOlmayan== '.')
        {
            ozellikler.ElemanAyraci= *sonrakiNumerikOlmayan;
            ozellikler.DoubleAyraci= *ilkNumerikOlmayan;
            ozellikler.SutunSayisi= std::count(sonrakiNumerikOlmayan, satir.end(), ozellikler.ElemanAyraci)+ 1;
            return ozellikler;
        }
        else if(*ilkNumerikOlmayan== ',')
        {
            if(VirgulDegil(*sonrakiNumerikOlmayan))
            {
                ozellikler.DoubleAyraci= *ilkNumerikOlmayan;
                ozellikler.ElemanAyraci= *sonrakiNumerikOlmayan;
                ozellikler.SutunSayisi= std::count(sonrakiNumerikOlmayan, satir.end(), ozellikler.ElemanAyraci)+ 1;
                return ozellikler;
            }
            else
            {
                std::string::iterator ilkVirgulOlmayan= std::find_if(sonrakiNumerikOlmayan+ 1, satir.end(), VirgulDegil);
                if(ilkVirgulOlmayan== satir.end())
                {
                    ozellikler.Belirsiz= true;
                    return ozellikler;
                }
                else
                {
                    ozellikler.SutunSayisi= std::count_if(sonrakiNumerikOlmayan+ 1, satir.end(), VirgulDegil)+ 1;
                    ozellikler.ElemanAyraci= *ilkVirgulOlmayan;
                    ozellikler.DoubleAyraci= *ilkNumerikOlmayan;
                    return ozellikler;
                }
            }
        }
        ozellikler.Belirsiz= true;
        return ozellikler;
    }
};


}}

#endif // CSVOKUYUCU_HPP

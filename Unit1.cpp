//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TF_Main *F_Main;
TStringList *Dict = new TStringList;
TStringList *Number = new TStringList;


//---------------------------------------------------------------------------
__fastcall TF_Main::TF_Main(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TF_Main::B_SendClick(TObject *Sender)
{
	struct T_InputData t;
	t.value = 1.5;
	t.measure = t_acc;



	TDateTime* myTime = new TDateTime(Now());
	String msg = E_Message->Text;
	String data = myTime->FormatString("dd.mm.yyyy") +
	" " + myTime->FormatString("hh:mm:ss") + " " ;
	String text = data + "User:" + msg;
	M_Chat->Lines->Add(text);
	if (E_Message->Text.Length()==E_Message->Text.Pos("?")) {
		if (E_Message->Text.Pos("дела")>0) {
			text = data + "Friend:" + "Хорошо";
			M_Chat->Lines->Add(text);
		}
		else if (E_Message->Text.Pos("то делаешь?")>0) {
			text = data + "Friend:" + "Ничего";
			M_Chat->Lines->Add(text);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TF_Main::E_MessageKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == '\r') {
		B_SendClick(Sender);
	}
}
//---------------------------------------------------------------------------



void __fastcall TF_Main::B_AnalysisClick(TObject *Sender)
{
	int pos;
	String text;
	String word;
	String numb;
	dL = 0;
	int number;
	char *meastext[]= {"","км/ч","км/ч^2","час","км"};
	bool numfound = false;
	text = M_Chat->Lines->GetText();


	do {
		pos = text.Pos(" ");
		if (pos == 0) {
			word = text;
		}
		else {
		word = text.SubString(1,pos-1);
		try {
		Dict->LoadFromFile("dictionary.txt");
		Number->LoadFromFile("number.txt");
			for (int j=0; j < Dict->Count; j++) {
				String strnum = Dict->Strings[j];
				if (word==strnum) {
					word=Number->Strings[j];
				}
				else if ((word=="час")&&(numfound==false)) {
				inputdata[dL].value =1;
				dL++;
				numfound = true;
			}
		}
		}catch (...) {
		ShowMessage("Файл dictionary.txt не найден");
		}
		text = text.SubString(pos+1,text.Length());
		}

		/*p = text.Pos(",");
		if (p>0) {
			word = textSubstring();
		}*/
		if (numfound == true) {
			if (word.Pos("км/ч^2")>0) {
					inputdata[dL-1].measure = t_acc;
			}
			else if (word.Pos("км/ч")>0) {
				inputdata[dL-1].measure = t_velocity ;
			}
			else if (word.Pos("ч")>0) {
				inputdata[dL-1].measure = t_time;
			}
			else if (word=="км") {
				inputdata[dL-1].measure = t_distance;
			}
			numfound = false;
		}
		M_Chat->Lines->Add(word);
		try
		{

			inputdata[dL].value = word.ToDouble();
			numfound = true;
			dL++;
			M_Chat->Lines->Add("Number");

		}
		catch(const Exception& e)
		{

		}

	}while(pos);

	/*for (int k=1; k < M_Chat->Lines->Count; k++) {
		if ((M_Chat->Lines->Strings[k].Pos("Number")>0)&&(M_Chat->Lines->Strings[k+2].Pos("Number")>0)&&
		(M_Chat->Lines->Strings[k+4].Pos("Number")>0)&&(M_Chat->Lines->Strings[k+6].Pos("Number")>0)
		&&(M_Chat->Lines->Strings[k+6].Pos("Number")==0)){
			if ((M_Chat->Lines->Strings[k-1].ToDouble()>999)&&(M_Chat->Lines->Strings[k+1].ToDouble()>99)&&
			(M_Chat->Lines->Strings[k+3].ToDouble()>19)) {
			numb =M_Chat->Lines->Strings[k-1].ToDouble()+M_Chat->Lines->Strings[k+1].ToDouble()+
			M_Chat->Lines->Strings[k+3].ToDouble()+M_Chat->Lines->Strings[k+5].ToDouble();
			inputdata[dL].value = numb.ToDouble();
			dL++;
			numfound= true;
			}
		}
		else if ((M_Chat->Lines->Strings[k-2].Pos("Number")==0)&&(M_Chat->Lines->Strings[k].Pos("Number")>0)&&
		(M_Chat->Lines->Strings[k+2].Pos("Number")>0)&&(M_Chat->Lines->Strings[k+4].Pos("Number")>0)){
			if ((M_Chat->Lines->Strings[k-1].ToDouble()>99)&&(M_Chat->Lines->Strings[k+1].ToDouble()>19)) {
			numb =M_Chat->Lines->Strings[k-1].ToDouble()+M_Chat->Lines->Strings[k+1].ToDouble()+
			M_Chat->Lines->Strings[k+3].ToDouble();
			M_Chat->Lines->Strings[k+3]= numb;
			inputdata[dL].value = numb.ToDouble();
			dL++;
			numfound= true;
			}
		}
		else if ((M_Chat->Lines->Strings[k-2].Pos("Number")==0)&&(M_Chat->Lines->Strings[k].Pos("Number")>0)&&
		(M_Chat->Lines->Strings[k+2].Pos("Number")>0)&&(M_Chat->Lines->Strings[k+4].Pos("Number")==0)) {
			if (M_Chat->Lines->Strings[k-1].ToDouble()>19) {
			numb =M_Chat->Lines->Strings[k-1].ToDouble()+M_Chat->Lines->Strings[k+1].ToDouble();
			M_Chat->Lines->Strings[k+1]= numb;
			inputdata[dL].value = numb.ToDouble();
			dL++;
			numfound= true;
			}
		}
	}*/

	for (int i = 0; i < dL; i++) {
		M_Debug->Lines->Add(FloatToStr(inputdata[i].value)+" "+
		meastext[inputdata[i].measure]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TF_Main::B_SoldClick(TObject *Sender)
{
	int i,k,j;
	int pos;
	double V=0;
	double S=0;
	double T=0;
	double v[10];
	double t[10];
	double s[10];
	String text;
	int iv=0,it=0;
	int is = 0;

	text=M_Chat->Lines->GetText();
	pos = text.Pos("Найдите среднюю скорость");
	if (pos==0) {
		M_Chat->Lines->Add("Неверно");
		return;
	}
	if (pos>0) {
		M_Chat->Lines->Add("Решение есть");
		B_AnalysisClick(M_Chat);
		for (i = 0; i < dL; i++) {
			if (inputdata[i].measure==t_velocity) {
				v[iv]=inputdata[i].value;
				iv++;
			}
			else if (inputdata[i].measure==t_time) {
				t[it]=inputdata[i].value;
				it++;
			}
			else if (inputdata[i].measure==t_distance) {
				s[is]=inputdata[i].value;
				is++;
			}
		}
		if (iv>0 && it>0) {
			for (k  = 0; k < iv; k++) {
				S=S+v[k]*t[k];
			}
			for (j = 0; j < it; j++) {
				T=T+t[j];
			}
		}
		if (iv>0 && is>0 && it==0) {
			for (k  = 0; k < iv; k++) {
				T = T+s[k]/v[k];
			}
			for (j = 0; j < is; j++) {
				S=S+s[j];
			}
		}
		V = S/T;
		M_Solution->Lines->Add("Ответ:"+FloatToStr(V)+ " км/ч.");
	}
}
//---------------------------------------------------------------------------


void __fastcall TF_Main::B_BdClick(TObject *Sender)
{
	ADOQuery1->Close();
	ADOQuery1->SQL->Clear();
	ADOQuery1->SQL->Add("SELECT * FROM numbers where word =:par1");
	ADOQuery1->Parameters->ParamByName("par1")->Value = Edit1->Text;
	ADOQuery1->Open();
	AnsiString str = ADOQuery1->FieldByName("number")->AsString;
	Label1->Caption = str;
}
//---------------------------------------------------------------------------



void __fastcall TF_Main::AddClick(TObject *Sender)
{
	int pos;
	String text;
	String word;
	String numb;
	dL = 0;
	int number;
	bool numfound = false;
	text = M_Chat->Lines->GetText();
	//words = (char **)0;
	words = NULL;            //указатель
	char *p=NULL;
	wd_n = 0;

	do {
		pos = text.Pos(" ");
		if (pos == 0) {
			word = text;
		}
		else {
			word = text.SubString(1,pos-1);
			try {
			Dict->LoadFromFile("dictionary.txt");
			Number->LoadFromFile("number.txt");
				for (int j=0; j < Dict->Count; j++) {
					String strnum = Dict->Strings[j];
					if (word==strnum) {
						word=Number->Strings[j];
					}
					else if ((word == "час")&&(numfound == false)) {
					inputdata[dL].value =1;
					dL++;
					numfound = true;
				}
			}
			}catch (...) {
			ShowMessage("Файл dictionary.txt или number.txt не найден");
			}
			text = text.SubString(pos+1,text.Length());
		}
		p=(char *)malloc(word.Length() + 1);
		if (p==NULL) {
			return;
		}
		wd_n++;
		if (words == NULL) {
			words =(char **)malloc(wd_n * sizeof(char *));
		}
		//words = malloc(wd_n * sizeof(char *));
		else {
			words =(char**)realloc(words,wd_n * sizeof (char *));
		}
		for (int j ; j < word.Length(); j++) {
			p[j] = (char)word.c_str()[j];
		}
		//strcpy(p,(char *)word.c_str()); //c_str преобразует в char строку
		words[wd_n - 1] = p;
		WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK, word.c_str(),-1,p,word.Length()+1,NULL,NULL);
	} while (pos);

	int i;
	for (i = 0; i < wd_n; i++) {
		M_Out->Lines->Add(words[i]);
	}
	//SELECT `sinonim` FROM `sinbd` WHERE `groupid`=1
	//SELECT `groupid` FROM `sinbd` WHERE `sinonim`="автомобиль"
}
//---------------------------------------------------------------------------

void __fastcall TF_Main::RandClick(TObject *Sender)
{
	int k;
	double h;
	bool numfound;
	int l;
	M_Rand->Text = " ";

	randomize();
	for (k = 0; k < wd_n; k++) {
		sscanf(words[k],"%f",&h);
		if (sscanf(words[k],"%f",&h)>0) {
			M_Rand->Text=M_Rand->Text+" "+rand() %1000;
		}
		else {
			AnsiString Query;
			Query = "SELECT sinonim FROM sinbd WHERE groupid=(SELECT groupid FROM sinbd WHERE sinonim=\"";
			Query = Query+words[k]+"\")";
			ADOQuery1->Close();
			ADOQuery1->SQL->Clear();
			ADOQuery1->SQL->Add(Query);
			//ADOQuery1->Parameters->ParamByName("par1")->Value = words[k];
			ADOQuery1->Open();
			String str= ADOQuery1->FieldByName("sinonim")->AsString;
			if (str=="") {
				M_Rand->Text=M_Rand->Text+" "+words[k];
			}
			else {
				M_Rand->Text=M_Rand->Text+" "+str;
			}
		   //	M_Rand->Text=M_Rand->Text+" "+words[k];
		}
	}
}

//---------------------------------------------------------------------------



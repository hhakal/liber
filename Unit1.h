//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <stdio.h>

//---------------------------------------------------------------------------
class TF_Main : public TForm
{
__published:	// IDE-managed Components
	TButton *B_Send;
	TMemo *M_Chat;
	TEdit *E_Message;
	TButton *B_Analysis;
	TButton *B_Sold;
	TDataSource *DataSource1;
	TDBGrid *DBGrid1;
	TMemo *M_Debug;
	TMemo *M_Solution;
	TADOTable *ADOtable1;
	TADOQuery *ADOQuery1;
	TButton *B_Bd;
	TEdit *Edit1;
	TLabel *Label1;
	TButton *Devide;
	TButton *Add;
	TMemo *M_Out;
	TButton *Rand;
	TMemo *M_Rand;



	void __fastcall B_SendClick(TObject *Sender);
	void __fastcall E_MessageKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall B_AnalysisClick(TObject *Sender);
	void __fastcall B_SoldClick(TObject *Sender);
	void __fastcall B_BdClick(TObject *Sender);
	void __fastcall AddClick(TObject *Sender);
	void __fastcall RandClick(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TF_Main(TComponent* Owner);

	enum T_Measure{t_velocity = 1, t_acc = 2, t_time = 3, t_distance = 4};

		struct T_InputData{
		double value;
		T_Measure measure;
		} inputdata[10];

		int dL;
		char **words;
		int wd_n;



};
//---------------------------------------------------------------------------
extern PACKAGE TF_Main *F_Main;
//---------------------------------------------------------------------------
#endif

#define OPAGE_MAIN			0
#define OPAGE_SAILING		1
#define OPAGE_SOUNDS		2
#define OPAGE_CAMERA_MOD	3
#define OPAGE_CONTROLS_1	4
#define OPAGE_CONTROLS_2	5
#define OPAGE_CONTROLS_3	6

#define MAX_PAGES_QUANTITY	4

float i_fCurMusic;
float i_fCurSound;
float i_fCurDialog;

int gi_nCurrentPage = -1;

bool g_bDisableControlChange = false;

string gsKeyWindowName;

object objArrayControls;

string g_sGroupName;
int nLastTextGroupNum;
int nLastTextStringNum;
int curCntrlIdx;

int nFadeStr_AlUsed = 0;
int nFadeStr_NoStick = 0;

void InitInterface(string iniName)
{
	GameInterface.title = "titleOptions";

	if( GetTargetPlatform()=="pc" ) {
		g_bDisableControlChange = false;
		gsKeyWindowName = "KEYSWINDOW_PC";
	} else {
		g_bDisableControlChange = true;
		gsKeyWindowName = "KEYSWINDOW_XBOX";
	}
//	g_bDisableControlChange = true;

	ISetVariable();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetNodeUsing("KEY_CHOOSER",false);
	gi_nCurrentPage = OPAGE_MAIN;
	SetFormatedText("RESTORE_STRINGS",XI_ConvertString("Confirm default restore keys"));

	CreateString(false,"GroupName","",FONT_NORMAL,COLOR_NORMAL,320,140,SCRIPT_ALIGN_CENTER,1.0);

	SetEventHandler("TitleSelect","DoTitleSelect",0);
	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);

	SetEventHandler("FormatedTextActivate","procFTActivate",0);
	SetEventHandler("evntUpdateFormtText","procFTUpdate",0);
	SetEventHandler("SetScrollerPos","procFTSetScrollPos",0);
	SetEventHandler("ScrollPosChange","ProcScrollPosChange",0);
	SetEventHandler("frame","IProcessFrame",0);
	SetEventHandler("evntKeyChoose","procKeyChoose",0);

	aref ar; makearef(ar,objControlsState.key_codes);
	SendMessage(&GameInterface,"lsla",MSG_INTERFACE_MSG_TO_NODE,"KEY_CHOOSER", 0,ar);

	if( g_bDisableControlChange ) {
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"MB_CONTROLS", 0,XI_ConvertString("View Controls"));
	}

	if( GetTargetPlatform()=="pc" ) {
		//SetSelectable("MB_CAMERA",false);
		SetNodeUsing("MB_CAMERA",false);
	}

	SetEventHandler("evntFadeStrings","FadeStringsUpdate",0);
	PostEvent("evntFadeStrings",100);
}

void ISetVariable()
{
	i_fCurMusic = 0.5;
	i_fCurSound = 0.5;
	i_fCurDialog = 0.5;

	SendMessage(&sound,"leee",MSG_SOUND_GET_MASTER_VOLUME,&i_fCurSound,&i_fCurMusic,&i_fCurDialog);

	GameInterface.nodes.music.value = i_fCurMusic;
	GameInterface.nodes.sound.value = i_fCurSound;
	GameInterface.nodes.dialog.value = i_fCurDialog;
}

void IProcessFrame()
{
	bool bYesChange = false;
	if(gi_nCurrentPage==OPAGE_SOUNDS)
	{
		if(i_fCurMusic!=stf(GameInterface.nodes.music.value)) {
			i_fCurMusic = stf(GameInterface.nodes.music.value);
			bYesChange = true;
		}
		if(i_fCurSound!=stf(GameInterface.nodes.sound.value)) {
			i_fCurSound = stf(GameInterface.nodes.sound.value);
			bYesChange = true;
		}
		if(i_fCurDialog!=stf(GameInterface.nodes.dialog.value)) {
			i_fCurDialog = stf(GameInterface.nodes.dialog.value);
			bYesChange = true;
		}
		if(bYesChange) {
			SendMessage(&sound,"lfff",MSG_SOUND_SET_MASTER_VOLUME,i_fCurSound,i_fCurMusic,i_fCurDialog);
		}
	}
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_OPTIONSCREEN_EXIT);
	if( !CheckAttribute(&InterfaceStates,"InstantExit") || sti(InterfaceStates.InstantExit)==false ) {
		ReturnToMainMenu();
	}
}

void IDoExit(int exitCode)
{
	DelEventHandler("TitleSelect","DoTitleSelect");
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("FormatedTextActivate","procFTActivate");
	DelEventHandler("evntUpdateFormtText","procFTUpdate");
	DelEventHandler("SetScrollerPos","procFTSetScrollPos");
	DelEventHandler("ScrollPosChange","ProcScrollPosChange");
	DelEventHandler("frame","IProcessFrame");
	DelEventHandler("evntKeyChoose","procKeyChoose");
	DelEventHandler("evntFadeStrings","FadeStringsUpdate");

    interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"InstantExit") && sti(InterfaceStates.InstantExit)==true ) {
	    EndCancelInterface(true);
	} else {
		EndCancelInterface(false);
	}
	SaveGameOptions();
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
	case "MB_SAILING":
		if(comName=="activate" || comName=="click") {
			ShowOptionsPage(OPAGE_SAILING);
		}
	break;

	case "MB_SOUNDS":
		if(comName=="activate" || comName=="click") {
			ShowOptionsPage(OPAGE_SOUNDS);
		}
	break;

	case "MB_CAMERA":
		if(comName=="activate" || comName=="click") {
			ShowOptionsPage(OPAGE_CAMERA_MOD);
		}
	break;

	case "MB_CONTROLS":
		if(comName=="activate" || comName=="click") {
			if( g_bDisableControlChange ) {ShowOptionsPage(OPAGE_CONTROLS_2);}
			else {ShowOptionsPage(OPAGE_CONTROLS_1);}
		}
		if(comName=="downstep")
		{
			if(GetSelectable("MB_CAMERA")) {SetCurrentNode("MB_CAMERA");}
		}
	break;




	case "ARCADEMODE_1":
		if(comName=="activate" || comName=="click")
		{
			bArcadeMode = true;
			TmpI_ShowArcadeMode();
		}
	break;

	case "ARCADEMODE_2":
		if(comName=="activate" || comName=="click")
		{
			bArcadeMode = false;
			TmpI_ShowArcadeMode();
		}
	break;

	case "CAMERAMODE_1":
		if(comName=="activate" || comName=="click")
		{
			locCameraEnableSpecialMode = true;
			TmpI_ShowCameraMode();
		}
	break;

	case "CAMERAMODE_2":
		if(comName=="activate" || comName=="click")
		{
			locCameraEnableSpecialMode = false;
			TmpI_ShowCameraMode();
		}
	break;







	case "CONTROLS_B_CHANGE":
		if(comName=="activate" || comName=="click") {
			ShowOptionsPage(OPAGE_CONTROLS_2);
		}
	break;
	case "CONTROLS_B_DEFAULT":
		if(comName=="activate" || comName=="click")
		{
			SetNodeUsing("RESTORE_RECT",true);
			SetNodeUsing("RESTORE_STRINGS",true);
			SetNodeUsing("RESTORE_OK",true);
			SetNodeUsing("RESTORE_CANCEL",true);
			SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 1, "RESTORE_OK");
			SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 2, "RESTORE_CANCEL");
			SetCurrentNode("RESTORE_OK");
		}
	break;
	case "RESTORE_OK":
		if(comName=="activate" || comName=="click")
		{
			InterfaceStates.InvertCameras = false;
			ControlsInit(GetTargetPlatform(),false);
			SetNodeUsing("RESTORE_RECT",false);
			SetNodeUsing("RESTORE_STRINGS",false);
			SetNodeUsing("RESTORE_OK",false);
			SetNodeUsing("RESTORE_CANCEL",false);
			SendMessage(&GameInterface,"ll", MSG_INTERFACE_LOCK_NODE, 0);
			SetCurrentNode("CONTROLS_B_DEFAULT");
		}
		if(comName=="deactivate")
		{
			SetNodeUsing("RESTORE_RECT",false);
			SetNodeUsing("RESTORE_STRINGS",false);
			SetNodeUsing("RESTORE_OK",false);
			SetNodeUsing("RESTORE_CANCEL",false);
			SendMessage(&GameInterface,"ll", MSG_INTERFACE_LOCK_NODE, 0);
			SetCurrentNode("CONTROLS_B_DEFAULT");
		}
	break;
	case "RESTORE_CANCEL":
		if(comName=="activate" || comName=="click" || comName=="deactivate")
		{
			SetNodeUsing("RESTORE_RECT",false);
			SetNodeUsing("RESTORE_STRINGS",false);
			SetNodeUsing("RESTORE_OK",false);
			SetNodeUsing("RESTORE_CANCEL",false);
			SendMessage(&GameInterface,"ll", MSG_INTERFACE_LOCK_NODE, 0);
			SetCurrentNode("CONTROLS_B_DEFAULT");
		}
	break;



	case "B_SAILING1ST":
		if(comName=="deactivate")
		{
			if( g_bDisableControlChange ) {
				ShowOptionsPage(OPAGE_MAIN);
				SetCurrentNode("MB_CONTROLS");
			} else {
				ShowOptionsPage(OPAGE_CONTROLS_1);
				SetCurrentNode("CONTROLS_B_CHANGE");
			}
		}
		if(comName=="activate" || comName=="click")
		{
			ShowOptionsPage(OPAGE_CONTROLS_3);
			SetShowGroup("Sailing1Pers");
		}
	break;
	case "B_PRIMARY_LAND":
		if(comName=="deactivate")
		{
			if( g_bDisableControlChange ) {
				ShowOptionsPage(OPAGE_MAIN);
				SetCurrentNode("MB_CONTROLS");
			} else {
				ShowOptionsPage(OPAGE_CONTROLS_1);
				SetCurrentNode("CONTROLS_B_CHANGE");
			}
		}
		if(comName=="activate" || comName=="click")
		{
			ShowOptionsPage(OPAGE_CONTROLS_3);
			SetShowGroup("PrimaryLand");
		}
	break;
	case "B_SAILING3RD":
		if(comName=="deactivate")
		{
			if( g_bDisableControlChange ) {
				ShowOptionsPage(OPAGE_MAIN);
				SetCurrentNode("MB_CONTROLS");
			} else {
				ShowOptionsPage(OPAGE_CONTROLS_1);
				SetCurrentNode("CONTROLS_B_CHANGE");
			}
		}
		if(comName=="activate" || comName=="click")
		{
			ShowOptionsPage(OPAGE_CONTROLS_3);
			SetShowGroup("Sailing3Pers");
		}
	break;
	case "B_FIGHTMODE":
		if(comName=="deactivate")
		{
			if( g_bDisableControlChange ) {
				ShowOptionsPage(OPAGE_MAIN);
				SetCurrentNode("MB_CONTROLS");
			} else {
				ShowOptionsPage(OPAGE_CONTROLS_1);
				SetCurrentNode("CONTROLS_B_CHANGE");
			}
		}
		if(comName=="activate" || comName=="click")
		{
			ShowOptionsPage(OPAGE_CONTROLS_3);
			SetShowGroup("FightModeControls");
		}
	break;

	case "CONTROLSWINDOW":
		if(comName=="deactivate") {
			ShowOptionsPage(OPAGE_CONTROLS_2);
			SetOldButton();
		}
	break;

	

	case "SET_BUTTON":
		if(comName=="deactivate") {
			ReturnToViewControls();
		}
		if(comName=="activate" || comName=="click") {
			ReturnToViewControls();
			SetReassignMode();
		}
		if(comName=="downstep")
		{
			if(GetSelectable("DELETE_BUTTON"))
			{	SetCurrentNode("DELETE_BUTTON");
			}
			else
			{
				if(GetSelectable("INVERSE_BUTTON"))
				{	SetCurrentNode("INVERSE_BUTTON");
				}
			}
		}
	break;

	case "DELETE_BUTTON":
		if(comName=="deactivate") {
			ReturnToViewControls();
		}
		if(comName=="activate" || comName=="click") {
			ReturnToViewControls();
			UnmapControl();
		}
		if(comName=="downstep")
		{
			if(GetSelectable("INVERSE_BUTTON"))
				{	SetCurrentNode("INVERSE_BUTTON");	}
		}
		if(comName=="upstep")
			{	SetCurrentNode("SET_BUTTON")	}
	break;

	case "INVERSE_BUTTON":
		if(comName=="deactivate") {
			ReturnToViewControls();
		}
		if(comName=="activate" || comName=="click") {
			InverseControl();
			ReturnToViewControls();
		}
		if(comName=="upstep")
		{
			if(GetSelectable("DELETE_BUTTON"))
				{	SetCurrentNode("DELETE_BUTTON");	}
			else
				{	SetCurrentNode("SET_BUTTON");	}
		}
	break;

	}
}

void TmpI_ShowArcadeMode()
{
	if(bArcadeMode) {
		CreateImage("ArcadeModeImg","icons","complete",532,202,564,234);
	} else {
		CreateImage("ArcadeModeImg","icons","complete",532,248,564,280);
	}
}

void TmpI_ShowCameraMode()
{
	if(locCameraEnableSpecialMode) {
		CreateImage("CameraModeImg","icons","complete",532,206,564,238);
	} else {
		CreateImage("CameraModeImg","icons","complete",532,262,564,294);
	}
}

void TmpI_ShowInvertMode()
{
	if( CheckAttribute(&InterfaceStates,"InvertCameras") && sti(InterfaceStates.InvertCameras)==true ) {
		CreateImage("InvertCameraImg","icons","complete",532,318,564,350);
	} else {
		CreateImage("InvertCameraImg","","",0,0,0,0);
	}
}

void ShowOptionsPage(int pageNum)
{
	if(pageNum==gi_nCurrentPage) return;

	switch(gi_nCurrentPage)
	{
	case OPAGE_MAIN:
		SetNodeUsing("MB_SAILING",false);
		SetNodeUsing("MB_SOUNDS",false);
		SetNodeUsing("MB_CAMERA",false);
		SetNodeUsing("MB_CONTROLS",false);
	break;
	case OPAGE_SAILING:
		SetNodeUsing("SUBTITLE",false);
		SetNodeUsing("STRINGS_ARCADEMODE",false);
		SetNodeUsing("ARCADEMODE_1",false);
		SetNodeUsing("ARCADEMODE_2",false);
		GameInterface.pictures.ArcadeModeImg.pic = -1;
		GameInterface.pictures.ArcadeModeImg.tex = -1;
		SetCurrentNode("MB_SAILING");
	break;
	case OPAGE_SOUNDS:
		SetNodeUsing("SUBTITLE",false);
		SetNodeUsing("STRINGS_SOUNDS",false);
		SetNodeUsing("DIALOG",false);
		SetNodeUsing("SOUND",false);
		SetNodeUsing("MUSIC",false);
		SetCurrentNode("MB_SOUNDS");
	break;
	case OPAGE_CAMERA_MOD:
		SetNodeUsing("SUBTITLE",false);
		SetNodeUsing("STRINGS_CAMERA",false);
		SetNodeUsing("CAMERAMODE_1",false);
		SetNodeUsing("CAMERAMODE_2",false);
		GameInterface.pictures.CameraModeImg.pic = -1;
		GameInterface.pictures.CameraModeImg.tex = -1;
		GameInterface.pictures.InvertCameraImg.pic = -1;
		GameInterface.pictures.InvertCameraImg.tex = -1;
		SetCurrentNode("MB_CAMERA");
	break;

	case OPAGE_CONTROLS_1:
		SetNodeUsing("SUBTITLE",false);
		SetNodeUsing("STRINGS_CONTROLS",false);
		SetNodeUsing("CONTROLS_B_CHANGE",false);
		SetNodeUsing("CONTROLS_B_DEFAULT",false);
		SetCurrentNode("MB_CONTROLS");
	break;

	case OPAGE_CONTROLS_2:
		SetNodeUsing("SUBTITLE",false);
		SetNodeUsing("STRINGS_CONTROLS",false);
		SetNodeUsing("B_SAILING1ST",false);
		SetNodeUsing("B_PRIMARY_LAND",false);
		SetNodeUsing("B_SAILING3RD",false);
		SetNodeUsing("B_FIGHTMODE",false);
	break;

	case OPAGE_CONTROLS_3:
		SetNodeUsing("SUBTITLE",false);
		SetNodeUsing("STRINGS_CONTROLS",false);
		SetNodeUsing("CONTROLSWINDOW",false);
		SetNodeUsing(gsKeyWindowName,false);
		SetNodeUsing("CONTROLGROUP",false);
		SetNodeUsing("SCROLL",false);
		DisableString("GroupName");
	break;
	}

	gi_nCurrentPage = pageNum;

	switch(pageNum)
	{
	case OPAGE_MAIN:
		SetNodeUsing("MB_SAILING",true);
		SetNodeUsing("MB_SOUNDS",true);
		if(GetTargetPlatform()=="xbox")	{SetNodeUsing("MB_CAMERA",true);}
		SetNodeUsing("MB_CONTROLS",true);
	break;
	case OPAGE_SAILING:
		SetNodeUsing("SUBTITLE",true);
		SetNodeUsing("STRINGS_ARCADEMODE",true);
		SetNodeUsing("ARCADEMODE_1",true);
		SetNodeUsing("ARCADEMODE_2",true);
		TmpI_ShowArcadeMode();
		SetCurrentNode("ARCADEMODE_1");
	break;
	case OPAGE_SOUNDS:
		SetNodeUsing("SUBTITLE",true);
		SetNodeUsing("STRINGS_SOUNDS",true);
		SetNodeUsing("DIALOG",true);
		SetNodeUsing("SOUND",true);
		SetNodeUsing("MUSIC",true);
		SetCurrentNode("MUSIC");
	break;
	case OPAGE_CAMERA_MOD:
		SetNodeUsing("SUBTITLE",true);
		SetNodeUsing("STRINGS_CAMERA",true);
		SetNodeUsing("CAMERAMODE_1",true);
		SetNodeUsing("CAMERAMODE_2",true);
		TmpI_ShowCameraMode();
		TmpI_ShowInvertMode();
		if( GetTargetPlatform()=="pc" )	{
			SetSelectable("CAMERAMODE_1",false);
			SetSelectable("CAMERAMODE_2",false);
		} else {SetCurrentNode("CAMERAMODE_1");}
	break;

	case OPAGE_CONTROLS_1:
		SetNodeUsing("SUBTITLE",true);
		SetNodeUsing("STRINGS_CONTROLS",true);
		SetNodeUsing("CONTROLS_B_CHANGE",true);
		SetNodeUsing("CONTROLS_B_DEFAULT",true);
		SetCurrentNode("CONTROLS_B_CHANGE");
	break;

	case OPAGE_CONTROLS_2:
		SetNodeUsing("SUBTITLE",true);
		SetNodeUsing("STRINGS_CONTROLS",true);
		SetNodeUsing("B_SAILING1ST",true);
		SetNodeUsing("B_PRIMARY_LAND",true);
		SetNodeUsing("B_SAILING3RD",true);
		SetNodeUsing("B_FIGHTMODE",true);
		SetCurrentNode("B_SAILING1ST");
	break;

	case OPAGE_CONTROLS_3:
		SetNodeUsing("SUBTITLE",true);
		SetNodeUsing("STRINGS_CONTROLS",true);
		SetNodeUsing("CONTROLSWINDOW",true);
		SetNodeUsing(gsKeyWindowName,true);
		SetNodeUsing("CONTROLGROUP",true);
		SetNodeUsing("SCROLL",true);
		EnableString("GroupName");
		SetCurrentNode("CONTROLSWINDOW");
	break;
	}
}

void DoTitleSelect()
{
	ShowOptionsPage(OPAGE_MAIN);
}

void SetShowGroup(string groupName)
{
	g_sGroupName = groupName;
	switch(groupName)
	{
	case "Sailing1Pers":
		GameInterface.strings.GroupName = XI_ConvertString("Sailing 1St Person");
	break;
	case "PrimaryLand":
		GameInterface.strings.GroupName = XI_ConvertString("Primary Land");
	break;
	case "Sailing3Pers":
		GameInterface.strings.GroupName = XI_ConvertString("Sailing 3rd Person");
	break;
	case "FightModeControls":
		GameInterface.strings.GroupName = XI_ConvertString("Fight Mode");
	break;
	}

	SetFormatedText("CONTROLSWINDOW","");

	int lngFile = LanguageOpenFile("ControlsNames.txt");
	if(lngFile<0) return;

	aref arGroup;
	makearef(arGroup,objControlsState.keygroups.(groupName));

	// ѕрописать контроли в список
	DeleteAttribute(&objArrayControls,"");
	int i, idx, tmpcolor;
	aref arControl;
	bool bTmpBool;
	int qn = GetAttributesNum(arGroup);
	string cntrlText,tmpstr;
	idx = 0;
	for(i=0; i<qn; i++)
	{
		arControl = GetAttributeN(arGroup,i);
		if( DisableShowControl(arControl) ) continue;
		//if( ControlIsStick(arControl) ) continue;
		if( CheckAttribute(arControl,"invisible") && sti(arControl.invisible)==true ) continue;
		if( CheckAttribute(arControl,"remapping") && sti(arControl.remapping)==false ) {
			bTmpBool = false;
			tmpcolor = argb(255,128,128,128);
		}
		else {
			bTmpBool = true;
			tmpcolor = argb(255,255,255,255);
		}

		if( g_bDisableControlChange )
		{
			bTmpBool = false;
			tmpcolor = argb(255,128,128,128);
		}

		tmpstr = GetAttributeName(arControl);

		cntrlText = LanguageConvertString(lngFile,tmpstr);
		if(cntrlText=="") continue;
		SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"CONTROLSWINDOW", 0,&cntrlText);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CONTROLSWINDOW", 8,-1,tmpcolor);
		SetControlNameForIdx(idx, tmpstr, bTmpBool);
		idx++;
	}

	LanguageCloseFile(lngFile);
	Event("evntUpdateFormtText","sll","CONTROLSWINDOW",0,0);
}

void SetControlNameForIdx(int idx, string controlName, bool bRemapEnable)
{
	string attrName = "i"+idx;
	objArrayControls.(attrName) = controlName;
	objArrayControls.(attrName).enable = bRemapEnable;
}

void procFTUpdate()
{
	string nodName = GetEventData();
	if(nodName!="CONTROLSWINDOW") return;
	int grNum = GetEventData(); // перва€ группа в изменени€х
	int strNum = GetEventData(); // перва€ строка в изменени€х

	object objPos,obj;
	DeleteAttribute(&objPos,"");
	SendMessage(&GameInterface,"lsla",MSG_INTERFACE_MSG_TO_NODE,"CONTROLSWINDOW", 3,&objPos);

	SetFormatedText(gsKeyWindowName,"");

	int i,qn,posnum;
	qn = GetAttributesNum(&objPos);
	int idx=0;
	for(i=0; i<qn; i++)
	{
		posnum = sti( GetAttributeValue(GetAttributeN(&objPos,i)) );
		if(posnum>=0)
		{
			idx = SetKeysStrings(grNum+i,posnum,idx);
		}
	}
	nLastTextGroupNum = grNum;
	nLastTextStringNum = strNum;
}

void procFTSetScrollPos()
{
	string nodName = GetEventData();
	float fpos = GetEventData();
	if(nodName=="CONTROLSWINDOW")
	{
		SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL",fpos);
	}
}

void ProcScrollPosChange()
{
	float newPos = GetEventData();
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"CONTROLSWINDOW",2, newPos);
}

int SetKeysStrings(int grNum, int newpos, int oldpos)
{
	int i;
	string tmpStr;
	string keyStr = " ";
	for(i=oldpos; i<newpos; i++)
	{
		SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,gsKeyWindowName, 0,&keyStr);
	}

	aref arGroupRoot,arKey;
	makearef(arGroupRoot,objControlsState.keygroups.(g_sGroupName));
	tmpStr = GetControlNameFromIdx(grNum);
	if( CheckAttribute(arGroupRoot,tmpStr) )	tmpStr = arGroupRoot.(tmpStr);
	else	tmpStr = "";

	if(CheckAttribute(&objControlsState,"key_codes."+tmpStr+".img"))
	{
		keyStr = objControlsState.key_codes.(tmpStr).img;
	}
	if(keyStr=="")	keyStr=" ";

	i += SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,gsKeyWindowName, 0,&keyStr);
	return i;
}

string GetControlNameFromIdx(int idx)
{
	string attrName = "i"+idx;
	if( CheckAttribute(&objArrayControls,attrName) ) return objArrayControls.(attrName);
	return "";
}

void procFTActivate()
{
	string nodName = GetEventData();
	if(nodName!="CONTROLSWINDOW") return;
	curCntrlIdx = GetEventData(); // номер текста

	if( !IsEnableRemapping(curCntrlIdx) ) return;

	SetNodeUsing("KEYCHOOSE_RECT",true);
	SetNodeUsing("SET_BUTTON",true);
	SetNodeUsing("DELETE_BUTTON",true);
	SetNodeUsing("INVERSE_BUTTON",true);
	SetCurrentNode("SET_BUTTON");

	SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 1, "SET_BUTTON");
	SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 2, "DELETE_BUTTON");
	SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 2, "INVERSE_BUTTON");
}

bool IsEnableRemapping(int nControl)
{
	aref arControl;
	arControl = GetAttributeN(&objArrayControls,nControl);
	return sti(arControl.enable);
}

void ReturnToViewControls()
{
	SetNodeUsing("KEYCHOOSE_RECT",false);
	SetNodeUsing("SET_BUTTON",false);
	SetNodeUsing("DELETE_BUTTON",false);
	SetNodeUsing("INVERSE_BUTTON",false);
	SendMessage(&GameInterface,"ll", MSG_INTERFACE_LOCK_NODE, 0);
	SetCurrentNode("CONTROLSWINDOW");
}

void SetReassignMode()
{
	SetNodeUsing("KEYCHOOSE_RECT",true);
	SetNodeUsing("KEY_CHOOSER",true);
	SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 1, "KEY_CHOOSER");
	SetCurrentNode("KEY_CHOOSER");
}

void ReturnFromReassign()
{
	SetNodeUsing("KEYCHOOSE_RECT",false);
	SetNodeUsing("KEY_CHOOSER",false);
	SendMessage(&GameInterface,"ll", MSG_INTERFACE_LOCK_NODE, 0);
	SetCurrentNode("CONTROLSWINDOW");
}

void UnmapControl()
{
	aref arControlGroup;
	string contrlName,groupName;

	makearef(arControlGroup,objControlsState.keygroups.(g_sGroupName));

	contrlName = GetControlNameFromIdx(curCntrlIdx);

	int state = 0;
	if(CheckAttribute(&arControlGroup,contrlName+".state"))
	{	state = sti(arControlGroup.(contrlName).state);	}

	CI_CreateAndSetControls( g_sGroupName,contrlName, -1,state, true );

	Event("evntUpdateFormtText","sll","CONTROLSWINDOW", nLastTextGroupNum, nLastTextStringNum);
}

void InverseControl()
{
	if(curCntrlIdx<0)	return;
	aref arControlGroup;
	string contrlName;

	makearef(arControlGroup, objControlsState.keygroups.(g_sGroupName));
	contrlName = GetAttributeValue(GetAttributeN(&objArrayControls,curCntrlIdx));

	int state = 0;
	if(CheckAttribute(arControlGroup,contrlName+".state")) {
		state = sti(arControlGroup.(contrlName).state);
	}

	switch(state)
	{
	case USE_AXIS_AS_BUTTON:		state=USE_AXIS_AS_INVERSEBUTTON;	break;
	case USE_AXIS_AS_INVERSEBUTTON:	state=USE_AXIS_AS_BUTTON;	break;
	case INVERSE_CONTROL:			state=0;	break;
	case 0:							state=INVERSE_CONTROL;	break;
	}

	arControlGroup.(contrlName).state = state;
	CI_CreateAndSetControls( g_sGroupName, contrlName, CI_GetKeyCode(arControlGroup.(contrlName)), state, true );

	Event("evntUpdateFormtText","sll","CONTROLSWINDOW", nLastTextGroupNum, nLastTextStringNum);
}

int glob_retVal;
ref procKeyChoose()
{
	int keyIdx = GetEventData();
	int stickUp = GetEventData();

	glob_retVal = false;
	if( DoMapToOtherKey(keyIdx,stickUp) )
	{
		ReturnFromReassign();
		Event("evntUpdateFormtText","sll","CONTROLSWINDOW", nLastTextGroupNum, nLastTextStringNum);
		glob_retVal = true;
	}

	return &glob_retVal;
}

bool DoMapToOtherKey(int keyIdx,int stickUp)
{
	aref arControlGroup;
	aref arKeyRoot,arKey;
	string contrlName, tmpstr;
	int keyCode;

	if( stickUp )
	{
		SetStickNotAvailable();
		return false;
	}

	makearef(arControlGroup,objControlsState.keygroups.(g_sGroupName));

	contrlName = GetControlNameFromIdx(curCntrlIdx);

	makearef(arKeyRoot,objControlsState.key_codes);
	arKey = GetAttributeN(arKeyRoot,keyIdx);
	keyCode = sti(GetAttributeValue(arKey));

	if( CheckAttribute(arKey,"stick") && sti(arKey.stick)==true ) return false;

	if( KeyAlreadyUsed(g_sGroupName, contrlName, GetAttributeName(arKey)) )
	{
		SetAlreadyUsedShow();
		return false;
	}

	tmpstr = arControlGroup.(contrlName);
	if( CheckAttribute(arKeyRoot,tmpstr+".stick") && sti(arKeyRoot.(tmpstr).stick)==true ) return false;

	int state = 0;
	if(CheckAttribute(arControlGroup,contrlName+".state"))
	{	state = sti(arControlGroup.(contrlName).state);	}

	CI_CreateAndSetControls( g_sGroupName,contrlName,keyCode, state, true );
	return true;
}

void SetAlreadyUsedShow()
{
	nFadeStr_NoStick = 0;
	nFadeStr_AlUsed = 15;
}
void SetStickNotAvailable()
{
	nFadeStr_AlUsed = 0;
	nFadeStr_NoStick = 15;
}

void FadeStringsUpdate()
{
	int color;
	if( nFadeStr_AlUsed>0 )
	{
		nFadeStr_AlUsed--;
		if(nFadeStr_AlUsed==0)
		{
			GameInterface.strings.AlreadyUsed = "";
		}
		else
		{
			color = argb(GetAlphaFromFade(nFadeStr_AlUsed),255,255,255);
			CreateString(true,"AlreadyUsed",XI_ConvertString("Button Already Used"),FONT_NORMAL,color,320,258,SCRIPT_ALIGN_CENTER,1.0);
		}
	}

	if( nFadeStr_NoStick>0 )
	{
		nFadeStr_NoStick--;
		if(nFadeStr_NoStick==0)
		{
			GameInterface.strings.AlreadyUsed = "";
		}
		else
		{
			color = argb(GetAlphaFromFade(nFadeStr_NoStick),255,255,255);
			CreateString(true,"AlreadyUsed",XI_ConvertString("thumbstick cannot be used"),FONT_NORMAL,color,320,258,SCRIPT_ALIGN_CENTER,1.0);
		}
	}

	PostEvent("evntFadeStrings",100);
}

bool KeyAlreadyUsed(string groupName, string controlName, string keyName)
{
	int n, q;
	aref arRoot, arCntrl;
	makearef( arRoot, objControlsState.keygroups.(groupName) );
	q = GetAttributesNum(arRoot);

	for(n=0; n<q; n++)
	{
		arCntrl = GetAttributeN(arRoot,n);
		if( GetAttributeName(arCntrl)==controlName ) continue;
		if( GetAttributeValue(arCntrl)==keyName) return true;
	}

	return false;
}

int GetAlphaFromFade(int n)
{
	int alpha = n*20;
	if(alpha>255) alpha = 255;
	if(alpha<0) alpha = 0;
	return alpha;
}

void SetOldButton()
{
	switch(g_sGroupName)
	{
	case "Sailing1Pers":		SetCurrentNode("B_SAILING1ST"); break;
	case "PrimaryLand":			SetCurrentNode("B_PRIMARY_LAND"); break;
	case "Sailing3Pers":		SetCurrentNode("B_SAILING3RD"); break;
	case "FightModeControls":	SetCurrentNode("B_FIGHTMODE"); break;
	}
}

void TmpI_ProcessCameraInvert()
{
	if( GetTargetPlatform() == "pc" )
	{
		object objTmpCntrlList;
		aref arGroupRoot, arGroup, arControl;
		string contrlName, groupName;
		int i1, i2, q1, q2, state;
		bool bChangeEnable;

		makearef(arGroupRoot, objControlsState.keygroups);
		q1 = GetAttributesNum(arGroupRoot);

		for(i1=0; i1<q1; i1++)
		{
			arGroup = GetAttributeN(arGroupRoot,i1);
			q2 = GetAttributesNum(arGroup);
			for(i2=0; i2<q2; i2++)
			{
				arControl = GetAttributeN(&arGroup,i2);
				if( !ControlIsStick(arControl) ) {continue;}

				if( !CheckAttribute(arControl,"remapping") || sti(arControl.remapping)==false ) {continue;}

				groupName = GetAttributeName(arGroup);
				contrlName = GetAttributeName(arControl);

				if( CheckAttribute(&objTmpCntrlList,contrlName) ) {continue;}

				if( CheckAttribute(arControl,"state") )	{state = sti(arControl.state);}
				else	{state = 0;}

				if( state!=0 && state!=INVERSE_CONTROL ) {continue;}

				objTmpCntrlList.(contrlName).group = groupName;
				objTmpCntrlList.(contrlName).key = CI_GetKeyCode(GetAttributeValue(arControl));

				if( state==0 ) {
					objTmpCntrlList.(contrlName).state = INVERSE_CONTROL;
				} else {
					objTmpCntrlList.(contrlName).state = 0;
				}
			}
		}

		makearef(arGroupRoot, objTmpCntrlList);
		q1 = GetAttributesNum(arGroupRoot);
		for(i1=0; i1<q1; i1++)
		{
			arControl = GetAttributeN(arGroupRoot,i1);
			CI_CreateAndSetControls( arControl.group, GetAttributeName(arControl), sti(arControl.key), sti(arControl.state), true );
		}
	}

	if( CheckAttribute(&InterfaceStates,"InvertCameras") && sti(InterfaceStates.InvertCameras)!=0 ) {
		InterfaceStates.InvertCameras = false;
	} else {
		InterfaceStates.InvertCameras = true;
	}

	if( GetTargetPlatform()=="xbox" )
	{
		ControlsInit("xbox",false);
	}
}

bool ControlIsStick(aref arControl)
{
	string sKeyName = GetAttributeValue(arControl);
	if( CheckAttribute(&objControlsState,"key_codes."+sKeyName+".stick") &&
		sti(objControlsState.key_codes.(sKeyName).stick)==true )
	{
		return true;
	}
	return false;
}

bool DisableShowControl(aref arControl)
{
	if( ControlIsStick(arControl) ) return true;
	switch( GetAttributeValue(arControl) )
	{
	case "DPAD_UP": return true; break;
	case "DPAD_DOWN": return true; break;
	case "DPAD_RIGHT": return true; break;
	case "DPAD_LEFT": return true; break;
	}
	return false;
}

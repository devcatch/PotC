
#include "dialog_func.c"


#define EVENT_DIALOG_START		"evntDialogStart"
#define EVENT_DIALOG_EXIT		"evntDialogExit"

#event_handler("dlgReady", "StartDialogWithMainCharacter");
#event_handler("EmergencyDialogExit","DialogExit");

extern void ProcessDialogEvent();


bool dialogDisable = false;
object	Dialog;
ref		CharacterRef;
bool	dialogRun = false;

bool	dialogSelf = false;

string  FullDialogPath;

//�������������
void DialogsInit()
{
	Quest_Init();				//������������� ���������� ��������� ������ � ���������� �� NPC ------- �����
}

//������ ������
bool DialogMain(ref Character)
{
	//���� ������ �������, �������
	if(dialogRun != false) return false;
	//������ �� �������� ���������
	ref mainChr = GetMainCharacter();
	//���� ������ �� ��������, �������
	if(!IsEntity(mainChr)) return false;
	if(!IsEntity(Character)) return false;
	if(LAi_IsDead(mainChr)) return false;
	if(LAi_IsDead(Character)) return false;
	//�������� �� ������������� �������� ����
	if(!CheckAttribute(Character, "Dialog.CurrentNode"))
	{
		Trace("Dialog: Character <" + Character.id + "> can't have field Dialog.CurrentNode, exit from dialog!")
		return false;
	}
	//���� �������� �� ����� �������� �������
	if(!LAi_Character_CanDialog(mainChr, Character)) return false;
	//���� �������� �� ����� �������� �������
	if(!LAi_Character_CanDialog(Character, mainChr)) return false;
	//��������� ������ �� ���� � ��� �������
	CharacterRef = Character;
	//���� �� �������
	FullDialogPath = "dialogs\" + Character.Dialog.Filename;
	if(LoadSegment(FullDialogPath)==0)
	{
		Trace("Dialog: Missing dialog file: " + FullDialogPath);
		FullDialogPath = "dialogs\error_dialog.c";
		if(LoadSegment(FullDialogPath)==0)
		{
			Trace("Dialog: Missing dialog file: " + FullDialogPath);
			return false;
		}
	}
	//����� �������� ������
	dialogRun = true;
	dialogSelf = false;
	LAi_Character_StartDialog(mainChr, Character);
	LAi_Character_StartDialog(Character, mainChr);
	SendMessage(mainChr, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 1);
	SendMessage(Character, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 1);	
	//��������� ������
	//Trace("Dialog: dialog path for character <" + Character.id + "> = " + FullDialogPath);
	Dialog.CurrentNode = CharacterRef.Dialog.CurrentNode;
	startDialogMainCounter = 0;
	SetEventHandler("frame", "StartDialogMain", 1);
	SetTimeScale(0.0);
	return true;	
}

int startDialogMainCounter = 0;
int dialogWaitGreetingSound = 0;
string dialogGreetingSound = "";

void StartDialogMain()
{
	startDialogMainCounter++;
	if(startDialogMainCounter < 3) return;
	
	DelEventHandler("frame", "StartDialogMain");

	CreateEntity(&Dialog, "dialog");
	Dialog.headModel = CharacterRef.headModel;
	Dialog.gender = CharacterRef.sex;

	DeleteAttribute(&Dialog,"Links");
	DeleteAttribute(&Dialog,"Text");

	if(CheckAttribute(CharacterRef, "greeting"))
	{
		if(CharacterRef.greeting != "")
		{
			dialogGreetingSound = CharacterRef.greeting;
			dialogWaitGreetingSound = 0;
			SetEventHandler("frame", "DialogPlayGreeting", 1);
		}
	}

	object persRef = GetCharacterModel(Characters[GetMainCharacterIndex()]);
	SendMessage(&Dialog, "lii", 0, &Characters[GetMainCharacterIndex()], &persRef);

	object charRef = GetCharacterModel(Characters[makeint(CharacterRef.index)]);
	SendMessage(&Dialog, "lii", 1, &Characters[makeint(CharacterRef.index)], &charRef);

	LayerCreate("realize",1);
	LayerSetRealize("realize",1);
	LayerAddObject("realize",Dialog,-256);
	Set_inDialog_Attributes();
	ProcessDialogEvent();

	SetEventHandler("DialogEvent","ProcessDialogEvent",0);
	//SetEventHandler("DialogCancel","DialogExit",0);

	Event(EVENT_DIALOG_START,"");
}

void DialogPlayGreeting()
{
	dialogWaitGreetingSound++;
	if(dialogWaitGreetingSound < 10) return;
	dialogWaitGreetingSound = 0;
	DelEventHandler("frame", "DialogPlayGreeting");
	Dialog.greeting = CharacterRef.greeting;
}

//������ ������ � ����� �����
void SelfDialog(ref Character)
{
	//���� ������ �������, �������
	if(dialogRun != false) return false;
	//���� ������ �� ��������, �������
	if(!IsEntity(Character)) return false;
	//�������� �� ������������� �������� ����
	if(!CheckAttribute(Character, "Dialog.CurrentNode"))
	{
		Trace("SelfDialog: Character <" + Character.id + "> can't have field Dialog.CurrentNode, exit from dialog!")
		return false;
	}
	//��������� ������ �� ���� � ��� �������
	CharacterRef = Character;
	//���� �� �������
	FullDialogPath = "dialogs\" + Character.Dialog.Filename;
	if(LoadSegment(FullDialogPath)==0)
	{
		Trace("SelfDialog: Missing dialog file: " + FullDialogPath);
		FullDialogPath = "dialogs\error_dialog.c";
		if(LoadSegment(FullDialogPath)==0)
		{
			Trace("SelfDialog: Missing dialog file: " + FullDialogPath);
			return false;
		}
	}
	//���� �������� �� ����� �������� �������
	LAi_Character_CanDialog(Character, Character);
	//����� �������� ������
	dialogRun = true;
	dialogSelf = true;
	SendMessage(Character, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 1);
	//��������� ������
	Dialog.CurrentNode = CharacterRef.Dialog.CurrentNode;
	//Trace("SelfDialog: dialog path for self character <" + Character.id + "> = " + FullDialogPath);
	CreateEntity(&Dialog, "dialog");
	Dialog.headModel = Character.headModel;
	Dialog.gender = Character.sex;

	object persRef = GetCharacterModel(Characters[GetMainCharacterIndex()]);
	SendMessage(&Dialog, "lii", 0, Character, &persRef);
	SendMessage(&Dialog, "lii", 1, Character, &persRef);
	

	LayerCreate("realize",1);
	LayerSetRealize("realize",1);
	LayerAddObject("realize",Dialog,-256);
	Set_inDialog_Attributes();
	ProcessDialogEvent();

	SetEventHandler("DialogEvent","ProcessDialogEvent",0);
	//SetEventHandler("DialogCancel","DialogExit",0);	

	Event(EVENT_DIALOG_START,"");
}

//��������� ������
void DialogExit()
{
	//���� ������� ��� �� ������, ������
	if(dialogRun == false) return;
	DelEventHandler("frame", "DialogPlayGreeting");
	//����������� �������
	DeleteClass(&Dialog);
	UnloadSegment(FullDialogPath);
	if(dialogSelf == false)
	{
		//������ �� �������� ���������
		ref mainChr = GetMainCharacter();
		//�������, ��� ��������� ������������ �� �������
		LAi_Character_EndDialog(mainChr, CharacterRef);
		LAi_Character_EndDialog(CharacterRef, mainChr);
		SendMessage(mainChr, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 0);
		SendMessage(CharacterRef, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 0);
	}else{
		LAi_Character_EndDialog(CharacterRef, CharacterRef);
		SendMessage(CharacterRef, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 0);
	}
	dialogRun = false;
	//������� �� ��������� �������
	PostEvent(EVENT_DIALOG_EXIT, 1, "l", sti(CharacterRef.index));
}

//��� ������� �������� �� Player
void StartDialogWithMainCharacter()
{
	if(LAi_IsBoardingProcess()) return;
	if(dialogDisable) return;
	//� ��� ����� ��������
	int person = GetEventData();
	//���� � ����� �� ��������
	if(person == GetMainCharacterIndex()) return;
	//� ��������������� ����������� �� ��������
	if(!IsEntity(&Characters[person])) return;
	//�������� ������
	DialogMain(&Characters[person]);	
	//Trace("Dialog: start dialog " + person + " whith main character");
}

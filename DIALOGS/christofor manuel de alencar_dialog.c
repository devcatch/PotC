#include "DIALOGS\christofor manuel de alencar_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref PChar;
	PChar = GetMainCharacter();

	
	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";

			if (npchar.quest.meeting == "0")
			{
				dialog.snd = "Voice\CHMA\CHMA001";
				dialog.text = DLG_TEXT[0] + npchar.name + " " + npchar.middlename + " " + npchar.lastname + DLG_TEXT[1] + address_form.spa + DLG_TEXT[2];
				Link.l1 = DLG_TEXT[3] + pchar.name + " " + pchar.lastname + DLG_TEXT[4];
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.snd = "Voice\CHMA\CHMA002";
				dialog.text = DLG_TEXT[5];
				link.l1 = DLG_TEXT[6];
				link.l1.go = "quests";
				link.l2 = DLG_TEXT[7];
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "node_1":
			dialog.snd = "Voice\CHMA\CHMA003";
			dialog.text = DLG_TEXT[8];
			link.l1 = DLG_TEXT[9];
			link.l1.go = "quests";
			link.l2 = DLG_TEXT[10];
			link.l2.go = "node_2";
		break;

		case "node_2":
			dialog.snd = "Voice\CHMA\CHMA004";
			dialog.text = DLG_TEXT[11];
			link.l1 = DLG_TEXT[12];
			link.l1.go = "exit";
		break;

		case "quests":
			dialog.snd = "Voice\CHMA\CHMA005";
			dialog.text = DLG_TEXT[13] + address_form.spa + DLG_TEXT[14];
			link.l1 = DLG_TEXT[15];
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "quest.generate_kill_quest") && GetNationRelation2MainCharacter(SPAIN) != RELATION_ENEMY)
			{
				dialog.text = DLG_TEXT[16];
				link.l1 = DLG_TEXT[17];
				link.l1.go = "kill_pirate";
			}			
			if (CheckQuestAttribute("generate_kill_quest", "completed"))
			{
				dialog.text = DLG_TEXT[18];
				link.l1 = DLG_TEXT[19];
				link.l1.go = "kill_pirate_completed";
			}	
		break;
		
		case "kill_pirate":
			GeneratePirateQuest("IslaMuelle");
			dialog.text = DLG_TEXT[20] + characters[GetCharacterIndex(DLG_TEXT[21])].ship.name + DLG_TEXT[22] + pchar.quest.killdestination + DLG_TEXT[23] + pchar.quest.killmoney + DLG_TEXT[24];
			link.l1 = DLG_TEXT[25];
			link.l1.go = "kill_pirate_agree";
			link.l2 = DLG_TEXT[26];
			link.l2.go = "kill_pirate_refused";
		break;
		
		case "kill_pirate_agree":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("kill_pirate_agree");
		break;
		
		case "kill_pirate_refused":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("kill_pirate_refused");
		break;
		
		case "kill_pirate_completed":
			AddPartyExp(pchar, 1500);
			AddMoneyToCharacter(pchar, makeint(pchar.quest.killmoney));
			AddDialogExitQuest("kill_pirate_refused_2");
			ChangeCharacterReputation(pchar, 1);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.quest.generate_kill_quest = "wait_timer";
		break;
						
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
	}
}

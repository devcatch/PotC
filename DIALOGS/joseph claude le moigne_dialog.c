#include "DIALOGS\joseph claude le moigne_dialog.h"
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
		// -----------------------------------ƒиалог первый - перва€ встреча
		case "First time":
			Dialog.defAni = "Gov_dialog_1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "Gov_dialog_1";
			Dialog.cam = "1";
			Dialog.snd = "dialogs\0\009";

			dialog.text = DLG_TEXT[0] + Address_form.fra + DLG_TEXT[1];
			Link.l1 = DLG_TEXT[2] + pchar.name + " " + pchar.lastname + DLG_TEXT[3] + pchar.ship.name + DLG_TEXT[4];
			Link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			if (makeint(pchar.reputation) < 10)
			{
				Dialog.Text = DLG_TEXT[5] + npchar.name + " " + npchar.lastname + DLG_TEXT[6];
				link.l1 = DLG_TEXT[7];
				link.l1.go = "second time";
			}
			else
			{
				Dialog.text = DLG_TEXT[8] + Address_form.fra + DLG_TEXT[9];
				link.l1 = DLG_TEXT[10];
				link.l1.go = "second time";
			}
		break;

		case "Second time":
			dialog.text = DLG_TEXT[11] + Address_Form.fra + DLG_TEXT[12];
			link.l1 = DLG_TEXT[13];
			link.l1.go = "quest";
			if (npchar.quest.english_war_ship == "1")
			{
				link.l1 = DLG_TEXT[14];
				link.l1.go = "english_war_ship_5";
			}
			link.l2 = DLG_TEXT[15];
			link.l2.go = "node_2";
			NextDiag.TempNode = "Second time";
		break;

		case "node_2":
			dialog.text = DLG_TEXT[16] + Address_Form.Fra + DLG_TEXT[17];
			link.l1 = DLG_TEXT[18];
			link.l1.go = "exit";
		break;

		case "quest":
			dialog.text = DLG_TEXT[19] + Address_form.fra + DLG_TEXT[20];
			link.l1 = DLG_TEXT[21];
			link.l1.go = "exit";
			if (npchar.quest.english_war_ship == "0")
			{
				dialog.text = DLG_TEXT[22];
				link.l1 = DLG_TEXT[23];
				link.l1.go = "english_war_ship";
			}
			if (npchar.quest.english_war_ship == "2")
			{
				dialog.text = DLG_TEXT[24] + Address_form.Fra + DLG_TEXT[25];
				link.l1 = DLG_TEXT[26];
				link.l1.go = "english_war_ship_4";
				npchar.quest.english_war_ship = "done"
			}
			if (!CheckAttribute(pchar, "quest.generate_kill_quest") && GetNationRelation2MainCharacter(FRANCE) != RELATION_ENEMY)
			{
				dialog.text = DLG_TEXT[27];
				link.l2 = DLG_TEXT[28];
				link.l2.go = "kill_pirate";
			}			
			if (CheckQuestAttribute("generate_kill_quest", "completed"))
			{
				dialog.text = DLG_TEXT[29];
				link.l2 = DLG_TEXT[30];
				link.l2.go = "kill_pirate_completed";
			}	
			if (CheckQuestAttribute("gambling_with_girl", "gambled") || CheckQuestAttribute("gambling_with_girl", "prisoned") || CheckQuestAttribute("gambling_with_girl", "to_hovernor_2"))
			{
				if (CheckQuestAttribute("gambling_with_girl", "to_hovernor_2") && GetNationRelation2MainCharacter(FRANCE) == RELATION_ENEMY)
				{
					//прощают
					dialog.text = DLG_TEXT[31];
					link.l1 = DLG_TEXT[32];
					link.l1.go = "forgive";
					AddQuestRecord("gambled_girl", "13");
					CloseQuestHeader("gambled_girl");
				}
				else
				{
					if (GetNationRelation2MainCharacter(FRANCE) == RELATION_ENEMY)
					{
						//позвол€ют уйти
						dialog.text = DLG_TEXT[33];
						link.l1 = DLG_TEXT[34] + GetCharacterFullName(DLG_TEXT[35]) + DLG_TEXT[36];
						link.l1.go = "ransom";
						AddQuestRecord("gambled_girl", "15");
						CloseQuestHeader("gambled_girl");
					}
					else
					{
						//обычный разговор
						dialog.text = DLG_TEXT[37];
						link.l1 = DLG_TEXT[38] + GetCharacterFullName(DLG_TEXT[39]) + DLG_TEXT[40];
						link.l1.go = "virginie";
						AddQuestRecord("gambled_girl", "14");
						CloseQuestHeader("gambled_girl");
					}
				}
			}
		break;
		
		case "kill_pirate":
			GeneratePirateQuest("Falaisedefleur");
			dialog.text = DLG_TEXT[41] + characters[GetCharacterIndex(DLG_TEXT[42])].ship.name + DLG_TEXT[43] + pchar.quest.killdestination + DLG_TEXT[44] + pchar.quest.killmoney + DLG_TEXT[45];
			link.l1 = DLG_TEXT[46];
			link.l1.go = "kill_pirate_agree";
			link.l2 = DLG_TEXT[47];
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

		case "virginie":
			dialog.text = DLG_TEXT[48];
			link.l1 = DLG_TEXT[49];
			link.l1.go = "ransom_2";
			link.l2 = DLG_TEXT[50];
			link.l2.go = "virginie_2";
		break;

		case "virginie_2":
			dialog.text = DLG_TEXT[51];
			link.l1 = DLG_TEXT[52] + characters[GetCharacterIndex(DLG_TEXT[53])].name + DLG_TEXT[54];
			link.l1.go = "virginie_3";
		break;

		case "virginie_3":
			dialog.text = DLG_TEXT[55];
			link.l1 = DLG_TEXT[56];
			link.l1.go = "exit";
			pchar.quest.gambling_with_girl = "done";
			AddMoneyToCharacter(pchar, 4000);
			SetNationRelation2MainCharacter(FRANCE,RELATION_FRIEND);
			AddPartyExp(pchar, 2800);
			RemovePassenger(pchar, characterFromID("Virginie d'Espivant"));
		break;

		case "ransom":
			dialog.text = DLG_TEXT[57];
			link.l1 = DLG_TEXT[58];
			link.l1.go = "ransom_2";
		break;

		case "ransom_2":
			dialog.text = DLG_TEXT[59];
			link.l1 = DLG_TEXT[60];
			link.l1.go = "ransom_3";
		break;

		case "ransom_3":
			dialog.text = DLG_TEXT[61];
			link.l1 = DLG_TEXT[62];
			link.l1.go = "ransom_4";
		break;

		case "ransom_4":
			dialog.text = DLG_TEXT[63];
			link.l1 = DLG_TEXT[64];
			link.l1.go = "ransom_5";
		break;

		case "ransom_5":
			dialog.text = DLG_TEXT[65];
			link.l1 = DLG_TEXT[66];
			link.l1.go = "ransom_6";
		break;

		case "ransom_6":
			dialog.text = DLG_TEXT[67];
			link.l1 = DLG_TEXT[68];
			link.l1.go = "exit";
			pchar.quest.gambling_with_girl = "done";
			AddMoneyToCharacter(pchar, 7000);
			AddPartyExp(pchar, 1600);
			pchar.quest.remove_virginie.win_condition.l1 = "location";
			pchar.quest.remove_virginie.win_condition.l1.location = "FalaiseDeFleur";
			pchar.quest.remove_virginie.win_condition = "remove_virginie_complete";
			SetNationRelation2MainCharacter(FRANCE,RELATION_ENEMY);
		break;

		case "forgive":
			dialog.text = DLG_TEXT[69];
			link.l1 = DLG_TEXT[70];
			link.l1.go = "forgive_2";
		break;

		case "forgive_2":
			dialog.text = DLG_TEXT[71];
			link.l1 = DLG_TEXT[72];
			link.l1.go = "forgive_3";
		break;

		case "forgive_3":
			dialog.text = DLG_TEXT[73];
			link.l1 = DLG_TEXT[74];
			link.l1.go = "exit";
			pchar.quest.gambling_with_girl = "done";
			AddMoneyToCharacter(pchar, 4000);
			SetNationRelation2MainCharacter(FRANCE,RELATION_NEUTRAL);
			AddPartyExp(pchar, 2500);
			RemovePassenger(pchar, characterFromID("Virginie d'Espivant"));
		break;

		case "english_war_ship":
			dialog.text = DLG_TEXT[75];
			link.l1 = DLG_TEXT[76];
			link.l1.go = "english_war_ship_1";
			link.l2 = DLG_TEXT[77];
			link.l2.go = "exit";
		break;

		case "english_war_ship_1":
			dialog.text = DLG_TEXT[78] + Address_form.fra + DLG_TEXT[79];
			link.l1 = DLG_TEXT[80];
			link.l1.go = "english_war_ship_2";
			link.l2 = DLG_TEXT[81];
			link.l2.go = "english_war_ship_3";
		break;

		case "english_war_ship_2":
			dialog.text = DLG_TEXT[82] + Address_form.fra + DLG_TEXT[83];
			link.l1 = DLG_TEXT[84];
			link.l1.go = "exit";
			AddDialogExitQuest("joseph_claude_le_mougne_english_war_ship");
		break;

		case "english_war_ship_3":
			dialog.text = DLG_TEXT[85];
			link.l1 = DLG_TEXT[86];
			link.l1.go = "english_war_ship_2";
			link.l2 = DLG_TEXT[87];
			link.l2.go = "exit";
			npchar.quest.english_war_ship = "done";
		break;

		case "english_war_ship_4":
			dialog.text = DLG_TEXT[88];
			link.l1 = DLG_TEXT[89];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			AddPartyExp(pchar, 1500);
			npchar.quest.english_war_ship = "done";
			AddQuestRecord("Hire_by_france_for_defeat_england_corvette", "3");
			CloseQuestHeader("Hire_by_france_for_defeat_england_corvette");
		break;

		case "english_war_ship_5":
			dialog.text = DLG_TEXT[90];
			link.l1 = DLG_TEXT[91];
			link.l1.go = "english_war_ship_6";
			link.l2 = DLG_TEXT[92];
			link.l2.go = "exit";
		break;

		case "english_war_ship_6":
			dialog.text = DLG_TEXT[93];
			link.l1 = DLG_TEXT[94];
			link.l1.go = "exit";
			npchar.quest.english_war_ship = "done_1";
			ChangeCharacterReputation(pchar, -1);
			AddQuestRecord("Hire_by_france_for_defeat_england_corvette", "2");
			CloseQuestHeader("Hire_by_france_for_defeat_england_corvette");
		break;
				
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
	}
}

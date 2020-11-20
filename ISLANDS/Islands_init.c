
void InitIslands()
{
	int		n, i;

	for (i=0; i<MAX_ISLANDS; i++)
	{
		DeleteAttribute(&Islands[i], "");

		Islands[i].id = "";
		Islands[i].reload_enable = true;
		Islands[i].visible = true;
	}

	// ==================================================================================================
	// Create temp module for enumerate locators
		object	locator;
		CreateEntity(&locator,"locator");


	// ==================================================================================================
	// Falaise de fleur
		n = 0;
		Islands[n].id = "FalaiseDeFleur";
		Islands[n].model = "FalaiseDeFleur";
		Islands[n].filespath.models = "islands\FalaiseDeFleur";
		Islands[n].refl_model = "FalaiseDeFleur_refl";
		Islands[n].locators = "FalaiseDeFleur_locators";
		Islands[n].visible = true;
		Islands[n].smuggling_nation = FRANCE;

		Islands[n].reload.l1.label = "Порт Фале де Флер";
		Islands[n].reload.l1.name = "reload_1";
		Islands[n].reload.l1.go = "Falaise_de_fleur_port_01";
		Islands[n].reload.l1.emerge = "sea";
		Islands[n].reload.l1.radius = 200.0;
		Islands[n].reload.l1.pic = 0;
		Islands[n].reload.l1.tex = "t1";

		Islands[n].reload.l2.label = "Залив Осьминога";
		Islands[n].reload.l2.name = "reload_2";
		Islands[n].reload.l2.go = "Falaise_de_Fleur_shore";
		Islands[n].reload.l2.emerge = "reload1";
		Islands[n].reload.l2.radius = 200.0;
		Islands[n].reload.l2.pic = 2;
		Islands[n].reload.l2.tex = "t1";

		Islands[n].reload.l3.label = "Форт Фале де Флер";
		Islands[n].reload.l3.name = "reload_fort1";
		Islands[n].reload.l3.go = "Falaise_de_Fleur_fort";
		Islands[n].reload.l3.GoAfterBoard.location = "reload_1";
		Islands[n].reload.l3.emerge = "see";
		Islands[n].reload.l3.radius = 250.0;
		Islands[n].reload.l3.fortname = "fort_Falaise_De_Fleur";
		Islands[n].reload.l3.fort.model = "FalaiseDeFleur_fort1";
		Islands[n].reload.l3.fort.locators = "FalaiseDeFleur_fort1_locators";
		Islands[n].reload.l3.pic = 1;
		Islands[n].reload.l3.tex = "t1";
				
		Islands[n].InterfaceTextures.t1 = "battle_interface\moor_7.tga";
		Islands[n].InterfaceTextures.t1.h = 4;
		Islands[n].InterfaceTextures.t1.v = 1;

		Islands[n].Trade.Export.id1 = GOOD_SAILCLOTH;
		Islands[n].Trade.Export.id2 = GOOD_CHOCOLATE;
		Islands[n].Trade.Export.id3 = GOOD_LINEN;
		Islands[n].Trade.Export.id4 = GOOD_SILK;
		Islands[n].Trade.Import.id1 = GOOD_PLANKS;
		Islands[n].Trade.Import.id2 = GOOD_EBONY;
		Islands[n].Trade.Import.id3 = GOOD_RUM;
		Islands[n].Trade.Import.id4 = GOOD_LEATHER;
		Islands[n].Trade.Contraband.id1 = GOOD_SANDAL;
		Islands[n].Trade.Contraband.id2 = GOOD_FRUITS;
		Islands[n].Trade.Contraband.id3 = GOOD_CINNAMON;
        //        Islands[n].Trade.Contraband.id4 = GOOD_SLAVES;

		//breakpoint();
		SendMessage(&locator,"le",LM_LOCATE_I,&Islands[n]);

	// ==================================================================================================
	// Redmond
		n = n + 1;
		Islands[n].id = "Redmond";
		Islands[n].model = "redmond";
		Islands[n].filespath.models = "islands\redmond";
		Islands[n].refl_model = "redmond_refl";
		Islands[n].locators = "redmond_locators";
		Islands[n].visible = true;
		Islands[n].smuggling_nation = ENGLAND;

		Islands[n].reload.l1.label = "Порт Редмонд";
		Islands[n].reload.l1.name = "reload_2";
		Islands[n].reload.l1.go = "REDMOND_PORT";
		Islands[n].reload.l1.emerge = "sea_1";
		Islands[n].reload.l1.radius = 600.0;
		Islands[n].reload.l1.pic = 0;
		Islands[n].reload.l1.tex = "t1";

		Islands[n].reload.l2.label = "Глотка дьявола";
		Islands[n].reload.l2.name = "reload_1";
		Islands[n].reload.l2.go = "Redmond_Shore_01";
		Islands[n].reload.l2.emerge = "reload1";
		Islands[n].reload.l2.radius = 200.0;
		Islands[n].reload.l2.pic = 2;
		Islands[n].reload.l2.tex = "t1";

		Islands[n].reload.l3.label = "Скалистый берег";
		Islands[n].reload.l3.name = "reload_3";
		Islands[n].reload.l3.go = "Redmond_Shore_02";
		Islands[n].reload.l3.emerge = "reload1";
		Islands[n].reload.l3.radius = 200.0;
		Islands[n].reload.l3.pic = 3;
		Islands[n].reload.l3.tex = "t1";

		Islands[n].reload.l4.label = "Форт Редмонд";
		Islands[n].reload.l4.name = "reload_fort1";
		Islands[n].reload.l4.go = "Redmond_fort";
		Islands[n].reload.l4.GoAfterBoard.location = "reload_2";
		Islands[n].reload.l4.emerge = "see";
		Islands[n].reload.l4.fortname = "fort_Redmond";
		Islands[n].reload.l4.radius = 250.0;
		Islands[n].reload.l4.fort.model = "Redmond_fort1";
		Islands[n].reload.l4.fort.locators = "Redmond_fort1_locators";
		Islands[n].reload.l4.pic = 1;
		Islands[n].reload.l4.tex = "t1";

		Islands[n].InterfaceTextures.t1 = "battle_interface\moor_8.tga";
		Islands[n].InterfaceTextures.t1.h = 4;
		Islands[n].InterfaceTextures.t1.v = 1;

		Islands[n].Trade.Export.id1 = GOOD_SAILCLOTH;
		Islands[n].Trade.Export.id2 = GOOD_LINEN;
		Islands[n].Trade.Export.id3 = GOOD_ALE;
		Islands[n].Trade.Export.id4 = GOOD_CLOTHES;
		Islands[n].Trade.Import.id1 = GOOD_PLANKS;
		Islands[n].Trade.Import.id2 = GOOD_CINNAMON;
		Islands[n].Trade.Import.id3 = GOOD_SILK;
		Islands[n].Trade.Import.id4 = GOOD_SANDAL;
		Islands[n].Trade.Contraband.id1 = GOOD_EBONY;
		Islands[n].Trade.Contraband.id2 = GOOD_COFFEE;
		Islands[n].Trade.Contraband.id3 = GOOD_PAPRIKA;
         //       Islands[n].Trade.Contraband.id4 = GOOD_SLAVES;

		SendMessage(&locator,"le",LM_LOCATE_I,&Islands[n]);

	// ==================================================================================================
	// Isla Muelle
		n = n + 1;
		Islands[n].id = "IslaMuelle";
		Islands[n].model = "IslaMuelle";
		Islands[n].filespath.models = "islands\IslaMuelle";
		Islands[n].refl_model = "IslaMuelle_refl";
		Islands[n].locators = "IslaMuelle_locators";
		Islands[n].visible = true;
		Islands[n].smuggling_nation = SPAIN;

		Islands[n].reload.l1.label = "Порт Исла Муелле";
		Islands[n].reload.l1.name = "reload_1";
		Islands[n].reload.l1.go = "Muelle_port";
		Islands[n].reload.l1.emerge = "Reload3";
		Islands[n].reload.l1.radius = 200.0;
		Islands[n].reload.l1.pic = 0;
		Islands[n].reload.l1.tex = "t1";

		Islands[n].reload.l2.label = "Берег";
		Islands[n].reload.l2.name = "reload_2";
		Islands[n].reload.l2.go = "Muelle_shore_02";
		Islands[n].reload.l2.emerge = "see";
		Islands[n].reload.l2.radius = 200.0;
		Islands[n].reload.l2.enable = false;
		Islands[n].reload.l2.pic = 3;
		Islands[n].reload.l2.tex = "t1";

		Islands[n].reload.l3.label = "Устричный пляж";
		Islands[n].reload.l3.name = "reload_3";
		Islands[n].reload.l3.go = "Muelle_shore";
		Islands[n].reload.l3.emerge = "reload2";
		Islands[n].reload.l3.radius = 200.0;
		Islands[n].reload.l3.pic = 2;
		Islands[n].reload.l3.tex = "t1";

		Islands[n].reload.l4.label = "Форт Исла Муелле";
		Islands[n].reload.l4.name = "reload_fort1";
		Islands[n].reload.l4.go = "IslaMuelle_fort";
		Islands[n].reload.l4.GoAfterBoard.location = "reload_1";
		Islands[n].reload.l4.emerge = "see";
		Islands[n].reload.l4.fortname = "fort_Isla_Muelle";
		Islands[n].reload.l4.radius = 250.0;
		Islands[n].reload.l4.fort.model = "IslaMuelle_fort1";
		Islands[n].reload.l4.fort.locators = "IslaMuelle_fort1_locators";
		Islands[n].reload.l4.pic = 1;
		Islands[n].reload.l4.tex = "t1";

		Islands[n].InterfaceTextures.t1 = "battle_interface\moor_4.tga";
		Islands[n].InterfaceTextures.t1.h = 4;
		Islands[n].InterfaceTextures.t1.v = 1;

		Islands[n].Trade.Export.id1 = GOOD_EBONY;
		Islands[n].Trade.Export.id2 = GOOD_MAHOGANY;
		Islands[n].Trade.Export.id3 = GOOD_CINNAMON;
		Islands[n].Trade.Export.id4 = GOOD_SANDAL;
		Islands[n].Trade.Import.id1 = GOOD_PLANKS;
		Islands[n].Trade.Import.id2 = GOOD_SAILCLOTH;
		Islands[n].Trade.Import.id3 = GOOD_SUGAR;
		Islands[n].Trade.Import.id4 = GOOD_LINEN;
		Islands[n].Trade.Contraband.id1 = GOOD_ALE;
		Islands[n].Trade.Contraband.id2 = GOOD_SILK;
		Islands[n].Trade.Contraband.id3 = GOOD_TOBACCO;
        //        Islands[n].Trade.Contraband.id4 = GOOD_SLAVES;

		SendMessage(&locator,"le",LM_LOCATE_I,&Islands[n]);

	// ==================================================================================================
	// Oxbay
		n = n + 1;
		Islands[n].id = "Oxbay";
		Islands[n].model = "Oxbay";
		Islands[n].filespath.models = "islands\Oxbay";
		Islands[n].refl_model = "Oxbay_refl";
		Islands[n].locators = "Oxbay_locators";
		Islands[n].visible = true;
		Islands[n].smuggling_nation = ENGLAND;

		Islands[n].reload.l1.label = "Порт Оксбей";
		Islands[n].reload.l1.name = "reload_2";
		Islands[n].reload.l1.go = "Oxbay_port";
		Islands[n].reload.l1.emerge = "reload2";
		Islands[n].reload.l1.radius = 200.0;
		Islands[n].reload.l1.pic = 0;
		Islands[n].reload.l1.tex = "t1";

		Islands[n].reload.l2.label = "Порт Гринфорд";
  		Islands[n].reload.l2.name = "reload_1";
		Islands[n].reload.l2.go = "Greenford_port";
		Islands[n].reload.l2.emerge = "reload1";
		Islands[n].reload.l2.radius = 200.0;
		Islands[n].reload.l2.pic = 1;
		Islands[n].reload.l2.tex = "t1";

		Islands[n].reload.l3.label = "Залив серой скалы";
		Islands[n].reload.l3.name = "reload_3";
		Islands[n].reload.l3.go = "Oxbay_shore_02";
		Islands[n].reload.l3.emerge = "reload1";
		Islands[n].reload.l3.radius = 300.0;
		Islands[n].reload.l3.pic = 5;
		Islands[n].reload.l3.tex = "t1";

		Islands[n].reload.l4.label = "Маяк";
		Islands[n].reload.l4.name = "reload_4";
		Islands[n].reload.l4.go = "Oxbay_lighthouse";
		Islands[n].reload.l4.emerge = "reload3";
		Islands[n].reload.l4.radius = 200.0;
		Islands[n].reload.l4.pic = 6;
		Islands[n].reload.l4.tex = "t1";

		Islands[n].reload.l5.label = "Дальняя бухта";
		Islands[n].reload.l5.name = "reload_5";
		Islands[n].reload.l5.go = "Oxbay_Shore_01";
		Islands[n].reload.l5.emerge = "see";
		Islands[n].reload.l5.radius = 200.0;
		Islands[n].reload.l5.pic = 4;
		Islands[n].reload.l5.tex = "t1";

		Islands[n].reload.l6.label = "Форт Гринфорд";
		Islands[n].reload.l6.name = "reload_fort1";
		Islands[n].reload.l6.go = "Oxbay_fort2";
		Islands[n].reload.l6.GoAfterBoard.location = "reload_1";
		Islands[n].reload.l6.emerge = "see";
		Islands[n].reload.l6.radius = 250.0;
		Islands[n].reload.l6.fortname = "fort_Greenford";
		Islands[n].reload.l6.fort.model = "Oxbay_fort1";
		Islands[n].reload.l6.fort.locators = "Oxbay_fort1_locators";
		Islands[n].reload.l6.pic = 3;
		Islands[n].reload.l6.tex = "t1";

		Islands[n].reload.l7.label = "Форт Оксбей";
		Islands[n].reload.l7.name = "reload_fort2";
		Islands[n].reload.l7.go = "Oxbay_fort1";
		Islands[n].reload.l7.GoAfterBoard.location = "reload_2";
		Islands[n].reload.l7.emerge = "see";
		Islands[n].reload.l7.fortname = "fort_Oxbay";
		Islands[n].reload.l7.radius = 250.0;
		Islands[n].reload.l7.fort.model = "Oxbay_fort2";
		Islands[n].reload.l7.fort.locators = "Oxbay_fort2_locators";
		Islands[n].reload.l7.pic = 2;
		Islands[n].reload.l7.tex = "t1";

		Islands[n].InterfaceTextures.t1 = "battle_interface\moor_1.tga";
		Islands[n].InterfaceTextures.t1.h = 4;
		Islands[n].InterfaceTextures.t1.v = 2;

		Islands[n].Trade.Export.id1 = GOOD_SANDAL;
		Islands[n].Trade.Export.id2 = GOOD_RUM;
		Islands[n].Trade.Export.id3 = GOOD_TOBACCO;
		Islands[n].Trade.Import.id1 = GOOD_SAILCLOTH;
		Islands[n].Trade.Import.id2 = GOOD_CHOCOLATE;
		Islands[n].Trade.Import.id3 = GOOD_SILK;
		Islands[n].Trade.Import.id4 = GOOD_LEATHER;
		Islands[n].Trade.Contraband.id1 = GOOD_EBONY;
		Islands[n].Trade.Contraband.id2 = GOOD_COFFEE;
		Islands[n].Trade.Contraband.id3 = GOOD_PAPRIKA;
        //        Islands[n].Trade.Contraband.id4 = GOOD_SLAVES;

		SendMessage(&locator,"le",LM_LOCATE_I,&Islands[n]);

	// ==================================================================================================
	// Conceicao
		n = n + 1;
		Islands[n].id = "Conceicao";
		Islands[n].model = "Conceicao";
		Islands[n].filespath.models = "islands\Conceicao";
		Islands[n].refl_model = "Conceicao_refl";
		Islands[n].locators = "Conceicao_locators";
		Islands[n].visible = true;
		Islands[n].smuggling_nation = PORTUGAL;

		Islands[n].reload.l1.label = "Порт Консейкао";
		Islands[n].reload.l1.name = "reload_1";
		Islands[n].reload.l1.go = "Conceicao_port";
		Islands[n].reload.l1.emerge = "reload2";
		Islands[n].reload.l1.radius = 200.0;
		Islands[n].reload.l1.pic = 0;
		Islands[n].reload.l1.tex = "t1";

		Islands[n].reload.l2.label = "Солнечная бухта";
  		Islands[n].reload.l2.name = "reload_2";
		Islands[n].reload.l2.go = "Conceicao_shore_01";
		Islands[n].reload.l2.emerge = "reload1";
		Islands[n].reload.l2.radius = 200.0;
		Islands[n].reload.l2.pic = 2;
		Islands[n].reload.l2.tex = "t1";

		Islands[n].reload.l3.label = "Скала Левиафана";
		Islands[n].reload.l3.name = "reload_3";
		Islands[n].reload.l3.go = "Conceicao_shore_02";
		Islands[n].reload.l3.emerge = "see";
		Islands[n].reload.l3.radius = 200.0;
		Islands[n].reload.l3.pic = 3;
		Islands[n].reload.l3.tex = "t1";

		Islands[n].reload.l4.label = "Форт Консейкао";
		Islands[n].reload.l4.name = "reload_fort1";
		Islands[n].reload.l4.go = "Conceicao_fort";
		Islands[n].reload.l4.GoAfterBoard.location = "reload_1";
		Islands[n].reload.l4.emerge = "see";
		Islands[n].reload.l4.radius = 250.0;
		Islands[n].reload.l4.fortname = "fort_Conceicao";
		Islands[n].reload.l4.fort.locators = "Conceicao_fort1_locators";
		Islands[n].reload.l4.fort.model = "Conceicao_fort1";
		Islands[n].reload.l4.pic = 1;
		Islands[n].reload.l4.tex = "t1";

		Islands[n].InterfaceTextures.t1 = "battle_interface\moor_2.tga";
		Islands[n].InterfaceTextures.t1.h = 4;
		Islands[n].InterfaceTextures.t1.v = 1;

		Islands[n].Trade.Export.id1 = GOOD_SAILCLOTH;
		Islands[n].Trade.Export.id2 = GOOD_SUGAR;
		Islands[n].Trade.Export.id3 = GOOD_CINNAMON;
		Islands[n].Trade.Export.id4 = GOOD_FRUITS;
		Islands[n].Trade.Import.id1 = GOOD_SILK;
		Islands[n].Trade.Import.id2 = GOOD_ALE;
		Islands[n].Trade.Import.id3 = GOOD_RUM;
		Islands[n].Trade.Import.id4 = GOOD_CHOCOLATE;
		Islands[n].Trade.Contraband.id1 = GOOD_WINE;
		Islands[n].Trade.Contraband.id2 = GOOD_MAHOGANY;
		Islands[n].Trade.Contraband.id3 = GOOD_COPRA;
         //       Islands[n].Trade.Contraband.id4 = GOOD_SLAVES;

		SendMessage(&locator,"le",LM_LOCATE_I,&Islands[n]);

	// ==================================================================================================
	// Douwesen
		n = n + 1;
		Islands[n].id = "Douwesen";
		Islands[n].model = "Douwesen";
		Islands[n].filespath.models = "islands\Douwesen";
		Islands[n].refl_model = "Douwesen_refl";
		Islands[n].locators = "Douwesen_locators";
		Islands[n].visible = true;
		Islands[n].smuggling_nation = HOLLAND;

		Islands[n].reload.l1.label = "Порт Дувезен";
		Islands[n].reload.l1.name = "reload_1";
		Islands[n].reload.l1.go = "Douwesen_port";
		Islands[n].reload.l1.emerge = "reload2";
		Islands[n].reload.l1.radius = 200.0;
		Islands[n].reload.l1.pic = 0;
		Islands[n].reload.l1.tex = "t1";

		Islands[n].reload.l2.label = "Пальмовый берег";
		Islands[n].reload.l2.name = "reload_2";
		Islands[n].reload.l2.go = "Douwesen_shore_01";
		Islands[n].reload.l2.emerge = "reload1";
		Islands[n].reload.l2.radius = 200.0;
		Islands[n].reload.l2.pic = 2;
		Islands[n].reload.l2.tex = "t1";

		Islands[n].reload.l3.label = "Крабовый утес";
		Islands[n].reload.l3.name = "reload_3";
		Islands[n].reload.l3.go = "Douwesen_shore_02";
		Islands[n].reload.l3.emerge = "reload1";
		Islands[n].reload.l3.radius = 200.0;
		Islands[n].reload.l3.pic = 3;
		Islands[n].reload.l3.tex = "t1";

		Islands[n].reload.l4.label = "Форт Дувезен";
		Islands[n].reload.l4.name = "reload_fort1";
		Islands[n].reload.l4.go = "Douwesen_fort";
		Islands[n].reload.l4.GoAfterBoard.location = "reload_1";
		Islands[n].reload.l4.emerge = "see";
		Islands[n].reload.l4.radius = 250.0;
		Islands[n].reload.l4.fortname = "fort_Douwesen";
		Islands[n].reload.l4.fort.model = "Douwesen_fort1";
		Islands[n].reload.l4.fort.locators = "Douwesen_fort1_locators";
		Islands[n].reload.l4.pic = 1;
		Islands[n].reload.l4.tex = "t1";

		Islands[n].InterfaceTextures.t1 = "battle_interface\moor_3.tga";
		Islands[n].InterfaceTextures.t1.h = 4;
		Islands[n].InterfaceTextures.t1.v = 1;

		Islands[n].Trade.Export.id1 = GOOD_TOBACCO;
		Islands[n].Trade.Export.id2 = GOOD_COFFEE;
		Islands[n].Trade.Export.id3 = GOOD_COPRA;
		Islands[n].Trade.Export.id4 = GOOD_ALE;
		Islands[n].Trade.Import.id1 = GOOD_PLANKS;
		Islands[n].Trade.Import.id2 = GOOD_SAILCLOTH;
		Islands[n].Trade.Import.id3 = GOOD_WHEAT;
		Islands[n].Trade.Import.id4 = GOOD_WINE;
		Islands[n].Trade.Contraband.id1 = GOOD_SUGAR;
		Islands[n].Trade.Contraband.id2 = GOOD_LINEN;
		Islands[n].Trade.Contraband.id3 = GOOD_RUM;
        //        Islands[n].Trade.Contraband.id4 = GOOD_SLAVES;

		SendMessage(&locator,"le",LM_LOCATE_I,&Islands[n]);

	// ==================================================================================================
	// Quebradas
		n = n + 1;
		Islands[n].id = "QuebradasCostillas";
		Islands[n].model = "QuebradasCostillas";
		Islands[n].filespath.models = "islands\QuebradasCostillas";
		Islands[n].refl_model = "QuebradasCostillas_refl";
		Islands[n].locators = "QuebradasCostillas_locators";
		Islands[n].visible = false;
		Islands[n].smuggling_nation = PIRATE;

		Islands[n].reload.l1.label = "Порт Квебрадас Костиллас";
		Islands[n].reload.l1.name = "reload_1";
		Islands[n].reload.l1.go = "QC_port";
		Islands[n].reload.l1.emerge = "reload1";
		Islands[n].reload.l1.radius = 200.0;
		Islands[n].reload.l1.pic = 0;
		Islands[n].reload.l1.tex = "t1";

		Islands[n].InterfaceTextures.t1 = "battle_interface\moor_6.tga";
		Islands[n].InterfaceTextures.t1.h = 1;
		Islands[n].InterfaceTextures.t1.v = 1;

		SendMessage(&locator,"le",LM_LOCATE_I,&Islands[n]);

	// ==================================================================================================
	// Khael Roa
		n = n + 1;
		Islands[n].id = "KhaelRoa";
		Islands[n].model = "KhaelRoa";
		Islands[n].filespath.models = "islands\KhaelRoa";
		Islands[n].refl_model = "KhaelRoa_refl";
		Islands[n].locators = "KhaelRoa_locators";
		Islands[n].visible = false;
		Islands[n].Enc_enable = false;
		Islands[n].smuggling_nation = PIRATE;

		Islands[n].reload.l1.label = "Берег Каель Роа";
		Islands[n].reload.l1.name = "reload_1";
		Islands[n].reload.l1.go = "KhaelRoa_port";
		Islands[n].reload.l1.emerge = "Reload2";
		Islands[n].reload.l1.radius = 200.0;
		Islands[n].reload.l1.enable = false;
		Islands[n].reload.l1.goto_enable = false;
		Islands[n].reload.l1.pic = 0;
		Islands[n].reload.l1.tex = "t1";

		Islands[n].InterfaceTextures.t1 = "battle_interface\moor_5.tga";
		Islands[n].InterfaceTextures.t1.h = 1;
		Islands[n].InterfaceTextures.t1.v = 1;

		SendMessage(&locator,"le",LM_LOCATE_I,&Islands[n]);


	// ==================================================================================================
	// delete temp module
		DeleteClass(&locator);
}

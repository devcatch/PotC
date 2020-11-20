// BOAL 09.09.03 Каюта капитана
bool	bCabinStarted = false;
string	sCabinLocator;


void Cabin_ReloadStartFade()
{
	int a = GetEventData();
	aref reload_fader = GetEventData();
	LayerFreeze(SEA_EXECUTE,true);
	LayerFreeze(SEA_REALIZE,true);
	LayerFreeze("sea_reflection",true);
	LayerFreeze("execute",false);
	LayerFreeze("realize",false);

	MoveWeatherToLayers("execute", "realize");
	MoveSeaToLayers("execute", "realize");

	SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);

	DelEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFade");

	fOldMaxSeaHeight = stf(Sea.MaxSeaHeight);
	Sea.MaxSeaHeight = 1.2;						// set maxinum sea height for ship Cabin
}

void Return2SeaAfterCabin()
{
	//Установить хендлеры для обработки
	SetEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFadeAfter", 0);
	SetEventHandler("FaderEvent_EndFade", "Cabin_ReloadEndFadeAfter", 0);
	//Создаём фейдер и запускаем
	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "ls", FADER_PICTURE, "loading\sea.tga");
	
	float fadeOutTime = RELOAD_TIME_FADE_OUT;
	
	SendMessage(&boarding_fader, "lfl", FADER_OUT, fadeOutTime, false);
	SendMessage(&boarding_fader, "l", FADER_STARTFRAME);
}

void Cabin_ReloadEndFade()
{
	// Delete current cannonballs
	AIBalls.Clear = "";

	// unload all models
	aref arModel;
	if (FindClass(&arModel, "modelr")) 
	{
		SendMessage(arModel, "l", MSG_MODEL_RELEASE);
		while (FindClassNext(&arModel)) { SendMessage(arModel, "l", MSG_MODEL_RELEASE); }
	}

	PauseParticles(true);

	// start Cabin location
	int a = GetEventData();
	aref reload_fader = GetEventData();
	
	Cabin_Start();
	
	DelEventHandler("FaderEvent_EndFade", "Cabin_ReloadEndFade");
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}

void Sea_CabinStartNow()
{
	if (!bAbordageStarted)
	{
    bSeaReloadStarted = true;

	object reload_fader;
	CreateEntity(&reload_fader, "fader");
	SetEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "Cabin_ReloadEndFade", 0);

	SendMessage(&reload_fader, "ls", FADER_PICTURE, "loading\Cabin.tga");
	SendMessage(&reload_fader, "lfl", FADER_OUT, 1.0, false);
	SendMessage(&reload_fader, "l", FADER_STARTFRAME);

	PauseAllSounds();
	ResetSoundScheme();

	bAbordageStarted = true;
	bCabinStarted = true;
	Sea.AbordageMode = true;
	}
	else
	{
	   Return2SeaAfterCabin();
	}
}

//////////////
int cabin_officers;
void Cabin_Start()
{
	ResetSoundScheme();
	PauseAllSounds();
	int i;
	//Настроим интерфейс
	DeleteBattleInterface();
	StartBattleLandInterface();
	
	ref mchr = GetMainCharacter();
	
	string deckID = "";
	deckID = "Tutorial_deck";
	
	int locID = -1;
	locID = FindLocation(deckID);
	if(locID < 0)
	{
		Trace("Boarding: ship location not found <" + deckID + ">, set default");
	    deckID = "";
	    return;
	}
	//Выставим  и запомним адреса
	boarding_adr[0].location = mchr.location;
	boarding_adr[0].group = mchr.location.group;
	boarding_adr[0].locator = mchr.location.locator;
	for(i = 1; i < 4; i++)
	{
		int idx = GetOfficersIndex(GetMainCharacter(), i);
		if(idx < 0)
		{
			boarding_adr[i].location = "";
			boarding_adr[i].group = "";
			boarding_adr[i].locator = "";
			continue;
		}
		boarding_adr[i].location = Characters[idx].location;
		boarding_adr[i].group = Characters[idx].location.group;
		boarding_adr[i].locator = Characters[idx].location.locator;
	}
	//Стартуем
	LAi_boarding_process = false;
	Cabin_LoadLocation(deckID);
	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}

//Загрузить локацию абордажа
void Cabin_LoadLocation(string locationID)
{
	ReloadProgressStart();
	//Ищем локацию
	int locIndex = FindLocation(locationID);
	Log_SetActiveAction("Nothing");
	if(locIndex >= 0)
	{
		//Устанавливаем главного персонажа
		ref mchr = GetMainCharacter();
		mchr.location = locationID;
		mchr.location.group = "reload";
		mchr.location.locator = "reload1";
		//Устанавливаем офицеров, если такие есть
		for(int i = 1; i < 4; i++)
		{
			int idx = GetOfficersIndex(GetMainCharacter(), i);
			if(idx < 0) continue;
			DeleteAttribute(&Characters[idx], "location");
			Characters[idx].location = locationID;
			Characters[idx].location.group = "goto";
			Characters[idx].location.locator = "goto2";
		}
		//Перегружаемся в локацию
		boarding_location = locIndex;
		Locations[locIndex].boarding = "true";
		if(LoadLocation(&Locations[locIndex]))
		{
			//Расставляем персонажей
			//SetEventHandler(EVENT_LOCATION_LOAD,"qprocEndReload",0);
			//Запретим диалог
			dialogDisable = false;
		}else{
			Trace("Boarding: Boarding location not loaded, current loc <" + locationID + ">");
		}
	}else{
		Trace("Boarding: Boarding location not found, current loc <" + locationID + ">");
	}
	ReloadProgressEnd();
	PostEvent("LoadSceneSound", 500);
}

/////////////
void Cabin_ReloadStartFadeAfter()
{
	//Выгружаем локацию
	ResetSoundScheme();
	PauseAllSounds();
	DelEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFadeAfter");
	if(boarding_location >= 0) UnloadLocation(&Locations[boarding_location]);
}

void Cabin_ReloadEndFadeAfter()
{
	//Загружаем следующую локацию
	DelEventHandler("FaderEvent_EndFade", "Cabin_ReloadEndFadeAfter");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
	//Определим возможность продолжения перегрузок
		//Следующей локации нет
		//DelEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill");
		boarding_location = -1;
		//Настроим интерфейс
		Log_SetActiveAction("Nothing");
		EndBattleLandInterface();
		//Востановим адреса
		ref mchr = GetMainCharacter();
		mchr.location = boarding_adr[0].location;
		mchr.location.group = boarding_adr[0].group;
		mchr.location.locator = boarding_adr[0].locator;
		for(int i = 1; i < 4; i++)
		{
			int idx = GetOfficersIndex(GetMainCharacter(), i);
			if(idx < 0) continue;
			Characters[idx].location = boarding_adr[i].location;
			Characters[idx].location.group = boarding_adr[i].group;
			Characters[idx].location.locator = boarding_adr[i].locator;
		}
		//Выгружаемся в интерфейс		
		LAi_boarding_process = false;
/////////////////////////////////////////////////////////////////////
    // load all models back to sea
	aref arModel;
	if (FindClass(&arModel, "modelr"))
	{
		SendMessage(arModel, "l", MSG_MODEL_RESTORE);
		while (FindClassNext(&arModel))
		{
			//Trace("XYZ");
			SendMessage(arModel, "l", MSG_MODEL_RESTORE);
		}
	}

	LayerFreeze("execute",true);
	LayerFreeze("realize",true);

	LayerFreeze("sea_reflection", false);
	LayerFreeze(SEA_EXECUTE,false);
	LayerFreeze(SEA_REALIZE,false);

	MoveWeatherToLayers(SEA_EXECUTE, SEA_REALIZE);
	MoveSeaToLayers(SEA_EXECUTE, SEA_REALIZE);

	Sea.MaxSeaHeight = fOldMaxSeaHeight;		// restore old MaxSeaHeight
	bAbordageStarted = false;
	bCabinStarted = false;
	Sea.AbordageMode = false;

	InitBattleInterface();
	StartBattleInterface();
	RefreshBattleInterface();

	SetSchemeForSea();

	PauseParticles(false);

	bSeaReloadStarted = false;
}

//Таблица слухов, и их состояние. "active" - слух включен в поле случаного выбора слуха, "passive" - слух исключен из поля
#define MAX_RUMOURS 7
object	Rumour[MAX_RUMOURS];


void SetRumourDefaults()
{
	Rumour[0].text = "Nothing interesting happens lately. Life goes smooth. I wonder, how long it will go like this!";
	Rumour[0].state = "active";

	Rumour[1].text = "People says that some kind of aboriginal cemetery was found inside Oxbay mine. A lot of bones, crockery, spikes and clay plates were found but not a grain of gold!";
	Rumour[1].state = "active";

	Rumour[2].text = "I heard that Redmond Governor ordered once to seize some merchant and put him in a jail for small tavern fight. But actually he ordered that just becase he wanted to grab that merchant's goods."; 
	Rumour[2].state = "active";

	Rumour[3].text = "I heard that Redmond Governor ordered once to seize some merchant and put him in a jail for small tavern fight. But actually he ordered that just becase he wanted to grab that merchant's goods."; 
	Rumour[3].state = "active";

	Rumour[4].text = "I heard that Redmond Governor ordered once to seize some merchant and put him in a jail for small tavern fight. But actually he ordered that just becase he wanted to grab that merchant's goods."; 
	Rumour[4].state = "active";

	Rumour[5].text = "I heard that Redmond Governor ordered once to seize some merchant and put him in a jail for small tavern fight. But actually he ordered that just becase he wanted to grab that merchant's goods."; 
	Rumour[5].state = "active";

	Rumour[6].text = "I heard that Redmond Governor ordered once to seize some merchant and put him in a jail for small tavern fight. But actually he ordered that just becase he wanted to grab that merchant's goods."; 
	Rumour[6].state = "active";

}

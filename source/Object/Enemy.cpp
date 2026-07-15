#include<DxLib.h>
#include"Circle.h"
#include"Enemy.h"

ENEMY stage_enemy[ENEMYCOUNT];//{‰ŠúxÀ•W,‰ŠúyÀ•W,“®‚©‚µ•û‚Ìí—Ş,‘å‚«‚³,•\‰æ–Ê‚Æ— ‰æ–Ê‚Ç‚¿‚ç‚Å•\¦‚³‚¹‚é‚©}

HIT stage_circle[ENEMYCOUNT];//©‹@‚ÌˆÊ’u

int stage_mode;//‰æ–Ê•\¦

void EnemyInit(void)//“G‚ÌˆÊ’u‚Ì‰Šú‰»
{
	for (int x = 0; x < ENEMYCOUNT; x++)
	{
		switch (x)
		{
		case 0:
			stage_enemy[x] = { 215.0f,660.0f,TRUE,15,NULL };//‰º‘¤‚Å‚ä‚Á‚­‚è¶‰E‚µ‚Ä‚¢‚é“G
			break;
		case 1:
			stage_enemy[x] = { 300.0f,315.0f,TRUE,15,NULL };//¶‘¤‚Å‚ä‚Á‚­‚èã‰º‚µ‚Ä‚¢‚é“G
			break;
		case 2:
			stage_enemy[x] = { 1200.0f,705.0f,TRUE,15,NULL };//‰E‘¤‚Å‘f‘‚­ã‰º‚µ‚Ä‚¢‚é“G
			break;
		case 3:
			stage_enemy[x] = { 300.0f,40.0f,NULL,15,TRUE };//Å‰‚Ì“G
			break;
		case 4:
			stage_enemy[x] = { 915.0f,330.0f,FALSE,5,NULL };//1ƒ}ƒX‚Ì“Ê‰š‚Å¶‰E‚É“®‚¢‚Ä‚¢‚é¬‚³‚¢“G
			break;
		case 5:
			stage_enemy[x] = { 525.0f,70.0f,TRUE,3,NULL };//ƒS[ƒ‹‘O‚Ì‘f‘‚­¶‰E‚µ‚Ä‚¢‚é“G
		}
	}
	stage_mode = TRUE;//‰æ–Êó‘Ô‚Ì‰Šú‰»
}

void EnemyUpdate(float delta_second)//“G‚Ì“®ì
{
	if (stage_enemy[0].move == TRUE)
	{
		stage_enemy[0].ex += 65.0f * delta_second;
		if (stage_enemy[0].ex >= 665.0f)
		{
			stage_enemy[0].ex = 665.0f;
			stage_enemy[0].move = FALSE;
		}
	}
	if (stage_enemy[0].move == FALSE)
	{
		stage_enemy[0].ex += -65.0f * delta_second;
		if (stage_enemy[0].ex <= 215.0f)
		{
			stage_enemy[0].ex = 215.0f;
			stage_enemy[0].move = TRUE;
		}
	}

	if (stage_enemy[1].move == TRUE)
	{
		stage_enemy[1].ey += 40.0f * delta_second;
		if (stage_enemy[1].ey >= 405.0f)
		{
			stage_enemy[1].ey = 405.0f;
			stage_enemy[1].move = FALSE;
		}
	}
	if (stage_enemy[1].move == FALSE)
	{
		stage_enemy[1].ey += -40.0f * delta_second;
		if (stage_enemy[1].ey <= 315.0f)
		{
			stage_enemy[1].ey = 315.0f;
			stage_enemy[1].move = TRUE;
		}
	}

	if (stage_enemy[2].move == TRUE)
	{
		stage_enemy[2].ey += -90.0f * delta_second;
		if (stage_enemy[2].ey <= 235.0f)
		{
			stage_enemy[2].ey = 235.0f;
			stage_enemy[2].move = FALSE;
		}
	}
	if (stage_enemy[2].move == FALSE)
	{
		stage_enemy[2].ey += 90.0f * delta_second;
		if (stage_enemy[2].ey >= 705.0f)
		{
			stage_enemy[2].ey = 705.0f;
			stage_enemy[2].move = TRUE;
		}
	}

	if (stage_enemy[4].move == TRUE)
	{
		stage_enemy[4].ex += -45.0f * delta_second;
		if (stage_enemy[4].ex <= 745.0f)
		{
			stage_enemy[4].ex = 745.0f;
			stage_enemy[4].move = FALSE;
		}
	}
	if (stage_enemy[4].move == FALSE)
	{
		stage_enemy[4].ex += 45.0f * delta_second;
		if (stage_enemy[4].ex >= 915.0f)
		{
			stage_enemy[4].ex = 915.0f;
			stage_enemy[4].move = TRUE;
		}
	}

	if (stage_enemy[5].move == TRUE)
	{
		stage_enemy[5].ex += 210.0f * delta_second;
		if (stage_enemy[5].ex >= 1280.0f)
		{
			stage_enemy[5].ex = 1280.0f;
			stage_enemy[5].move = FALSE;
		}
	}
	if (stage_enemy[5].move == FALSE)
	{
		stage_enemy[5].ex += -210.0f * delta_second;
		if (stage_enemy[5].ex <= 525.0f)
		{
			stage_enemy[5].ex = 525.0f;
			stage_enemy[5].move = TRUE;
		}
	}
}

void EnemyDraw(void)//“G‚Ì•`‰æ
{
	for (int x = 0; x < ENEMYCOUNT; x++)
	{
		if (stage_enemy[x].mode == stage_mode || stage_enemy[x].mode == NULL)
		{
			DrawCircle(stage_enemy[x].ex, stage_enemy[x].ey, stage_enemy[x].size, GetColor(255, 0, 0), TRUE);
		}

	}
}

int HitCheckEnemy1(void)//©‹@‚Æ‚ÌÕ“Ëƒ`ƒFƒbƒN
{
	Circle circle = ReturnCircle();

	for (int x = 0; x < ENEMYCOUNT; x++)
	{
		if (stage_enemy[x].mode == stage_mode || stage_enemy[x].mode == NULL)
		{
			stage_circle[x].hx = (float)circle.x - stage_enemy[x].ex;
			stage_circle[x].hy = (float)circle.y - stage_enemy[x].ey;

			if (stage_circle[x].hx >= -17 && stage_circle[x].hx <= 17)
			{
				if (stage_circle[x].hy >= -17 && stage_circle[x].hy <= 17)
				{
					return TRUE;
				}
			}
		}

	}
	return FALSE;
}

void ChangeEnemy(int x)
{
	stage_mode = x;//“G‚Ì•`‰æØ‚è‘Ö‚¦
}
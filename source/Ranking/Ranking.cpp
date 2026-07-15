#include<dxlib.h>
#include"Ranking.h"

RankData ranking[MAX_RANK];
int color_w;
int color_b;

int LoadRankData()
{
	FILE* fp = NULL;
	errno_t result = fopen_s(&fp, "assets/dat/rankingdata.txt", "r");

	//ファイルを開く
	if (result != NULL)
	{
		return FALSE;//開かなければ失敗
	}

	for (int i = 0; i < MAX_RANK; i++)
	{
		fscanf_s(fp, "%2d %3d", &ranking[i].num, &ranking[i].time);
	}

	fclose(fp);
	return TRUE;
}

int CheckRankData(int time)
{
	if (time < ranking[4].time)
	{
		ranking[4].time = time;

		if (SortRankData() != TRUE)
		{
			return FALSE;
		}
	}

	return TRUE;
}

int SortRankData()
{
	int swap_time = {};

	for (int i = 0; i < MAX_RANK; i++)
	{
		ranking[i].num = i + 1;
	}

	for (int i = 0; i < MAX_RANK - 1; i++)
	{
		for (int j = i + 1; j < MAX_RANK; j++)
		{
			if (ranking[j].time == ranking[i].time)
			{
				swap_time = ranking[i + 1].time;
				ranking[i + 1].time = ranking[j].time;
				ranking[j].time = swap_time;

			}
			if (ranking[j].time < ranking[i].time)
			{
				swap_time = ranking[i].time;
				ranking[i].time = ranking[j].time;
				ranking[j].time = swap_time;

			}
		}
	}

	if (AddRankData() != TRUE)
	{
		return FALSE;
	}

	return TRUE;
}

int AddRankData()
{
	FILE* fp = NULL;
	errno_t result = fopen_s(&fp, "assets/dat/rankingdata.txt", "w");

	//ファイルを開く
	if (result != NULL)
	{
		return FALSE;//開かなければ失敗
	}

	for (int i = 0; i < MAX_RANK; i++)
	{
		fprintf_s(fp, "%2d %3d\n", ranking[i].num, ranking[i].time);
	}

	fclose(fp);

	return TRUE;
}

void ColorRankW(int color)
{
	color_w = color;
}
void ColorRankB(int color)
{
	color_b = color;
}

void DrawRankData()
{
	SetFontSize(65);
	DrawFormatString(900, 290, color_w, "%d位  %d秒", ranking[0].num, ranking[0].time);
	for (int i = 1; i < MAX_RANK; i++)
	{
		SetFontSize(40);
		DrawFormatString(950, 350 + i * 50, color_b, "%d位   %d秒", ranking[i].num, ranking[i].time);
	}

}
#pragma once
#define MAX_RANK (5)
#define MAX_NAME (10)

struct RankData
{
	int time;
	int num;
};

int LoadRankData();
int CheckRankData(int time);
int SortRankData();
int AddRankData();
void DrawRankData();
void ColorRankW(int color);
void ColorRankB(int color);

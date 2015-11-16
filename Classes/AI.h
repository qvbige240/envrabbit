#ifndef __AI_H__
#define __AI_H__
int *  getDistance(int r, int c, int *dir, bool (*active_blocks)[9], bool (*passed)[9], int cost, int len);
int *  getDistance1(int r, int c, int *dir, bool (*active_blocks)[9], bool (*passed)[9], int cost, int len);
#endif
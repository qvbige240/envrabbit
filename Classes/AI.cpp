#include "AI.h"
#include "cocos2d.h"
#include "config.h"
USING_NS_CC;
int ROW_MINUS_1 = ROW - 1, COL_MINUS_1 = COL - 1;


int *  getDistance(int r, int c, int *dir, bool (*active_blocks)[9], bool (*passed)[9], int cost, int len)
{
	int dir_choices[2][3][2] = {0};

	for(int i = 0; i < 2; i++) {
		//CCLog("{");
		for(int j = 0; j < len; j++){
			//CCLog("[");
			for(int k = 0; k < 2; k++){
				//CCLog("%d--->     %d, ", i *2 + j * len + k, *(dir_choices + i * len * 2 + j * 2 + k));
				dir_choices[i][j][k] = *(dir + i * len * 2 + j * 2 + k);
			}
			//CCLog("]");
		}
		//CCLog("}");

	}

	passed[r][c] = true;
	if (r <= 0 || r >= ROW_MINUS_1 || c <= 0 || c >= COL_MINUS_1) {
		int temp[3];
		temp[0] = r;
		temp[1] = c;
		temp[2] = cost;

CCLog("&&tmp:%d, %d, %d", temp[0], temp[1], temp[2]);
		return temp;
	}

	int odd = (r % 2 == 1) ? 1 : 0;
	//var choices = dir_choices[odd];

	int choices[3][2];
	for(int i =0; i< 3; i ++){
		for(int j = 0; j < 2; j++){
			choices[i][j] = dir_choices[odd][i][j];
		}
	}
	
	int nextr, nextc, result[3] = {-1, -1, -1};
	int *pResult = result;
	for (int i = 0, l = len; i < l; i++) {
		nextr = r + choices[i][0];
		nextc = c + choices[i][1];

		if (!active_blocks[nextr][nextc] && !passed[nextr][nextc]) {
			cost ++;
			pResult = getDistance(nextr, nextc, (int *)dir_choices, active_blocks, passed, cost, len);
			if (pResult != NULL) {
				//result[0] = pResult[0];
				//result[1] = pResult[1];
				result[2] = pResult[2];

				
				result[0] = nextr;
				result[1] = nextc;
CCLog("&&result:%d, %d, %d", result[0], result[1], result[2]);
				return result;
			}
		}
	}
	return NULL;
}

int *  getDistance1(int r, int c, int *dir, bool (*active_blocks)[9], bool (*passed)[9], int cost, int len)
{

	int dir_choices[2][2][2] = {0};

	for(int i = 0; i < 2; i++) {
		//CCLog("{");
		for(int j = 0; j < len; j++){
			//CCLog("[");
			for(int k = 0; k < 2; k++){
				//CCLog("%d--->     %d, ", i *2 + j * len + k, *(dir_choices + i * len * 2 + j * 2 + k));
				dir_choices[i][j][k] = *(dir + i * len * 2 + j * 2 + k);
			}
			//CCLog("]");
		}
		//CCLog("}");

	}

	passed[r][c] = true;
	if (r <= 0 || r >= ROW_MINUS_1 || c <= 0 || c >= COL_MINUS_1) {
	    int temp[3];
		temp[0] = r;
		temp[1] = c;
		temp[2] = cost;
CCLog("&&tmp:%d, %d, %d", temp[0], temp[1], temp[2]);

		return temp;
	}

	int odd = (r % 2 == 1) ? 1 : 0;
	//var choices = dir_choices[odd];

	int choices[2][2];
	for(int i =0; i< 2; i ++){
		for(int j = 0; j < 2; j++){
			choices[i][j] = dir_choices[odd][i][j];
		}
	}


	int nextr, nextc, result[3] = {-1, -1, -1};
	int *pResult = result;
	for (int i = 0, l = len; i < l; i++) {
		nextr = r + choices[i][0];
		nextc = c + choices[i][1];

		if (!active_blocks[nextr][nextc] && !passed[nextr][nextc]) {
			cost ++;
			pResult = getDistance1(nextr, nextc, (int *)dir_choices, active_blocks, passed, cost, len);
			if (pResult != NULL) {

				//result[0] = pResult[0];
				//result[1] = pResult[1];
				result[2] = pResult[2];

				result[0] = nextr;
				result[1] = nextc;
CCLog("&&result:%d, %d, %d", result[0], result[1], result[2]);
				return result;
			}
		}
	}
	return NULL;
}

#include <stdio.h>
#include <string.h>

int num1[10000001];
int num2[10000001];
int res[10000001];

void GetDiffIsMaxNum1(int len1) {
    for(int i = 0; i < len1; ++i) {
        if(num1[i] < num2[i]) {
            for(int j = i; j >= 0; --j) {
                if(0 < res[j]) {
                    res[j] -= 1;
                    for(int l = j+1; l < i; ++l) {
                        res[l] = 9;
                    }
                    break;
                }
            }
            num1[i] += 10;
        }
        res[i] = num1[i] - num2[i];
    }
}

void GetDiffIsMaxNum2(int len2) {
    for(int i = 0; i < len2; ++i) {
        if(num2[i] < num1[i]) {
            for(int j = i; j >= 0; --j) {
                if(0 < res[j]) {
                    res[j] -= 1;
                    for(int l = j+1; l < i; ++l) {
                        res[l] = 9;
                    }
                    break;
                }
            }
            num2[i] += 10;
        }
        res[i] = num2[i] - num1[i];
    }
}

int GetDiffernce(int len1, int len2, int max) {
    int flag = 0;
    if(len2 < len1) {
        GetDiffIsMaxNum1(len1);
    } else if(len1 < len2) {
        GetDiffIsMaxNum2(len2);
    } else {
        for(int i = 0; i < len1; ++i) {
            if(num2[i] < num1[i]) {
                GetDiffIsMaxNum1(len1);
                flag = 1;
                break;
            } else if(num1[i] < num2[i]) {
                GetDiffIsMaxNum2(len2);
                flag = 1;
                break;
            }
        }
        // 두 수가 완전히 같은경우
        if(flag == 0) {
            return 0;
        }
    }
    return 1;
}
//3409850934850 - 2382340982345 = 1027509952505
//1000000010045 - 1000000009882 = 163
/*
   23579823758927359872398
  -23049875093128409280923
     529948665798950591475
 */
int Padding(int len1, int len2) {
    if(len2 < len1) {
        for(int i = len2; i >= 0; --i) {
            num2[i + (len1-len2)] = num2[i];
            num2[i] = 0;
        }
        return len1;
    } else if(len1 < len2) {
        for(int i = len1; i >= 0; --i) {
            num1[i + (len2-len1)] = num1[i];
            num1[i] = 0;
        }
        return len2;
    }
    return len1;
}

int main() {

    int len1;
    int len2;
    int max;
    int flag;

    char str1[1000001];
    char str2[1000001];

    scanf("%s %s", str1, str2);

    len1 = strlen(str1);
    len2 = strlen(str2);

    for(int i = 0; i < len1; ++i) {
        num1[i] = str1[i] - 48;
    }
    for(int i = 0; i < len2; ++i) {
        num2[i] = str2[i] - 48;
    }
    max = Padding(len1, len2);
    flag = GetDiffernce(len1, len2, max);

    if(flag) {
        for (int i = 0; i < max; ++i) {
            printf("%d", res[i]);
        }
    } else {
        printf("0");
    }

    return 0;
}
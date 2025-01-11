#include "IA.h"
#include "../constante.h"

static int testScore(int score, int maxScore) {
    if (score == 3) {  
        score = 100;
    }
    if (score > maxScore) {
        maxScore = score;
    } else if (score == maxScore) {
        maxScore += score;
    }
    score = 0;
    return maxScore;
}

int f_score(int (*grille)[LEN_GRILLE] , const int ID, Coor * dpt, Coor * arv) {
    int score = 0;
    int MaxScore = 0;
    int JoueurAdverse = ID*-1;

    // Tester les lignes
    for (unsigned int i = 0; i < 3; i++) {
        for (unsigned int j = 0; j < 3; j++) {
            if (ID == grille[i][j]) {
                score++;
            } else if (JoueurAdverse == grille[i][j]) {
                score =-10;
            }
        }
        MaxScore = testScore(score, MaxScore);
        if (score >= 3 && dpt != NULL && arv != NULL) {
            dpt->x = 0;
            dpt->y = (int)i;
            arv->x = 2;
            arv->y = (int)i;
            //return MaxScore;
        }
        score = 0;
    }   
    
    // Tester les colones
    for (unsigned int i = 0; i < 3; i++) {
        for (unsigned int j = 0; j < 3; j++) {
            if (ID == grille[j][i]) {
                score++;
            } else if (JoueurAdverse == grille[j][i]) {
                score =-10;
            }
        }
        MaxScore = testScore(score, MaxScore);
        if (score >= 3 && dpt != NULL && arv != NULL) {
            dpt->x = (int)i;
            dpt->y = 0;
            arv->x = (int)i;
            arv->y = 2;
            //return MaxScore;
        }
        score = 0;
    }   
    
    // tester la diago 1 (L-> R)
    for (unsigned int i = 0; i < 3; i++) {
        if (ID == grille[i][i]) {
            score++;
        } else if (JoueurAdverse == grille[i][i]) {
            score =-10;
        }
    }
    MaxScore = testScore(score, MaxScore);
    if (score >= 3 && dpt != NULL && arv != NULL) {
        dpt->x = 0;
        dpt->y = 0;
        arv->x = 2;
        arv->y = 2;
        //return MaxScore;
    }
    score = 0;
    
    // tester la diago 2 (R-> L)
    unsigned int i = 0;
    for (unsigned int j = 3; j > 0; j--) {
        if (ID == grille[i][j-1]) {
            score++;
        } else if (JoueurAdverse == grille[i][j-1]) {
            score =-10;
        }
        i++;
    }
    MaxScore = testScore(score, MaxScore);
    if (score >= 3 && dpt != NULL && arv != NULL) {
            dpt->x = 2;
            dpt->y = 0;
            arv->x = 0;
            arv->y = 2;
            //return MaxScore;
        }
    score = 0;
    
    return MaxScore;  
}    
#include "IA.h"
#include "../constante.h"

int_fast32_t testScore(int_fast32_t score, int_fast32_t maxScore) {
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

int_fast32_t f_score(int_fast8_t (*grille)[LEN_GRILLE] , const char ID, Coor * dpt, Coor * arv) {
    int_fast32_t score = 0;
    int_fast32_t MaxScore = 0;
    char JoueurAdverse = ID*-1;

    // Tester les lignes
    for (int_fast32_t i = 0; i < 3; i++) {
        for (int_fast32_t j = 0; j < 3; j++) {
            if (ID == grille[i][j]) {
                score++;
            } else if (JoueurAdverse == grille[i][j]) {
                score =-10;
            }
        }
        MaxScore = testScore(score, MaxScore);
        if (score >= 3 && dpt != ((void*)0) && arv != ((void*)0)) {
            dpt->x = 0;
            dpt->y = i;
            arv->x = 2;
            arv->y = i;
            //return MaxScore;
        }
        score = 0;
    }   
    
    // Tester les colones
    for (int_fast32_t i = 0; i < 3; i++) {
        for (int_fast32_t j = 0; j < 3; j++) {
            if (ID == grille[j][i]) {
                score++;
            } else if (JoueurAdverse == grille[j][i]) {
                score =-10;
            }
        }
        MaxScore = testScore(score, MaxScore);
        if (score >= 3 && dpt != ((void*)0) && arv != ((void*)0)) {
            dpt->x = i;
            dpt->y = 0;
            arv->x = i;
            arv->y = 2;
            //return MaxScore;
        }
        score = 0;
    }   
    
    // tester la diago 1 (L-> R)
    for (int_fast32_t i = 0; i < 3; i++) {
        if (ID == grille[i][i]) {
            score++;
        } else if (JoueurAdverse == grille[i][i]) {
            score =-10;
        }
    }
    MaxScore = testScore(score, MaxScore);
    if (score >= 3 && dpt != ((void*)0) && arv != ((void*)0)) {
        dpt->x = 0;
        dpt->y = 0;
        arv->x = 2;
        arv->y = 2;
        //return MaxScore;
    }
    score = 0;
    
    // tester la diago 2 (R-> L)
    int_fast32_t i = 0;
    for (int_fast32_t j = 2; j > -1; j--) {
        if (ID == grille[i][j]) {
            score++;
        } else if (JoueurAdverse == grille[i][j]) {
            score =-10;
        }
        i += 1;
    }
    MaxScore = testScore(score, MaxScore);
    if (score >= 3 && dpt != ((void*)0) && arv != ((void*)0)) {
            dpt->x = 2;
            dpt->y = 0;
            arv->x = 0;
            arv->y = 2;
            //return MaxScore;
        }
    score = 0;
    
    return MaxScore;  
}    
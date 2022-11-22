/**
 *   @file Score.h
 *   @author Waine Jr. (waine@alunos.utfpr.edu.br)
 *   @brief Score from a gameplay representation
 *   @version 0.1.0
 *   @date 21/11/2022
 *
 *   @copyright Copyright (c) 2022
 *
 */

#ifndef _MODELS_SCORE_H_
#define _MODELS_SCORE_H_
namespace models {
class Score {
public:
    float curr_score;
    float multiplier;

    Score();
};
}
#endif
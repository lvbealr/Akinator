#ifndef PHRASES_H_
#define PHRASES_H_

#include "akinator.h"
#include "colorPrint.h"

static const char *phrases[] = {"КОНТРЛ ПЛЮС ДВА РАЗА!", "СИ ПЛЮС ПЛЮС ИЛИ СЕКС?", "УУУ КОШАЧЬЯ ТВАРЬ ^//", "КОШАЧЬЯ МОРДА <3",
                         "У НАС С ТОБОЙ ТАК НИЧЕГО НЕ ПОЛУЧИТСЯ //", "НИЧЕГО НЕ СЛЫШУ :<", "МНЕ НАДО ВЫЙТИ НА 15 МИНУТ :)",
                         "ЧЕ МЫ ХАВАТЬ ТО ПОЙДЕМ?", "НАСТРАИВАЮ НЕЙРОСЕТКУ..."};

static const size_t phrasesArraySize = sizeof(phrases) / sizeof(phrases[0]);

inline akinatorError initializePhrases(Akinator *akinator, const char **phrasesArray) {
  customWarning(akinator != NULL, AKINATOR_BAD_POINTER);

  akinator->phrases = phrasesArray;

  return AKINATOR_NO_ERRORS;
};

inline akinatorError putPhrase(Akinator *akinator) {
  customWarning(akinator != NULL, AKINATOR_BAD_POINTER);

  customPrint(white, bold, bgDefault, "\n%s\n\n", phrases[rand() % phrasesArraySize]);

  return AKINATOR_NO_ERRORS;
}


#endif // PHRASES_H_
/**
 * @file messages.h
 * @brief Локализованные сообщения об ошибках
 */

#ifndef MESSAGES_H
#define MESSAGES_H

#include "errors.h"

/**
 * @enum Language
 * @brief Поддерживаемые языки для сообщений
 */
typedef enum { LANG_EN = 0, LANG_RU = 1, LANG_COUNT = 2 } Language;

/**
 * @struct ErrorMessage
 * @brief Структура для хранения сообщения об ошибке на разных языках
 */
typedef struct {
  const MatrixErrorCode errorCode;
  const char*			msgEn;
  const char*			msgRu;
} ErrorMessage;

#define DEFAULT_LANGUAGE LANG_EN

#endif
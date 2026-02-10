#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <cstddef>

using namespace std;

class IUtils {
public:
    static enum class CompareResult : uint8_t {
        Above,
        Equals,
        Less
    };

    /**
     * Разбивает строку на подстроки по указанному разделителю
     * @param str Исходная строка
     * @param separator Разделитель
     * @param skipEmpty Пропускать пустые подстроки (по умолчанию true)
     * @return Вектор подстрок
     */
    static std::vector<std::string> Split(std::string, char, bool);

    /**
     * Альтернативная версия с поддержкой строки-разделителя
     * @param str Исходная строка
     * @param separator Строка-разделитель
     * @param skipEmpty Пропускать пустые подстроки (по умолчанию true)
     * @return Вектор подстрок
     */
    static std::vector<std::string> Split(const std::string&, const std::string&, bool);

    /**
     * Вспомогательная функция для разбиения с удалением пробелов в начале и конце подстрок
     * @param str Исходная строка
     * @param separator Разделитель
     * @param trimSpaces Удалять пробелы в начале и конце подстрок
     * @param skipEmpty Пропускать пустые подстроки (по умолчанию true)
     * @return Вектор подстрок
     */
    static std::vector<std::string> SplitAndTrim(const std::string&, char, bool, bool);

    /**
      * Функция для сравнения двух версий между собой
      * @param ver1 Первая версия
      * @param ver2 Вторая версия
      * @return Результат сравнения
    */
    static CompareResult CompareVersion(string, string);
};
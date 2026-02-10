#include "IUtils.h"

vector<string> IUtils::Split(string str, char separator, bool skipEmpty = true)
{
    std::vector<std::string> result;

    // ≈сли строка пуста€, возвращаем пустой вектор
    if (str.empty()) {
        return result;
    }

    size_t start = 0;
    size_t end = 0;

    while (end != std::string::npos) {
        // »щем следующий разделитель
        end = str.find(separator, start);

        // »звлекаем подстроку от start до разделител€ (или до конца строки)
        std::string token;
        if (end == std::string::npos) {
            token = str.substr(start);
        }
        else {
            token = str.substr(start, end - start);
        }

        // ƒобавл€ем подстроку в результат, если она не пуста€ или skipEmpty = false
        if (!skipEmpty || !token.empty()) {
            result.push_back(std::move(token));
        }

        // ѕеремещаем start за найденный разделитель
        start = end + (end != std::string::npos ? 1 : 0);
    }

    // ќсобый случай: если последний символ - разделитель и skipEmpty = false,
    // нужно добавить пустую строку в конец
    if (!skipEmpty && !str.empty() && str.back() == separator) {
        result.push_back("");
    }

    return result;
}

vector<string> IUtils::Split(const std::string& str, const std::string& separator, bool skipEmpty = true)
{
    std::vector<std::string> result;

    if (str.empty() || separator.empty()) {
        if (!skipEmpty && !str.empty()) {
            result.push_back(str);
        }
        return result;
    }

    size_t start = 0;
    size_t end = 0;
    size_t sep_len = separator.length();

    while (end != std::string::npos) {
        end = str.find(separator, start);

        std::string token;
        if (end == std::string::npos) {
            token = str.substr(start);
        }
        else {
            token = str.substr(start, end - start);
        }

        if (!skipEmpty || !token.empty()) {
            result.push_back(std::move(token));
        }

        start = end + (end != std::string::npos ? sep_len : 0);
    }

    // ƒобавл€ем пустую строку в конце если нужно
    if (!skipEmpty && !str.empty() && str.length() >= sep_len &&
        str.compare(str.length() - sep_len, sep_len, separator) == 0) {
        result.push_back("");
    }

    return result;
}

vector<string> IUtils::SplitAndTrim(const string& str, char separator, bool skipEmpty = true, bool trimSpaces = true)
{
    auto result = Split(str, separator, skipEmpty);

    if (trimSpaces) {
        for (auto& token : result) {
            // ”дал€ем пробелы в начале
            token.erase(token.begin(), std::find_if(token.begin(), token.end(),
                [](unsigned char ch) { return !std::isspace(ch); }));

            // ”дал€ем пробелы в конце
            token.erase(std::find_if(token.rbegin(), token.rend(),
                [](unsigned char ch) { return !std::isspace(ch); }).base(), token.end());
        }

        // ”дал€ем пустые строки если нужно
        if (skipEmpty) {
            result.erase(std::remove_if(result.begin(), result.end(),
                [](const std::string& s) { return s.empty(); }), result.end());
        }
    }

    return result;
}

IUtils::CompareResult IUtils::CompareVersion(string ver1, string ver2)
{
    vector<string> floats1 = IUtils::Split(ver1, '.', false);
    vector<string> floats2 = IUtils::Split(ver2, '.', false);

    if (floats1.size() < floats2.size())
    {
        for (uint64_t i = 0; i < floats2.size() - floats1.size(); i++)
        {
            floats1.push_back("0");
        }
    }
    if (floats2.size() < floats1.size())
    {
        for (uint64_t i = 0; i < floats1.size() - floats2.size(); i++)
        {
            floats2.push_back("0");
        }
    }

    for (uint64_t i = 0; i < floats1.size(); i++)
    {
        if (stoi(floats1[i]) > stoi(floats2[i]))
        {
            return IUtils::CompareResult::Above;
        }
        else if (stoi(floats1[i]) < stoi(floats2[i]))
        {
            return IUtils::CompareResult::Less;
        }
    }

    return IUtils::CompareResult::Equals;
}
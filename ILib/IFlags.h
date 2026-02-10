#pragma once

#include <cstdint>
#include <cassert>

class IFlags {
public:
    /**
     * Добавляет флаг (устанавливает бит) в битовую маску
     * @param flags Исходная битовая маска
     * @param flag Флаг для добавления (один установленный бит)
     * @return Новая битовая маска с установленным флагом
     */
    static uint64_t AddFlag(uint64_t flags, uint64_t flag) {
        // Проверяем, что передается только один бит
        assert((flag & (flag - 1)) == 0 && "Flag should be a single bit");
        return flags | flag;
    }

    /**
     * Добавляет флаг со сдвигом в битовую маску
     * @param flags Исходная битовая маска
     * @param flag Базовый флаг (один установленный бит)
     * @param shift Сдвиг для флага
     * @return Новая битовая маска с установленным флагом
     */
    static uint64_t AddFlag(uint64_t flags, uint64_t flag, uint64_t shift) {
        // Проверяем, что передается только один бит
        assert((flag & (flag - 1)) == 0 && "Flag should be a single bit");
        assert(shift < 64 && "Shift must be less than 64");

        uint64_t shifted_flag = flag << shift;
        // Проверяем, что после сдвига флаг не выходит за границы 64 бит
        assert(shifted_flag >> shift == flag && "Shifted flag overflow");
        return flags | shifted_flag;
    }

    /**
     * Удаляет флаг (сбрасывает бит) из битовой маски
     * @param flags Исходная битовая маска
     * @param flag Флаг для удаления (один установленный бит)
     * @return Новая битовая маска без указанного флага
     */
    static uint64_t RemoveFlag(uint64_t flags, uint64_t flag) {
        // Проверяем, что передается только один бит
        assert((flag & (flag - 1)) == 0 && "Flag should be a single bit");
        return flags & ~flag;
    }

    /**
     * Удаляет флаг со сдвигом из битовой маски
     * @param flags Исходная битовая маска
     * @param flag Базовый флаг (один установленный бит)
     * @param shift Сдвиг для флага
     * @return Новая битовая маска без указанного флага
     */
    static uint64_t RemoveFlag(uint64_t flags, uint64_t flag, uint64_t shift) {
        // Проверяем, что передается только один бит
        assert((flag & (flag - 1)) == 0 && "Flag should be a single bit");
        assert(shift < 64 && "Shift must be less than 64");

        uint64_t shifted_flag = flag << shift;
        // Проверяем, что после сдвига флаг не выходит за границы 64 бит
        assert(shifted_flag >> shift == flag && "Shifted flag overflow");
        return flags & ~shifted_flag;
    }

    /**
     * Проверяет наличие флага в битовой маске
     * @param flags Битовая маска для проверки
     * @param flag Флаг для проверки (один установленный бит)
     * @return true если флаг установлен, иначе false
     */
    static bool CheckFlag(uint64_t flags, uint64_t flag) {
        // Проверяем, что передается только один бит
        assert((flag & (flag - 1)) == 0 && "Flag should be a single bit");
        return (flags & flag) != 0;
    }

    /**
     * Проверяет наличие флага со сдвигом в битовой маске
     * @param flags Битовая маска для проверки
     * @param flag Базовый флаг (один установленный бит)
     * @param shift Сдвиг для флага
     * @return true если флаг установлен, иначе false
     */
    static bool CheckFlag(uint64_t flags, uint64_t flag, uint64_t shift) {
        // Проверяем, что передается только один бит
        assert((flag & (flag - 1)) == 0 && "Flag should be a single bit");
        assert(shift < 64 && "Shift must be less than 64");

        uint64_t shifted_flag = flag << shift;
        // Проверяем, что после сдвига флаг не выходит за границы 64 бит
        assert(shifted_flag >> shift == flag && "Shifted flag overflow");
        return (flags & shifted_flag) != 0;
    }
};
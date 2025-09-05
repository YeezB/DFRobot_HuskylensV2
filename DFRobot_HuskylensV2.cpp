#include <DFRobot_HuskylensV2.h>

HuskylensV2::HuskylensV2() : result{} {
}
HuskylensV2::~HuskylensV2() {
    for (uint8_t algo = 0; algo < ALGORITHM_COUNT; algo++) {
        for (uint8_t i = 0; i < MAX_RESULT_NUM; i++) {
            if (result[algo][i]) {
                delete result[algo][i];
                result[algo][i] = NULL;
            }
        }
    }
}

bool HuskylensV2::begin(Stream &streamInput) {
    stream = &streamInput;
    wire   = NULL;
    return knock();
}
bool HuskylensV2::begin(TwoWire &streamInput) {
    DBG("\n");
    wire   = &streamInput;
    stream = NULL;
    return knock();
}

int8_t HuskylensV2::getResult(eAlgorithm_t algo) {
    // 所有结果返回到ProtocolV2内存
    // 然后将所有权转给HuskylensV2
#ifndef LARGE_MEMORY
    algo = 0;
#endif

    for (uint8_t i = 0; i < MAX_RESULT_NUM; i++) {
        if (result[algo][i]) {
            delete result[algo][i];
            result[algo][i] = NULL;
        }
    }

    int8_t count = ProtocolV2::getResult(algo);

    for (uint8_t i = 0; i < MAX_RESULT_NUM; i++) {
        // DBG(i);
        // DBG((long long)ProtocolV2::result[i]);
        result[algo][i]       = ProtocolV2::result[i];
        ProtocolV2::result[i] = NULL;
    }
    return count;
}

bool HuskylensV2::available(eAlgorithm_t algo) {
    bool ret = false;
#ifndef LARGE_MEMORY
    algo = 0;
#endif

    for (uint8_t i = 0; i < MAX_RESULT_NUM; i++) {
        if (result[algo][i] != NULL)
            if (!result[algo][i]->used) {
                DBG(i);
                ret = true;
                break;
            }
    }

    return ret;
}

Result *HuskylensV2::popCachedResult(eAlgorithm_t algo) {
    DBG("\n");
#ifndef LARGE_MEMORY
    algo = 0;
#endif
    for (int8_t i = 0; i < MAX_RESULT_NUM; i++) {
        if (result[algo][i]) {
            if (result[algo][i]->used) {
                continue;
            }

            result[algo][i]->used = 1;
            DBG_PRINT("return ");
            DBG_PRINTLN((unsigned long)result[algo][i]);
            DBG(i);
            return result[algo][i];
        }
    }

    return NULL;
}

Result *HuskylensV2::getCachedCenterResult(eAlgorithm_t algo) {
    // DBG("\n");
#ifndef LARGE_MEMORY
    algo = 0;
#endif
    int8_t  centerIndex = -1;
    int32_t minLen      = 0x0FFFFFFF;
    for (int8_t i = 0; i < MAX_RESULT_NUM; i++) {
        if (result[algo][i]) {
            uint32_t len = SQUARE(result[algo][i]->xCenter - LCD_WIDTH / 2) + SQUARE(result[algo][i]->yCenter - LCD_HEIGHT / 2);
            if (len < minLen) {
                minLen      = len;
                centerIndex = i;
            }
        }
    }
    if (centerIndex != -1) {
        return result[algo][centerIndex];
    }
    return NULL;
}

Result *HuskylensV2::getCachedResultByIndex(eAlgorithm_t algo, int16_t index) {
    DBG("\n");
#ifndef LARGE_MEMORY
    algo = 0;
#endif
    if (index >= MAX_RESULT_NUM) {
        return NULL;
    }
    return result[algo][index];
}

Result *HuskylensV2::getCachedResultByID(eAlgorithm_t algo, int16_t ID) {
    DBG("\n");
#ifndef LARGE_MEMORY
    algo = 0;
#endif
    for (uint8_t i = 0; i < MAX_RESULT_NUM; i++) {
        if (result[algo][i] == NULL) {
            continue;
        }
        if (result[algo][i]->ID == ID) {
            return result[algo][i];
        }
    }
    return NULL;
}

int16_t HuskylensV2::getCachedResultNum(eAlgorithm_t algo) {
    DBG("\n");
    int16_t count = 0;
#ifndef LARGE_MEMORY
    algo = 0;
#endif

    for (uint8_t i = 0; i < MAX_RESULT_NUM; i++) {
        if (result[algo][i]) {
            count++;
        }
    }
    return count;
}

int16_t HuskylensV2::getCachedResultLearnedNum(eAlgorithm_t algo) {
    DBG("\n");
    int16_t count = 0;
#ifndef LARGE_MEMORY
    algo = 0;
#endif
    for (uint8_t i = 0; i < MAX_RESULT_NUM; i++) {
        if (result[algo][i] && result[algo][i]->ID) {
            count++;
        }
    }
    return count;
}

int16_t HuskylensV2::getCachedResultNumByID(eAlgorithm_t algo, uint8_t id) {
    DBG("\n");
    int16_t count = 0;
#ifndef LARGE_MEMORY
    algo = 0;
#endif
    for (uint8_t i = 0; i < MAX_RESULT_NUM; i++) {
        if (result[algo][i] && (id == result[algo][i]->ID)) {
            count++;
        }
    }
    return count;
}

Result *HuskylensV2::getCachedIndexResultByID(eAlgorithm_t algo, uint8_t id, uint8_t index) {
    DBG("\n");
    Result *rlt    = NULL;
    uint8_t _index = 0;
#ifndef LARGE_MEMORY
    algo = 0;
#endif
    for (uint8_t i = 0; i < MAX_RESULT_NUM; i++) {
        if (result[algo][i] && (id == result[algo][i]->ID)) {
            if (_index == index) {
                return result[algo][i];
            }
            _index++;
        }
    }
    return rlt;
}

int16_t HuskylensV2::getCachedResultMaxID(void) {
    return maxID;
}
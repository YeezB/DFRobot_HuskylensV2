#include <DFRobot_HuskylensV2.h>

HuskylensV2::HuskylensV2() {
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

Result *HuskylensV2::getCachedResult(eAlgorithm_t algo) {
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

Result *HuskylensV2::getCachedResultByID(eAlgorithm_t algo, int16_t ID) {
    DBG("\n");
#ifndef LARGE_MEMORY
    algo = 0;
#endif
    for (uint8_t i = 0; i < MAX_RESULT_NUM; i++) {
        if (result[algo][i]->used) {
            continue;
        }
        if (result[algo][i]->ID == ID) {
            result[algo][i]->used = 1;
            return result[algo][i];
        }
    }

    return NULL;
}

int16_t HuskylensV2::getCachedResultNum(eAlgorithm_t algo) {
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
/*
为ino提供接口
存储分析result
 */

#ifndef DFROBOT_HUSKYLENS_V2_H
#define DFROBOT_HUSKYLENS_V2_H
#include <Arduino.h>
#include <ProtocolV2.h>

class HuskylensV2 : public ProtocolV2 {
  public:
    HuskylensV2();
    ~HuskylensV2();

    bool begin(Stream &streamInput);
    bool begin(TwoWire &streamInput);

    bool    available(eAlgorithm_t algo);
    int8_t  getResult(eAlgorithm_t algo);
    Result *getCachedResult(eAlgorithm_t algo);
    Result *getCachedResultByID(eAlgorithm_t algo, int16_t ID);
    int16_t getCachedResultNum(eAlgorithm_t algo);
    int16_t getCachedResultLearnedNum(eAlgorithm_t algo);

  public:
    Result *result[ALGORITHM_COUNT][MAX_RESULT_NUM] = {NULL};
};

#endif // DFROBOT_HUSKYLENS_V2_H
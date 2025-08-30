#include <Result.h>

Result::Result(const void *buf) {
    PacketHead_t *head   = (PacketHead_t *)buf;
    PacketData_t *packet = (PacketData_t *)head->data;
    type                 = head->cmd;
    ID                   = packet->ID;
    level                = packet->level;
    xCenter              = packet->first;
    yCenter              = packet->second;
    width                = packet->third;
    height               = packet->fourth;
    used                 = 0;
    String_t *pname      = (String_t *)packet->payload;
    String_t *pcontent   = (String_t *)(packet->payload + sizeof(String_t) + pname->length);
    DBG_KV("sizeof(String_t)=", sizeof(String_t));
    DBG_KV("pname->length=", pname->length);
    DBG_KV("pcontent->length=", pcontent->length);

    if (head->data_length == (uint8_t)((uint32_t)pname - (uint32_t)packet)) {
        DBG("no string data");
    } else {
        if (pname->length) {
            name = pname->toString();
        }
        if (pcontent->length) {
            content = pcontent->toString();
        }
    }
    DBG_KV("type=", type);
    DBG_KV("ID=", ID);
    DBG_KV("xCenter=", xCenter);
    DBG_KV("yCenter=", yCenter);
    DBG_KV("width=", width);

    DBG_KV("height=", height);
    DBG_KV("name=", name);
    DBG_KV("content=", content);
}
Result::~Result() {
}
#ifdef LARGE_MEMORY

FaceResult::FaceResult(const void *buf) : Result(buf) {
    DBG("\n");
    PacketHead_t *head     = (PacketHead_t *)buf;
    PacketData_t *packet   = (PacketData_t *)head->data;
    String_t     *pname    = (String_t *)packet->payload;
    String_t     *pcontent = (String_t *)(packet->payload + sizeof(String_t) + pname->length);
    if (head->data_length == (uint8_t)((uint32_t)pname - (uint32_t)packet)) {
        DBG("no string data");
        return;
    }
    int16_t *face_data = (int16_t *)(packet->payload + pname->length + pcontent->length + sizeof(String_t) * 2);
    if (head->data_length == (uint8_t)((uint32_t)face_data - (uint32_t)packet)) {
        DBG("no externed data");
        return;
    }
    leye_x   = *face_data++;
    leye_y   = *face_data++;
    reye_x   = *face_data++;
    reye_y   = *face_data++;
    nose_x   = *face_data++;
    nose_y   = *face_data++;
    lmouth_x = *face_data++;
    lmouth_y = *face_data++;
    rmouth_x = *face_data++;
    rmouth_y = *face_data++;
}

HandResult::HandResult(const void *buf) : Result(buf) {
    DBG("\n");
    PacketHead_t *head     = (PacketHead_t *)buf;
    PacketData_t *packet   = (PacketData_t *)head->data;
    String_t     *pname    = (String_t *)packet->payload;
    String_t     *pcontent = (String_t *)(packet->payload + sizeof(String_t) + pname->length);

    if (head->data_length == (uint8_t)((uint32_t)pname - (uint32_t)packet)) {
        DBG("no string data");
        return;
    }
    int16_t *hand_data = (int16_t *)(packet->payload + pname->length + pcontent->length + sizeof(String_t) * 2);
    if (head->data_length <= (uint8_t)((uint32_t)hand_data - (uint32_t)packet)) {
        DBG("no externed data");
        return;
    }

    wrist_x = *hand_data++; // 手腕
    wrist_y = *hand_data++;
    DBG_HEX(wrist_x);
    DBG_HEX(wrist_y);
    thumb_cmc_x = *hand_data++;
    thumb_cmc_y = *hand_data++; // 拇指根部
    thumb_mcp_x = *hand_data++;
    thumb_mcp_y = *hand_data++; // 拇指中间关节
    thumb_ip_x  = *hand_data++;
    thumb_ip_y  = *hand_data++; // 拇指第二关节
    thumb_tip_x = *hand_data++;
    thumb_tip_y = *hand_data++; // 拇指指尖

    index_finger_mcp_x  = *hand_data++;
    index_finger_mcp_y  = *hand_data++; // 食指根部
    index_finger_pip_x  = *hand_data++;
    index_finger_pip_y  = *hand_data++; // 食指第一关节
    index_finger_dip_x  = *hand_data++;
    index_finger_dip_y  = *hand_data++; // 食指第二关节
    index_finger_tip_x  = *hand_data++;
    index_finger_tip_y  = *hand_data++; // 食指指尖
    middle_finger_mcp_x = *hand_data++;
    middle_finger_mcp_y = *hand_data++; // 中指根部

    middle_finger_pip_x = *hand_data++;
    middle_finger_pip_y = *hand_data++; // 中指第一关节
    middle_finger_dip_x = *hand_data++;
    middle_finger_dip_y = *hand_data++; // 中指第二关节
    middle_finger_tip_x = *hand_data++;
    middle_finger_tip_y = *hand_data++; // 中指指尖
    ring_finger_mcp_x   = *hand_data++;
    ring_finger_mcp_y   = *hand_data++; // 无名指根部
    ring_finger_pip_x   = *hand_data++;
    ring_finger_pip_y   = *hand_data++; // 无名指第一关节

    ring_finger_dip_x  = *hand_data++;
    ring_finger_dip_y  = *hand_data++; // 无名指第二关节
    ring_finger_tip_x  = *hand_data++;
    ring_finger_tip_y  = *hand_data++; // 无名指指尖
    pinky_finger_mcp_x = *hand_data++;
    pinky_finger_mcp_y = *hand_data++; // 小指根部
    pinky_finger_pip_x = *hand_data++;
    pinky_finger_pip_y = *hand_data++; // 小指第一关节
    pinky_finger_dip_x = *hand_data++;
    pinky_finger_dip_y = *hand_data++; // 小指第二关节
    DBG_HEX(pinky_finger_dip_x);
    DBG_HEX(pinky_finger_dip_y);
    pinky_finger_tip_x = *hand_data++;
    pinky_finger_tip_y = *hand_data++; // 小指指尖
    DBG_HEX(pinky_finger_tip_x);
    DBG_HEX(pinky_finger_tip_y);
}

PoseResult::PoseResult(const void *buf) : Result(buf) {
    DBG("begin parse\n");
    PacketHead_t *head      = (PacketHead_t *)buf;
    PacketData_t *packet    = (PacketData_t *)head->data;
    String_t     *pname     = (String_t *)packet->payload;
    String_t     *pcontent  = (String_t *)(packet->payload + sizeof(String_t) + pname->length);
    int16_t      *pose_data = (int16_t *)(packet->payload + pname->length + pcontent->length + sizeof(String_t) * 2);
    if (head->data_length == (uint8_t)((uint32_t)pname - (uint32_t)packet)) {
        DBG("no string data");
        return;
    }
    if (head->data_length == (uint8_t)((uint32_t)pose_data - (uint32_t)packet)) {
        DBG("no externed data");
        return;
    }
    DBG("hax externed data");
    DBG_PRINTLN(head->data_length - (uint8_t)((uint32_t)pose_data - (uint32_t)packet));
    nose_x      = *pose_data++;
    nose_y      = *pose_data++;
    leye_x      = *pose_data++;
    leye_y      = *pose_data++;
    reye_x      = *pose_data++;
    reye_y      = *pose_data++;
    lear_x      = *pose_data++;
    lear_y      = *pose_data++;
    rear_x      = *pose_data++;
    rear_y      = *pose_data++;
    lshoulder_x = *pose_data++;
    lshoulder_y = *pose_data++;
    rshoulder_x = *pose_data++;
    rshoulder_y = *pose_data++;
    lelbow_x    = *pose_data++;
    lelbow_y    = *pose_data++;
    relbow_x    = *pose_data++;
    relbow_y    = *pose_data++;
    lwrist_x    = *pose_data++;
    lwrist_y    = *pose_data++;
    rwrist_x    = *pose_data++;
    rwrist_y    = *pose_data++;
    lhip_x      = *pose_data++;
    lhip_y      = *pose_data++;
    rhip_x      = *pose_data++;
    rhip_y      = *pose_data++;
    lknee_x     = *pose_data++;
    lknee_y     = *pose_data++;
    rknee_x     = *pose_data++;
    rknee_y     = *pose_data++;
    lankle_x    = *pose_data++;
    lankle_y    = *pose_data++;
    rankle_x    = *pose_data++;
    rankle_y    = *pose_data++;
    DBG("end parse\n");
}

#endif
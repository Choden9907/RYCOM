#include "frameparse.h"


 /*****************************************************
  描    述：  CRC8校验常量表，校验公式为 x^8+x^5+x^4+x^0
******************************************************/
const uint8_t Crc8Table[]={
  0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65,
  157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220,
  35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98,
  190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255,
  70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7,
  219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154,
  101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36,
  248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185,
  140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205,
  17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80,
  175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238,
  50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115,
  202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139,
  87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22,
  233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168,
  116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53
};


/** @brief : CRC校验计算
 * 
 */
quint8 GetCrc8CheckSum(const QByteArray & buf)
{
    quint8 tCrc8 = 0;
    for(quint8 byte : buf)
    {
        tCrc8 = Crc8Table[tCrc8 ^ byte];
    }
    return tCrc8;
}

QList<QByteArray> frameparse::GetDataFrame(QByteArray &recvData)
{
    QList<QByteArray> result;    // 存储解析结果
    QByteArray invalidPkg;       // 临时存储无效数据包
    int index = 0;               // 当前处理位置索引

    while(index < recvData.size())
    {
            uint8_t currentByte = static_cast<uint8_t>(recvData[index]);
            
            // 处理非帧头数据
            if (currentByte != 0xFA && currentByte != 0xFB && currentByte != 0xFC) {
                invalidPkg.append(recvData[index]);
                index++;
                continue;
            }

            // 保存之前的无效数据
            if (!invalidPkg.isEmpty()) {
                result.append(invalidPkg);
                invalidPkg.clear();
            }

            // 检查长度字段是否存在
            if (index + 1 >= recvData.size()) {
                break; // 长度字段不完整，保留数据
            }

            // 获取并验证帧长度
            uint8_t frameLen = static_cast<uint8_t>(recvData[index + 1]);
            if (frameLen < 5 || frameLen > 128) {
                // 长度字段无效，将帧头作为无效数据
                invalidPkg.append(recvData[index]);
                index++;
                continue;
            }

            // 检查完整帧是否存在
            if (index + frameLen > recvData.size()) {
                break; // 数据不完整，保留
            }

            // 提取完整帧
            QByteArray frame = recvData.mid(index, frameLen);
            index += frameLen;

            // 验证CRC (校验位是最后1字节)
            QByteArray dataForCrc = frame.left(frameLen - 1);
            uint8_t crcCalc = GetCrc8CheckSum(dataForCrc);
            uint8_t crcReceived = static_cast<uint8_t>(frame[frameLen - 1]);
            
            if (crcCalc == crcReceived) {
                result.append(frame); // 有效帧
            } else {
                result.append(frame); // 无效帧（校验失败）
            }
    }

    // 处理末尾的无效数据
    if (!invalidPkg.isEmpty()) {
        result.append(invalidPkg);
    }


    // 处理末尾的无效数据
    if (!invalidPkg.isEmpty()) {
        result.append(invalidPkg);
    }

    // 保留未处理数据
    recvData = recvData.mid(index);

    return result;
}

#ifndef FRAMEPARSE_H
#define FRAMEPARSE_H

#include <stdint.h>
#include <QString>
#include <QList>

#define UART_PACK_MAX       128                 //串口1通讯包最大包长(包含Head 1B,ID 1B,LEN 1B,CRC 1B)


typedef struct
{
    uint8_t mHeadId;
    uint8_t mPacketId;
    uint8_t mPacketTotalLen;
    uint8_t mPacketCrc;
    uint8_t mPacketData[UART_PACK_MAX-4];
}APP_UART_PACKET;



class frameparse
{
public:
    static QList<QByteArray> GetDataFrame(QByteArray &recvData);
};

#endif // FRAMEPARSE_H

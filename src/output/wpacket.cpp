#include "wpacket.h"

WPacket::WPacket()
{
}

void WPacket::Clear()
{
    _rdata.clear();
}

void WPacket::AddRobot(RobotData rd)
{
    //rd.RID = htons(rd.RID); // RID was 2 bytes before
    //_rdata.append(rd);
    _rdata[rd.RID]=rd;
}

QByteArray WPacket::GetPacket()
{
    QByteArray rd;

    for(int i=0; i<_rdata.size(); i++)
    {
        _rdata[i].M0 = qToBigEndian<unsigned short int>(_rdata[i].M0);
        _rdata[i].M1 = qToBigEndian<unsigned short int>(_rdata[i].M1);
        _rdata[i].M2 = qToBigEndian<unsigned short int>(_rdata[i].M2);
        _rdata[i].M3 = qToBigEndian<unsigned short int>(_rdata[i].M3);
        rd.append((const char*)&(_rdata[i]), 11); //sizeof(RobotData);


//        if(i == 3)
//        {
//            qDebug()<<"rdata[i].M0 : "<<_rdata[i].M0;
//            qDebug()<<"rdata[i].M1 : "<<_rdata[i].M1;
//            qDebug()<<"rdata[i].M2 : "<<_rdata[i].M2;
//            qDebug()<<"rdata[i].M3 : "<<_rdata[i].M3;
//        }
    }

    unsigned char checksum=0;
    for(int i=0; i<rd.size(); ++i)
        checksum += rd.at(i);

    SendPacketHeader h;
    h.SIB = (2 + 1 + 1) + rd.size() + 1; //RobotData size + 3 byte packet header + 2 byte SOP + 1 byte EOP
    h.CHK = checksum;

    QByteArray ans;
    ans.append(WP_SOP);
    ans.append((const char*)&h, 2); //sizeof(h));
    ans.append(rd);
    ans.append(WP_EOP);

    //qDebug() << ans.toHex();

    // !!!
    Clear();
    return ans;
}

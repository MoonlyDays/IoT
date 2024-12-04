#ifndef PROTOCOL_H
#define PROTOCOL_H

#define PROTOCOL_MSG_LEN 200

enum CmdProtocolType
{
    CMD_REQUEST_METRICS = 0,
};

struct CmdProtocol
{
    int m_iID;
    int m_iEmiterID;
    int m_iSenderID;
    CmdProtocolType m_eCommand;
};

void serialize(const CmdProtocol* protocol, char* packet);
bool deserialize(const char* packet, CmdProtocol* protocol);

#endif
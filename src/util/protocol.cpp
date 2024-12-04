#include "protocol.h"

void serialize(const CmdProtocol *protocol, char *packet)
{
    strcpy(packet, "#START#");
    char *ptr = packet + strlen(packet);

    memcpy(ptr, &protocol->m_iID, sizeof(protocol->m_iID));
    ptr += sizeof(protocol->m_iID);

    memcpy(ptr, &protocol->m_iEmiterID, sizeof(protocol->m_iEmiterID));
    ptr += sizeof(protocol->m_iEmiterID);

    memcpy(ptr, &protocol->m_iSenderID, sizeof(protocol->m_iSenderID));
    ptr += sizeof(protocol->m_iSenderID);

    memcpy(ptr, &protocol->m_eCommand, sizeof(protocol->m_eCommand));
    ptr += sizeof(protocol->m_eCommand);

    strcpy(ptr, "#END#");
}

bool deserialize(const char *packet, CmdProtocol *protocol)
{
    if (strncmp(packet, "#START#", 7) != 0)
        return false;

    packet += 7;

    memcpy(&protocol->m_iID, packet, sizeof(protocol->m_iID));
    packet += sizeof(protocol->m_iID);

    memcpy(&protocol->m_iEmiterID, packet, sizeof(protocol->m_iEmiterID));
    packet += sizeof(protocol->m_iEmiterID);

    memcpy(&protocol->m_iSenderID, packet, sizeof(protocol->m_iSenderID));
    packet += sizeof(protocol->m_iSenderID);

    memcpy(&protocol->m_eCommand, packet, sizeof(protocol->m_eCommand));
    packet += sizeof(protocol->m_eCommand);

    if (strncmp(packet, "#END#", 5) != 0)
        return false;

    return true;
}
#ifndef __SWARM__
#define __SWARM__

#include <painlessMesh.h>


class SwarmNetwork final
{
public:
    SwarmNetwork();
    ~SwarmNetwork();

    void Init(uint8_t channel = 0);
    void Update();
    uint32_t GetTime();
    uint32_t GetNodeCount();

    using ReceivedCallbackT = std::function<void(uint32_t from, String& msg)>;
    void Broadcast(const String& msg);
    void SetReceived(ReceivedCallbackT callback);

private:
    // Callbacks for mesh control
    void ReceivedCallback(uint32_t from, String& msg);
    void NewConnectionCallback(uint32_t nodeId);
    void ChangedConnectionCallback();
    void NodeTimeAdjustedCallback(int32_t offset);
    void DelayReceivedCallback(uint32_t from, int32_t delay);

    painlessMesh m_mesh;
    bool calc_delay = false;
    SimpleList<uint32_t> nodes;
    uint32_t sendMessageTime = 0;
};

#endif
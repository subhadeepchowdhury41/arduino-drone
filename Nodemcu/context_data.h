#ifndef CONTEXT_DATA_H
#define CONTEXT_DATA_H

#include <Arduino.h>

class ContextData {
    public:
        ContextData();
        String getCurrAngles();
        String getCurrPIDs();
        String getCurrThrusts();
        
        String getRemoteString();

        void setCurrAngles(String data);
        void setCurrPids(String data);
        void setCurrThrusts(String data);

        void setRemoteData(String data);
    private:
        String remoteData;

        String currPids;
        String currThrusts;
        String currAngles;
};

#endif

#include "context_data.h"

// constructor
ContextData::ContextData() {
    setCurrThrusts("10000100");
}

// get current strings
String ContextData::getCurrThrusts() {
    return currThrusts;
}

String ContextData::getCurrPIDs() {
    return currPids;
}

String ContextData::getCurrAngles() {
    return currAngles;
}

// set current strings
void ContextData::setCurrAngles(String data) {
    currAngles = data;
}

void ContextData::setCurrPids(String data) {
    currPids = data;
}

void ContextData::setCurrThrusts(String data) {
    currThrusts = data;
}

// set remote data
void ContextData::setRemoteData(String data) {
    remoteData = data;
}

#include "MissClassifier.h"

void MissClassifier::classifyMiss(uint32_t tag, bool isRead, SMPState state) {
    if (state == SMPState::Invalid) {
        if (isRead) readCoheMiss.inc();
        else writeCoheMiss.inc();
    } else if (isCompulsory(tag)) {
        if (isRead) readCompMiss.inc();
        else writeCompMiss.inc();
    } else {
        if (isRead) readReplMiss.inc();
        else writeReplMiss.inc();
    }
}

bool MissClassifier::isCompulsory(uint32_t tag) {
    auto result = accessedTags.insert(tag);
    return result.second; // true if tag was not in the set, indicating a compulsory miss
}

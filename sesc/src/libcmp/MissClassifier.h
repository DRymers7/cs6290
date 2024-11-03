#ifndef MISS_CLASSIFIER_H
#define MISS_CLASSIFIER_H

#include <unordered_set>
#include "../libsuc/GStats.h"

class MissClassifier {

    public:

    enum class MissType { Compulsory, Replacement, Coherence };

    MissClassifier() : readCompMiss("readCompMiss"), writeCompMiss("writeCompMiss"),
                       readReplMiss("readReplMiss"), writeReplMiss("writeReplMiss"),
                       readCoheMiss("readCoheMiss"), writeCoheMiss("writeCoheMiss") {}

    // Classify a miss based on tag and cache state, and update the appropriate counter
    void classifyMiss(uint32_t tag, bool isRead, SMPState state);

private:

    std::unordered_set<uint32_t> accessedTags;

    GStatsCntr readCompMiss, writeCompMiss;
    GStatsCntr readReplMiss, writeReplMiss;
    GStatsCntr readCoheMiss, writeCoheMiss;

    bool isCompulsory(uint32_t tag);
};

#endif // MISS_CLASSIFIER_H
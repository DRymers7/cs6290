#ifndef PREVIOUSCACHESTATETRACKER_H
#define PREVIOUSCACHESTATETRACKER_H

#include "../libcore/MemObj.h"
#include <unordered_set>

#include <cstdint>

class PreviousCacheStateTracker {
    
    private:
        PAddr lastValidTag;
        bool wasValid;
    
    public:
        PreviousCacheStateTracker() : lastValidTag(0), wasValid(false) {}

        void setLastValidTag(PAddr tag) {
            if (lastValidTag != tag) {  // Only update if the tag has changed
                lastValidTag = tag;
                wasValid = true;
            }
        }

        PAddr getLastValidTag() const {
            return lastValidTag;
        }

        bool wasPreviouslyValid() const {
            return wasValid;
        }

        void reset() {
            wasValid = false;
        }

};

#endif // PREVIOUSCACHESTATETRACKER_H
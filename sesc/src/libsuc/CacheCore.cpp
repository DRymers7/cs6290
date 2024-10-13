/*
   SESC: Super ESCalar simulator
   Copyright (C) 2003 University of Illinois.

   Contributed by Jose Renau
                  Basilio Fraguela
                  James Tuck
                  Smruti Sarangi
                  Luis Ceze
                  Karin Strauss

This file is part of SESC.

SESC is free software; you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation;
either version 2, or (at your option) any later version.

SESC is    distributed in the  hope that  it will  be  useful, but  WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should  have received a copy of  the GNU General  Public License along with
SESC; see the file COPYING.  If not, write to the  Free Software Foundation, 59
Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#define CACHECORE_CPP

#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>

#include "CacheCore.h"
#include "SescConf.h"
#include "libcore/EnergyMgr.h"

#define k_RANDOM     "RANDOM"
#define k_LRU        "LRU"
#define k_NXLRU      "NXLRU"

//
// Class CacheGeneric, the combinational logic of Cache
//
template<class State, class Addr_t, bool Energy>
CacheGeneric<State, Addr_t, Energy> *CacheGeneric<State, Addr_t, Energy>::create(int32_t size, int32_t assoc, int32_t bsize, int32_t addrUnit, const char *pStr, bool skew)
{
    CacheGeneric *cache;

    if (skew) {
        I(assoc=1); // Skew cache should be direct map
        cache = new CacheDMSkew<State, Addr_t, Energy>(size, bsize, addrUnit, pStr);
    } else if (assoc==1) {
        // Direct Map cache
        cache = new CacheDM<State, Addr_t, Energy>(size, bsize, addrUnit, pStr);
    } else if(size == (assoc * bsize)) {
        // TODO: Fully assoc can use STL container for speed
        cache = new CacheAssoc<State, Addr_t, Energy>(size, assoc, bsize, addrUnit, pStr);
    } else {
        // Associative Cache
        cache = new CacheAssoc<State, Addr_t, Energy>(size, assoc, bsize, addrUnit, pStr);
    }

    I(cache);
    return cache;
}

template<class State, class Addr_t, bool Energy>
PowerGroup CacheGeneric<State, Addr_t, Energy>::getRightStat(const char* type)
{
    if(strcasecmp(type,"icache")==0)
        return FetchPower;

    if(strcasecmp(type,"itlb")==0)
        return FetchPower;

    if(strcasecmp(type,"cache")==0)
        return MemPower;

    if(strcasecmp(type,"tlb")==0)
        return MemPower;

    if(strcasecmp(type,"dir")==0)
        return MemPower;

    if(strcasecmp(type,"revLVIDTable")==0)
        return MemPower;

    if(strcasecmp(type,"nicecache")==0)
        return MemPower;

    MSG("Unknown power group for [%s], add it to CacheCore", type);
    I(0);

    // default case
    return MemPower;
}

template<class State, class Addr_t, bool Energy>
void CacheGeneric<State, Addr_t, Energy>::createStats(const char *section, const char *name)
{
    // get the type
    bool typeExists = SescConf->checkCharPtr(section, "deviceType");
    const char *type = 0;
    if (typeExists)
        type = SescConf->getCharPtr(section, "deviceType");

    int32_t procId = 0;
    if ( name[0] == 'P' && name[1] == '(' ) {
        // This structure is assigned to an specific processor
        const char *number = &name[2];
        procId = atoi(number);
    }

    if (Energy) {
        PowerGroup pg;
        pg = getRightStat(type);
        rdEnergy[0] = new GStatsEnergy("rdHitEnergy",name
                                       ,procId
                                       ,pg
                                       ,EnergyMgr::get(section,"rdHitEnergy"));

        rdEnergy[1] = new GStatsEnergy("rdMissEnergy",name
                                       ,procId
                                       ,pg
                                       ,EnergyMgr::get(section,"rdMissEnergy"));

        wrEnergy[0]  = new GStatsEnergy("wrHitEnergy",name
                                        ,procId
                                        ,pg
                                        ,EnergyMgr::get(section,"wrHitEnergy"));

        wrEnergy[1] = new GStatsEnergy("wrMissEnergy",name
                                       ,procId
                                       ,pg
                                       ,EnergyMgr::get(section,"wrMissEnergy"));

    } else {
        rdEnergy[0]  = 0;
        rdEnergy[1]  = 0;
        wrEnergy[0]  = 0;
        wrEnergy[1]  = 0;
    }
}

template<class State, class Addr_t, bool Energy>
CacheGeneric<State, Addr_t, Energy> *CacheGeneric<State, Addr_t, Energy>::create(const char *section, const char *append, const char *format, ...)
{
    CacheGeneric *cache=0;
    char size[STR_BUF_SIZE];
    char bsize[STR_BUF_SIZE];
    char addrUnit[STR_BUF_SIZE];
    char assoc[STR_BUF_SIZE];
    char repl[STR_BUF_SIZE];
    char skew[STR_BUF_SIZE];

    snprintf(size ,STR_BUF_SIZE,"%sSize" ,append);
    snprintf(bsize,STR_BUF_SIZE,"%sBsize",append);
    snprintf(addrUnit,STR_BUF_SIZE,"%sAddrUnit",append);
    snprintf(assoc,STR_BUF_SIZE,"%sAssoc",append);
    snprintf(repl ,STR_BUF_SIZE,"%sReplPolicy",append);
    snprintf(skew ,STR_BUF_SIZE,"%sSkew",append);

    int32_t s = SescConf->getInt(section, size);
    int32_t a = SescConf->getInt(section, assoc);
    int32_t b = SescConf->getInt(section, bsize);
    bool sk = false;
    if (SescConf->checkBool(section, skew))
        sk = SescConf->getBool(section, skew);

    //For now, tolerate caches that don't have this defined.
    int32_t u;
    if ( SescConf->checkInt(section,addrUnit) ) {
        if ( SescConf->isBetween(section, addrUnit, 0, b) &&
                SescConf->isPower2(section, addrUnit) )
            u = SescConf->getInt(section,addrUnit);
        else
            u = 1;
    } else {
        u = 1;
    }

    const char *pStr = SescConf->getCharPtr(section, repl);

    if(SescConf->isGT(section, size, 0) &&
            SescConf->isGT(section, bsize, 0) &&
            SescConf->isGT(section, assoc, 0) &&
            SescConf->isPower2(section, size) &&
            SescConf->isPower2(section, bsize) &&
            SescConf->isPower2(section, assoc) &&
            SescConf->isInList(section, repl, k_RANDOM, k_LRU, k_NXLRU)) {

        cache = create(s, a, b, u, pStr, sk);
    } else {
        // this is just to keep the configuration going,
        // sesc will abort before it begins
        cache = new CacheAssoc<State, Addr_t, Energy>(2,
                1,
                1,
                1,
                pStr);
    }

    I(cache);

    char cacheName[STR_BUF_SIZE];
    {
        va_list ap;

        va_start(ap, format);
        vsprintf(cacheName, format, ap);
        va_end(ap);
    }

    cache->createStats(section, cacheName);

    return cache;
}

/*********************************************************
 *  CacheAssoc
 *********************************************************/

template<class State, class Addr_t, bool Energy>
CacheAssoc<State, Addr_t, Energy>::CacheAssoc(int32_t size, int32_t assoc, int32_t blksize, int32_t addrUnit, const char *pStr)
    : CacheGeneric<State, Addr_t, Energy>(size, assoc, blksize, addrUnit)
{
    I(numLines>0);

    if (strcasecmp(pStr, k_RANDOM) == 0)
        policy = RANDOM;
    else if (strcasecmp(pStr, k_LRU)    == 0)
        policy = LRU;
    // Defining NXLRU policy
    else if (strcasecmp(pStr, k_NXLRU) == 0) {
        policy = NXLRU;
    } else {
        MSG("Invalid cache policy [%s]",pStr);
        exit(0);
    }

    mem     = new Line [numLines + 1];
    content = new Line* [numLines + 1];

    for(uint32_t i = 0; i < numLines; i++) {
        mem[i].initialize(this);
        mem[i].invalidate();
        content[i] = &mem[i];
    }

    irand = 0;
}

template<class State, class Addr_t, bool Energy>
typename CacheAssoc<State, Addr_t, Energy>::Line *CacheAssoc<State, Addr_t, Energy>::findLinePrivate(Addr_t addr)
{
    Addr_t tag = calcTag(addr);

    GI(Energy, goodInterface); // If modeling energy. Do not use this
    // interface directly. use readLine and
    // writeLine instead. If it is called
    // inside debugging only use
    // findLineDebug instead

    Line **theSet = &content[calcIndex4Tag(tag)];

    // Check most typical case
    if ((*theSet)->getTag() == tag) {
        //this assertion is not true for SMP; it is valid to return invalid line
#if !defined(SESC_SMP) && !defined(SESC_CRIT)
        I((*theSet)->isValid());
#endif
        return *theSet;
    }

    Line **lineHit=0;
    Line **setEnd = theSet + assoc;

    // For sure that position 0 is not (short-cut)
    {
        Line **l = theSet + 1;
        while(l < setEnd) {
            if ((*l)->getTag() == tag) {
                lineHit = l;
                break;
            }
            l++;
        }
    }

    if (lineHit == 0)
        return 0;

    I((*lineHit)->isValid());

    // No matter what is the policy, move lineHit to the *theSet. This
    // increases locality
    Line *tmp = *lineHit;
    {
        Line **l = lineHit;
        while(l > theSet) {
            Line **prev = l - 1;
            *l = *prev;;
            l = prev;
        }
        *theSet = tmp;
    }

    return tmp;
}

/*
Parameter Addr_t addr: The new address that needs a line in the cache

This method does not only implement the replacement policy because an actual replacement
(e.g., replacing one valid line with another) may not be needed.

:returns If the address is alredy in thecache, this method will return the line
that contains addr. When the set where addr belongs contains non-valid lines, one of those non
valid lines is used - a valid block may have a cache hit in the future, while a non-valid
line cannot. So, we should only replace a valid line if the set has no non-valid lines.

TLDR implementation: 
From the set where addr belongs, return the line that contains addr if there is such a line, 
otherwise return the invalid line that was accessed most recently if there are any invalid lines, 
otherwise return the least recently used line among the lines that are not locked

TODO: NXLRU -> treat hits and invalid lines like existing LRU policy, but when there is no hit
and no valid lines to reutrn, NXLRU should find the second-least-recently-used line among
the non-locked lines. If only one non-locked line exists, that line should be returned,
else if all lines are valid and locked, NXLRU shoul dact like LRU.
*/
template<class State, class Addr_t, bool Energy>
typename CacheAssoc<State, Addr_t, Energy>::Line
*CacheAssoc<State, Addr_t, Energy>::findLine2Replace(Addr_t addr, bool ignoreLocked)
{
    /*
    This method uses set positioning to handle the counts for LRU lines. Based on the position in the set
    we can determine the LRU line as the set end -1 of unlocked lines. Therefore, to implement NXLRU, 
    we simply need to find the LRU line, and then find the next LRU from that position in the set of 
    unlocked lines.
    */
    Addr_t tag    = calcTag(addr);
    Line **theSet = &content[calcIndex4Tag(tag)]; // array (content) of cache lines where each set contains assoc number of lines 

    /*
    1. Check to see if the MRU line in the set (theSet) has a tag that matches the desired tag
    theSet is a pointer to the array of cache lines that make up where the set where the address maps to. 
    */
    // Check most typical case
    if ((*theSet)->getTag() == tag) {
        GI(tag,(*theSet)->isValid());
        return *theSet;
    }

    Line **lineHit=0; // pointer to the line where cache hit occurs
    Line **lineFree=0; // Order of preference, invalid, locked - pointer to candidate line for replacement
    Line **setEnd = theSet + assoc; // pointer to end of set array

    int counter = 0; // simple integer value for tracking count
    Line **targetLinePointer = 0; // target line pointer for managing NXLRU

    /*
    Refactored to use a switch statement that changes based on the active policy. This way, we can ensure that
    the behavior for LRU and RANDOM does not change, and we can add NXLRU, and other policy additions going forward as needed.

    This method is responsible for selecting and applying the appropriate replacement policy for choosing a cache line in a 
    cache set. It currently supports three policies (since policy is enumerated, there is no inherent need for a default case):

    Case: LRU/RANDOM - existing logic/while loop
    Case: NXLRU - NXLRU implementation
    */
    {
        Line **l = setEnd -1;
        switch (policy) {
            case LRU:
            case RANDOM:
            while(l >= theSet) {
                // For each line, the method checks if the tag matches the target tag.
                if ((*l)->getTag() == tag) {
                    lineHit = l;
                    break;
                }
                // if the line is invalid, lineFree is set to this line. Looping LRU to MRU , last invalid closest to MRU is used.
                if (!(*l)->isValid())
                    lineFree = l; // prefer the most recently used invalid line
                // if no invalid line has been found yet and the line is unlocked, lineFree is set to this line
                else if (lineFree == 0 && !(*l)->isLocked())
                    lineFree = l; // choose the least recently used unlocked line if no invalid line

                // If line is invalid, isLocked must be false
                GI(!(*l)->isValid(), !(*l)->isLocked());
                l--;
            }
            break;

            case NXLRU: {
                while (l >= theSet && policy == NXLRU) {
                    // For each line, the method checks if the tag matches the target tag.
                    if ((*l)->getTag() == tag) {
                        lineHit = l;
                        break;
                    }
                    // if the line is invalid, lineFree is set to this line. Looping LRU to MRU , last invalid closest to MRU is used.
                    if (!(*l)->isValid())
                        lineFree = l; // prefer the most recently used invalid line
                    // if no invalid line has been found yet and the line is unlocked, lineFree is set to this line
                    else if (lineFree == 0 && !(*l)->isLocked()) {
                        counter++;
                        targetLinePointer = l;
                        if (counter == 2) {
                            lineFree = l;
                        }
                    }
                    // If line is invalid, isLocked must be false
                    GI(!(*l)->isValid(), !(*l)->isLocked());
                    l--;
                }
                if (counter == 1 && lineFree == 0) {
                    lineFree = targetLinePointer;
                }
                break;
            }
        }
    }

    GI(lineFree, !(*lineFree)->isValid() || !(*lineFree)->isLocked());

    // return the line where the cache hit was found *
    if (lineHit)
        return *lineHit;

    I(lineHit==0);

    // no replacement is possible because all lines are locked
    if(lineFree == 0 && !ignoreLocked)
        return 0;

    /*
    No invalid or unlocked lines are found and ignoreLocked is true: inactive for our use case
    per project FAQ

    Replacement candidates:
    1. LRU -> line in LRU position in the set (end -1)
    2. NXLRU -> line in NXLRU position in the set (end - 2)
    */
    if (lineFree == 0) {
        I(ignoreLocked);
        if (policy == RANDOM) {
            lineFree = &theSet[irand];
            irand = (irand + 1) & maskAssoc;
        } else if (policy == LRU) {
            I(policy == LRU);
            // Get the oldest line possible
            lineFree = setEnd-1;
        } else if (policy == NXLRU) {
            I(policy == NXLRU);
            lineFree = setEnd -2;
        }
    } else if(ignoreLocked) { // Ignore this, this is dead code
        if (policy == RANDOM && (*lineFree)->isValid()) {
            lineFree = &theSet[irand];
            irand = (irand + 1) & maskAssoc;
        } else {
            //      I(policy == LRU);
            // Do nothing. lineFree is the oldest
        }
    }

    I(lineFree);
    GI(!ignoreLocked, !(*lineFree)->isValid() || !(*lineFree)->isLocked());

    if (lineFree == theSet)
        return *lineFree; // Hit in the first possition - already at MRU position

    // Move lineFree to MRU position
    Line *tmp = *lineFree;
    {
        Line **l = lineFree;
        while(l > theSet) {
            Line **prev = l - 1;
            *l = *prev;;
            l = prev;
        }
        *theSet = tmp;
    }

    return tmp;

}

/*********************************************************
 *  CacheDM
 *********************************************************/

template<class State, class Addr_t, bool Energy>
CacheDM<State, Addr_t, Energy>::CacheDM(int32_t size, int32_t blksize, int32_t addrUnit, const char *pStr)
    : CacheGeneric<State, Addr_t, Energy>(size, 1, blksize, addrUnit)
{
    I(numLines>0);

    mem     = new Line[numLines + 1];
    content = new Line* [numLines + 1];

    for(uint32_t i = 0; i < numLines; i++) {
        mem[i].initialize(this);
        mem[i].invalidate();
        content[i] = &mem[i];
    }
}

template<class State, class Addr_t, bool Energy>
typename CacheDM<State, Addr_t, Energy>::Line *CacheDM<State, Addr_t, Energy>::findLinePrivate(Addr_t addr)
{
    Addr_t tag = calcTag(addr);

    GI(Energy, goodInterface); // If modeling energy. Do not use this
    // interface directly. use readLine and
    // writeLine instead. If it is called
    // inside debugging only use
    // findLineDebug instead

    Line *line = content[calcIndex4Tag(tag)];

    if (line->getTag() == tag) {
        I(line->isValid());
        return line;
    }

    return 0;
}

template<class State, class Addr_t, bool Energy>
typename CacheDM<State, Addr_t, Energy>::Line
*CacheDM<State, Addr_t, Energy>::findLine2Replace(Addr_t addr, bool ignoreLocked)
{
    Addr_t tag = calcTag(addr);
    Line *line = content[calcIndex4Tag(tag)];

    if (ignoreLocked)
        return line;

    if (line->getTag() == tag) {
        GI(tag,line->isValid());
        return line;
    }

    if (line->isLocked())
        return 0;

    return line;
}

/*********************************************************
 *  CacheDMSkew
 *********************************************************/

template<class State, class Addr_t, bool Energy>
CacheDMSkew<State, Addr_t, Energy>::CacheDMSkew(int32_t size, int32_t blksize, int32_t addrUnit, const char *pStr)
    : CacheGeneric<State, Addr_t, Energy>(size, 1, blksize, addrUnit)
{
    I(numLines>0);

    mem     = new Line[numLines + 1];
    content = new Line* [numLines + 1];

    for(uint32_t i = 0; i < numLines; i++) {
        mem[i].initialize(this);
        mem[i].invalidate();
        content[i] = &mem[i];
    }
}

template<class State, class Addr_t, bool Energy>
typename CacheDMSkew<State, Addr_t, Energy>::Line *CacheDMSkew<State, Addr_t, Energy>::findLinePrivate(Addr_t addr)
{
    Addr_t tag = calcTag(addr);

    GI(Energy, goodInterface); // If modeling energy. Do not use this
    // interface directly. use readLine and
    // writeLine instead. If it is called
    // inside debugging only use
    // findLineDebug instead

    Line *line = content[calcIndex4Tag(tag)];

    if (line->getTag() == tag) {
        I(line->isValid());
        return line;
    }

    // BEGIN Skew cache
    Addr_t tag2 = calcTag(addr ^ (addr>>7));
    line = content[calcIndex4Tag(tag2)];

    if (line->getTag() == tag) {
        I(line->isValid());
        return line;
    }
    // END Skew cache

    return 0;
}

template<class State, class Addr_t, bool Energy>
typename CacheDMSkew<State, Addr_t, Energy>::Line
*CacheDMSkew<State, Addr_t, Energy>::findLine2Replace(Addr_t addr, bool ignoreLocked)
{
    Addr_t tag = calcTag(addr);
    Line *line = content[calcIndex4Tag(tag)];

    if (ignoreLocked)
        return line;

    if (line->getTag() == tag) {
        GI(tag,line->isValid());
        return line;
    }

    if (line->isLocked())
        return 0;

    // BEGIN Skew cache
    Addr_t tag2 = calcTag(addr ^ (addr>>7));
    Line *line2 = content[calcIndex4Tag(tag2)];

    if (line2->getTag() == tag) {
        I(line2->isValid());
        return line2;
    }
    static int32_t rand_number =0;
    if (rand_number++ & 1)
        return line;
    else
        return line2;
    // END Skew cache

    return line;
}

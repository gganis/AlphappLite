//////////////////////////////////////////////////////////
//
// CLASS TimeInfo 
// Class for time storage and comparison. 
//
///////////////////////////////////////////////////////////
 

#ifndef _ALTIME_H_
#define _ALTIME_H_

//! class used to store time information
/*!
 * can be compared, and build from std alpha integer time/date format
 */
class TimeInfo {
public:
TimeInfo() {}
TimeInfo(int,int);
int msec;
int sec;
int min;
int hour;
int day;
int month;
int year;
bool operator<(const TimeInfo op2) const;
bool operator>(const TimeInfo op2) const;
};
#endif

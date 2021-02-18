////////////////////////////////////////////////////////////////////
//
// Implementation of class TimeInfo
//
//
////////////////////////////////////////////////////////////////////

#include "TimeInfo.h"

TimeInfo::TimeInfo(int date, int time)
{
      msec  = (time%100)*10;
      sec   = (time/100)%100;
      min   = (time/10000)%100;
      hour  = time/1000000;
      day   = date%100;
      month = (date/100)%100;
      year  = date/10000;
      if (year>50) year+=1900; else year+=2000;
}

bool TimeInfo::operator<(const TimeInfo op2) const
{
  if (year<op2.year) return 1;
  if (year>op2.year) return 0;
  if (month<op2.month) return 1;
  if (month>op2.month) return 0;
  if (day<op2.day) return 1;
  if (day>op2.day) return 0;
  if (hour<op2.day) return 1;
  if (hour>op2.day) return 0;
  if (min<op2.min) return 1;
  if (min>op2.min) return 0;
  if (sec<op2.sec) return 1;
  if (sec>op2.sec) return 0;
  if (msec<op2.sec) return 1;
  return 0;
}

bool TimeInfo::operator>(const TimeInfo op2) const
{
  if (year>op2.year) return 1;
  if (year<op2.year) return 0;
  if (month>op2.month) return 1;
  if (month<op2.month) return 0;
  if (day>op2.day) return 1;
  if (day<op2.day) return 0;
  if (hour>op2.day) return 1;
  if (hour<op2.day) return 0;
  if (min>op2.min) return 1;
  if (min<op2.min) return 0;
  if (sec>op2.sec) return 1;
  if (sec<op2.sec) return 0;
  if (msec>op2.sec) return 1;
  return 0;
}


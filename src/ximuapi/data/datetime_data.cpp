/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#include "ximuapi/data/datetime_data.h"

namespace ximu {


DateTimeData::DateTimeData()
    :
    DateTimeData(2000, 1, 1, 0, 0, 0) {
}


DateTimeData::DateTimeData(const std::tm& t)
    :
    DateTimeData(t.tm_year, t.tm_mon, t.tm_mday,
                 t.tm_hour, t.tm_min, t.tm_sec) {
}

DateTimeData::DateTimeData(size_t year, size_t month, size_t day,
               size_t hours, size_t minutes, size_t seconds)
    :
    _year(year),
    _month(month),
    _day(day),
    _hours(hours),
    _minutes(minutes),
    _seconds(seconds) {
}


size_t DateTimeData::year() const {
  return _year;
}

void DateTimeData::year(size_t year) {
  _year = year;
}

size_t DateTimeData::month() const {
  return _month;
}

void DateTimeData::month(size_t month) {
  _month = month;
}

size_t DateTimeData::day() const {
  return _day;
}

void DateTimeData::day(size_t day) {
  _day = day;
}

size_t DateTimeData::hours() const {
  return _hours;
}

void DateTimeData::hours(size_t hours) {
_hours = hours;
}

size_t DateTimeData::minutes() const {
  return _minutes;
}

void DateTimeData::minutes(size_t minutes) {
  _minutes = minutes;
}

size_t DateTimeData::seconds() const {
  return _seconds;
}

void DateTimeData::seconds(size_t seconds) {
  _seconds = seconds;
}

}  // namespace ximu

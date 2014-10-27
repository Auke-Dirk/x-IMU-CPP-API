/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_DATA_DATETIME_DATA_H_
#define INCLUDE_XIMUAPI_DATA_DATETIME_DATA_H_

#include <ctime>
#include "ximuapi/enumerations.h"

namespace ximu {

// DateTime Data class
class DateTimeData {
 public:
  DateTimeData();
  explicit DateTimeData(const std::tm& time);
  DateTimeData(size_t year, size_t month, size_t day,
               size_t hours, size_t minutes, size_t seconds);


  // <summary>
  // Gets or sets the year. Value must be from 2000 2099.
  // </summary>
  size_t year() const;
  void year(size_t year);

  // <summary>
  // Gets or sets the month. Value must be from 1 to 12.
  // </summary>
  size_t month() const;
  void month(size_t month);

  // <summary>
  // Gets or sets the day. Value must be from 1 to 31.
  // </summary>
  size_t day() const;
  void day(size_t day);

  // <summary>
  // Gets or sets the hours. Value must be from 0 to 23.
  // </summary>
  size_t hours() const;
  void hours(size_t hours);

  // <summary>
  // Gets or sets the minutes. Value must be from 0 to 59.
  // </summary>
  size_t minutes() const;
  void minutes(size_t minutes);

  // <summary>
  // Gets or sets the seconds. Value must be from 0 to 59.
  // </summary>
  size_t seconds() const;
  void seconds(size_t seconds);

 private:
  size_t _year;
  size_t _month;
  size_t _day;
  size_t _hours;
  size_t _minutes;
  size_t _seconds;
};

}  // namespace ximu

#endif  // INCLUDE_XIMUAPI_DATA_DATETIME_DATA_H_

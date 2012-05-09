#ifndef CAL_SYSTEM_ENUMS
#define CAL_SYSTEM_ENUMS


enum day_of_week{
  SUNDAY = 0,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
};
enum color{
  CLEAR=0,
  RED,
  ORANGE,
  YELLOW,
  GREEN,
  BLUE,
  PURPLE,
  BLACK
};

enum font{
  FONT_A=0,
  FONT_B
};

enum ruleAntecedentField{
  SUMMARY = 0,
  LOCATION,
  TIME
};

enum ruleConsequentField{
  BOX_COLOR = 0,
  TEXT_COLOR,
  TIME_FONT,
  SUMMARY_FONT,
  LOCATION_FONT
};
#endif /* !CAL_SYSTEM_ENUMS */

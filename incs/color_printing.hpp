#ifndef COLOR_PRINTING_HPP
#define COLOR_PRINTING_HPP

//ansi color codes
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLDBLACK   "\033[1m\033[30m"
#define BOLDRED     "\033[1m\033[31m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define BOLDBLUE    "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN    "\033[1m\033[36m"
#define BOLDWHITE   "\033[1m\033[37m"

//printing macros
#include <iostream>

#define MSG_COLOR RED
#define POS_COLOR CYAN

#define PRINTPOS        std::cerr<<POS_COLOR<<"["<<__FILE__<<":"<<__LINE__<<"]"<<RESET<<std::endl;
#define DBG(X)          std::cerr<<POS_COLOR<<"["<<__FILE__<<":"<<__LINE__<<"]"<<"\n"<<MSG_COLOR<<X<<RESET<<std::endl;
#define PRINTCOLOR(c,s) std::cerr<<c<<s<<RESET<<std::endl;

#endif

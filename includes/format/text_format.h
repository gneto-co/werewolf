#ifndef STRINGS_H
#define STRINGS_H

/******************************************
 *                                        *
 *                DEFINES                 *
 *                                        *
 ******************************************/

#define PRINT std::cout

#define ENDL "\n"

#define STRING std::string

// print (x) 'n'
#define SPACER(x)               \
    for (int i = 0; i < x; i++) \
        PRINT << ENDL;

// reset text config + '\n'
#define RESEND \
    RESET ENDL

// align the text (x) spaces to the Right
#define R_ALIGN(x) \
    std::right << std::setw(x)

// align the text (x) spaces to the Left
#define L_ALIGN(x) \
    std::left << std::setw(x)

// a debug message for functions
#define FT_MSG(name) \
    PRINT << MAGENTA ITALICS << name << " called" << RESEND;

// a title message for main
#define MAIN_MSG(name) \
    PRINT << GREEN UNDERLINED << name << RESEND;

// default try catch exception handle
// print error message followed by a '\n'
#define CATCH \
    catch (const std::exception &e) { std::cerr << e.what() << '\n'; }

#define ON 1
#define OFF 0

/******************************************
 *                                        *
 *              DEFINE COLORS             *
 *                                        *
 ******************************************/

#define COLORS ON

#if COLORS == ON

// Cursor Moving
#define CURSOR_UP(x) "\033[" << x << "A"
#define CURSOR_DOWN(x) "\033[" << x << "B"
#define CURSOR_RIGHT(x) "\033[" << x << "C"
#define CURSOR_LEFT(x) "\033[" << x << "D"
#define CURSOR_ALL_LEFT "\033[0G"

// Cursor Clear Screen
#define CLEAR_SCREEN_FORWARD_CURSOR "\033[J"
#define CLEAR_LINE_FORWARD_CURSOR "\033[K"
#define CLEAR_LINE_BACK_CURSOR "\033[1K"
#define CLEAR_ACTUAL_LINE "\033[0K"
#define CLEAR_SCREEN "\033[2J\033[H"

// Reset
#define RESET "\033[0m"

// Text Colors (30-37)
#define RED "\033[31m"
#define MAGENTA "\033[35m"
#define ORANGE "\033[38;2;255;140;0m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define PURPLE "\033[38;2;128;0;128m"
#define PINK "\033[38;2;255;105;180m"
#define BLACK "\033[30m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

// Bright Text Colors (90-97)
#define BRIGHT_BLACK "\033[90m"
#define BRIGHT_RED "\033[91m"
#define BRIGHT_GREEN "\033[92m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN "\033[96m"
#define BRIGHT_WHITE "\033[97m"

// Text Background (40-47)
#define BLACK_BACKGROUND "\033[40m"
#define RED_BACKGROUND "\033[41m"
#define GREEN_BACKGROUND "\033[42m"
#define YELLOW_BACKGROUND "\033[43m"
#define BLUE_BACKGROUND "\033[44m"
#define MAGENTA_BACKGROUND "\033[45m"
#define CYAN_BACKGROUND "\033[46m"
#define WHITE_BACKGROUND "\033[47m"

// Text Formatting (1-9)
#define BOLT "\033[1m"
#define LOW_BRIGHT "\033[2m"
#define ITALICS "\033[3m"
#define UNDERLINED "\033[4m"
#define BLINKING "\033[5m"
#define REVERSE_COLORS "\033[7m"
#define HIDE_TEXT "\033[8m"
#define CROSSED_OUT "\033[9m"

#else

#define CURSOR_UP(x) ""
#define CURSOR_DOWN(x) ""
#define CURSOR_RIGHT(x) ""
#define CURSOR_LEFT(x) ""
#define CURSOR_ALL_LEFT ""
#define CLEAR_SCREEN_FORWARD_CURSOR ""
#define CLEAR_LINE_FORWARD_CURSOR ""
#define CLEAR_LINE_BACK_CURSOR ""
#define CLEAR_ACTUAL_LINE ""
#define RESET ""
#define BLACK ""
#define RED ""
#define GREEN ""
#define YELLOW ""
#define BLUE ""
#define MAGENTA ""
#define CYAN ""
#define WHITE ""
#define ORANGE ""
#define BRIGHT_BLACK ""
#define BRIGHT_RED ""
#define BRIGHT_GREEN ""
#define BRIGHT_YELLOW ""
#define BRIGHT_BLUE ""
#define BRIGHT_MAGENTA ""
#define BRIGHT_CYAN ""
#define BRIGHT_WHITE ""
#define BLACK_BACKGROUND ""
#define RED_BACKGROUND ""
#define GREEN_BACKGROUND ""
#define YELLOW_BACKGROUND ""
#define BLUE_BACKGROUND ""
#define MAGENTA_BACKGROUND ""
#define CYAN_BACKGROUND ""
#define WHITE_BACKGROUND ""
#define BOLT ""
#define LOW_BRIGHT ""
#define ITALICS ""
#define UNDERLINED ""
#define BLINKING ""
#define REVERSE_COLORS ""
#define HIDE_TEXT ""
#define CROSSED_OUT ""

#endif

#endif

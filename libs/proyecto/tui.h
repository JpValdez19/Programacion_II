#ifndef TUI_H
#define TUI_H

// Needed to store the list of focusable widgets
#include "../llist/llist.h"
#include "proyecto.h"
#include <wchar.h>
#include <locale.h>

// if in linux, use termios.h
#ifdef __linux__

    #include <termios.h>
    #include <unistd.h>
    #include <sys/ioctl.h>

#endif

/**
 * @brief The TUI class
 * This class is the driver for the TUI in this proyect.
 */

Result initTUI();

/**
 * @brief Positions the cursor at the given coordinates.
 *
 * @param x X coordinate.
 * @param y Y coordinate.
 */
void gotoxy(int x, int y);

/**
 * @brief Creates a new window.
 *
 */
#define NEW_SCREEN() printf("\e[?1049h")

/**
 * @brief Deletes the current window.
 *
 */
#define CLOSE_SCREEN() printf("\e[?1049l")

/**
 * @brief Prints the status bar at the bottom of the screen.
 *
 */
void print_status_bar();

// Text styles
#define NORMAL "\e[0m"
#define BOLD "\e[1m"
#define DIM "\e[2m"
#define ITALIC "\e[3m"
#define INVERSE "\e[7m"

// Colors

/**
 * @brief Returns the colored-terminal-code for the given color in the foreground.
 *
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 *
 * @return wchar_t The color text-code.
 */
wchar_t *FRGB(int r, int g, int b);

/**
 * @brief Returns the colored-terminal-code for the given color in the background.
 *
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 *
 * @return wchar_t The color text-code.
 */
wchar_t *BRGB(int r, int g, int b);

// MISC
#define HIDE_CURSOR "\e[?25l"
#define SHOW_CURSOR "\e[?25h"

// Cursor echo
Result noEcho();
Result echo();

// RAW Modes
Result rawMode();
Result cookedMode();

// Get window size
void get_window_size(int *rows, int *cols);

/**
 * @brief Input widget definition
 *
 */
typedef struct inputWidget
{
    // Position of the widget
    int x, y;
    // Size of the widget
    int width, height;

    // Type of input to accept
    enum input_type
    {
        NUMERIC,
        ALPHA,
        ALPHANUMERIC,
        ANY,
    } type;

    // Password mode
    enum text_mode
    {
        PLAIN,
        PASSWORD,
    } mode;

    // Tile of the widget
    wchar_t *title;

    // Function to call when the input is accepted
    Result (*on_accept)(wchar_t *input);

    // Function to call when the input is cancelled
    Result (*on_cancel)(void *opcional_data);

    // Function to call when the input is changed
    Result (*on_change)(wchar_t *input);

    // Focus / Unfocus handlers
    Result (*on_focus)(void *opcional_data);
    Result (*on_unfocus)(void *opcional_data);
};

/**
 * @brief Focusable list widget definition
 *
 */
typedef struct listWidget
{
    // Position of the widget
    int x, y;
    // Size of the widget
    int width, height;

    // Title of the widget
    wchar_t *title;

    // List of items
    LList *items;

    // Index of the focused item
    int selected;

    // Function to call when the focused item is selected
    Result (*on_accept)(void *opcional_data);

    // Function to call when the input is cancelled
    Result (*on_cancel)(void *opcional_data);

    // Function to call when the focused item is changed
    Result (*on_change)(void *opcional_data);

    // Focus / Unfocus handlers
    Result (*on_focus)(void *opcional_data);
    Result (*on_unfocus)(void *opcional_data);
};

/**
 * @brief Focusable button widget definition
 *
 */
typedef struct buttonWidget
{
    // Position of the widget
    int x, y;
    // Size of the widget
    int width, height;

    // Title of the widget
    wchar_t *title;

    // Function to call when the button is pressed
    Result (*on_press)(void *opcional_data);

    // Focus / Unfocus handlers
    Result (*on_focus)(void *opcional_data);
    Result (*on_unfocus)(void *opcional_data);
};

/**
 * @brief Focus the first widget in the list.
 *
 *  Handles all input through the configured functions.
 *  Any other non-input is handled internally such as <enter>'s, <tab>'s, <arrow-key>'s etc.
 *
 * @param widgets List of widgets to focus
 *
 */
Result focus(LList *widgets);

/**
 * @brief Generic Widget type definition, meant to be used in the list of widgets.
 *
 */
typedef struct Widget
{
    // Type of widget
    enum widget_type
    {
        INPUT,
        LIST,
        BUTTON,
    } type;

    // Pointer to the widget
    Result *widget;
};

#endif
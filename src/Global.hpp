/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 09/06/2020
 */
#pragma once

#include <string>

/**
 * This header file defines global variables used between more Controllers.
 */

/**
 * The ASCII transition currently used by the application.
 */
extern std::string glob_ASCII_transition;

/**
 * The inverted ASCII transition currently used by the application.
 */
extern std::string glob_ASCII_transition_inverted;


/**
 * This variable stores whether the inversion is set to true in the application.
 */
extern bool glob_inverted;

/**
 * This variable stores whether the application has already done a conversion since a new folder was set.
 */
extern bool glob_converted;

/**
 * Full path to the folder the application is working with.
 */
extern std::string glob_folder_location;
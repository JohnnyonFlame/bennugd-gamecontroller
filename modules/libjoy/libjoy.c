/*
 *  Copyright � 2006-2012 SplinterGU (Fenix/Bennugd)
 *  Copyright � 2002-2006 Fenix Team (Fenix)
 *  Copyright � 1999-2002 Jos� Luis Cebri�n Pag�e (Fenix)
 *
 *  This file is part of Bennu - Game Development
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty. In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *
 *     2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *
 *     3. This notice may not be removed or altered from any source
 *     distribution.
 *
 */

/* --------------------------------------------------------------------------- */
/* Thanks Sandman for suggest on openjoys at initialization time               */
/* --------------------------------------------------------------------------- */
/* Credits SplinterGU/Sandman 2007-2009                                        */
/* --------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>

/* --------------------------------------------------------------------------- */

#include "bgddl.h"

#include "bgdrtm.h"

#include "files.h"
#include "xstrings.h"

/* --------------------------------------------------------------------------- */

#ifdef TARGET_CAANOO
#include "caanoo/te9_tf9_hybrid_driver.c"

#ifndef ABS
#define ABS(x) (((x) < 0) ? -(x):(x))
#endif

#endif

/* --------------------------------------------------------------------------- */

#define MAX_JOYS    4

int libjoy_get_button_specific( int joy, int button );
int libjoy_get_position_specific( int joy, int axis );
int libjoy_get_hat_specific( int joy, int hat );
static int _max_joys = 0;
static int _selected_joystick = -1;

static SDL_GameController *controllers[MAX_JOYS];

/* --------------------------------------------------------------------------- */
/* libjoy_num ()                                                               */
/* Returns the number of joysticks present in the system                       */
/* --------------------------------------------------------------------------- */

int libjoy_num( void )
{
    return _max_joys;
}

/* --------------------------------------------------------------------------- */
/* libjoy_name (int JOY)                                                       */
/* Returns the name for a given joystick present in the system                 */
/* --------------------------------------------------------------------------- */

int libjoy_name( int joy )
{
    int result;
    result = string_new( SDL_GameControllerName( controllers[joy] ) );
    string_use( result );
    return result;
}

/* --------------------------------------------------------------------------- */
/* libjoy_select (int JOY)                                                     */
/* Returns the selected joystick number                                        */
/* --------------------------------------------------------------------------- */

int libjoy_select( int joy )
{
    return ( _selected_joystick = joy );
}

/* --------------------------------------------------------------------------- */
/* libjoy_buttons ()                                                           */
/* Returns the selected joystick total buttons                                 */
/* --------------------------------------------------------------------------- */

int libjoy_buttons( void )
{
    return SDL_CONTROLLER_BUTTON_MAX;
}

/* --------------------------------------------------------------------------- */
/* libjoy_axes ()                                                              */
/* Returns the selected joystick total axes                                    */
/* --------------------------------------------------------------------------- */

int libjoy_axes( void )
{
    return 4;
}

/* --------------------------------------------------------------------------- */
/* libjoy_get_button ( int button )                                            */
/* Returns the selected joystick state for the given button                    */
/* --------------------------------------------------------------------------- */

int libjoy_get_button( int button )
{
    return libjoy_get_button_specific( button, _selected_joystick );
}

/* --------------------------------------------------------------------------- */
/* libjoy_get_position ( int axis )                                            */
/* Returns the selected joystick state for the given axis                      */
/* --------------------------------------------------------------------------- */

int libjoy_get_position( int axis )
{
    return libjoy_get_position_specific( axis, _selected_joystick );
}

/* --------------------------------------------------------------------------- */
/* libjoy_hats ()                                                              */
/* Returns the total number of POV hats of the current selected joystick       */
/* --------------------------------------------------------------------------- */

int libjoy_hats( void )
{
    if ( _selected_joystick >= 0 && _selected_joystick < _max_joys )
    {
        return 1;
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/* libjoy_balls ()                                                             */
/* Returns the total number of balls of the current selected joystick          */
/* --------------------------------------------------------------------------- */

int libjoy_balls( void )
{
    return 0;
}

/* --------------------------------------------------------------------------- */
/* libjoy_get_hat (int HAT)                                                    */
/* Returns the state of the specfied hat on the current selected joystick      */
/* --------------------------------------------------------------------------- */

int libjoy_get_hat( int hat )
{
    return libjoy_get_hat_specific( hat, _selected_joystick );
}

/* --------------------------------------------------------------------------- */
/* libjoy_get_ball (int BALL, int* dx, int* dy)                                */
/* Returns the state of the specfied ball on the current selected joystick     */
/* --------------------------------------------------------------------------- */

int libjoy_get_ball( int ball, int * dx, int * dy )
{
    return -1;
}

/* --------------------------------------------------------------------------- */

int libjoy_get_accel( int * x, int * y, int * z )
{
    return -1;
}

/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
/* libjoy_buttons_specific (int JOY)                                           */
/* Returns the selected joystick total buttons                                 */
/* --------------------------------------------------------------------------- */

int libjoy_buttons_specific( int joy )
{
    if ( joy >= 0 && joy < _max_joys )
    {
        return 12;
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/* libjoy_axes_specific (int JOY)                                              */
/* Returns the selected joystick total axes                                    */
/* --------------------------------------------------------------------------- */

int libjoy_axes_specific( int joy )
{
    if ( joy >= 0 && joy < _max_joys )
    {
        return 4;
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/* libjoy_get_button_specific (int JOY, int button)                            */
/* Returns the selected joystick state for the given button                    */
/* --------------------------------------------------------------------------- */

int libjoy_get_button_specific( int joy, int button )
{
    if ( joy >= 0 && joy < _max_joys )
    {
        switch ( button )
        {
            case  0: return SDL_GameControllerGetButton( controllers[joy], SDL_CONTROLLER_BUTTON_A );
            case  1: return SDL_GameControllerGetButton( controllers[joy], SDL_CONTROLLER_BUTTON_B );
            case  2: return SDL_GameControllerGetButton( controllers[joy], SDL_CONTROLLER_BUTTON_X );
            case  3: return SDL_GameControllerGetButton( controllers[joy], SDL_CONTROLLER_BUTTON_Y );
            case  4: return SDL_GameControllerGetButton( controllers[joy], SDL_CONTROLLER_BUTTON_LEFTSHOULDER );
            case  5: return SDL_GameControllerGetButton( controllers[joy], SDL_CONTROLLER_BUTTON_RIGHTSHOULDER );
            case  6: return SDL_GameControllerGetButton( controllers[joy], SDL_CONTROLLER_BUTTON_BACK );
            case  7: return SDL_GameControllerGetButton( controllers[joy], SDL_CONTROLLER_BUTTON_START );
            case  8: return SDL_GameControllerGetButton( controllers[joy], SDL_CONTROLLER_BUTTON_LEFTSTICK );
            case  9: return SDL_GameControllerGetButton( controllers[joy], SDL_CONTROLLER_BUTTON_RIGHTSTICK );
            case 10: return SDL_GameControllerGetAxis( controllers[joy], SDL_CONTROLLER_AXIS_TRIGGERLEFT ) > 8000;
            case 11: return SDL_GameControllerGetAxis( controllers[joy], SDL_CONTROLLER_AXIS_TRIGGERRIGHT ) > 8000;
        }
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/* libjoy_get_position_specific (int JOY, int axis)                            */
/* Returns the selected joystick state for the given axis                      */
/* --------------------------------------------------------------------------- */

int libjoy_get_position_specific( int joy, int axis )
{
    if ( joy >= 0 && joy < _max_joys )
    {
        if (axis < 0 || axis >= 4)
            return 0;

        return SDL_GameControllerGetAxis( controllers[ joy ], axis ) ;
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/* Added by Sandman */
/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
/* libjoy_hats_specific (int JOY)                                              */
/* Returns the total number of POV hats of the specified joystick              */
/* --------------------------------------------------------------------------- */

int libjoy_hats_specific( int joy )
{
    if ( joy >= 0 && joy < _max_joys )
    {
        return 1;
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/* libjoy_balls_specific (int JOY)                                             */
/* Returns the total number of balls of the specified joystick                 */
/* --------------------------------------------------------------------------- */

int libjoy_balls_specific( int joy )
{
    return 0;
}

/* --------------------------------------------------------------------------- */
/* libjoy_get_hat_specific (int JOY, int HAT)                                  */
/* Returns the state of the specfied hat on the specified joystick             */
/* --------------------------------------------------------------------------- */

int libjoy_get_hat_specific( int joy, int hat )
{
    int u, d, l, r;
    if ( hat != 0 )
        return 0;
    if ( joy >= 0 && joy < _max_joys )
    {
        if ( hat == 0 )
        {
            u = SDL_HAT_UP    * SDL_GameControllerGetButton( controllers[joy], SDL_CONTROLLER_BUTTON_DPAD_UP );
            d = SDL_HAT_DOWN  * SDL_GameControllerGetButton( controllers[joy], SDL_CONTROLLER_BUTTON_DPAD_DOWN );
            l = SDL_HAT_LEFT  * SDL_GameControllerGetButton( controllers[joy], SDL_CONTROLLER_BUTTON_DPAD_LEFT );
            r = SDL_HAT_RIGHT * SDL_GameControllerGetButton( controllers[joy], SDL_CONTROLLER_BUTTON_DPAD_RIGHT );
            return u | d | l | r;
        }
    }
    return 0 ;

}

/* --------------------------------------------------------------------------- */
/* libjoy_get_ball_specific (int JOY, int BALL, int* dx, int* dy)              */
/* Returns the state of the specfied ball on the specified joystick            */
/* --------------------------------------------------------------------------- */

int libjoy_get_ball_specific( int joy, int ball, int * dx, int * dy )
{
    return -1;
}

/* --------------------------------------------------------------------------- */

int libjoy_get_accel_specific( int joy, int * x, int * y, int * z )
{
    return -1;
}

/* --------------------------------------------------------------------------- */
/* Funciones de inicializacion del modulo/plugin                               */

DLCONSTANT __bgdexport( libjoy, constants_def )[] =
{
    { "JOY_HAT_CENTERED"    , TYPE_DWORD, SDL_HAT_CENTERED  },
    { "JOY_HAT_UP"          , TYPE_DWORD, SDL_HAT_UP        },
    { "JOY_HAT_RIGHT"       , TYPE_DWORD, SDL_HAT_RIGHT     },
    { "JOY_HAT_DOWN"        , TYPE_DWORD, SDL_HAT_DOWN      },
    { "JOY_HAT_LEFT"        , TYPE_DWORD, SDL_HAT_LEFT      },
    { "JOY_HAT_RIGHTUP"     , TYPE_DWORD, SDL_HAT_RIGHTUP   },
    { "JOY_HAT_RIGHTDOWN"   , TYPE_DWORD, SDL_HAT_RIGHTDOWN },
    { "JOY_HAT_LEFTUP"      , TYPE_DWORD, SDL_HAT_LEFTUP    },
    { "JOY_HAT_LEFTDOWN"    , TYPE_DWORD, SDL_HAT_LEFTDOWN  },
    { NULL                  , 0         , 0                 }
} ;

/* --------------------------------------------------------------------------- */

void  __bgdexport( libjoy, module_initialize )()
{
    int i;

    if ( !SDL_WasInit( SDL_INIT_GAMECONTROLLER ) )
    {
        SDL_InitSubSystem( SDL_INIT_GAMECONTROLLER );
        SDL_JoystickEventState( SDL_ENABLE ) ;
    }

    /* Open all joysticks */
    for ( i = 0; i < SDL_NumJoysticks(); i++ )
    {
        if ( !SDL_IsGameController(i) )
            continue;
        
        controllers[_max_joys] = SDL_GameControllerOpen(i);
        if (controllers[_max_joys])
            _max_joys++;
        else
            printf( "[JOY] Failed to open joystick '%i'", i );
    }

    SDL_GameControllerUpdate();
#if 0
    if (( _max_joys = SDL_NumJoysticks() ) > MAX_JOYS )
    {
        printf( "[JOY] Warning: maximum number of joysticks exceeded (%i>%i)", _max_joys, MAX_JOYS );
        _max_joys = MAX_JOYS;
    }

    for ( i = 0; i < _max_joys; i++ )
    {
        _joysticks[i] = SDL_JoystickOpen( i ) ;
        if ( !_joysticks[ i ] ) printf( "[JOY] Failed to open joystick '%i'", i );
    }

    SDL_JoystickUpdate() ;
#endif
}

/* ----------------------------------------------------------------- */

void  __bgdexport( libjoy, module_finalize )()
{
    int i;

#ifdef TARGET_CAANOO
    KIONIX_ACCEL_deinit();
#endif

    for ( i = 0; i < _max_joys; i++ )
        if ( controllers[ i ] ) SDL_GameControllerClose( controllers[ i ] ) ;

    if ( SDL_WasInit( SDL_INIT_GAMECONTROLLER ) ) SDL_QuitSubSystem( SDL_INIT_GAMECONTROLLER );

}

/* ----------------------------------------------------------------- */

char * __bgdexport( libjoy, modules_dependency )[] =
{
    "libsdlhandler",
    NULL
};

/* ----------------------------------------------------------------- */
